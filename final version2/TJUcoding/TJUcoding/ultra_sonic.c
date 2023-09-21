#include <ultra_sonic.h>

float Distance = 0;

long Measure_Distance(void)//�����������
{   
	//TR1 = 0;
	long int dis = 0;
	Timer1Init(); //���ö�ʱ��0
	TL0 = 0;
	//TH1 = 0;
	TH0 = 0;
	StartModule(); //����������
	
	while(!Echo);	//�ȴ��������ķ�������
	
	TR0 = 1;      //�򿪶�ʱ������ʼ��ʱ
	while(Echo);  //�ȴ��������ķ����������
	TR0 = 0;      //��ʱ����
	
//	Distance = ((TH1*256+TL1)*VELOCITY)/2+1.5; //�������
	dis = TH0;		//��������߰�λ
	dis <<= 8;		//����ʮ��λ�ĸ߰�λ
	dis |= TL0;	//��Ͱ�λ�ϲ�
	Distance = dis * 0.0172;//��λcm
	return Distance;
}

void StartModule() //����һ�γ�����ģ��
{
	Trig = 1;
	Delay20us();
	Trig = 0;
}


void Timer1Init(void)
{
	//TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	
	//TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TMOD &= 0xF0;
	TMOD |= 0x01;
	//TL1 = 0;
	TL0 = 0;
	//TH1 = 0;
	TH0 = 0;
}

void Delay20us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	i = 7;
	while (--i);
}
