/*
 * SysCFG_Interface.h
 *
 *  Created on: Dec 5, 2023
 *      Author: AlsharQawy
 */

#ifndef SYSCFG_INTERFACE_H_
#define SYSCFG_INTERFACE_H_

//@SysCFGPort_t
typedef enum
{
	PORT_A=0,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G,
	PORT_H,
	SYSCFG_TOTAL_PORTS
}SysCFGPort_t;

//@EXTI_line_t
typedef enum
{
	EXTI_LINE_0=0,
	EXTI_LINE_1,
	EXTI_LINE_2,
	EXTI_LINE_3,
	EXTI_LINE_4,
	EXTI_LINE_5,
	EXTI_LINE_6,
	EXTI_LINE_7,
	EXTI_LINE_8,
	EXTI_LINE_9,
	EXTI_LINE_10,
	EXTI_LINE_11,
	EXTI_LINE_12,
	EXTI_LINE_13,
	EXTI_LINE_14,
	EXTI_LINE_15,
	SYSCFG_TOTAL_LINES
}EXTI_line_t;


ErrorStatus_t SysCFG_voidSetEXTI_Port(EXTI_line_t line, SysCFGPort_t port);

#endif /* SYSCFG_INTERFACE_H_ */
