// StudentManagement.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "StudentManagement.h"
#include "afxdialogex.h"

//#include "stdafx.h"

#define ARRAY_SIZE 10

// StudentManagement dialog

IMPLEMENT_DYNAMIC(StudentManagement, CDialogEx)

StudentManagement::StudentManagement(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_STUDENT, pParent)
	, rad_search_id(0)
	, rad_search_name(1)
{

}

StudentManagement::~StudentManagement()
{
	if (sql_delete_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_delete_handle);
		sql_delete_handle = NULL;
	}
	if (sql_update_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_update_handle);
		sql_update_handle = NULL;
	}
	if (sql_check_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_check_handle);
		sql_check_handle = NULL;
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

BOOL StudentManagement::OnInitDialog() {
	CDialogEx::OnInitDialog();
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_STD));
	SetIcon(hIcon, FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void StudentManagement::startDialog() {
	edt_sid.SetLimitText(9);
	edt_sname.SetLimitText(49);
	edt_email.SetLimitText(49);

	cbx_sfalculty.AddString(_T("Computer Engineering"));
	cbx_sfalculty.AddString(_T("Computer Science"));
	cbx_sfalculty.SetCurSel(0);

	lcl_list_student.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVCFMT_FIXED_RATIO);
	lcl_list_student.InsertColumn(0, _T("ON"), LVCFMT_LEFT, 40);
	lcl_list_student.InsertColumn(1, _T("ID"), LVCFMT_LEFT, 70);
	lcl_list_student.InsertColumn(2, _T("NAME"), LVCFMT_LEFT, 140);
	lcl_list_student.InsertColumn(3, _T("EMAIL"), LVCFMT_LEFT, 140);
	lcl_list_student.InsertColumn(4, _T("FALCULTY"), LVCFMT_LEFT, 130);
	lcl_list_student.InsertColumn(5, _T("COMPANY"), LVCFMT_LEFT, 130);

	hstmt = SQL_NULL_HSTMT;
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
	if (retcode == -1) {
		connected = false;
		return;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_update_handle)) {
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

	//
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
		MessageBox(_T("get handle failed"));
	}
	if (SQL_SUCCESS != SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from company", SQL_NTS))
	{
		MessageBox(_T("execdirect get failed"));
	}
	else
	{
		char id[50], intro[100], addr[50], email[50];
		int num;
		while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
		{
			SQLGetData(sql_get_handle, 1, SQL_C_CHAR, id, 50, NULL);
			cbx_company_list.AddString((CString)id);
		}

	}
	SQLFreeStmt(sql_get_handle, SQL_CLOSE);
	SQLFreeStmt(sql_get_handle, SQL_UNBIND);
	SQLFreeStmt(sql_get_handle, SQL_RESET_PARAMS);
	//
}

void StudentManagement::UpdateStudentCount() {
	int position = lcl_list_student.GetItemCount();
	CString str_count = std::to_string(position).c_str();
	txt_count_student_stddlg.SetWindowText(str_count);
}

void StudentManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_SID, edt_sid);
	DDX_Control(pDX, IDC_EDT_SNAME, edt_sname);
	DDX_Control(pDX, IDC_EDT_SEMAIL, edt_email);
	//DDX_Control(pDX, IDC_EDT_SCOMPANY, edt_scompany);
	DDX_Control(pDX, IDC_CBX_SFALCULTY, cbx_sfalculty);
	DDX_Control(pDX, IDC_LBX_STUDENT, lcl_list_student);
	DDX_Control(pDX, IDC_TXT_COUNT_STUDENT, txt_count_student_stddlg);
	DDX_Control(pDX, IDC_CBX_COMPANY, cbx_company_list);
	DDX_Control(pDX, IDC_EDT_SEARCH, edt_search_stddlg);
	DDX_Check(pDX, IDC_RAD_SEARCH_ID, rad_search_id);
	DDX_Check(pDX, IDC_RAD_SEARCH_NAME, rad_search_name);
	if (start == TRUE) {
		start = FALSE;
		startDialog();
	}
}


