#pragma once
#include "P3.h"
#include "Vector.h"
#include "Lighting.h"
class CBicubicBezierPatch
{
public:
	CBicubicBezierPatch(void);
	~CBicubicBezierPatch(void);
	void ReadControlPoint(CP3 P[4][4]);//����16�����Ƶ�
	void DrawCurvedPatch(CDC* pDC,CP3 ViewPoint,CLighting *pLight,CMaterial *pMaterial);//����˫����Bezier����Ƭ
	void DrawControlGrid(CDC* pDC);//���ƿ�������
private:
	void LeftMultiplyMatrix(double M[][4],CP3 P[][4]);//��˶������
	void RightMultiplyMatrix(CP3 P[][4],double M[][4]);//�ҳ˶������
	void TransposeMatrix(double M[][4]);//ת�þ���
	CP2 ObliqueProjection(CP3 Point3);//б����ͶӰ
public:
	CP3 P[4][4];//��ά���Ƶ�
	CP3 PV[121];
	CVector NV[121];
};
