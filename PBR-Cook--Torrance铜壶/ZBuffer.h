#pragma once
#include"P2.h"
#include"Point2.h"
#include "P3.h"
#include "Vector3.h"
#include "Lighting.h"

class CZBuffer
{
public:
	CZBuffer(void);
	virtual ~CZBuffer(void);
	void SetPoint(CPi3 P0,CPi3 P1,CPi3 P2,CVector3 N0,CVector3 N1,CVector3 N2);//�����γ�ʼ��
	void PhongShading(CDC* pDC,CP3 ViewPoint,CLighting* pLight,CMaterial* pMaterial,BOOL Sign);//Phong�����������������
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//Ϊ�������
	void InitDeepBuffer(int,int,double);//��ʼ����Ȼ�����
	CRGB LinearInterpolation (double t, double tStart, double tEnd, CRGB intensityStart, CRGB intensityEnd);//��ǿ���Բ�ֵ
	CVector3 LinearInterpolation (double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd);//��ʸ�����Բ�ֵ
	void SortVertex();//��������
public:
	CPoint2 point0, point1, point2;//�����ε�������������
	CPi3 V0, V1, V2;//�����εĸ�������������
	CPoint2* pLeft; //��ȵ���������־
	CPoint2* pRight;//��ȵ��յ������־
	int nIndex;//��¼ɨ��������
	double **zBuffer;//����ȳ���
	int Width,Height;//����������
};

