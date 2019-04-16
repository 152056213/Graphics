#pragma once
#include "Vector.h"
#include "Material.h"
#include "LightSource.h"

class CLighting  //������
{
public:
	CLighting();
	CLighting(int );
	virtual ~CLighting();
	void SetLightNumber(int LightNumber);//���ù�Դ����		
	CRGB Lighting(CP3 ViewPoint, CP3 Point, CVector Normal, CMaterial* pMaterial);//����	
public:
	int LightNumber;//��Դ����
	CLightSource* LightSource;//��Դ����
	CRGB Ambient;//������
};

