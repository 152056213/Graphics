
// NBzierView.cpp : CNBzierView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "NBzier.h"
#endif

#include "NBzierDoc.h"
#include "NBzierView.h"
#include "math.h"
#define  PI 3.1415926//PI�ĺ궨��
#define Round(a) int(floor(a+0.5)) //��������궨��
#define MAX 8//���ƶ���ε���󶥵���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNBzierView

IMPLEMENT_DYNCREATE(CNBzierView, CView)

BEGIN_MESSAGE_MAP(CNBzierView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNBzierView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAWPIC, &CNBzierView::OnDrawpic)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CNBzierView ����/����

CNBzierView::CNBzierView()
{
	// TODO: �ڴ˴���ӹ������
	P=new CPoint[MAX];
	bFlag = TRUE;
}

CNBzierView::~CNBzierView()
{
}

BOOL CNBzierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CNBzierView ����

void CNBzierView::OnDraw(CDC* /*pDC*/)
{
	CNBzierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CNBzierView ��ӡ


void CNBzierView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNBzierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CNBzierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CNBzierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CNBzierView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CNBzierView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CNBzierView ���

#ifdef _DEBUG
void CNBzierView::AssertValid() const
{
	CView::AssertValid();
}

void CNBzierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNBzierDoc* CNBzierView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNBzierDoc)));
	return (CNBzierDoc*)m_pDocument;
}
#endif //_DEBUG


// CNBzierView ��Ϣ�������
void CNBzierView::OnDrawpic()
{
	// TODO: �ڴ���������������
	MessageBox(CString("������ƿ��ƶ���Σ��Ҽ���������"),CString("��ʾ"),MB_OK);
	//RedrawWindow();
	Invalidate(TRUE);
	bFlag=TRUE;
	CtrlPointNum=0;
}

void CNBzierView::DrawCtrlPolygon()//���ƿ��ƶ����
{
	CDC *pDC=GetDC();//��ȡ�豸������ָ�� 
	CBrush NewBrush,*pOldBrush;
	NewBrush.CreateSolidBrush(RGB(0,255,0));
	pOldBrush=/*(CBrush*)*/pDC->SelectObject(&NewBrush);/*SelectStockObject(GRAY_BRUSH);*///��ɫʵ��Բ���ƿ��Ƶ�
	for(int i=0;i<=n;i++)
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
	pDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
}
long CNBzierView::Fac(int m)//�׳˺���
{
	long F;
	if(m==0 || m ==1)
		F = 1;
	else
		F = m*Fac(m-1);
	return F;
}
double CNBzierView::Cni(const int &n,const int &i)//Bernstein��һ�����
{
	return double (Fac(n)/(Fac(i)*Fac(n-i)));
}
void CNBzierView::DrawBezier()//����Bezier����
{
	CDC *pDC = GetDC();
	CPen NewPen,*pOldPen;
	NewPen.CreatePen(PS_SOLID,1,RGB(0,255,0));
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(P[0]);
	for(double t=0.0; t<=1.0; t+=0.01)
	{
		double x = 0,y = 0;
		for(int i=0;i<=n;i++)
		{
			x+=P[i].x*Cni(n,i)*pow(t,i)*pow((1-t),n-i);
			y+=P[i].y*Cni(n,i)*pow(t,i)*pow((1-t),n-i);
		}
		pDC->LineTo(Round(x),Round(y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
	ReleaseDC(pDC);
}
void CNBzierView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	if(bFlag)
	{
		P[CtrlPointNum].x = point.x;
		P[CtrlPointNum].y = point.y;
		if(CtrlPointNum<MAX)
			CtrlPointNum++;
		else
			bFlag = FALSE;
		n = CtrlPointNum-1;
		DrawCtrlPolygon();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CNBzierView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(CtrlPointNum!=0)
		DrawBezier();

	CView::OnRButtonDown(nFlags, point);
}
