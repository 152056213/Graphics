
// TCubeView.h : CTCubeView ��Ľӿ�
//

#pragma once
#include "P3.h"
#include "Face.h"
#include "Transform.h"


class CTCubeView : public CView
{
protected: // �������л�����
	CTCubeView();
	DECLARE_DYNCREATE(CTCubeView)

// ����
public:
	CTCubeDoc* GetDocument() const;

// ����
public:
	void ReadPoint();//���붥���
	void ReadFace();//��������
	void ObliqueProject(CP3);//б�Ȳ�任
	void DrawObject(CDC *);//����ͼ��
	void DrawPolygon(CDC *);//���ƶ����
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
	virtual ~CTCubeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect rect;//����ͻ���
	CP3 P[8];
	CP2 ScreenP;
	CFace F[6];
	CTransform trans;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTleft();
	afx_msg void OnTright();
	afx_msg void OnTup();
	afx_msg void OnTdown();
	afx_msg void OnTfront();
	afx_msg void OnTback();
	afx_msg void OnTbig();
	afx_msg void OnTsmall();
	afx_msg void OnRxaxis();
	afx_msg void OnRyaxis();
	afx_msg void OnRzaxis();
	afx_msg void OnRxoy();
	afx_msg void OnRyoz();
	afx_msg void OnRxoz();
	afx_msg void OnSxdirectionplus();
	afx_msg void OnSydirectionplus();
	afx_msg void OnSzdirectionneg();
	afx_msg void OnDrawpic();
	afx_msg void OnReset();
	afx_msg void OnAaa();
	afx_msg void OnBbb();
	afx_msg void OnCcc();
	afx_msg void OnDdd();
};

#ifndef _DEBUG  // TCubeView.cpp �еĵ��԰汾
inline CTCubeDoc* CTCubeView::GetDocument() const
   { return reinterpret_cast<CTCubeDoc*>(m_pDocument); }
#endif

