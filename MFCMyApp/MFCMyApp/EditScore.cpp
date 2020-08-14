// EditScore.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "EditScore.h"
#include "afxdialogex.h"


// EditScore dialog

IMPLEMENT_DYNAMIC(EditScore, CDialogEx)

EditScore::EditScore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_EDIT_SCORE, pParent)
{

}

EditScore::~EditScore()
{
	if (sql_get_handle != SQL_NULL_HENV) {
		SQLFreeHandle(SQL_HANDLE_ENV, sql_get_handle);
		sql_get_handle = NULL;
	}
	if (sql_update_handle != SQL_NULL_HENV) {
		SQLFreeHandle(SQL_HANDLE_ENV, sql_update_handle);
		sql_update_handle = NULL;
	}
}

void EditScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_SID_EDTSCOREDLG, edt_name_edt_score_dlg);
	DDX_Control(pDX, IDC_EDT_SNAME_EDTSCOREDLG, edt_id_edt_score_dlg);
	DDX_Control(pDX, IDC_EDT_COMPANY_EDTSCOREDLG, edt_company_edt_score_dlg);
	DDX_Control(pDX, IDC_EDT_SCORE1, edt_score1);
	DDX_Control(pDX, IDC_EDT_SCORE2, edt_score2);
	DDX_Control(pDX, IDC_EDT_SCORE3, edt_score3);
	DDX_Control(pDX, IDC_EDT_SCORE4, edt_score4);

	if (start == true) {
		start = false;
		StartDialog();
	}
	DDX_Control(pDX, IDC_CHECK_DECIMAL_SCORE, chb_10_score_scale);
}


BEGIN_MESSAGE_MAP(EditScore, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CHECK_SCOREDLG, &EditScore::OnBnClickedBtnCheckScoredlg)
	ON_BN_CLICKED(IDOK, &EditScore::OnBnClickedOk)
END_MESSAGE_MAP()

void EditScore::StartDialog()
{
	edt_score1.SetLimitText(2);
	edt_score2.SetLimitText(2);
	edt_score3.SetLimitText(2);
	edt_score4.SetLimitText(2);
	edt_id_edt_score_dlg.SetLimitText(9);
	edt_name_edt_score_dlg.EnableWindow(FALSE);
	edt_company_edt_score_dlg.EnableWindow(FALSE);

	edt_id_edt_score_dlg.SetWindowText(id);
	edt_name_edt_score_dlg.SetWindowText(name);
	edt_company_edt_score_dlg.SetWindowText(company);

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_update_handle)) {
		connected = false;
		return;
	}
	/*if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
		MessageBox(_T("get handle failed"));
	}
	if (SQL_SUCCESS != SQLExecDirect(sql_get_handle, (SQLCHAR*)"select * from student", SQL_NTS))
	{
		MessageBox(_T("execdirect get failed"));
	}
	else {

	}

	SQLFreeStmt(sql_get_handle, SQL_CLOSE);
	SQLFreeStmt(sql_get_handle, SQL_UNBIND);
	SQLFreeStmt(sql_get_handle, SQL_RESET_PARAMS);*/
}
void EditScore::GetInfo(CString id_, CString name_, CString company_)
{
	id = id_;
	name = name_;
	company = company_;
}
void EditScore::GetHandle(SQLHANDLE handle)
{
	sql_connection_handle = handle;
}
// EditScore message handlers


void EditScore::OnBnClickedBtnCheckScoredlg()
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sql_connection_handle, &sql_get_handle)) {
		MessageBox(_T("get handle failed"));
	}
	else {
		UpdateData(TRUE);
		CString id_new;
		SQLINTEGER cb1 = SQL_NTS, cb2 = SQL_NTS, cb3 = SQL_NTS;
		char char_id[10], char_name[50], char_com[50];
		edt_id_edt_score_dlg.GetWindowText(id_new);
		SQLBindParameter(sql_get_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 10, 0, char_id, 0, &cb1);
		sprintf_s(char_id, "%s", id_new);

		SQL_SUCCESS != SQLExecDirect(sql_get_handle, (SQLCHAR*)"select s_name, company from student where id = ?", SQL_NTS);

		while (SQLFetch(sql_get_handle) == SQL_SUCCESS)
		{
			SQLGetData(sql_get_handle, 1, SQL_C_CHAR, char_name, 50, NULL);
			SQLGetData(sql_get_handle, 2, SQL_C_CHAR, char_com, 50, NULL);
		}
		edt_name_edt_score_dlg.SetWindowText((CString)char_name);
		edt_company_edt_score_dlg.SetWindowText((CString)char_com);
		SQLFreeStmt(sql_get_handle, SQL_CLOSE);
		SQLFreeStmt(sql_get_handle, SQL_UNBIND);
		SQLFreeStmt(sql_get_handle, SQL_RESET_PARAMS);
		UpdateData(FALSE);
	}

	
}


