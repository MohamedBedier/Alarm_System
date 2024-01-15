/***********************************************************
* @file GetTime.c
* @Author Abdullah AlsharQawy
* @Brief The main file for the function for setting the time of the RTC clock system module
***********************************************************/


#include <stdint.h>
#include <ErrType.h>

#include <RTC_Wrapper.h>
#include <GetTime.h>
#include <SetTime.h>


void Clock_SetTime(NowTimeStruct_t SetTimeStruct, TimeStyle_t TimeStyle)
{
	RTC_SetTime(SetTimeStruct, TimeStyle);
}
