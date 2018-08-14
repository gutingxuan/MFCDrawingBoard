// HColorBar.cpp : implementation file

#include "stdafx.h"
#include "Draw2.h"
#include "HColorBar.h"
#include "Draw2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HColorBar

HColorBar::HColorBar()
{
	//初始化调色盘颜色
	int index = 0;
	for(int i = 0; i <= 256; i += 128)
	{
		for(int j = 0; j <= 256; j += 128)
		{
			for(int k = 0; k <= 256; k +=128)
			{
				m_COLOR[index ++] = RGB(256==i?255:i, 256==j?255:j, 256==k?255:k);
			}
		}
	}
	m_COLOR[index] = RGB(1,2,3);
}


HColorBar::~HColorBar()
{
}


BEGIN_MESSAGE_MAP(HColorBar, CToolBar)
	//{{AFX_MSG_MAP(HColorBar)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HColorBar message handlers



COLORREF HColorBar::GetColor()
{
	return m_currentColor;
}

void HColorBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect(&rc);
	
	//画当前选中颜色的显示框
	dc.Draw3dRect(rc.left+1, rc.top+5, 33, 33, RGB(0, 0, 0), RGB(255, 255, 255));

	//画出当前选中颜色块矩形
	CPen pen2(PS_SOLID, 1, m_currentColor);
	CBrush bru2(m_currentColor);
	dc.SelectObject(&pen2);
	dc.SelectObject(&bru2);
	dc.Rectangle(rc.left+6, rc.top+10, rc.left+29, rc.top+33);

	//初始化颜色块矩形位置
    for(int i=0;i<COLORNUMBER/2;i++)
	{
        m_rect[i*2].left=rc.left+36+i*17+1;//要比边框矩形往右移1个单位
		m_rect[i*2].top=rc.top+5+1;//要比边框矩形往下移1个单位
		m_rect[i*2].right=m_rect[i*2].left+13;
		m_rect[i*2].bottom=m_rect[i*2].top+13;
		
        m_rect[i*2+1].left=rc.left+36+i*17+1;
		m_rect[i*2+1].top=rc.top+22+1;
		m_rect[i*2+1].right=m_rect[i*2+1].left+13;
		m_rect[i*2+1].bottom=m_rect[i*2+1].top+13;
	};

	//画出颜色小矩形
    for(i =0;i<COLORNUMBER/2;i++)
	{
		//第一行
		//先画白底黑框的矩形
		dc.Draw3dRect(rc.left+36+i*17, rc.top+5, 15, 15, RGB(0, 0, 0), RGB(255, 255, 255));

		//再画出颜色块
	    CPen pen3(PS_SOLID, 1, m_COLOR[i*2]);
	    CBrush bru3(m_COLOR[i*2]);
	    dc.SelectObject(&pen3);
	    dc.SelectObject(&bru3);
	    dc.Rectangle(m_rect[i*2].left, m_rect[i*2].top, m_rect[i*2].right, m_rect[i*2].bottom);

		//第二行
		dc.Draw3dRect(rc.left+36+i*17, rc.top+22, 15, 15, RGB(0, 0, 0), RGB(255, 255, 255));
	    CPen pen4(PS_SOLID, 1, m_COLOR[i*2+1]);
	    CBrush bru4(m_COLOR[i*2+1]);
	    dc.SelectObject(&pen4);
	    dc.SelectObject(&bru4);
	    dc.Rectangle(m_rect[i*2+1].left, m_rect[i*2+1].top, m_rect[i*2+1].right, m_rect[i*2+1].bottom);
	};

	//计算颜色总矩形大小
	m_rectAll.left=m_rect[0].left;
	m_rectAll.top=m_rect[0].top;
	m_rectAll.right=m_rect[COLORNUMBER-1].right;
	m_rectAll.bottom=m_rect[1].bottom;
}

void HColorBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	for(int i=0;i<COLORNUMBER;i++)
	{
		if(m_rect[i].PtInRect(point))
		{
			m_currentColor = m_COLOR[i];
			UpdateDocument();
         	CPen pen(PS_SOLID, 1, m_currentColor);
         	CBrush bru(m_currentColor);
          	dc.SelectObject(&pen);
         	dc.SelectObject(&bru);
          	dc.Rectangle(rc.left+6, rc.top+10, rc.left+29, rc.top+33);
			break;
		}
	}
	CToolBar::OnLButtonDown(nFlags, point);
}


void HColorBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//双击弹出颜色选择对话框
	CClientDC dc(this);
	CRect rc;
	GetClientRect(&rc);
    if(m_rectAll.PtInRect(point))//判断点是否在总矩形内
	{
        CColorDialog dlg;

		//使得颜色对话框中选中当前颜色
		dlg.m_cc.Flags |= CC_RGBINIT;
		dlg.m_cc.rgbResult=m_currentColor;

		if(dlg.DoModal()==IDOK)
		{
			m_currentColor=dlg.GetColor();
			UpdateDocument();
         	CPen pen(PS_SOLID, 1, m_currentColor);
			CBrush bru(m_currentColor);
          	dc.SelectObject(&pen);
         	dc.SelectObject(&bru);
          	dc.Rectangle(rc.left+6, rc.top+10, rc.left+29, rc.top+33);
		}
	}
}

void HColorBar::UpdateDocument()
{
	//更新view中的画笔颜色

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CDraw2View *pView = (CDraw2View*)pChild->GetActiveView();
	pView->m_color=m_currentColor;
}
