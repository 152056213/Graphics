#pragma once
#include "Vector.h"
class CAET
{
public:
	CAET(void);
	~CAET(void);
public:
	double  x;//��ǰɨ��������Ч�߽����x����
	int     yMax;//�ߵ����yֵ
	double  k;//б�ʵĵ���(x������)
	CPi2    ps;//�ߵ����
	CPi2    pe;//�ߵ��յ�
	CVector ns;//��㷨ʸ��
	CVector ne;//�յ㷨ʸ��
	double A;
	double B;
	CAET   *pNext;

};

