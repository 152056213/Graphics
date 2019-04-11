#pragma once
#include "AET.h"
#include "Bucket.h"
#include "P2.h"
#include "RGB.h"

class CFill
{
public:
	CFill(void);
	~CFill(void);
public:
	void SetPoint(CPi2 *p,int);     //��ʼ��
	void CreateBucket();            //����Ͱ
	void CreateEdge();              //�����߱�
	void AddET(CAET *);             //�ϲ�ET��
	void ETOrder();                 //ET������
	void Gouraud(CDC *);            //�������
	CRGB Interpolation(double,double,double,CRGB,CRGB);//���Բ�ֵ
	void ClearMemory();             //�����ڴ�
	void DeleteAETChain(CAET *pAET);//ɾ���߱�
public:
	int PNum;                       //�������
	CPi2 *P;                         //�������궯̬����
	CAET *pHeadE,*pCurrentE,*pEdge; //��Ч�߱���ָ��
	CBucket *pHeadB,*pCurrentB;     //Ͱ����ָ��
};

