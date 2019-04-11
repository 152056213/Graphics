
// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���
#define SNOW_NUMBER 200  //ѩ�����ӵ�����
//��ʱ���������ú�Ƚ����
#define TIMER_PAINT 1
#define TIMER_HEROMOVE 2
//�ĸ�����
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3
//���ڴ�С
#define WINDOW_WIDTH 1916
#define WINDOW_HEIGHT 964

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_GRAPH_DRAW, &CTestView::OnGraphDraw)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DRAW, &CTestView::OnUpdateGraphDraw)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_APP_Play, &CTestView::OnAppPlay)
	ON_COMMAND(ID_MUSIC_PLAY, &CTestView::OnMusicPlay)
END_MESSAGE_MAP()

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	bPlay = TRUE;
	bFlag = TRUE;
}

CTestView::~CTestView()
{
	mciSendString("stop bgMusic ",NULL,0,NULL);
	delete m_snow;
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestView drawing

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CTestView printing


void CTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView message handlers


void CTestView::OnGraphDraw()
{
	// TODO: Add your command handler code here
}


void CTestView::OnUpdateGraphDraw(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

//�����ͼ���x��ʼλ��
void CTestView::GetMapStartX()
{
	//������ﲻ������ߺ����ұ߰����Ļ��ʱ����ͼ����ʼ��������Ҫ��������λ�ü���ġ�
	if(MyHero.x<m_mapWidth-WINDOW_WIDTH/2 && MyHero.x>WINDOW_WIDTH/2)
		m_xMapStart=MyHero.x-WINDOW_WIDTH/2;
}
//��ȡ��������Ļ�ϵ�����
int GetScreenX(int xHero,int mapWidth)
{
	//�������������ߺ����ұ߰����Ļ��ʱ����ô����ʹ�����Ļ�м�
	if(xHero<mapWidth-WINDOW_WIDTH/2 && xHero>WINDOW_WIDTH/2)
		return WINDOW_WIDTH/2;
	else if(xHero<=WINDOW_WIDTH/2)     //������߰����Ļʱ����������Ļ�ϵ�λ�þ����Լ���x������
		return xHero;
	else 
		return WINDOW_WIDTH-(mapWidth-xHero);  //�����ұ߰����Ļ
}

void CTestView::DrawObject()
{
	static double lastTime=timeGetTime();   //�����Ժ���Ƶ�ϵͳʱ�䡣��ʱ��Ϊ��ϵͳ����������������ʱ�䡣 
	static double currentTime=timeGetTime();
	//��ȡ����DCָ��
	CDC *cDC=this->GetDC();
	//��ȡ���ڴ�С
	GetClientRect(&rect);
	//��������DC
	memDC.CreateCompatibleDC(NULL);
	memBitmap.CreateCompatibleBitmap(cDC,rect.Width(),rect.Height());
	memDC.SelectObject(&memBitmap);
	//���㱳����ͼ��ʼλ��
	GetMapStartX();
	//������������������������������������������ʼ���ơ�������������������������������������������
	//������,������ͼ�������ڻ���DC��m_cache����
	m_bg.Draw(memDC,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,m_xMapStart,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	//��Ӣ��
	MyHero.hero.Draw(memDC,GetScreenX(MyHero.x,m_mapWidth),MyHero.y,120,120,MyHero.frame*80,MyHero.direct*80,80,80);
	//����ѩ������
	m_snow->Draw(memDC);
	//����ѩ��
	currentTime=timeGetTime();
	m_snow->Update(currentTime-lastTime);
	lastTime=currentTime;
	//��󽫻���DC�������������DC��
	cDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	//�������������������������������������������ƽ���������������������������������������������
	
	//�ڻ�����ͼ��,ʹ��������Ч
	ValidateRect(&rect);
	//�ͷŻ���DC
	memDC.DeleteDC();
	//�ͷŶ���
	memBitmap.DeleteObject();
	//�ͷŴ���DC
	ReleaseDC(cDC);
}

void CTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	//���ر���
	m_bg.Load("bigbg.png");
	//��ȡ������ͼ�Ŀ��
	m_mapWidth=m_bg.GetWidth();
	//����ѩ��ͼ��
	m_snow=new CParticle(SNOW_NUMBER,WINDOW_WIDTH,WINDOW_HEIGHT);
	//��ʼ��ѩ������
	m_snow->Init();
	//����Ӣ��ͼƬ
	MyHero.hero.Load("heroMove.png");
	m_snow->TransparentPNG(&MyHero.hero);
	//��ʼ��Ӣ��״̬
	MyHero.direct=UP;
	MyHero.frame=0;
	//����Ӣ�۳�ʼλ��
	MyHero.x=80;    
	MyHero.y=700;
	//���õ�ͼ��ʼ������˿�ʼ��ʾ
	m_xMapStart=0;
	//�������ļ�
	mciSendString("open BackMusic�����ѩ.mp3 alias bgMusic ", NULL, 0, NULL);
	mciSendString("play bgMusic repeat", NULL, 0, NULL);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case TIMER_PAINT:DrawObject();//�����ػ涨ʱ������ִ��OnPaint����
		break;  
	case TIMER_HEROMOVE:               //���������ƶ��Ķ�ʱ��
		{
			MyHero.frame++;              //ÿ�ε��˼��ʱ��ͽ�ͼƬ��Ϊ��һ֡
			if(MyHero.frame==4)          //�����������ͷ��ʼ
				MyHero.frame=0;
		}
		break;
	}

	CView::OnTimer(nIDEvent);
}

int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//����һ��10�������һ����Ϣ�Ķ�ʱ��
	SetTimer(TIMER_PAINT,10,NULL);
	//�����������߶�����ʱ��
	SetTimer(TIMER_HEROMOVE,100,NULL);
	return 0;
}


void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	//nChar��ʾ���µļ�ֵ
	switch(nChar)
	{
	case 'd':         //��Ϸ�а��µļ���ȻӦ�ò����ִ�Сд��
	case 'D':
	case VK_RIGHT:
		MyHero.direct=RIGHT;
		MyHero.x+=5;
		break;
	case 'a':
	case 'A':
	case VK_LEFT:
		MyHero.direct=LEFT;
		MyHero.x-=5;
		break;
	case 'w':
	case 'W':
	case VK_UP:
		MyHero.direct=UP;
		MyHero.y-=5;
		break;
	case 's':
	case 'S':
	case VK_DOWN:
		MyHero.direct=DOWN;
		MyHero.y+=5;
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTestView::OnAppPlay()
{
	// TODO: Add your command handler code here
	bFlag = !bFlag;
	if(bFlag)//���ö�ʱ��
		SetTimer(TIMER_PAINT, 10, NULL);	
	else
		KillTimer(TIMER_PAINT);
}


void CTestView::OnMusicPlay()
{
	// TODO: Add your command handler code here
	bPlay = !bPlay;
	if(bPlay)//���ö�ʱ��
	{	
		//�������ļ�
		mciSendString("open BackMusic�����ѩ.mp3 alias bgMusic ", NULL, 0, NULL);
		mciSendString("play bgMusic repeat", NULL, 0, NULL);	
	}
	else
		mciSendString("stop bgMusic ",NULL,0,NULL);
}
