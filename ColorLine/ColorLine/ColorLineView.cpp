
// ColorLineView.cpp : CColorLineView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ColorLine.h"
#endif

#include "ColorLineDoc.h"
#include "ColorLineView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PI 3.1415926
#define Round(a) int(floor(a+0.5))//���ذ�ָ��λ�����������������ֵ��


// CColorLineView

IMPLEMENT_DYNCREATE(CColorLineView, CView)

BEGIN_MESSAGE_MAP(CColorLineView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CColorLineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CColorLineView ����/����

CColorLineView::CColorLineView()
{
	// TODO: �ڴ˴���ӹ������
	Theta = 0;
	q = -1;
}

CColorLineView::~CColorLineView()
{
}

BOOL CColorLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CColorLineView ����

void CColorLineView::OnDraw(CDC* pDC)
{
	CColorLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;//�������
	GetClientRect(&rect);//��ÿͻ�������
	pDC->SetMapMode(MM_ANISOTROPIC);//����ӳ��ģʽ
	pDC->SetWindowExt(rect.Width(),rect.Height());
	pDC->SetViewportExt(rect.Width(),-rect.Height());//����������x��ˮƽ����Ϊ����y�ᴹֱ����Ϊ��
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//���ÿͻ�������Ϊ����ԭ��
	CDC memDC;//�����ڴ�DC
	CBitmap NewBitmap,*pOldBitmap;
	memDC.CreateCompatibleDC(pDC);//����һ������ʾDC���ݵ��ڴ�DC 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//���������ڴ�λͼ 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//������λͼѡ���ڴ�DC
	memDC.FillSolidRect(rect,pDC->GetBkColor());//��ԭ������ɫ���ͻ����������Ǻ�ɫ
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	memDC.SetMapMode(MM_ANISOTROPIC);//�ڴ�DC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	DrawObject(&memDC);
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY); //���ڴ�DC�е�λͼ�������豸DC
	memDC.SelectObject(pOldBitmap);

	SetTimer(1,5,NULL);


}


// CColorLineView ��ӡ


void CColorLineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CColorLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CColorLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CColorLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CColorLineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CColorLineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CColorLineView ���

#ifdef _DEBUG
void CColorLineView::AssertValid() const
{
	CView::AssertValid();
}

void CColorLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorLineDoc* CColorLineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorLineDoc)));
	return (CColorLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorLineView ��Ϣ�������
void CColorLineView::DrawObject(CDC *pDC)
{
	//����
	long R = 100;
	long r = 10;
	long r1 = 5*r;
	CPoint ld,rt,as,ae;

	CPen NewPen, *pOldPen;
	CBrush NewBrush, *pOldBrush;

	NewPen.CreatePen(PS_DOT,1,RGB(20,20,20));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(-R,-R+200); rt = CPoint(R,R+200); 
	as = CPoint(Round(R*cos(30*PI/180)),-Round(R*sin(30*PI/180))+200); 
	ae = CPoint(Round(R*cos(30*PI/180)),Round(R*sin(30*PI/180))+200);
	pDC->Pie(CRect(ld,rt),as,ae);//�������κ������ƺ�ɫ��Բ


	pDC->SelectObject(pOldPen);//ѡ���ϱʡ�
	NewPen.DeleteObject();//����DeleteObject���������ͷ���Դ��

	//����
	long Width = 30, Height = 40;
	NewPen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	if(0<=Theta && Theta<=180)
	{
		ld = CPoint(-Width/2,-Height/2+100-10/9*Theta-r);
		rt = CPoint(Width/2,Height/2+100-10/9*Theta+r);
	}
	if(180<=Theta && Theta<=360)
	{
        ld = CPoint(-Width/2,-Height/2+100-10/9*(Theta+q)-r);
	    rt = CPoint(Width/2,Height/2+100-10/9*(Theta+q)+r);
	}
	pDC->Rectangle(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	
		//�´�Բ
	NewPen.CreatePen(PS_DOT,1,RGB(0,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(0-r1,-200-r1);
	rt = CPoint(0+r1,-200+r1);
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

		//ֱ��
	pDC->MoveTo(0,300);
	pDC->LineTo(0,-200);

	

		//�Ϸ�����
	NewPen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	pOldPen=pDC->SelectObject(&NewPen);
	if(0<=Theta && Theta<=180)
	{
		as = CPoint(0,200);
		ae = CPoint(Round(1.5*R*cos((30-Theta/3)*PI/180)),200+Round(1.5*R*sin((30-Theta/3)*PI/180)));
	}
	if(180<Theta && Theta<360)
	{
		as = CPoint(0,200);
		ae = CPoint(Round(1.5*R*cos((30-(Theta+q)/3)*PI/180)),200+Round(1.5*R*sin((30-(Theta+q)/3)*PI/180)));
		q-=2;
	}
		//p = 30-(Theta+q)/3;//ae = CPoint(Ro180und(2*R*cos(30*PI/180)),50);
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//�м����
	NewPen.CreatePen(PS_SOLID,3,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	if(0<=Theta && Theta<=180)
	{
		as = CPoint(0,100-10/9*Theta);
		ae = CPoint(Round(R*cos((30-Theta/3)*PI/180)),200+Round(R*sin((30-Theta/3)*PI/180)));
	}
	if(180<=Theta && Theta<=360)
	{
        as = CPoint(0,100-10/9*(Theta+q));
	    ae = CPoint(Round(R*cos((30-(Theta+q)/3)*PI/180)),200+Round(R*sin((30-(Theta+q)/3)*PI/180)));
	}
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//�·�����
	NewPen.CreatePen(PS_SOLID,3,RGB(255,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	//as = CPoint(0,-200+r1);
	//as = CPoint(0,100);
	if(0<=Theta && Theta<=180)
	{
        as = CPoint(Round(r1*cos((-Theta-90)*PI/180)),-200-Round(r1*sin((-Theta-90)*PI/180)));
		ae = CPoint(0,100-10/9*Theta);
		//ae = CPoint(0,100-10/9*Theta);
	}
	if(180<=Theta && Theta<=360)
	{
		as = CPoint(Round(r1*cos((-Theta-90)*PI/180)),-200-Round(r1*sin((-Theta-90)*PI/180)));
        ae = CPoint(0,100-10/9*(Theta+q));
	    //ae = CPoint(0,100-10/9*(Theta+q));
	}
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//�·�����
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,255));
	pOldPen=pDC->SelectObject(&NewPen);

	as = CPoint(0,-200);
	ae = CPoint(Round(r1*cos((-Theta-90)*PI/180)),-200-Round(r1*sin((-Theta-90)*PI/180)));
	pDC->MoveTo(as);
	pDC->LineTo(ae);

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//������С��Բ
	NewPen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&NewPen);

	
	if(0<=Theta && Theta<=180)
	{
		ld = CPoint(-r,100-10/9*Theta-r);
		rt = CPoint(r,100-10/9*Theta+r);
	}
	if(180<=Theta && Theta<=360)
	{
        ld = CPoint(-r,100-10/9*(Theta+q)-r);
	    rt = CPoint(r,100-10/9*(Theta+q)+r);
	}
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//�Ϸ�СԲ
	NewPen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(-r,-r+200);
	rt = CPoint(r,r+200);
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

    //���Ϸ�СԲ
	NewPen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	//ld = CPoint(Round(R*cos(30*PI/180)-r),-Round(R*sin(30*PI/180))+150-r);
	//rt = CPoint(Round(R*cos(30*PI/180)+r),-Round(R*sin(30*PI/180))+150+r);
	if(0<=Theta && Theta<=180)
	{
        ld = CPoint(Round(R*cos((30-Theta/3)*PI/180))-r,200+Round(R*sin((30-Theta/3)*PI/180))-r);
	    rt = CPoint(Round(R*cos((30-Theta/3)*PI/180))+r,200+Round(R*sin((30-Theta/3)*PI/180))+r);
	}
	if(180<=Theta && Theta<=360)
	{
        ld = CPoint(Round(R*cos((30-(Theta+q)/3)*PI/180))-r,200+Round(R*sin((30-(Theta+q)/3)*PI/180))-r);
	    rt = CPoint(Round(R*cos((30-(Theta+q)/3)*PI/180))+r,200+Round(R*sin((30-(Theta+q)/3)*PI/180))+r);
	}
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//��С��Բ
	NewPen.CreatePen(PS_SOLID,2,RGB(0,0,255));
	pOldPen=pDC->SelectObject(&NewPen);

	ld = CPoint(0-r,-200-r);
	rt = CPoint(0+r,-200+r);
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	//����С��Բ
	NewPen.CreatePen(PS_SOLID,2,RGB(255,255,0));
	pOldPen=pDC->SelectObject(&NewPen);

	//ld = CPoint(-r,-150-r);
	//rt = CPoint(r,-150+r);
	ld = CPoint(-r+Round(r1*cos((-Theta-90)*PI/180)),-r-200-Round(r1*sin((-Theta-90)*PI/180)));
	rt = CPoint(r+Round(r1*cos((-Theta-90)*PI/180)),r-200-Round(r1*sin((-Theta-90)*PI/180)));
	pDC->Ellipse(CRect(ld,rt));

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

	
	

}


void CColorLineView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	Theta += 1;
	if(Theta == 360)
			{
				Theta = 0;
				q = -1;
	        }
	Invalidate(FALSE);//ֱ���ػ棬������������
	CView::OnTimer(nIDEvent);
}

