#pragma once
#include "RGB.h"

class CMaterial  //������
{
public:
	CMaterial();
	virtual ~CMaterial();
	void SetAmbient(CRGB c);//���ò��ʶԻ�����ķ�����
	void SetDiffuse(CRGB c);//���ò��ʶ��������ķ�����
	void SetSpecular(CRGB c);//���ò��ʶԾ��淴���ķ�����
	void SetEmit(CRGB c);//���ò�������������ɫ
	void SetExp(double n);//���ò��ʵĸ߹�ָ��	
public:
	CRGB M_Ambient;//���ʶԻ�����ķ�����
	CRGB M_Diffuse;//���ʶ��������ķ�����
	CRGB M_Specular;//���ʶԾ��淴���ķ�����
	CRGB M_Emit;//��������ɢ����ɫ
	double M_n;//���ʵĸ߹�ָ��
};


