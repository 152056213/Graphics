#pragma once
#include"P2.h"
#include"Point2.h"
#include "P3.h"
#include "Vector3.h"

class CTriangle
{
public:
	CTriangle(void);
	~CTriangle(void);
	void SetPoint(CP3 P0, CP3 P1, CP3 P2);
	void Gouraud(CDC* pDC);//���������
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//Ϊ�������
	void InitDeepBuffer(int,int,double);//��ʼ����Ȼ�����
	CRGBA ClrInterpolation(double t, double mStart, double mEnd, CRGBA cStart, CRGBA cEnd);//��ɫ���Բ�ֵ
	double ClrInterpolation(double t, double mStart, double mEnd, double tStart, double tEnd);//͸�������Բ�ֵ
	void SortVertex();//��������
public:
	CPoint2 point0, point1, point2;//�����ε�������������
	CPoint2* pLeft; //��ȵ���������־
	CPoint2* pRight;//��ȵ��յ������־
	int nIndex;//��¼ɨ��������
	double **zBuffer;//����ȳ���
	int Width,Height;//����������
};
