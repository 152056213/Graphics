#pragma once
#include "P3.h"

class CTransform
{
public:
	CTransform(void);
	~CTransform(void);
	void SetMat(CP3 *,int);
	void Identity();
	void Translate(double,double,double);//ƽ�Ʊ任����
	void Scale(double,double,double);//�����任����
	void Scale(double,double,double,CP3);//����������ı����任����
	void RotateX(double);//��ת�任����
	void RotateX(double,CP3);//�����������X��ת�任����
	void RotateY(double);//��ת�任����
	void RotateY(double,CP3);//�����������Y��ת�任����
	void RotateZ(double);//��ת�任����
	void RotateZ(double,CP3);//�����������Z��ת�任����
	void ReflectX();//X�ᷴ��任����
	void ReflectY();//Y�ᷴ��任����
	void ReflectZ();//Z�ᷴ��任����
	void ReflectXOY();//XOY�淴��任����
	void ReflectYOZ();//YOZ�淴��任����
	void ReflectXOZ();//XOZ�淴��任����
	void ShearX(double,double);//X������б任����
	void ShearY(double,double);//Y������б任����
	void ShearZ(double,double);//Z������б任����
	void MultiMatrix();//�������
public:
	double T[4][4];
	CP3 *POld;
	int num;
};

