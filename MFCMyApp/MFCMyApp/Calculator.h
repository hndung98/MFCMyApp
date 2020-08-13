#pragma once


// Calculator dialog

class Calculator : public CDialogEx
{
	DECLARE_DYNAMIC(Calculator)

public:
	Calculator(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Calculator();

	
	void SetUsername(CString name);
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CALCULATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CString username;
	DECLARE_MESSAGE_MAP()
	CEdit edt_val_1;
	CEdit edt_val_2;
	CEdit edt_result;
	CStatic txt_username;
	int rad_sum;
	int rad_sub;
	int rad_mul;
	int rad_div;
public:
	afx_msg void OnBnClickedBtnCalculate();
};
