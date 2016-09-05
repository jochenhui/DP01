// Logon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DP01.h"
#include "Logon.h"
#include "afxdialogex.h"


// Logon �Ի���

IMPLEMENT_DYNAMIC(Logon, CDialogEx)

Logon::Logon(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGINDLG, pParent)
{

}

Logon::~Logon()
{
}

BOOL Logon::OnInitDialog() {
	CDialogEx::OnInitDialog();
	m_edtUser.SetFocus();
	return FALSE;
}

void Logon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtUser);
	DDX_Control(pDX, IDC_EDIT2, m_edtPass);
}


BEGIN_MESSAGE_MAP(Logon, CDialogEx)
	ON_BN_CLICKED(IDOK, &Logon::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Logon::OnBnClickedClose)
	ON_EN_CHANGE(IDC_EDIT1, &Logon::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Logon ��Ϣ�������

void Logon::OnBnClickedOk()
{
	wchar_t szUserID[32], szPwd[32];
	m_edtPass.GetWindowText(szPwd, _countof(szPwd));
	m_edtUser.GetWindowText(szUserID, _countof(szUserID));

	m_csUserID = szUserID;
	m_csPassword = szPwd;

	CDialogEx::OnOK();
}



void Logon::OnBnClickedClose()
{
	CDialogEx::OnCancel();
}



void Logon::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
