#pragma once
#include "P3.h"

class Bezier
{
public:
	Bezier(void);
	~Bezier(void);
	Bezier(CP3[][4]);
public:
	void ObliqueProjection();//б�Ȳ�ͶӰ
	void LeftMultiMatrix(double M0[][4],CP3 P0[][4]); //��˾���
	void RightMultiMatrix(CP3 P0[][4],double M0[][4]);//�ҳ˾���
	void TransposeMatrix(double M0[][4]);//����ת��
	void DrawObject(CDC *);//����Bezier����
	void DrawCtrlPolygon(CDC *);//���ƿ��ƶ����
public:
	CP3 P3[4][4];//��ά����
	CP2 P2[4][4];//��ά����
	double MT[4][4];//M��ת�þ���
};

