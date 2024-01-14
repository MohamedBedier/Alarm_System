/*
 * GetTime.h
 *
 *  Created on: Jan 6, 2024
 *      Author: AlsharQawy
 */

#ifndef APP_H_
#define APP_H_



/*@NowTimeStruct_t*/
typedef struct
{
	uint16_t NowTimeSEC;
	uint16_t NowTimeMIN;
	uint16_t NowTimeHOUR;
	uint16_t NowTimeDAY;
	uint16_t NowTimeDATE;
	uint16_t NowTimeMONTH;
	uint16_t NowTimeYEAR;
	uint16_t Now_pm_am;
}NowTimeStruct_t;



void GetTime_Init(void);
void GetTime_Runnable(void);
void voidFinishTransFlag_Setter(void);




#endif /* APP_H_ */
