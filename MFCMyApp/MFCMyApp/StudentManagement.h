#pragma once
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "user32.lib")
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string>
#include "EditStudent.h"
#include "EditScore.h"

// StudentManagement dialog

class StudentManagement : public CDialogEx
{
	DECLARE_DYNAMIC(StudentManagement)

public:
	StudentManagement(CWnd* pParent = nullptr);   // standard constructor
	virtual ~StudentManagement();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	
	bool start = TRUE;
	void startDialog();
	//void show_error(unsigned int handletype, SQLHANDLE& handle);
	SQLHSTMT hstmt;
	SQLHANDLE sql_env_handle;
	SQLHANDLE sql_connection_handle;
	SQLHANDLE sql_get_handle;
	SQLHANDLE sql_add_handle;
	SQLHANDLE sql_check_handle;
	SQLHANDLE sql_delete_handle;
	SQLHANDLE sql_update_handle;
	SQLRETURN retcode = 0;
	bool connected = true;
	CEdit edt_sid;
	CEdit edt_sname;
	CEdit edt_email;
	//CEdit edt_scompany;
	CComboBox cbx_sfalculty;
public:
	afx_msg void OnBnClickedBtnSmAdd();
	void UpdateStudentCount();
	void UpdateStudentList();
protected:
	CListCtrl lcl_list_student;
public:
	afx_msg void OnBnClickedBtnGetData();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	CStatic txt_count_student_stddlg;
public:
	afx_msg void OnBnClickedBtnEditStddlg();
	void CheckInputValues();
	afx_msg void OnStnClickedTxtCountStudent();
protected:
	CComboBox cbx_company_list;
	CEdit edt_search_stddlg;
public:
	afx_msg void OnBnClickedBtnEditScore();
};
