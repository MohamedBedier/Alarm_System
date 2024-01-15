/***********************************************************
* @file DoTasks.c
* @Author Abdullah AlsharQawy
* @Brief Here we perform the tasks ordered by the master MCU
***********************************************************/


#include <stdint.h>
#include <ErrType.h>


#include <SysTick_Interface.h>
#include <RCC_Interface.h>
#include <GPIO_Interface.h>
#include <BZR_interface.h>
#include <LED_Interface.h>
#include <ReceiveData.h>

#include <Screen_Wrapper.h>
#include <DoTasks_cfg.h>
#include <DoTasks_prv.h>
#include <DoTasks.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
extern NowTimeStruct_t NowTime_Struct;
extern uint16_t Rece_Ins;
extern Fptr InstructionsArr[TOTAL_INS];
extern char AlarmName[ALARM_LETTERS_NUM+1];

static char* Days[]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static char* Months[]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};



/***********************************************************
* @fn Tasks_Init
* @Brief Function you want to run when the third instruction is received
* @Param void
* @retval void
***********************************************************/
void Tasks_Init(void)
{
	/*Initialization of the LCD*/
	Screen_Init();
	/*Initialization of the Tasks functions*/
	UserTask_Init();
}

/***********************************************************
* @fn Screen_ShowTimeRunnable
* @Brief Function for showing received time from the master MCU on the Screen
* @Param void
* @retval void
***********************************************************/
void Screen_ShowTimeRunnable(void)
{
	Screen_SetCursor(0, 2);
	Screen_WriteNumberInTwoDigits(NowTime_Struct.NowTimeHOUR);
	Screen_WriteString(":");
	Screen_WriteNumberInTwoDigits(NowTime_Struct.NowTimeMIN);
	Screen_WriteString(":");
	Screen_WriteNumberInTwoDigits(NowTime_Struct.NowTimeSEC);
	Screen_SetCursor(0, 11);
	switch(NowTime_Struct.Now_pm_am)
	{
		case NOW_PM:
			Screen_WriteString(" PM");		break;
		case NOW_AM:
			Screen_WriteString(" AM");		break;
	}

	Screen_SetCursor(1, 1);
	Screen_WriteNumberInTwoDigits(NowTime_Struct.NowTimeDATE);
	Screen_WriteString("-");
	if(NowTime_Struct.NowTimeMONTH<=12)
	{
		Screen_WriteString(Months[NowTime_Struct.NowTimeMONTH-1]);
	}
	Screen_WriteString("-");
	Screen_WriteNumberInTwoDigits(NowTime_Struct.NowTimeYEAR);
	Screen_SetCursor(1, 12);
	if(NowTime_Struct.NowTimeDAY<=7)
	{
		Screen_WriteString(Days[NowTime_Struct.NowTimeDAY-1]);
	}
}

/***********************************************************
* @fn RequestedTask_Runnable
* @Brief Function for checking if there is an instruction has been received
* @Param void
* @retval void
***********************************************************/
void RequestedTask_Runnable(void)
{
	/*Checking if the Rece_Ins value has been changed*/
	if(Rece_Ins<TOTAL_INS)
	{
		/*Run the function of the task to the related received instruction*/
		InstructionsArr[(ReceInstruc_t)Rece_Ins]();
		/*Bringing Rece_Ins value back to the default value*/
		Rece_Ins=TOTAL_INS;
	}
}

