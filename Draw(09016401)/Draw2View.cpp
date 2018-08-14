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

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//ָ��ͼ����ʼλ�õ�ָ��
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//ָ��������ʼλ�õ�ָ��

    int numColors=(int)DIBNumColors((char *)lpDIB);//��ȡͼ�����ɫ��Ϣ

    //���ͼ����256ɫ����
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//�������
		return;
	 }

	int w, h, dw;
	w = (int)DIBWidth((char *)lpDIB);//��ȡͼ��Ŀ��
	h = (int)DIBHeight((char *)lpDIB);//��ȡͼ��ĸ߶�
	dw = (w+3)/4*4;//����ͼ��ÿ�е��ֽ��� DataSizePerLine= (biWidth*1+3)/4*4   

	for(int i=0;i<w/2;i++)//��
	{
		for(int j=0;j<h;j++)//��
		{
			BYTE temp;
			temp=*(oldPos+j*dw+i);
			*(oldPos+j*dw+i)=*(oldPos+j*dw+w-i);
			*(oldPos+j*dw+w-i)=temp;
		}
	}
	//�������
	GlobalUnlock((HGLOBAL)hDIB);
}

void FlipVertical(HDIB hDIB)
{

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//ָ��ͼ����ʼλ�õ�ָ��
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//ָ��������ʼλ�õ�ָ��

    int numColors=(int)DIBNumColors((char *)lpDIB);//��ȡͼ�����ɫ��Ϣ

    //���ͼ����256ɫ����
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//�������
		return;
	 }

	int w, h, dw;
	w = (int)DIBWidth((char *)lpDIB);//��ȡͼ��Ŀ��
	h = (int)DIBHeight((char *)lpDIB);//��ȡͼ��ĸ߶�
	dw = (w+3)/4*4;//����ͼ��ÿ�е��ֽ��� DataSizePerLine= (biWidth*1+3)/4*4   

	for(int i=0;i<h/2;i++)//��
	{
		for(int j=0;j<w;j++)//��
		{
			BYTE temp;
			temp=*(oldPos+i*dw+j);
			*(oldPos+i*dw+j)=*(oldPos+(h-i)*dw+j);
			*(oldPos+(h-i)*dw+j)=temp;
		}
	}
	//�������
	GlobalUnlock((HGLOBAL)hDIB);
}

HDIB RotateAntiClock90(HDIB hDIB)
{
	//��ת�������ҷ�ת

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//ָ��ͼ����ʼλ�õ�ָ��
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//ָ��������ʼλ�õ�ָ��

    int numColors=(int)DIBNumColors((char *)lpDIB);//��ȡͼ�����ɫ��Ϣ

    //���ͼ����256ɫ����
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//�������
		return(hDIB);
	 }

	int w, h, dw,dh;
	w = (int)DIBWidth((char *)lpDIB);//��ȡͼ��Ŀ��
	h = (int)DIBHeight((char *)lpDIB);//��ȡͼ��ĸ߶�
	dw = (w+3)/4*4;//����ͼ��ÿ�е��ֽ��� DataSizePerLine= (biWidth*1+3)/4*4   
	dh = (h+3)/4*4;//����ͼ��ÿ�е��ֽ��� DataSizePerLine= (biWidth*1+3)/4*4   

	HDIB newhDIB=NewDIB(h,w,8);  //����һ����ԭͼ�񳤿��෴��25ɫ�Ҷ�λͼ
	BYTE* newlpDIB=(BYTE*)GlobalLock((HGLOBAL) newhDIB);//ָ���µ�λͼ��ָ��
    BYTE* newPos = (BYTE*)FindDIBBits((char *)newlpDIB);//ָ���µ�λͼ��������ʼλ�õ�ָ�� 


	//��ͼ�����ת��
    for(int i=0;i<w;i++)
    {  
	   for(int j=0;j<h;j++)
	   {   
		   *(newPos+i*dh+j)=*(oldPos+j*dw+i);
	   }
	} 

	//��ͼ��������ҷ�ת
	for(int m=0;m<h/2;m++)//��
	{
		for(int n=0;n<w;n++)//��
		{
			BYTE temp;
			temp=*(newPos+n*dh+m);
			*(newPos+n*dh+m)=*(newPos+n*dh+h-m);
			*(newPos+n*dh+h-m)=temp;
		}
	}

	//�������
	GlobalUnlock((HGLOBAL)hDIB);
	return(newhDIB);
}

