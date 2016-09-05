#include "StdAfx.h"
#ifdef __MACH__
#include <libkern/OSAtomic.h>
#endif
#include <stdio.h>
#include "MessageChain.h"

using namespace DP_MESSAGE;
CMessageChain::CMessageChain(CBaseMessage *pBase)
{
	m_pHead = NULL;
	m_pTail = NULL;

	m_pBase = pBase;

	m_hSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
}

CMessageChain::~CMessageChain()
{
	CBaseMessage *p, *pn;
	p = m_pHead;
	m_pHead = NULL;
	m_pTail = NULL;
	while (p)
	{
		pn = p->m_pNext;
		delete p;
		p = pn;
	}
	if (m_pBase != NULL)
		delete m_pBase;
	CloseHandle(m_hSemaphore);
}

void CMessageChain::Push_NoLock(CBaseMessage *p)
{
	CBaseMessage *pt;

	p->m_pNext = NULL;

	if (m_pHead == NULL)
	{
		m_pHead = p;
		m_pTail = p;
		return;
	}

	pt = m_pTail;
	while (pt->m_pNext)		// 先循环到队列尾
		pt = pt->m_pNext;

	pt->m_pNext = p;

	m_pTail = p;

}
// 增加一个元素
void CMessageChain::Push(CBaseMessage *p)
{
	Lock();
	{
		Push_NoLock(p);
	}
	UnLock();
	ReleaseSemaphore(m_hSemaphore, 1, NULL);
}

// 增加一个元素
void CMessageChain::_unused_Push(CBaseMessage *p)
{
	bool m_bRet;
	CBaseMessage *pt, *pold;

	assert(0);
	p->m_pNext = NULL;

	printf("Chain:%p Push:%p\n", this, p);
	pt = m_pTail;
	pold = pt;


	m_bRet = true;
	while (pt->m_pNext)		// 先循环到队列尾
		pt = pt->m_pNext;
	// if (pt->m_pNext == NULL) pt->m_pNext = p;
	//m_bRet = OSAtomicCompareAndSwapPtr((void*)(NULL), p, (void* volatile *)(&pt->m_pNext));
	while (m_bRet == false)
	{
		while (pt->m_pNext)		// 先循环到队列尾
			pt = pt->m_pNext;
		// if (pt->m_pNext == NULL) pt->m_pNext = p;
		//  m_bRet = OSAtomicCompareAndSwapPtr((void*)(NULL), p, (void* volatile *)(&pt->m_pNext));
	}
	// if (m_pTail == pold) m_pTail = p;
	//m_bRet = OSAtomicCompareAndSwapPtr((void*)pold, p, (void* volatile *)(&m_pTail));

	//	printf("\tm_Head:%p,m_Head->m_pNext:%p\n",m_pHead,m_pHead->m_pNext);
	//	printf("\tm_Tail:%p,m_Tail->m_pNext:%p\n",m_pTail,m_pTail->m_pNext);

}

// 从队列中取出一个元素
CBaseMessage *CMessageChain::_unused_Pop()
{
	bool	m_bRet;
	CBaseMessage *pt;

	assert(0);

	pt = m_pHead;
	if (pt->m_pNext == NULL)
		return NULL;
	m_bRet = true;

	// if (m_pHead == pt) m_pHead = pt->m_pNext;
	//m_bRet = OSAtomicCompareAndSwapPtr((void*)pt, (void*)pt->m_pNext, (void *volatile *)(&m_pHead));
	while (m_bRet == false)
	{
		pt = m_pHead;
		if (pt->m_pNext == NULL)
			return NULL;
		// if (m_pHead == pt) m_pHead = pt->m_pNext;
		//  m_bRet = OSAtomicCompareAndSwapPtr((void*)pt, (void*)pt->m_pNext, (void *volatile *)(&m_pHead));
	}
	//	printf("Chain:%p Pop:%p\n",this,pt->m_pNext);
	//	printf("\tm_Head:%p,m_Head->m_pNext:%p\n",m_pHead,m_pHead->m_pNext);
	//	printf("\tm_Tail:%p,m_Tail->m_pNext:%p\n",m_pTail,m_pTail->m_pNext);
	return pt->m_pNext;
}
CBaseMessage *CMessageChain::Pop_NoLock()
{
	bool	m_bRet;
	CBaseMessage *pt;

	m_bRet = false;
	if (m_pHead == NULL)
	{
		pt = NULL;
		goto L_RET;
	}
	pt = m_pHead;
	m_pHead = m_pHead->m_pNext;
	if (m_pHead == NULL)
		m_pTail = NULL;
L_RET:
	return pt;
}
CBaseMessage *CMessageChain::Pop_NoLock_by_Msytpye(CBaseMessage::MsgTypes msgType)
{
	bool m_bRet;
	CBaseMessage *pt;
	CBaseMessage *pre;
	if (m_pHead == NULL)
	{
		pt = NULL;
		goto L_RET;
	}
	pt = m_pHead;
	if (msgType == pt->m_msgType)//首个命中
	{
		m_pHead = m_pHead->m_pNext;
		if (m_pHead == NULL)
			m_pTail = NULL;
	}
	else
	{
		while (pt&&msgType != pt->m_msgType)//非首个命中
		{
			pre = pt;
			pt = pre->m_pNext;
		}
		if (NULL == pt)//无此消息类型节点
			goto L_RET;
		pre->m_pNext = pt->m_pNext;
	}
L_RET:
	return pt;
}
// 从队列中取出一个元素
CBaseMessage *CMessageChain::Pop()
{
	CBaseMessage *pt;

	// 1. Lock
	Lock();
	{
		pt = Pop_NoLock();
	}
	UnLock();
	return pt;
}

//从链表中分配一个指定类型的节点
CBaseMessage *CMessageChain::AllocatePop(CBaseMessage::MsgTypes msgType)
{
	CBaseMessage *pt;
	// 1. Lock
	Lock();
	{
		pt = Pop_NoLock_by_Msytpye(msgType);
	}
	UnLock();
/*	pt = Pop();*/
// 	if (pt == NULL)
// 	{
// 		//		pt = new CPackage();
// 		pt = m_pBase->New();
// 		pt->m_pNext = NULL;
// 	}
	return pt;
}

bool DP_MESSAGE::CMessageChain::WaitNew(bool * bQuit, HANDLE hQuit, HANDLE hKill)
{
	HANDLE h[3];
	int hc;
	DWORD dwRet, dwi;

	int iq = -1;
	h[0] = m_hSemaphore;
	hc = 1;
	if (hQuit)
	{
		iq = hc;
		h[hc++] = hQuit;
	}
	if (hKill)
		h[hc++] = hKill;
	dwRet = WaitForMultipleObjects(hc, h, false, INFINITE);
	switch (dwRet)
	{
	case WAIT_TIMEOUT:
	case WAIT_FAILED:
		return false;
	default:
		dwi = dwRet - WAIT_OBJECT_0;
		if (dwi == iq)
		{
			ReleaseSemaphore(hQuit, 1, NULL);
		}
		if (dwi != 0)
		{
			if (bQuit)
			{
				*bQuit = true;
			}
			return false;
		}
	}
	return true;
}
