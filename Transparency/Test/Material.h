#pragma once
#include "RGBA.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetAmbient(CRGBA c);//���ò��ʶԻ�����ķ�����	
	void SetDiffuse(CRGBA c);//���ò��ʶ��������ķ�����ic:
	void SetSpecular(CRGBA c);//���ò��ʶԾ��淴���ķ�����CRGB M_Ambient;//���ʶԻ�����ķ�����
	void SetEmit(CRGBA);//���ò�������������ɫ
	void SetSlope(double k);//���ò��ʵ�΢ƽ��б��
	void SetFresnel(double f);//���ò��ʵ�Fresnel����ϵ��
public:
	CRGBA M_Ambient;//���ʶԻ�����ķ�����
	CRGBA M_Diffuse;//���ʶ��������ķ�����
	CRGBA M_Specular;//���ʶԾ��淴���ķ�����
	CRGBA M_Emit;//��������������ɫ
	double M_k;//���ʵ�΢ƽ��б��
	double M_f;//Fresnel����ϵ��
	double M_n;//���ʵĸ߹�ָ��
};