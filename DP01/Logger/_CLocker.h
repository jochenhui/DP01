//
//  _CLocker.h
//  fmcore
//
//  Created by 史光伟 on 15/6/23.
//  Copyright (c) 2015年 史光伟. All rights reserved.
//

#ifndef __fmcore___CLocker__
#define __fmcore___CLocker__
//#include "StdAfx.h"  //added by chenhui 20160830
#ifdef __MACH__
#include <libkern/OSAtomic.h>
#endif
#include <stdio.h>
#ifdef _WINDOWS
#include <process.h>
#include <Windows.h>
#endif

class 	_CLocker
{
public:
	_CLocker();
	~_CLocker();
	bool Lock(bool *pbQuit=NULL,HANDLE hQuit=NULL,HANDLE hKill=NULL);
	void UnLock();
private:
	int 	m_Lock;
#ifdef WIN32
	HANDLE	m_hSemaphore;
#endif
};
#endif /* defined(__fmcore___CLocker__) */
