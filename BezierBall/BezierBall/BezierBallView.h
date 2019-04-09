
// BezierBallView.h : CBezierBallView ��Ľӿ�
//

#pragma once
#include "P3.h"
#include "Bezier.h"
#include "Transform.h"

class CBezierBallView : public CView
{
protected: // �������л�����
	CBezierBallView();
	DECLARE_DYNCREATE(CBezierBallView)

// ����
public:
	CBezierBallDoc* GetDocument() const;

// ����
public:
	void ReadPoint();
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
	virtual ~CBezierBallView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 Q1[4][4],Q2[4][4],Q3[4][4],Q4[4][4],Q5[4][4],Q6[4][4],Q7[4][4],Q8[4][4];
	//CP3 V1[4][4],V2[4][4],V3[4][4],V4[4][4],V5[4][4],V6[4][4],V7[4][4],V8[4][4];
	CP3 P1[16],P2[16],P3[16],P4[16],P5[16],P6[16],P7[16],P8[16];//���
	double Alpha,Beta;//��x����ת�Ǧ�����y����ת�Ǧ�
	Transform tran;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // BezierBallView.cpp �еĵ��԰汾
inline CBezierBallDoc* CBezierBallView::GetDocument() const
   { return reinterpret_cast<CBezierBallDoc*>(m_pDocument); }
#endif

