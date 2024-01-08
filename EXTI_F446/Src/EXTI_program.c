/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : EXTI_Program.c                              **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/
#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "SYSCFG_interface.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"


/***    Global array of pointer to function to hold callback functions   ***/


static void (*EXTI_pfFuncPtr[NUM_OF_EXTI]) (void)= {NULL};


/**
 * @brief : this function to initiate EXTI
 * @param[in] Copy_psEXTIConfig : pointer from struct which carrying EXTI registers
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t EXTI_u8Init(EXTI_Config_t *Copy_psEXTIConfig)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	if(Copy_psEXTIConfig != NULL)
	{
		/*	setting trigger source configuration  */
		switch(Copy_psEXTIConfig->EdgeTriggerSource)
		{
		case RISING_EDGE:
			SET_BIT((EXTI->EXTI_RTSR),(Copy_psEXTIConfig->EXTI_Line));
			CLR_BIT((EXTI->EXTI_FTSR),(Copy_psEXTIConfig->EXTI_Line));/* to make sure that no both edge will happen */
			break;
		case FALLING_EDGE:
			SET_BIT((EXTI->EXTI_FTSR),(Copy_psEXTIConfig->EXTI_Line));
			CLR_BIT((EXTI->EXTI_RTSR),(Copy_psEXTIConfig->EXTI_Line));/* to make sure that no both edge will happen */
			break;
		case FALLING_AND_RISING_EDGE:
			SET_BIT(EXTI->EXTI_RTSR,(Copy_psEXTIConfig->EXTI_Line));
			SET_BIT(EXTI->EXTI_FTSR,(Copy_psEXTIConfig->EXTI_Line));
			break;
		default:Local_u8ErrorState=NOK;/* update Error state value  */
		}
		/*	setting trigger Enable or disable for the EXTI  */
		switch(Copy_psEXTIConfig->EXTI_State)
		{
		case EXTI_ENABLED:SET_BIT((EXTI->EXTI_IMR),(Copy_psEXTIConfig->EXTI_Line));break;
		case EXTI_DISABLED:CLR_BIT((EXTI->EXTI_IMR),(Copy_psEXTIConfig->EXTI_Line));break;
		default:Local_u8ErrorState=NOK;/* update Error state value  */
		}
		/*setting Callback function pointer */
		if(Copy_psEXTIConfig->CallBackFunc != NULL)
		{
			EXTI_pfFuncPtr[Copy_psEXTIConfig->EXTI_Line]=Copy_psEXTIConfig->CallBackFunc;
		}else
		{
			/* update Error state value  */
			Local_u8ErrorState=NULL_PTR_ERR;
		}

	}else
	{
		/* update Error state value  */
		Local_u8ErrorState=NULL_PTR_ERR;
	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}
/**
 * @brief : this function to Enable Interrupt
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8EnableInterrupt(EXTI_IMR_AND_EMR_BitNum_t Copy_EnumEXTIBitNum)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	if((Copy_EnumEXTIBitNum >= EXTI_MR0) && (Copy_EnumEXTIBitNum<= EXTI_MR22))
	{
		SET_BIT(EXTI->EXTI_IMR,Copy_EnumEXTIBitNum);
	}else
	{
		/* update Error state value  */
		Local_u8ErrorState=NOK;
	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}
/**
 * @brief : this function to Disable Interrupt
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8DisableInterrupt(EXTI_IMR_AND_EMR_BitNum_t Copy_EnumEXTIBitNum)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	if((Copy_EnumEXTIBitNum >= EXTI_MR0) && (Copy_EnumEXTIBitNum<= EXTI_MR22))
	{
		CLR_BIT(EXTI->EXTI_IMR,Copy_EnumEXTIBitNum);
	}else
	{
		/* update Error state value  */
		Local_u8ErrorState=NOK;
	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}
/**
 * @brief : this function to Clear Pending Flag
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8ClearPendingFlag(EXTI_SWIER_AND_PR_BitNum_t Copy_EnumEXTIBitNum)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;
	if((Copy_EnumEXTIBitNum >= EXTI_SWIER_OR_PR0) && (Copy_EnumEXTIBitNum <= EXTI_SWIER_OR_PR22))
	{
		/* note that : clear pending flag by 1  */
		SET_BIT(EXTI->EXTI_PR,Copy_EnumEXTIBitNum);
	}else
	{
		/* update Error state value  */
		Local_u8ErrorState=NOK;
	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}
/**
 * @brief : this function to generate Software Interrupt Event
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8SoftwareInterruptEvent(EXTI_SWIER_AND_PR_BitNum_t Copy_EnumEXTIBitNum)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;
	if((Copy_EnumEXTIBitNum >= EXTI_SWIER_OR_PR0) && (Copy_EnumEXTIBitNum <= EXTI_SWIER_OR_PR22))
	{
		/* note that : clear pending flag by 1  */
		SET_BIT(EXTI->EXTI_SWIER,Copy_EnumEXTIBitNum);
	}else
	{
		/* update Error state value  */
		Local_u8ErrorState=NOK;
	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}
