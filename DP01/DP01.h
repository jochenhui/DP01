// DP01.h : DP01 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDP01App
// �йش���ʵ�ֵ���Ϣ������� DP01.cpp
//

class CDP01App : public CWinApp
{
public:
	CDP01App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
