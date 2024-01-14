/***********************************************************
* @file RTC_Wrapper.c
* @Author Abdullah AlsharQawy
* @Brief Functions for the RTC module wrapper functions
***********************************************************/
#include <stdint.h>
#include <ErrType.h>

#include <SetTime.h>
#include <DS1307_Interface.h>
#include <RTC_Wrapper.h>


void RTC_Init(void)
{
	DS1307_Init(OWN_ADDRESS, F_SCL);
}


void RTC_Enable(void)
{
	DS1307_Enable_RX(TIMEOUT);
}


void RTC_GetNowTime(NowTime_t TimeType, uint16_t* NowTime, uint16_t* Now_pm_am)
{
	DS1307_GetNowTime(TimeType, NowTime, Now_pm_am);
}

void RTC_SetTime(NowTimeStruct_t SetTimeStruct, TimeStyle_t TimeStyle)
{
	DS_Time_t SetTime=
	{
		.Seconds=SetTimeStruct.NowTimeSEC,
		.Minutes=SetTimeStruct.NowTimeMIN,
		.Hours=SetTimeStruct.NowTimeHOUR,
		.Day=SetTimeStruct.NowTimeDAY,
		.Date=SetTimeStruct.NowTimeDATE,
		.Month=SetTimeStruct.NowTimeMONTH,
		.Year=SetTimeStruct.NowTimeYEAR
	};

	DS1307_AmPm_t AmPM=(SetTimeStruct.Now_pm_am==NOW_AM)?_AM_:_PM_;
	DS1307_Style_t HourStyle=(TimeStyle==_24_STYLE)?_24_:_12_;

	DS1307_TimeSetting_Init(OWN_ADDRESS, F_SCL);
	DS1307_RunTimeSetting(SetTime, AmPM, HourStyle, TIMEOUT);
}








