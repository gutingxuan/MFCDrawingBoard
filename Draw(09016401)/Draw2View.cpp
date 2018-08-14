// Draw2View.cpp : implementation of the CDraw2View class
//

#include "stdafx.h"
#include "Draw2.h"

#include "Draw2Doc.h"
#include "Draw2View.h"
#include "NewPaperDlg.h"
#include "SettingDlg.h"

#include "math.h"

#include "MainFrm.h"


#include <afxdtctl.h>  
#define ULONG_PTR ULONG  
#include <gdiplus.h>  
using namespace Gdiplus;  
#pragma comment(lib, "gdiplus.lib")  


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define DEFAULT_BITMAP_FILE_EXTENSION						_T("bmp")
#define DEFAULT_BITMAP_FILE_NAME							_T("My Drawing")
#define ID_EDIT_TEXTBOX WM_USER+1


void FlipHorizontal(HDIB hDIB)
{

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//指向图像起始位置的指针
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//指向像素起始位置的指针

    int numColors=(int)DIBNumColors((char *)lpDIB);//获取图像的颜色信息

    //如果图像不是256色返回
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//解除锁定
		return;
	 }

	int w, h, dw;
	w = (int)DIBWidth((char *)lpDIB);//获取图像的宽度
	h = (int)DIBHeight((char *)lpDIB);//获取图像的高度
	dw = (w+3)/4*4;//计算图像每行的字节数 DataSizePerLine= (biWidth*1+3)/4*4   

	for(int i=0;i<w/2;i++)//列
	{
		for(int j=0;j<h;j++)//行
		{
			BYTE temp;
			temp=*(oldPos+j*dw+i);
			*(oldPos+j*dw+i)=*(oldPos+j*dw+w-i);
			*(oldPos+j*dw+w-i)=temp;
		}
	}
	//解除锁定
	GlobalUnlock((HGLOBAL)hDIB);
}

void FlipVertical(HDIB hDIB)
{

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//指向图像起始位置的指针
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//指向像素起始位置的指针

    int numColors=(int)DIBNumColors((char *)lpDIB);//获取图像的颜色信息

    //如果图像不是256色返回
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//解除锁定
		return;
	 }

	int w, h, dw;
	w = (int)DIBWidth((char *)lpDIB);//获取图像的宽度
	h = (int)DIBHeight((char *)lpDIB);//获取图像的高度
	dw = (w+3)/4*4;//计算图像每行的字节数 DataSizePerLine= (biWidth*1+3)/4*4   

	for(int i=0;i<h/2;i++)//行
	{
		for(int j=0;j<w;j++)//列
		{
			BYTE temp;
			temp=*(oldPos+i*dw+j);
			*(oldPos+i*dw+j)=*(oldPos+(h-i)*dw+j);
			*(oldPos+(h-i)*dw+j)=temp;
		}
	}
	//解除锁定
	GlobalUnlock((HGLOBAL)hDIB);
}

HDIB RotateAntiClock90(HDIB hDIB)
{
	//先转置再左右翻转

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//指向图像起始位置的指针
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//指向像素起始位置的指针

    int numColors=(int)DIBNumColors((char *)lpDIB);//获取图像的颜色信息

    //如果图像不是256色返回
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//解除锁定
		return(hDIB);
	 }

	int w, h, dw,dh;
	w = (int)DIBWidth((char *)lpDIB);//获取图像的宽度
	h = (int)DIBHeight((char *)lpDIB);//获取图像的高度
	dw = (w+3)/4*4;//计算图像每行的字节数 DataSizePerLine= (biWidth*1+3)/4*4   
	dh = (h+3)/4*4;//计算图像每列的字节数 DataSizePerLine= (biWidth*1+3)/4*4   

	HDIB newhDIB=NewDIB(h,w,8);  //建立一个和原图像长宽相反的25色灰度位图
	BYTE* newlpDIB=(BYTE*)GlobalLock((HGLOBAL) newhDIB);//指向新的位图的指针
    BYTE* newPos = (BYTE*)FindDIBBits((char *)newlpDIB);//指向新的位图的象素起始位置的指针 


	//对图像进行转置
    for(int i=0;i<w;i++)
    {  
	   for(int j=0;j<h;j++)
	   {   
		   *(newPos+i*dh+j)=*(oldPos+j*dw+i);
	   }
	} 

	//对图像进行左右翻转
	for(int m=0;m<h/2;m++)//列
	{
		for(int n=0;n<w;n++)//行
		{
			BYTE temp;
			temp=*(newPos+n*dh+m);
			*(newPos+n*dh+m)=*(newPos+n*dh+h-m);
			*(newPos+n*dh+h-m)=temp;
		}
	}

	//解除锁定
	GlobalUnlock((HGLOBAL)hDIB);
	return(newhDIB);
}