HDIB RotateClock90(HDIB hDIB)
{
	//��ת�������·�ת

	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL)hDIB);//ָ��ͼ����ʼλ�õ�ָ��
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//ָ��������ʼλ�õ�ָ��

    int numColors=(int)DIBNumColors((char *)lpDIB);//��ȡͼ�����ɫ��Ϣ

    //���ͼ����256ɫ����
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//�������
		return(hDIB);
	 }

	int w, h, dw,dh;
	w = (int)DIBWidth((char *)lpDIB);//��ȡͼ��Ŀ��
	h = (int)DIBHeight((char *)lpDIB);//��ȡͼ��ĸ߶�
	dw = (w+3)/4*4;//����ͼ��ÿ�е��ֽ��� DataSizePerLine= (biWidth*1+3)/4*4   
	dh = (h+3)/4*4;//����ͼ��ÿ�е��ֽ��� DataSizePerLine= (biWidth*1+3)/4*4   

	HDIB newhDIB=NewDIB(h,w,8);  //����һ����ԭͼ�񳤿��෴��25ɫ�Ҷ�λͼ
	BYTE* newlpDIB=(BYTE*)GlobalLock((HGLOBAL) newhDIB);//ָ���µ�λͼ��ָ��
    BYTE* newPos = (BYTE*)FindDIBBits((char *)newlpDIB);//ָ���µ�λͼ��������ʼλ�õ�ָ�� 


	//��ͼ�����ת��
    for(int i=0;i<w;i++)
    {  
	   for(int j=0;j<h;j++)
	   {   
		   *(newPos+i*dh+j)=*(oldPos+j*dw+i);
	   }
	} 

	//��ͼ��������·�ת
	for(int m=0;m<w/2;m++)//��
	{
		for(int n=0;n<h;n++)//��
		{
			BYTE temp;
			temp=*(newPos+m*dh+n);
			*(newPos+m*dh+n)=*(newPos+(w-m)*dh+n);
			*(newPos+(w-m)*dh+n)=temp;
		}
	}

	//�������
	GlobalUnlock((HGLOBAL)hDIB);
	return(newhDIB);
}


void Convert256toGray(HDIB hDIB)
{
	LPSTR	lpDIB;
	lpDIB = (LPSTR) GlobalLock((HGLOBAL)hDIB);// ��DIB����õ�DIBָ�벢����DIB

	LPSTR lpDIBBits;// ָ��DIB������������ָ��	
	LONG lWidth;// ͼ����	
	LONG lHeight;// ͼ��߶�	
	LONG lLineBytes;	// ͼ��ÿ�е��ֽ���
	
	LPBITMAPINFO lpbmi;	// ָ��BITMAPINFO�ṹ��ָ��
	lpbmi = (LPBITMAPINFO)lpDIB;// ��ȡָ��BITMAPINFO�ṹ��ָ��

	BYTE bMap[256];// �Ҷ�ӳ���
	
	// ����Ҷ�ӳ������������ɫ�ĻҶ�ֵ����������DIB��ɫ��
	int	i,j;
	for (i = 0; i < 256; i ++)
	{
		// �������ɫ��Ӧ�ĻҶ�ֵ  Gray = (R*299 + G*587 + B*114 + 500) / 1000
		bMap[i] = (BYTE)(0.299 * lpbmi->bmiColors[i].rgbRed +
					     0.587 * lpbmi->bmiColors[i].rgbGreen +
				         0.114 * lpbmi->bmiColors[i].rgbBlue + 0.5);			
		
		lpbmi->bmiColors[i].rgbRed = i;	// ����DIB��ɫ���ɫ����
		lpbmi->bmiColors[i].rgbGreen = i; // ����DIB��ɫ����ɫ����
		lpbmi->bmiColors[i].rgbBlue = i; // ����DIB��ɫ����ɫ����
	}
	
	lpDIBBits = FindDIBBits(lpDIB); // �ҵ�DIBͼ��������ʼλ��
	lWidth = DIBWidth(lpDIB);	// ��ȡͼ����
	lHeight = DIBHeight(lpDIB); // ��ȡͼ��߶�	
	lLineBytes = WIDTHBYTES(lWidth * 8); // ����ͼ��ÿ�е��ֽ���

	// ����ÿ�����ص���ɫ�����������ջҶ�ӳ����ɻҶ�ֵ��
	for(i = 0; i < lHeight; i++)//��
	{
		for(j = 0; j < lWidth; j++)//��
		{
			// ָ��DIB��i�У���j�����ؽ��б任
			*(lpDIBBits + i*lLineBytes + j)=bMap[*(unsigned char*)(lpDIBBits + i*lLineBytes + j)];
		}
	}

	//�������
	GlobalUnlock ((HGLOBAL)hDIB);
}


