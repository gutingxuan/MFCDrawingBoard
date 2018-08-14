// NewPaperDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw2.h"
#include "NewPaperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewPaperDlg dialog

CNewPaperDlg::CNewPaperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewPaperDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewPaperDlg)
	m_Length = 0;
	m_Width = 0;
	//}}AFX_DATA_INIT
}


void CNewPaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewPaperDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Length);
	DDX_Text(pDX, IDC_EDIT2, m_Width);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewPaperDlg, CDialog)
	//{{AFX_MSG_MAP(CNewPaperDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewPaperDlg message handlers



