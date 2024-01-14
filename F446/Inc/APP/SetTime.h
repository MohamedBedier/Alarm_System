/*
 * SetTime.h
 *
 *  Created on: Jan 13, 2024
 *      Author: AlsharQawy
 */

#ifndef APP_SETTIME_H_
#define APP_SETTIME_H_

#include <GetTime.h>

/*@SetAM_PM_t*/
typedef enum
{
	NOW_AM=0,
	NOW_PM
}SetAM_PM_t;

/*@TimeStyle_t*/
typedef enum
{
	_24_STYLE=0,
	_12_STYLE
}TimeStyle_t;


void Clock_SetTime(NowTimeStruct_t SetTimeStruct, TimeStyle_t TimeStyle);


#endif /* APP_SETTIME_H_ */