/*
	ͼ�����ģ�壬��ʵ�ָ�˹ƽ��
	��˹�˲����Ƕ�����ͼ����м�Ȩƽ���Ĺ��̣�ÿһ�����ص��ֵ�������䱾��������ڵ���������ֵ������Ȩƽ����õ���
	��˹�˲��ľ�������ǣ���һ��ģ�壨��ƾ������ģ��ɨ��ͼ���е�ÿһ�����أ���ģ��ȷ�������������صļ�Ȩƽ���Ҷ�ֵȥ���ģ���������ص��ֵ��

	HDIB hDIB         ��ͼ��ľ��
    double* tem       ��ָ��ģ���ָ��
    int tem_w         ��ģ��Ŀ��
	int tem_h         ��ģ��ĸ߶�
    double xishu      ��ģ���ϵ��
*/

 HDIB Template(HDIB hDIB,double* tem ,int tem_w,int tem_h,double xishu)
{
	 
	BYTE* lpDIB=(BYTE*)GlobalLock((HGLOBAL) hDIB);//ָ��ͼ����ʼλ�õ�ָ��
	BYTE* oldPos =(BYTE*)FindDIBBits((char*)lpDIB);//ָ��������ʼλ�õ�ָ��

    int numColors=(int)DIBNumColors((char *)lpDIB);//��ȡͼ�����ɫ��Ϣ

    //���ͼ����256ɫ����
     if (numColors!=256) 
	 {   
	  	GlobalUnlock((HGLOBAL)hDIB);//�������
		return(hDIB);
	 }

	int w, h, dw;
	w = (int)DIBWidth((char *)lpDIB);//��ȡͼ��Ŀ��
	h = (int)DIBHeight((char *)lpDIB);//��ȡͼ��ĸ߶�
	dw = (w+3)/4*4;//����ͼ��ÿ�е��ֽ��� DataSizePerLine= (biWidth*1+3)/4*4   

    HDIB newhDIB=NewDIB(w,h,8);  //����һ����ԭͼ���С��ͬ��25ɫ�Ҷ�λͼ
	BYTE* newlpDIB=(BYTE*)GlobalLock((HGLOBAL) newhDIB);//ָ���µ�λͼ��ָ��
    BYTE* newPos = (BYTE*)FindDIBBits((char *)newlpDIB);//ָ���µ�λͼ��������ʼλ�õ�ָ�� 
	
	double sum;//ͳ���м�ֵ

	//��ͼ�����ɨ��
    for(int i=0;i<h;i++)//��
    {  
	   for(int j=0;j<w;j++)//��
	   {   
	       sum=0;//Ϊͳ�Ʊ�������ʼֵ

          //���㣨i,j������Ϊģ�������
          for(int m=i-((tem_h-1)/2);m<=i+((tem_h-1)/2);m++)
          {
		     for(int n=j-((tem_w-1)/2);n<=j+((tem_w-1)/2);n++)
		    
             //���Ե㣨i��j��Ϊ���ģ���ģ���С��ͬ�ķ�Χ�ڵ�������ģ����Ӧλ�ö�Ӧ��ϵ��������˲����ε���
		     sum+= *(oldPos+m*dw+n) * tem[(m-i+((tem_h-1)/2))*tem_w+n-j+((tem_w-1)/2)]; //�൱��tem[��ǰ����*ģ����+��ǰ����]
		  
		  }
          sum=(int)sum*xishu;//����������ܵ�ģ��ϵ��
		  sum = fabs(sum);//�������ֵ
		  
          if(sum>255)
			  sum=255;//�������255��ǿ�Ƹ�ֵΪ255����Ϊ����ֵ0~255 

	      *(newPos+i*dw+j)=sum;//������Ľ���ŵ��µ�λͼ����Ӧλ��
	   }
	} 

	//�������
	GlobalUnlock((HGLOBAL)hDIB);
    
	//�����µ�λͼ�ľ��
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

	LPSTR lpDIB=(LPSTR)GlobalLock(pDoc->m_hDIB); //����m_hDIB����
	int dibWidth=DIBWidth(lpDIB);	//���ͼ����
	int dibHeight=DIBHeight(lpDIB); //���ͼ��߶�
	CRect rect2(0,0,dibWidth,dibHeight), rcDIB(0,0,dibWidth,dibHeight);

	//����DIBAPI�е�PaintDIB��������ͼ��
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


void CDraw2View::OnLine() //ѡ��ֱ�߶�
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

void CDraw2View::OnEllipse() //ѡ����Բ
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


void CDraw2View::OnRectangle() //ѡ�о���
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


void CDraw2View::OnLButtonDown(UINT nFlags, CPoint point) //����������
{
	// TODO: Add your message handler code here and/or call default
	m_ptOrigin=m_ptEnd=point;
	CView::OnLButtonDown(nFlags, point);
	m_bLBtnDown=true;
  
    CView::OnLButtonDown(nFlags, point);  
}

void CDraw2View::OnLButtonUp(UINT nFlags, CPoint point) //����������
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CPen pen(m_nLineStyle,m_nLineWidth,m_color);
	dc.SelectObject(&pen);
	m_bLBtnDown=false;

	//����ͰЧ��
	if(m_nWriterType==4)
	{
		CDC* pDC=GetDC();
		CBrush brush(m_color);
		pDC->SelectObject (&brush);
		pDC->FloodFill (m_ptOrigin.x,m_ptOrigin.y,m_color);
	}

	//�������һ���̶�ͼ�Σ��Ա��ⷴɫ���紦�������
	if(m_nDrawType==2)//ֱ�߶�
	{
		 dc.MoveTo(m_ptOrigin);  
         dc.LineTo(point); 
	}
	if(m_nDrawType==3)//��Բ
	{
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush *pOldBrush=dc.SelectObject(pBrush);
        dc.Ellipse(CRect(m_ptOrigin,point));  
	}
	if(m_nDrawType==4)//����
	{
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush *pOldBrush=dc.SelectObject(pBrush);
		dc.Rectangle(CRect(m_ptOrigin,point));
	}  
	if(m_nDrawType==5)//ʵ�ľ���
	{
		CBrush brush;
		brush.CreateSolidBrush(m_color);
		dc.SelectObject(&brush); 
		dc.Rectangle(CRect(m_ptOrigin,point));
	}  
	if(m_nDrawType==6)//ʵ����Բ
	{
		CBrush brush;
		brush.CreateSolidBrush(m_color);
		dc.SelectObject(&brush);
        dc.Ellipse(CRect(m_ptOrigin,point));  
	}
	if(m_nDrawType==7)//Բ��
	{
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CBrush *pOldBrush=dc.SelectObject(pBrush);
		point.y=point.x-m_ptOrigin.x+m_ptOrigin.y;  
        dc.Ellipse(CRect(m_ptOrigin,point));  
	}
	if(m_nDrawType==8)//ʵ��Բ��
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
			if(m_bLBtnDown&&m_nDrawType==1)//����һ��ͼ��
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
			if(m_bLBtnDown&&m_nDrawType==2)//����ֱ��
			{

				//SetROP2������Ҫ�����趨��ǰǰ��ɫ�Ļ��ģʽ
				//����ȡֵR2_NOTXORPEN����������ɫ��R2_XORPEN�෴��R2_XORPEN����Ļ��ɫ�ͻ�����ɫ����򣨲�ͬΪ1����ͬΪ0��

				//��һ�ε���OnMouseMoveʱ����û���ߣ�������Ļ����ɫ�ǰ�ɫ��
				//R2_XORPEN�ǵ�ǰ���ʵ���ɫȡ������ôR2_NOTXORPEN���ǵ�ǰ������ɫ�ˡ�����˵��һ�λ������ǻ��ʵ���ɫ��

				//�ڶ��ε���OnMouseMoveʱ��m_ptOrigin��m_ptEnd�����㻹û�䣬���Կ��������������ٻ��ߣ�����һ�λ����߸��ǵ�����ɻ�������ɫ
				//Ȼ�����µ�point���m_ptOrigin֮�����»��ߣ���ɫΪ������ɫ��

				//�ھɵ�ֱ�����滭�ߣ���Ϊ�߱�������ɫ������R2_XORPEN����Ļ����ɫ==������ɫ���ͻ��ɺ�ɫ��1 xor 1=0��0 xor 0=0����
				//ȡ������R2_NOTXORPENΪ��ɫ�����ǻ�������ɫ��������������ʧ��һ������ʵֻ�������߱�ɰ�ɫ

				//�ɵ�ֱ��ɾ���ˣ��Ϳ������µĵ�point���ٴλ����ˡ�

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
			if(m_bLBtnDown&&m_nDrawType==3)//������Բ
			{
				CClientDC dc(this);

				//�հ��ڲ�
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
			if(m_bLBtnDown&&m_nDrawType==4)//���ƾ���
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
			if(m_bLBtnDown&&m_nDrawType==5)//����ʵ�ľ���
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
			if(m_bLBtnDown&&m_nDrawType==6)//����ʵ����Բ
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
			if(m_bLBtnDown&&m_nDrawType==7)//����Բ��
			{
				CClientDC dc(this);  

				CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				CBrush *pOldBrush=dc.SelectObject(pBrush);
				
				int oldmode=dc.SetROP2(R2_NOTXORPEN);
				CPen pen(m_nLineStyle, m_nLineWidth, m_color), *oldpen;
				oldpen = dc.SelectObject(&pen);

				//�趨��Բ��y���꣬��ΪҪ��֤�����x֮�����y֮��  
				m_ptEnd.y=m_ptEnd.x-m_ptOrigin.x+m_ptOrigin.y;  
				dc.Ellipse(CRect(m_ptOrigin,m_ptEnd));  
				point.y=point.x-m_ptOrigin.x+m_ptOrigin.y;  
                dc.Ellipse(CRect(m_ptOrigin,point));  

				m_ptEnd=point;
				dc.SelectObject(oldpen);	
				dc.SetROP2(oldmode);
				ReleaseDC(&dc);
			}
			if(m_bLBtnDown&&m_nDrawType==8)//����ʵ��Բ��
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

		if(m_bLBtnDown&&m_nWriterType==2)//�ֱ�Ч��
		{
			CClientDC dc(this);
			CPen Pen(PS_SOLID,m_nLineWidth*2,m_color);
			CPen *OldPen = dc.SelectObject(&Pen);

			//�ֱʹ���Ϊ���Ե�Ϊ���ĵ������εĶԽ���
			int a = m_nLineWidth;
			for(int i=0;i<m_nLineWidth;i++)
			{
				//����
				dc.MoveTo(point.x-a,point.y-a);
				dc.LineTo(point.x+a,point.y+a);
			}

			//��ԭDC
			dc.SelectObject(OldPen);
		}

		if(m_bLBtnDown&&m_nWriterType==3)//������Ч��
		{
			CClientDC dc(this);
			CPoint RandPoint;//���������
			int n;//��������
			int x,y;
			n=rand()%m_nLineWidth+m_nLineWidth*2;//��������
			
			for(int j=0;j<n;j++)
			{

				//��֤x��y�����и���ʹ�������ֲ��ڵ�ǰ������
				x=rand()%(m_nLineWidth*2+1)-m_nLineWidth;
				y=rand()%(m_nLineWidth*2+1)-m_nLineWidth;
		
				RandPoint.x=point.x+x;
				RandPoint.y=point.y+y;

				dc.SetPixel(RandPoint,m_color);                                                    
			}	
		
			m_ptOrigin=point;
		}


	}


	if(m_bLBtnDown&&m_nWriterType==5)//��Ƥ��Ч��
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



void CDraw2View::OnDot() //ѡ�е�
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
    CBitmap bitmap;  //������ʱλͼ������Ϊ����    
    CDC memDC ;      //����һ����ʾ�豸����  
    CRect rect;      
    GetClientRect(rect);      

    memDC.CreateCompatibleDC(pDC);  //��������Ļ��ʾ���ݵ��ڴ���ʾ�豸 

	//�жϵ�ǰ������ǻ�������ͼƬ
	//��ͼƬ�󻭲������Ϊ0
	if(m_Length!=0&&m_Width!=0)
    {
		bitmap.CreateCompatibleBitmap(pDC,m_Length,m_Width);  //����һ������Ļ��ʾ���ݵ�λͼ 
		memDC.SelectObject(&bitmap);   //memDC��հ�λͼ����
		memDC.BitBlt(0,0,m_Length,m_Width,pDC,0,0,SRCCOPY);  //��pDC�ϻ���ͼ��������
	}
	else
	{
		CDraw2Doc* pDoc=GetDocument();
		bitmap.CreateCompatibleBitmap(pDC,pDoc->m_sizeDoc.cx>rect.Width()?rect.Width():pDoc->m_sizeDoc.cx,
			pDoc->m_sizeDoc.cy>rect.Height()?rect.Height():pDoc->m_sizeDoc.cy);  //����һ������Ļ��ʾ���ݵ�λͼ 
		//�Ƚ�ͼƬ����Ϳͻ�����С��ȷ�����滭���С
		memDC.SelectObject(&bitmap);   //memDC��հ�λͼ����
		memDC.BitBlt(0,0,pDoc->m_sizeDoc.cx>rect.Width()?rect.Width():pDoc->m_sizeDoc.cx,
			pDoc->m_sizeDoc.cy>rect.Height()?rect.Height():pDoc->m_sizeDoc.cy,pDC,0,0,SRCCOPY);  //��pDC�ϻ���ͼ��������
	}
 
    CFileDialog fDlg(FALSE,_T("bmp"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("λͼ�ļ�(*.bmp)|*.bmp|"),this);      
    if (fDlg.DoModal()==IDOK)      
    {      

        CString bmpfile = fDlg.GetPathName();      
        CFile file(bmpfile,CFile::modeCreate|CFile::modeWrite);      
 
        BITMAP bInfo;      
        bitmap.GetBitmap(&bInfo); //���bitmap��Ϣ     
 
        //�����ɫ���С      
        int panelsize = 0;      

        //����λͼ��Ϣ      
        BITMAPINFO*  bMapInfo = (BITMAPINFO*)LocalAlloc(LPTR,sizeof(BITMAPINFO)+panelsize); //�Ӷ��з���ָ����С���ֽ���     
        bMapInfo->bmiHeader.biBitCount = bInfo.bmBitsPixel;      
        bMapInfo->bmiHeader.biHeight = bInfo.bmHeight;      
		bMapInfo->bmiHeader.biWidth = bInfo.bmWidth;      
        bMapInfo->bmiHeader.biPlanes = bInfo.bmPlanes;    //ָ��λͼ�е���ɫƽ���������
        bMapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);      
        bMapInfo->bmiHeader.biSizeImage = bInfo.bmHeight*bInfo.bmWidthBytes;    //�߶�*ÿ����դ���е��ֽ���
        
  
		//��ȡλͼ��ʵ������      
		char* pData = new char[bMapInfo->bmiHeader.biSizeImage];      
        int len = GetDIBits(pDC->m_hDC,bitmap,0,bInfo.bmHeight,pData,bMapInfo,DIB_RGB_COLORS);  
        BITMAPFILEHEADER bFileHeader;      

        bFileHeader.bfType = 0x4D42;    //ͼƬ������ ������BM ��0x4d42��ʮ���Ƶ�19778   
        bFileHeader.bfSize = sizeof(BITMAPFILEHEADER);   //ͼƬ�Ĵ�С  
        bFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+panelsize;  

        //���ļ���д��λͼ����      
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
	m_Length=0;//��������Ϊ0
	m_Width=0;//�������Ϊ0
	m_isOnOpen=1;
	CDraw2Doc* pDoc=GetDocument();

	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT,_T("λͼ�ļ�(*.BMP)|*.BMP|")); 
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
    CFileDialog fDlg(FALSE,_T("bmp"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("λͼ�ļ�(*.bmp)|*.bmp|"),this);  
    CDraw2Doc* pDoc=GetDocument();
    if (fDlg.DoModal()==IDOK)      
    {      
		CString bmpfile = fDlg.GetPathName();	//����·����  
        CFile nFile;
		if(pDoc->m_hDIB == NULL)
			return;
		nFile.Open(bmpfile,CFile::modeWrite | CFile::modeCreate);	//�򿪸�·��λ�ã��ļ�д��ģʽ
		SaveDIB(pDoc->m_hDIB, nFile);	//�����ļ�
		nFile.Close();
	}
  
}

BOOL CDraw2View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_nWriterType==5)//�������Ƥ��
	{
		HCURSOR   hCursor;
		hCursor = AfxGetApp()->LoadCursor(IDC_ERASER);//װ���Զ�����
		SetCursor(hCursor);		//���ù��
		return TRUE;//ֱ�ӷ��أ����ٵ���CView::OnSetCursor
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}



void CDraw2View::OnGauss() 
{
	// TODO: Add your command handler code here

	CDraw2Doc* pDoc = GetDocument();
	//�趨ģ�����
	double tem[9]={1,2,1,
		           2,4,2,
				   1,2,1};

    //�趨ģ��ϵ��
    double  xishu = 0.0625;  

    //����ģ�����
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
