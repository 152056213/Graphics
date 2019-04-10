#include "StdAfx.h"
#include "Material.h"

CMaterial::CMaterial(void)
{
	M_Ambient = CRGBA(0.2,0.2,0.2);//���ʶԻ�����ķ�����
	M_Diffuse = CRGBA(0.8,0.8,0.8);//���ʶ��������ķ�����
	M_Specular = CRGBA(0.0,0.0,0.0);//���ʶԾ��淴���ķ�����
	M_k = 0.0;//���ϴֲڶ�
	M_f = 1.0;//Fresnel����ϵ��
}

CMaterial::~CMaterial(void)
{

}

void CMaterial::SetAmbient(CRGBA c)
{
	M_Ambient = c;
}

void CMaterial::SetDiffuse(CRGBA c)
{
	M_Diffuse = c;
}

void CMaterial::SetSpecular(CRGBA c)
{
	M_Specular = c;
}

void CMaterial::SetEmit(CRGBA emi)
{
	M_Emit=emi;
}

void CMaterial::SetSlope(double k)
{
	M_k = k;
}

void CMaterial::SetFresnel(double f)
{
	M_f = f;
}