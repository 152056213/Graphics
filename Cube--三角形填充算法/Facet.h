#pragma once
#include "P3.h"
#include "Vector.h"

class CFacet
{
public:
	CFacet(void);
	~CFacet(void);
	void SetFaceNormal(CP3,CP3,CP3);//����С�淨ʸ��
public:
	int pIndex[4];
	CVector fNormal; //С��ķ�ʸ��
};

