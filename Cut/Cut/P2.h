#pragma once
class CP2
{
public:
	CP2(void);
	~CP2(void);
public:
	double x;//ֱ�߶ζ˵�x����
	double y;//ֱ�߶ζ˵�y����
	UINT  rc;//ֱ�߶ζ˵����int���з��ŵ�
	//����Ϊ����������8λ��intֵ���Ǵ�-128��127.
	//uint���޷��ŵģ�ֻ��Ϊ0������������8λuint�Ǵ�0-255 
	//uint��λ����(bit manipulation)�г��õ�����~, <<, >>, &, |, ^ 
	//int  rc;//ֱ�߶ζ˵����
};

