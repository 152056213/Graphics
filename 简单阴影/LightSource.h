#pragma once
#include "P3.h"

class CLightSource  //��Դ��
{
public:
	CLightSource();
	virtual ~CLightSource();
	void SetDiffuse(CRGB diffuse);//���ù�Դ���������
	void SetSpecular(CRGB specular);//���ù�Դ�ľ��淴���
	void SetPosition(double x, double y, double z);//���ù�Դ��ֱ������λ��
	void SetGlobal(double r, double phi, double theta);//���ù�Դ��������λ��
	void SetCoefficient(double c0, double c1, double c2);//���ù�ǿ��˥��ϵ��
	void SetOnOff(BOOL);//���ù�Դ����״̬	
	void GlobalToXYZ();//������ת��Ϊֱ������	
public:
	CRGB L_Diffuse;//�����������ɫ	
	CRGB L_Specular;//��ľ���߹���ɫ
	CP3  L_Position;//��Դ��λ��
	double L_R,L_Phi,L_Theta;//��Դ������
	double L_C0;//����˥��ϵ��
	double L_C1;//����˥��ϵ��
	double L_C2;//����˥��ϵ��
	BOOL L_OnOff;//��Դ����
};

