#pragma once
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "user32.lib")
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string>
#include "EditScore.h"

// ScoreTable dialog

class ScoreTable : public CDialogEx
{
	DECLARE_DYNAMIC(ScoreTable)

public:
	ScoreTable(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ScoreTable();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SCORE_TABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CEdit edt_search_scoretable_dlg;
	CListCtrl lcl_score_table;
	bool start = true;
	SQLHANDLE sql_env_handle;
	SQLHANDLE sql_connection_handle;
	SQLHANDLE sql_get_handle;
	SQLHANDLE sql_edit_handle;
	SQLRETURN retcode = 0;
	bool connected = true;
public :
	void StartDialog();
	void UpdateStudentList();
	afx_msg void OnBnClickedBtnSearchScoredlg();
	afx_msg void OnLvnItemchangedLclScoreTable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedEditScoreDlg();
};