BEGIN_MESSAGE_MAP(StudentManagement, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SM_ADD, &StudentManagement::OnBnClickedBtnSmAdd)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &StudentManagement::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_DELETE, &StudentManagement::OnBnClickedBtnDelete)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BTN_EDIT_STDDLG, &StudentManagement::OnBnClickedBtnEditStddlg)
	ON_STN_CLICKED(IDC_TXT_COUNT_STUDENT, &StudentManagement::OnStnClickedTxtCountStudent)
	ON_BN_CLICKED(IDC_BTN_EDIT_SCORE, &StudentManagement::OnBnClickedBtnEditScore)
END_MESSAGE_MAP()

void StudentManagement::UpdateStudentList()
{
	UpdateData(TRUE);
	do
	{
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
			MessageBox(_T("get handle failed"));
		}
		if (SQL_SUCCESS != SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from student", SQL_NTS))
		{
			MessageBox(_T("execdirect get failed"));
			break;
		}
		else
		{
			lcl_list_student.SetRedraw(FALSE);
			lcl_list_student.DeleteAllItems();
			lcl_list_student.SetRedraw(TRUE);
			int stt = 0;
			char id[10], username[50], email[50], sname[50], falculty[50], company[50];
			while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
			{
				SQLGetData(sql_get_handle, 1, SQL_C_CHAR, id, 10, NULL);
				SQLGetData(sql_get_handle, 2, SQL_C_CHAR, username, 50, NULL);
				SQLGetData(sql_get_handle, 3, SQL_C_CHAR, sname, 50, NULL);
				SQLGetData(sql_get_handle, 4, SQL_C_CHAR, email, 50, NULL);
				SQLGetData(sql_get_handle, 5, SQL_C_CHAR, falculty, 50, NULL);
				SQLGetData(sql_get_handle, 6, SQL_C_CHAR, company, 50, NULL);
				lcl_list_student.InsertItem(stt, std::to_string(stt+1).c_str());
				lcl_list_student.SetItemText(stt, 1, id);
				lcl_list_student.SetItemText(stt, 2, sname);
				lcl_list_student.SetItemText(stt, 3, email);
				lcl_list_student.SetItemText(stt, 4, falculty);
				lcl_list_student.SetItemText(stt++, 5, company);
			}
			/*MessageBox(_T("Successfully!"));*/

		}
	} while (FALSE);
	SQLFreeStmt(sql_get_handle, SQL_CLOSE);
	SQLFreeStmt(sql_get_handle, SQL_UNBIND);
	SQLFreeStmt(sql_get_handle, SQL_RESET_PARAMS);
	UpdateData(FALSE);
	UpdateStudentCount();
	/*if (sql_get_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_get_handle);
		sql_get_handle = NULL;
	}*/
}

void StudentManagement::OnLButtonDblClk(UINT nFlags, CPoint point) {
	/*POSITION pos = lcl_list_student.GetFirstSelectedItemPosition();
	if (pos == NULL) {

	}
	else {
		int n = lcl_list_student.GetNextSelectedItem(pos);
		CString str = std::to_string(n).c_str();
		MessageBox(str);
	}*/
	
	//MessageBox(_T(output));
	/*CString str_ = _T("-");
	CString str0 = lcl_list_student.GetItemText(0,1);
	CString str1 = lcl_list_student.GetItemText(1,1);
	CString str2 = lcl_list_student.GetItemText(2,1);
	MessageBox(str + str_ + str0 + str_ + str1 + str_ + str2);*/

	/*int position = lcl_list_student.GetSelectionMark();
	CString str_position = std::to_string(position).c_str();
	MessageBox(str_position);*/
}

