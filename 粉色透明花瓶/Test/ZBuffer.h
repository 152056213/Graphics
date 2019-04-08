#pragma once
#include "Bucket.h"
#include "Vector.h"
#include "Lighting.h"
#include "Material.h"
class CZBuffer
{
public:
	CZBuffer();
    virtual ~CZBuffer();
	void CreateBucket();//����Ͱ
	void CreateEdge();//�߱�
	void AddEt(CAET *);//�ϲ�ET��
	void ETOrder();
	void Phong(CDC *,CP3,CLighting *,CMaterial *,int);//Phong��亯��
	CRGB GetTransColor(CRGB,CRGB);//����͸����ɫ
	void InitDeepBuffer(CDC *,int,int,double,CRGB);//��ʼ����Ȼ���
    CRGB Interpolation(double,double,double,CRGB,CRGB);//���Բ�ֵ
	CVector Interpolation(double,double,double,CVector,CVector);//��ʸ���Բ�ֵ
	double Interpolation(double,double,double,double,double);
	void SetPoint(CPi3 *,CVector *,int);
	void ClearMemory();//�����ڴ�
	void DeleteAETChain(CAET* pAET);//ɾ���߱�
protected:
	int PNum;//�������
	CPi3 *P;//��������
	CVector *N;//����ķ�ʸ����̬����
	CAET *pHeadE,*pCurrentE,*pEdge;//��Ч�߱���ָ��
	CBucket *pCurrentB,*pHeadB;
	double **zBuffer;//����ȳ���
	CRGB   **cBuffer;//��ɫ������
	int Width,Height;//����������
	double VAB;
	COLORREF BkaClr;
};