void EditScore::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString cs1, cs2, cs3, cs4;
	edt_score1.GetWindowText(cs1);
	edt_score2.GetWindowText(cs2);
	edt_score3.GetWindowText(cs3);
	edt_score4.GetWindowText(cs4);
	edt_id_edt_score_dlg.GetWindowText(id);
	bool allow = true;
	if (id.GetLength() == 0) {
		MessageBox(_T("please type ID"));
		allow = false;
	}
	else if (cs1.GetLength() == 0 || cs2.GetLength() == 0 || cs3.GetLength() == 0 || cs4.GetLength() == 0) {
		MessageBox(_T("please type all scores"));
		allow = false;
	}//if ((!atoi(cs1) && (cs1 != _T("0") || cs1 != _T("00"))) || (!atoi(cs2) && (cs2 != _T("0") || cs2 != _T("00"))) || (!atoi(cs3) && (cs3 != _T("0") || cs3 != _T("00"))) || (!atoi(cs4)) && (cs4 != _T("0") || cs4 != _T("00")))
	else  {
		bool a1 = true, a2 = true, a3 = true, a4 = true;
		if (!atoi(cs1) && cs1 != _T("0") && cs1 !=_T("00"))  {
			a1 = false;
		}
		if (!atoi(cs2) && cs2 != _T("0") && cs2 != _T("00")) {
			a2 = false;
		}
		if (!atoi(cs3) && cs3 != _T("0") && cs3 != _T("00")) {
			a3 = false;
		}
		if (!atoi(cs4) && cs4 != _T("0") && cs4 != _T("00")) {
			a4 = false;
		}
		if (a1 && a2 && a3 && a4) {
			allow = true;
		}
		else {
			MessageBox(_T("Not a number"));
			allow = false;
		}
	}
	if (allow == true) {
		int s1 = atoi(cs1);
		int s2 = atoi(cs2);
		int s3 = atoi(cs3);
		int s4 = atoi(cs4); 
		if (s1 < 0 || s2 < 0 || s3 < 0 || s4 < 0) {
			MessageBox(_T("Score cannot be negative number"));
			return;
		}
		else if (chb_10_score_scale.GetCheck() == 1) {
			if (s1 > 10 || s2 > 10 || s3 > 10 || s3 > 10) {
				MessageBox(_T("Score must be smaller than 10"));
				return;
			}
		}

		SQLINTEGER cb1 = SQL_NTS, cb2 = SQL_NTS, cb3 = SQL_NTS, cb4 = SQL_NTS, cb5 = SQL_NTS;
		char char_id[10];

		SQLBindParameter(sql_update_handle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 1, 0, &s1, 0, &cb1);
		SQLBindParameter(sql_update_handle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 1, 0, &s2, 0, &cb2);
		SQLBindParameter(sql_update_handle, 3, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 1, 0, &s3, 0, &cb3);
		SQLBindParameter(sql_update_handle, 4, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 1, 0, &s4, 0, &cb4);
		SQLBindParameter(sql_update_handle, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 10, 0, char_id, 0, &cb5);

		sprintf_s(char_id, "%s", id);
		SQLExecDirect(sql_update_handle, (SQLCHAR*)"update student set week1 = ?, week2 = ?, week3 = ?, week4 = ? where id = ?", SQL_NTS);

		SQLFreeStmt(sql_update_handle, SQL_CLOSE);
		SQLFreeStmt(sql_update_handle, SQL_UNBIND);
		SQLFreeStmt(sql_update_handle, SQL_RESET_PARAMS);

		edt_score1.SetWindowText(_T(""));
		edt_score2.SetWindowText(_T(""));
		edt_score3.SetWindowText(_T(""));
		edt_score4.SetWindowText(_T(""));
		MessageBox(_T("edit score successfully"));
	}
	UpdateData(FALSE);
	//CDialogEx::OnOK();
}
