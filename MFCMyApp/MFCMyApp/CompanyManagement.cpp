// CompanyManagement.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "CompanyManagement.h"
#include "afxdialogex.h"


// CompanyManagement dialog

IMPLEMENT_DYNAMIC(CompanyManagement, CDialogEx)

CompanyManagement::CompanyManagement(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_COMPANY, pParent)
{

}

CompanyManagement::~CompanyManagement()
{
	if (sql_get_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_get_handle);
	}
	if (sql_connection_handle != SQL_NULL_HDBC) {
		SQLDisconnect(sql_connection_handle);
		SQLFreeHandle(SQL_HANDLE_DBC, sql_connection_handle);
	}

	if (sql_env_handle != SQL_NULL_HENV) {
		SQLFreeHandle(SQL_HANDLE_ENV, sql_env_handle);
	}
}

BOOL CompanyManagement::OnInitDialog() {
	CDialogEx::OnInitDialog();
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_COM));
	SetIcon(hIcon, FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CompanyManagement::StartDialog() {
	lcl_company.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVCFMT_FIXED_RATIO);
	lcl_company.InsertColumn(0, _T("ON"), LVCFMT_LEFT, 30);
	lcl_company.InsertColumn(1, _T("NAME"), LVCFMT_LEFT, 100);
	lcl_company.InsertColumn(2, _T("INTRODUCE"), LVCFMT_LEFT, 250);
	lcl_company.InsertColumn(3, _T("ADDRESS"), LVCFMT_LEFT, 200);
	lcl_company.InsertColumn(4, _T("EMAIL"), LVCFMT_LEFT, 120);
	lcl_company.InsertColumn(5, _T("NUM OF STUDENTS"), LVCFMT_LEFT, 100);

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
		break;
	case SQL_INVALID_HANDLE:
		break;
	case SQL_ERROR:
		retcode = -1;
		break;
	default:
		break;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_edit_handle)) {
		connected = false;
		return;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_add_handle)) {
		connected = false;
		return;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_delete_handle)) {
		connected = false;
		return;
	}
}

void CompanyManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LCL_COMPANY_LIST, lcl_company);

	if (start == true) {
		start = false;
		StartDialog();
		/*UpdateCompanyList();*/
	}
}


BEGIN_MESSAGE_MAP(CompanyManagement, CDialogEx)
	ON_BN_CLICKED(IDOK, &CompanyManagement::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_ADD_COMDLG, &CompanyManagement::OnBnClickedBtnAddComdlg)
	ON_BN_CLICKED(IDC_BTN_EDIT_COMDLG, &CompanyManagement::OnBnClickedBtnEditComdlg)
	ON_BN_CLICKED(ID_DELETE_COMDLG, &CompanyManagement::OnBnClickedDeleteComdlg)
	ON_BN_CLICKED(IDC_BTN_LOAD_COMDLG, &CompanyManagement::OnBnClickedBtnLoadComdlg)
END_MESSAGE_MAP()


// CompanyManagement message handlers

void CompanyManagement::UpdateCompanyList() 
{
	UpdateData(TRUE);
	do
	{
		if (retcode == -1) {
			break;
		}
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
			break;
		}
		if (SQL_SUCCESS != SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from company", SQL_NTS))
		{
			MessageBox(_T("get data failed"));
			break;
		}
		else
		{
			lcl_company.SetRedraw(FALSE);
			lcl_company.DeleteAllItems();
			lcl_company.SetRedraw(TRUE);

			char cname[50], introduce[100], email[50], address[50];
			int total_students = 0;
			int num_of_students;
			int stt = 0;
			while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
			{
				SQLGetData(sql_get_handle, 1, SQL_C_CHAR, cname, 50, NULL);
				SQLGetData(sql_get_handle, 2, SQL_C_CHAR, introduce, 100, NULL);
				SQLGetData(sql_get_handle, 3, SQL_C_CHAR, address, 50, NULL);
				SQLGetData(sql_get_handle, 4, SQL_C_CHAR, email, 50, NULL);
				SQLGetData(sql_get_handle, 5, SQL_C_DEFAULT, &num_of_students, 0, NULL);
				total_students += num_of_students;
				lcl_company.InsertItem(stt, std::to_string(stt+1).c_str());
				lcl_company.SetItemText(stt, 1, cname);
				lcl_company.SetItemText(stt, 2, introduce);
				lcl_company.SetItemText(stt, 3, address);
				lcl_company.SetItemText(stt, 4, email);
				lcl_company.SetItemText(stt, 5, std::to_string(num_of_students).c_str());
				stt++;
			}
			lcl_company.InsertItem(stt, _T("Total"));
			lcl_company.SetItemText(stt,5,std::to_string(total_students).c_str());
			/*MessageBox(_T("Successfully!"));*/

		}
	} while (FALSE);
	UpdateData(FALSE);
};
void CompanyManagement::OnBnClickedOk()
{
	
}


void CompanyManagement::OnBnClickedBtnAddComdlg()
{
	AddCompany ac;
	ac.SetHandle(sql_add_handle);
	ac.DoModal();
	UpdateCompanyList();
}


void CompanyManagement::OnBnClickedBtnEditComdlg()
{
	int num_company = lcl_company.GetItemCount() - 1;
	int selected_row = -1;
	for (int i = 0; i < num_company; i++) {
		if (lcl_company.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			selected_row = i;
			break;
		}
	}

	if (selected_row != -1) {
		CString cname = lcl_company.GetItemText(selected_row, 1);// 0 is ordinal number
		CString cintro = lcl_company.GetItemText(selected_row, 2);
		CString caddr = lcl_company.GetItemText(selected_row, 3);
		CString cemail = lcl_company.GetItemText(selected_row, 4);

		EditCompany ec;
		ec.SetInfo(cname, caddr, cemail, cintro);
		ec.SetHandle(sql_edit_handle);
		ec.DoModal();
		UpdateCompanyList();
	}
}


void CompanyManagement::OnBnClickedDeleteComdlg()
{
	int num_company = lcl_company.GetItemCount() - 1;
	int selected_row = -1;
	for (int i = 0; i < num_company; i++) {
		if (lcl_company.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			selected_row = i;
			break;
		}
	}

	if (selected_row != -1) {
		if (MessageBox(_T("OK"), _T("Confirm"), MB_OKCANCEL) == IDOK) {
			CString selected_id = lcl_company.GetItemText(selected_row, 1); //get id select
			if (connected == false) {
				MessageBox(_T("connecte failed!"));
				return;
			}
			else {
				SQLINTEGER cb1 = SQL_NTS;
				char name[50];

				SQLBindParameter(sql_delete_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, name, 0, &cb1);

				sprintf_s(name, "%s", selected_id);

				SQLExecDirect(sql_delete_handle, (SQLCHAR*)"delete from company where cname =?", SQL_NTS);
			}
			lcl_company.DeleteItem(selected_row);
			UpdateCompanyList();

			SQLFreeStmt(sql_delete_handle, SQL_CLOSE);
			SQLFreeStmt(sql_delete_handle, SQL_UNBIND);
			SQLFreeStmt(sql_delete_handle, SQL_RESET_PARAMS);
		}
		else {

		}
	}

	
}


void CompanyManagement::OnBnClickedBtnLoadComdlg()
{
	UpdateCompanyList();
}
