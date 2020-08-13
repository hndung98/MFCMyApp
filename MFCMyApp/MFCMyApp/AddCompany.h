#pragma once
#pragma comment(lib, "odbc32.lib")
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string>

// AddCompany dialog

class AddCompany : public CDialogEx
{
	DECLARE_DYNAMIC(AddCompany)

public:
	AddCompany(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddCompany();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_COMPANY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void StartDialog();
	void SetHandle(SQLHANDLE handle);
protected:
	CEdit edt_name_com_add;
	CEdit edt_intro_com_add;
	CEdit edt_addr_com_add;
	CEdit edt_email_com_add;
	bool start = true;
	SQLHANDLE sql_connection_handle;
	SQLHANDLE sql_add_handle;
	bool connected = true;
};
