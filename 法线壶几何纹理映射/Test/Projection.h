#pragma once
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
