/*
 * DoTasks.h
 *
 *  Created on: Jan 12, 2024
 *      Author: AlsharQawy
 */

#ifndef APP_DOTASKS_H_
#define APP_DOTASKS_H_

void Tasks_Init(void);
void Screen_ShowTimeRunnable(void);
void RequestedTask_Runnable(void);

/////////////////////////////////
#define  BUZZER_PORT       PORTB
#define  BUZZER_PIN        PIN9
#define  RED_LED_PORT      PORTA
#define  RED_LED_PIN       PIN1
#define  GREEN_LED_PORT    PORTC
#define  GREEN_LED_PIN     PIN15
#define  STOP_ALARM_PORT   PORTB
#define  STOP_ALARM_PIN    PIN11
//////////////////////////////////

#endif /* APP_DOTASKS_H_ */
