#pragma once
#include "Vector3.h"

class CFacet//���������
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void SetVertexNum(int vNumber);//���ñ��涥�����
	void SetFacetNormal(CP3 Vertex0,CP3 Vertex1,CP3 Vertex2);//����С�淨ʸ��
public:
	int vNumber;//��Ķ�����
	int vIndex[4];//��Ķ���������
	CVector3 fNormal;//��ķ�ʸ��
};
