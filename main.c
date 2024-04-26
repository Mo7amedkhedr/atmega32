
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#define F_CPU  8000000
#include <util/delay.h>
#include "DIO_Interface.h"
#include "Motors_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "ADC_Interface.h"
#include "Sensors.h"
#include "EX_Interrupt.h"
#include "Timers.h"
#include "UART.h"
#include "UART_Service.h"
#include "SPI.h"
#include "WDT.h"
#include <stdlib.h>
float function(float number1,float number2 ,u8 operation)
{
	switch (operation)
	{
		case '+' :
		return number1+number2;
		case '-' :
		return number1-number2;
		case '*' :
		return number1*number2;
		case '/' :
		return number1/number2;
	}
}
float power(u16 base,u16 powerer){
	float x =1;
	for(int i=0 ;i<powerer;i++){
		x *= base;
	}
	return x;
}
int main(void)
{
   DIO_Init();
  // MOTOR_Init();
   LCD_Init();
   KEYPAD_Init();
  // EXI_Init();
  // ADC_Init(VREF_AREF,ADC_SCALER_64);
   //UART_Init();
   
  float ans=0;
  u8 charcter,operation,flag_num2=0;
  float number1=0,number2=0;
  u8 flag_dot=0;
  u8 flag_operation_done=0;
  u8 i=1;
  LCD_WriteString("Mohamed Ali ");
   _delay_ms(1000);
   LCD_Clear();
  LCD_WriteString("Challenge ");
  _delay_ms(1000);
  LCD_Clear();
 while (1)
 {
	 charcter = KEYPAD_GetKey();
	 _delay_ms(200);
	 switch(charcter)
	 {
		case '+':
		case '-':
		case '/':
		case '*':
			operation=charcter;
			flag_num2=1;
			flag_dot=0;
			if(flag_operation_done)
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("ans");
				flag_operation_done=0;
				number2=0;
			}
			LCD_WriteChar(charcter);
			i=1;
			break;	
		case '=':
		    LCD_WriteChar(charcter);
	         if(operation=='/'&&number2==0)
			{			
				LCD_SetCursor(1,0);
				LCD_WriteString("Math error");
			}
			else
			{
				ans=function(number1,number2,operation);
				LCD_SetCursor(1,0);
			//	LCD_WriteString("ans=");
				LCD_WriteNumber(ans);
				number1=ans;
			}
			flag_dot=0;
			flag_operation_done=1;
			break;	
		case '.':
		  LCD_WriteChar(charcter);
			flag_dot=1;
			break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			if(flag_operation_done)
			{
				LCD_Clear();
				number1=0;number2=0;
				flag_operation_done=0;
				flag_num2=0;
			}
			LCD_WriteChar(charcter);
			if(flag_num2)
			{
				if(flag_dot)
				{
					number2=number2 + ((charcter-'0')/power(10,i));
					i++;
				}
				else
				{
					number2=number2 * 10.0 + (charcter-'0');
				}
			}
			else
			{
				if(flag_dot)
				{
					number1=number1 + ((charcter-'0')/power(10,i));
					i++;
				}
				else
				{
					number1=number1 * 10.0 + (charcter-'0');
				}
			}
			flag_operation_done=0;
			break;

		};
	}									  			
	 
	 
 return 0;

}
/*
ISR(TIMER0_OVF_vect)
{
	static u16 c=0;
	static u16 c2=0;
	c++;
	c2++;
	if (c==3906)
	{
		DIO_TogglePin(PINC1);
		c=0;
	}
	if (c2==1953)
	{
		DIO_TogglePin(PINC0);
		c2=0;
	}
}*/
/*
ISR(TIMER0_OVF_vect)
{
	static u16 c=0;
	TCNT0=6;
	c++;
	
	if (c%20==0)
	{
		DIO_TogglePin(PINC0);
	}
	if (c%40==0)
	{
		DIO_TogglePin(PINC1);
	}
	if (c%100==0)
	{
		DIO_TogglePin(PINC2);
	}
	if (c==200)
	{
		c=0;
	}
}*/

