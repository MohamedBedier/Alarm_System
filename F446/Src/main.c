 /******************************************************************************
 * @file           : main.c
 * @author         : Abdullah AlsharQawy
 * @brief          : Main program body
 ******************************************************************************/


#include <stdint.h>
#include <ErrType.h>
#include <cnfg.h>

#include <SysTick_Interface.h>
#include <GetTime.h>
#include <SetTime.h>
#include <SendData.h>
#include <CompareTime.h>



int main(void)
{
	SysTick_Init(SYSTICK_PROCESSOR_CLK, AHB_CLK/1000000);
	SysTick_Delayms(300);

	GetTime_Init();
	SendData_Init();

	while(1)
	{
		GetTime_Runnable();
		SysTick_Delayms(10);
		SendData_Runnable();
		CompareTime_Runnable();
	}
    return 0;
}

