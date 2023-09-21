#include <bluetooth.h>
#include "oled.h"

int RETURN_FLAG = 0;	//模式切换变量
//定义FLAG = 1时切换，=0继续运行
int PATTERN = 0;	//模式变量初始化
char Flag_BluetoothCar = 's';
unsigned char m;

void Bluetooth_Init()//蓝牙模块初始化
{
   
   //	SCON = 0x50; 	// SCON: 模式1, 8-bit UART
////波特率9600，11.0592MHz
////	TMOD |= 0x20;
////	TH1=0xfd; 		
////	TL1=0xfd;
//	
////波特率9600，12MHz
//	T2CON = 0x34;	//RCLK、TCLK、TR2置1
//	RCAP2L = 0xD9;	//9600波特率对应 FFD9，低位为D9
//    RCAP2H = 0xFF;	//高位为FF
//	EA = 1;	    	//打开总中断
//	ES = 1; 		//打开串口中断
//	PS = 1;			//串口的优先级置1
	
//    PCON |= 0x80;	//使能波特率倍速位SMOD
//	SCON = 0x50;		//8位数据,可变波特率，可接收数据
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xF3;		//设定定时初值
//	TH1 = 0xF3;		//设定定时器重装值
//	ET1 = 0;		//禁止定时器1中断
//	TR1 = 1;		//启动定时器1

	
    PCON |= 0x80;		//使能波特率倍速位SMOD//9600bps@11.0592MHz
    SCON = 0x50;		//8位数据,可变波特率
	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	//TMOD &= 0x0F;		//清除定时器1模式位
	TMOD &= 0x00;
	//TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TMOD |= 0x21;
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	TL0 = 0x00;
	//TH1 = 0;
	TH0 = 0x00;
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
//	TMOD &= 0xF0;
//	TMOD |= 0x01;
//	//TL1 = 0;
//	TL0 = 0x00;
//	//TH1 = 0;
//	TH0 = 0x00;
	
//	PCON &= 0x7F;		//波特率不倍速
//	SCON = 0x50;		//8位数据,可变波特率
//	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xFD;		//设定定时初值
//	TH1 = 0xFD;		//设定定时器重装值
//	ET1 = 0;		//禁止定时器1中断
//	TR1 = 1;		//启动定时器1
//	
//	PCON |= 0x80;		//使能波特率倍速位SMOD//9600bps@12.000MHz
//	SCON = 0x50;		//8位数据,可变波特率
//	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xF9;		//设定定时初值
//	TH1 = 0xF9;		//设定定时器重装值
//	ET1 = 0;		//禁止定时器1中断
//	TR1 = 1;		//启动定时器1
//	
//	PCON &= 0x7F;		//波特率不倍速
//	SCON = 0x50;		//8位数据,可变波特率
//	//AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	//AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xFD;		//设定定时初值
//	TH1 = 0xFD;		//设定定时器重装值
//	ET1 = 0;		//禁止定时器1中断
//	TR1 = 1;		//启动定时器1
    ES=1;		//启动串口中断
	EA=1;		//中断总开关打开
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
//	//添加一个标志
//	switch (n)
//		{
//		case '0':PATTERN = 0; RETURN_FLAG = 1; break; 	//静息模式（初始化模式）
//		case '1':PATTERN = 1; RETURN_FLAG = 1; break;	//小车电机转动
//		case '2':PATTERN = 2; RETURN_FLAG = 1; break;	//循迹模式
//		case '3':PATTERN = 3; RETURN_FLAG = 1; break;	//超声波测距加OLED显示
//		case '4':PATTERN = 4; RETURN_FLAG = 1; break; 	//循迹加超声避障
//		case '5':PATTERN = 5; RETURN_FLAG = 1; break;	//蓝牙遥控
//		case 'f':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'f'; break;	//前进
//		case 'b':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'b'; break;	//后退
//		case 'l':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'l'; break;	//左转
//		case 'r':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'r'; break;	//右转
//		case 's':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 's'; break;	//停止
//		default:break;
//		}
//	}

//unsigned char Read_SBUF()
//{
//	return m;
//	
//}	

void UART_SER() interrupt 4//串口中断序号为4
{
	if(RI==1)
		{
			RI=0;//将RI接受中断归零
			//Read_SBUF();
			m=SBUF;//接受数据直接赋给P2
			//UART_Change=1;
			
			//UART_sendByte(agency);//将接受数据重新发出；
			switch (m)
		{
		case '0':PATTERN = 0; 
			RETURN_FLAG = 1;
			OLED_CLS();
	OLED_P8x16Str(0, 0, "Quiet", 0);
	OLED_Show16x16(48, 3, 0, 0);
	OLED_Show16x16(64, 3, 1, 0);
			break; 	//静息模式（初始化模式）
		//case '1':PATTERN = 1; RETURN_FLAG = 1; break;	//小车电机转动
		case '2':
			//TR1 = 1;
			//Bluetooth_Init();
		PATTERN = 2; 
			RETURN_FLAG = 1; 
			OLED_CLS();
	   OLED_P8x16Str(0, 0, "Tracking", 0);
	   OLED_Show16x16(48, 3, 2, 0);
	   OLED_Show16x16(64, 3, 3, 0);
			break;	//循迹模式
		case '3':
			
		PATTERN = 3;
			RETURN_FLAG = 1;
			
            OLED_CLS();
	        OLED_P8x16Str(0, 0, "Distance:", 0);
			break;	//超声波测距加OLED显示
		case '4':PATTERN = 4; 
		RETURN_FLAG = 1; 
		OLED_CLS();
	    OLED_P8x16Str(0, 0, "UnicTrac", 0);
		break; 	//循迹加超声避障
		case '5':PATTERN = 5;
			RETURN_FLAG = 1;
			OLED_CLS();
	        OLED_P8x16Str(0, 0, "BTCon", 0);
	        OLED_Show16x16(48, 3, 4, 0);
	        OLED_Show16x16(64, 3, 5, 0);
			break;	//蓝牙遥控
		case 'f':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'f'; break;	//前进
		case 'b':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'b'; break;	//后退
		case 'l':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'l'; break;	//左转
		case 'r':PATTERN = 5; RETURN_FLAG = 0; Flag_BluetoothCar = 'r'; break;	//右转
		case 's':PATTERN = 5;
			RETURN_FLAG = 0; 
			Flag_BluetoothCar = 's'; 
			break;	//停止
		default:break;
		}
}
}