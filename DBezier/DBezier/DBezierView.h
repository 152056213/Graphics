
// DBezierView.h : CDBezierView ��Ľӿ�
//

#pragma once


class CDBezierView : public CView
{
protected: // �������л�����
	CDBezierView();
	DECLARE_DYNCREATE(CDBezierView)

// ����
public:
	CDBezierDoc* GetDocument() const;

// ����
public:
	void DrawPolygon(CDC *);//���ƶ����
	void DrawBezier(CDC *);//����Bezier����
	void DrawPic(CDC *);
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
	virtual ~CDBezierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPoint P[4];
	CPoint p[6];
	CPoint q[100];
	double t;
	int j;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // DBezierView.cpp �еĵ��԰汾
inline CDBezierDoc* CDBezierView::GetDocument() const
   { return reinterpret_cast<CDBezierDoc*>(m_pDocument); }
#endif

