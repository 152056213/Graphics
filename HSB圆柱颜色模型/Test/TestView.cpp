
// TestView.cpp : CTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//������ѧͷ�ļ�
#define  PI 3.1415926//PI�ĺ궨��
#define Round(d) int(floor(d+0.5))//��������궨��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO: �ڴ˴���ӹ������
	R=800.0;d=1000;Phi=90;Theta=0;
	Alpha=0.0;Beta=0.0;
	V=NULL;F=NULL;
}

CTestView::~CTestView()
{
	if(V!=NULL)
	{
		delete[] V;
		V=NULL;
	}
	for(int n=0;n<N2+2;n++)//ע�⳷������,���к���,�������෴
	{
		delete[] F[n];
		F[n]=NULL;
	}
	delete[] F;
	F=NULL;
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTestView ����

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	DoubleBuffer(pDC);
	//����ʱ�亯��
	SetTimer(1,1,NULL);//��һ��������ID�š��ڶ�����ʱ���������룩�����������ص�������
}


// CTestView ��ӡ


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

// CTestView ���

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView ��Ϣ�������
void CTestView::ReadVertex()//���
{
	r=100;//Բ������뾶
	h=300;//Բ���ĸ�
	int cTheta=10;//����н�
	int cNum=300;//������
	double red,green,blue;
	N1=360/cTheta;//N1����������
	N2=Round(h/cNum);//N2Ϊ����������
	V=new CP3[N1*(N2+1)+2];
	double cTheta1,cNum1;
	V[0].x=0.0;V[0].y=-150.0;V[0].z=0.0;//��������
	V[0].c=CRGB(0.0,0.0,0.0);
	V[N1*(N2+1)+1].x=0;V[N1*(N2+1)+1].y=h-150;V[N1*(N2+1)+1].z=0;//��������	
	V[N1*(N2+1)+1].c = CRGB(1.0,1.0,1.0);
	for(int i=0;i<N2+1;i++)//����
	{	
		cNum1=i*cNum;
		for(int j=0;j<N1;j++)//����
		{
			cTheta1=j*cTheta*PI/180;
			V[i*N1+j+1].x=r*cos(cTheta1);
			V[i*N1+j+1].y=cNum1-150;	
			V[i*N1+j+1].z=r*sin(cTheta1);			
		}
	}
	for(int j=0;j<N1;j++)//��һȦ
		{
			V[j+1].c = CRGB(0.0,0.0,0.0);
		}
	
		for(int j=0;j<N1;j++)//���һȦ
			{
				cTheta1=j*cTheta;
				if(0<=cTheta1 && cTheta1<60)
				{
					red = 1.0;
					green = 0.0 + cTheta1*(1.0/60);
					blue = 0.0;
				}
				if(60<=cTheta1 && cTheta1<120)
				{
					red = 1.0 - (cTheta1-60)*(1.0/60);
					green = 1.0;
					blue = 0.0;
				}
				if(120<=cTheta1 && cTheta1<180)
				{
					red = 0.0;
					green = 1.0;
					blue = 0.0 + (cTheta1-60*2)*(1.0/60);
				}
				if(180<=cTheta1 && cTheta1<240)
				{
					red = 0.0;
					green = 1.0 - (cTheta1-60*3)*(1.0/60);
					blue = 1.0;
				}
				if(240<=cTheta1 && cTheta1<300)
				{
					red = 0.0 + (cTheta1-60*4)*(1.0/60);
					green = 0.0;
					blue = 1.0;
				}
				if(300<=cTheta1 && cTheta1<360)
				{
					red = 1.0;
					green = 0.0;
					blue = 1.0 - (cTheta1-60*5)*(1.0/60);
				}
				V[N1*N2+j+1].c = CRGB(red,green,blue);
			}

	CFill * fill;
	for(int i=1;i<N2;i++)//���� �м�Ȧ
	{	
		for(int j=0;j<N1;j++)//����
		{
			V[i*N1+j+1].c = fill->Interpolation(h,V[j+1].y,V[N1*N2+j+1].y,V[j+1].c,V[N1*N2+j+1].c);  
		}
	}
}

