#pragma once
#include "Vector.h"
class Facet
{
public:
	Facet(void);
	~Facet(void);
	void SetNum(int);
	void SetFaceNormal(CP3,CP3,CP3);//����С�淨ʸ��
public:
	int pNumber;
	int pIndex[4][4];
	int vN;         //С��Ķ�����
	int *vI;        //С��Ķ�������
	CVector fNormal;//С��ķ�ʸ��
};


