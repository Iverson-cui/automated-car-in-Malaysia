#include "oled.h"
#include "codetab.h"

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
	OLED_SDA = 1;
//	oled_delayus(1);
	OLED_SCL = 1;
//	oled_delayus(1);
	OLED_SDA = 0;
//	oled_delayus(1);
	OLED_SCL = 0;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
	OLED_SDA = 0;
//	oled_delayus(1);
	OLED_SCL = 0;
//	oled_delayus(1);
	OLED_SDA = 1;
//	oled_delayus(1);
	OLED_SCL = 1;
}

/**********************************************
// ͨ��I2C����дһ���ֽ�
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		if (IIC_Byte & 0x80)
			OLED_SDA = 1;
		else
			OLED_SDA = 0;
//		oled_delayus(1);
		OLED_SCL = 1;
//		oled_delayus(1);  //�����б���SCL�������ʱ
		OLED_SCL = 0;
//		oled_delayus(1);
		IIC_Byte <<= 1;
	}
    OLED_SDA = 1; //ԭ����������һ������SDA������OLED��DATASHEET���˾����ȥ����
                  //no no no,���ھ͸ü�����
	OLED_SCL = 1;
	oled_delayus(1);
	OLED_SCL = 0;
}

/*********************OLEDд����*********************************/
void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Byte(IIC_Data);
	IIC_Stop();
}

/*********************OLEDд����**********************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);           //Slave address,SA0=0
	Write_IIC_Byte(0x00);           //write command
	Write_IIC_Byte(IIC_Command);
	IIC_Stop();
}

/*********************OLED ��������*******************************/
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
	OLED_WrCmd((x & 0x0f) | 0x01);
}

/*********************OLEDȫ��************************************/
void OLED_Fill(unsigned char bmp_dat)
{
	unsigned char y, x;
	for (y = 0; y < 8; y++)
	{
		OLED_WrCmd(0xb0 + y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for (x = 0; x < X_WIDTH; x++)
                  OLED_WrDat(bmp_dat);
	}
}

/*********************OLED��λ************************************/
void OLED_CLS(void)
{
	OLED_Fill(0x00);
}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED�������л���
//--------------------------------------------------------------
//void OLED_ON(void)
//{
//	OLED_WrCmd(0X8D);  //���õ�ɱ�
//	OLED_WrCmd(0X14);  //������ɱ�
//	OLED_WrCmd(0XAF);  //OLED����
//}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
//--------------------------------------------------------------
//void OLED_OFF(void)
//{
//	OLED_WrCmd(0X8D);  //���õ�ɱ�
//	OLED_WrCmd(0X10);  //�رյ�ɱ�
//	OLED_WrCmd(0XAE);  //OLED����
//}

/*********************OLED��ʼ��************************************/
void OLED_Init(void)
{   
	/*************************************************/
	OLED_RST = 0;
	oled_delayms(100);//��ʼ��֮ǰ����ʱ����Ҫ��
	OLED_RST = 1;
	// �ⲿ����ʹ��32�����Ĳ�û��
	// ����ʹ��51��Ƭ���ı�����������λ�������ͳ���200ms,��һֱ���ָߵ�ƽ
	// ��Ȼ�����OLED��û�������λ�ӿڣ���Ҳ���Ǽ��ɵ��˰�����ⲿ��Ҳ�Ͳ��ù���
	// Ӱ�첻��
	/*************************************************/
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set 0 column address
	OLED_WrCmd(0x10);//---set 1 column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //��ʼ����
	OLED_Set_Pos(0, 0);
}

/*������������ʾ6*8һ���׼ASCII�ַ���	
��ʾ�����꣨x,y����yΪҳ��Χ0��7*/
//void OLED_P6x8Str(unsigned char x, unsigned char y, unsigned char ch[], unsigned char against)
//{
//	unsigned char c = 0, i = 0, j = 0;
//	unsigned char Temp;
//	if (!against)Temp = 0x00;
//	else Temp = 0xFF;
//	while (ch[j] != '\0')
//	{
//		c = ch[j] - 32;
//		if (x > 126) { x = 0; y++; }
//		OLED_Set_Pos(x, y);
//		for (i = 0; i < 6; i++)
//			OLED_WrDat(F6x8[c][i] ^ Temp);
//		x += 6;
//		j++;
//	}
//}
/*������������ʾ8*16һ���׼ASCII�ַ���	 
��ʾ�����꣨x,y����yΪҳ��Χ0��7  against:0,������ʾ;1,������ʾ*/
void OLED_P8x16Str(unsigned char x, unsigned  char y, unsigned char ch[], unsigned char against)
{
	unsigned char c = 0, i = 0, j = 0;
	unsigned char Temp;
	if (!against)Temp = 0x00;
	else Temp = 0xFF;
	while (ch[j] != '\0')
	{
		c = ch[j] - 32;
		if (x > 120) { x = 0; y++; }
		OLED_Set_Pos(x, y);
		for (i = 0; i < 8; i++)
			OLED_WrDat(F8X16[c * 16 + i] ^ Temp);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i < 8; i++)
			OLED_WrDat(F8X16[c * 16 + i + 8] ^ Temp);
		x += 8;
		j++;
	}
}
/*������������ʾ 6*8 ���� ��ʾ�����꣨x,y����yΪҳ��Χ0��7*/
//void OLED_Show6x8(unsigned char x, unsigned char y, unsigned int N, unsigned char against)
//{
//	unsigned char i = 0;
//	unsigned int  adder = 6 * N;
//	unsigned char Temp;
//	if (!against)Temp = 0x00;
//	else Temp = 0xFF;
//	if (x > 126)
//		x = 0, y++;
//	OLED_Set_Pos(x, y);
//	for (i = 0; i < 6; i++)OLED_WrDat(My6x8[adder++] ^ Temp);
//}