void StudentManagement::OnBnClickedBtnSmAdd()
{
	UpdateData(TRUE);
	bool allow_add = true;
	CString str_ID, str_name, str_email, str_company, str_falculty;
	edt_sid.GetWindowText(str_ID);
	edt_sname.GetWindowText(str_name);
	edt_email.GetWindowText(str_email);
	cbx_sfalculty.GetLBText(cbx_sfalculty.GetCurSel(), str_falculty);

	if (str_ID.GetLength() == 0) {
		MessageBox(_T("ID IS EMPTY!"));
	}
	else if (str_name.GetLength() == 0){
		MessageBox(_T("NAME IS EMPTY!"));
	}
	else if (str_email.GetLength() == 0) {
		MessageBox(_T("EMAIL IS EMPTY!"));
	}
	else if (cbx_company_list.GetCurSel() == -1) {
		MessageBox(_T("COMPANY IS EMPTY!"));
	}
	else {
		cbx_company_list.GetLBText(cbx_company_list.GetCurSel(), str_company);
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_check_handle)) {
			MessageBox(_T("check handle failed"));
		}
		if (SQL_SUCCESS != SQLExecDirect(sql_check_handle, (SQLCHAR*)"select * from Student", SQL_NTS))
		{
			MessageBox(_T("execDirect check error"));
			return;
		}
		CString cs_id, cs_sname, cs_email;
		char id[10], username[50], email[50], sname[50], falculty[50], company[50];
		while (SQLFetch(sql_check_handle) == SQL_SUCCESS)
		{
			SQLGetData(sql_check_handle, 1, SQL_C_CHAR, id, 10, NULL);
			SQLGetData(sql_check_handle, 2, SQL_C_CHAR, username, 50, NULL);
			SQLGetData(sql_check_handle, 3, SQL_C_CHAR, sname, 50, NULL);
			SQLGetData(sql_check_handle, 4, SQL_C_CHAR, email, 50, NULL);
			SQLGetData(sql_check_handle, 5, SQL_C_CHAR, falculty, 50, NULL);
			SQLGetData(sql_check_handle, 6, SQL_C_CHAR, company, 50, NULL);
			if (str_ID == (CString)id) {
				allow_add = false;
				MessageBox(_T("ID is already exists"));
				break;
			}
			else if (str_email == (CString)email) {
				allow_add = false;
				MessageBox(_T("EMAIL is already exists"));
				break;
			}
		}
		SQLFreeStmt(sql_check_handle, SQL_CLOSE);
		SQLFreeStmt(sql_check_handle, SQL_UNBIND);
		SQLFreeStmt(sql_check_handle, SQL_RESET_PARAMS);
		if (allow_add == false) {
			//MessageBox(_T("allow = false"));
			return;
		}
		else {
			/*lcl_list_student.InsertItem(0, 0);
			lcl_list_student.SetItemText(0, 1, str_ID);
			lcl_list_student.SetItemText(0, 2, str_name);
			lcl_list_student.SetItemText(0, 3, str_email);
			lcl_list_student.SetItemText(0, 4, str_falculty);
			lcl_list_student.SetItemText(0, 5, str_company);*/

			SQLINTEGER cb1 = SQL_NTS, cb2 = SQL_NTS, cb3 = SQL_NTS, cb4 = SQL_NTS, cb5 = SQL_NTS, cb6 = SQL_NTS;
			char id[10], name[50], uname[30], email[50], falculty[50], company[50];

			SQLBindParameter(sql_add_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 10, 0, id, 0, &cb1);
			SQLBindParameter(sql_add_handle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 30, 0, uname, 0, &cb2);
			SQLBindParameter(sql_add_handle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, name, 0, &cb3);
			SQLBindParameter(sql_add_handle, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, email, 0, &cb4);
			SQLBindParameter(sql_add_handle, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, falculty, 0, &cb5);
			SQLBindParameter(sql_add_handle, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, company, 0, &cb6);
			sprintf_s(id, "%s", str_ID);
			sprintf_s(name, "%s", str_name);
			sprintf_s(uname, "%s", _T("Pep"));
			sprintf_s(email, "%s", str_email);
			sprintf_s(falculty, "%s", str_falculty);
			sprintf_s(company, "%s", str_company);
			//MessageBox(uname);
			SQLExecDirect(sql_add_handle, (SQLCHAR*)"INSERT INTO student(id,username,s_name,email,falculty,company) VALUES(?,?,?,?,?,?);", SQL_NTS);
			//SQLExecDirect(sql_edit_handle, (SQLCHAR*)"DELETE FROM student where id='123'", SQL_NTS);
			//SQLExecDirect(sql_edit_handle, (SQLCHAR*)"INSERT INTO student(id,username,s_name,email,falculty,company) VALUES('123','Jose','Dung','nul','nul','nul');", SQL_NTS);
			edt_sid.SetWindowText(_T(""));
			edt_sname.SetWindowText(_T(""));
			edt_email.SetWindowText(_T(""));
			cbx_company_list.SetCurSel(-1);
		}
		
	}

	SQLFreeStmt(sql_add_handle, SQL_CLOSE);
	SQLFreeStmt(sql_add_handle, SQL_UNBIND);
	SQLFreeStmt(sql_add_handle, SQL_RESET_PARAMS);
	UpdateData(FALSE);
	UpdateStudentList();
	UpdateStudentCount();
}

