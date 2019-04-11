
// CubeView.h : CCubeView ��Ľӿ�
//

#pragma once
#include "P3.h"
#include "P2.h"
#include "Facet.h"
#include "Transform.h"
#include "Pi2.h"
#include "Fill.h"
#include "Triangle.h"

class CCubeView : public CView
{
protected: // �������л�����
	CCubeView();
	DECLARE_DYNCREATE(CCubeView)

// ����
public:
	CCubeDoc* GetDocument() const;

// ����
public:
	void ReadPoint();
	void ReadFace();
	void DrawObject(CDC*);
	void InitParameter();//������ʼ��
	void PerProject(CP3);//͸��ͶӰ
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
	virtual ~CCubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 P[8];//���
	CP3 ViewPoint;//�ӵ�������
	CP2 ScreenP;//��Ļ����ϵ�Ķ�ά�����
	CFacet F[6];//���
	double k[9];//���㳣��
	double Alpha,Beta;//��x����ת�Ǧ�����y����ת�Ǧ�
	double R,Theta,Phi,d;//R,Theta,Phi�ӵ����û�����ϵ��������,d�Ӿ�
	BOOL bPlay;//��������
	Transform tran;//�任����

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void On32772();
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // CubeView.cpp �еĵ��԰汾
inline CCubeDoc* CCubeView::GetDocument() const
   { return reinterpret_cast<CCubeDoc*>(m_pDocument); }
#endif

