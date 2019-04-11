// Vector3.h: interface for the CVector33 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR3_H__AF0E0B97_5194_4C82_A77D_28BD70CFE75F__INCLUDED_)
#define AFX_VECTOR3_H__AF0E0B97_5194_4C82_A77D_28BD70CFE75F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Pi3.h"
#include "P3.h" 
class CVector3  
{
public:
	CVector3();	
	virtual ~CVector3();
	CVector3(double,double,double);
	CVector3(const CP3 &);
	CVector3(const CP3 &,const CP3 &);
	CVector3(const CPi3 &,const CPi3 &);
	double Mag();//ʸ����ģ
	CVector3 Normalize();//��λʸ��
	friend CVector3 operator +(const CVector3 &,const CVector3 &);//���������
	friend CVector3 operator -(const CVector3 &,const CVector3 &);
	friend CVector3 operator *(const CVector3 &,double);
	friend CVector3 operator *(double,const CVector3 &);
	friend CVector3 operator /(const CVector3 &,double);
	friend CVector3 operator+=(CVector3 &,CVector3 &);
	friend CVector3 operator-=(CVector3 &,CVector3 &);
	friend CVector3 operator*=(CVector3 &,CVector3 &);
	friend CVector3 operator/=(CVector3 &,double);
	friend double  Dot(const CVector3 &,const CVector3 &);  //ʸ�����
	friend CVector3 Cross(const CVector3 &,const CVector3 &);//ʸ�����
public:
	double x,y,z;//�������ݳ�Ա�������ⲿ����
};
#endif // !defined(AFX_VECTOR3_H__AF0E0B97_5194_4C82_A77D_28BD70CFE75F__INCLUDED_)
