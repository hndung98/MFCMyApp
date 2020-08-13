#pragma once
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "user32.lib")
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string>

// EditScore dialog

class EditScore : public CDialogEx
{
	DECLARE_DYNAMIC(EditScore)

public:
	EditScore(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditScore();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_EDIT_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	bool start = true;
	bool connected = true;
	CString id, name, company;
	SQLHANDLE sql_connection_handle;
	SQLHANDLE sql_update_handle;
	SQLHANDLE sql_get_handle;
	SQLRETURN retcode = 0;
	CEdit edt_name_edt_score_dlg;
	CEdit edt_id_edt_score_dlg;
	CEdit edt_company_edt_score_dlg;
	CEdit edt_score1;
	CEdit edt_score2;
	CEdit edt_score3;
	CEdit edt_score4;

public:
	void StartDialog();
	void GetInfo(CString id_, CString name_, CString company_);
	void GetHandle(SQLHANDLE handle);
	afx_msg void OnBnClickedBtnCheckScoredlg();
	afx_msg void OnBnClickedOk();
protected:
	CButton chb_10_score_scale;
};