HDIB RotateClock90(HDIB hDIB)
{
	//先转置再上下翻转

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//指向图像起始位置的指针
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//指向像素起始位置的指针

    int numColors=(int)DIBNumColors((char *)lpDIB);//获取图像的颜色信息

    //如果图像不是256色返回
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//解除锁定
		return(hDIB);
	 }

	int w, h, dw,dh;
	w = (int)DIBWidth((char *)lpDIB);//获取图像的宽度
	h = (int)DIBHeight((char *)lpDIB);//获取图像的高度
	dw = (w+3)/4*4;//计算图像每行的字节数 DataSizePerLine= (biWidth*1+3)/4*4   
	dh = (h+3)/4*4;//计算图像每列的字节数 DataSizePerLine= (biWidth*1+3)/4*4   

	HDIB newhDIB=NewDIB(h,w,8);  //建立一个和原图像长宽相反的25色灰度位图
	BYTE* newlpDIB=(BYTE*)GlobalLock((HGLOBAL) newhDIB);//指向新的位图的指针
    BYTE* newPos = (BYTE*)FindDIBBits((char *)newlpDIB);//指向新的位图的象素起始位置的指针 


	//对图像进行转置
    for(int i=0;i<w;i++)
    {  
	   for(int j=0;j<h;j++)
	   {   
		   *(newPos+i*dh+j)=*(oldPos+j*dw+i);
	   }
	} 

	//对图像进行上下翻转
	for(int m=0;m<w/2;m++)//行
	{
		for(int n=0;n<h;n++)//列
		{
			BYTE temp;
			temp=*(newPos+m*dh+n);
			*(newPos+m*dh+n)=*(newPos+(w-m)*dh+n);
			*(newPos+(w-m)*dh+n)=temp;
		}
	}

	//解除锁定
	GlobalUnlock((HGLOBAL)hDIB);
	return(newhDIB);
}


void Convert256toGray(HDIB hDIB)
{
	LPSTR	lpDIB;
	lpDIB = (LPSTR) GlobalLock((HGLOBAL)hDIB);// 由DIB句柄得到DIB指针并锁定DIB

	LPSTR lpDIBBits;// 指向DIB像素数据区的指针	
	LONG lWidth;// 图像宽度	
	LONG lHeight;// 图像高度	
	LONG lLineBytes;	// 图像每行的字节数
	
	LPBITMAPINFO lpbmi;	// 指向BITMAPINFO结构的指针
	lpbmi = (LPBITMAPINFO)lpDIB;// 获取指向BITMAPINFO结构的指针

	BYTE bMap[256];// 灰度映射表
	
	// 计算灰度映射表（保存各个颜色的灰度值），并更新DIB调色板
	int	i,j;
	for (i = 0; i < 256; i ++)
	{
		// 计算该颜色对应的灰度值  Gray = (R*299 + G*587 + B*114 + 500) / 1000
		bMap[i] = (BYTE)(0.299 * lpbmi->bmiColors[i].rgbRed +
					     0.587 * lpbmi->bmiColors[i].rgbGreen +
				         0.114 * lpbmi->bmiColors[i].rgbBlue + 0.5);			
		
		lpbmi->bmiColors[i].rgbRed = i;	// 更新DIB调色板红色分量
		lpbmi->bmiColors[i].rgbGreen = i; // 更新DIB调色板绿色分量
		lpbmi->bmiColors[i].rgbBlue = i; // 更新DIB调色板蓝色分量
	}
	
	lpDIBBits = FindDIBBits(lpDIB); // 找到DIB图像像素起始位置
	lWidth = DIBWidth(lpDIB);	// 获取图像宽度
	lHeight = DIBHeight(lpDIB); // 获取图像高度	
	lLineBytes = WIDTHBYTES(lWidth * 8); // 计算图像每行的字节数

	// 更换每个像素的颜色索引（即按照灰度映射表换成灰度值）
	for(i = 0; i < lHeight; i++)//行
	{
		for(j = 0; j < lWidth; j++)//列
		{
			// 指向DIB第i行，第j个像素进行变换
			*(lpDIBBits + i*lLineBytes + j)=bMap[*(unsigned char*)(lpDIBBits + i*lLineBytes + j)];
		}
	}

	//解除锁定
	GlobalUnlock ((HGLOBAL)hDIB);
}


/*
	图像处理的模板，可实现高斯平滑
	高斯滤波就是对整幅图像进行加权平均的过程，每一个像素点的值，都由其本身和邻域内的其他像素值经过加权平均后得到。
	高斯滤波的具体操作是：用一个模板（或称卷积、掩模）扫描图像中的每一个像素，用模板确定的邻域内像素的加权平均灰度值去替代模板中心像素点的值。

	HDIB hDIB         －图像的句柄
    double* tem       －指向模板的指针
    int tem_w         －模板的宽度
	int tem_h         －模板的高度
    double xishu      －模板的系数
*/

 HDIB Template(HDIB hDIB,double* tem ,int tem_w,int tem_h,double xishu)
{
	 
	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL) hDIB);//指向图像起始位置的指针
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//指向像素起始位置的指针

    int numColors=(int)DIBNumColors((char *)lpDIB);//获取图像的颜色信息

    //如果图像不是256色返回
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//解除锁定
		return(hDIB);
	 }

	int w, h, dw;
	w = (int)DIBWidth((char *)lpDIB);//获取图像的宽度
	h = (int)DIBHeight((char *)lpDIB);//获取图像的高度
	dw = (w+3)/4*4;//计算图像每行的字节数 DataSizePerLine= (biWidth*1+3)/4*4   

    HDIB newhDIB=NewDIB(w,h,8);  //建立一个和原图像大小相同的25色灰度位图
	BYTE* newlpDIB=(BYTE*)GlobalLock((HGLOBAL) newhDIB);//指向新的位图的指针
    BYTE* newPos = (BYTE*)FindDIBBits((char *)newlpDIB);//指向新的位图的像素起始位置的指针 
	
	double sum;//统计中间值

	//对图像进行扫描
    for(int i=0;i<h;i++)//行
    {  
	   for(int j=0;j<w;j++)//列
	   {   
	       sum=0;//为统计变量赋初始值

          //将点（i,j）点作为模板的中心
          for(int m=i-((tem_h-1)/2);m<=i+((tem_h-1)/2);m++)
          {
		     for(int n=j-((tem_w-1)/2);n<=j+((tem_w-1)/2);n++)
		    
             //将以点（i，j）为中心，与模板大小相同的范围内的像素与模板相应位置对应的系数进行相乘并线形叠加
		     sum+= *(oldPos+m*dw+n) * tem[(m-i+((tem_h-1)/2))*tem_w+n-j+((tem_w-1)/2)]; //相当于tem[当前行数*模板宽度+当前列数]
		  
		  }
          sum=(int)sum*xishu;//将结果乘上总的模板系数
		  sum = fabs(sum);//计算绝对值
		  
          if(sum>255)
			  sum=255;//如果大于255，强制赋值为255，因为像素值0~255 

	      *(newPos+i*dw+j)=sum;//将计算的结果放到新的位图的相应位置
	   }
	} 

	//解除锁定
	GlobalUnlock((HGLOBAL)hDIB);
    
	//返回新的位图的句柄
    return(newhDIB);
}

