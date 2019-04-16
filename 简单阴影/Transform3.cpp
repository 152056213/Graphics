#include "StdAfx.h"
#include "Transform3.h"

#include<cmath>
#define PI 3.1415926
#include "Transform3.h"


CTransform3::CTransform3(void)
{

}

CTransform3::~CTransform3(void)
{
}

void CTransform3::Identity()//��λ�����ʼ��
{
	T[0][0]=1.0;T[0][1]=0.0;T[0][2]=0.0;T[0][3]=0.0;
	T[1][0]=0.0;T[1][1]=1.0;T[1][2]=0.0;T[1][3]=0.0;
	T[2][0]=0.0;T[2][1]=0.0;T[2][2]=1.0;T[2][3]=0.0;
	T[3][0]=0.0;T[3][1]=0.0;T[3][2]=0.0;T[3][3]=1.0;
}

void CTransform3::SetMatrix(CP3* P,int ptNumber)//���������ʼ��
{
	this->P=P;
	this->ptNumber=ptNumber;
}

void CTransform3::Translate(double tx,double ty,double tz)//ƽ�Ʊ任
{
	Identity();
	T[0][3]=tx;
	T[1][3]=ty;
	T[2][3]=tz;
	MultiplyMatrix();
}

void CTransform3::Scale(double sx,double sy,double sz)//�����任
{
	Identity();
	T[0][0]=sx;
	T[1][1]=sy;
	T[2][2]=sz;
	MultiplyMatrix();
}

void CTransform3::Scale(double sx,double sy,double sz,CP3 p)//����������ı����任
{
	Translate(-p.x,-p.y,-p.z);
	Scale(sx,sy,sz);
	Translate(p.x,p.y,p.z);
}
void CTransform3::RotateX(double beta)//��X����ת�任
{
	Identity();
	double rad=beta*PI/180;
	T[1][1]=cos(rad);T[1][2]=-sin(rad);
	T[2][1]=sin(rad);T[2][2]=cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateY(double beta)//��Y����ת�任
{
	Identity();
	double rad=beta*PI/180;
	T[0][0]=cos(rad); T[0][2]=sin(rad);
	T[2][0]=-sin(rad);T[2][2]=cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateZ(double beta)//��Z����ת�任
{
	Identity();
	double rad=beta*PI/180;
	T[0][0]=cos(rad);T[0][1]=-sin(rad);
	T[1][0]=sin(rad);T[1][1]=cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateX(double beta,CP3 p)//�����������X����ת�任
{
	Translate(-p.x,-p.y,-p.z);
	RotateX(beta);
	Translate(p.x,p.y,p.z);
}

void CTransform3::RotateY(double beta,CP3 p)//�����������Y����ת�任
{
	Translate(-p.x,-p.y,-p.z);
	RotateY(beta);
	Translate(p.x,p.y,p.z);
}

void CTransform3::RotateZ(double beta,CP3 p)//�����������Z����ת�任
{
	Translate(-p.x,-p.y,-p.z);
	RotateZ(beta);
	Translate(p.x,p.y,p.z);
}

void CTransform3::ReflectX()//X�ᷴ��任
{
	Identity();
	T[1][1]=-1;
	T[2][2]=-1;
	MultiplyMatrix();
}

void CTransform3::ReflectY()//Y�ᷴ��任
{
	Identity();
	T[0][0]=-1;
	T[2][2]=-1;
	MultiplyMatrix();
}

void CTransform3::ReflectZ()//Z�ᷴ��任
{
	Identity();
	T[0][0]=-1;
	T[1][1]=-1;
	MultiplyMatrix();
}

void CTransform3::ReflectXOY()//XOY�淴��任
{
	Identity();
	T[2][2]=-1;
	MultiplyMatrix();
}

void CTransform3::ReflectYOZ()//YOZ�淴��任
{
	Identity();
	T[0][0]=-1;
	MultiplyMatrix();
}

void CTransform3::ReflectZOX()//XOZ�淴��任
{
	Identity();
	T[1][1]=-1;
	MultiplyMatrix();
}
	
void CTransform3::ShearX(double b,double c)//X������б任
{
	Identity();
	T[0][1]=b;T[0][2]=c;
	MultiplyMatrix();
}

void CTransform3::ShearY(double d,double f)//Y������б任
{
	Identity();
	T[1][0]=d;T[1][2]=f;
	MultiplyMatrix();
}

void CTransform3::ShearZ(double g,double h)//Z������б任
{
	Identity();
	T[2][0]=g;T[2][1]=h;
	MultiplyMatrix();
}

void CTransform3::MultiplyMatrix()//�������
{
	CP3* PTemp=new CP3[ptNumber];
	for(int i=0;i<ptNumber;i++)
		PTemp[i]=P[i];
	for(int i=0;i<ptNumber;i++)
	{	
		P[i].x=T[0][0]*PTemp[i].x + T[0][1]*PTemp[i].y + T[0][2]*PTemp[i].z + T[0][3]*PTemp[i].w;
		P[i].y=T[1][0]*PTemp[i].x + T[1][1]*PTemp[i].y + T[1][2]*PTemp[i].z + T[1][3]*PTemp[i].w;
		P[i].z=T[2][0]*PTemp[i].x + T[2][1]*PTemp[i].y + T[2][2]*PTemp[i].z + T[2][3]*PTemp[i].w;
		P[i].w=T[3][0]*PTemp[i].x + T[3][1]*PTemp[i].y + T[3][2]*PTemp[i].z + T[3][3]*PTemp[i].w;
	}
	delete []PTemp;
}
