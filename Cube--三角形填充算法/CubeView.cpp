
// CubeView.cpp : CCubeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Cube.h"
#endif

#include "CubeDoc.h"
#include "CubeView.h"
#include "math.h"
#define PI 3.1415926

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCubeView

IMPLEMENT_DYNCREATE(CCubeView, CView)

BEGIN_MESSAGE_MAP(CCubeView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCubeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
//	ON_COMMAND(ID_32772, &CCubeView::On32772)
END_MESSAGE_MAP()

// CCubeView ����/����

CCubeView::CCubeView()
{
	// TODO: �ڴ˴���ӹ������
	R=1000.0;d=900.0;Alpha=0.0;Beta=0.0;
}

CCubeView::~CCubeView()
{
}

BOOL CCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCubeView ����

void CCubeView::OnDraw(CDC* pDC)
{
	CCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CRect rect;//����ͻ�������
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(),-rect.Height());//����������Χ,x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//�ͻ�������Ϊԭ��
	CDC memDC;//�ڴ�DC
	memDC.CreateCompatibleDC(pDC);//����һ������ʾpDC���ݵ��ڴ�memDC
	CBitmap NewBitmap,*pOldBitmap;//�ڴ��г��ص���ʱλͼ 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//��������λͼ 
	pOldBitmap=memDC.SelectObject(&NewBitmap);//������λͼѡ��memDC 
	memDC.FillSolidRect(rect,pDC->GetBkColor());//��ԭ���������ͻ����������Ǻ�ɫ
	memDC.SetMapMode(MM_ANISOTROPIC);//memDC�Զ�������ϵ
	memDC.SetWindowExt(rect.Width(),rect.Height());
	memDC.SetViewportExt(rect.Width(),-rect.Height());
	memDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	DrawObject(&memDC);//��memDC����ͼ��
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//���ڴ�memDC�е�λͼ��������ʾpDC��
	memDC.SelectObject(pOldBitmap);//�ָ�λͼ
	NewBitmap.DeleteObject();//ɾ��λͼ 
}


// CCubeView ��ӡ


void CCubeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CCubeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCubeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCubeView ���

#ifdef _DEBUG
void CCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCubeDoc* CCubeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCubeDoc)));
	return (CCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CCubeView ��Ϣ�������
void CCubeView::ReadPoint()
{
	double a = 150;
	P[0].x=-a;P[0].y=-a;P[0].z=-a;P[0].c=CRGB(0.0,0.0,0.0);//��ɫ
	P[1].x=+a;P[1].y=-a;P[1].z=-a;P[1].c=CRGB(1.0,0.0,0.0);//��ɫ
	P[2].x=+a;P[2].y=+a;P[2].z=-a;P[2].c=CRGB(1.0,1.0,0.0);//��ɫ
	P[3].x=-a;P[3].y=+a;P[3].z=-a;P[3].c=CRGB(0.0,1.0,0.0);//��ɫ
	P[4].x=-a;P[4].y=-a;P[4].z=+a;P[4].c=CRGB(0.0,0.0,1.0);//��ɫ
	P[5].x=+a;P[5].y=-a;P[5].z=+a;P[5].c=CRGB(1.0,0.0,1.0);//Ʒ��
	P[6].x=+a;P[6].y=+a;P[6].z=+a;P[6].c=CRGB(1.0,1.0,1.0);//��ɫ
	P[7].x=-a;P[7].y=+a;P[7].z=+a;P[7].c=CRGB(0.0,1.0,1.0);//��ɫ
}
void CCubeView::ReadFace()
{
	//��Ķ�����������
	F[0].pIndex[0]=4;F[0].pIndex[1]=5;F[0].pIndex[2]=6;F[0].pIndex[3]=7;
	F[1].pIndex[0]=0;F[1].pIndex[1]=3;F[1].pIndex[2]=2;F[1].pIndex[3]=1;
	F[2].pIndex[0]=0;F[2].pIndex[1]=4;F[2].pIndex[2]=7;F[2].pIndex[3]=3;
	F[3].pIndex[0]=1;F[3].pIndex[1]=2;F[3].pIndex[2]=6;F[3].pIndex[3]=5;
	F[4].pIndex[0]=2;F[4].pIndex[1]=3;F[4].pIndex[2]=7;F[4].pIndex[3]=6;
	F[5].pIndex[0]=0;F[5].pIndex[1]=1;F[5].pIndex[2]=5;F[5].pIndex[3]=4;
}
void CCubeView::InitParameter()//͸�ӱ任������ʼ��
{
	k[1]=sin(PI*Beta/180);
	k[2]=sin(PI*Alpha/180);
	k[3]=cos(PI*Beta/180);
	k[4]=cos(PI*Alpha/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];
	ViewPoint.x=R*k[6];
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}
void CCubeView::PerProject(CP3 P)//͸�ӱ任
{
	CP3 ViewP;
	ViewP.x=P.x*k[3]-P.z*k[1];//�۲�����ϵ��ά����
	ViewP.y=-P.x*k[8]+P.y*k[2]-P.z*k[7];
	ViewP.z=-P.x*k[6]-P.y*k[4]-P.z*k[5]+R;
    ViewP.c=P.c;
    ScreenP.x=d*ViewP.x/ViewP.z;//��Ļ����ϵ��ά����
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.c=ViewP.c;
}
void CCubeView::DrawObject(CDC *pDC)
{
	CPoint Screen[4];
	CP2 l;
	for(int nFacet = 0; nFacet<6; nFacet++)
	{
		CVector ViewVector(P[F[nFacet].pIndex[0]],ViewPoint);//�����ʸ��
		ViewVector=ViewVector.Normalize();//��ʸ����λ��
		F[nFacet].SetFaceNormal(P[F[nFacet].pIndex[0]],P[F[nFacet].pIndex[1]],P[F[nFacet].pIndex[2]]);
		F[nFacet].fNormal.Normalize();//��ĵ�λ����ʸ��
		if(Dot(ViewVector,F[nFacet].fNormal)>=0)//�����޳�
		{
			for(int nPoint=0;nPoint<4;nPoint++)//����ѭ��
		{
			PerProject(P[F[nFacet].pIndex[nPoint]]);//͸��ͶӰ
			if(0==nPoint)
			{
				pDC->MoveTo(ScreenP.x,ScreenP.y);
				l=ScreenP;
			}
			else
				pDC->LineTo(ScreenP.x,ScreenP.y);
		}
			pDC->LineTo(l.x,l.y);;//�պ϶����
		}
	}
}
void CCubeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nChar)
	{
	case VK_UP:
		Alpha += 5;
		//tran.RotateX(Alpha);
		break;
	case VK_DOWN:
		Alpha -= 5;
		//tran.RotateX(Alpha);
		break;
	case VK_LEFT:
		Beta += 5;
		//tran.RotateY(Beta);
		break;
	case VK_RIGHT:
		Beta -= 5;
		//tran.RotateY(Beta);
		break;
	default:
		break;
	}
	InitParameter();
	Invalidate(FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CCubeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	ReadPoint();
	ReadFace();
	//tran.SetMatrix(P,8);
	InitParameter();
}
