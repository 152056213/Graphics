
// EetFillView.h : CEetFillView ��Ľӿ�
//

#pragma once
#include "P2.h"
#include "Pi2.h"


class CEetFillView : public CView
{
protected: // �������л�����
	CEetFillView();
	DECLARE_DYNCREATE(CEetFillView)

// ����
public:
	CEetFillDoc* GetDocument() const;
// ����
public:
	void Draw(CDC *);
	void ReadPoint();
	void FillPolygon(CDC *);//�������
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
	virtual ~CEetFillView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPi2 P1[10];//y�������
	CPoint *Q,t;
	int Max,num;
	BOOL bFlag;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawpolygon();
	afx_msg void OnFill();
};

#ifndef _DEBUG  // EetFillView.cpp �еĵ��԰汾
inline CEetFillDoc* CEetFillView::GetDocument() const
   { return reinterpret_cast<CEetFillDoc*>(m_pDocument); }
#endif

