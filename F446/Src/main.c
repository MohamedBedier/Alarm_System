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
#include <LogInAndMenuOptions.h>



int main(void)
{
	uint8_t Local_u8ReceivedDataFromMenu = INIT_VALUE_BY_ZERO;
	SysTick_Init(SYSTICK_PROCESSOR_CLK, AHB_CLK/1000000);
	SysTick_Delayms(300);

	System_Init();
	GetTime_Init();
	SendData_Init();

	Local_u8ReceivedDataFromMenu = SystemLogIn();
	if(Local_u8ReceivedDataFromMenu!=TERMINATE_SYSTEM)
	{
		WorkingOnMenuOptions(Local_u8ReceivedDataFromMenu);
	}

	while(1)
	{
		if(Local_u8ReceivedDataFromMenu!=TERMINATE_SYSTEM)
		{
			ReturnToMenu();
			GetTime_Runnable();
			SysTick_Delayms(10);
			SendData_Runnable();
			CompareTime_Runnable();
		}
	}
    return 0;
}

