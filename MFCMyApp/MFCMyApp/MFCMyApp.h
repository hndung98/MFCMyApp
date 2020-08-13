
// MFCMyApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCMyAppApp:
// See MFCMyApp.cpp for the implementation of this class
//

class CMFCMyAppApp : public CWinApp
{
public:
	CMFCMyAppApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCMyAppApp theApp;
