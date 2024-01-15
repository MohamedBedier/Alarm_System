/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : SCB_interface.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_


/**
 * @brief : this enum to carry options of Priority
 */
typedef enum
{
	SixteenGroup_ZeroSub=3,/**< SixteenGroup_ZeroSub */
	EightGroup_TwoSub,     /**< EightGroup_TwoSub */
	FourGroup_FourSub,     /**< FourGroup_FourSub */
	TwoGroup_EightSub,     /**< TwoGroup_EightSub */
	ZeroGroup_SixteenSub   /**< ZeroGroup_SixteenSub */
}Priority_t;



/**
 * @brief : this enum to carry options of System handler control and state
 */


typedef enum
{
	MEMFAULTACT=0, /**< Memory management fault exception active bit, reads as 1 if exception is active */
	BUSFAULTACT,   /**< Bus fault exception active bit, reads as 1 if exception is active */
	Reserved_1,    /**< Reserved_1 */
	USGFAULTACT,   /**<  Usage fault exception active bit, reads as 1 if exception is active */
	Reserved_2,    /**< Reserved_2 */
	Reserved_3,    /**< Reserved_3 */
	Reserved_4,    /**< Reserved_4 */
	SVCALLACT,     /**< SVC call active bit, reads as 1 if SVC call is active */
	MONITORACT,    /**< Debug monitor active bit, reads as 1 if Debug monitor is active */
	Reserved_9,    /**< Reserved_9 */
	PENDSVACT,     /**< PendSV exception active bit, reads as 1 if exception is active */
	SYSTICKACT,    /**< SysTick exception active bit, reads as 1 if exception is active */
	USGFAULTPENDED,/**< Usage fault exception pending bit, reads as 1 if exception is pending */
	MEMFAULTPENDED,/**< Memory management fault exception pending bit, reads as 1 if exception is pending */
	BUSFAULTPENDED,/**< Bus fault exception pending bit, reads as 1 if exception is pending */
	SVCALLPENDED,  /**<  SVC call pending bit, reads as 1 if exception is pending */
	MEMFAULTENA, /**< Memory management fault enable bit, set to 1 to enable */
	BUSFAULTENA, /**< Bus fault enable bit, set to 1 to enable */
	USGFAULTENA  /**< Usage fault enable bit, set to 1 to enable */

}SHCSR_t;


/**
 * @brief : this enum to carry ISR names inside vector table
 */
typedef enum
{
	ISRName_Reset_Handler=0,
	ISRName_NMI_Handler,
	ISRName_HardFault_Handler,
	ISRName_MemManage_Handler,
	ISRName_BusFault_Handler,
	ISRName_UsageFault_Handler,
	ISRName_SVC_Handler,
	ISRName_DebugMon_Handler,
	ISRName_PendSV_Handler,
	ISRName_SysTick_Handler
}ISRNames_t;


/**
 * @brief: This function to set the priority Group from user by send Copy_EnumProirtyGroup
 * @param[in] Copy_EnumProirtyGroup : this enum to carry priority Group
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */

uint8_t SCB_u8SetIRQPriorty(Priority_t  Copy_EnumProirtyGroup);


/**
 * @brief: This function to Enable FaultExceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8EnableFaultExceptions(SHCSR_t  Copy_EnumSHCSR);

/**
 * @brief: This function to Disable FaultExceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8DisableFaultExceptions(SHCSR_t  Copy_EnumSHCSR);

/**
 * @brief: This function to Set pending for Fault Exceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8SetPendingFaultExceptions(SHCSR_t  Copy_EnumSHCSR);

/**
 * @brief: This function to clear pending for Fault Exceptions from user by send Copy_EnumSHCSR
 * @param[in] Copy_EnumSHCSR : this enum to carry options of System handler control and state
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8ClearPendingFaultExceptions(SHCSR_t  Copy_EnumSHCSR);

/**
 * @brief: This function to Set Call Back for Fault Exceptions from user by send address of the function which writting in APP
 * @param[in] Copy_EnumISRNames : this enum to carry ISR name
 * @param[in] Copy_pfFuncPtr : this is a pointer to function which carry address of the function which writting in APP
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t SCB_u8SetCallBack(ISRNames_t  Copy_EnumISRNames ,void (*Copy_pfFuncPtr)(void));


#endif /* SCB_INTERFACE_H_ */
