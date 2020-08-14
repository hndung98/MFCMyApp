// ScoreTable.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "ScoreTable.h"
#include "afxdialogex.h"


// ScoreTable dialog

IMPLEMENT_DYNAMIC(ScoreTable, CDialogEx)

ScoreTable::ScoreTable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SCORE_TABLE, pParent)
	, rad_id_search(0)
	, rad_name_search(1)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_SCORE);
}

ScoreTable::~ScoreTable()
{
	if (sql_edit_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_edit_handle);
		sql_edit_handle = NULL;
	}
	if (sql_get_handle != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, sql_get_handle);
		sql_get_handle = NULL;
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

void ScoreTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edt_search_scoretable_dlg);
	DDX_Control(pDX, IDC_LCL_SCORE_TABLE, lcl_score_table);
	DDX_Check(pDX, IDC_RAD_SEARCH_ID_SCOREDLG, rad_id_search);
	DDX_Check(pDX, IDC_RAD_SEARCH_NAME_SCOREDLG, rad_name_search);

	if (start == true) {
		start = false;
		StartDialog();
	}
}


BEGIN_MESSAGE_MAP(ScoreTable, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SEARCH_SCOREDLG, &ScoreTable::OnBnClickedBtnSearchScoredlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LCL_SCORE_TABLE, &ScoreTable::OnLvnItemchangedLclScoreTable)
	ON_BN_CLICKED(IDC_EDIT_SCORE_DLG, &ScoreTable::OnBnClickedEditScoreDlg)
END_MESSAGE_MAP()

BOOL ScoreTable::OnInitDialog() {
	CDialogEx::OnInitDialog();
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SCORE));
	SetIcon(hIcon, FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void ScoreTable::StartDialog()
{
	lcl_score_table.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVCFMT_FIXED_RATIO);
	lcl_score_table.InsertColumn(0, _T("ON"), LVCFMT_LEFT, 50);
	lcl_score_table.InsertColumn(1, _T("ID"), LVCFMT_LEFT, 80);
	lcl_score_table.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 150);
	lcl_score_table.InsertColumn(3, _T("Company"), LVCFMT_LEFT, 150);
	lcl_score_table.InsertColumn(4, _T("week 1"), LVCFMT_LEFT, 60);
	lcl_score_table.InsertColumn(5, _T("week 2"), LVCFMT_LEFT, 60);
	lcl_score_table.InsertColumn(6, _T("week 3"), LVCFMT_LEFT, 60);
	lcl_score_table.InsertColumn(7, _T("week 4"), LVCFMT_LEFT, 60);

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
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_edit_handle)) {
		connected = false;
		return;
	}

}

void ScoreTable::UpdateStudentList()
{
	UpdateData(TRUE);
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
		MessageBox(_T("get handle failed"));
	}
	if (SQL_SUCCESS != SQLExecDirect(sql_get_handle, (SQLCHAR*)"select id, s_name, company, week1, week2, week3, week4 from student", SQL_NTS))
	{
		MessageBox(_T("execdirect get failed"));
	}
	else
	{
		lcl_score_table.SetRedraw(FALSE);
		lcl_score_table.DeleteAllItems();
		lcl_score_table.SetRedraw(TRUE);

		char id[10], name[50], company[50];
		int w1, w2, w3, w4;
		int stt = 0;
		while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
		{
			SQLGetData(sql_get_handle, 1, SQL_C_CHAR, id, 10, NULL);
			SQLGetData(sql_get_handle, 2, SQL_C_CHAR, name, 50, NULL);
			SQLGetData(sql_get_handle, 3, SQL_C_CHAR, company, 50, NULL);
			SQLGetData(sql_get_handle, 4, SQL_C_DEFAULT, &w1, 0, NULL);
			SQLGetData(sql_get_handle, 5, SQL_C_DEFAULT, &w2, 0, NULL);
			SQLGetData(sql_get_handle, 6, SQL_C_DEFAULT, &w3, 0, NULL);
			SQLGetData(sql_get_handle, 7, SQL_C_DEFAULT, &w4, 0, NULL);
			lcl_score_table.InsertItem(stt, std::to_string(stt + 1).c_str());
			lcl_score_table.SetItemText(stt, 1, id);
			lcl_score_table.SetItemText(stt, 2, name);
			lcl_score_table.SetItemText(stt, 3, company);
			lcl_score_table.SetItemText(stt, 4, std::to_string(w1).c_str());
			lcl_score_table.SetItemText(stt, 5, std::to_string(w2).c_str());
			lcl_score_table.SetItemText(stt, 6, std::to_string(w3).c_str());
			lcl_score_table.SetItemText(stt++, 7, std::to_string(w4).c_str());
		}

	}
	SQLFreeStmt(sql_get_handle, SQL_CLOSE);
	SQLFreeStmt(sql_get_handle, SQL_UNBIND);
	SQLFreeStmt(sql_get_handle, SQL_RESET_PARAMS);
	UpdateData(FALSE);
}
// ScoreTable message handlers


