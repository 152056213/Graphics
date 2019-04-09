#pragma once
#include "P3.h"

class Transform
{
public:
	Transform(void);
	~Transform(void);
public:
	void SetMatrix(CP3* p, int ptNumber);//��ȡ��Ķ������
	void Identity();//��ʼ�任����
	void Translate(double tx,double ty, double tz); //ƽ�Ʊ任����
	void RotateX(double beta); //��x����ת�任��������ת�任����
	void RotateY(double beta); //��y����ת�任��������ת�任����
	void MultiplyMatrix();     //��ɱ任��ľ���
public:
	double T[4][4];
	CP3* P;
	int ptNumber;
};