void StudentManagement::OnBnClickedBtnGetData()
{
	//Search 
	
	CString condition;
	edt_search_stddlg.GetWindowText(condition);
	if (condition.GetLength() > 0) {
		UpdateData(TRUE);
		do
		{
			if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
				MessageBox(_T("get handle failed"));
			}
			else
			{
				SQLINTEGER cb1 = SQL_NTS;
				char con[50];
				SQLBindParameter(sql_get_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, con, 0, &cb1);
				sprintf_s(con, "%s", condition);

				if (rad_search_id == 1) {
					SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from searchID(?)", SQL_NTS);
				}
				else if (rad_search_name == 1) {
					SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from searchName(?)", SQL_NTS);
				}

				lcl_list_student.SetRedraw(FALSE);
				lcl_list_student.DeleteAllItems();
				lcl_list_student.SetRedraw(TRUE);

				char id[10], username[50], email[50], sname[50], falculty[50], company[50];
				int stt = 0;
				while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
				{
					SQLGetData(sql_get_handle, 1, SQL_C_CHAR, id, 10, NULL);
					SQLGetData(sql_get_handle, 2, SQL_C_CHAR, username, 50, NULL);
					SQLGetData(sql_get_handle, 3, SQL_C_CHAR, sname, 50, NULL);
					SQLGetData(sql_get_handle, 4, SQL_C_CHAR, email, 50, NULL);
					SQLGetData(sql_get_handle, 5, SQL_C_CHAR, falculty, 50, NULL);
					SQLGetData(sql_get_handle, 6, SQL_C_CHAR, company, 50, NULL);
					lcl_list_student.InsertItem(stt, std::to_string(stt+1).c_str());
					lcl_list_student.SetItemText(stt, 1, id);
					lcl_list_student.SetItemText(stt, 2, sname);
					lcl_list_student.SetItemText(stt, 3, email);
					lcl_list_student.SetItemText(stt, 4, falculty);
					lcl_list_student.SetItemText(stt++, 5, company);
				}
			}
		} while (FALSE);
		SQLFreeStmt(sql_get_handle, SQL_CLOSE);
		SQLFreeStmt(sql_get_handle, SQL_UNBIND);
		SQLFreeStmt(sql_get_handle, SQL_RESET_PARAMS);
		UpdateData(FALSE);
		UpdateStudentCount();
	}
	else {
		UpdateStudentList();
	}
	//UpdateData(TRUE);
	//do
	//{
	//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
	//		return;
	//	}
	//	if (SQL_SUCCESS != SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from Student", SQL_NTS))
	//	{
	//		/*MessageBox(_T("get data error"));
	//		return;*/
	//	}
	//	else
	//	{
	//		lcl_list_student.SetRedraw(FALSE);
	//		lcl_list_student.DeleteAllItems();
	//		lcl_list_student.SetRedraw(TRUE);
	//		char id[30], username[50], email[50], sname[50], falculty[50], company[50];
	//		while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
	//		{
	//			SQLGetData(sql_get_handle, 1, SQL_C_CHAR, id, 30, NULL);
	//			SQLGetData(sql_get_handle, 2, SQL_C_CHAR, username, 50, NULL);
	//			SQLGetData(sql_get_handle, 3, SQL_C_CHAR, sname, 50, NULL);
	//			SQLGetData(sql_get_handle, 4, SQL_C_CHAR, email, 50, NULL);
	//			SQLGetData(sql_get_handle, 5, SQL_C_CHAR, falculty, 50, NULL);
	//			SQLGetData(sql_get_handle, 6, SQL_C_CHAR, company, 50, NULL);
	//			lcl_list_student.InsertItem(0, id);
	//			lcl_list_student.SetItemText(0, 1, sname);
	//			lcl_list_student.SetItemText(0, 2, email);
	//			lcl_list_student.SetItemText(0, 3, falculty);
	//			lcl_list_student.SetItemText(0, 4, company);
	//		}
	//		/*MessageBox(_T("Successfully!"));*/
	//		
	//	}
	//} while (FALSE);
	//UpdateStudentCount();
	//UpdateData(FALSE);
}

