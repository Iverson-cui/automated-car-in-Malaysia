#include <tracking.h>
#include <driver.h>

unsigned char Infrared;

void TRACK(void)
{
	Infrared = P1 & 0x0F;
	switch (Infrared)
	{
	case 0x00:
		zhizou(); break;   //0000
	case 0x08:
		dazhuan1(); break; //1000
	case 0x04:
		weitiao1(); break; //0100
	case 0x02:
		weitiao2(); break; //0010
	case 0x01:
		dazhuan2(); break; //0001
	case 0x0C:
		dazhuan1(); break; //1100
	case 0x03:
		dazhuan2(); break; //0011
	case 0x0E:
		dazhuan1(); break; //1110
	case 0x07:
		dazhuan2(); break; //0111
	case 0x0F:
		zhizou(); break;   //1111
	case 0x06:
	 zhizou(); break;   //0110
	case 0x05:
	 dazhuan2(); break;  //0101
	 case 0x0A:
	 dazhuan1(); break;  //1010
	default:   break;
	}
}

void zhizou()
{
	Motor_Left(1, 30);
	Motor_Right(1, 30);
}

void zhizou2()
{
	Motor_Left(1, 20);
	Motor_Right(1, 20);
}


void dazhuan1()
{
		
		while ( P1 & 0x0F ) {
			zhizou2();
		}
		while ( (P1 & 0x04) != 0x04) {    //0x02?0000 0010 P0&0x0F only can be 0000 and 0010
        Motor_Left(0, 40);
				Motor_Right(1, 40);	
				}				
		while ( P1 & 0x0F ) {
				Motor_Left(0, 40);
				Motor_Right(1, 40);
		}
		
	}
	
void dazhuan2()
{
		
		while ( P1 & 0x0F ) {
			zhizou2();
		}
		while ( (P1 & 0x02) != 0x02) {    //0x02?0000 0010 P0&0x0F only can be 0000 and 0010
        Motor_Left(1, 40);
				Motor_Right(0, 40);	
				}				
		while ( P1 & 0x0F ) {
				Motor_Left(1, 40);
				Motor_Right(0, 40);
		}
		
	}


void weitiao1()
{
	
		Motor_Left(0, 50); Motor_Right(1, 50);
}

void weitiao2()
{
		
		Motor_Left(1, 50); Motor_Right(0, 50);
}


