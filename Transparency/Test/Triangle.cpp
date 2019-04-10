#include "StdAfx.h"
#include "Triangle.h"
#include <math.h>
#define Round(d) int(floor(d+0.5))//四舍五入宏定义

CTriangle::CTriangle(void)
{
}


CTriangle::~CTriangle(void)
{
	for(int i=0;i<Width;i++)
	{
		delete[] zBuffer[i];
		zBuffer[i]=NULL;
	}
	if(zBuffer!=NULL)
	{
		delete zBuffer;
		zBuffer=NULL;
	}
}

void CTriangle::SetPoint(CP3 P0, CP3 P1, CP3 P2)
{
	point0.x = Round(P0.x);
	point0.y = Round(P0.y);
	point0.z = (P0.z);
	point0.c = P0.c;
	point0.T = P0.T;
	point1.x = Round(P1.x);
	point1.y = Round(P1.y);
	point1.z = (P1.z);
	point1.c = P1.c;
	point1.T = P1.T;
	point2.x = Round(P2.x);
	point2.y = Round(P2.y);
	point2.z = (P2.z);
	point2.c = P2.c;
	point2.T = P2.T;
}

void CTriangle::Gouraud(CDC* pDC)
{
	double	CurrentDepth = 0.0;//当前扫描线的深度
	CVector3 Vector01(point0,point1),Vector02(point0,point2);
	CVector3 Normal=CrossProduct(Vector01,Vector02);
	double A = Normal.x,B = Normal.y,C = Normal.z;//平面方程Ax+By+Cz＋D=0的系数
	double D = -A*point0.x - B*point0.y - C*point0.z;//当前扫描线随着x增长的深度步长
	double DepthStep=-A/C;//计算扫描线深度步长增量
	//三点能构成三角形
	if(point0 != point1 && point0 != point2 && point1 != point2)	//重载了 ！= 运算符
	{
		//point0点为y坐标最小的点,point1点为y坐标最大的点,point2点的y坐标位于二者之间。如果y值相同，取x最小的点
		SortVertex();
		//定义三角形覆盖的扫描线条数
		int nTotalLine = point1.y - point0.y + 1;
		//定义span的起点与终点数组
		pLeft  = new CPoint2[nTotalLine];
		pRight = new CPoint2[nTotalLine];
		
		//判断三角形与P0P1边的位置关系，0-1-2为右手系
		int nDeltz = (point1.x - point0.x) * (point2.y - point1.y) - (point1.y - point0.y) * (point2.x - point1.x);//点矢量叉积的z坐标
		if(nDeltz > 0)//三角形位于P0P1边的左侧
		{
			nIndex = 0;
			EdgeFlag(point0, point2, TRUE);
			EdgeFlag(point2, point1, TRUE);
			nIndex = 0;
			EdgeFlag(point0, point1, FALSE);
		}
		else//三角形位于P0P1边的右侧
		{
			nIndex = 0;
			EdgeFlag(point0, point1, TRUE);
			nIndex = 0;	
			EdgeFlag(point0, point2, FALSE);
			EdgeFlag(point2, point1, FALSE);
		}
		for(int y = point0.y ; y < point1.y; y++)//下闭上开
		{	
			int n = y - point0.y;
			BOOL bInFlag = FALSE;//区间内外测试标志，初始值为假表示区间外部
			for(int x = pLeft[n].x; x < pRight[n].x; x++)//左闭右开
			{
				if(bInFlag == FALSE)
				{
					CurrentDepth=-(pLeft[n].x*A+y*B+D)/C;//z=-(Ax+By-D)/C
					bInFlag = TRUE;
					x = pLeft[n].x-1;
				}
				else
				{
					CRGBA clr = ClrInterpolation(x, pLeft[n].x, pRight[n].x, pLeft[n].c, pRight[n].c);
					/*CRGBA clr;
					clr.red   = Round(pLeft[n].c.red +(pRight[n].c.red-pLeft[n].c.red)*(x-pLeft[n].x)/(pRight[n].x-pLeft[n].x));
					clr.green = Round(pLeft[n].c.green +(pRight[n].c.green-pLeft[n].c.green)*(x-pLeft[n].x)/(pRight[n].x-pLeft[n].x));
					clr.blue  = Round(pLeft[n].c.blue +(pRight[n].c.blue-pLeft[n].c.blue)*(x-pLeft[n].x)/(pRight[n].x-pLeft[n].x));*/
					double T = ClrInterpolation(x, pLeft[n].x, pRight[n].x, pLeft[n].T, pRight[n].T);
					//double T = Round(pLeft[n].T +(pRight[n].T-pLeft[n].T)*(x-pLeft[n].x)/(pRight[n].x-pLeft[n].x));
					if(CurrentDepth <= zBuffer[x + Width/2][y + Height/2])//如果当前采样点的深度小于帧缓冲器中原采样点的深度)
					{
						zBuffer[x + Width/2][y + Height/2] = CurrentDepth;//使用当前采样点的深度更新深度缓冲器
						COLORREF bclr = pDC->GetPixel(x, y);
						pDC->SetPixelV(x, y, RGB(
						T*GetRValue(bclr)+clr.red*(1-T)*255,
						T*GetGValue(bclr)+clr.green*(1-T)*255,
						T*GetBValue(bclr)+clr.blue*(1-T)*255));
						//pDC->SetPixelV(x, y, RGB(clr.red * 255, clr.green * 255, clr.blue * 255));
					}
					CurrentDepth += DepthStep;
				}
				
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
		}
		if(pLeft)
		{
			delete []pLeft;
			pLeft = NULL;
		}
		if(pRight)
		{
			delete []pRight;
			pRight = NULL;
		}
	}
}

void CTriangle::EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature)
{

	CRGBA crColor = PStart.c;
	int dx = abs(PEnd.x - PStart.x);
	int dy = abs(PEnd.y - PStart.y);
	BOOL bInterChange = FALSE;//bInterChange为假，主位移方向为x方向
	int e, s1, s2, temp;
	s1 = (PEnd.x > PStart.x) ? 1 :((PEnd.x < PStart.x) ? -1 : 0);
	s2 = (PEnd.y > PStart.y) ? 1 :((PEnd.y < PStart.y) ? -1 : 0);
	if(dy > dx)//bInterChange为真，主位移方向为y方向
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e = -dx;
	int x = PStart.x , y  = PStart.y; double T = PStart.T;
	for(int i = 0;i < dx; i++)
	{
		if(bFeature)
			pLeft[nIndex] = CPoint2(x, y, T, crColor);
		else
			pRight[nIndex] = CPoint2(x, y, T, crColor);
		if(bInterChange)
		{
			y += s2;
			crColor = ClrInterpolation(y, PStart.y, PEnd.y, PStart.c, PEnd.c);
			T = ClrInterpolation(y, PStart.y, PEnd.y, PStart.T, PEnd.T);
			if(bFeature)
				pLeft[++nIndex] = CPoint2(x, y, T, crColor);
			else
				pRight[++nIndex] = CPoint2(x, y, T, crColor);
		}
		else 
		{
			x += s1;
			crColor = ClrInterpolation(x, PStart.x, PEnd.x, PStart.c, PEnd.c);
			T = ClrInterpolation(x, PStart.x, PEnd.x, PStart.T, PEnd.T);
		}
		e += 2 * dy;
		if(e >= 0)
		{
			if(bInterChange)
			{
				x += s1;
				crColor = ClrInterpolation(y, PStart.y, PEnd.y, PStart.c, PEnd.c);
				T = ClrInterpolation(y, PStart.y, PEnd.y, PStart.T, PEnd.T);
			}
			else
			{
				y += s2;
				crColor = ClrInterpolation(x, PStart.x, PEnd.x, PStart.c, PEnd.c);
				T = ClrInterpolation(x, PStart.x, PEnd.x, PStart.T, PEnd.T);
				if(bFeature)
					pLeft[++nIndex] = CPoint2(x, y, T, crColor);
				else
					pRight[++nIndex] = CPoint2(x, y, T, crColor);
			}
			e -= 2 * dx;
		}
	}
}

