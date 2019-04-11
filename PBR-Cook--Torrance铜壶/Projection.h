// Projection.h: interface for the CProjection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTION_H__3AD9667B_0D4A_4C17_B204_3046C2C158AE__INCLUDED_)
#define AFX_PROJECTION_H__3AD9667B_0D4A_4C17_B204_3046C2C158AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"
#include "Pi3.h"
class CProjection  
{
public:
	CProjection();
	virtual ~CProjection();
	CP3 InitalParameter();
	CPi3 PerspectiveProjection(CP3 WorldP);//͸��ͶӰ
	CP2 OrthogonalProjection(CP3 WorldP);//����ͶӰ
	CP2 CavalierProjection(CP3 WorldP);//б�Ȳ�ͶӰ
	CP2 CabinetProjection(CP3 WorldP);//б����ͶӰ
private:
	double k[9];//͸��ͶӰ����
	double R, Theta, Phi, d;//�ӵ����û�����ϵ�е�������
		double	Near,Far;//����������Զ������

};

#endif // !defined(AFX_PROJECTION_H__3AD9667B_0D4A_4C17_B204_3046C2C158AE__INCLUDED_)
