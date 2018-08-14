// Draw2.h : main header file for the DRAW2 application
//

#if !defined(AFX_DRAW2_H__61F3773C_651F_410B_BF13_125728AF7018__INCLUDED_)
#define AFX_DRAW2_H__61F3773C_651F_410B_BF13_125728AF7018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define ULONG_PTR ULONG
#include "gdiplus.h"
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

/////////////////////////////////////////////////////////////////////////////
// CDraw2App:
// See Draw2.cpp for the implementation of this class
//

class CDraw2App : public CWinApp
{
public:
	CDraw2App();
	ULONG_PTR m_gdiplusToken;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDraw2App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDraw2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAW2_H__61F3773C_651F_410B_BF13_125728AF7018__INCLUDED_)

