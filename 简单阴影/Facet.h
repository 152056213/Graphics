#pragma once
#include "RGB.h"
#include "Vector.h"
class CFacet
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void PointNum(int ptNumber);
	void SetFaceNormal(CP3,CP3,CP3);//����С�淨ʸ��
public:
	int ptNumber; //��Ķ�����
	int ptIndex[4];//��Ķ���������
	CRGB c;
	CVector fNormal; //С��ķ�ʸ��
};

