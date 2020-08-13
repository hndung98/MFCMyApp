#pragma once
#pragma comment(lib, "odbc32.lib")
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string>

// EditCompany dialog

class EditCompany : public CDialogEx
{
	DECLARE_DYNAMIC(EditCompany)

public:
	EditCompany(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditCompany();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_EDIT_COMPANY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void StartDialog();
	void SetHandle(SQLHANDLE handle);
	void SetInfo(CString name, CString addr, CString email, CString intro);
protected:
	CEdit edt_name_com_edit;
	CEdit edt_intro_com_edit;
	CEdit edt_addr_com_edit;
	CEdit edt_email_com_edit;
	
	bool start = true;
	bool connected = true;
	SQLHANDLE sql_connection_handle;
	SQLHANDLE sql_edit_handle;
	CString cs_cname, cs_cemail, cs_cintro, cs_caddr;
};
