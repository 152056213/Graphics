
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
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(IDM_DRAWPIC, &CTestView::OnDrawpic)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDM_PLAY, &CTestView::OnPlay)
	ON_UPDATE_COMMAND_UI(IDM_PLAY, &CTestView::OnUpdatePlay)
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO: �ڴ˴���ӹ������
	bPlay=FALSE;
	R=1000.0,d=800.0,Phi=90.0,Theta=0.0;//�ӵ�λ����ǰ��
	Near=200.0,Far=1200.0;//����������Զ������		
	Alpha=0.0,Beta=0.0;//��ת��
	LightNum=1;//��Դ����
	r=250;//Բ������뾶
	h=800;//Բ���ĸ�
	nWidth=Round(2*PI*r);//Ŀ��ͼ��Ŀ��
	nHeight=Round(h);//Ŀ��ͼ��ĸ߶�
	pLight=new CLighting(LightNum);//һά��Դ��̬����
    pLight->Light[0].SetPosition(0,0,800);//���ù�Դλ������
	for(int i=0;i<LightNum;i++)
	{
		pLight->Light[i].L_Diffuse=CRGB(0.7,0.7,0.7); //��Դ����������ɫ	
		pLight->Light[i].L_Specular=CRGB(0.5,0.5,0.5);//��Դ����߹���ɫ
		pLight->Light[i].L_C0=1.0;//����˥��ϵ��
		pLight->Light[i].L_C1=0.0000001;//����˥��ϵ��
		pLight->Light[i].L_C2=0.00000001;//����˥��ϵ��
		pLight->Light[i].L_OnOff=TRUE;//��Դ����	
	}
	pMaterial=new CMaterial;//һά���ʶ�̬����
	pMaterial->SetAmbient(CRGB(0.247,0.200,0.075));//���ʶԻ������ķ�����
	pMaterial->SetDiffuse(CRGB(0.752,0.606,0.226));//���ʶ��������ķ�����
	pMaterial->SetSpecular(CRGB(1.0,1.0,1.0));//���ʶԾ��淴���ķ�����
	pMaterial->SetEmit(CRGB(0.05,0.05,0.002));//��������ɢ����ɫ
	pMaterial->M_n=10.0;//�߹�ָ��




	NumObject = 4;
	P = new CP3*[NumObject];
	for (int i = 0; i < NumObject; i++)
	{
		P[i] = new CP3 [4];
	}
	double a = 1.3;
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

CTestView::~CTestView()
{
	if(pLight!=NULL)
	{
		delete pLight;
		pLight=NULL;
	}
	if(pMaterial!=NULL)
	{
		delete pMaterial;
		pMaterial=NULL;
	}
	 if (P!=NULL)
	{
		for (int i = 0; i < NumObject; i++)
		{
			delete []P[i];
		}
		delete []P;
	}
	for(int n=0;n<bmp.bmHeight;n++)
	{
		delete []Image[n];
		Image[n]=NULL;	
	}
	delete []Image;
	Image=NULL;
	for(int n=0;n<nHeight;n++)
	{
		delete []N[n];
		N[n]=NULL;
		delete []LImage[n];
		LImage[n]=NULL;
	}
	delete []N;
	N=NULL;
	delete []LImage;
	LImage=NULL;
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
}


// CTestView ��ӡ

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
	ViewPoint.x=R*k[6];
	ViewPoint.y=R*k[4];
	ViewPoint.z=R*k[5];
}

void CTestView::PerProject(CP3 P)//͸�ӱ任
{
	CP3 ViewP;
	ViewP.x=P.x*k[3]-P.z*k[1];//�۲�����ϵ��ά����
	ViewP.y=-P.x*k[8]+P.y*k[2]-P.z*k[7];
	ViewP.z=-P.x*k[6]-P.y*k[4]-P.z*k[5]+R;
	ViewP.c=P.c;
    ScreenP.x=d*ViewP.x/ViewP.z;//��Ļ����ϵ��ά����
	ScreenP.y=Round(d*ViewP.y/ViewP.z);
	ScreenP.z=Far*(1-Near/ViewP.z)/(Far-Near);
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
	//memDC.FillSolidRect(rect,pDC->GetBkColor());//��ԭ���������ͻ����������Ǻ�ɫ
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

void CTestView::DrawObject(CDC* pDC)//����������
{

	DrawBezier.DrawObject(pDC,N,nWidth,nHeight);
}

void CTestView::ReadNormal()//���뷨����
{
	CBitmap NewBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP6);//����DDBλͼ
	NewBitmap.GetBitmap(&bmp);//��CBitmap����Ϣ���浽Bitmap�ṹ����
	int nbytesize=bmp.bmWidthBytes*bmp.bmHeight;
	im=new BYTE[nbytesize];
	NewBitmap.GetBitmapBits(nbytesize,(LPVOID)im);
	Image=new COLORREF*[bmp.bmHeight];
	for(int n1=0;n1<bmp.bmHeight;n1++)
		Image[n1]=new COLORREF[bmp.bmWidth];
	for(int n1=0;n1<bmp.bmHeight;n1++)
	{
		for(int n2=0;n2<bmp.bmWidth;n2++)
		{
			int pos=n1*bmp.bmWidthBytes+4*n2;//��ɫ����λ��
			n1=bmp.bmHeight-1-n1;//λͼ�����½������Ͻǻ���
			Image[n1][n2]=RGB(im[pos+2],im[pos+1],im[pos]);
		}
	}
	delete []im;
	LImage=new COLORREF*[nHeight];
	for(int n1=0;n1<nHeight;n1++)
		LImage[n1]=new COLORREF[nWidth];
	BiLinear_BMP(LImage,nWidth,nHeight,Image,bmp.bmWidth,bmp.bmHeight);
	COLORREF clr ;
	N=new CVector*[nHeight];
	for(int n=0;n<nHeight;n++)
		N[n]=new CVector[nWidth];
	for(int i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			clr = LImage[i][j];
			N[i][j] = CVector(GetRValue(clr),GetGValue(clr),GetBValue(clr));
			N[i][j].x = 2 * N[i][j].x - 255 ;
			N[i][j].y = 2 * N[i][j].y - 255 ;
			N[i][j].z = 2 * N[i][j].z - 255 ;
		}
	}
}

