// EditCompany.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "EditCompany.h"
#include "afxdialogex.h"


// EditCompany dialog

IMPLEMENT_DYNAMIC(EditCompany, CDialogEx)

EditCompany::EditCompany(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_EDIT_COMPANY, pParent)
{

}

EditCompany::~EditCompany()
{
}

void EditCompany::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_COM_NAME_EDIT, edt_name_com_edit);
	DDX_Control(pDX, IDC_EDT_COM_INTRO_EDIT, edt_intro_com_edit);
	DDX_Control(pDX, IDC_EDT_COM_ADDR_EDIT, edt_addr_com_edit);
	DDX_Control(pDX, IDC_EDT_COM_EMAIL_EDIT, edt_email_com_edit);

	if (start == true) {
		start = false;
		StartDialog();
	}
}


BEGIN_MESSAGE_MAP(EditCompany, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditCompany::OnBnClickedOk)
END_MESSAGE_MAP()


// EditCompany message handlers
void EditCompany::StartDialog()
{
	edt_name_com_edit.EnableWindow(FALSE);
	edt_addr_com_edit.SetLimitText(49);
	edt_email_com_edit.SetLimitText(49);
	edt_intro_com_edit.SetLimitText(99);

	edt_name_com_edit.SetWindowText(cs_cname);
	edt_addr_com_edit.SetWindowText(cs_caddr);
	edt_email_com_edit.SetWindowText(cs_cemail);
	edt_intro_com_edit.SetWindowText(cs_cintro);

}

void EditCompany::SetHandle(SQLHANDLE handle)
{
	sql_edit_handle = handle;
}

void EditCompany::SetInfo(CString name, CString addr, CString email, CString intro) 
{
	cs_cname = name;
	cs_caddr = addr;
	cs_cemail = email;
	cs_cintro = intro;
}

void EditCompany::OnBnClickedOk()
{
	if (MessageBox(_T("OK"), _T("Confirm"), MB_OKCANCEL) == IDOK) {
		CString cname, cemail, cintro, caddr;
		edt_addr_com_edit.GetWindowText(caddr);
		edt_name_com_edit.GetWindowText(cname);
		edt_email_com_edit.GetWindowText(cemail);
		edt_intro_com_edit.GetWindowText(cintro);

		SQLINTEGER cb1 = SQL_NTS, cb2 = SQL_NTS, cb3 = SQL_NTS, cb4 = SQL_NTS, cb5 = SQL_NTS;
		char name[50], email[50], addr[50], intro[100];

		SQLBindParameter(sql_edit_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, intro, 0, &cb1);
		SQLBindParameter(sql_edit_handle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, addr, 0, &cb2);
		SQLBindParameter(sql_edit_handle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, email, 0, &cb3);
		SQLBindParameter(sql_edit_handle, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, name, 0, &cb4);

		sprintf_s(email, "%s", cemail);
		sprintf_s(name, "%s", cname);
		sprintf_s(intro, "%s", cintro);
		sprintf_s(addr, "%s", caddr);


		SQLExecDirect(sql_edit_handle, (SQLCHAR*)"update company set introduce = ?, address = ?, email = ? where cname = ?", SQL_NTS);

		SQLFreeStmt(sql_edit_handle, SQL_CLOSE);
		SQLFreeStmt(sql_edit_handle, SQL_UNBIND);
		SQLFreeStmt(sql_edit_handle, SQL_RESET_PARAMS);
		CDialogEx::OnOK();
	}
	else {

	}
}
