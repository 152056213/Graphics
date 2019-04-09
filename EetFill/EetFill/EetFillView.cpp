
// EetFillView.cpp : CEetFillView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "EetFill.h"
#endif

#include "EetFillDoc.h"
#include "EetFillView.h"
#include "Fill.h"
#include "math.h"
#define Round(a) int(floor(a+0.5))

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEetFillView

IMPLEMENT_DYNCREATE(CEetFillView, CView)

BEGIN_MESSAGE_MAP(CEetFillView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEetFillView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_DRAW, &CEetFillView::OnDraw)
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_DrawPolygon, &CEetFillView::OnDrawpolygon)
ON_COMMAND(ID_Fill, &CEetFillView::OnFill)
END_MESSAGE_MAP()

// CEetFillView ����/����

CEetFillView::CEetFillView()
{
	// TODO: �ڴ˴���ӹ������
}

CEetFillView::~CEetFillView()
{
}

BOOL CEetFillView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CEetFillView ����

void CEetFillView::OnDraw(CDC* pDC)
{
	CEetFillDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//CRect rect;                                         //����ͻ���
	//GetClientRect(&rect);                               //��ÿͻ����Ĵ�С                                   //�����豸������ָ��              
	//pDC->SetMapMode(MM_ANISOTROPIC);                    //�Զ�������ϵ
	//pDC->SetWindowExt(rect.Width(),rect.Height());      //���ô��ڱ���
	//pDC->SetViewportExt(rect.Width(),-rect.Height());   //����������������x��ˮƽ���ң�y�ᴹֱ����
	//pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//���ÿͻ�������Ϊ����ϵԭ��
	//rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);  //������ͻ����غ�
	////Draw(pDC);
	//FillPolygon(pDC);
}


// CEetFillView ��ӡ


void CEetFillView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEetFillView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CEetFillView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CEetFillView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}
// CEetFillView ���

#ifdef _DEBUG
void CEetFillView::AssertValid() const
{
	CView::AssertValid();
}

void CEetFillView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEetFillDoc* CEetFillView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEetFillDoc)));
	return (CEetFillDoc*)m_pDocument;
}
#endif //_DEBUG
void CEetFillView::Draw(CDC*pDC)
{
	for(int i = 0;i<num;i++)
	{
	    if(i == 0)
		{
	        pDC->MoveTo(Q[i]);
			t = Q[i];
		}
		else
		    pDC->LineTo(Q[i]);
	}
}
void CEetFillView::FillPolygon(CDC *pDC)
{
	//ReadPoint();
	for(int i=0;i<num;i++)//ת���������꣬y����ȡΪ����
	{
		P1[i].x=Round(Q[i].x);
		P1[i].y=Round(Q[i].y);
		if(i == 0)
		    P1[i].c=CRGB(0.0,0.0,0.0);
		if(i == 1)	
		    P1[i].c=CRGB(1.0,0.0,0.0);
		if(i == 2)	
		    P1[i].c=CRGB(1.0,1.0,0.0);
		if(i == 3)	
		    P1[i].c=CRGB(0.0,1.0,0.0);
		if(i == 4)	
		    P1[i].c=CRGB(0.0,0.0,1.0);
		if(i == 5)
		    P1[i].c=CRGB(1.0,0.0,1.0);
	}
	CFill *fill=new CFill;      //��̬�����ڴ� 
	fill->SetPoint(P1,num);       //��ʼ��Fill����
	fill->CreateBucket();       //����Ͱ��
	fill->CreateEdge();         //�����߱�
    fill->Gouraud(pDC);         //�������
	delete fill;                //�����ڴ�
}
void CEetFillView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC = GetDC();
	if(bFlag)
	{
	    Q[num].x = point.x;
	    Q[num].y = point.y;
		if(num<Max)
		num++;
	}
	Draw(pDC);
	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}


void CEetFillView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC = GetDC();
	bFlag = FALSE;
	Draw(pDC);
	pDC->LineTo(t);
	ReleaseDC(pDC);
	CView::OnRButtonDown(nFlags, point);
}


void CEetFillView::OnDrawpolygon()
{
	// TODO: �ڴ���������������
	MessageBox(CString("������ƿ��ƶ���Σ��Ҽ��պ϶����"),CString("��ʾ"),MB_OK);
	//RedrawWindow();//��������
	bFlag = TRUE;
	Max = 10;
	num = 0;
    Q=new CPoint[Max];
}


void CEetFillView::OnFill()
{
	// TODO: �ڴ���������������
	CDC *pDC = GetDC();
	FillPolygon(pDC);
	ReleaseDC(pDC);
}

