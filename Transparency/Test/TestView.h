
// TestView.h : interface of the CTestView class
//

#pragma once
#include "Facet.h"
#include "Vector3.h"
#include "Lighting.h"
#include "Triangle.h"

class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument() const;

// Operations
public:
	public:
	void DoubleBuffer(CDC *pDC);//˫����
	void ReadControlVertex(void);//���붥���
	void ReadFacet(void);//�������
	void LeftMultiMatrix(double M0[][4],CP3 P0[][4],int p,int f); //��˾���
	void RightMultiMatrix(CP3 P0[][4],double M1[][4],int p,int f);//�ҳ˾���
	void TransposeMatrix(double M0[][4]);//����ת��
	void InitialParameter(void);//�任����
	void Perspect(); //͸��
	CP3 PerspectiveProject(CP3 WorldPoint);//͸��ͶӰ
	void DrawGround(CDC *pDC);//��������ײ���ɫƽ��
	void Bezier();//����Bezier����
	void DrawGraph(CDC *pDC);//��ͼ
public:
	double R, Psi,Phi;//�ӵ����û�����ϵ�е�������
	double d;//�Ӿ�
	double k[8];
	CP3 ViewPoint;//�ӵ�������λ��	
	CTriangle* pFill; //���������
	int LightSourceNumer;//��Դ����
	CLighting* pLight;//���ջ���
	CMaterial* pMaterial;//�������
public:
	double MT[4][4];//M��ת�þ���
	CFacet F[100];
	CP3 ControlP[3][4][4][4];
	CP3 ObjectP[3][4][121];
	int part;//�����м�����
	int face;//ÿ�����м�����
	BOOL bPlay;//��������
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGraphDraw();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateGraphDraw(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