void CTestView::ReadFace()//���
{
	//���ö�ά��̬����
	F=new CFace *[N2+2];//����
	for(int n=0;n<N2+2;n++)
		F[n]=new CFace[N1];//����
	for(int j=0;j<N1;j++)//����ײ���������Ƭ
	{
		int tempj=j+1;
		if(tempj==N1) tempj=0;//��Ƭ����β����
		int BottomIndex[3];//�ײ���������Ƭ����������
		BottomIndex[0]=0;
		BottomIndex[1]=j+1;
		BottomIndex[2]=tempj+1;
		F[0][j].SetNum(3);
		for(int k=0;k<F[0][j].vN;k++)//��Ƭ�ж��������
			F[0][j].vI[k]=BottomIndex[k];
	}
	for(int i=1;i<=N2;i++)//����Բ�����ı�����Ƭ
	{
		for(int j=0;j<N1;j++)
	    {
			int tempi=i+1;
			int tempj=j+1;
			if(N1==tempj) tempj=0;
			int BodyIndex[4];//Բ�����ı�����Ƭ����������
			BodyIndex[0]=(i-1)*N1+j+1;
			BodyIndex[1]=(tempi-1)*N1+j+1;
			BodyIndex[2]=(tempi-1)*N1+tempj+1;
			BodyIndex[3]=(i-1)*N1+tempj+1;
			F[i][j].SetNum(4);
			for(int k=0;k<F[i][j].vN;k++)
				F[i][j].vI[k]=BodyIndex[k];
		}
	}
	for(int j=0;j<N1;j++)//���춥����������Ƭ
	{
		int tempj=j+1;
		if(tempj==N1) tempj=0;
		int TopIndex[3];//������������Ƭ����������
		TopIndex[0]=N1*(N2+1)+1;
		TopIndex[1]=N1*N2+tempj+1;
		TopIndex[2]=N1*N2+j+1;
		F[N2+1][j].SetNum(3);	
		for(int k=0;k<F[N2+1][j].vN;k++)
			F[N2+1][j].vI[k]=TopIndex[k];
	}
}

void CTestView::InitParameter()//͸�ӱ任������ʼ��
{	
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];
	ViewPoint.x=R*k[6];//�û�����ϵ���ӵ�������
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}

void CTestView::PerProject(CP3 P)//͸�ӱ任
{
	CP3 ViewP;
	ViewP.x=k[3]*P.x-k[1]*P.z;//�۲�����ϵ��ά����
	ViewP.y=-k[8]*P.x+k[2]*P.y-k[7]*P.z;
	ViewP.z=-k[6]*P.x-k[4]*P.y-k[5]*P.z+R;
	ViewP.c=P.c;
    ScreenP.x=d*ViewP.x/ViewP.z;//��Ļ����ϵ��ά����
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.c=ViewP.c;
}

void CTestView::DoubleBuffer(CDC *pDC)//˫����
{
	CRect rect;//����ͻ�������
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

void CTestView::DrawObject(CDC* pDC)//����Բ��������
{
    CPi2 Point3[3],t3;//��������涥������
	CPi2 Point4[4],t4;//���涥������
	for(int i=0;i<N2+2;i++)//N2+2
	{
		for(int j=0;j<N1;j++)
		{
			CVector ViewVector(V[F[i][j].vI[0]],ViewPoint);//���������
			ViewVector=ViewVector.Normalize();//��λ��������
			F[i][j].SetFaceNormal(V[F[i][j].vI[0]],V[F[i][j].vI[1]],V[F[i][j].vI[2]]);	
			F[i][j].fNormal.Normalize();//��λ����ʸ��
			if(Dot(ViewVector,F[i][j].fNormal)>=0)//�����޳�
			{
				if(3==F[i][j].vN)//��������Ƭ
				{
					for(int m=0;m<F[i][j].vN;m++)
					{
						PerProject(V[F[i][j].vI[m]]);
						Point3[m]=ScreenP;
					}			
					CFill *fill=new CFill;//��̬�����ڴ� 
					fill->SetPoint(Point3,3);//���ö���
					fill->CreateBucket();//����Ͱ��
					fill->CreateEdge();//�����߱�
					fill->Gouraud(pDC);//�����Ƭ
					delete fill;//�����ڴ�
				}
				else//�ı�����Ƭ
				{
					for(int m=0;m<F[i][j].vN;m++)
					{
						PerProject(V[F[i][j].vI[m]]);
						Point4[m]=ScreenP;						
					}
					CFill *fill=new CFill;//��̬�����ڴ� 
					fill->SetPoint(Point4,4);//���ö���
					fill->CreateBucket();//����Ͱ��
					fill->CreateEdge();//�����߱�
					fill->Gouraud(pDC);//�����Ƭ
					delete fill;//�����ڴ�
				}
			} 	
		}	
	}
}

void CTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	ReadVertex();
	ReadFace();
	tran.SetMat(V,N1*(N2+1)+2);
	InitParameter();
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		switch(nChar)
		{
		case VK_UP:
			Alpha=-5;
			tran.RotateX(Alpha);
			break;
		case VK_DOWN:
			Alpha=5;
			tran.RotateX(Alpha);
			break;
		case VK_LEFT:
			Beta=-5;
			tran.RotateY(Beta);
			break;
		case VK_RIGHT:
			Beta=5;
			tran.RotateY(Beta);
			break;
		default:
			break;			
		}
		Invalidate(FALSE);		
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	R=R+100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	R=R-100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnRButtonDown(nFlags, point);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Beta=5;
	Alpha=5;
	tran.RotateY(Beta);
	tran.RotateX(Alpha);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}