void CTestView::BiLinear_BMP(COLORREF **DesImage,int DesWidth,int DesHeight,COLORREF **SrcImage,int SrcWidth,int SrcHeight)//˫���Բ�ֵ
{	
	double WidScale=(double)SrcWidth/(double)DesWidth;//Դ/Ŀ��=����
	double HeiScale=(double)SrcHeight/(double)DesHeight;
	double pm[4];
	BYTE red[4],green[4],blue[4];
	for(int i=0;i<DesHeight;i++)
	{
		double Sy=i*HeiScale;
		int ty=int(Sy);
		double v=fabs(Sy-ty);
		for(int j=0;j<DesWidth;j++)
		{
			double Sx=j*WidScale;
			int tx=int(Sx);		
			double u=fabs(Sx-tx);
			pm[0]=(1-u)*(1-v);
			pm[1]=v*(1-u);
			pm[2]=u*(1-v);
			pm[3]=u*v;
			if(tx>=SrcWidth-2)
				tx=SrcWidth-2;
			if(ty>=SrcHeight-2)
				ty=SrcHeight-2;
			red[0]=GetRValue(SrcImage[ty][tx]);
			red[1]=GetRValue(SrcImage[ty+1][tx]);
			red[2]=GetRValue(SrcImage[ty][tx+1]);
			red[3]=GetRValue(SrcImage[ty+1][tx+1]);	
			green[0]=GetGValue(SrcImage[ty][tx]);
			green[1]=GetGValue(SrcImage[ty+1][tx]);
			green[2]=GetGValue(SrcImage[ty][tx+1]);
			green[3]=GetGValue(SrcImage[ty+1][tx+1]);
			blue[0]=GetBValue(SrcImage[ty][tx]);
			blue[1]=GetBValue(SrcImage[ty+1][tx]);
			blue[2]=GetBValue(SrcImage[ty][tx+1]);
			blue[3]=GetBValue(SrcImage[ty+1][tx+1]);
			double r=0,g=0,b=0;
			for(int m=0;m<4;m++)
			{
				r+=pm[m]*red[m];
				g+=pm[m]*green[m];
				b+=pm[m]*blue[m];
			}	
			DesImage[i][j]=RGB(r,g,b);
		} 
	}
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!bPlay)
	{
		switch(nChar)
	{
		int i;
	case VK_UP:
		Alpha = -5;
		for (i = 0; i < NumObject ;i ++)
		{
			tran.SetMat(DrawBezier.Vertex[i],64);
			tran.RotateX(Alpha);
		}
		
		break;
	case VK_DOWN:
		Alpha = 5;
		for (i = 0; i < NumObject ;i ++)
		{
			tran.SetMat(DrawBezier.Vertex[i],64);
			tran.RotateX(Alpha);
		}	
		break;
	case VK_LEFT:
		Beta = -5;
		for (i = 0; i < NumObject ;i ++)
		{
            tran.SetMat(DrawBezier.Vertex[i],64);
			tran.RotateY(Beta);
		}
		break;
	case VK_RIGHT:
		Beta = 5;
		for (i = 0; i < NumObject ;i ++)
		{
			tran.SetMat(DrawBezier.Vertex[i],64);
			tran.RotateY(Beta);
		}
		break;
	default:
		break;			
	}
	Invalidate(FALSE);			
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Alpha=5;Beta=5;
	tran.RotateX(Alpha);
	tran.RotateY(Beta);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
		//ReadVertex();
	//ReadFace();
	ReadNormal();
	//tran.SetMat(V,8);	
	InitParameter();
}


void CTestView::OnPlay()
{
	// TODO: �ڴ���������������
	bPlay=bPlay?FALSE:TRUE;
	if(bPlay)//���ö�ʱ��
		SetTimer(1,150,NULL);	
	else
		KillTimer(1);
}


void CTestView::OnUpdatePlay(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(bPlay)
	{
		pCmdUI->SetCheck(TRUE);
		pCmdUI->SetText(CString("ֹͣ"));
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->SetText(CString("����"));
	}	
}
