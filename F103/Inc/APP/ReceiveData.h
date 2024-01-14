/*
 * SendData.h
 *
 *  Created on: Jan 8, 2024
 *      Author: AlsharQawy
 */

#ifndef APP_SENDDATA_H_
#define APP_SENDDATA_H_



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


#define  NOW_AM   0
#define  NOW_PM   1



void ReceData_Init(void);

#endif /* APP_SENDDATA_H_ */
