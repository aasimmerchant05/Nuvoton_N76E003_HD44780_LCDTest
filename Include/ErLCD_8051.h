/**
* @file ErLCD_8051.h
* @brief This header file will contain all required
* definitions and basic LCD functions.
*
* @author Mohd Asim Mercant
*	@bug	No known bugs
* @date 14/7/2018
*/
 
#ifndef ErLCD_8051
#define ErLCD_8051
 
//Dont include the below files if already included in project
/*
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
*/

#define MODE_4BIT										1
#define MODE_FLOAT									1

#if	MODE_4BIT

//4bit
#define MrLCDsCrib									P1			//PORT1
#define MrLCDsCrib_M1								P1M1
#define MrLCDsCrib_M2								P1M2
#define MrLCDsControl								P1
#define MrLCDsControl_M1						P1M1
#define MrLCDsControl_M2						P1M2
#define LightSwitch									3		//Enable pin on LCD
#define ReadWrite										2		//R/W pin on LCD
#define BiPolarMood									1		//RS Register Select pin on LCD

#define MrLCDsCrib_M1_1							4	//LCD Data Pin Number for D4
#define MrLCDsCrib_M2_1							4	//LCD Data Pin Number for D4
#define MrLCDsCrib_M1_2							5	//LCD Data Pin Number for D5
#define MrLCDsCrib_M2_2							5	//LCD Data Pin Number for D5
#define MrLCDsCrib_M1_3							6	//LCD Data Pin Number for D6
#define MrLCDsCrib_M2_3							6	//LCD Data Pin Number for D6
#define MrLCDsCrib_M1_4							7	//LCD Data Pin Number for D7
#define MrLCDsCrib_M2_4							7	//LCD Data Pin Number for D7
#define Output_MrLCDsCrib						MrLCDsCrib_M1 &= ~(1<<MrLCDsCrib_M1_1);MrLCDsCrib_M2 |= (1<<MrLCDsCrib_M2_1);MrLCDsCrib_M1 &= ~(1<<MrLCDsCrib_M1_2);MrLCDsCrib_M2 |= (1<<MrLCDsCrib_M2_2);MrLCDsCrib_M1 &= ~(1<<MrLCDsCrib_M1_3);MrLCDsCrib_M2 |= (1<<MrLCDsCrib_M2_3);MrLCDsCrib_M1 &= ~(1<<MrLCDsCrib_M1_4);MrLCDsCrib_M2 |= (1<<MrLCDsCrib_M2_4);		//Set push-pull mode
#define Input_MrLCDsCrib						MrLCDsCrib_M1 |= (1<<MrLCDsCrib_M1_1);MrLCDsCrib_M2 &= ~(1<<MrLCDsCrib_M2_1);MrLCDsCrib_M1 |= (1<<MrLCDsCrib_M1_2);MrLCDsCrib_M2 &= ~(1<<MrLCDsCrib_M2_2);MrLCDsCrib_M1 |= (1<<MrLCDsCrib_M1_3);MrLCDsCrib_M2 &= ~(1<<MrLCDsCrib_M2_3);MrLCDsCrib_M1 |= (1<<MrLCDsCrib_M1_4);MrLCDsCrib_M2 &= ~(1<<MrLCDsCrib_M2_4);		//Set input mode

#else

//8bit
//Change Pin Definitions according to connection to mcu
#define MrLCDsCrib								P1			//PORT1
#define MrLCDsCrib_M1							P1M1
#define MrLCDsCrib_M2							P1M2
#define Output_MrLCDsCrib					MrLCDsCrib_M1 = 0x00;MrLCDsCrib_M2 = 0xFF;		//Set push-pull mode
#define Input_MrLCDsCrib					MrLCDsCrib_M1 = 0xFF;MrLCDsCrib_M2 = 0x00;		//Set input mode
#define MrLCDsControl							P0
#define MrLCDsControl_M1					P0M1
#define MrLCDsControl_M2					P0M2

#define LightSwitch								5		//Enable pin on LCD
#define ReadWrite									4		//R/W pin on LCD
#define BiPolarMood								3		//RS Register Select pin on LCD

#endif

//char firstColumnPositionForLCD[2] = {0, 64,}; //For 16x2 LCD just {0,64} & For 16x4 {0, 64, 16, 80} & for 20x4 {0,64,20,84}
char firstColumnPositionForLCD[4] = {0, 64, 20, 84};

