// EditStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "EditStudent.h"
#include "afxdialogex.h"


// EditStudent dialog

IMPLEMENT_DYNAMIC(EditStudent, CDialogEx)

EditStudent::EditStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_EDIT_STUDENT, pParent)
{

}

EditStudent::~EditStudent()
{
	if (sql_update_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_update_handle);
		sql_update_handle = NULL;
	}
	if (sql_connection_handle != SQL_NULL_HDBC) {
		SQLDisconnect(sql_connection_handle);
		SQLFreeHandle(SQL_HANDLE_DBC, sql_connection_handle);
		sql_connection_handle = NULL;
	}

	if (sql_env_handle != SQL_NULL_HENV) {
		SQLFreeHandle(SQL_HANDLE_ENV, sql_env_handle);
		sql_env_handle = NULL;
	}
}

void EditStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBX_FALCULTY_EDITSDLG, cbx_falculty_editdlg);
	DDX_Control(pDX, IDC_EDIT1, edt_name_editdlg);
	DDX_Control(pDX, IDC_EDIT2, edt_email);
	DDX_Control(pDX, IDC_EDIT3, edit_company_editdlg);
	DDX_Control(pDX, IDC_TXT_SID_EDITDIALOG, txt_student_id_edtdlg);
	if (start == true) {//started
		start = false;
		StartDialog();
	}
}
void EditStudent::StartDialog() {
	edt_email.SetLimitText(49);
	edit_company_editdlg.SetLimitText(49);
	edt_name_editdlg.SetLimitText(49);

	cbx_falculty_editdlg.AddString(_T("Computer Science"));
	cbx_falculty_editdlg.AddString(_T("Computer Engineering"));
	if (student_falculty == _T("Computer Engineering")) {
		cbx_falculty_editdlg.SetCurSel(0);
	}
	else {
		cbx_falculty_editdlg.SetCurSel(1);
	}

	txt_student_id_edtdlg.SetWindowText(student_id);
	edt_name_editdlg.SetWindowText(student_name);
	edt_email.SetWindowText(student_email);
	edit_company_editdlg.SetWindowText(student_company);

	GetConnectDB();
}

//void EditStudent::SetHandle(SQLHANDLE handle)
//{
//	sql_update_handle = handle;
//}

BEGIN_MESSAGE_MAP(EditStudent, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditStudent::OnBnClickedOk)
END_MESSAGE_MAP()

void EditStudent::SetID(CString ID) 
{ 
	student_id = ID;
}
void EditStudent::GetConnectDB() {
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sql_env_handle)) {
		connected = false;
	}
	if (SQL_SUCCESS != SQLSetEnvAttr(sql_env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
		connected = false;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sql_env_handle, &sql_connection_handle)) {
		connected = false;
	}
	SQLCHAR retconstring[1024];
	switch (SQLDriverConnect(sql_connection_handle, NULL,
		(SQLCHAR*)"DRIVER={SQL Server};SERVER=LAPTOP-V3RHTVBG\\SQLEXPRESS;DATABASE=Intern;Trusted_Connection=yes;",
		SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT))
	{
	case SQL_SUCCESS_WITH_INFO:
		//MessageBox(_T("SQL_SUCCESS_WITH_INFO"));
		break;
	case SQL_INVALID_HANDLE:
		//MessageBox(_T("SQL_INVALID_HANDLE"));
		break;
	case SQL_ERROR:
		//MessageBox(_T("SQL_ERROR"));
		break;
	default:
		//MessageBox(_T("DEFAULT"));
		break;
	}

	
}
// EditStudent message handlers
void EditStudent::SetInfo(CString falculty, CString name, CString email, CString company)
{
	student_falculty = falculty;
	student_name = name;
	student_email = email;
	student_company = company;
}

void EditStudent::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (MessageBox(_T("Are you sure?"), _T("Confirm"), MB_OKCANCEL) == IDOK) {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_update_handle)) {
			//MessageBox(_T("connect failed"));
			return;
		}
		edt_email.GetWindowText(student_email);
		edt_name_editdlg.GetWindowText(student_name);
		edit_company_editdlg.GetWindowText(student_company);
		cbx_falculty_editdlg.GetLBText(cbx_falculty_editdlg.GetCurSel(), student_falculty);
		SQLINTEGER cb1 = SQL_NTS;
		SQLINTEGER cb2 = SQL_NTS;
		SQLINTEGER cb3 = SQL_NTS;
		SQLINTEGER cb4 = SQL_NTS;
		SQLINTEGER cb5 = SQL_NTS;
		char id[10],name[50],email[50],falculty[50],company[50];

		SQLBindParameter(sql_update_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, email, 0, &cb1);
		SQLBindParameter(sql_update_handle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, name, 0, &cb2);
		SQLBindParameter(sql_update_handle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, falculty, 0, &cb3);
		SQLBindParameter(sql_update_handle, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, company, 0, &cb4);
		SQLBindParameter(sql_update_handle, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 10, 0, id, 0, &cb5);

		sprintf_s(email, "%s", student_email);
		sprintf_s(name, "%s", student_name);
		sprintf_s(falculty, "%s", student_falculty);
		sprintf_s(company, "%s", student_company);
		sprintf_s(id, "%s", student_id);

		SQLExecDirect(sql_update_handle, (SQLCHAR*)"update student set email = ?, s_name = ?, falculty = ?, company = ? where id = ?", SQL_NTS);
		
		SQLFreeStmt(sql_update_handle, SQL_CLOSE);
		SQLFreeStmt(sql_update_handle, SQL_UNBIND);
		SQLFreeStmt(sql_update_handle, SQL_RESET_PARAMS);
		OnOK();
	}
	UpdateData(FALSE);
}