/////////////////////////////////////////////////////////////////////////////
// CDraw2View

IMPLEMENT_DYNCREATE(CDraw2View, CScrollView)

BEGIN_MESSAGE_MAP(CDraw2View, CScrollView)
	//{{AFX_MSG_MAP(CDraw2View)
	ON_COMMAND(IDM_ELLIPSE, OnEllipse)
	ON_COMMAND(IDM_LINE, OnLine)
	ON_COMMAND(IDM_RECTANGLE, OnRectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_UPDATE_COMMAND_UI(IDM_DOT, OnUpdateDot)
	ON_UPDATE_COMMAND_UI(IDM_ELLIPSE, OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(IDM_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(IDM_RECTANGLE, OnUpdateRectangle)
	ON_COMMAND(IDM_LINESETTING, OnLinesetting)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_DOT, OnDot)
	ON_COMMAND(IDM_PAINT, OnPaint1)
	ON_COMMAND(IDM_PEN, OnPen)
	ON_COMMAND(IDM_SPRAYER, OnSprayer)
	ON_COMMAND(IDM_ERASER, OnEraser)
	ON_UPDATE_COMMAND_UI(IDM_SPRAYER, OnUpdateSprayer)
	ON_UPDATE_COMMAND_UI(IDM_PEN, OnUpdatePen)
	ON_UPDATE_COMMAND_UI(IDM_PAINT, OnUpdatePaint)
	ON_UPDATE_COMMAND_UI(IDM_ERASER, OnUpdateEraser)
	ON_UPDATE_COMMAND_UI(IDM_BRUSH, OnUpdateBrush)
	ON_COMMAND(IDM_BRUSH, OnBrush)
	ON_COMMAND(IDM_NEWSCREEN, OnNewscreen)
	ON_COMMAND(IDM_SAVE, OnSave)
	ON_COMMAND(IDM_NEW, OnNew)
	ON_COMMAND(IDM_OPEN, OnOpen)
	ON_COMMAND(IDM_SOLIDRECTANGLE, OnSolidrectangle)
	ON_UPDATE_COMMAND_UI(IDM_SOLIDRECTANGLE, OnUpdateSolidrectangle)
	ON_COMMAND(IDM_CIRCLE, OnCircle)
	ON_COMMAND(IDM_SOLIDELLIPSE, OnSolidellipse)
	ON_COMMAND(IDM_SOLIDCIRCLE, OnSolidcircle)
	ON_UPDATE_COMMAND_UI(IDM_SOLIDELLIPSE, OnUpdateSolidellipse)
	ON_UPDATE_COMMAND_UI(IDM_SOLIDCIRCLE, OnUpdateSolidcircle)
	ON_UPDATE_COMMAND_UI(IDM_CIRCLE, OnUpdateCircle)
	ON_COMMAND(ID_SAVEIMAGE, OnSaveimage)
	ON_WM_SETCURSOR()
	ON_COMMAND(IDM_GAUSS, OnGauss)
	ON_COMMAND(IDM_COLORGREY, OnColorgrey)
	ON_UPDATE_COMMAND_UI(IDM_TEXT, OnUpdateText)
	ON_WM_CANCELMODE()
	ON_COMMAND(IDM_ROT_LEFT, OnRotLeft)
	ON_COMMAND(IDM_ROT_RIGHT, OnRotRight)
	ON_COMMAND(IDM_FLIP_HOR, OnFlipHor)
	ON_COMMAND(IDM_FLIP_VER, OnFlipVer)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDraw2View construction/destruction

CDraw2View::CDraw2View()
{
	// TODO: add construction code here
	m_ptOrigin=0;
	m_nDrawType=1;
	m_click1=0;
	m_click2=0;
	m_click3=0;
	m_click4=0;
	m_click5=0;
	m_click6=0;
	m_click7=0;
	m_click8=0;
	m_click9=0;
	m_color=RGB(0,0,0);
	m_nLineWidth=1;
	m_nLineStyle=0;
	m_bLBtnDown=false;
	m_writerclick1=0;
	m_writerclick2=0;
	m_writerclick3=0;
	m_writerclick4=0;
	m_writerclick5=0;
	m_nWriterType=0;
	m_isOnDraw=true;
	m_isOnWriter=false;
	m_isOnOpen=0;

	m_Length=800;
	m_Width=600;

}

CDraw2View::~CDraw2View()
{
}

BOOL CDraw2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT BOOL CMFCMDIView::PreCreateWindow(CREATESTRUCT& cs)  
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDraw2View drawing

void CDraw2View::OnDraw(CDC* pDC)
{

	CDraw2Doc* pDoc = (CDraw2Doc*)GetDocument();
	ASSERT_VALID(pDoc);	

	RECT rect1;
	GetClientRect(&rect1);
	pDC->FillSolidRect(&rect1, RGB(96, 96, 96));
	CRect rt(5,5,5+m_Length,5+m_Width); 
	pDC->FillSolidRect(rt, RGB(255, 255, 255)); 
	
	if(pDoc->m_hDIB == NULL)
		return ;
	// TODO: add draw code for native data here
    if (!pDoc)
        return;

	LPSTR lpDIB=(LPSTR)GlobalLock(pDoc->m_hDIB); //锁定m_hDIB对象
	int dibWidth=DIBWidth(lpDIB);	//获得图像宽度
	int dibHeight=DIBHeight(lpDIB); //获得图像高度
	CRect rect2(0,0,dibWidth,dibHeight), rcDIB(0,0,dibWidth,dibHeight);

	//利用DIBAPI中的PaintDIB函数绘制图像
	PaintDIB(pDC->m_hDC, &rect2, pDoc->m_hDIB, &rcDIB, pDoc->m_palDIB);
}




/////////////////////////////////////////////////////////////////////////////
// CDraw2View printing

BOOL CDraw2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDraw2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDraw2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDraw2View diagnostics

#ifdef _DEBUG
void CDraw2View::AssertValid() const
{
	CView::AssertValid();
}

void CDraw2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDraw2View message handlers


void CDraw2View::OnLine() //选中直线段
{
	// TODO: Add your command handler code here
	m_nDrawType=2;
	m_click1=0;
	m_click2=1;
	m_click3=0;
	m_click4=0;
	m_click5=0;
	m_click6=0;
	m_click7=0;
	m_click8=0;
	m_click9=0;
}

void CDraw2View::OnEllipse() //选中椭圆
{
	// TODO: Add your command handler code here
	m_nDrawType=3;
	m_click1=0;
	m_click2=0;
	m_click3=1;
	m_click4=0;
	m_click5=0;
	m_click6=0;
	m_click7=0;
	m_click8=0;
	m_click9=0;
}


void CDraw2View::OnRectangle() //选中矩形
{
	// TODO: Add your command handler code here
	m_nDrawType=4;
	m_click1=0;
	m_click2=0;
	m_click3=0;
	m_click4=1;
	m_click5=0;
	m_click6=0;
	m_click7=0;
	m_click8=0;
	m_click9=0;
}


void CDraw2View::OnLButtonDown(UINT nFlags, CPoint point) //鼠标左键按下
{
	// TODO: Add your message handler code here and/or call default
	m_ptOrigin=m_ptEnd=point;
	CView::OnLButtonDown(nFlags, point);
	m_bLBtnDown=true;
  
    CView::OnLButtonDown(nFlags, point);  
}

void CDraw2View::OnLButtonUp(UINT nFlags, CPoint point) //鼠标左键弹起
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CPen pen(m_nLineStyle,m_nLineWidth,m_color);
	dc.SelectObject(&pen);
	m_bLBtnDown=false;

	//油漆桶效果
	if(m_nWriterType==4)
	{
		CDC* pDC=GetDC();
		CBrush brush(m_color);
		pDC->SelectObject (&brush);
		pDC->FloodFill (m_ptOrigin.x,m_ptOrigin.y,m_color);
	}

	//补画最后一个固定图形，以避免反色交界处变白问题
	if(m_nDrawType==2)//直线段
	{
		 dc.MoveTo(m_ptOrigin);  
         dc.LineTo(point); 
	}
	if(m_nDrawType==3)//椭圆
	{
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush *pOldBrush=dc.SelectObject(pBrush);
        dc.Ellipse(CRect(m_ptOrigin,point));  
	}
	if(m_nDrawType==4)//矩形
	{
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush *pOldBrush=dc.SelectObject(pBrush);
		dc.Rectangle(CRect(m_ptOrigin,point));
	}  
	if(m_nDrawType==5)//实心矩形
	{
		CBrush brush;
		brush.CreateSolidBrush(m_color);
		dc.SelectObject(&brush); 
		dc.Rectangle(CRect(m_ptOrigin,point));
	}  
	if(m_nDrawType==6)//实心椭圆
	{
		CBrush brush;
		brush.CreateSolidBrush(m_color);
		dc.SelectObject(&brush);
        dc.Ellipse(CRect(m_ptOrigin,point));  
	}
	if(m_nDrawType==7)//圆形
	{
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush *pOldBrush=dc.SelectObject(pBrush);
		point.y=point.x-m_ptOrigin.x+m_ptOrigin.y;  
        dc.Ellipse(CRect(m_ptOrigin,point));  
	}
	if(m_nDrawType==8)//实心圆形
	{
		CBrush brush;
		brush.CreateSolidBrush(m_color);
		dc.SelectObject(&brush);
		point.y=point.x-m_ptOrigin.x+m_ptOrigin.y;  
        dc.Ellipse(CRect(m_ptOrigin,point));   
	}


	CView::OnLButtonUp(nFlags, point);

}


void CDraw2View::OnUpdateDot(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click1);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}