void Check_IF_MrLCD_isBusy(void);
void Peek_A_Boo(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);
void GotoLCDLocation(uint8_t x, uint8_t y);
void InitializeLcd(void);
void Send_A_StringToLcdwithLocation(uint8_t x, uint8_t y, char *Stringofcharacters);
void itoa(int n, char *s);
void Send_An_Integer(uint8_t x, uint8_t y, int IntegerToDisplay);
void Send_An_32Integer(uint8_t x, uint8_t y, uint32_t IntegerToDisplay);
void Send_An_lInteger(uint8_t x, uint8_t y, long IntegerToDisplay);
//void CopyStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y);
void Send_A_2Float(uint8_t x, uint8_t y, float floatToDisplay);
void Send_A_1Float(uint8_t x, uint8_t y, float floattoDisplay);
void Send_A_0Float(uint8_t x, uint8_t y, float floattoDisplay);
void itoa(int n, char *s);

/**
* @brief This method converts an integer to characters
* @author Unknown
* @date 14/7/2018
* @param n Input Integer to be converted
* @param s Destination String to which the integer is to be converted
* @return Void.
*/
void itoa(int n, char *s) { 
char i;
int n1;
if (n<0) {
  n=-n;
  *s++='-';
}
do
{
  n1=n;
  i=0;
while (1) {
  if (n1<=9)   {
    *s++=n1+'0';
    break;
  }
  n1=n1/10;
  i++;
}
while (i) {
  i--;
  n1=n1*10;
}
n-=n1;
}while (n);
*s++=0;
}

/**
* @brief This method checks if the LCD is busy or not.
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param Void.
* @return Void.
*/
void Check_IF_MrLCD_isBusy(void)
{
	///Set all pins connected to data pins of LCD to Input Mode
	Input_MrLCDsCrib;
	///Set LCD Mode to Read mode by setting RW pin HIGH
	MrLCDsControl |= (1<<ReadWrite);
	///Set LCD to command mode by setting RS pin HIGH
	MrLCDsControl &= ~(1<<BiPolarMood);
	///Set LCD Enable pin HIGH
	MrLCDsControl |= (1<<LightSwitch);
	///Wait for 1ms for LCD operation
	//Timer0_Delay1ms(1);
	///Check for pin D7, if it is HIGH LCD is busy else not busy
	while (MrLCDsCrib >= 0x80)
	{
		///Toggle Enable pin of LCD
		Peek_A_Boo();
	}
	///Set LCD Enable pin LOW, Can read the lcd address counter here as it is made available alongwith the busy flag
	MrLCDsControl &= ~(1<<LightSwitch);
	///Set Data pins of controller to OUTPUT or PUSH PULL mode
	Output_MrLCDsCrib;
}

/**
* @brief This method toggles LCD Enable pin
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param Void.
* @return Void.
*/
void Peek_A_Boo(void)
{
	///Set enable pin HIGH
	MrLCDsControl |= (1<<LightSwitch);
	///Wait for around 100uS
	Timer0_Delay100us(1);
	///Set Enable pin LOW
	MrLCDsControl &= ~(1<<LightSwitch);
}

#if	MODE_4BIT
/**
* @brief This method will send a command to LCD if it is in 4bit mode
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param command	The command to send to LCD
* @return Void.
*/
void Send_A_Command(unsigned char command)
{
	///Check if LCD is busy
	Check_IF_MrLCD_isBusy();
	///Clear higher nibble bits and mask lower nibble bits of data port
	MrLCDsCrib &= 0x0F;
	///Set command higher nibble to higher nibble of port
	MrLCDsCrib |= (command & 0xF0);
	///Set RW LOW for Write mode and RS pin to LOW for command mode
	MrLCDsControl &= ~ ((1<<ReadWrite)|(1<<BiPolarMood));
	///Toggle Enable pin
	Peek_A_Boo();
	///Clear higher nibble bits and mask lower nibble bits of data port
	MrLCDsCrib &= 0x0F;
	///Set command lower nibble to higher nibble of port
	MrLCDsCrib |= ((command<<4) & 0xF0);
	///Set RW LOW for Write mode and RS pin to LOW for command mode
	MrLCDsControl &= ~ ((1<<ReadWrite)|(1<<BiPolarMood));
	///Toggle Enable pin
	Peek_A_Boo();
	///Clear higher nibble bits and mask lower nibble bits of data port
	MrLCDsCrib &= 0x0F;
}

