#include "StdAfx.h"
#include "Lighting.h"
#include <math.h>
#define  PI  3.14159265
#define  MIN(a,b)  ((a<b)?(a):(b))
#define  MAX(a,b)  ((a>b)?(a):(b))

CLighting::CLighting()
{
	LightNum=1;
	Light=new CLight[LightNum];
	Ambient=CRGB(0.3,0.3,0.3);//������㶨����
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

CRGB CLighting::Lighting(CP3 ViewPoint,CP3 Point,CVector Normal,CMaterial *pMaterial,BOOL M,CRGB InitC)
{
	

	if(M)
	{
		LastC=pMaterial->M_Emit;//��������ɢɫΪ��ʼֵ	
		 for(int i=0;i<LightNum;i++)//���Թ�Դ
		{	
		if(Light[i].L_OnOff)
		{	
			
			CVector VL(Point,Light[i].L_Position);//VLΪָ���Դ��ʸ��
			double d=VL.Mag();//dΪ�⴫���ľ��룬���ڹ�ʸ��VL��ģ
			VL=VL.Normalize();//��λ����ʸ��
			CVector VN=Normal;
			VN=VN.Normalize();//��λ����ʸ��			
			//��1���������������
			double CosTheta=MAX(Dot(VL,VN),0);			
			InitC+=Light[i].L_Diffuse*pMaterial->M_Diffuse*CosTheta;
			
			//��2�������뾵�淴���
				//CVector VV(Point,ViewPoint);//VVΪ��ʸ��
				//VV=VV.Normalize();//��λ����ʸ��
				//CVector VH=(VL+VV)/(VL+VV).Mag();//VHΪƽ��ʸ��	
				//double nHN=pow(max(Dot(VH,VN),0),pMaterial->M_n);
				//InitC+=Light[i].L_Specular*pMaterial->M_Specular*nHN;
			
			//��3������ǿ˥��
			//double c0=Light[i].L_C0;//c0Ϊ����˥������
			//double c1=Light[i].L_C1;//c1����˥������
			//double c2=Light[i].L_C2;//c2����˥������			
			//double f=(1.0/(c0+c1*d+c2*d*d));//��ǿ˥������
			//f=MIN(1.0,f);		
			//LastC+=InitC*f;		
		}
		else
			LastC+=Point.c;//����������ɫ		
	}
	//��4�������뻷����
		LastC+=Ambient*pMaterial->M_Ambient;
		LastC.Normalize();		
	//��6�������������㶥��Ĺ�ǿ��ɫ
	return LastC;

	}
	else
	{
		  for(int i=0;i<LightNum;i++)//���Թ�Դ
		{	
			if(Light[i].L_OnOff)
			{
			CVector VL(Point,Light[i].L_Position);//VLΪָ���Դ��ʸ��
			double d=VL.Mag();//dΪ�⴫���ľ��룬���ڹ�ʸ��VL��ģ
			VL=VL.Normalize();//��λ����ʸ��
			CVector VN=Normal;
			VN=VN.Normalize();//��λ����ʸ��	
			CVector VV(Point,ViewPoint);//VVΪ��ʸ��
			VV=VV.Normalize();//��λ����ʸ��
			CVector VH=(VL+VV)/(VL+VV).Mag();//VHΪƽ��ʸ��	
			double nHN=pow(max(Dot(VH,VN),0),pMaterial->M_n);
			InitC+=Light[i].L_Specular*pMaterial->M_Specular*nHN;
			double c0=Light[i].L_C0;//c0Ϊ����˥������
			double c1=Light[i].L_C1;//c1����˥������
			double c2=Light[i].L_C2;//c2����˥������			
			double f=(1.0/(c0+c1*d+c2*d*d));//��ǿ˥������
			f=MIN(1.0,f);		
			LastC+=InitC*f;
			
			}
		 }
			LastC.Normalize();
			return LastC; 
		 
	}
		
}