void CDraw2View::OnUpdateEllipse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click3);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}

void CDraw2View::OnUpdateLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click2);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}

void CDraw2View::OnUpdateRectangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click4);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}



void CDraw2View::OnLinesetting() 
{
	// TODO: Add your command handler code here
	CSettingDlg dlg;
	dlg.m_nLineWidth=m_nLineWidth;
	dlg.m_nLineStyle=m_nLineStyle;
	if(IDOK==dlg.DoModal())
	{
		m_nLineWidth=dlg.m_nLineWidth;
		m_nLineStyle=dlg.m_nLineStyle;
	}
	
}

void CDraw2View::OnMouseMove(UINT nFlags, CPoint point) 
{ 
	// TODO: Add your message handler code here and/or call default
	if(m_isOnDraw)
	{
		if(!m_isOnWriter)
		{
			if(m_bLBtnDown&&m_nDrawType==1)//绘制一般图线
			{
				CPen m_irPen;
				m_irPen.CreatePen(m_nLineStyle,m_nLineWidth,m_color);
				CDC* pDC= GetDC();
				pDC->SelectObject(&m_irPen);
				pDC->MoveTo(m_ptOrigin);
				pDC->LineTo(point);
				m_ptOrigin=point;
				ReleaseDC(pDC);
			}
			if(m_bLBtnDown&&m_nDrawType==2)//绘制直线
			{

				//SetROP2函数主要用于设定当前前景色的混合模式
				//参数取值R2_NOTXORPEN画出来的颜色与R2_XORPEN相反，R2_XORPEN是屏幕颜色和画笔颜色的异或（不同为1，相同为0）

				//第一次调用OnMouseMove时，还没画线，所以屏幕的颜色是白色的
				//R2_XORPEN是当前画笔的颜色取反，那么R2_NOTXORPEN就是当前画笔颜色了。就是说第一次画的线是画笔的颜色。

				//第二次调用OnMouseMove时，m_ptOrigin和m_ptEnd两个点还没变，所以可以用这两个点再画线，将第一次画的线覆盖掉，变成画布的颜色
				//然后在新的point点和m_ptOrigin之间重新画线，颜色为画笔颜色。

				//在旧的直线上面画线，因为线本来有颜色，所以R2_XORPEN（屏幕的颜色==画笔颜色）就会变成黑色（1 xor 1=0，0 xor 0=0），
				//取反，即R2_NOTXORPEN为白色，就是画布的颜色，看起来就像消失了一样，其实只不过是线变成白色

				//旧的直线删除了，就可以在新的点point上再次画线了。

				CClientDC dc(this);
			    int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);

				dc.MoveTo(m_ptOrigin);
				dc.LineTo(m_ptEnd);

				m_ptEnd=point;

				dc.MoveTo(m_ptOrigin);
				dc.LineTo(m_ptEnd);

				dc.SelectObject(oldpen);
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);

			}
			if(m_bLBtnDown&&m_nDrawType==3)//绘制椭圆
			{
				CClientDC dc(this);

				//空白内部
				CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				CBrush *pOldBrush=dc.SelectObject(pBrush);

				int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);

				dc.Ellipse(CRect(this->m_ptOrigin, m_ptEnd));
				m_ptEnd=point;
				dc.Ellipse(CRect(this->m_ptOrigin, m_ptEnd));

				dc.SelectObject(oldpen);
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);
			}
			if(m_bLBtnDown&&m_nDrawType==4)//绘制矩形
			{

				CClientDC dc(this);  

				CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				CBrush *pOldBrush=dc.SelectObject(pBrush);

				int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);
					
				dc.Rectangle(CRect(m_ptOrigin,m_ptEnd));  
                dc.Rectangle(CRect(m_ptOrigin,point));  
                m_ptEnd=point;  
				dc.SelectObject(oldpen);	
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);
			}	
			if(m_bLBtnDown&&m_nDrawType==5)//绘制实心矩形
			{
				CClientDC dc(this);
				CBrush brush;
				brush.CreateSolidBrush(m_color);
				
				int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);
		
				dc.SelectObject(&brush);
				dc.Rectangle(CRect(this->m_ptOrigin, m_ptEnd));
				m_ptEnd=point;
				dc.Rectangle(CRect(this->m_ptOrigin, m_ptEnd));
				dc.SelectObject(oldpen);	
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);
			}	
			if(m_bLBtnDown&&m_nDrawType==6)//绘制实心椭圆
			{
				CClientDC dc(this);

				CBrush brush;
				brush.CreateSolidBrush(m_color);

				int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);
				
				dc.SelectObject(&brush);
				dc.Ellipse(CRect(this->m_ptOrigin, m_ptEnd));
				m_ptEnd=point;
				dc.Ellipse(CRect(this->m_ptOrigin, m_ptEnd));

				dc.SelectObject(oldpen);
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);
			}
			if(m_bLBtnDown&&m_nDrawType==7)//绘制圆形
			{
				CClientDC dc(this);  

				CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				CBrush *pOldBrush=dc.SelectObject(pBrush);
				
				int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);

				//设定该圆的y坐标，因为要保证两点的x之差等于y之差  
				m_ptEnd.y=m_ptEnd.x-m_ptOrigin.x+m_ptOrigin.y;  
				dc.Ellipse(CRect(m_ptOrigin,m_ptEnd));  
				point.y=point.x-m_ptOrigin.x+m_ptOrigin.y;  
                dc.Ellipse(CRect(m_ptOrigin,point));  

				m_ptEnd=point;
				dc.SelectObject(oldpen);	
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);
			}
			if(m_bLBtnDown&&m_nDrawType==8)//绘制实心圆形
			{
				CClientDC dc(this);

				CBrush brush;
				brush.CreateSolidBrush(m_color);

				int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);
				
				dc.SelectObject(&brush);
				m_ptEnd.y=m_ptEnd.x-m_ptOrigin.x+m_ptOrigin.y;  
				dc.Ellipse(CRect(m_ptOrigin,m_ptEnd));  
				point.y=point.x-m_ptOrigin.x+m_ptOrigin.y;  
                dc.Ellipse(CRect(m_ptOrigin,point));  

				m_ptEnd=point;
				dc.SelectObject(oldpen);	
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);

			}
		}

		if(m_bLBtnDown&&m_nWriterType==2)//钢笔效果
		{
			CClientDC dc(this);
			CPen Pen(PS_SOLID,m_nLineWidth*2,m_color);
			CPen *OldPen = dc.SelectObject(&Pen);

			//钢笔工具为做以点为中心的正方形的对角线
			int a = m_nLineWidth;
			for(int i=0;i<m_nLineWidth;i++)
			{
				//画出
				dc.MoveTo(point.x-a,point.y-a);
				dc.LineTo(point.x+a,point.y+a);
			}

			//还原DC
			dc.SelectObject(OldPen);
		}

		if(m_bLBtnDown&&m_nWriterType==3)//喷雾器效果
		{
			CClientDC dc(this);
			CPoint RandPoint;//接收随机点
			int n;//随机点个数
			int x,y;
			n=rand()%m_nLineWidth+m_nLineWidth*2;//随机点个数
			
			for(int j=0;j<n;j++)
			{

				//保证x和y有正有负，使得随机点分布在当前点四周
				x=rand()%(m_nLineWidth*2+1)-m_nLineWidth;
				y=rand()%(m_nLineWidth*2+1)-m_nLineWidth;
		
				RandPoint.x=point.x+x;
				RandPoint.y=point.y+y;

				dc.SetPixel(RandPoint,m_color);                                                    
			}	
		
			m_ptOrigin=point;
		}


	}


	if(m_bLBtnDown&&m_nWriterType==5)//橡皮擦效果
	{
		CBrush brush(RGB(255,255,255));
		CClientDC dc(this);
		RECT rt;
		rt.left = point.x + 10;
		rt.top = point.y + 11;
		rt.bottom = rt.top + 11*m_nLineWidth;
		rt.right = rt.left + 12*m_nLineWidth;
		dc.FillRect(&rt ,&brush);
	}
	CView::OnMouseMove(nFlags, point);
}



