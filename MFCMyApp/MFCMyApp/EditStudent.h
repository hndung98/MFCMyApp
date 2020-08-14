#pragma once
#pragma comment(lib, "odbc32.lib")
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <string>

// EditStudent dialog

class EditStudent : public CDialogEx
{
	DECLARE_DYNAMIC(EditStudent)

public:
	EditStudent(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditStudent();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_EDIT_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void StartDialog();
	void SetID(CString ID);
	void GetConnectDB();
	void SetInfo(CString falculty, CString name, CString email, CString company);
	void SetHandle(SQLHANDLE handle);

protected:
	CComboBox cbx_falculty_editdlg;
	CEdit edt_name_editdlg;
	CEdit edt_email;
	//CEdit edit_company_editdlg;
	bool start = true;
	CString student_id = _T("-1");
	CStatic txt_student_id_edtdlg;

	SQLHANDLE sql_env_handle;
	SQLHANDLE sql_connection_handle;
	SQLHANDLE sql_update_handle;
	SQLHANDLE sql_get_handle;
	SQLRETURN retcode = 0;
	bool connected = true;

	CString student_email;
	CString student_name;
	CString student_company;
	CString student_falculty;
	CComboBox cbx_company;
};
