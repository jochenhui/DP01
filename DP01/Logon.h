#pragma once
#include "afxwin.h"
#include "resource.h"

// Logon �Ի���

class Logon : public CDialogEx
{
	DECLARE_DYNAMIC(Logon)

public:
	Logon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Logon();
	virtual BOOL OnInitDialog();

	//{{AFX_DATA(LogonDlg)
	CEdit m_edtUser;
	CEdit m_edtPass;
	//}}AFX_DATA

// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGINDLG };
//#endif

	CString m_csUserID, m_csPassword;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedClose();
	afx_msg void OnEnChangeEdit1();
};
