#pragma once
#include "P3.h"
#include "Point2.h"
class CVector  
{
public:
	CVector();	
	virtual ~CVector();
	CVector(double,double,double);
	CVector(const CP3 &);
	CVector(const CP3 &,const CP3 &);
	CVector(const CPoint2 &,const CPoint2 &);
	double Mag();//ʸ����ģ
	CVector Normalize();//��λʸ��
	friend CVector operator +(const CVector &,const CVector &);//���������
	friend CVector operator -(const CVector &,const CVector &);
	friend CVector operator *(const CVector &,double);
	friend CVector operator *(double,const CVector &);
	friend CVector operator /(const CVector &,double);
	friend CVector operator+=(CVector &,CVector &);
	friend CVector operator-=(CVector &,CVector &);
	friend CVector operator*=(CVector &,CVector &);
	friend CVector operator/=(CVector &,double);
	friend double  Dot(const CVector &,const CVector &);  //ʸ�����
	friend CVector Cross(const CVector &,const CVector &);//ʸ�����
public:
	double x,y,z;//�������ݳ�Ա�������ⲿ����
};

