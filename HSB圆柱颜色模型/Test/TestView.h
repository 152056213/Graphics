
// TestView.h : CTestView ��Ľӿ�
//

#pragma once
#include "Face.h"
#include "Transform.h"
#include "Fill.h"

class CTestView : public CView
{
protected: // �������л�����
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// ����
public:
	CTestDoc* GetDocument() const;

// ����
public:
	void ReadVertex();//������
	void ReadFace();//�������
	void InitParameter();//������ʼ��
	void PerProject(CP3);//͸��ͶӰ
	void DoubleBuffer(CDC *pDC);//˫�����ͼ
	void DrawObject(CDC *);//��������
	void CalVertexColor();//�������Ĺ�����ɫ
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
	CP3 *V;//���
	CFace **F;//���
	int N1,N2;//N1Ϊ��������,N2��������
	double R,Theta,Phi,d;//R,Theta,Phi�ӵ����û�����ϵ��������,d�Ӿ�
	double k[9];//���㳣��
	CP3 ViewPoint;//�ӵ�������
	CPi2 ScreenP;//��Ļ����ϵ�Ķ�ά�����
	//BOOL bPlay;//��������
	double Alpha,Beta;//x������ת����,y������ת�½�
	CTransform tran;//�任����
	double h;//Բ���߶�
	double r;//Բ���뾶
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	virtual void OnInitialUpdate();
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // TestView.cpp �еĵ��԰汾
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

