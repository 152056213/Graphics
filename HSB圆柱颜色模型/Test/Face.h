#pragma once
#include "Vector.h"

class CFace
{
public:
	CFace(void);
	~CFace(void);
	void SetNum(int);
	void SetFaceNormal(CP3,CP3,CP3);//����С�淨ʸ��
public:
	int vN;          //С��Ķ�����
	int *vI;         //С��Ķ�������
	CVector fNormal; //С��ķ�ʸ��
};

