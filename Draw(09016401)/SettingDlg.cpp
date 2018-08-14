// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw2.h"
#include "SettingDlg.h"
#include "NewPaperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_nLineWidth = 0;
	m_nLineStyle = -1;
	//}}AFX_DATA_INIT
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Text(pDX, IDC_LINE_WIDTH, m_nLineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_EN_CHANGE(IDC_LINE_WIDTH, OnChangeLineWidth)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers


void CSettingDlg::OnChangeLineWidth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnPaint() //线型设置界面的示例
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateData();
	CPen pen(m_nLineStyle,m_nLineWidth,RGB(0,0,0));
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);
	// Do not call CDialog::OnPaint() for painting messages
}
