#pragma once
#include "RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	~CMaterial(void);
	void SetAmbient(CRGB);   //设置材质对环境光的反射率
	void SetDiffuse(CRGB);   //设置材质对漫反射光的反射率
	void SetSpecular(CRGB);  //设置材质对镜面反射光的反射率
	void SetEmit(CRGB);      //设置材质自身辐射的颜色
	void SetExp(double);     //设置材质的高光指数
public:
	CRGB M_Ambient;      //材质对环境光的反射率       
	CRGB M_Diffuse;		 //材质对漫反射光的反射率
	CRGB M_Specular;	 //材质对镜面反射光的反射率
	CRGB M_Emit;         //材质自身辐射的颜色
	double M_n;        //高光指数
};

