
// CutView.cpp : CCutView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Cut.h"
//#include "math.h"
#endif

#include "CutDoc.h"
#include "CutView.h"
#include "math.h"
#define LEFT 1     //����0001
#define RIGHT 2    //����0010
#define BOTTOM 4   //����0100
#define TOP 8      //����1000
#define Round(a) int(floor(a+0.5))//��������궨��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCutView

IMPLEMENT_DYNCREATE(CCutView, CView)

BEGIN_MESSAGE_MAP(CCutView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCutView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OnDrawPic, &CCutView::OnOndrawpic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CLIP, &CCutView::OnClip)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CCutView ����/����

CCutView::CCutView()
{
	// TODO: �ڴ˴���ӹ������
	wxl=-300;
	wyt=150;
	wxr=300;
	wyb=-150;
	PtCount=0;
	bDrawLine=FALSE;
}

CCutView::~CCutView()
{
}

BOOL CCutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCutView ����

void CCutView::OnDraw(CDC* pDC)
{
	CCutDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;//����ͻ���
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
	DrawWindowRect(&memDC);//���ƴ���
	if(PtCount>=1)
	{
		CPen NewPen,*pOldPen;
		NewPen.CreatePen(PS_DASH,3,RGB(255,0,0));
		pOldPen = memDC.SelectObject(&NewPen);
		memDC.MoveTo(Round(P[0].x),Round(P[0].y));
		memDC.LineTo(Round(P[1].x),Round(P[1].y));
		pDC->SelectObject(pOldPen);
		NewPen.DeleteObject();
	}
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//���ڴ�memDC�е�λͼ��������ʾpDC��
	memDC.SelectObject(pOldBitmap);//�ָ�λͼ
	NewBitmap.DeleteObject();//ɾ��λͼ
}


// CCutView ��ӡ


void CCutView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCutView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCutView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCutView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CCutView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCutView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCutView ���

#ifdef _DEBUG
void CCutView::AssertValid() const
{
	CView::AssertValid();
}

void CCutView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCutDoc* CCutView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCutDoc)));
	return (CCutDoc*)m_pDocument;
}
#endif //_DEBUG


 //CCutView ��Ϣ�������
void CCutView::OnOndrawpic()
{
	// TODO: �ڴ���������������
	PtCount=0;
	bDrawLine=TRUE;
	MessageBox(CString("��껭�ߣ������ü�"),CString("��ʾ"),/*MB_YESNO*/MB_OKCANCEL);
}
void CCutView::EnCode(CP2 &pt)//�˵���뺯��
{
	pt.rc=0;
	if(pt.x<wxl)
		pt.rc=pt.rc|LEFT;// a|b�ǰ�λ��
	else if(pt.x>wxr)
		pt.rc=pt.rc|RIGHT;
	if(pt.y<wyb)
		pt.rc=pt.rc|BOTTOM;
	else if(pt.y>wyt)
		pt.rc=pt.rc|TOP;
}
void CCutView::Cohen()//Cohen-Sutherland�㷨
{
	CP2 p;//��������
	EnCode(P[0]);//������
	EnCode(P[1]);//�յ����
	while(P[0].rc!=0 || P[1].rc!=0)//��������һ�������ڴ���֮������
	{
		if((P[0].rc & P[1].rc)!=0)//����֮
		{
			PtCount=0;
			return;
		}
		if(0==P[0].rc)//ȷ��P[0]λ�ڴ���֮��
		{
			CP2 Temp;
			Temp=P[0];
			P[0]=P[1];
			P[1]=Temp;
		}
		UINT RC=P[0].rc;
		double k=(P[1].y-P[0].y)/(P[1].x-P[0].x);//ֱ�߶ε�б��
		//���ڱ߽簴���ҡ��¡��ϵ�˳��ü�ֱ�߶�
		if(RC & LEFT)//P[0]��λ�ڴ��ڵ����1
		{
			p.x=wxl;//���㽻��y����
			p.y=k*(p.x-P[0].x)+P[0].y;
		}
		else if(RC & RIGHT)//P[0]��λ�ڴ��ڵ��Ҳ�
		{
			p.x=wxr;//���㽻��y����
			p.y=k*(p.x-P[0].x)+P[0].y;
		}
		else if(RC & BOTTOM)//P[0]��λ�ڴ��ڵ��²�
		{
			p.y=wyb;//���㽻��x����
			p.x=(p.y-P[0].y)/k+P[0].x;
		}			
		else if(RC & TOP)//P[0]��λ�ڴ��ڵ��ϲ�
		{
			p.y=wyt;//���㽻��x����
			p.x=(p.y-P[0].y)/k+P[0].x;
		}
		EnCode(p);
		P[0]=p;
	}
}
void CCutView::DrawWindowRect(CDC *pDC)
{
	pDC->SetTextColor(RGB(255,0,0));
	pDC->TextOut(wxl+10,wyt+20,CString("����"));
	CPen NewPen,*pOldPen;//����3�����ؿ�ȵĻ���
	NewPen.CreatePen(PS_SOLID,3,RGB(0,255,0));
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->Rectangle(wxl,wyb,wxr,wyt);
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}
CP2 CCutView::Convert(CPoint point)//�豸����ϵ���Զ�������ϵת��
{
	CRect rect;
	GetClientRect(&rect);
	CP2 ptemp;
	ptemp.x=point.x-rect.Width()/2;
	ptemp.y=rect.Height()/2-point.y;
	return ptemp;
}
void CCutView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(bDrawLine)
	{	if(PtCount<2)
		{
			P[PtCount]=Convert(point);
			PtCount++;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CCutView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	if(bDrawLine)
	{	if(PtCount<2)
		{
			P[PtCount]=Convert(point);
			Invalidate(FALSE);
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CCutView::OnClip() 
{
	// TODO: �ڴ���������������
	Cohen();
	bDrawLine=FALSE;
	Invalidate(FALSE);
}


BOOL CCutView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;//���Ӧ�ó�����Ӧ����WM_ERASEBKGND��Ϣ������������Ӧ���ط���ֵ ������Windowsû�б�Ҫ�ٲ���
	//�����ڱ������뱻����ʱ �����磬���ڵ��ƶ������ڵĴ�С�ĸı䣩�ŷ��͡�
    //�����ڵ�һ������Ч��Ҫ�ػ�ʱ���ʹ���Ϣ��
	//return CView::OnEraseBkgnd(pDC);
}
