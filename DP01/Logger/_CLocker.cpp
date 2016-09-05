//
//  _CLocker.cpp
//  fmcore
//
//  Created by 史光伟 on 15/6/23.
//  Copyright (c) 2015年 史光伟. All rights reserved.
//
#include "_CLocker.h"


_CLocker::_CLocker()
{
	m_Lock = 0;
#ifdef WIN32
	m_hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
#endif
}
_CLocker::~_CLocker()
{
#ifdef WIN32
	CloseHandle(m_hSemaphore);
#endif
}

bool _CLocker::Lock(bool *pbQuit,HANDLE hQuit,HANDLE hKill)
{
#ifdef __MACH__
	bool m_bRet;

	while (m_bRet == false)
	{
		if (pbQuit)
		{
			if (*pbQuit == true)
				return false;
		}
		m_bRet = OSAtomicCompareAndSwap32(0, 1, &m_Lock);
	}
	return true;
#else
	m_Lock = 1;

	HANDLE h[3];
	int hc;
	DWORD dwRet,dwi;

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
			if (pbQuit)
			{
				*pbQuit = true;
			}
			return false;
		}
	}
	return true;
#endif
}

void _CLocker::UnLock()
{
	m_Lock = 0;
#ifdef WIN32
	ReleaseSemaphore(m_hSemaphore, 1, NULL);
#endif
}
