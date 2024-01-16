 /******************************************************************************
 * @file           : main.c
 * @author         : Abdullah AlsharQawy
 * @brief          : Main program body
 ******************************************************************************/


#include <stdint.h>
#include <ErrType.h>
#include <cnfg.h>

#include <SysTick_Interface.h>
#include <ReceiveData.h>
#include <DoTasks.h>



int main(void)
{
	SysTick_Init(SYSTICK_PROCESSOR_CLK, AHB_CLK/1000000);
	Tasks_Init();
	ReceData_Init();

	while(1)
	{
		Screen_ShowTimeRunnable();
		RequestedTask_Runnable();
		SysTick_Delayms(950);
	}

	return 0;
}





