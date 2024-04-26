

#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"

#include "FreeRTOS.h"

#include "task.h"
#include "semphr.h"

void LCD1(void* pvParam);
void LCD2(void* pvParam);

xSemaphoreHandle LCDSem;
int main(void)
{
    DIO_Init();
	LCD_Init();
	
	xTaskCreate(&LCD1,NULL,250,NULL,1,NULL);
	xTaskCreate(&LCD2,NULL,250,NULL,1,NULL);
	
	LCDSem = xSemaphoreCreateCounting(1,1);
	if (LCDSem != NULL  )
	{
		/*Semphore is created successfully*/
	} 
	
	
	vTaskStartScheduler();
    while (1) 
    {
    }
}

void LCD1(void* pvParam)
{
	u8 State;
	while(1)
	{
		State = xSemaphoreTake(LCDSem,0);
		if (State == pdPASS)
		{
			LCD_WriteString("IamTask1");
			
			/*give the semphore after finishing with LCD*/
			xSemaphoreGive(LCDSem);
		} 
		else
		{
			/*do nothing*/
		}
		
		vTaskDelay(2);
	}
}

void LCD2(void* pvParam)
{
		u8 State;
		while(1)
		{
			State = xSemaphoreTake(LCDSem,0);
			if (State == pdPASS)
			{
				LCD_WriteString("IamTask2");
				
				/*give the semphore after finishing with LCD*/
				xSemaphoreGive(LCDSem);
			}
			else
			{
				/*do nothing*/
			}
			
			vTaskDelay(2);
		}
}