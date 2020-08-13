
// MFCMyAppDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCMyApp.h"
#include "MFCMyAppDlg.h"
#include "afxdialogex.h"
#include "Calculator.h"
#include "StudentManagement.h"
#include "EditStudent.h"
#include "CompanyManagement.h"
#include "ScoreTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnStudent();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_STUDENT, &CAboutDlg::OnBnClickedBtnStudent)
END_MESSAGE_MAP()


// CMFCMyAppDlg dialog



CMFCMyAppDlg::CMFCMyAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMYAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMyAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDT_USER, edt_username_);
}

BEGIN_MESSAGE_MAP(CMFCMyAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCMyAppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_STUDENT, &CMFCMyAppDlg::OnBnClickedBtnStudent)
	ON_BN_CLICKED(ID_BTN_OPEN_DIALOG, &CMFCMyAppDlg::OnBnClickedBtnOpenDialog)

	ON_BN_CLICKED(IDC_OPEN_SCORE_TABLE, &CMFCMyAppDlg::OnBnClickedOpenScoreTable)
END_MESSAGE_MAP()


// CMFCMyAppDlg message handlers

BOOL CMFCMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCMyAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCMyAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMyAppDlg::OnBnClickedButton1()
{
	CString username;
	//edt_username_.GetWindowText(username);
	Calculator cal;
	//cal.SetUsername(username);
	cal.DoModal();
	
}


void CAboutDlg::OnBnClickedBtnStudent()
{
	MessageBox(_T("STD"));
}


void CMFCMyAppDlg::OnBnClickedBtnStudent()
{
	StudentManagement sm;
	sm.DoModal();
}


void CMFCMyAppDlg::OnBnClickedBtnOpenDialog()
{
	CompanyManagement cm;
	cm.DoModal();
}


void CMFCMyAppDlg::OnBnClickedOpenScoreTable()
{
	ScoreTable st;
	st.DoModal();
}
