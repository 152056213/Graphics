#pragma once
#include "AET.h"

class CBucket
{
public:
	CBucket(void);
	~CBucket(void);
public:
	int ScanLine;    //ɨ����
	CAET *pET;       //Ͱ�ϵı߱�ָ��
	CBucket *pNext;
};

