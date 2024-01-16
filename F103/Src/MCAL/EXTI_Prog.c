/***********************************************************
* @file EXTI_Prog
* @Author Abdullah AlsharQawy
* @Brief The main file for external interrupt peripheral
***********************************************************/

#include <stdint.h>
#include <Stm32F103xx.h>
#include <ErrType.h>

#include <EXTI_Interface.h>
#include <EXTI_prv.h>

/**********************************		GLOBAL VARIABLES	 ********************************/
static void (*EXTI_CallBackFunctions[TOTAL_EXTI_LINES])(void)={NullPtr};


/***********************************************************
* @fn EXTI_voidEnableLine
* @Brief Function for enabling different External interrupt sources
* @Param[in] line : The external interrupt line, option at @EXTI_Line_t enum
* @retval void
***********************************************************/
void EXTI_voidEnableLine(EXTI_Line_t line)
{
	EXTI_IMR|=(1<<line);
}

/***********************************************************
* @fn EXTI_voidDisableLine
* @Brief Function for disabling different External interrupt sources
* @Param[in] line : The external interrupt line, option at @EXTI_Line_t enum
* @retval void
***********************************************************/
void EXTI_voidDisableLine(EXTI_Line_t line)
{
	EXTI_IMR&=~(1<<line);
}

/***********************************************************
* @fn EXTI_voidSetEdgeTrigger
* @Brief Function for setting trigger edge
* @Param[in] line : The external interrupt line, option at @EXTI_Line_t enum
* @Param[in] Edge : The trigger edge type, option at @EXTI_Edge_t enum
* @retval void
***********************************************************/
void EXTI_voidSetEdgeTrigger(EXTI_Line_t Line, EXTI_Edge_t Edge)
{
	if(Edge==FALLING_EDGE)
	{
		EXTI_RTSR&=~(1<<(Line));
		EXTI_FTSR|= (1<<(Line));
	}
	else if(Edge==RISING_EDGE)
	{
		EXTI_FTSR&=~(1<<(Line));
		EXTI_RTSR|= (1<<(Line));
	}
	else if(Edge==RISING_FALLING_EDGE)
	{
		EXTI_FTSR|= (1<<(Line));
		EXTI_RTSR|= (1<<(Line));
	}
}

/***********************************************************
* @fn EXTI_ReadPendingFlag
* @Brief Function for reading pending flag
* @Param[in] line : The external interrupt line, option at @EXTI_Line_t enum
* @retval EXTI_PendFlag_t : pending flag status. options at @EXTI_PendFlag_t enum
***********************************************************/
EXTI_PendFlag_t EXTI_ReadPendingFlag(EXTI_Line_t line)
{
	return (EXTI_PR>>line)&1;
}

/***********************************************************
* @fn EXTI_ClearPendingFlag
* @Brief Function for clearing pending flag
* @Param[in] line : The external interrupt line, option at @EXTI_Line_t enum
* @retval void
***********************************************************/
void EXTI_ClearPendingFlag(EXTI_Line_t line)
{
	EXTI_PR=(1<<line);
}

/***********************************************************
* @fn EXTI_voidLineConfig
* @Brief Function for setting the external line
* @Param[in] lineConfig : The configuration parameters for external interrupt line
* @retval void
***********************************************************/
void EXTI_voidLineConfig(EXTIConfig_t* lineConfig)
{
	EXTI_IMR&=~(1<<(lineConfig->Line));
	EXTI_IMR|=((lineConfig->Mask)<<(lineConfig->Line));

	if(lineConfig->Edge==FALLING_EDGE)
	{
		EXTI_RTSR&=~(1<<(lineConfig->Line));
		EXTI_FTSR|= (1<<(lineConfig->Line));
	}
	else if(lineConfig->Edge==RISING_EDGE)
	{
		EXTI_FTSR&=~(1<<(lineConfig->Line));
		EXTI_RTSR|= (1<<(lineConfig->Line));
	}
	else if(lineConfig->Edge==RISING_FALLING_EDGE)
	{
		EXTI_FTSR|= (1<<(lineConfig->Line));
		EXTI_RTSR|= (1<<(lineConfig->Line));
	}

	EXTI_CallBackFunctions[lineConfig->Line]=lineConfig->FPtr;
}

/**********************************		IRQs	 ********************************/
void EXTI0_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI0);
	if(EXTI_CallBackFunctions[EXTI0]!=NullPtr)
	{
		EXTI_CallBackFunctions[EXTI0]();
	}
}
void EXTI1_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI1);
	if(EXTI_CallBackFunctions[EXTI1]!=NullPtr)
	{
		EXTI_CallBackFunctions[EXTI1]();
	}
}
void EXTI2_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI2);
	if(EXTI_CallBackFunctions[EXTI2]!=NullPtr)
	{
		EXTI_CallBackFunctions[EXTI2]();
	}
}
void EXTI3_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI3);
	if(EXTI_CallBackFunctions[EXTI3]!=NullPtr)
	{
		EXTI_CallBackFunctions[EXTI3]();
	}
}
void EXTI4_IRQHandler(void)
{
	EXTI_ClearPendingFlag(EXTI4);
	if(EXTI_CallBackFunctions[EXTI4]!=NullPtr)
	{
		EXTI_CallBackFunctions[EXTI4]();
	}
}
void EXTI9_5_IRQHandler(void)
{
	for(EXTI_Line_t line=EXTI5; line<=EXTI9; line++)
	{
		if(EXTI_ReadPendingFlag(line)==EXTI_TRIGGERED)
		{
			EXTI_ClearPendingFlag(line);
			if(EXTI_CallBackFunctions[line]!=NullPtr)
			{
				EXTI_CallBackFunctions[line]();
			}
		}
	}
}
void EXTI15_10_IRQHandler(void)
{
	for(EXTI_Line_t line=EXTI10; line<=EXTI15; line++)
	{
		if(EXTI_ReadPendingFlag(line)==EXTI_TRIGGERED)
		{
			if(EXTI_CallBackFunctions[line]!=NullPtr)
			{
				EXTI_CallBackFunctions[line]();
			}
			EXTI_ClearPendingFlag(line);
		}
	}
}





