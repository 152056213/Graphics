
// BezierBallView.cpp : CBezierBallView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BezierBall.h"
#endif

#include "BezierBallDoc.h"
#include "BezierBallView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBezierBallView

IMPLEMENT_DYNCREATE(CBezierBallView, CView)

BEGIN_MESSAGE_MAP(CBezierBallView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBezierBallView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CBezierBallView ����/����

CBezierBallView::CBezierBallView()
{
	// TODO: �ڴ˴���ӹ������
}

CBezierBallView::~CBezierBallView()
{
}

BOOL CBezierBallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBezierBallView ����

void CBezierBallView::OnDraw(CDC* pDC)
{
	CBezierBallDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;//���� �ͻ�������
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(),-rect.Height());//����������Χ,x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//�ͻ�������Ϊԭ��
	CDC memDC;//�ڴ�DC
	CBitmap NewBitmap,*pOldBitmap;//�ڴ��г��ص���ʱλͼ
	memDC.CreateCompatibleDC(pDC);//����һ������ʾpDC���ݵ��ڴ�memDC 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//��������λͼ 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//������λͼѡ��memDC 
	memDC.FillSolidRect(rect,pDC->GetBkColor());//��ԭ���������ͻ����������Ǻ�ɫ
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	/////////
	Bezier B1(Q1);
	B1.DrawObject(&memDC);
	Bezier B2(Q2);
	B2.DrawObject(&memDC);
	Bezier B3(Q3);
	B3.DrawObject(&memDC);
	Bezier B4(Q4);
	B4.DrawObject(&memDC);
	Bezier B5(Q5);
	B5.DrawObject(&memDC);
	Bezier B6(Q6);
	B6.DrawObject(&memDC);
	Bezier B7(Q7);
	B7.DrawObject(&memDC);
	Bezier B8(Q8);
	B8.DrawObject(&memDC);
	///////////
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//���ڴ�memDC�е�λͼ��������ʾpDC��
	memDC.SelectObject(pOldBitmap);//�ָ�λͼ
	NewBitmap.DeleteObject();//ɾ��λͼS

	SetTimer(1,200,NULL);   SetTimer(2,300,NULL);
	SetTimer(3,400,NULL);   SetTimer(4,500,NULL);
	SetTimer(5,600,NULL);   SetTimer(6,700,NULL);
	SetTimer(7,800,NULL);   SetTimer(8,900,NULL);
}


// CBezierBallView ��ӡ


void CBezierBallView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBezierBallView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBezierBallView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBezierBallView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CBezierBallView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBezierBallView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBezierBallView ���

#ifdef _DEBUG
void CBezierBallView::AssertValid() const
{
	CView::AssertValid();
}

void CBezierBallView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBezierBallDoc* CBezierBallView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBezierBallDoc)));
	return (CBezierBallDoc*)m_pDocument;
}
#endif //_DEBUG