void CDraw2View::OnDot() //选中点
{
	// TODO: Add your command handler code here
	m_nDrawType=1;
	m_click1=1;
	m_click2=0;
	m_click3=0;
	m_click4=0;
	m_click5=0;
	m_click6=0;
	m_click7=0;
	m_click8=0;
	m_click9=0;
}



void CDraw2View::OnPaint1() 
{
	// TODO: Add your command handler code here
	m_isOnDraw=true;
	m_isOnWriter=true;
	m_writerclick1=0;
	m_writerclick2=0;
	m_writerclick3=0;
	m_writerclick4=1;
	m_writerclick5=0;
	m_nWriterType=4;
}

void CDraw2View::OnPen() 
{
	// TODO: Add your command handler code here
	m_isOnDraw=true;
	m_isOnWriter=true;
	m_writerclick1=0;
	m_writerclick2=1;
	m_writerclick3=0;
	m_writerclick4=0;
	m_writerclick5=0;
	m_nWriterType=2;
	m_nDrawType=1;
}

void CDraw2View::OnSprayer() 
{
	// TODO: Add your command handler code here
	m_isOnDraw=true;
	m_isOnWriter=true;
	m_writerclick1=0;
	m_writerclick2=0;
	m_writerclick3=1;
	m_writerclick4=0;
	m_writerclick5=0;
	m_nWriterType=3;
	m_nDrawType=1;
}

