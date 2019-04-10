#include "StdAfx.h"
#include "Particle.h"


CParticle::CParticle(void)
{
}

CParticle::CParticle(int number,int WIDTH,int HEIGHT)
{
	m_number=number;
	m_pSnow=new struct snow[m_number];
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
}

CParticle::~CParticle(void)
{
	delete[] m_pSnow;
}

//��png��ͼ͸��
void CParticle::TransparentPNG(CImage *png)
{
	for(int i = 0; i <png->GetWidth(); i++)
	{
		for(int j = 0; j <png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(png->GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

void CParticle::Init()
{
	//����ѩ��ͼ��
	char buf[20];
	for(int i=0;i<7;i++)    //��������ͼ��
	{
		sprintf_s(buf,"Snow//%d.png",i);//��Snow�ļ����µ�ͼƬ��ӡ���ַ���������buf��
		m_snowMap[i].Load(buf);
		TransparentPNG(&m_snowMap[i]);
	}
	//��ʼ��ѩ������
	for(int i=0;i<m_number;i++)
	{
		m_pSnow[i].x=rand()% WIDTH;   //���ѩ����ˮƽ�������������
		m_pSnow[i].y=rand()% HEIGHT; //��ֱ������Ҳ���������
		m_pSnow[i].number=rand()%7;         //����ѩ���е�һ��
		m_pSnow[i].speedx=(rand()%5+1)/30.0;
		m_pSnow[i].speedy=(rand()%5+1)/20.0;
	}
}

void CParticle::Draw(CDC &pDC)
{
	//����ѩ������
	for(int i=0;i<m_number;i++)
		m_snowMap[m_pSnow[i].number].Draw(pDC,m_pSnow[i].x,m_pSnow[i].y,32,32);
}

void CParticle::Update(double time)
{
	for(int i=0;i<m_number;i++)
	{
		m_pSnow[i].x+=time*m_pSnow[i].speedx;
		if(m_pSnow[i].x>WIDTH)
			m_pSnow[i].x=-32;  

		m_pSnow[i].y+=time*m_pSnow[i].speedy;
		if(m_pSnow[i].y>HEIGHT)
			m_pSnow[i].y=-32; 
	}
}