/*������������ʾ 8*16 ���� ��ʾ�����꣨x,y����yΪҳ��Χ0��7*/
//void OLED_Show8x16(unsigned char x, unsigned char y, unsigned int N, unsigned char against)
//{
//	unsigned char i = 0;
//	unsigned int  adder = 16 * N;
//	unsigned char Temp;
//	if (!against)Temp = 0x00;
//	else Temp = 0xFF;
//	if (x > 120)
//		x = 0, y++;
//	OLED_Set_Pos(x, y);
//	for (i = 0; i < 8; i++)
//		OLED_WrDat(My8x16[adder++] ^ Temp);
//	OLED_Set_Pos(x, y + 1);
//	for (i = 0; i < 8; i++)
//		OLED_WrDat(My8x16[adder++] ^ Temp);
//}

/*������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7*/
void OLED_Show16x16(unsigned char x, unsigned char y, unsigned int N, unsigned char against)
{
	unsigned char wm = 0;
	unsigned int  adder = 32 * N;
	unsigned char Temp;
	if (!against)Temp = 0x00;
	else Temp = 0xFF;
	OLED_Set_Pos(x, y);
	for (wm = 0; wm < 16; wm++)
	{
		OLED_WrDat(yufan[adder] ^ Temp);
		adder += 1;
	}
	OLED_Set_Pos(x, y + 1);
	for (wm = 0; wm < 16; wm++)
	{
		OLED_WrDat(yufan[adder] ^ Temp);
		adder += 1;
	}
}

/*������������ʾ6x8����8x16�� u16���޷���16λ���ݣ�����ʾ�����꣨x,y����yΪҳ��Χ0��7*/
//void Oled_Printf_U16(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
//{
//	unsigned char temp[6], i;
//	temp[5] = '\0';
//	temp[4] = (unsigned char)(num % 10 + '0'); num /= 10;
//	temp[3] = (unsigned char)(num % 10 + '0'); num /= 10;
//	temp[2] = (unsigned char)(num % 10 + '0'); num /= 10;
//	temp[1] = (unsigned char)(num % 10 + '0'); num /= 10;
//	temp[0] = (unsigned char)(num % 10 + '0');
//	for (i = 0; i < 4; i++)
//	{
//		if (temp[i] == '0')
//			temp[i] = ' ';
//		else
//			break;
//	}
//	switch (TextSize)
//	{
//	case 0:
//		OLED_P6x8Str(x, y, temp, 0);
//		break;
//	case 1:
//		OLED_P8x16Str(x, y, temp, 0);
//		break;
//	default:
//		break;
//	}
//}
//��ʾ���999.99������
/*������������ʾ6x8����8x16�� float ���ݣ���ʾ�����꣨x,y����yΪҳ��Χ0��7*/
void Oled_Printf_Float(unsigned char x, unsigned char y, float num, unsigned char TextSize)
{
	unsigned char i;
	unsigned char result[8];
	unsigned int  tempH;
	unsigned char tempL;
	result[7] = '\0'; result[4] = '.';
	if (num < 0)
	{
		num = -num;
		result[0] = '-';
	}
	else
		result[0] = ' ';
	tempH = (unsigned int)num;
	tempL = (unsigned char)(num * 100 - tempH * 100);

	/*��ʾ��������*/
	result[3] = tempH % 10 + '0'; tempH /= 10;
	result[2] = tempH % 10 + '0'; tempH /= 10;
	result[1] = tempH + '0';

	/*��ʾС������*/
	result[6] = tempL % 10 + '0'; tempL /= 10;
	result[5] = tempL + '0';

	for (i = 1; i < 3; i++)
	{
		if (result[i] == '0')
			result[i] = ' ';
		else
			break;
	}
	switch (TextSize)
	{
//	case 0:
//		OLED_P6x8Str(x, y, result, 0); break;
	case 1:
		OLED_P8x16Str(x, y, result, 0); break;
	default:break;
	}
}

void oled_delayus(unsigned int num)
{
	while(num --);
}

void oled_delayms(unsigned int num)
{
	unsigned int x, y;
	for(x = num; x > 0; x--)
		for(y = 110; y > 0; y--);
}
