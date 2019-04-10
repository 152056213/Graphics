#pragma once
#include "Light.h"
#include "Material.h"
#include "Vector.h"

class CLighting
{
public:
	CLighting(void);
	CLighting(int);
	~CLighting(void);
	void SetLightNumber(int);  //���ù�Դ����
	CRGB Lighting(CP3,CP3,CVector,CMaterial *);  //�������
public:
	int LightNum;   //��Դ����
	CLight *Light;  //��Դ����
	CRGB Ambient;   //������
};

