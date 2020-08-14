// AddCompany.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "AddCompany.h"
#include "afxdialogex.h"


// AddCompany dialog

IMPLEMENT_DYNAMIC(AddCompany, CDialogEx)

AddCompany::AddCompany(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_ADD_COMPANY, pParent)
{
	
}

AddCompany::~AddCompany()
{
	
}

void AddCompany::StartDialog() {
	edt_name_com_add.SetLimitText(49);
	edt_email_com_add.SetLimitText(49);
	edt_addr_com_add.SetLimitText(49);
	edt_intro_com_add.SetLimitText(99);
	
}
void AddCompany::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_COM_NAME, edt_name_com_add);
	DDX_Control(pDX, IDC_EDT_COM_INTRO, edt_intro_com_add);
	DDX_Control(pDX, IDC_EDT_COM_ADDR, edt_addr_com_add);
	DDX_Control(pDX, IDC_EDT_COM_EMAIL, edt_email_com_add);
	if (start == true) {
		start = false;
		StartDialog();
	}
}


BEGIN_MESSAGE_MAP(AddCompany, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddCompany::OnBnClickedOk)
END_MESSAGE_MAP()


// AddCompany message handlers

void AddCompany::SetHandle(SQLHANDLE handle) {
	sql_add_handle = handle;
}
void AddCompany::OnBnClickedOk()
{
	if (MessageBox(_T("Are you sure?"), _T("confirm"), MB_OKCANCEL) == IDOK) {
		UpdateData(TRUE);

		CString csName, csIntro, csAddr, csEmail;
		edt_name_com_add.GetWindowText(csName);
		edt_intro_com_add.GetWindowText(csIntro);
		edt_addr_com_add.GetWindowText(csAddr);
		edt_email_com_add.GetWindowText(csEmail);

		SQLINTEGER cb1 = SQL_NTS, cb2 = SQL_NTS, cb3 = SQL_NTS, cb4 = SQL_NTS;
		char name[50], intro[100], email[50], addr[50];

		SQLBindParameter(sql_add_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, name, 0, &cb1);
		SQLBindParameter(sql_add_handle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, intro, 0, &cb2);
		SQLBindParameter(sql_add_handle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, addr, 0, &cb3);
		SQLBindParameter(sql_add_handle, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, email, 0, &cb4);

		sprintf_s(name, "%s", csName);
		sprintf_s(intro, "%s", csIntro);
		sprintf_s(addr, "%s", csAddr);
		sprintf_s(email, "%s", csEmail);

		//MessageBox(uname);
		SQLExecDirect(sql_add_handle, (SQLCHAR*)"INSERT INTO company(cname, introduce, address, email) VALUES(?,?,?,?);", SQL_NTS);
		
		SQLFreeStmt(sql_add_handle, SQL_CLOSE);
		SQLFreeStmt(sql_add_handle, SQL_UNBIND);
		SQLFreeStmt(sql_add_handle, SQL_RESET_PARAMS);
		UpdateData(FALSE);
		CDialogEx::OnOK();
	}
}