/**
* @brief This method will send a character to LCD if it is in 4bit mode
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param character	The character to send to LCD
* @return Void.
*/
void Send_A_Character(unsigned char character)
{
	///Check if LCD is busy
	Check_IF_MrLCD_isBusy();
	///Clear higher nibble bits and mask lower nibble bits of data port
	MrLCDsCrib &= 0x0F;
	///Set character higher nibble to higher nibble of port
	MrLCDsCrib |= (character & 0xF0);
	///Set RW LOW for Write mode and RS pin to HIGH for data mode
	MrLCDsControl &= ~ (1<<ReadWrite);
	MrLCDsControl |= 1<<BiPolarMood;
	///Toggle Enable pin
	Peek_A_Boo();
	///Clear higher nibble bits and mask lower nibble bits of data port
	MrLCDsCrib &= 0x0F;
	///Set character lower nibble to higher nibble of port
	MrLCDsCrib |= ((character<<4) & 0xF0);
	///Set RW LOW for Write mode and RS pin to HIGH for data mode
	MrLCDsControl &= ~ (1<<ReadWrite);
	MrLCDsControl |= 1<<BiPolarMood;
	///Toggle Enable pin
	Peek_A_Boo();
	///Clear higher nibble bits and mask lower nibble bits of data port
	MrLCDsCrib &= 0x0F;
}
/**
* @brief This method will Initialize LCD and set it to 4bit mode
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param Void.
* @return Void.
*/
void InitializeLcd()
{
	///Set LCD Enable, ReadWrite and RS pins to Output or PushPull mode
	MrLCDsControl_M1 &= ~(1<<LightSwitch);
	MrLCDsControl_M1 &= ~(1<<ReadWrite);
	MrLCDsControl_M1 &= ~(1<<BiPolarMood);
	
	MrLCDsControl_M2 |= (1<<LightSwitch);
	MrLCDsControl_M2 |= (1<<ReadWrite);
	MrLCDsControl_M2 |= (1<<BiPolarMood);
	
	///Wait for 15ms
	Timer0_Delay1ms(15);
	
	///Send command 0x02 for
	Send_A_Command(0x02);
	///Wait for 2ms
	Timer0_Delay1ms(2);
	///Send command 0x01 for
	Send_A_Command(0x01);	//Clear Screen 0x01 = 00000001
	///Wait for 1ms
	Timer0_Delay1ms(1);
	///Send command 0x28 for
	Send_A_Command(0x28);
	///Wait for 1ms
	Timer0_Delay1ms(1);
	///Send command 0x0C for
	Send_A_Command(0x0C);
	///Wait for 1ms
	Timer0_Delay1ms(1);
}

#else
/**
* @brief This method will send a command to LCD if it is in 8bit mode
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param command	The command to send to LCD
* @return Void.
*/
void Send_A_Command(unsigned char command)
{
	///Check if LCD is busy
	Check_IF_MrLCD_isBusy();
	///Set command to Data port
	MrLCDsCrib = command;
	///Set RW LOW for Write mode and RS pin to LOW for command mode
	MrLCDsControl &= ~ ((1<<ReadWrite)|(1<<BiPolarMood));
	///Toggle Enable pin
	Peek_A_Boo();
	///Clear Data port
	MrLCDsCrib = 0;
}
/**
* @brief This method will send a character to LCD if it is in 8bit mode
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param character	The character to send to LCD
* @return Void.
*/
void Send_A_Character(unsigned char character)
{
	Check_IF_MrLCD_isBusy();
	MrLCDsCrib = character;
	MrLCDsControl &= ~ (1<<ReadWrite);
	MrLCDsControl |= 1<<BiPolarMood;
	Peek_A_Boo();
	MrLCDsCrib = 0;
}
/**
* @brief This method will Initialize LCD and set it to 8bit mode
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param Void.
* @return Void.
*/
void InitializeLcd()
{
	MrLCDsControl_M1 &= ~(1<<LightSwitch);
	MrLCDsControl_M1 &= ~(1<<ReadWrite);
	MrLCDsControl_M1 &= ~(1<<BiPolarMood);

	MrLCDsControl_M2 |= (1<<LightSwitch);
	MrLCDsControl_M2 |= (1<<ReadWrite);
	MrLCDsControl_M2 |= (1<<BiPolarMood);
	
	Timer0_Delay1ms(15);

	Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
	Timer0_Delay1ms(2);
	Send_A_Command(0x38);
	Timer0_Delay1ms(1);
	Send_A_Command(0x0C);
	Timer0_Delay1ms(1);
	
}
#endif
/**
* @brief This method sends LCD cursor location to print character
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @return Void.
*/
void GotoLCDLocation(uint8_t x, uint8_t y)
{
	Send_A_Command(0x80 + firstColumnPositionForLCD[y-1] + (x-1));
}
/**
* @brief This method prints String on LCD at earlier cursor location
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param Stringofcharacters The string to display on LCD	
* @return Void.
*/
void Send_A_String (char *Stringofcharacters)
{
	while(*Stringofcharacters > 0)
	{
		Send_A_Character(*Stringofcharacters++);
	}
}
/**
* @brief This method prints String on LCD at specific cursor location
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @param Stringofcharacters The string to display on LCD	
* @return Void.
*/
void Send_A_StringToLcdwithLocation(uint8_t x, uint8_t y, char *Stringofcharacters)
{
	GotoLCDLocation(x, y);
	Send_A_String(Stringofcharacters);
}
/**
* @brief This method prints Integer on LCD at specific cursor location
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @param IntegerToDisplay The integer to display on LCD	
* @return Void.
*/
void Send_An_Integer(uint8_t x, uint8_t y, int IntegerToDisplay)
{
	char StringToDisplay[5];	//increase array length for more digits
	//itoa(IntegerToDisplay, StringToDisplay);
	sprintf(StringToDisplay, "%d", IntegerToDisplay);		//eats 1014bytes
	//for(int i=0; i<NumberofDigits;i++) Send_A_String(" ");	//comment this line if number of digits does not change, or blur effect is visible
	Send_A_StringToLcdwithLocation(x, y, StringToDisplay);
}
/**
* @brief This method prints 32bit data on LCD at specific cursor location
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @param IntegerToDisplay The 32bit data to display on LCD	
* @return Void.
*/
void Send_An_32Integer(uint8_t x, uint8_t y, uint32_t IntegerToDisplay)
{
	char StringToDisplay[12];
	int i = 0;
	//ltoa(IntegerToDisplay, StringToDisplay, 10);
	sprintf(StringToDisplay, "%ld", IntegerToDisplay);		//eats 1014bytes
	for(i=0; i<12;i++) Send_A_String(" ");	//comment this line if number of digits does not change, or blur effect is visible
	Send_A_StringToLcdwithLocation(x, y, StringToDisplay);
}
/**
* @brief This method prints Long on LCD at specific cursor location
* @author Mohd Asim Merchant
* @date 14/7/2018
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @param IntegerToDisplay The long data to display on LCD	
* @return Void.
*/
void Send_An_lInteger(uint8_t x, uint8_t y, long IntegerToDisplay)
{
	char StringToDisplay[12];
	//ltoa(IntegerToDisplay, StringToDisplay, 10);
	sprintf(StringToDisplay, "%ld", IntegerToDisplay);		//eats 1014bytes
	//for(int i=0; i<NumberofDigits;i++) Send_A_String(" ");	//comment this line if number of digits does not change, or blur effect is visible
	Send_A_StringToLcdwithLocation(x, y, StringToDisplay);
}