void CDraw2View::OnEraser() 
{
	// TODO: Add your command handler code here
	m_isOnDraw=false;
	m_isOnWriter=true;
	m_writerclick1=0;
	m_writerclick2=0;
	m_writerclick3=0;
	m_writerclick4=0;
	m_writerclick5=1;
	m_nWriterType=5;
	m_nDrawType=1;
}



void CDraw2View::OnUpdateSprayer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_writerclick3);
	
}

void CDraw2View::OnUpdatePen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_writerclick2);
	
}

void CDraw2View::OnUpdatePaint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_writerclick4);
}

void CDraw2View::OnUpdateEraser(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_writerclick5);
}

void CDraw2View::OnUpdateBrush(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_writerclick1);
}

void CDraw2View::OnBrush() 
{
	// TODO: Add your command handler code here
	m_isOnDraw=true;
	m_isOnWriter=false;
	m_writerclick1=1;
	m_writerclick2=0;
	m_writerclick3=0;
	m_writerclick4=0;
	m_writerclick5=0;
	m_click1=0;
	m_click2=0;
	m_click3=0;
	m_click4=0;
	m_click5=0;
	m_click6=0;
	m_click7=0;
	m_click8=0;
	m_click9=0;
	m_nWriterType=1;
	m_nDrawType=1;
}




