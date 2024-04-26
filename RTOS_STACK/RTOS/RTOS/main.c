 #include "StdTypes.h"
 
 #include "Kernal_interface.h"
#include "DIO_Interface.h"

void LED2(void);
void LED1(void);

int main(void)
{
	DIO_Init();
	RTOS_u8CreateTask(0,&LED1,1000,1);
    RTOS_u8CreateTask(1,&LED2,2000,2);
	//RTOS_voidSuspendTask(1);
	RTOS_voidStart();
    while (1) 
    {
    }
}

void LED1(void)
{
	DIO_TogglePin(PINA0);
	//RTOS_voidResumeTask(1);
}
void LED2(void)
{
	DIO_TogglePin(PINA1);
	
}