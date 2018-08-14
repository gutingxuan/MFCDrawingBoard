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
	if(m_hDIB!=NULL)	//�жϴ��ͼ���ļ���DIB�����Ƿ�Ϊ�գ����ǿգ��㽫���޳����������
	{
		GlobalFree(m_hDIB);//�ͷ�DIB
		m_hDIB=NULL;
	}
	CFile file;
	if(file.Open(lpszPathName,CFile::modeRead,NULL))//����ѡ����ļ�����ֻ����ʽ����򿪣���һ�����ļ�·�����ڶ�����ģʽλ����������Ȩ��λһ�㲻�ã�ΪNULL
	{
		m_hDIB=ReadDIBFile(file);//����DIBAPI����ReadDIBFile���򿪵��ļ������ڴ棬��HDIB����m_hDIB������
		LPSTR lpDIB = (LPSTR)GlobalLock((HGLOBAL) m_hDIB);//ָ��DIB
		m_sizeDoc.cx = (int) DIBWidth(lpDIB);         // Size of DIB - x
		m_sizeDoc.cy = (int) DIBHeight(lpDIB);        // Size of DIB - y
		GlobalUnlock((HGLOBAL) m_hDIB);
		file.Close();
	}

	//ʵ��ҳ�����
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
	nFile.Open(lpszPathName,CFile::modeWrite | CFile::modeCreate);//��·��λ��
	SaveDIB(m_hDIB, nFile);//����DIBAPI�еĺ����洢ͼ��
	nFile.Close();//�ر��ļ�
	return true;
	//return CDocument::OnSaveDocument(lpszPathName);
}