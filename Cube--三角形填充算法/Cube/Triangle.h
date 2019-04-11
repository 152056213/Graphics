#pragma once
#include "P2.h"
#include "Point2.h"

class CTriangle
{
public:
	CTriangle(void);
	CTriangle(CP2 P0, CP2 P1, CP2 P2);//����������������
	~CTriangle(void);
	void Gouraud(CDC* pDC);//���������
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//Ϊ�������
	CRGB ClrInterpolation(double t, double mStart, double mEnd, CRGB cStart, CRGB cEnd);//��ɫ���Բ�ֵ
	void SortVertex();//��������
public:
	CPoint2 point0, point1, point2;//�����ε�������������
	CPoint2* pLeft; //��ȵ���������־
	CPoint2* pRight;//��ȵ��յ������־
	int nIndex;//��¼ɨ��������
};

