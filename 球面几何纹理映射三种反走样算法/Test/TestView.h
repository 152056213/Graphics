
// TestView.h : CTestView ��Ľӿ�
//

#pragma once

#include "Face.h"
#include "Vector.h"
#include "ZBuffer.h"
#include "Lighting.h"
#include "Transform.h"
#include "T2.h"
class CTestView : public CView
{
protected: // �������л�����
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// ����
public:
	CTestDoc* GetDocument() const;

// ����
public:
	void ReadVertex();//���붥������
	void ReadFace();//����������
	void ReadImage(int Sign);//������ɫ����
	void ReadBumpMap(int Sign);//���밼͹����
	void BiLinear_BMP(COLORREF **,int,int,COLORREF **,int,int);//���ڽ�ȡ���㷨
	void BiLinear_BMP1(COLORREF **,int,int,COLORREF **,int,int);//˫���Բ�ֵ�㷨
	void BiInterpolation_BMP(COLORREF **,int,int,COLORREF **,int,int);//˫���β�ֵ�㷨
	double BiInterpolation(double);//˫���β�ֵ
	void InitParameter();//�任����
	void PerProject(CP3);//͸��ͶӰ
	void DoubleBuffer(CDC *pDC);//˫����
	void DrawObject(CDC *,int Sign);//��������
	void Paint(CDC *);//��������
	void ClearMemory();//�����ڴ�
	void DrawPic(CDC *);//����ַ���
// ��д
public:
	void Diamond();//���ƽ��ʯͼ������
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	UINT nScale;//�Ŵ󾵱���
	CP2 nRCenter;//�ü����ε���������
	double nRHHeight,nRHWidth;//�ü����εİ�߶ȺͰ���
    double R,Theta,Phi;//�ӵ����û�����ϵ�е�������
	double d;//�Ӿ�
	double Near,Far;//Զ��������
	double k[9];//͸�ӱ任����
	CP3 ViewPoint;//�ӵ�������λ��
	CPi3 ScreenP;//��Ļ����ϵ����ά�����
	CP3 *V;//Բ������һά����
	CT2 *T;//Բ������һά����
	CFace **F;//��Ķ�ά����
	int N1,N2;//N1Ϊ��������,N2Ϊγ������
	int gAlpha,gBeta;//γ�Ƚ��뾭�Ƚ�
	int LightNum;//��Դ����
	CLighting *pLight;//���ջ���
	CMaterial *pMaterial;//�������
	BOOL bPlay;//��������
	CTransform tran;//�任����
	double Alpha,Beta;//x������ת����,y������ת�½�
	COLORREF **Image1,**Image2,**LImage1,**LImage2;//��ά��̬����
	BITMAP bmp1,bmp2;//BITMAP�ṹ�����
	BYTE *im;
	double **Imgx_Gradient,**Imgy_Gradient;
	int nWidth,nHeight;//ͼ��Ŀ�Ⱥ͸߶�
	int r;//����뾶
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDrawpic();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnPlay();
	afx_msg void OnUpdatePlay(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // TestView.cpp �еĵ��԰汾
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