// CBezierBallView ��Ϣ�������
void CBezierBallView::ReadPoint()
{
	double m=0.5523;
	int  r=200;
	Q1[0][0].x=0; Q1[0][0].y=r;Q1[0][0].z=0;//P00
	Q1[0][1].x=0; Q1[0][1].y=r;Q1[0][1].z=r*m;//P01
	Q1[0][2].x=0;Q1[0][2].y=r*m;Q1[0][2].z=r; //P02
	Q1[0][3].x=0;Q1[0][3].y=0; Q1[0][3].z=r;  //P03

	Q1[1][0].x=0; Q1[1][0].y=r;Q1[1][0].z=0;//P10
	Q1[1][1].x=r*m*m; Q1[1][1].y=r;Q1[1][1].z=r*m;//p11
	Q1[1][2].x=r*m; Q1[1][2].y=r*m;Q1[1][2].z=r; //p12
	Q1[1][3].x=r*m;Q1[1][3].y=0;Q1[1][3].z=r;  //p13

	Q1[2][0].x=0; Q1[2][0].y=r; Q1[2][0].z=0;//P20
	Q1[2][1].x=r*m; Q1[2][1].y=r;Q1[2][1].z=r*m*m; //P21
	Q1[2][2].x=r;Q1[2][2].y=r*m;Q1[2][2].z=r*m; //P22
	Q1[2][3].x=r;Q1[2][3].y=0;Q1[2][3].z=r*m;//P23

	Q1[3][0].x=0; Q1[3][0].y=r;Q1[3][0].z=0;//P30
	Q1[3][1].x=r*m; Q1[3][1].y=r;Q1[3][1].z=0; //P31
	Q1[3][2].x=r;Q1[3][2].y=r*m;Q1[3][2].z=0;  //P32
	Q1[3][3].x=r;Q1[3][3].y=0;Q1[3][3].z=0;//P33
	////////////////////////////////////////////////////////
	Q2[0][0].x=0; Q2[0][0].y=r;Q2[0][0].z=0;//P00
	Q2[0][1].x=r*m; Q2[0][1].y=r;Q2[0][1].z=0;//P01
	Q2[0][2].x=r;Q2[0][2].y=r*m;Q2[0][2].z=0; //P02
	Q2[0][3].x=r;Q2[0][3].y=0; Q2[0][3].z=0;  //P03

	Q2[1][0].x=0; Q2[1][0].y=r;Q2[1][0].z=0;//P10
	Q2[1][1].x=r*m; Q2[1][1].y=r;Q2[1][1].z=-r*m*m;//p11
	Q2[1][2].x=r; Q2[1][2].y=r*m;Q2[1][2].z=-r*m; //p12
	Q2[1][3].x=r;Q2[1][3].y=0;Q2[1][3].z=-r*m;  //p13

	Q2[2][0].x=0; Q2[2][0].y=r; Q2[2][0].z=0;//P20
	Q2[2][1].x=r*m*m; Q2[2][1].y=r;Q2[2][1].z=-r*m; //P21
	Q2[2][2].x=r*m;Q2[2][2].y=r*m;Q2[2][2].z=-r; //P22
	Q2[2][3].x=r*m;Q2[2][3].y=0;Q2[2][3].z=-r;//P23

	Q2[3][0].x=0; Q2[3][0].y=r;Q2[3][0].z=0;//P30
	Q2[3][1].x=0; Q2[3][1].y=r;Q2[3][1].z=-r*m; //P31
	Q2[3][2].x=0;Q2[3][2].y=r*m;Q2[3][2].z=-r;  //P32
	Q2[3][3].x=0;Q2[3][3].y=0;Q2[3][3].z=-r;//P33*/
///////////////////////////////////////////////////////////////////
	Q3[0][0].x=0; Q3[0][0].y=r;Q3[0][0].z=0;//P00
	Q3[0][1].x=0; Q3[0][1].y=r;Q3[0][1].z=r*m;//P01
	Q3[0][2].x=0;Q3[0][2].y=r*m;Q3[0][2].z=r; //P02
	Q3[0][3].x=0;Q3[0][3].y=0; Q3[0][3].z=r;  //P03

	Q3[1][0].x=0; Q3[1][0].y=r;Q3[1][0].z=0;//P10
	Q3[1][1].x=-r*m*m; Q3[1][1].y=r;Q3[1][1].z=r*m;//p11
	Q3[1][2].x=-r*m; Q3[1][2].y=r*m;Q3[1][2].z=r; //p12
	Q3[1][3].x=-r*m;Q3[1][3].y=0;Q3[1][3].z=r;  //p13

	Q3[2][0].x=0; Q3[2][0].y=r; Q3[2][0].z=0;//P20
	Q3[2][1].x=-r*m; Q3[2][1].y=r;Q3[2][1].z=r*m*m; //P21
	Q3[2][2].x=-r;Q3[2][2].y=r*m;Q3[2][2].z=r*m; //P22
	Q3[2][3].x=-r;Q3[2][3].y=0;Q3[2][3].z=r*m;//P23

	Q3[3][0].x=0; Q3[3][0].y=r;Q3[3][0].z=0;//P30
	Q3[3][1].x=-r*m; Q3[3][1].y=r;Q3[3][1].z=0; //P31
	Q3[3][2].x=-r;Q3[3][2].y=r*m;Q3[3][2].z=0;  //P32
	Q3[3][3].x=-r;Q3[3][3].y=0;Q3[3][3].z=0;//P33
	////////////////////////////////////////////////
	Q4[0][0].x=0; Q4[0][0].y=r;Q4[0][0].z=0;//P00
	Q4[0][1].x=-r*m; Q4[0][1].y=r;Q4[0][1].z=0;//P01
	Q4[0][2].x=-r;Q4[0][2].y=r*m;Q4[0][2].z=0; //P02
	Q4[0][3].x=-r;Q4[0][3].y=0; Q4[0][3].z=0;  //P03

	Q4[1][0].x=0; Q4[1][0].y=r;Q4[1][0].z=0;//P10
	Q4[1][1].x=-r*m; Q4[1][1].y=r;Q4[1][1].z=-r*m*m;//p11
	Q4[1][2].x=-r; Q4[1][2].y=r*m;Q4[1][2].z=-r*m; //p12
	Q4[1][3].x=-r;Q4[1][3].y=0;Q4[1][3].z=-r*m;  //p13

	Q4[2][0].x=0; Q4[2][0].y=r; Q4[2][0].z=0;//P20
	Q4[2][1].x=-r*m*m; Q4[2][1].y=r;Q4[2][1].z=-r*m; //P21
	Q4[2][2].x=-r*m;Q4[2][2].y=r*m;Q4[2][2].z=-r; //P22
	Q4[2][3].x=-r*m;Q4[2][3].y=0;Q4[2][3].z=-r;//P23

	Q4[3][0].x=0; Q4[3][0].y=r;Q4[3][0].z=0;//P30
	Q4[3][1].x=0; Q4[3][1].y=r;Q4[3][1].z=-r*m; //P31
	Q4[3][2].x=0;Q4[3][2].y=r*m;Q4[3][2].z=-r;  //P32
	Q4[3][3].x=0;Q4[3][3].y=0;Q4[3][3].z=-r;//P33
	////////////////////////////////////////////////////
	Q5[0][0].x=0;   Q5[0][0].y=-r;   Q5[0][0].z=0;//P00
	Q5[0][1].x=0;   Q5[0][1].y=-r;   Q5[0][1].z=r*m;//P01
	Q5[0][2].x=0;   Q5[0][2].y=-r*m; Q5[0][2].z=r; //P02
	Q5[0][3].x=0;   Q5[0][3].y=0;    Q5[0][3].z=r;  //P03

	Q5[1][0].x=0;     Q5[1][0].y=-r;    Q5[1][0].z=0;//P10
	Q5[1][1].x=r*m*m; Q5[1][1].y=-r;    Q5[1][1].z=r*m;//p11
	Q5[1][2].x=r*m;   Q5[1][2].y=-r*m;  Q5[1][2].z=r; //p12
	Q5[1][3].x=r*m;   Q5[1][3].y=0;     Q5[1][3].z=r;  //p13

	Q5[2][0].x=0;     Q5[2][0].y=-r;    Q5[2][0].z=0;//P20
	Q5[2][1].x=r*m;   Q5[2][1].y=-r;    Q5[2][1].z=r*m*m; //P21
	Q5[2][2].x=r;     Q5[2][2].y=-r*m;  Q5[2][2].z=r*m; //P22
	Q5[2][3].x=r;     Q5[2][3].y=0;     Q5[2][3].z=r*m;//P23

	Q5[3][0].x=0;     Q5[3][0].y=-r;    Q5[3][0].z=0;//P30
	Q5[3][1].x=r*m;   Q5[3][1].y=-r;    Q5[3][1].z=0; //P31
	Q5[3][2].x=r;     Q5[3][2].y=-r*m;  Q5[3][2].z=0;  //P32
	Q5[3][3].x=r;     Q5[3][3].y=0;     Q5[3][3].z=0;//P33
	////////////////////////////////////////////////////////
	Q6[0][0].x=0;     Q6[0][0].y=-r;    Q6[0][0].z=0;//P00
	Q6[0][1].x=r*m;   Q6[0][1].y=-r;    Q6[0][1].z=0;//P01
	Q6[0][2].x=r;     Q6[0][2].y=-r*m;  Q6[0][2].z=0; //P02
	Q6[0][3].x=r;     Q6[0][3].y=0;     Q6[0][3].z=0;  //P03

	Q6[1][0].x=0;     Q6[1][0].y=-r;    Q6[1][0].z=0;//P10
	Q6[1][1].x=r*m;   Q6[1][1].y=-r;    Q6[1][1].z=-r*m*m;//p11
	Q6[1][2].x=r;     Q6[1][2].y=-r*m;  Q6[1][2].z=-r*m; //p12
	Q6[1][3].x=r;     Q6[1][3].y=0;     Q6[1][3].z=-r*m;  //p13

	Q6[2][0].x=0;     Q6[2][0].y=-r;    Q6[2][0].z=0;//P20
	Q6[2][1].x=r*m*m; Q6[2][1].y=-r;    Q6[2][1].z=-r*m; //P21
	Q6[2][2].x=r*m;   Q6[2][2].y=-r*m;  Q6[2][2].z=-r; //P22
	Q6[2][3].x=r*m;   Q6[2][3].y=0;     Q6[2][3].z=-r;//P23

	Q6[3][0].x=0;	  Q6[3][0].y=-r;    Q6[3][0].z=0;//P30
	Q6[3][1].x=0;	  Q6[3][1].y=-r;    Q6[3][1].z=-r*m; //P31
	Q6[3][2].x=0;     Q6[3][2].y=-r*m;	Q6[3][2].z=-r;  //P32
	Q6[3][3].x=0;	  Q6[3][3].y=0;		Q6[3][3].z=-r;//P33
/////////////////////////////////////////////////////////////////
	Q7[0][0].x=0;     Q7[0][0].y=-r;	Q7[0][0].z=0;//P00
	Q7[0][1].x=-r*m;  Q7[0][1].y=-r;	Q7[0][1].z=0;//P01
	Q7[0][2].x=-r;	  Q7[0][2].y=-r*m;  Q7[0][2].z=0; //P02
	Q7[0][3].x=-r;	  Q7[0][3].y=0;		Q7[0][3].z=0;  //P03

	Q7[1][0].x=0;     Q7[1][0].y=-r;	Q7[1][0].z=0;//P10
	Q7[1][1].x=-r*m;  Q7[1][1].y=-r;	Q7[1][1].z=r*m*m;//p11
	Q7[1][2].x=-r;	  Q7[1][2].y=-r*m;	Q7[1][2].z=r*m; //p12
	Q7[1][3].x=-r;	  Q7[1][3].y=0;		Q7[1][3].z=r*m;  //p13

	Q7[2][0].x=0;      Q7[2][0].y=-r;  Q7[2][0].z=0;//P20
	Q7[2][1].x=-r*m*m; Q7[2][1].y=-r;  Q7[2][1].z=r*m; //P21
	Q7[2][2].x=-r*m;   Q7[2][2].y=-r*m;Q7[2][2].z=r; //P22
	Q7[2][3].x=-r*m;   Q7[2][3].y=0;   Q7[2][3].z=r;//P23

	Q7[3][0].x=0;      Q7[3][0].y=-r;  Q7[3][0].z=0;//P30
	Q7[3][1].x=0;      Q7[3][1].y=-r;  Q7[3][1].z=r*m; //P31
	Q7[3][2].x=0;      Q7[3][2].y=-r*m;Q7[3][2].z=r;  //P32
	Q7[3][3].x=0;	   Q7[3][3].y=0;   Q7[3][3].z=r;//P33
	////////////////////////////////////////////////
	Q8[0][0].x=0; Q8[0][0].y=-r;Q8[0][0].z=0;//P00
	Q8[0][1].x=-r*m; Q8[0][1].y=-r;Q8[0][1].z=0;//P01
	Q8[0][2].x=-r;Q8[0][2].y=-r*m;Q8[0][2].z=0; //P02
	Q8[0][3].x=-r;Q8[0][3].y=0; Q8[0][3].z=0;  //P03

	Q8[1][0].x=0; Q8[1][0].y=-r;Q8[1][0].z=0;//P10
	Q8[1][1].x=-r*m; Q8[1][1].y=-r;Q8[1][1].z=-r*m*m;//p11
	Q8[1][2].x=-r; Q8[1][2].y=-r*m;Q8[1][2].z=-r*m; //p12
	Q8[1][3].x=-r;Q8[1][3].y=0;Q8[1][3].z=-r*m;  //p13

	Q8[2][0].x=0; Q8[2][0].y=-r; Q8[2][0].z=0;//P20
	Q8[2][1].x=-r*m*m; Q8[2][1].y=-r;Q8[2][1].z=-r*m; //P21
	Q8[2][2].x=-r*m;Q8[2][2].y=-r*m;Q8[2][2].z=-r; //P22
	Q8[2][3].x=-r*m;Q8[2][3].y=0;Q8[2][3].z=-r;//P23

	Q8[3][0].x=0; Q8[3][0].y=-r;Q8[3][0].z=0;//P30
	Q8[3][1].x=0; Q8[3][1].y=-r;Q8[3][1].z=-r*m; //P31
	Q8[3][2].x=0;Q8[3][2].y=-r*m;Q8[3][2].z=-r;  //P32
	Q8[3][3].x=0;Q8[3][3].y=0;Q8[3][3].z=-r;//P33
}


