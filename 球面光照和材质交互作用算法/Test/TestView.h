
// TestView.h : CTestView ��Ľӿ�
//

#pragma once
#include "Pi2.h"
#include "Face.h"
#include "Vector.h"
#include "Lighting.h"
#include "Material.h"
#include "Transform.h"
#include "ZBuffer.h"

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
	void ReadVertex();//���붥���
	void ReadFace();//�������
	void InitParameter();//�任����
	void PerProject(CP3);//͸��ͶӰ
	void DoubleBuffer(CDC *pDC);//˫����
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
	double R,Theta,Phi;//�ӵ����û�����ϵ�е�������
	double d;//�Ӿ�
	double Near,Far;//Զ��������
	double k[9];
	CP3 ViewPoint;//�ӵ�������λ��
	CPi3 ScreenP;//��Ļ����ϵ����ά�����
	CP3 *V;//��Ķ���һά����
	CFace **F;//��Ķ�ά����
	double Alpha,Beta;//x������ת����,y������ת�½�
	int N1,N2;//N1Ϊγ������,N2Ϊ��������
	int	 LightNum;//��Դ����
	CLighting *pLight;//���ջ���
	CMaterial *pMaterial;//�������
	CTransform tran;//�任����	
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // TestView.cpp �еĵ��԰汾
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