void ScoreTable::OnBnClickedBtnSearchScoredlg()
{
	CString condition;
	edt_search_scoretable_dlg.GetWindowText(condition);
	if (condition.GetLength() == 0) {
		UpdateStudentList();
	}
	else {
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

				if (rad_id_search == 1) {
					SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from searchScoreID(?)", SQL_NTS);
				}
				else if (rad_name_search == 1) {
					SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from searchScore(?)", SQL_NTS);
				}

				lcl_score_table.SetRedraw(FALSE);
				lcl_score_table.DeleteAllItems();
				lcl_score_table.SetRedraw(TRUE);

				char id[10], name[50], company[50];
				int w1, w2, w3, w4;
				int stt = 0;
				while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
				{
					SQLGetData(sql_get_handle, 1, SQL_C_CHAR, id, 10, NULL);
					SQLGetData(sql_get_handle, 2, SQL_C_CHAR, name, 50, NULL);
					SQLGetData(sql_get_handle, 3, SQL_C_CHAR, company, 50, NULL);
					SQLGetData(sql_get_handle, 4, SQL_C_DEFAULT, &w1, 0, NULL);
					SQLGetData(sql_get_handle, 5, SQL_C_DEFAULT, &w2, 0, NULL);
					SQLGetData(sql_get_handle, 6, SQL_C_DEFAULT, &w3, 0, NULL);
					SQLGetData(sql_get_handle, 7, SQL_C_DEFAULT, &w4, 0, NULL);
					lcl_score_table.InsertItem(stt, std::to_string(stt + 1).c_str());
					lcl_score_table.SetItemText(stt, 1, id);
					lcl_score_table.SetItemText(stt, 2, name);
					lcl_score_table.SetItemText(stt, 3, company);
					lcl_score_table.SetItemText(stt, 4, std::to_string(w1).c_str());
					lcl_score_table.SetItemText(stt, 5, std::to_string(w2).c_str());
					lcl_score_table.SetItemText(stt, 6, std::to_string(w3).c_str());
					lcl_score_table.SetItemText(stt++, 7, std::to_string(w4).c_str());
				}
			}
		} while (FALSE);
		SQLFreeStmt(sql_get_handle, SQL_CLOSE);
		SQLFreeStmt(sql_get_handle, SQL_UNBIND);
		SQLFreeStmt(sql_get_handle, SQL_RESET_PARAMS);
		UpdateData(FALSE);
	}
}


void ScoreTable::OnLvnItemchangedLclScoreTable(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	//MessageBox(_T("hoho"));
}


void ScoreTable::OnBnClickedEditScoreDlg()
{
	int num_student = lcl_score_table.GetItemCount();
	int int_select_row = -1;
	for (int i = 0; i < num_student; i++) {
		if (lcl_score_table.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) {
			int_select_row = i;
			break;
		}
	}

	if (int_select_row != -1) {
		CString str_select_row = std::to_string(int_select_row).c_str();
		CString str_select_id = lcl_score_table.GetItemText(int_select_row, 1);
		CString str_select_name = lcl_score_table.GetItemText(int_select_row, 2);
		CString str_select_company = lcl_score_table.GetItemText(int_select_row, 3);

		EditScore es;
		es.GetHandle(sql_connection_handle);
		es.GetInfo(str_select_id, str_select_name, str_select_company);
		es.DoModal();
	}
}
