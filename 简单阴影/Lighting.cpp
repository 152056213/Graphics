#include "StdAfx.h"
#include "Lighting.h"
#include "math.h"
#define  PI  3.14159265
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))


CLighting::CLighting()
{
	LightNumber = 1;
	LightSource = new CLightSource[LightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);//�������ǳ���
}

CLighting::~CLighting()
{
	if (LightSource)
	{
		delete []LightSource;
		LightSource = NULL;
	}
}
void CLighting::SetLightNumber(int LightNumber)
{
	if(LightSource)
	{
		delete []LightSource;
	}
	this->LightNumber = LightNumber;
	LightSource = new CLightSource[LightNumber];
}

CLighting::CLighting(int LightNumber)
{
	this->LightNumber = LightNumber;
	LightSource = new CLightSource[LightNumber];
	Ambient = CRGB(0.3, 0.3, 0.3);
}

CRGB CLighting::Lighting(CP3 ViewPoint, CP3 Point, CVector Normal, CMaterial* pMaterial)
{	
	CRGB LastIntensity = pMaterial->M_Emit;//��������ɢɫΪ��ʼֵ	
	for (int loop = 0; loop < LightNumber; loop++)//����Դ����״̬
	{	
		if (LightSource[loop].L_OnOff)
		{		
			CRGB Intensity = CRGB(0.0, 0.0, 0.0);
			CVector vectorL(Point, LightSource[loop].L_Position);//vLΪָ���Դ��ʸ��
			double d = vectorL.Mag();//dΪ�⴫���ľ��룬���ڹ�ʸ��vectorL��ģ
			vectorL = vectorL.Normalize();//��λ����ʸ��
			CVector vectorN = Normal;
			vectorN = vectorN.Normalize();//��λ����ʸ��			
			//��1���������������
			double CosBeta = MAX(Dot(vectorL, vectorN), 0);			
			Intensity.red += LightSource[loop].L_Diffuse.red * pMaterial->M_Diffuse.red * CosBeta;
			Intensity.green += LightSource[loop].L_Diffuse.green * pMaterial->M_Diffuse.green * CosBeta;
			Intensity.blue += LightSource[loop].L_Diffuse.blue * pMaterial->M_Diffuse.blue * CosBeta;
			//��2�������뾵�淴���
			CVector vectorV(Point, ViewPoint);//VVΪ��ʸ��
			vectorV = vectorV.Normalize();//��λ����ʸ��
			CVector vectorH = (vectorL + vectorV) / (vectorL + vectorV).Mag();//VHΪƽ��ʸ��	
			double nHN = pow(MAX(Dot(vectorH, vectorN), 0), pMaterial->M_n);
			Intensity.red += LightSource[loop].L_Specular.red * pMaterial->M_Specular.red * nHN;
			Intensity.green += LightSource[loop].L_Specular.green * pMaterial->M_Specular.green * nHN;
			Intensity.blue += LightSource[loop].L_Specular.blue * pMaterial->M_Specular.blue * nHN;	
			//��3������ǿ˥��
			double c0 = LightSource[loop].L_C0;//c0Ϊ����˥������
			double c1 = LightSource[loop].L_C1;//c1����˥������
			double c2 = LightSource[loop].L_C2;//c2����˥������			
			double f = (1.0 / (c0 + c1 * d + c2 * d * d));//��ǿ˥������
			f = MIN(1.0,f);		
			LastIntensity += Intensity * f;		
		}
		else
			LastIntensity += Point.c;//����������ɫ		
	}
	//��4�������뻷����
	LastIntensity += Ambient * pMaterial->M_Ambient;
	//��5������ɫ��һ����[0,1]����
	LastIntensity.Normalize();		
	//��6�������������㶥��Ĺ�ǿ��ɫ
	return LastIntensity;
}	