void CBezierBallView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Alpha=5;Beta=5;
	switch(nIDEvent)
	{
		case 1:
	{
		tran.SetMatrix(P1,16);
		for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			Q1[i][j].x = P1[i*4+j].x;
			Q1[i][j].y = P1[i*4+j].y;
			Q1[i][j].z = P1[i*4+j].z;
		}
	}
		tran.RotateX(Alpha);
		tran.RotateY(Beta);
	}
		case 2:
		{
			tran.SetMatrix(P2,16);
		for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			Q2[i][j].x = P2[i*4+j].x;
			Q2[i][j].y = P2[i*4+j].y;
			Q2[i][j].z = P2[i*4+j].z;
		}
	}
		tran.RotateX(Alpha);
		tran.RotateY(Beta);
		}

		case 3:
			{
				tran.SetMatrix(P3,16);
		for(int i=0;i<4;i++)
	  {
		for(int j=0;j<4;j++)
		{
			Q3[i][j].x = P3[i*4+j].x;
			Q3[i][j].y = P3[i*4+j].y;
			Q3[i][j].z = P3[i*4+j].z;
		}
	  }
		tran.RotateX(Alpha);
		tran.RotateY(Beta);
	  }
		case 4:
			{
				tran.SetMatrix(P4,16);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						Q4[i][j].x = P4[i*4+j].x;
						Q4[i][j].y = P4[i*4+j].y;
						Q4[i][j].z = P4[i*4+j].z;
					}
				}
				tran.RotateX(Alpha);
				tran.RotateY(Beta);
			}
		case 5:
			{
				tran.SetMatrix(P5,16);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						Q5[i][j].x = P5[i*4+j].x;
						Q5[i][j].y = P5[i*4+j].y;
						Q5[i][j].z = P5[i*4+j].z;
					}
				}
				tran.RotateX(Alpha);
				tran.RotateY(Beta);
			}
	    case 6:
			{
				tran.SetMatrix(P6,16);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						Q6[i][j].x = P6[i*4+j].x;
						Q6[i][j].y = P6[i*4+j].y;
						Q6[i][j].z = P6[i*4+j].z;
					}
				}
				tran.RotateX(Alpha);
				tran.RotateY(Beta);
			}
		case 7:
			{
				tran.SetMatrix(P7,16);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						Q7[i][j].x = P7[i*4+j].x;
						Q7[i][j].y = P7[i*4+j].y;
						Q7[i][j].z = P7[i*4+j].z;
					}
				}
				tran.RotateX(Alpha);
				tran.RotateY(Beta);
				Invalidate(FALSE);
			}
	    case 8:
			{
				tran.SetMatrix(P8,16);
				for(int i=0;i<4;i++)
				{
					for(int j=0;j<4;j++)
					{
						Q8[i][j].x = P8[i*4+j].x;
						Q8[i][j].y = P8[i*4+j].y;
						Q8[i][j].z = P8[i*4+j].z;
					}
				}
				tran.RotateX(Alpha);
				tran.RotateY(Beta);
				Invalidate(FALSE);
			}
	}
	CView::OnTimer(nIDEvent);
}


