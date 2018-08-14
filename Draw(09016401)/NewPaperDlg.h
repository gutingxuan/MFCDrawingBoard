#if !defined(AFX_NEWPAPERDLG_H__1BC68A52_8C9C_4814_8034_FBA06B22DDE3__INCLUDED_)
#define AFX_NEWPAPERDLG_H__1BC68A52_8C9C_4814_8034_FBA06B22DDE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewPaperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewPaperDlg dialog

class CNewPaperDlg : public CDialog
{
// Construction
public:
	CNewPaperDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewPaperDlg)
	enum { IDD = IDD_NEWPAPER };
	UINT	m_Length;
	UINT	m_Width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewPaperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewPaperDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPAPERDLG_H__1BC68A52_8C9C_4814_8034_FBA06B22DDE3__INCLUDED_)
