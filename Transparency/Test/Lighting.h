#pragma once
#include "LightSource.h"
#include "Material.h"
#include "Vector3.h"

class CLighting
{
public:
	CLighting(void);
	CLighting(int LightNumber);
	virtual ~CLighting(void);
	void SetLightNumber(int Number);//���ù�Դ����
	CRGBA illuminate(CP3 ViewPoint, CP3 Point, CVector3 Normal, CMaterial* pMaterial);//�������	
public:
	int Number;//��Դ����
	CLightSource* LightSource;//��Դ����
	CRGBA Ambient;//������
};