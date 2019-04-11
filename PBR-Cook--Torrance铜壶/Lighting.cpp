// Lighting.cpp: implementation of the CLighting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "test.h"
#include "Lighting.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "math.h"
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))
#define  PI  3.14159265
CLighting::CLighting()
{
	LightNum=1;
	Light=new CLight[LightNum];
	Ambient=CRGB(1.0,1.0,1.0);//������㶨����
}

CLighting::~CLighting()
{
	if(Light)
	{
		delete []Light;
		Light=NULL;
	}
}
void CLighting::SetLightNumber(int lnum)
{
	if(Light)
		delete []Light;
	LightNum=lnum;
	Light=new CLight[lnum];
}

CLighting::CLighting(int lnum)
{
	LightNum=lnum;
	Light=new CLight[lnum];
	Ambient=CRGB(0.3,0.3,0.3);	
}

CRGB CLighting::Lighting(CP3 ViewPoint,CP3 Point,CVector3 Normal,CMaterial *pMaterial,BOOL Sign)
{
	CRGB LastC=pMaterial->M_Emit;//��������ɢɫΪ��ʼֵ
	for(int i=0;i<LightNum;i++)//���Թ�Դ
	{
		if(Light[i].L_OnOff)
		{
			CRGB InitC;
			InitC.red=0.0,InitC.green=0.0,InitC.blue=0.0;
			CVector3 VL(Point,Light[i].L_Position);//ָ���Դ��ʸ��
			double d=VL.Mag();//�⴫���ľ��룬����ʸ��VL��ģ
			VL=VL.Normalize();//��λ����ʸ��
			CVector3 VN=Normal;
			VN=VN.Normalize();//��λ����ʸ��
			double NdotL = MAX(Dot(VL, VN), 0.0);
			//��1���������������
			if(Light[i].b_Diffuse)
			{
				//double CosTheta=MAX(Dot(VL,VN),0);
				InitC.red+=Light[i].L_Diffuse.red*pMaterial->M_Diffuse.red*NdotL;
				InitC.green+=Light[i].L_Diffuse.green*pMaterial->M_Diffuse.green*NdotL;
				InitC.blue+=Light[i].L_Diffuse.blue*pMaterial->M_Diffuse.blue*NdotL;
			}
			if(Sign)
			{
				//��2�������뾵�淴���
				if(Light[i].b_Specular)
				{
					CVector3 VV(Point,ViewPoint);//VVΪ��ʸ��
					VV=VV.Normalize();//��λ����ʸ��
					CVector3 VH=(VL+VV)/(VL+VV).Mag();//ƽ��ʸ��
					double nHN=pow(MAX(Dot(VH,VN),0),pMaterial->M_n);
					InitC.red+=Light[i].L_Specular.red*pMaterial->M_Specular.red*nHN;
					InitC.green+=Light[i].L_Specular.green*pMaterial->M_Specular.green*nHN;
					InitC.blue+=Light[i].L_Specular.blue*pMaterial->M_Specular.blue*nHN;		
				}
			}
			else
			{
				if(Light[i].b_Specular)
				{
					CVector3 VV(Point,ViewPoint);//VVΪ��ʸ��
					VV=VV.Normalize();//��λ����ʸ��
					CVector3 VH=(VL+VV)/(VL+VV).Mag();//ƽ��ʸ��
					double NdotH = MAX(Dot(VN, VH), 0.0);
					double NdotV = MAX(Dot(VN, VV), 0.0);
					double VdotH = MAX(Dot(VV, VH), 0.0);
					if(NdotL > 0.0 && NdotV > 0.0)
					{
						//geometric attenuation ����˥��
						double NH2 = 2.0 * NdotH;
						double g1 = (NH2 * NdotV) / VdotH;
						double g2 = (NH2 * NdotL) / VdotH;
						double geoAtt = MIN(1.0, MIN(g1, g2));
						// beckmann distribution function �������ֲ����� 
						double r1 = 1.0 / (pow(pMaterial->M_m, 2) * pow(NdotH, 4.0));
						double r2 = (NdotH * NdotH - 1.0) / (pow(pMaterial->M_m, 2) * pow(NdotH, 2));
						double roughness = r1 * exp(r2);
						// fresnel Schlick approximation  ������������ʹ��Schlick�ƽ�
						double fresnel = pMaterial->M_f + pow(1.0 - VdotH, 5.0) * (1.0 - pMaterial->M_f);
						double Rs = (fresnel * geoAtt * roughness) / (NdotV * NdotL * 4);

						InitC.red += Light[i].L_Specular.red * pMaterial->M_Specular.red * Rs;
						InitC.green += Light[i].L_Specular.green * pMaterial->M_Specular.green * Rs;
						InitC.blue += Light[i].L_Specular.blue * pMaterial->M_Specular.blue * Rs;
					}
				}
			}
			//LastC+=InitC;
			//��3������ǿ˥��
			double c0=Light[i].L_C0;//c0Ϊ����˥������
			double c1=Light[i].L_C1;//c1����˥������
			double c2=Light[i].L_C2;//c2����˥������
			double f=(1.0/(c0+c1*d+c2*d*d));//��ǿ˥������
			f=MIN(1.0,f);
			LastC+=InitC*f;
		}
		else
			LastC+=Point.c;//����������ɫ
	}
	//��4�������뻷����
	if(Light[0].b_Ambient)
		LastC+=Ambient*pMaterial->M_Ambient;
	//��5������ɫ��һ����[0,1]����
	LastC.Normalize();
	//��6�������������㶥��Ĺ�ǿ��ɫ
	return LastC;
}