// Draw2Doc.cpp : implementation of the CDraw2Doc class
//

#include "stdafx.h"
#include "Draw2.h"

#include "Draw2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDraw2Doc

IMPLEMENT_DYNCREATE(CDraw2Doc, CDocument)

BEGIN_MESSAGE_MAP(CDraw2Doc, CDocument)
	//{{AFX_MSG_MAP(CDraw2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDraw2Doc construction/destruction

CDraw2Doc::CDraw2Doc()
{
	// TODO: add one-time construction code here
	m_sizeDoc.cx = 0;
	m_sizeDoc.cy = 0;

	m_palDIB = NULL;
	m_hDIB = NULL;
}

CDraw2Doc::~CDraw2Doc()
{
	if (m_hDIB != NULL)
	{
		GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB=NULL;
	}	
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB=NULL;
	}

}
BOOL CDraw2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_sizeDoc.cx=0;
	m_sizeDoc.cy=0;
	m_hDIB = NewDIB(m_sizeDoc.cx, m_sizeDoc.cy,8);
	InitDIBData();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDraw2Doc serialization

void CDraw2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDraw2Doc diagnostics

#ifdef _DEBUG
void CDraw2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDraw2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDraw2Doc commands



BOOL CDraw2Doc::InitDIBData()
{
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}
	if (m_hDIB == NULL)
	{
		return FALSE;
	}
	m_palDIB = new CPalette;
	if (m_palDIB == NULL)
	{
		GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
		return FALSE;
	}

	if (CreateDIBPalette(m_hDIB, m_palDIB) == NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}

	return TRUE;
}

BOOL CDraw2Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	PathName=lpszPathName;
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO: Add your specialized creation code here
	if(m_hDIB!=NULL)	//判断存放图像文件的DIB对象是否为空，若非空，便将其剔除，重新填充
	{
		GlobalFree(m_hDIB);//释放DIB
		m_hDIB=NULL;
	}
	CFile file;
	if(file.Open(lpszPathName,CFile::modeRead,NULL))//根据选择的文件按照只读方式将其打开，第一个是文件路径，第二个是模式位，第三个是权限位一般不用，为NULL
	{
		m_hDIB=ReadDIBFile(file);//调用DIBAPI函数ReadDIBFile将打开的文件读入内存，由HDIB对象m_hDIB来保存
		LPSTR lpDIB = (LPSTR)GlobalLock((HGLOBAL) m_hDIB);//指向DIB
		m_sizeDoc.cx = (int) DIBWidth(lpDIB);         // Size of DIB - x
		m_sizeDoc.cy = (int) DIBHeight(lpDIB);        // Size of DIB - y
		GlobalUnlock((HGLOBAL) m_hDIB);
		file.Close();
	}

	//实现页面滚动
	POSITION pos;
	pos = GetFirstViewPosition();
	CScrollView * pView = (CScrollView *)GetNextView(pos);
	if(pView != NULL)
	{
		pView->SetScrollSizes(MM_TEXT, m_sizeDoc);
	}
}

BOOL CDraw2Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	CFile nFile;
	if(m_hDIB == NULL)
		return  false;
	nFile.Open(lpszPathName,CFile::modeWrite | CFile::modeCreate);//打开路径位置
	SaveDIB(m_hDIB, nFile);//利用DIBAPI中的函数存储图像
	nFile.Close();//关闭文件
	return true;
	//return CDocument::OnSaveDocument(lpszPathName);
}