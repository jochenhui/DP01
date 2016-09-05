// Logon.cpp : 实现文件
//

#include "stdafx.h"
#include "DP01.h"
#include "Logon.h"
#include "afxdialogex.h"


// Logon 对话框

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


// Logon 消息处理程序

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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