CRGBA CTriangle::ClrInterpolation(double t, double mStart, double mEnd, CRGBA cStart, CRGBA cEnd)//颜色线性插值
{
	CRGBA color;
	color = (t - mEnd) / (mStart - mEnd) * cStart + (t - mStart) / (mEnd - mStart) * cEnd;
	return color;
}

double CTriangle::ClrInterpolation(double t, double mStart, double mEnd, double tStart, double tEnd)//颜色线性插值
{
	double T;
	T = (t - mEnd) / (mStart - mEnd) * tStart + (t - mStart) / (mEnd - mStart) * tEnd;
	return T;
}

void CTriangle::SortVertex()
{
	CPoint2 p[3];
	p[0] = point0;
	p[1] = point1;
	p[2]  = point2;
	for(int i = 0; i < 2; ++i)
	{
		int k = i;
		for(int j = i + 1;j < 3; ++j)
		{
			if(p[k].y > p[j].y)
				k = j;
			if(p[k].y == p[j].y)
				if(p[k].x > p[j].x)
					k = j;
		}
		if(k != i)
		{
			CPoint2 pTemp = p[i];
			p[i] = p[k];
			p[k] = pTemp;
		}
	}
	point0 = p[0];
	point1 = p[2];
	point2  = p[1];
}
void CTriangle::InitDeepBuffer(int Width,int Height,double Depth)//初始化深度缓冲
{
	this->Width=Width,this->Height=Height;
	zBuffer=new double *[Width];
	for(int i=0;i<Width;i++)
		zBuffer[i]=new double[Height];
	for(int i=0;i<Width;i++)//初始化深度缓冲
		for(int j=0;j<Height;j++)
			zBuffer[i][j]=Depth;
}