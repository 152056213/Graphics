
// TestView.h : CTestView ��Ľӿ�
//
#include"Transform3.h"
#pragma once
#include"BicubicBezierPatch.h"
#include"Revolution.h"
#include "Facet.h"
#include "ZBuffer.h"
class CTestView : public CView
{
protected: // �������л�����
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// ����
public:
	CTestDoc* GetDocument() const;
	void DoubleBuffer(CDC* pDC);//˫����
	void DrawGraph1(CDC* pDC);
	void InitParameter();//�任����
	void PerProject(CP3);//͸��ͶӰ
	void ReadFace();//�������
	void DrawObject(CDC *,CZBuffer *);//��������
	void ReadCubeVertex();//���������嶥��
	void ReadCubeFace();//�������������
	void DrawCube(CDC *,CZBuffer *);//����������
// ����
public:
 void	DrawGraph(CDC*pDC);
 void ReadPoint();
private:
	CP3 P[4];CP3 P1[4];CP3 P2[4],P3[3];
	double Alpha,Beta;
	Transform3 tran;
	Transform3 tran1;
	Transform3 tran2;
	Transform3 tran3;
	Transform3 tran4;
	CRevolution pdd; 
	CRevolution pdd1; 
	CRevolution pdd2; 
	CRevolution pdd3; 
	Facet F[100];
	double R,Theta,Phi;//�ӵ����û�����ϵ�е�������
	double d;//�Ӿ�
	double Near,Far;//Զ��������
	double k[9];
	CP3 N0[4][121],N1[4][121],N2[4][121];
	CVector Nv0[4][121],Nv1[4][121],Nv2[4][121];
	CP3 ViewPoint;//�ӵ�������λ��
	CPi3 ScreenP;//��Ļ����ϵ����ά�����
	int	 LightNum;//��Դ����
	CLighting *pLight;//���ջ���
	CMaterial *pMaterial;//�������
	CZBuffer *pFill;
	CP3 BN[12][12];
	CP3 CN[144];
	Facet FC[121];
// ��д
public:
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

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // TestView.cpp �еĵ��԰汾
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

