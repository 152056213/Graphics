
// DBezierView.cpp : CDBezierView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DBezier.h"
#endif

#include "DBezierDoc.h"
#include "DBezierView.h"
#include "math.h"
#define Round(a) int(floor(a+0.5))

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDBezierView

IMPLEMENT_DYNCREATE(CDBezierView, CView)

BEGIN_MESSAGE_MAP(CDBezierView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDBezierView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CDBezierView ����/����

CDBezierView::CDBezierView()
{
	// TODO: �ڴ˴���ӹ������
	t = 0.0;
	j = 0;
	P[0].x = -400, P[0].y = -200;
	P[1].x = -200, P[1].y = 100;
	P[2].x = 300,  P[2].y = 200;
	P[3].x = 400,  P[3].y = -200;
}

CDBezierView::~CDBezierView()
{
}

BOOL CDBezierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDBezierView ����

void CDBezierView::OnDraw(CDC* pDC)
{
	CDBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width()/2, rect.Height()/2);
	CDC memDC;//�����ڴ�DC
	memDC.CreateCompatibleDC(pDC);//����һ������ʾDC���ݵ��ڴ�DC
	CBitmap NewBitmap, *pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(), rect.Height());//���������ڴ�λͼ 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//������λͼѡ���ڴ�DC
	memDC.FillSolidRect(rect,pDC->GetBkColor());//���ÿͻ�������ɫ
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//�ڴ�DC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	DrawPic(&memDC);
	DrawPolygon(&memDC);
	DrawBezier(&memDC);//��memDC����ͼ��
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width()/2, -rect.Height()/2, SRCCOPY); //���ڴ�DC�е�λͼ��������ʾDC
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();

	SetTimer(1,100,NULL);
}


// CDBezierView ��ӡ


void CDBezierView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDBezierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDBezierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDBezierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CDBezierView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDBezierView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDBezierView ���

#ifdef _DEBUG
void CDBezierView::AssertValid() const
{
	CView::AssertValid();
}

void CDBezierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBezierDoc* CDBezierView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBezierDoc)));
	return (CDBezierDoc*)m_pDocument;
}
#endif //_DEBUG


// CDBezierView ��Ϣ�������
void CDBezierView::DrawPic(CDC *pDC)//�ַ�����ʽ��
{
	CString str;
	str.Format(_T("t=%g"), t);
	pDC->TextOutW(P[0].x+100,P[0].y,str);
}
void CDBezierView::DrawPolygon(CDC *pDC)
{
	CPen NewPen,*pOldPen;
	CBrush NewBrush,*pOldBrush;
	NewPen.CreatePen(PS_SOLID,2,RGB(0,0,255));
	NewBrush.CreateSolidBrush(RGB(0,0,255));
	pOldPen = pDC->SelectObject(&NewPen);
	pOldBrush = pDC->SelectObject(&NewBrush);
	for(int i=0;i<4;i++)
	{
		if(0==i)
		{
			pDC->MoveTo(P[i]);
			pDC->Ellipse(P[i].x-5,P[i].y-5,P[i].x+5,P[i].y+5);
		}
		else
		{
			pDC->LineTo(P[i]);
			pDC->Ellipse(P[i].x-5,P[i].y-5,P[i].x+5,P[i].y+5);
		}
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
	pDC->SelectObject(pOldBrush);
	NewPen.DeleteObject();
}
void CDBezierView::DrawBezier(CDC *pDC)
{	
	CBrush NewBrush,*pOldBrush;
	//����
	NewBrush.CreateSolidBrush(RGB(0,255,0));
	pOldBrush = pDC->SelectObject(&NewBrush);
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	pOldPen = pDC->SelectObject(&NewPen);
	    p[0].x = Round(P[0].x+(P[1].x-P[0].x)*t);
		p[0].y = Round(P[0].y+(P[1].y-P[0].y)*t);
		p[1].x = Round(P[1].x+(P[2].x-P[1].x)*t);
		p[1].y = Round(P[1].y+(P[2].y-P[1].y)*t);
		p[2].x = Round(P[2].x+(P[3].x-P[2].x)*t);
		p[2].y = Round(P[2].y+(P[3].y-P[2].y)*t);
		for(int i = 0;i<3;i++)
		{
			if(i == 0)
			{
				pDC->MoveTo(p[i]);
				pDC->Ellipse(p[i].x-5,p[i].y-5,p[i].x+5,p[i].y+5);
			}
			else
			{
				pDC->LineTo(p[i]);
				pDC->Ellipse(p[i].x-5,p[i].y-5,p[i].x+5,p[i].y+5);
			}
		}
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		NewBrush.DeleteObject();
		NewPen.DeleteObject();
		//����
		NewPen.CreatePen(PS_SOLID,3,RGB(255,255,0));
		pOldPen = pDC->SelectObject(&NewPen);
		NewBrush.CreateSolidBrush(RGB(255,255,0));
		pOldBrush = pDC->SelectObject(&NewBrush);
		p[3].x = Round(p[0].x+(p[1].x-p[0].x)*t);
		p[3].y = Round(p[0].y+(p[1].y-p[0].y)*t);
		p[4].x = Round(p[1].x+(p[2].x-p[1].x)*t);
		p[4].y = Round(p[1].y+(p[2].y-p[1].y)*t);
		for(int i = 3;i<5;i++)
		{
			if(i == 3)
			{
				pDC->MoveTo(p[i]);
				pDC->Ellipse(p[i].x-5,p[i].y-5,p[i].x+5,p[i].y+5);
			}
			else
			{
				pDC->LineTo(p[i]);
				pDC->Ellipse(p[i].x-5,p[i].y-5,p[i].x+5,p[i].y+5);
			}
		}
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		NewBrush.DeleteObject();
		NewPen.DeleteObject();
		//����
		
		NewPen.CreatePen(PS_SOLID,3,RGB(255,0,0));
		pOldPen = pDC->SelectObject(&NewPen);
		NewBrush.CreateSolidBrush(RGB(255,0,0));
		pOldBrush = pDC->SelectObject(&NewBrush);
		p[5].x = Round(p[3].x+(p[4].x-p[3].x)*t);
		p[5].y = Round(p[3].y+(p[4].y-p[3].y)*t);
		q[j].x = p[5].x;
		q[j].y = p[5].y;

		for(int i=0;i<=j;i++)
		{
		if(i==0)
		{
			pDC->MoveTo(q[i].x,q[i].y);	
		}
		else
		{
			pDC->LineTo(q[i].x,q[i].y);
			pDC->Ellipse(q[j].x-5,q[j].y-5,q[j].x+5,q[j].y+5);
		}
		}
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
		NewBrush.DeleteObject();
		NewPen.DeleteObject();
}

void CDBezierView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	t+=0.01;
	j+=1;
	if(t >= 1.0)//��һ��˲�䲻����1.0����������
	{
		t = 0.0;
		j = 0;
	}			    
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}
