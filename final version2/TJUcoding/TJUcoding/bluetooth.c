#include <bluetooth.h>
#include "oled.h"

int RETURN_FLAG = 0;	//ģʽ�л�����
//����FLAG = 1ʱ�л���=0��������
int PATTERN = 0;	//ģʽ������ʼ��
char Flag_BluetoothCar = 's';
unsigned char m;

void Bluetooth_Init()//����ģ���ʼ��
{
   
   //	SCON = 0x50; 	// SCON: ģʽ1, 8-bit UART
////������9600��11.0592MHz
////	TMOD |= 0x20;
////	TH1=0xfd; 		
////	TL1=0xfd;
//	
////������9600��12MHz
//	T2CON = 0x34;	//RCLK��TCLK��TR2��1
//	RCAP2L = 0xD9;	//9600�����ʶ�Ӧ FFD9����λΪD9
//    RCAP2H = 0xFF;	//��λΪFF
//	EA = 1;	    	//�����ж�
//	ES = 1; 		//�򿪴����ж�
//	PS = 1;			//���ڵ����ȼ���1
	
//    PCON |= 0x80;	//ʹ�ܲ����ʱ���λSMOD
//	SCON = 0x50;		//8λ����,�ɱ䲨���ʣ��ɽ�������
//	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
//	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
//	TL1 = 0xF3;		//�趨��ʱ��ֵ
//	TH1 = 0xF3;		//�趨��ʱ����װֵ
//	ET1 = 0;		//��ֹ��ʱ��1�ж�
//	TR1 = 1;		//������ʱ��1

	
    PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD//9600bps@11.0592MHz
    SCON = 0x50;		//8λ����,�ɱ䲨����
	//AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	//AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	//TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD &= 0x00;
	//TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TMOD |= 0x21;
	TL1 = 0xFA;		//�趨��ʱ��ֵ
	TH1 = 0xFA;		//�趨��ʱ����װֵ
	TL0 = 0x00;
	//TH1 = 0;
	TH0 = 0x00;
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
//	TMOD &= 0xF0;
//	TMOD |= 0x01;
//	//TL1 = 0;
//	TL0 = 0x00;
//	//TH1 = 0;
//	TH0 = 0x00;
	
//	PCON &= 0x7F;		//�����ʲ�����
//	SCON = 0x50;		//8λ����,�ɱ䲨����
//	//AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
//	//AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
//	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
//	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
//	TL1 = 0xFD;		//�趨��ʱ��ֵ
//	TH1 = 0xFD;		//�趨��ʱ����װֵ
//	ET1 = 0;		//��ֹ��ʱ��1�ж�
//	TR1 = 1;		//������ʱ��1
//	
//	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD//9600bps@12.000MHz
//	SCON = 0x50;		//8λ����,�ɱ䲨����
//	//AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
//	//AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
//	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
//	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
//	TL1 = 0xF9;		//�趨��ʱ��ֵ
//	TH1 = 0xF9;		//�趨��ʱ����װֵ
//	ET1 = 0;		//��ֹ��ʱ��1�ж�
//	TR1 = 1;		//������ʱ��1
//	
//	PCON &= 0x7F;		//�����ʲ�����
//	SCON = 0x50;		//8λ����,�ɱ䲨����
//	//AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
//	//AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
//	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
//	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
//	TL1 = 0xFD;		//�趨��ʱ��ֵ
//	TH1 = 0xFD;		//�趨��ʱ����װֵ
//	ET1 = 0;		//��ֹ��ʱ��1�ж�
//	TR1 = 1;		//������ʱ��1
    ES=1;		//���������ж�
	EA=1;		//�ж��ܿ��ش�
	PS=1;
}



void BluetoothControlCar(void)
{
	switch(Flag_BluetoothCar)
	{
		case 'f': Motor_Left(1,45); Motor_Right(1,45); break;
		case 'b': Motor_Left(0,45); Motor_Right(0,45); break;
		case 'l': Motor_Left(0,25); Motor_Right(1,40); break;
		case 'r': Motor_Left(1,40); Motor_Right(0,25); break;
		case 's': Motor_Stop();  break;
		default:break;
	}
}

//void UART_SER () interrupt 4
//{
//	unsigned char n;
//	RI=0;
//	n = SBUF;
//	//���һ����־
//	switch (n)
//		{
//		case '0':PATTERN = 0; RETURN_FLAG = 1; break; 	//��Ϣģʽ����ʼ��ģʽ��
//		case '1':PATTERN = 1; RETURN_FLAG = 1; break;	//С�����ת��
//		case '2':PATTERN = 2; RETURN_FLAG = 1; break;	//ѭ��ģʽ
//		case '3':PATTERN = 3; RETURN_FLAG = 1; break;	//����������OLED��ʾ
//		case '4':PATTERN = 4; RETURN_FLAG = 1; break; 	//ѭ���ӳ�������
//		case '5':PATTERN = 5; RETURN_FLAG = 1; break;	//����ң��
//		case 'f':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'f'; break;	//ǰ��
//		case 'b':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'b'; break;	//����
//		case 'l':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'l'; break;	//��ת
//		case 'r':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'r'; break;	//��ת
//		case 's':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 's'; break;	//ֹͣ
//		default:break;
//		}
//	}

//unsigned char Read_SBUF()
//{
//	return m;
//	
//}	

void UART_SER() interrupt 4//�����ж����Ϊ4
{
	if(RI==1)
		{
			RI=0;//��RI�����жϹ���
			//Read_SBUF();
			m=SBUF;//��������ֱ�Ӹ���P2
			//UART_Change=1;
			
			//UART_sendByte(agency);//�������������·�����
			switch (m)
		{
		case '0':PATTERN = 0; 
			RETURN_FLAG = 1;
			OLED_CLS();
	OLED_P8x16Str(0, 0, "Quiet", 0);
	OLED_Show16x16(48, 3, 0, 0);
	OLED_Show16x16(64, 3, 1, 0);
			break; 	//��Ϣģʽ����ʼ��ģʽ��
		//case '1':PATTERN = 1; RETURN_FLAG = 1; break;	//С�����ת��
		case '2':
			//TR1 = 1;
			//Bluetooth_Init();
		PATTERN = 2; 
			RETURN_FLAG = 1; 
			OLED_CLS();
	   OLED_P8x16Str(0, 0, "Tracking", 0);
	   OLED_Show16x16(48, 3, 2, 0);
	   OLED_Show16x16(64, 3, 3, 0);
			break;	//ѭ��ģʽ
		case '3':
			
		PATTERN = 3;
			RETURN_FLAG = 1;
			
            OLED_CLS();
	        OLED_P8x16Str(0, 0, "Distance:", 0);
			break;	//����������OLED��ʾ
		case '4':PATTERN = 4; 
		RETURN_FLAG = 1; 
		OLED_CLS();
	    OLED_P8x16Str(0, 0, "UnicTrac", 0);
		break; 	//ѭ���ӳ�������
		case '5':PATTERN = 5;
			RETURN_FLAG = 1;
			OLED_CLS();
	        OLED_P8x16Str(0, 0, "BTCon", 0);
	        OLED_Show16x16(48, 3, 4, 0);
	        OLED_Show16x16(64, 3, 5, 0);
			break;	//����ң��
		case 'f':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'f'; break;	//ǰ��
		case 'b':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'b'; break;	//����
		case 'l':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'l'; break;	//��ת
		case 'r':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'r'; break;	//��ת
		case 's':PATTERN = 5;
			RETURN_FLAG = 0; 
			Flag_BluetoothCar = 's'; 
			break;	//ֹͣ
		default:break;
		}
}
}