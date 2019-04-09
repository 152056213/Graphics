
// NBzierView.h : CNBzierView ��Ľӿ�
//

#pragma once


class CNBzierView : public CView
{
protected: // �������л�����
	CNBzierView();
	DECLARE_DYNCREATE(CNBzierView)

// ����
public:
	CNBzierDoc* GetDocument() const;

// ����
public:
	void DrawCtrlPolygon();//���ƿ��ƶ���κ���
	long Fac(int);//�׳˺���
	double Cni(const int &,const int &);//Bernstein��һ��
	void DrawBezier();//����Bezier����
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
	virtual ~CNBzierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL bFlag; //��־
	CPoint *P;//����
	int  CtrlPointNum;//���ƶ���ζ������
	int  n;//Bezier���ߵĽ״�
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawpic();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // NBzierView.cpp �еĵ��԰汾
inline CNBzierDoc* CNBzierView::GetDocument() const
   { return reinterpret_cast<CNBzierDoc*>(m_pDocument); }
#endif

