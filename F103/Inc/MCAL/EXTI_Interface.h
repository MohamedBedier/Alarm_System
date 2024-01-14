/*
 * EXTI_Interface.h
 *
 *  Created on: Dec 5, 2023
 *      Author: AlsharQawy
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

//@EXTI_Line_t
typedef enum
{
	EXTI0=0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	EXTI5,
	EXTI6,
	EXTI7,
	EXTI8,
	EXTI9,
	EXTI10,
	EXTI11,
	EXTI12,
	EXTI13,
	EXTI14,
	EXTI15,
	TOTAL_EXTI_LINES
}EXTI_Line_t;

//@EXTI_Edge_t
typedef enum
{
	RISING_EDGE=0,
	FALLING_EDGE,
	RISING_FALLING_EDGE,
}EXTI_Edge_t;

//@EXTI_MASK_t
typedef enum
{
	EXTI_MASKED=0,
	EXTI_UNMASKED,
}EXTI_MASK_t;

//@EXTI_PendFlag_t
typedef enum
{
	EXTI_NO_TRIGGER=0,
	EXTI_TRIGGERED,
}EXTI_PendFlag_t;

typedef struct
{
	EXTI_Line_t Line;
	EXTI_Edge_t Edge;
	EXTI_MASK_t Mask;
	void (*FPtr)(void);
}EXTIConfig_t;

void EXTI_voidEnableLine(EXTI_Line_t line);
void EXTI_voidDisableLine(EXTI_Line_t line);
void EXTI_voidSetEdgeTrigger(EXTI_Line_t Line, EXTI_Edge_t Edge);
EXTI_PendFlag_t EXTI_ReadPendingFlag(EXTI_Line_t line);
void EXTI_ClearPendingFlag(EXTI_Line_t line);
void EXTI_voidLineConfig(EXTIConfig_t* lineConfig);

#endif /* EXTI_INTERFACE_H_ */
