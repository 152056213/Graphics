#pragma once
#include"P2.h"
#include"Point2.h"
#include "P3.h"
#include "Vector.h"

class CZBuffer
{
public:
	CZBuffer(void);
	~CZBuffer(void);
	void SetPoint(CP3 P0, CP3 P1, CP3 P2);
	void Gouraud(CDC* pDC);//���������
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//Ϊ�������
	void InitDeepBuffer(int,int,double);//��ʼ����Ȼ�����
	CRGB ClrInterpolation(double t, double mStart, double mEnd, CRGB cStart, CRGB cEnd);//��ɫ���Բ�ֵ
	void SortVertex();//��������
public:
	CPoint2 point0, point1, point2;//�����ε�������������
	CPoint2* pLeft; //��ȵ���������־
	CPoint2* pRight;//��ȵ��յ������־
	int nIndex;//��¼ɨ��������
	double **zBuffer;//����ȳ���
	int Width,Height;//����������
};