void StudentManagement::OnBnClickedBtnDelete()
{
	UpdateData(TRUE);

	int num_student = lcl_list_student.GetItemCount(); 
	int int_select_pos = -1;
	for (int i = 0; i < num_student; i++) {
		if (lcl_list_student.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			int_select_pos = i;
			break;
		}
	}
	if (int_select_pos != -1) {
		if (MessageBox(_T("Are you sure?"), _T("Delete confirm"), MB_OKCANCEL) == IDOK) {
			CString selected_id = lcl_list_student.GetItemText(int_select_pos, 0); //get id select
			SQLINTEGER cb1 = SQL_NTS;
			char id[10];

			SQLBindParameter(sql_delete_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 10, 0, id, 0, &cb1);

			sprintf_s(id, "%s", selected_id);

			SQLExecDirect(sql_delete_handle, (SQLCHAR*)"delete from student where id =?", SQL_NTS);

			lcl_list_student.DeleteItem(int_select_pos);
			UpdateStudentCount();
			SQLFreeStmt(sql_delete_handle, SQL_CLOSE);
			SQLFreeStmt(sql_delete_handle, SQL_UNBIND);
			SQLFreeStmt(sql_delete_handle, SQL_RESET_PARAMS);
		};
		
	}

	UpdateData(FALSE);
}

void StudentManagement::OnBnClickedBtnEditStddlg()
{
	int num_student = lcl_list_student.GetItemCount();
	int int_select_pos = -1;
	for (int i = 0; i < num_student; i++) {
		if (lcl_list_student.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			int_select_pos = i;
			break;
		}
	}

	if (int_select_pos != -1) {
		CString str_select_pos = std::to_string(int_select_pos).c_str();
		CString str_select_id = lcl_list_student.GetItemText(int_select_pos, 0);
		CString str_select_name = lcl_list_student.GetItemText(int_select_pos, 1);
		CString str_select_email = lcl_list_student.GetItemText(int_select_pos, 2);
		CString str_select_falculty = lcl_list_student.GetItemText(int_select_pos, 3);
		CString str_select_company = lcl_list_student.GetItemText(int_select_pos, 4);
		EditStudent es;
		es.SetID(str_select_id);
		es.SetInfo(str_select_falculty, str_select_name, str_select_email, str_select_company);
		es.DoModal();
		UpdateStudentList();
	}
}

void StudentManagement::CheckInputValues() {
	
}

void StudentManagement::OnStnClickedTxtCountStudent()
{
	// TODO: Add your control notification handler code here
}

void StudentManagement::OnBnClickedBtnEditScore()
{
	int num_student = lcl_list_student.GetItemCount();
	int int_select_pos = -1;
	for (int i = 0; i < num_student; i++) {
		if (lcl_list_student.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			int_select_pos = i;
			break;
		}
	}
	if (int_select_pos != -1) {
		CString sid = lcl_list_student.GetItemText(int_select_pos, 0);
		CString sname = lcl_list_student.GetItemText(int_select_pos, 1);
		CString scompany = lcl_list_student.GetItemText(int_select_pos, 4);
		
		EditScore es;
		es.GetHandle(sql_connection_handle);
		es.GetInfo(sid, sname, scompany);
		es.DoModal();
	}

	
}
