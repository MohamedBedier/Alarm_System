/***********************************************************
* @file GetTime.c
* @Author Abdullah AlsharQawy
* @Brief The main file for the function of getting data from the RTC clock system
***********************************************************/


#include <stdint.h>
#include <ErrType.h>

#include <RTC_Wrapper.h>
#include <I2C_Wrapper.h>
#include <GetTime.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
static volatile uint8_t u8FinishTransFlag=0;
NowTimeStruct_t NowTime_Struct;


/***********************************************************
* @fn GetTime_Init
* @brief Function for initiation of the RTC module to start get time
* @param void
* @retval void
***********************************************************/
void GetTime_Init(void)
{
	/*Initializing the RTC module*/
	RTC_Init();
	/*Starting getting time*/
	RTC_Enable();
}

/***********************************************************
* @fn GetTime_Runnable
* @brief Function for continuously getting time from the RTC module to save it in the NowTime struct
* @param void
* @retval void
***********************************************************/
void GetTime_Runnable(void)
{
	/*Getting seconds now*/
	RTC_GetNowTime(NOW_TIME_SECONDS, &(NowTime_Struct.NowTimeSEC), &(NowTime_Struct.Now_pm_am));
	/*Getting minutes now*/
	RTC_GetNowTime(NOW_TIME_MINUTE, &(NowTime_Struct.NowTimeMIN), &(NowTime_Struct.Now_pm_am));
	/*Getting the hour now and whether it is am or pm*/
	RTC_GetNowTime(NOW_TIME_HOURS, &(NowTime_Struct.NowTimeHOUR), &(NowTime_Struct.Now_pm_am));
	/*Getting the day of today*/
	RTC_GetNowTime(NOW_TIME_DAY, &(NowTime_Struct.NowTimeDAY), &(NowTime_Struct.Now_pm_am));
	/*Getting the date today*/
	RTC_GetNowTime(NOW_TIME_DATE, &(NowTime_Struct.NowTimeDATE), &(NowTime_Struct.Now_pm_am));
	/*Getting the current month*/
	RTC_GetNowTime(NOW_TIME_MONTH, &(NowTime_Struct.NowTimeMONTH), &(NowTime_Struct.Now_pm_am));
	/*Getting the current year*/
	RTC_GetNowTime(NOW_TIME_YEAR, &(NowTime_Struct.NowTimeYEAR), &(NowTime_Struct.Now_pm_am));

	/*If the RTC module finished transferring the whole time data*/
	if(u8FinishTransFlag==1)
	{
		/*Re-Enabling the DMA to keep receiving time*/
		RTC_Enable();
		/*Making the flag equal zero to not restart the DMA while it has not finished getting the whole time data yet*/
		u8FinishTransFlag=0;
	}
}

/***********************************************************
* @fn voidFinishTransFlag_Setter
* @brief This function will be called in the DMA I2C finish call-out function to show that is has already finished to start receiving again
* @param void
* @retval void
***********************************************************/
void voidFinishTransFlag_Setter(void)
{
	/*Setting a flag to my self to show that the RTC module has already finished transferring time data*/
	u8FinishTransFlag=1;
}
