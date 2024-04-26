
#ifndef SPI_H_
#define SPI_H_

typedef enum{
	SLAVE,
	MASTER
	
	
}SPI_Mode_type;



#define	 SPI_INTERRUPT_MODE	SPI_SEND
#define  SPI_SEND_MODE		1
#define  SPI_RECEIVE_MODE	0

void SPI_Init(SPI_Mode_type mode);

u8 SPI_SendReceive(u8 data);

void SPI_SendNoBlock(u8 data);

u8 SPI_ReceivePerodic(u8*pdata);

Bool_t SPI_SendReceiveTimeOut(u8 data,u8*recdata);

void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);
#endif /* SPI_H_ */