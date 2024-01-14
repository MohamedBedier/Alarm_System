/***********************************************************
* @file CompareTime.c
* @Author Abdullah AlsharQawy
* @Brief The main file for comparing between time and the set alarms.
***********************************************************/


#include <stdint.h>
#include <ErrType.h>

#include <DoTasks_cfg.h>
#include <GetTime.h>
#include <SendData.h>
#include <CompareTime.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
extern NowTimeStruct_t NowTime_Struct;
NowTimeStruct_t AlarmsArr[TOTAL_ALARMS]={{10, 54, 8, 4, 13, 1, 24, 0},
										 {10, 56, 8, 4, 13, 1, 24, 0},
		                                 {10, 57, 8, 4, 13, 1, 24, 0}};
char* AlarmName;
char* AlarmNamesArr[TOTAL_ALARMS]={"ABDULLAH","ALI","AL_SHARQAWY"};



/***********************************************************
* @fn CompareTime_Runnable
* @brief Function for comparing between set alarms by the user and the time now to send a related instruction
* @param void
* @retval void
***********************************************************/
void CompareTime_Runnable(void)
{
	/*Loop over the whole available alarms*/
	for(uint8_t alarm=0; alarm<TOTAL_ALARMS; alarm++)
	{
		/*Checking if the set alarm time has come or not yet*/
		if(AlarmsArr[alarm].NowTimeMIN==NowTime_Struct.NowTimeMIN     &&
		   AlarmsArr[alarm].NowTimeHOUR==NowTime_Struct.NowTimeHOUR   &&
		   AlarmsArr[alarm].Now_pm_am==NowTime_Struct.Now_pm_am       &&
		   AlarmsArr[alarm].NowTimeDATE==NowTime_Struct.NowTimeDATE   &&
		   AlarmsArr[alarm].NowTimeMONTH==NowTime_Struct.NowTimeMONTH &&
		   AlarmsArr[alarm].NowTimeYEAR==NowTime_Struct.NowTimeYEAR   &&
		   NowTime_Struct.NowTimeYEAR!=0)
		{
			/*Getting the name of this alarm that was entered by the user*/
			AlarmName=AlarmNamesArr[alarm];
			/*Making the year=0 to not call it again*/
			AlarmsArr[alarm].NowTimeYEAR=0;
			/*Sending instruction to the other MCU*/
			SendData_TransmitInstruction(ALARM_ON_INS);
			break;
		}
	}
}







