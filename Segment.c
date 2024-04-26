#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#define  F_CPU  8000000
#include <util/delay.h>
#define SEGMENT1_PORT   PORTC
#define SEGMENT2_PORT   PORTA

void segment_display(u8 n)
{
	unsigned char d0,d1, segmentArr[]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f};
	d0=n%10;
	d1=n/10;
	
	SEGMENT1_PORT=segmentArr[d0]<<1;
	SEGMENT2_PORT=~segmentArr[d1];
	
}
void segment_display_hex(unsigned char n)
{
	unsigned char d0,d1, segmentArr[]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f,};
	d0=n&0x0f;
	d1=n>>4;
	PORTD=segmentArr[d0]<<1;
	PORTC=~segmentArr[d1];
}
void segment_display_BCD(unsigned char n)
{
	PORTA=n;
}
void segment_display_MLX(unsigned char n)
{
	unsigned char d0,d1, segmentArr[]={0X3f,0X06,0X5b,0X4f,0X66,0X6d,0X7d,0X07,0X7f,0X6f};
	d0=n%10;
	d1=n/10;
	SET_BIT(PORTD,6);
	
	SEGMENT1_PORT=segmentArr[d0]<<1;
	CLR_BIT(PORTD,7);
	_delay_ms(1);
	SET_BIT(PORTD,7);
	
	SEGMENT1_PORT=segmentArr[d1]<<1;
	CLR_BIT(PORTD,6);
	_delay_ms(1);
	
}