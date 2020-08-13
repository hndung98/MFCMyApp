#pragma once
#pragma comment(lib, "odbc32.lib")
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string>
#include "AddCompany.h"
#include "EditCompany.h"
// CompanyManagement dialog

class CompanyManagement : public CDialogEx
{
	DECLARE_DYNAMIC(CompanyManagement)

public:
	CompanyManagement(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CompanyManagement();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COMPANY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
protected:
	CListCtrl lcl_company;
	bool start = true;
	SQLHANDLE sql_env_handle;
	SQLHANDLE sql_connection_handle;
	SQLHANDLE sql_get_handle;
	SQLHANDLE sql_add_handle;
	SQLHANDLE sql_edit_handle;
	SQLHANDLE sql_delete_handle;
	SQLRETURN retcode = 0;
	bool connected = true;
public:
	afx_msg void OnBnClickedBtnAddComdlg();
	afx_msg void OnBnClickedBtnEditComdlg();
	void StartDialog();
	void UpdateCompanyList();
	afx_msg void OnBnClickedDeleteComdlg();
	afx_msg void OnBnClickedBtnLoadComdlg();
};
