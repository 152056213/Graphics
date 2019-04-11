// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//��ѧͷ�ļ�
#define Round(d) int(floor(d+0.5))//��������궨��
#define nNum  4//����Bezier4�����Ƶ�
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
//{{AFX_MSG_MAP(CTestView)
ON_COMMAND(IDM_DRAWPIC, OnDrawpic)
ON_WM_TIMER()
ON_WM_KEYDOWN()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	Alpha = 0.0, Beta = 0.0;
	bPlay = FALSE;
	P = NULL;
}

CTestView::~CTestView()
{
	if (P!=NULL)
	{
		for (int i = 0; i < NumObject; i++)
		{
			delete []P[i];
		}
		delete []P;
	}
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DoubleBuffer(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::DoubleBuffer(CDC* pDC)//˫����
{
	CRect rect;//�ͻ�������
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(), rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(), -rect.Height());//x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width() / 2,rect.Height() / 2);//�ͻ�������Ϊԭ��
	CDC memDC;//�ڴ�DC	
	memDC.CreateCompatibleDC(pDC);//��������ʾpDC���ݵ�memDC
	CBitmap NewBitmap, *pOldBitmap;//�ڴ��г���ͼ�����ʱλͼ 
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//��������λͼ 
	pOldBitmap = memDC.SelectObject(&NewBitmap);//������λͼѡ��memDC
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2,rect.Height() / 2);
//	memDC.FillSolidRect(rect, pDC->GetBkColor());//���ñ���ɫ
	DrawObject(&memDC);//����˫����Bezier����Ƭ
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//���ڴ�memDC�е�λͼ��������ʾpDC��
	memDC.SelectObject(pOldBitmap);//�ָ�λͼ
	NewBitmap.DeleteObject();//ɾ��λͼ
	memDC.DeleteDC();//ɾ��memDC	
}

void CTestView::DrawObject(CDC* pDC)
{
	
	DrawBezier.DrawObject(pDC);
	//DrawBezier.DrawControlGrid(pDC);
}

void CTestView::OnDrawpic() 
{
	// TODO: Add your command handler code here
	bPlay = !bPlay;
	if (bPlay)//���ö�ʱ��
		SetTimer(1, 150, NULL);	
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Alpha = 5;
	Beta = 5;
	for (int i = 0; i < NumObject ;i ++)
	{
		transform.SetMatrix(DrawBezier.Vertex[i],64);
		transform.RotateX(Alpha);
		transform.RotateY(Beta);
	}
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
		int i;
	case VK_UP:
		Alpha = -5;
		for (i = 0; i < NumObject ;i ++)
		{
			transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateX(Alpha);
		}
		
		break;
	case VK_DOWN:
		Alpha = 5;
		for (i = 0; i < NumObject ;i ++)
		{
			transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateX(Alpha);
		}	
		break;
	case VK_LEFT:
		Beta = -5;
		for (i = 0; i < NumObject ;i ++)
		{
            transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateY(Beta);
		}
		break;
	case VK_RIGHT:
		Beta = 5;
		for (i = 0; i < NumObject ;i ++)
		{
			transform.SetMatrix(DrawBezier.Vertex[i],64);
			transform.RotateY(Beta);
		}
		break;
	default:
		break;			
	}
	Invalidate(FALSE);	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	NumObject = 4;
	P = new CP3*[NumObject];
	for (int i = 0; i < NumObject; i++)
	{
		P[i] = new CP3 [4];
	}
	//double a = 1.3;
	P[0][0].x = -43,  P[0][0].y = 203, P[0][0].z = 0;
	P[0][1].x = -83,  P[0][1].y = 228, P[0][1].z = 0;
	P[0][2].x = -96,  P[0][2].y = 195, P[0][2].z = 0;
	P[0][3].x = -51,  P[0][3].y = 191, P[0][3].z = 0;
	P[1][0].x = -51,  P[1][0].y = 191, P[1][0].z = 0;
	P[1][1].x = -51,  P[1][1].y = 171, P[1][1].z = 0;
	P[1][2].x = -47,  P[1][2].y = 138, P[1][2].z = 0;
	P[1][3].x = -110,  P[1][3].y = 61, P[1][3].z = 0;
	P[2][0].x = -110,  P[2][0].y = 61, P[2][0].z = 0;
	P[2][1].x = -189,  P[2][1].y = -18, P[2][1].z = 0;
	P[2][2].x = -259,  P[2][2].y = -110, P[2][2].z = 0;
	P[2][3].x = -168,  P[2][3].y = -212, P[2][3].z = 0;
	P[3][0].x = -168,  P[3][0].y = -213, P[3][0].z = 0;
	P[3][1].x = -168,  P[3][1].y = -238 ,P[3][1].z = 0;
	P[3][2].x = -159,  P[3][2].y = -227, P[3][2].z = 0;
	P[3][3].x = 0,  P[3][3].y = -227, P[3][3].z = 0;
	
	
	DrawBezier.ReadBeizerObject(NumObject,P);
}
