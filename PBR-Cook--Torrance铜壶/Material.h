// Material.h: interface for the CMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATERIAL_H__3EED0CA6_44EC_4729_8322_40321CE68965__INCLUDED_)
#define AFX_MATERIAL_H__3EED0CA6_44EC_4729_8322_40321CE68965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	~CMaterial(void);
public:
	void SetAmbient(CRGB);//���ò��ʶԻ�����ķ�����
	void SetDiffuse(CRGB);//���ò��ʶ��������ķ�����
	void SetSpecular(CRGB);//���ò��ʶԾ��淴���ķ�����
	void SetEmit(CRGB);//���ò�������������ɫ
	void SetExp(double);//���ò��ʵĸ߹�ָ��	
	void SetRough(double);//���ò��ʵĴֲڶ�
	void SetFresnel(double);//���ò��ʵķ���������ϵ������ʾ���䷽���ϵĹ�ǿռԭʼ��ǿ�ı���
public:
	CRGB M_Ambient;//���ʶԻ�����ķ�����
	CRGB M_Diffuse;//���ʶ��������ķ�����
	CRGB M_Specular;//���ʶԾ��淴���ķ�����
	CRGB M_Emit;//��������������ɫ
	double M_n;//���ʵĸ߹�ָ��
	double M_m;//���ʵĴֲڶ�
	double M_f;//����������ϵ��
};

#endif // !defined(AFX_MATERIAL_H__3EED0CA6_44EC_4729_8322_40321CE68965__INCLUDED_)
