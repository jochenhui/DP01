#pragma once
#include "BaseMessage.h"
#include "_CLocker.h"

namespace DP_MESSAGE
{

class CMessageChain : public _CLocker
{
public:
	CMessageChain(CBaseMessage *pBase);
	~CMessageChain();
	void Push(CBaseMessage *p);
	void Push_NoLock(CBaseMessage *p);
	CBaseMessage *Pop();
	CBaseMessage *Pop_NoLock();
	CBaseMessage *Pop_NoLock_by_Msytpye(CBaseMessage::MsgTypes msgType);//--chenhui
	CBaseMessage *AllocatePop(CBaseMessage::MsgTypes msgType);
	bool		  WaitNew(bool *bQuit = NULL, HANDLE hQuit = NULL, HANDLE hKill = NULL);
private:
	CBaseMessage *m_pHead;
	CBaseMessage *m_pTail;
	CBaseMessage *m_pBase;

	HANDLE		  m_hSemaphore;
	void _unused_Push(CBaseMessage *p);
	CBaseMessage * _unused_Pop(void);
};
}

