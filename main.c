/*
 * Nuvoton_N76E003_LCDTest
 *
 * Created: 16/7/2018 3:40:10 PM
 * Author : Asim Merchant
 */ 
 
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "ErLCD_8051.h"

//char code testString[20] = "Hello World";
void main (void)
{
	P10_PushPull_Mode;
	InitializeLcd();
	Send_A_Command(0x01);
	Timer0_Delay1ms(2);
	Send_A_Character('A');
	Send_An_Integer(3,1,10);
	Send_An_32Integer(1,2,3456);
	Send_An_lInteger(1,3,78910);
	Send_A_StringToLcdwithLocation(5,4,"Hello World");
	#if	MODE_FLOAT
	Send_A_2Float(6,1,25.387);
	Send_A_1Float(6,2,25.387);
	Send_A_0Float(10,3,25.387);
	#endif
	while(1)
	{
		P10 = ~P10;
		Timer0_Delay1ms(100);
	}
}
  
