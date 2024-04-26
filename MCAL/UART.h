
#ifndef UART_H_
#define UART_H_


void UART_Init(void);

void UART_Send(u8 data);
u8 UART_Receive(void);
u8 UART_ReceivePerodic(u8*pdata);

void UART_Send_NoBlock(u8 data);
u8 UART_ReceiveNoBlock(void);

void UART_TX_SetCallBack(void (*LocalFptr)(void));
void UART_RX_SetCallBack(void (*LocalFptr)(void));

void UART_TxInterruptEnable(void);
void UART_TxInterruptDisable(void);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
#endif /* UART_H_ */