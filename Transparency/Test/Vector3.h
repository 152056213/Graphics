#pragma once
#include "P3.h"
#include "Point2.h"

class CVector3
{
public:
	CVector3(void);
	virtual ~CVector3(void);
	CVector3(double x, double y, double z);//����ʸ��
	CVector3(const CP3 &vertex);
	CVector3(const CP3 &Vertex0, const CP3 &Vertex1);//���ʸ��
	CVector3(const CPoint2 &,const CPoint2 &);
	double Magnitude(void);//����ʸ����ģ
	CVector3 Normalize(void);//�淶��ʸ��
	friend CVector3 operator + (const CVector3 &v0, const CVector3 &v1);//���������
	friend CVector3 operator - (const CVector3 &v0, const CVector3 &v1);
	friend CVector3 operator * (const CVector3 &v, double scalar);
	friend CVector3 operator * (double scalar, const CVector3 &v);
	friend CVector3 operator / (const CVector3 &v,double scalar);
	friend double DotProduct(const CVector3 &v0, const CVector3 &v1);//����ʸ���ĵ��
	friend CVector3 CrossProduct(const CVector3 &v0, const CVector3 &v1);//����ʸ���Ĳ��
public:
	double x,y,z;
};

