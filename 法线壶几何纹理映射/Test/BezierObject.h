#pragma once
#include "P3.h"
#include "Matrix44.h"
#include "Projection.h"
#include "Transform.h"
#include "Face.h"
#include"Vector.h"
#include "ZBuffer.h"
#include "Lighting.h"
#include "Material.h"
#include "T2.h" 
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
	void DrawObject(CDC* pDC,CVector **N,int nWidth,int nHeight);//����Bezier����Ƭ
	void DrawControlGrid(CDC* pDC);//���ƿ�������
	void BicubicCurvedSurface(CDC* pDC,int NumObject,int m,int nWidth,int nHeight);//˫��������Ƭ
	void ControlGrid(CDC* pDC);//��������
    void DrawFace(CDC *pDC,int NumObject,bool sign);

    void DrawFaceP4(CDC *pDC,CP3 P4[4],CT2 tP4[4],bool sign);
	int NumObject;//�����м�����
	CP3 **Vertex; 
	CP3 **P;
	CP3 P3[16];//��ά���Ƶ�
	CP2 P2[16];//��ά���Ƶ�
	CFace **Patch;  //���ƶ������
	CP3 **FacePoint; //�������� ��� ���
	CT2 **FaceTPoint; //�������� ��� ���
	CProjection projection;//ͶӰ����
	int	 LightNum;//��Դ����
	CLighting *pLight;//���ջ���

	CMaterial *pMaterial1;//�������
	CZBuffer *zbuf;
};

