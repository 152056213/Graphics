// LeftPortion.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "LeftPortion.h"
#include "TestDoc.h"//
#include "math.h"//


// CLeftPortion

IMPLEMENT_DYNCREATE(CLeftPortion, CFormView)

CLeftPortion::CLeftPortion()
	: CFormView(CLeftPortion::IDD)
{
	EnableAutomation();
}

CLeftPortion::~CLeftPortion()
{
}

void CLeftPortion::OnFinalRelease()
{
	// TODO: �ڴ����ר�ô����/����û���
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣
	CFormView::OnFinalRelease();
}

void CLeftPortion::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AMBIENT, m_Ambient);
	DDX_Check(pDX, IDC_DIFFUSE, m_Diffuse);  
	DDX_Check(pDX, IDC_SPECULAR, m_Specular);
}

BEGIN_MESSAGE_MAP(CLeftPortion, CFormView)
	ON_BN_CLICKED(IDC_AMBIENT, &CLeftPortion::OnBnClickedAmbient)
	ON_BN_CLICKED(IDC_DIFFUSE, &CLeftPortion::OnBnClickedDiffuse)
	ON_BN_CLICKED(IDC_SPECULAR, &CLeftPortion::OnBnClickedSpecular)
	ON_BN_CLICKED(IDC_GOLD, &CLeftPortion::OnBnClickedGold)
	ON_BN_CLICKED(IDC_RUBY, &CLeftPortion::OnBnClickedRuby)
	ON_BN_CLICKED(IDC_SILVER, &CLeftPortion::OnBnClickedSilver)
	ON_BN_CLICKED(IDC_BERYL, &CLeftPortion::OnBnClickedBeryl)
	ON_BN_CLICKED(IDC_LEFTTOP, &CLeftPortion::OnBnClickedLefttop)
	ON_BN_CLICKED(IDC_LEFTDOWN, &CLeftPortion::OnBnClickedLeftdown)
	ON_BN_CLICKED(IDC_RIGHTTOP, &CLeftPortion::OnBnClickedRighttop)
	ON_BN_CLICKED(IDC_RIGHTDOWN, &CLeftPortion::OnBnClickedRightdown)
END_MESSAGE_MAP()


// CLeftPortion ���

#ifdef _DEBUG
void CLeftPortion::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftPortion::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftPortion ��Ϣ�������

void CLeftPortion::OnBnClickedAmbient()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	//�ھ��ж����ͼ��ĳ����У�ϵͳ���ֱܷ��Ƿ�ǰ��ͼ���ĵ���ƥ�䣬�����ǿ��ת����
 	pDoc->UpdateAllViews(NULL,1); 
}

void CLeftPortion::OnBnClickedDiffuse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,2);
}

void CLeftPortion::OnBnClickedSpecular()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,3);
}

void CLeftPortion::OnBnClickedGold()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,4);
}

void CLeftPortion::OnBnClickedSilver()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,5);
}

void CLeftPortion::OnBnClickedRuby()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,6);
}

void CLeftPortion::OnBnClickedBeryl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,7);
}

void CLeftPortion::OnBnClickedLefttop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,8);
}

void CLeftPortion::OnBnClickedLeftdown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,9);
}

void CLeftPortion::OnBnClickedRighttop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,10);
}

void CLeftPortion::OnBnClickedRightdown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestDoc *pDoc=(CTestDoc*)CFormView::GetDocument();
	pDoc->UpdateAllViews(NULL,11);
}

void CLeftPortion::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//�����󴰸�ؼ��ĳ�ʼ״̬
	CheckRadioButton(IDC_GOLD,IDC_BERYL,IDC_RUBY);
	CheckRadioButton(IDC_LEFTTOP,IDC_RIGHTDOWN,IDC_RIGHTTOP);
	m_Ambient = TRUE;
	m_Diffuse = TRUE;
	m_Specular = TRUE;
	UpdateData(FALSE);
	//UpdateData(TRUE) == ���ؼ���ֵ��ֵ����Ա����;UpdateData(FALSE) == ����Ա������ֵ��ֵ���ؼ���
}