/**
 * @brief : this function to Read Pending Flag
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @param[out] Copy_pu8PendingFlagValue this enum to carry Pending Flag Value
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8ReadPendingFlag(EXTI_SWIER_AND_PR_BitNum_t Copy_EnumEXTIBitNum , uint8_t* Copy_pu8PendingFlagValue)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	if(Copy_pu8PendingFlagValue != NULL)
	{
		if((Copy_EnumEXTIBitNum >= EXTI_SWIER_OR_PR0) && (Copy_EnumEXTIBitNum <= EXTI_SWIER_OR_PR22))
		{
			*Copy_pu8PendingFlagValue = GET_BIT((EXTI->EXTI_PR),Copy_EnumEXTIBitNum);
		}else
		{
			/* update Error state value  */
			Local_u8ErrorState=NOK;
		}
	}else
	{
		/* update Error state value  */
		Local_u8ErrorState=NULL_PTR_ERR;
	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}


/**
 * @brief : this function to Sense Control
 * @param[in] Copy_EnumSenseCTRL This enum to carry edge trigger options
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8SenseControl(EdgeTrigger_t Copy_EnumSenseCTRL, EXTI_FALLING_AND_RISING_BitNum_t Copy_EnumEXTIBitNum)
{
	/* define a variable to carry error state */
	uint8_t Local_u8ErrorState=OK;

	if((Copy_EnumEXTIBitNum >= EXTI_TR0) && (Copy_EnumEXTIBitNum<= EXTI_TR22)  && (Copy_EnumEXTIBitNum != RESERVED))
	{
		/*	setting trigger source configuration  */
		switch(Copy_EnumSenseCTRL)
		{
		case RISING_EDGE:
			SET_BIT((EXTI->EXTI_RTSR),Copy_EnumEXTIBitNum);
			CLR_BIT((EXTI->EXTI_FTSR),Copy_EnumEXTIBitNum);/* to make sure that no both edge will happen */
			break;
		case FALLING_EDGE:
			SET_BIT((EXTI->EXTI_FTSR),Copy_EnumEXTIBitNum);
			CLR_BIT((EXTI->EXTI_RTSR),Copy_EnumEXTIBitNum);/* to make sure that no both edge will happen */
			break;
		case FALLING_AND_RISING_EDGE:
			SET_BIT(EXTI->EXTI_RTSR,Copy_EnumEXTIBitNum);
			SET_BIT(EXTI->EXTI_FTSR,Copy_EnumEXTIBitNum);
			break;
		default:Local_u8ErrorState=NOK;/* update Error state value  */
		}
	}else
	{
		/* update Error state value  */
		Local_u8ErrorState=NOK;
	}

	/* return Error state value  and end the function */
	return Local_u8ErrorState;
}




/**
 * @brief: This function to Set Call Back for EXTI from user by send address of the function which writting in APP
 * @param[in] Copy_EnumEXTI_Line : this enum to carry EXTI_Line
 * @param[in] Copy_pfFuncPtr : this is a pointer to function which carry address of the function which writting in APP
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t EXTI_u8SetCallBack(EXTI_Lines_t  Copy_EnumEXTI_Line ,void (*Copy_pfFuncPtr)(void))
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;

	/* protect our function by check on Copy_pfFuncPtr is refer to NULL OR NOT */
	if(Copy_pfFuncPtr != NULL)
	{
		/* put the address of function in app into global pointer to function */
		EXTI_pfFuncPtr[Copy_EnumEXTI_Line] = Copy_pfFuncPtr;
	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

void EXTI0_IRQHandler()
{
	/* clear pending flag by 1*/
	SET_BIT((EXTI->EXTI_PR),EXTI_Line0);
	/* Calling ISR */
	EXTI_pfFuncPtr[EXTI_Line0]();
}

void EXTI1_IRQHandler()
{
	/* clear pending flag by 1*/
	SET_BIT((EXTI->EXTI_PR),EXTI_Line1);
	/* Calling ISR */
	EXTI_pfFuncPtr[EXTI_Line1]();
}

void EXTI2_IRQHandler()
{
	/* clear pending flag by 1*/
	SET_BIT((EXTI->EXTI_PR),EXTI_Line2);
	/* Calling ISR */
	EXTI_pfFuncPtr[EXTI_Line2]();
}

void EXTI3_IRQHandler()
{
	/* clear pending flag by 1*/
	SET_BIT((EXTI->EXTI_PR),EXTI_Line3);
	/* Calling ISR */
	EXTI_pfFuncPtr[EXTI_Line3]();
}

void EXTI4_IRQHandler()
{
	/* clear pending flag by 1*/
	SET_BIT((EXTI->EXTI_PR),EXTI_Line4);
	/* Calling ISR */
	EXTI_pfFuncPtr[EXTI_Line4]();
}

void EXTI9_5_IRQHandler()
{
	if(EXTI5_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line5);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line5]();
	}
	if(EXTI6_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line6);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line6]();
	}
	if(EXTI7_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line7);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line7]();
	}
	if(EXTI7_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line7);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line7]();
	}
	if(EXTI8_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line8);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line8]();
	}
	if(EXTI9_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line9);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line9]();
	}
	else
	{
		/* nothing */
	}
}

void EXTI15_10_IRQHandler()
{
	if(EXTI10_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line10);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line10]();
	}
	if(EXTI11_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line11);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line11]();
	}
	if(EXTI12_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line12);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line12]();
	}
	if(EXTI13_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line13);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line13]();
	}
	if(EXTI14_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line14);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line14]();
	}
	if(EXTI15_PENDING_FLAG == FLAG_RAISED)
	{
		/* clear pending flag by 1*/
		SET_BIT((EXTI->EXTI_PR),EXTI_Line15);
		/* Calling ISR */
		EXTI_pfFuncPtr[EXTI_Line15]();
	}
	else
	{
		/* nothing */
	}
}



