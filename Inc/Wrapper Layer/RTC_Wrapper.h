/*
 * RTC_Wrapper.h
 *
 *  Created on: Jan 13, 2024
 *      Author: AlsharQawy
 */

#ifndef WRAPPER_RTC_WRAPPER_H_
#define WRAPPER_RTC_WRAPPER_H_

#include <GetTime.h>
#include <SetTime.h>
#include <DS1307_Interface.h>


#define  OWN_ADDRESS  60
#define  F_SCL        10000
#define  TIMEOUT      10000

void RTC_Enable(void);
void RTC_Init(void);
void RTC_GetNowTime(NowTime_t TimeType, uint16_t* NowTime, uint16_t* Now_pm_am);
void RTC_SetTime(NowTimeStruct_t SetTimeStruct, TimeStyle_t TimeStyle);


#endif /* WRAPPER_RTC_WRAPPER_H_ */
