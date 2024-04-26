
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI.h"



void SPI_Init(SPI_Mode_type mode)
{
	if (mode==MASTER)
	{
		SET_BIT(SPCR,MSTR);
	}
	else
	{
		CLR_BIT(SPCR,MSTR);
	}
	
	//CLOCK 2 MHZ
	
	// SPI ENABLE
	SET_BIT(SPCR,SPE);
	
}



u8 SPI_SendReceive(u8 data)
{
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF));
	return SPDR;
}


void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}

u8 SPI_ReceivePerodic(u8*pdata)
{
	if (READ_BIT(SPSR,SPIF))
	{
		*pdata=SPDR;
		return 1;
	}
	return 0;
}

Bool_t SPI_SendReceiveTimeOut(u8 data,u8*recdata)
{
	Bool_t status=FALSE;
	u8 c=0;
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF) && (c<10))
	{
		c++;
		_delay_us(1);
	}
	if(READ_BIT(SPSR,SPIF))
	{
		*recdata=SPDR;
		status=TRUE;
	}
	return status;
}

void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}

void SPI_InterruptDisable(void)
{
	CLR_BIT(SPCR,SPIE);
}

/***********************Using SPI To Send_receive data using interrupt**************/

static void (*Spi_Ptr)(void)=NULLPTR;
#if(SPI_INTERRUPT_MODE	==	SPI_SEND_MODE)

void SPI_SendUsingInterrupt(void(*Ptf)(void))
{
	SPI_InterruptEnable();
	Spi_Ptr=Ptf;
}

ISR(SPI_STC_vect)
{
	if(Spi_Ptr!=(void*)0)
	{
		Spi_Ptr();
	}
}

#elif(SPI_INTERRUPT_MODE==SPI_RECEIVE_MODE)

void SPI_ReceiveUsingInterrupt(void(*Ptf)(void))
{
	SPI_InterruptEnable();
	Spi_Ptr=Ptf;
}

ISR(SPI_STC_vect)
{
	if(Spi_Ptr!=(void*)0)
	{
		Spi_Ptr();
	}
}

#endif