void CBezierBallView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	ReadPoint();
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			P1[i*4+j].x = Q1[i][j].x;
			P1[i*4+j].y = Q1[i][j].y;
			P1[i*4+j].z = Q1[i][j].z;
		}
	}
	//tran.SetMatrix(P1,16);
	//////
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			P2[i*4+j].x = Q2[i][j].x;
			P2[i*4+j].y = Q2[i][j].y;
			P2[i*4+j].z = Q2[i][j].z;
		}
	}
	//tran.SetMatrix(P2,16);
	////
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			P3[i*4+j].x = Q3[i][j].x;
			P3[i*4+j].y = Q3[i][j].y;
			P3[i*4+j].z = Q3[i][j].z;
		}
	}
	//tran.SetMatrix(P3,16);
	/////
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)

		{
			P4[i*4+j].x = Q4[i][j].x;
			P4[i*4+j].y = Q4[i][j].y;
			P4[i*4+j].z = Q4[i][j].z;
		}
	}
	//tran.SetMatrix(P4,16);
	////
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)

		{
			P5[i*4+j].x = Q5[i][j].x;
			P5[i*4+j].y = Q5[i][j].y;
			P5[i*4+j].z = Q5[i][j].z;
		}
	}
	//tran.SetMatrix(P5,16);
	/////
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)

		{
			P6[i*4+j].x = Q6[i][j].x;
			P6[i*4+j].y = Q6[i][j].y;
			P6[i*4+j].z = Q6[i][j].z;
		}
	}
	//tran.SetMatrix(P6,16);
	/////
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)

		{
			P7[i*4+j].x = Q7[i][j].x;
			P7[i*4+j].y = Q7[i][j].y;
			P7[i*4+j].z = Q7[i][j].z;
		}
	}
	//tran.SetMatrix(P7,16);
	/////
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)

		{
			P8[i*4+j].x = Q8[i][j].x;
			P8[i*4+j].y = Q8[i][j].y;
			P8[i*4+j].z = Q8[i][j].z;
		}
	}
	//tran.SetMatrix(P8,16);
	/////
}


//BOOL CBezierBallView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	return TRUE;
//}
