#include "StdAfx.h"
#include "ZBuffer.h"
#include "math.h"
#define Round(d) int(floor(d + 0.5))

CZBuffer::CZBuffer(void)
{
	zBuffer=NULL;
}
CZBuffer::~CZBuffer(void)
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
void CZBuffer::SetPoint(CPi3 P0,CPi3 P1,CPi3 P2,CVector3 N0,CVector3 N1,CVector3 N2)//�����γ�ʼ��
{
	point0.x = Round(P0.x);
	point0.y = Round(P0.y);
	point0.z = Round(P0.z);
	point0.c = P0.c;
	point0.N = N0;
	point1.x = Round(P1.x);
	point1.y = Round(P1.y);
	point1.z = Round(P1.z);
	point1.c = P1.c;
	point1.N = N1;
	point2.x = Round(P2.x);
	point2.y = Round(P2.y);
	point2.z = Round(P2.z);
	point2.c = P2.c;
	point2.N = N2;
	V0 = P0, V1 = P1, V2 = P2;
}

void CZBuffer::PhongShading(CDC* pDC,CP3 ViewPoint,CLighting* pLight,CMaterial* pMaterial,BOOL Sign)
{
	double	CurrentDepth = 0.0;//��ǰɨ���ߵ����
	CVector3 Vector01(V0,V1),Vector02(V0, V2);
	CVector3 fNormal = Cross(Vector01,Vector02);
	double A = fNormal.x, B = fNormal.y, C = fNormal.z;//ƽ�淽��Ax+By+Cz��D=0��ϵ��
	double D = -A * V0.x - B * V0.y - C * V0.z;//��ǰɨ��������x��������Ȳ���
	if (fabs(C) < 1e-4)
		C = 1.0;
	double DepthStep = -A/C;//����ɨ������Ȳ�������
	//�����ܹ���������
	if(point0 != point1 && point0 != point2 && point1 != point2)	//������ ��= �����
	{
		//point0��Ϊy������С�ĵ�,point1��Ϊy�������ĵ�,point2���y����λ�ڶ���֮�䡣���yֵ��ͬ��ȡx��С�ĵ�
		SortVertex();
		//���������θ��ǵ�ɨ��������
		int nTotalLine = point1.y - point0.y + 1;
		//����span��������յ�����
		pLeft  = new CPoint2[nTotalLine];
		pRight = new CPoint2[nTotalLine];		
		//�ж���������P0P1�ߵ�λ�ù�ϵ��0-1-2Ϊ����ϵ
		int nDeltz = (point1.x - point0.x) * (point2.y - point1.y) - (point1.y - point0.y) * (point2.x - point1.x);//��ʸ�������z����
		if(nDeltz > 0)//������λ��P0P1�ߵ����
		{
			nIndex = 0;
			EdgeFlag(point0, point2, TRUE);
			EdgeFlag(point2, point1, TRUE);
			nIndex = 0;
			EdgeFlag(point0, point1, FALSE);
		}
		else//������λ��P0P1�ߵ��Ҳ�
		{
			nIndex = 0;
			EdgeFlag(point0, point1, TRUE);
			nIndex = 0;	
			EdgeFlag(point0, point2, FALSE);
			EdgeFlag(point2, point1, FALSE);
		}
		for(int y = point0.y ; y < point1.y; y++)//�±��Ͽ�
		{	
			int n = y - point0.y;
			BOOL bInFlag = FALSE;//���������Ա�־����ʼֵΪ�ٱ�ʾ�������ⲿ
			for(int x = pLeft[n].x; x < pRight[n].x; x++)//����ҿ�
			{
				if(bInFlag == FALSE)
				{
					CurrentDepth = -(A*x + B*y +D)/C;//z=-(Ax+By+D)/C
					bInFlag = TRUE;
					x -= 1;
				}
				else
				{
					CVector3 ptNormal = LinearInterpolation (x, pLeft[n].x, pRight[n].x, pLeft[n].N, pRight[n].N);
					ptNormal = ptNormal.Normalize();
					CRGB clr = pLight->Lighting(ViewPoint,CP3(Round(x),y,CurrentDepth),ptNormal,pMaterial,Sign);
					if(CurrentDepth<=zBuffer[Round(x)+Width/2][Round(y)+Height/2])//�����ǰ����������С��֡��������ԭ����������
					{
						zBuffer[Round(x)+Width/2][Round(y)+Height/2]=CurrentDepth;//ʹ�õ�ǰ���������ȸ�����Ȼ�����
						if(Sign)
							pDC->SetPixelV(Round(x)+200,Round(y),RGB(clr.red*255,clr.green*255,clr.blue*255));//���Ƶ�ǰ������
						else
							pDC->SetPixelV(Round(x)-200,Round(y),RGB(clr.red*255,clr.green*255,clr.blue*255));//���Ƶ�ǰ������
					}
					CurrentDepth+=DepthStep;
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

void CZBuffer::EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature)
{
	CVector3 ptNormal = PStart.N;
	int dx = abs(PEnd.x - PStart.x);
	int dy = abs(PEnd.y - PStart.y);
	BOOL bInterChange = FALSE;//bInterChangeΪ�٣���λ�Ʒ���Ϊx����
	int e, s1, s2, temp;
	s1 = (PEnd.x > PStart.x) ? 1 :((PEnd.x < PStart.x) ? -1 : 0);
	s2 = (PEnd.y > PStart.y) ? 1 :((PEnd.y < PStart.y) ? -1 : 0);
	if(dy > dx)//bInterChangeΪ�棬��λ�Ʒ���Ϊy����
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e = -dx;
	int x = PStart.x , y  = PStart.y;
	for(int i = 0;i < dx; i++)
	{
		if(bFeature)
			pLeft[nIndex] = CPoint2(x, y, ptNormal);
		else
			pRight[nIndex] = CPoint2(x, y, ptNormal);
		if(bInterChange)
		{
			y += s2;
			ptNormal = LinearInterpolation(y, PStart.y, PEnd.y, PStart.N, PEnd.N);
			if(bFeature)
				pLeft[++nIndex] = CPoint2(x, y, ptNormal);
			else
				pRight[++nIndex] = CPoint2(x, y, ptNormal);
		}
		else 
		{
			x += s1;
			ptNormal = LinearInterpolation(x, PStart.x, PEnd.x, PStart.N, PEnd.N);			
		}
		e += 2 * dy;
		if(e >= 0)
		{
			if(bInterChange)
			{
				x += s1;
				ptNormal = LinearInterpolation(y, PStart.y, PEnd.y, PStart.N, PEnd.N);
			}
			else
			{
				y += s2;
				ptNormal = LinearInterpolation(x, PStart.x, PEnd.x, PStart.N, PEnd.N);
				if(bFeature)
					pLeft[++nIndex] = CPoint2(x, y, ptNormal);
				else
					pRight[++nIndex] = CPoint2(x, y, ptNormal);
			}
			e -= 2 * dx;
		}
	}
}

CRGB CZBuffer::LinearInterpolation (double t, double tStart, double tEnd, CRGB intensityStart, CRGB intensityEnd)//��ǿ���Բ�ֵ
{
	CRGB Intensity;
	Intensity = (tEnd - t) / (tEnd - tStart) * intensityStart + (t - tStart) / (tEnd - tStart) * intensityEnd;
	return Intensity;
}

CVector3 CZBuffer::LinearInterpolation (double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd)//��ǿ���Բ�ֵ
{
	CVector3 vector;
	vector = (tEnd - t) / (tEnd - tStart) * vStart + (t - tStart) / (tEnd - tStart) * vEnd;
	return vector;
}

void CZBuffer::SortVertex()
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

void CZBuffer::InitDeepBuffer(int Width,int Height,double Depth)//��ʼ����Ȼ���
{
	this->Width=Width,this->Height=Height;
	zBuffer=new double *[Width];
	for(int i=0;i<Width;i++)
		zBuffer[i]=new double[Height];
	for(int i=0;i<Width;i++)//��ʼ����Ȼ���
		for(int j=0;j<Height;j++)
			zBuffer[i][j]=Depth;
}