void CDraw2View::OnNewscreen() 
{
	// TODO: Add your command handler code here
	CDC *pDC=GetDC();
	RECT rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(96, 96, 96));
	CRect rt(5,5,5+m_Length,5+m_Width); 
	pDC->FillSolidRect(rt, RGB(255, 255, 255));  
}



void CDraw2View::OnSave() 
{
	// TODO: Add your command handler code here

	CDC* pDC = GetWindowDC();      
    CBitmap bitmap;  //创建临时位图对象作为画布    
    CDC memDC ;      //定义一个显示设备对象  
    CRect rect;      
    GetClientRect(rect);      

    memDC.CreateCompatibleDC(pDC);  //建立与屏幕显示兼容的内存显示设备 

	//判断当前保存的是画布还是图片
	//打开图片后画布长宽变为0
	if(m_Length!=0&&m_Width!=0)
    {
		bitmap.CreateCompatibleBitmap(pDC,m_Length,m_Width);  //建立一个与屏幕显示兼容的位图 
		memDC.SelectObject(&bitmap);   //memDC与空白位图链接
		memDC.BitBlt(0,0,m_Length,m_Width,pDC,0,0,SRCCOPY);  //把pDC上画的图保存起来
	}
	else
	{
		CDraw2Doc* pDoc=GetDocument();
		bitmap.CreateCompatibleBitmap(pDC,pDoc->m_sizeDoc.cx>rect.Width()?rect.Width():pDoc->m_sizeDoc.cx,
			pDoc->m_sizeDoc.cy>rect.Height()?rect.Height():pDoc->m_sizeDoc.cy);  //建立一个与屏幕显示兼容的位图 
		//比较图片长宽和客户区大小，确定保存画面大小
		memDC.SelectObject(&bitmap);   //memDC与空白位图链接
		memDC.BitBlt(0,0,pDoc->m_sizeDoc.cx>rect.Width()?rect.Width():pDoc->m_sizeDoc.cx,
			pDoc->m_sizeDoc.cy>rect.Height()?rect.Height():pDoc->m_sizeDoc.cy,pDC,0,0,SRCCOPY);  //把pDC上画的图保存起来
	}
 
    CFileDialog fDlg(FALSE,_T("bmp"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("位图文件(*.bmp)|*.bmp|"),this);      
    if (fDlg.DoModal()==IDOK)      
    {      

        CString bmpfile = fDlg.GetPathName();      
        CFile file(bmpfile,CFile::modeCreate|CFile::modeWrite);      
 
        BITMAP bInfo;      
        bitmap.GetBitmap(&bInfo); //获得bitmap信息     
 
        //计算调色板大小      
        int panelsize = 0;      

        //定义位图信息      
        BITMAPINFO*  bMapInfo = (BITMAPINFO*)LocalAlloc(LPTR,sizeof(BITMAPINFO)+panelsize); //从堆中分配指定大小的字节数     
        bMapInfo->bmiHeader.biBitCount = bInfo.bmBitsPixel;      
        bMapInfo->bmiHeader.biHeight = bInfo.bmHeight;      
		bMapInfo->bmiHeader.biWidth = bInfo.bmWidth;      
        bMapInfo->bmiHeader.biPlanes = bInfo.bmPlanes;    //指定位图中的颜色平面的数量。
        bMapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);      
        bMapInfo->bmiHeader.biSizeImage = bInfo.bmHeight*bInfo.bmWidthBytes;    //高度*每个光栅行中的字节数
        
  
		//获取位图的实际数据      
		char* pData = new char[bMapInfo->bmiHeader.biSizeImage];      
        int len = GetDIBits(pDC->m_hDC,bitmap,0,bInfo.bmHeight,pData,bMapInfo,DIB_RGB_COLORS);  
        BITMAPFILEHEADER bFileHeader;      

        bFileHeader.bfType = 0x4D42;    //图片的类型 必须是BM 填0x4d42即十进制的19778   
        bFileHeader.bfSize = sizeof(BITMAPFILEHEADER);   //图片的大小  
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+panelsize;  

        //向文件中写入位图数据      
        file.Write(&bFileHeader,sizeof(BITMAPFILEHEADER));      
        file.Write(&bMapInfo->bmiHeader,sizeof(BITMAPINFOHEADER));      
        file.Write(pData,bMapInfo->bmiHeader.biSizeImage+panelsize);
        file.Close();      
        delete pData;      
        LocalFree(bMapInfo);      
    }      

    bitmap.DeleteObject();      
    memDC.DeleteDC();    
}

