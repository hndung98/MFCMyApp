// Calculator.cpp : implementation file
//

#include "pch.h"
#include "MFCMyApp.h"
#include "Calculator.h"
#include "afxdialogex.h"


// Calculator dialog

IMPLEMENT_DYNAMIC(Calculator, CDialogEx)

Calculator::Calculator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CALCULATOR, pParent)
	, rad_sum(1)
	, rad_sub(0)
	, rad_mul(0)
	, rad_div(0)
{
	
}

Calculator::~Calculator()
{
}

void Calculator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_VAL_1, edt_val_1);
	DDX_Control(pDX, IDC_EDT_VAL_2, edt_val_2);
	DDX_Control(pDX, IDC_EDT_RESULT, edt_result);
	DDX_Control(pDX, IDC_TXT_USERNAME, txt_username);
	DDX_Check(pDX, IDC_RAD_SUM, rad_sum);
	DDX_Check(pDX, IDC_RAD_SUB, rad_sub);
	DDX_Check(pDX, IDC_RAD_MUL, rad_mul);
	DDX_Check(pDX, IDC_RAD_DIV, rad_div);
	txt_username.SetWindowText(username);
}


BEGIN_MESSAGE_MAP(Calculator, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CALCULATE, &Calculator::OnBnClickedBtnCalculate)
END_MESSAGE_MAP()

void Calculator::SetUsername(CString name) {
	username = name;
}

// Calculator message handlers


void Calculator::OnBnClickedBtnCalculate()
{
	UpdateData(TRUE);

	CString sresult = _T("");
	CString sval1, sval2;
	edt_val_1.GetWindowText(sval1);
	edt_val_2.GetWindowText(sval2);

	float fval1 = _ttof(sval1);
	float fval2 = _ttof(sval2);

	float fresult = 0.0;

	if (rad_sum == 1) {
		fresult = fval1 + fval2;
	}
	if (rad_sub == 1) {
		fresult = fval1 - fval2;
	}
	if (rad_mul == 1) {
		fresult = fval1 * fval2;
	}
	if (rad_div == 1) {
		if (fval2 == 0) {
			MessageBox(_T("Eror"));
		}
		else {
			fresult = fval1 / fval2;
		}
	}

	sresult.Format(_T("%f"), fresult);

	edt_result.SetWindowText(sresult);

	UpdateData(FALSE);
}
