
// CutView.h : CCutView ��Ľӿ�
//

#pragma once
#include "P2.h"

class CCutView : public CView
{
protected: // �������л�����
	CCutView();
	DECLARE_DYNCREATE(CCutView)

// ����
public:
	CCutDoc* GetDocument() const;

// ����
public:
	void DoubleBuffer(CDC *pDC);//˫����
	void DrawWindowRect(CDC *);//���Ʋü�����
	void Cohen();//�ü�����
	void EnCode(CP2 &);//���뺯��
	CP2  Convert(CPoint point);//����ϵת��
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
	virtual ~CCutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int wxl,wxr;//���ھ���x����
	int wyb,wyt;//���ھ���y����
	BOOL bDrawLine;//�Ƿ�������
	CP2 P[2];//ֱ�ߵ������յ�
	int PtCount;//�������
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOndrawpic();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClip();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // CutView.cpp �еĵ��԰汾
inline CCutDoc* CCutView::GetDocument() const
   { return reinterpret_cast<CCutDoc*>(m_pDocument); }
#endif

