/*
 * DS1307_Interface.h
 *
 *  Created on: Dec 28, 2023
 *      Author: AlsharQawy
 */

#ifndef DS1307_INTERFACE_H_
#define DS1307_INTERFACE_H_

/*@NowTime_t*/
typedef enum
{
	NOW_TIME_SECONDS=1,
	NOW_TIME_MINUTE,
	NOW_TIME_HOURS,
	NOW_TIME_DAY,
	NOW_TIME_DATE,
	NOW_TIME_MONTH,
	NOW_TIME_YEAR
}NowTime_t;

/*@DS1307_AmPm_t*/
typedef enum
{
	_AM_,
	_PM_
}DS1307_AmPm_t;

/*@DS1307_Style_t*/
typedef enum
{
	_24_,
	_12_
}DS1307_Style_t;


typedef struct
{
	uint8_t PointerRegister;
	uint8_t Seconds;
	uint8_t Minutes;
	uint8_t Hours;
	uint8_t Day;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
}DS_Time_t;



void DS1307_Init(uint8_t OwnAddress, uint32_t F_SCL_HZ);
ErrorStatus_t DS1307_Enable_RX(uint32_t TimeOut);
void DS1307_Disable_RX(void);
void DS1307_TimeSetting_Init(uint8_t OwnAddress, uint32_t F_SCL_HZ);
ErrorStatus_t DS1307_RunTimeSetting(DS_Time_t SetTime, DS1307_AmPm_t AmPM, DS1307_Style_t HourStyle, uint32_t TimeOut);
ErrorStatus_t DS1307_GetNowTime(NowTime_t TimeType, uint16_t* NowTime, uint16_t* Now_pm_am);

#endif /* DS1307_INTERFACE_H_ */
