#pragma once
#include "Light.h"
#include "Material.h"
#include "Vector.h"
class CLighting
{
public:
	CLighting();
	CLighting(int);
	virtual ~CLighting();
	void SetLightNumber(int);//���ù�Դ����
	CRGB Lighting(CP3 ViewPoint, CP3 Point, CVector Normal, CMaterial *pMaterial,BOOL,CRGB InitC);
public:
	int LightNum;//��Դ����
	CLight *Light;//��Դ����
	CRGB Ambient;//������
	CRGB LastC;
};

