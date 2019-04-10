#include "StdAfx.h"
#include "Lighting.h"
#include "math.h"
#define  PI  3.14159265
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))

CLighting::CLighting(void)
{
	Number = 1;
	LightSource = new CLightSource[Number];
	Ambient = CRGBA(0.3, 0.3, 0.3);//�������ǳ���
}

CLighting::~CLighting(void)
{
	if (LightSource)
	{
		delete []LightSource;
		LightSource = NULL;
	}
}

void CLighting::SetLightNumber(int Number)
{
	if(LightSource)
		delete []LightSource;
	this->Number = Number;
	LightSource = new CLightSource[Number];
}

CLighting::CLighting(int Number)
{
	this->Number = Number;
	LightSource = new CLightSource[Number];
	Ambient = CRGBA(0.3, 0.3, 0.3);
}

CRGBA CLighting::illuminate(CP3 ViewPoint, CP3 Point, CVector3 Normal, CMaterial* pMaterial)
{	
	CRGBA ResultI = pMaterial->M_Emit;// ��ʼ�������ա���ǿ	Ϊ������ɫ
	for (int loop = 0; loop < Number; loop++)//����Դ����״̬
	{	
		if (LightSource[loop].L_OnOff)//��Դ��
		{		
			CRGBA I = CRGBA(0.0, 0.0, 0.0);// I�������䡱��ǿ
			CVector3 L(Point, LightSource[loop].L_Position);// LΪ��ʸ��
			double d = L.Magnitude();// dΪ�⴫���ľ��� 
			L = L.Normalize();//�淶����ʸ��
			CVector3 N = Normal;
			N = N.Normalize();//�淶����ʸ��
			//��1���������������
			double NdotL = MAX(DotProduct(L, N), 0);			
			I += LightSource[loop].L_Diffuse * pMaterial->M_Diffuse * NdotL;
			//��2�������뾵�淴���
			CVector3 V(Point, ViewPoint);//VΪ��ʸ��
			V = V.Normalize();//�淶����ʸ��
			CVector3 H = (L + V) / (L + V).Magnitude();// HΪ��ֵʸ��
			double NdotH = MAX(DotProduct(N, H), 0);
			double NdotV = MAX(DotProduct(N, V), 0);
			double VdotH = MAX(DotProduct(V, H), 0);
			if(NdotL > 0.0 && NdotV > 0.0)
			{
				// fresnel��
				double F = pMaterial->M_f + (1.0 - pMaterial->M_f) * pow(1.0 - VdotH, 5.0);
				//beckmann�ֲ����� 
				double r1 = 1.0 / (pMaterial->M_k * pMaterial->M_k * pow(NdotH, 4.0));
				double r2 = (NdotH * NdotH - 1.0) / (pMaterial->M_k * pMaterial->M_k * NdotH * NdotH);
				double D = r1 * exp(r2);
				//����˥��
				double Gm = (2.0 * NdotH * NdotV) / VdotH;
				double Gs = (2.0 * NdotH * NdotL) / VdotH;
				double G = MIN(1.0, MIN(Gm, Gs));				  
				double Rs = (F * D * G) / (NdotV * NdotL * PI);
				I += LightSource[loop].L_Specular * pMaterial->M_Specular * Rs;
			}
			//��3������ǿ˥��
			double c0 = LightSource[loop].L_C0;//c0Ϊ����˥������
			double c1 = LightSource[loop].L_C1;//c1Ϊ����˥������
			double c2 = LightSource[loop].L_C2;//c2Ϊ����˥������			
			double f = (1.0/(c0 + c1 * d + c2 * d * d));//��ǿ˥������
			f = MIN(1.0, f);
			ResultI += I * f;
		}
		else
			ResultI += Point.c;//����������ɫ		
	}
	//��4�������뻷����
	ResultI += Ambient * pMaterial->M_Ambient;
	//��5������ǿ�淶����[0,1]����
	ResultI.Normalize();
	//��6�������������㶥������յĹ�ǿ��ɫ
	return ResultI;
}