#if	MODE_FLOAT
/**
* @brief This method prints Float with 2 decimals on LCD at specific cursor location
* @author Mohd Asim Merchant
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @param floattoDisplay The float to display on LCD	
* @date 14/7/2018
* @return Void.
*/
void Send_A_2Float(uint8_t x, uint8_t y, float floattoDisplay)		//rounds off to nearest value
{
	char buffer[20];
	sprintf(buffer,"%0.2f",floattoDisplay);
	Send_A_StringToLcdwithLocation(x,y, buffer);
}
/**
* @brief This method prints Float with 1 decimal on LCD at specific cursor location
* @author Mohd Asim Merchant
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @param floattoDisplay The float to display on LCD	
* @date 14/7/2018
* @return Void.
*/
void Send_A_1Float(uint8_t x, uint8_t y, float floattoDisplay)		//rounds off to nearest value
{
	char buffer[20];
	sprintf(buffer,"%0.1f",floattoDisplay);
	Send_A_StringToLcdwithLocation(x,y, buffer);
}
/**
* @brief This method prints Float with 0 decimals on LCD at specific cursor location
* @author Mohd Asim Merchant
* @param x X-axis Location i.e. horizontal location(begins with 1)
* @param y Y-axis Location i.e. vertical location(begins with 1)
* @param floattoDisplay The float to display on LCD	
* @date 14/7/2018
* @return Void.
*/
void Send_A_0Float(uint8_t x, uint8_t y, float floattoDisplay)		//rounds off to nearest value
{
	char buffer[20];
	sprintf(buffer,"%0.0f",floattoDisplay);
	Send_A_StringToLcdwithLocation(x,y, buffer);
}
#endif

/*void CopyStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y)	// not needed here
{
	uint8_t i;
	GotoLCDLocation(x, y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		Send_A_Character((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}*/

//char code testString[20] = "Hello World";
/*void main (void)
{
	//InitialUART0_Timer1(9600);           //UART0 Baudrate initial,T1M=0,SMOD=0
	//Timer0_Delay1ms(10);
	//Send_Data_To_UART0('R');
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
		//Send_Data_To_UART0('F');
		//Timer0_Delay1ms(30);
	}
}*/
  
#endif