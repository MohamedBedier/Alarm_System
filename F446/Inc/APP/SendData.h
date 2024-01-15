/*
 * SendData.h
 *
 *  Created on: Jan 8, 2024
 *      Author: AlsharQawy
 */

#ifndef APP_SENDDATA_H_
#define APP_SENDDATA_H_

#include <DoTasks_cfg.h>


#define  TRANSMIT_TIME_BYTES    8U
#define  ALARM_LETTERS_NUM      15U



void SendData_Init(void);
void SendData_TransmitInstruction(TransInstruc_t Trans_Ins);
void SendData_Runnable(void);

#endif /* APP_SENDDATA_H_ */
