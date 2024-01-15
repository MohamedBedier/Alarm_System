/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : SCB_program.c                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/
#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "SCB_interface.h"
#include "SCB_Private.h"

/******************************/
/***    Global variabled    ***/
/******************************/


static void (*SCB_pfFuncPtr[NUM_SYS_EXCEPTIONS]) (void)= {NULL};

/**
 * @brief: This function to set the priority Group from user by send Copy_EnumProirtyGroup
 * @param[in] Copy_EnumProirtyGroup : this enum to carry priority Group
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */

uint8_t SCB_u8SetIRQPriorty(Priority_t  Copy_EnumProirtyGroup)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;
	/* define a variable to carry all bits of AIRCR */
	uint32_t Local_u32Mask_AllBitsOf_AIRCR = INIT_VALUE_BY_ZERO;

	/* protect our function by check on Copy_EnumProirtyGroup which will send by user*/
	if((Copy_EnumProirtyGroup >= SixteenGroup_ZeroSub) && (Copy_EnumProirtyGroup <= ZeroGroup_SixteenSub))
	{
		/* put the VECTKEY_VALUE */
		Local_u32Mask_AllBitsOf_AIRCR = (VECTKEY_VALUE << VECTKEY_START_BIT);/* VECTKEY_START_BIT = 16U*/

		/* put PRIGROUP IN Local_u32Mak_AllBitsOf_AIRCR */
		Local_u32Mask_AllBitsOf_AIRCR |= (Copy_EnumProirtyGroup << PRIGROUP_START_BIT);/* PRIGROUP_START_BIT = 8U*/

		/* Assign the value of Local_u32Mak_AllBitsOf_AIRCR in AIRCR */
		SCB->AIRCR = Local_u32Mask_AllBitsOf_AIRCR;

	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}


/**
 * @brief: This function to Enable FaultExceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8EnableFaultExceptions(SHCSR_t  Copy_EnumSHCSR)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;

	/* protect our function by check on Copy_EnumProirtyGroup which will send by user*/
	if((Copy_EnumSHCSR >= MEMFAULTENA) && (Copy_EnumSHCSR <= USGFAULTENA))
	{
		/* clear bit before using */
		SCB->SHCSR &= (~(ONE_VALUE << FAULT_ENA_START_BITS));
		/* SET fault exception enable by put 1 in its bit*/
		SCB->SHCSR |= (ONE_VALUE << Copy_EnumSHCSR);

	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: This function to Disable FaultExceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8DisableFaultExceptions(SHCSR_t  Copy_EnumSHCSR)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;

	/* protect our function by check on Copy_EnumProirtyGroup which will send by user*/
	if((Copy_EnumSHCSR >= MEMFAULTENA) && (Copy_EnumSHCSR <= USGFAULTENA))
	{
		/* clear bit to disable */
		CLR_BIT((SCB->SHCSR),Copy_EnumSHCSR);

	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: This function to Set pending for Fault Exceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8SetPendingFaultExceptions(SHCSR_t  Copy_EnumSHCSR)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;

	/* protect our function by check on Copy_EnumProirtyGroup which will send by user*/
	if((Copy_EnumSHCSR >= USGFAULTPENDED) && (Copy_EnumSHCSR <= SVCALLPENDED))
	{
		/* clear bit before using */
		SCB->SHCSR &= (~(ONE_VALUE << FAULT_PENDING_START_BITS));
		/* SET fault exception enable by put 1 in its bit*/
		SCB->SHCSR |= (ONE_VALUE << Copy_EnumSHCSR);

	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: This function to clear pending for Fault Exceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8ClearPendingFaultExceptions(SHCSR_t  Copy_EnumSHCSR)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;

	/* protect our function by check on Copy_EnumProirtyGroup which will send by user*/
	if((Copy_EnumSHCSR >= USGFAULTPENDED) && (Copy_EnumSHCSR <= SVCALLPENDED))
	{
		/* clear bit to disable pending flag */
		CLR_BIT((SCB->SHCSR),Copy_EnumSHCSR);

	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}


/**
 * @brief: This function to Set Call Back for Fault Exceptions from user by send address of the function which writting in APP
 * @param[in] Copy_EnumISRNames : this enum to carry ISR name
 * @param[in] Copy_pfFuncPtr : this is a pointer to function which carry address of the function which writting in APP
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8SetCallBack(ISRNames_t  Copy_EnumISRNames ,void (*Copy_pfFuncPtr)(void))
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState;

	/* protect our function by check on Copy_pfFuncPtr is refer to NULL OR NOT */
	if(Copy_pfFuncPtr != NULL)
	{
		/* put the address of function in app into global pointer to function */
		SCB_pfFuncPtr[Copy_EnumISRNames] = Copy_pfFuncPtr;
	}else
	{
		/* update Local_u8ErrorState value*/
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

/**
 * @brief : Reset_Handler ISR
 */
void Reset_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_Reset_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_Reset_Handler]();
	}
}

/**
 * @brief : NMI_Handler ISR
 */
void NMI_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_NMI_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_NMI_Handler]();
	}
}
/**
 * @brief : HardFault_Handler ISR
 */

void HardFault_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_HardFault_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_HardFault_Handler]();
	}
}
/**
 * @brief : MemManage_Handler ISR
 */
void MemManage_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_MemManage_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_MemManage_Handler]();
	}
}
/**
 * @brief : BusFault_Handler ISR
 */
void BusFault_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_BusFault_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_BusFault_Handler]();
	}
}

/**
 * @brief : UsageFault_Handler ISR
 */
void UsageFault_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_UsageFault_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_UsageFault_Handler]();
	}
}
/**
 * @brief : SVC_Handler ISR
 */
void SVC_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_SVC_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_SVC_Handler]();
	}
}
/**
 * @brief : DebugMon_Handler ISR
 */
void DebugMon_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_DebugMon_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_DebugMon_Handler]();
	}
}
/**
 * @brief : PendSV_Handler ISR
 */
void PendSV_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_PendSV_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_PendSV_Handler]();
	}
}
/**
 * @brief : SysTick_Handler ISR
 */
void SysTick_Handler (void)
{
	/* check on the global Array of pointer to function is still refer to NULL OR NOT */
	if(SCB_pfFuncPtr[ISRName_SysTick_Handler] != NULL)
	{
		SCB_pfFuncPtr[ISRName_SysTick_Handler]();
	}
}

