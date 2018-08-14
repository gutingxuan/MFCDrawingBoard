// Draw2View.h : interface of the CDraw2View class
//
/////////////////////////////////////////////////////////////////////////////


class CDraw2Doc;


#if !defined(AFX_DRAW2VIEW_H__63E3DA34_9188_45F5_AA4E_6106C40236E5__INCLUDED_)
#define AFX_DRAW2VIEW_H__63E3DA34_9188_45F5_AA4E_6106C40236E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum DRAW_TYPE{TYPE_NONE, TYPE_LINE = 1, TYPE_RECT, TYPE_ROUNDRECT, 
TYPE_ELLIPSE, TYPE_POLYGON, TYPE_CIRCLE, TYPE_TEXT, TYPE_FREELINE, TYPE_POLYLINE};


class CDraw2View : public CScrollView
{
protected: // create from serialization only
	CDraw2View();
	DECLARE_DYNCREATE(CDraw2View)

// Attributes
public:
	CDraw2Doc* GetDocument();

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDraw2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
	public:

	UINT m_Width;	    //新建画布宽度
	UINT m_Length;	    //新建画布长度

	bool m_isOnWriter;	//判断是否用了笔刷
	bool m_isOnDraw;	//判断是否在绘画模式
	int m_nWriterType;	//笔刷类型
	bool m_bLBtnDown;	//判断左键是否按下
	CPoint m_ptEnd;		//终点
	int m_click1;		//点按钮
	int m_click2;		//直线按钮
	int m_click3;		//椭圆按钮
	int m_click4;		//矩形按钮
	int m_click5;	    //实心矩形按钮
	int m_click6;		//实心椭圆按钮
	int m_click7;		//圆形按钮
	int m_click8;		//实心圆形按钮
	int m_click9;		//文字输入按钮

	virtual ~CDraw2View();
	int m_nLineStyle;	//直线类型
	UINT m_nLineWidth;	//直线宽度
	COLORREF m_color;	//选中颜色
	UINT m_nDrawType;	//绘画类型
	CPoint m_ptOrigin;	//起点
	int m_writerclick1;	//笔刷按钮
	int m_writerclick2; //钢笔按钮
	int m_writerclick3;	//喷雾器按钮
	int m_writerclick4;	//油漆桶按钮
	int m_writerclick5;	//橡皮擦按钮
	int m_isOnOpen;		//判断是否打开了图片

	void OnInitialUpdate();


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:

	//{{AFX_MSG(CDraw2View)
	afx_msg void OnEllipse();
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUpdateDot(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnLinesetting();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDot();
	afx_msg void OnPaint1();
	afx_msg void OnPen();
	afx_msg void OnSprayer();
	afx_msg void OnEraser();
	afx_msg void OnUpdateSprayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePen(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEraser(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrush(CCmdUI* pCmdUI);
	afx_msg void OnBrush();
	afx_msg void OnNewscreen();
	afx_msg void OnSave();
	afx_msg void OnNew();
	afx_msg void OnOpen();
	afx_msg void OnSolidrectangle();
	afx_msg void OnUpdateSolidrectangle(CCmdUI* pCmdUI);
	afx_msg void OnCircle();
	afx_msg void OnSolidellipse();
	afx_msg void OnSolidcircle();
	afx_msg void OnUpdateSolidellipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSolidcircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnSaveimage();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnGauss();
	afx_msg void OnColorgrey();
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnCancelMode();
	afx_msg void OnRotLeft();
	afx_msg void OnRotRight();
	afx_msg void OnFlipHor();
	afx_msg void OnFlipVer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

#ifndef _DEBUG  // debug version in Draw2View.cpp
inline CDraw2Doc* CDraw2View::GetDocument()
   { return (CDraw2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAW2VIEW_H__63E3DA34_9188_45F5_AA4E_6106C40236E5__INCLUDED_)
