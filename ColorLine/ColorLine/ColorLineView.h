
// ColorLineView.h : CColorLineView ��Ľӿ�
//

#pragma once


class CColorLineView : public CView
{
protected: // �������л�����
	CColorLineView();
	DECLARE_DYNCREATE(CColorLineView)

// ����
public:
	CColorLineDoc* GetDocument() const;

public:
   void DrawObject(CDC *);
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
	virtual ~CColorLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double Theta,q;//��ת��
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // ColorLineView.cpp �еĵ��԰汾
inline CColorLineDoc* CColorLineView::GetDocument() const
   { return reinterpret_cast<CColorLineDoc*>(m_pDocument); }
#endif