void CDraw2View::OnNew() 
{
	// TODO: Add your command handler code here
	m_isOnOpen=0;
	CNewPaperDlg dlg;
	CDraw2Doc* pDoc=GetDocument();

	pDoc->OnNewDocument();
	if(IDOK==dlg.DoModal())
	{
		ModifyStyle( WS_VSCROLL|WS_HSCROLL, 0 ); 
		UpdateData(true);
		m_Length=dlg.m_Length;
		m_Width=dlg.m_Width;
		CDC *pDC=GetDC();
		RECT rect;
		GetClientRect(&rect);
		pDC->FillSolidRect(&rect, RGB(96, 96, 96));
		CRect rt(5,5,5+m_Length,5+m_Width); 
		pDC->FillSolidRect(rt, RGB(255, 255, 255)); 
		
	}
}

void CDraw2View::OnOpen() 
{
	// TODO: Add your command handler code here
	m_Length=0;//画布长变为0
	m_Width=0;//画布宽变为0
	m_isOnOpen=1;
	CDraw2Doc* pDoc=GetDocument();

	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|")); 
     if (IDOK==dlg.DoModal())
     {
		pDoc->OnOpenDocument(dlg.GetPathName());
        Invalidate();
     }	
	
}


void CDraw2View::OnSolidrectangle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=5;
	m_click1=0;
	m_click2=0;
	m_click3=0;
	m_click4=0;
	m_click5=1;
	m_click6=0;
	m_click7=0;
	m_click8=0;
	m_click9=0;
}

void CDraw2View::OnUpdateSolidrectangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click5);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}

void CDraw2View::OnCircle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=7;
	m_click1=0;
	m_click2=0;
	m_click3=0;
	m_click4=0;
	m_click5=0;
	m_click6=0;
	m_click7=1;
	m_click8=0;
	m_click9=0;
}

void CDraw2View::OnSolidellipse() 
{
	// TODO: Add your command handler code here
	m_nDrawType=6;
	m_click1=0;
	m_click2=0;
	m_click3=0;
	m_click4=0;
	m_click5=0;
	m_click6=1;
	m_click7=0;
	m_click8=0;
	m_click9=0;
}

void CDraw2View::OnSolidcircle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=8;
	m_click1=0;
	m_click2=0;
	m_click3=0;
	m_click4=0;
	m_click5=0;
	m_click6=0;
	m_click7=0;
	m_click8=1;
	m_click9=0;

}

void CDraw2View::OnUpdateSolidellipse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click6);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}

void CDraw2View::OnUpdateSolidcircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click8);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}

void CDraw2View::OnUpdateCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click7);
	if(m_isOnWriter)
		pCmdUI->Enable(0);
}



void CDraw2View::OnSaveimage() 
{
    CFileDialog fDlg(FALSE,_T("bmp"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("位图文件(*.bmp)|*.bmp|"),this);  
    CDraw2Doc* pDoc=GetDocument();
    if (fDlg.DoModal()==IDOK)      
    {      
		CString bmpfile = fDlg.GetPathName();	//保存路径名  
        CFile nFile;
		if(pDoc->m_hDIB == NULL)
			return;
		nFile.Open(bmpfile,CFile::modeWrite | CFile::modeCreate);	//打开该路径位置，文件写入模式
		SaveDIB(pDoc->m_hDIB, nFile);	//保存文件
		nFile.Close();
	}
  
}

BOOL CDraw2View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_nWriterType==5)//如果是橡皮擦
	{
		HCURSOR   hCursor;
		hCursor = AfxGetApp()->LoadCursor(IDC_ERASER);//装载自定义光标
		SetCursor(hCursor);		//设置光标
		return TRUE;//直接返回，不再调用CView::OnSetCursor
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}



void CDraw2View::OnGauss() 
{
	// TODO: Add your command handler code here

	CDraw2Doc* pDoc = GetDocument();
	//设定模板参数
	double tem[9]={1,2,1,
		           2,4,2,
				   1,2,1};

    //设定模板系数
    double  xishu = 0.0625;  

    //进行模板操作
	pDoc->m_hDIB =Template(pDoc->m_hDIB,tem ,3,3, xishu);

	Invalidate(TRUE);
}


CDraw2Doc* CDraw2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDraw2Doc)));
	return (CDraw2Doc*)m_pDocument;
}

void CDraw2View::OnColorgrey() 
{
	// TODO: Add your command handler code here
	CDraw2Doc* pDoc = GetDocument();
	Convert256toGray(pDoc->m_hDIB);	
	Invalidate(TRUE);

}

void CDraw2View::OnUpdateText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_click9);
}


void CDraw2View::OnCancelMode() 
{
	CScrollView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}


void CDraw2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, GetDocument()->m_sizeDoc);
}

void CDraw2View::OnRotLeft() 
{
	// TODO: Add your command handler code here
	CDraw2Doc* pDoc = GetDocument();
	pDoc->m_hDIB =RotateAntiClock90(pDoc->m_hDIB);
	Invalidate(TRUE);
}

void CDraw2View::OnRotRight() 
{
	// TODO: Add your command handler code here
	CDraw2Doc* pDoc = GetDocument();
	pDoc->m_hDIB=RotateClock90(pDoc->m_hDIB);
	Invalidate(TRUE);
}

void CDraw2View::OnFlipHor() 
{
	// TODO: Add your command handler code here
	CDraw2Doc* pDoc = GetDocument();
	FlipHorizontal(pDoc->m_hDIB);
	Invalidate(TRUE);
}

void CDraw2View::OnFlipVer() 
{
	// TODO: Add your command handler code here
	CDraw2Doc* pDoc = GetDocument();
	FlipVertical(pDoc->m_hDIB);
	Invalidate(TRUE);
}
