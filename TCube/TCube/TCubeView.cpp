
// TCubeView.cpp : CTCubeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TCube.h"
#endif

#include "TCubeDoc.h"
#include "TCubeView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTCubeView

IMPLEMENT_DYNCREATE(CTCubeView, CView)

BEGIN_MESSAGE_MAP(CTCubeView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTCubeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TFRONT, &CTCubeView::OnTfront)
	ON_COMMAND(ID_TBACK, &CTCubeView::OnTback)
	ON_COMMAND(ID_TBIG, &CTCubeView::OnTbig)
	ON_COMMAND(ID_TSMALL, &CTCubeView::OnTsmall)
	ON_COMMAND(ID_RXAXIS, &CTCubeView::OnRxaxis)
	ON_COMMAND(ID_RYAXIS, &CTCubeView::OnRyaxis)
	ON_COMMAND(ID_RZAXIS, &CTCubeView::OnRzaxis)
	ON_COMMAND(ID_RXOY, &CTCubeView::OnRxoy)
	ON_COMMAND(ID_RYOZ, &CTCubeView::OnRyoz)
	ON_COMMAND(ID_RXOZ, &CTCubeView::OnRxoz)
	ON_COMMAND(ID_SXDIRECTIONPLUS, &CTCubeView::OnSxdirectionplus)
	ON_COMMAND(ID_SYDIRECTIONPLUS, &CTCubeView::OnSydirectionplus)
	ON_COMMAND(ID_SZDIRECTIONNEG, &CTCubeView::OnSzdirectionneg)
	ON_COMMAND(IDM_DRAWPIC, &CTCubeView::OnDrawpic)
	ON_COMMAND(ID_RESET, &CTCubeView::OnReset)
	ON_COMMAND(ID_AAA, &CTCubeView::OnAaa)
	ON_COMMAND(ID_BBB, &CTCubeView::OnBbb)
	ON_COMMAND(ID_CCC, &CTCubeView::OnCcc)
	ON_COMMAND(ID_DDD, &CTCubeView::OnDdd)
END_MESSAGE_MAP()

// CTCubeView ����/����

CTCubeView::CTCubeView()
{
	// TODO: �ڴ˴���ӹ������

}

CTCubeView::~CTCubeView()
{
}

BOOL CTCubeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTCubeView ����

void CTCubeView::OnDraw(CDC* pDC)
{
	CTCubeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//CRect rect;//����ͻ�������
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
	DrawObject(&memDC);//��memDC����ͼ��
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//���ڴ�memDC�е�λͼ��������ʾpDC��
	memDC.SelectObject(pOldBitmap);//�ָ�λͼ
	NewBitmap.DeleteObject();//ɾ��λͼ
}


// CTCubeView ��ӡ


void CTCubeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTCubeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTCubeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTCubeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CTCubeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

//void CTCubeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
//{
//#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
//#endif
//}


// CTCubeView ���

#ifdef _DEBUG
void CTCubeView::AssertValid() const
{
	CView::AssertValid();
}

void CTCubeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTCubeDoc* CTCubeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTCubeDoc)));
	return (CTCubeDoc*)m_pDocument;
}
#endif //_DEBUG


// CTCubeView ��Ϣ�������
void CTCubeView::ReadPoint()//���
{
	double a=150;//������߳�Ϊa
	//�������ά����(x,y,z)
	P[0].x=0;P[0].y=0;P[0].z=0;
	P[1].x=a;P[1].y=0;P[1].z=0;
	P[2].x=a;P[2].y=a;P[2].z=0;
	P[3].x=0;P[3].y=a;P[3].z=0;
	P[4].x=0;P[4].y=0;P[4].z=a;
	P[5].x=a;P[5].y=0;P[5].z=a;
	P[6].x=a;P[6].y=a;P[6].z=a;
	P[7].x=0;P[7].y=a;P[7].z=a;
}
void CTCubeView::ReadFace()//���
{
	//��ı�������Ķ�����
	F[0].SetNum(4);F[0].vI[0]=4;F[0].vI[1]=5;F[0].vI[2]=6;F[0].vI[3]=7;//ǰ��
	F[1].SetNum(4);F[1].vI[0]=0;F[1].vI[1]=3;F[1].vI[2]=2;F[1].vI[3]=1;//����
	F[2].SetNum(4);F[2].vI[0]=0;F[2].vI[1]=4;F[2].vI[2]=7;F[2].vI[3]=3;//����
	F[3].SetNum(4);F[3].vI[0]=1;F[3].vI[1]=2;F[3].vI[2]=6;F[3].vI[3]=5;//����
	F[4].SetNum(4);F[4].vI[0]=2;F[4].vI[1]=3;F[4].vI[2]=7;F[4].vI[3]=6;//����
	F[5].SetNum(4);F[5].vI[0]=0;F[5].vI[1]=1;F[5].vI[2]=5;F[5].vI[3]=4;//����
}
void CTCubeView::ObliqueProject(CP3 p)//б�Ȳ�任
{
	ScreenP.x=p.x-p.z/(2*sqrt(2.0));
	ScreenP.y=p.y-p.z/(2*sqrt(2.0));	
}
void CTCubeView::DrawObject(CDC *pDC)//����ͼ��
{
	pDC->MoveTo(0,0);//����x��
	pDC->LineTo(rect.Width()/2,0);
	pDC->TextOut(rect.Width()/2-20,-20,CString("x"));
	pDC->MoveTo(0,0);//����y��
	pDC->LineTo(0,rect.Height()/2);
	pDC->TextOut(-20,rect.Height()/2-20,CString("y"));
	pDC->MoveTo(0,0);//����z��
	pDC->LineTo(-rect.Width()/2,-rect.Width()/2);
	pDC->TextOut(-rect.Height()/2-20,-rect.Height()/2+20,CString("z"));
	pDC->TextOut(10,-10,CString("O"));
	DrawPolygon(pDC);
}
void CTCubeView::DrawPolygon(CDC *pDC)//�����������߿�ģ��
{
	for(int nFace=0;nFace<6;nFace++)
	{
		CP2 t;
		CPoint a[4];
		for(int nVertex=0;nVertex<F[nFace].vN;nVertex++)//����ѭ��
		{
			ObliqueProject(P[F[nFace].vI[nVertex]]);//б�Ȳ�ͶӰ
			//a[nVertex].x = P[F[nFace].vI[nVertex]].x;
			//a[nVertex].y = P[F[nFace].vI[nVertex]].y;
			if(0==nVertex)
			{
				pDC->MoveTo(ScreenP.x,ScreenP.y);
				t=ScreenP;
				//pDC->MoveTo(a[nVertex].x,a[nVertex].y);
			}
			else
				pDC->LineTo(ScreenP.x,ScreenP.y);
				//pDC->LineTo(a[nVertex].x,a[nVertex].y);
		}
		pDC->LineTo(t.x,t.y);//�պ϶����
		//pDC->LineTo(a[0].x,a[0].y);//�պ϶����
	}
}

void CTCubeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	ReadPoint();
	ReadFace();
	trans.SetMat(P,8);
}
void CTCubeView::OnAaa()
{
	// TODO: �ڴ���������������t
	trans.Translate(-10,0,0);
	Invalidate(FALSE);
}


void CTCubeView::OnBbb()
{
	// TODO: �ڴ���������������
	trans.Translate(10,0,0);
	Invalidate(FALSE);
}


void CTCubeView::OnCcc()
{
	// TODO: �ڴ���������������
	trans.Translate(0,10,0);
	Invalidate(FALSE);
}


void CTCubeView::OnDdd()
{
	// TODO: �ڴ���������������
	trans.Translate(0,-10,0);
	Invalidate(FALSE);
}
void CTCubeView::OnTfront()
{
	// TODO: �ڴ���������������
	trans.Translate(0,0,10);
	Invalidate(FALSE);
}


void CTCubeView::OnTback()
{
	// TODO: �ڴ���������������
	trans.Translate(0,0,-10);
	Invalidate(FALSE);	
}


void CTCubeView::OnTbig()
{
	// TODO: �ڴ���������������
	trans.Scale(2,2,2);
	Invalidate(FALSE);
}


void CTCubeView::OnTsmall()
{
	// TODO: �ڴ���������������
	trans.Scale(0.5,0.5,0.5);
	Invalidate(FALSE);	
}


void CTCubeView::OnRxaxis()
{
	// TODO: �ڴ���������������
	trans.RotateX(30,P[0]);
	Invalidate(FALSE);
}


void CTCubeView::OnRyaxis()
{
	// TODO: �ڴ���������������
	trans.RotateY(30,P[0]);
	Invalidate(FALSE);
}


void CTCubeView::OnRzaxis()
{
	// TODO: �ڴ���������������
	trans.RotateZ(30,P[0]);
	Invalidate(FALSE);
}


void CTCubeView::OnRxoy()
{
	// TODO: �ڴ���������������
	trans.ReflectXOY();
	Invalidate(FALSE);
}


void CTCubeView::OnRyoz()
{
	// TODO: �ڴ���������������
	trans.ReflectYOZ();
	Invalidate(FALSE);
}


void CTCubeView::OnRxoz()
{
	// TODO: �ڴ���������������
	trans.ReflectZOX();
	Invalidate(FALSE);
}


void CTCubeView::OnSxdirectionplus()
{
	// TODO: �ڴ���������������
	trans.ShearX(1,1);
	Invalidate(FALSE);
}


void CTCubeView::OnSydirectionplus()
{
	// TODO: �ڴ���������������
	trans.ShearY(1,1);
	Invalidate(FALSE);	
}


void CTCubeView::OnSzdirectionneg()
{
	// TODO: �ڴ���������������
	trans.ShearZ(1,1);
	Invalidate(FALSE);
}


void CTCubeView::OnDrawpic()
{
	// TODO: �ڴ���������������
	MessageBox(CString("��ʹ��ͼ�갴ť������ά���α任"),CString("��ʾ"),MB_OK);
}


void CTCubeView::OnReset()
{
	// TODO: �ڴ���������������
	ReadPoint();
	Invalidate(FALSE);
}

