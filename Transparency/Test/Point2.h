#pragma once
#include"RGBA.h"

class CPoint2
{
public:
	CPoint2(void);
	CPoint2(int x, int y);
	CPoint2(int x, int y, double T, CRGBA c);
	virtual ~CPoint2(void);
	friend CPoint2 operator + (const CPoint2 &pt0, const CPoint2 &pt1);//���������
	friend CPoint2 operator - (const CPoint2 &pt0, const CPoint2 &pt1);
	friend CPoint2 operator * (const CPoint2 &pt, double m);
	friend CPoint2 operator * (int m, const CPoint2 &pt);
	friend CPoint2 operator / (const CPoint2 &pt, int m);
	friend BOOL operator != (const CPoint2 pt0, const CPoint2 pt1);
	friend CPoint2 operator < (const CPoint2 pt0, const CPoint2 pt1);		//��y����ѡ�����Сyֵ�ĵ�
	friend CPoint2 operator > (const CPoint2 pt0, const CPoint2 pt1);		//��y����ѡ������yֵ�ĵ�
public:
	int x, y;
	double z;
	double T;
	CRGBA   c;
};
