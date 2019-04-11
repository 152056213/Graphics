#pragma once

struct snow
{
	double x;
	double y;
	double speedx; //x�����ٶ�
	double speedy; //y�����ٶ�
	int number;  //����ͼ����
};

class CParticle
{
public:
	CParticle(void);
	~CParticle(void);
	CParticle(int number,int WIDTH,int HEIGHT);
	void TransparentPNG(CImage *);//��png��ͼ͸��
	void Init();  //��ʼ������
	void Draw(CDC &pDC);  //��������
	void Update(double time);//��������
private:
	int WIDTH,HEIGHT;
	int m_number; //����
	struct snow *m_pSnow;  //ѩ��
	CImage m_snowMap[7]; //����ѩ��ͼ��
};

