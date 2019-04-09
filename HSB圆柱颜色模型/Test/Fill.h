#pragma once
#include "Bucket.h"
class CFill
{
public:
	CFill(void);
	~CFill(void);
	void SetPoint(CPi2 *p,int);//��ʼ��
	void CreateBucket();//����Ͱ
	void CreateEdge();//�߱�
	void AddET(CAET *);//�ϲ�ET��
	void ETOrder();//ET������
	void Gouraud(CDC *);//�������
    CRGB Interpolation(double,double,double,CRGB,CRGB);//���Բ�ֵ
	void ClearMemory();//�����ڴ�
	void DeleteAETChain(CAET* pAET);//ɾ���߱�
protected:
	int     PNum;//�������
	CPi2    *P;//�������궯̬����
	CAET    *pHeadE,*pCurrentE,*pEdge; //��Ч�߱���ָ��
	CBucket *pHeadB,*pCurrentB;        //Ͱ����ָ��
};

