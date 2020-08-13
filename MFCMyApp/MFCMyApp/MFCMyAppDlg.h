
// MFCMyAppDlg.h : header file
//

#pragma once


// CMFCMyAppDlg dialog
class CMFCMyAppDlg : public CDialogEx
{
// Construction
public:
	CMFCMyAppDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMYAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//CEdit edt_username_;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnStudent();
	afx_msg void OnBnClickedBtnOpenDialog();
	afx_msg void OnBnClickedOpenScoreTable();
};
