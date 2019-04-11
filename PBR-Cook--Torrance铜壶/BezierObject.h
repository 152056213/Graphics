// BeierObject.h: interface for the CBeierObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEIEROBJECT_H__2B94CB06_D142_4F4B_855F_B7858A69C41E__INCLUDED_)
#define AFX_BEIEROBJECT_H__2B94CB06_D142_4F4B_855F_B7858A69C41E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"
#include "Matrix44.h"
#include "Projection.h"
#include "Transform3.h"
#include "Face.h"
#include"Vector3.h"
#include "ZBuffer.h"
#include "Lighting.h"
#include "Material.h"
class CBezierObject  
{
public:
	CBezierObject();

	virtual ~CBezierObject();
public:
    void ReadBeizerObject(int num,CP3 **P);

	void ReadVertex();//������ƶ���ζ���
	void ReadPatch();//����˫��������Ƭ
	void LeftMultiplyMatrix(CMatrix44 M, CP3* P); //��˾���
	void RightMultiMatrix(CP3* P, CMatrix44 M);//�ҳ˾���
	void DrawObject(CDC* pDC);//����Bezier����Ƭ
	void DrawControlGrid(CDC* pDC);//���ƿ�������
	void BicubicCurvedSurface(CDC* pDC,int NumObject,int m);//˫��������Ƭ
	void ControlGrid(CDC* pDC);//��������
    void DrawFace(CDC *pDC,int NumObject,bool sign);

    void DrawFaceP4(CDC *pDC,CP3 P4[4],bool sign);
	int NumObject;//�����м�����
	CP3 **Vertex; 
	CP3 **P;
	CP3 P3[16];//��ά���Ƶ�
	CP2 P2[16];//��ά���Ƶ�
	CFace **Patch;  //���ƶ������
	CP3 **FacePoint; //�������� ��� ���
	CProjection projection;//ͶӰ����
	int	 LightNum;//��Դ����
	CLighting *pLight;//���ջ���

	CMaterial *pMaterial1;//�������
	CZBuffer *zbuf;
};

#endif // !defined(AFX_BEIEROBJECT_H__2B94CB06_D142_4F4B_855F_B7858A69C41E__INCLUDED_)
