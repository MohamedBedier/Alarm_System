/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : EXTI_interface.h                            **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/**
 * @brief : this enum to carry EXTI lines options from line 0 to line 22 totally 23 EXTI_lines
 */
typedef enum
{
  EXTI_Line0=0,/**< EXTI_Line0 */
  EXTI_Line1,  /**< EXTI_Line1 */
  EXTI_Line2,  /**< EXTI_Line2 */
  EXTI_Line3,  /**< EXTI_Line3 */
  EXTI_Line4,  /**< EXTI_Line4 */
  EXTI_Line5,  /**< EXTI_Line5 */
  EXTI_Line6,  /**< EXTI_Line6 */
  EXTI_Line7,  /**< EXTI_Line7 */
  EXTI_Line8,  /**< EXTI_Line8 */
  EXTI_Line9,  /**< EXTI_Line9 */
  EXTI_Line10, /**< EXTI_Line10 */
  EXTI_Line11, /**< EXTI_Line11 */
  EXTI_Line12, /**< EXTI_Line12 */
  EXTI_Line13, /**< EXTI_Line13 */
  EXTI_Line14, /**< EXTI_Line14 */
  EXTI_Line15, /**< EXTI_Line15 */
  EXTI_Line16, /**< EXTI_Line16 */
  EXTI_Line17, /**< EXTI_Line17 */
  EXTI_Line18, /**< EXTI_Line18 */
  EXTI_Line19, /**< EXTI_Line19 */
  EXTI_Line20, /**< EXTI_Line20 */
  EXTI_Line21, /**< EXTI_Line21 */
  EXTI_Line22  /**< EXTI_Line22 */

}EXTI_Lines_t;

/**
 * @brief : this enum to carry at which edge trigger generate EXTI
 */
typedef enum
{
	FALLING_EDGE=0,           /**< generate trigger at FALLING_EDGE */
	RISING_EDGE,              /**< generate trigger at RISING_EDGE */
	FALLING_AND_RISING_EDGE   /**< generate trigger at FALLING_AND_RISING_EDGE */
}EdgeTrigger_t;

/**
 * @brief : this enum to carry EXTI state [ENABLED , DISABLED]
 */
typedef enum
{
	EXTI_ENABLED=0,
	EXTI_DISABLED
}EXTI_State_t;


/**
 *  @brief : this enum to carry BIT NUM
 */
typedef enum
{
	EXTI_TR0=0,/**< EXTI_TR0 */
	EXTI_TR1,  /**< EXTI_TR1 */
	EXTI_TR2,  /**< EXTI_TR2 */
	EXTI_TR3,  /**< EXTI_TR3 */
	EXTI_TR4,  /**< EXTI_TR4 */
	EXTI_TR5,  /**< EXTI_TR5 */
	EXTI_TR6,  /**< EXTI_TR6 */
	EXTI_TR7,  /**< EXTI_TR7 */
	EXTI_TR8,  /**< EXTI_TR8 */
	EXTI_TR9,  /**< EXTI_TR9 */
	EXTI_TR10, /**< EXTI_TR10 */
	EXTI_TR11, /**< EXTI_TR11 */
	EXTI_TR12, /**< EXTI_TR12 */
	EXTI_TR13, /**< EXTI_TR13 */
	EXTI_TR14, /**< EXTI_TR14 */
	EXTI_TR15, /**< EXTI_TR15 */
	EXTI_TR16, /**< EXTI_TR16 */
	EXTI_TR17, /**< EXTI_TR17 */
	EXTI_TR18, /**< EXTI_TR18 */
	RESERVED,  /**< RESERVED */
	EXTI_TR20, /**< EXTI_TR20 */
	EXTI_TR21, /**< EXTI_TR21 */
	EXTI_TR22, /**< EXTI_TR22 */

}EXTI_FALLING_AND_RISING_BitNum_t;

/**
 *  @brief : this enum to carry BIT NUM
 */
typedef enum
{
	EXTI_MR0=0,/**< EXTI_MR0 */
	EXTI_MR1,  /**< EXTI_MR1 */
	EXTI_MR2,  /**< EXTI_MR2 */
	EXTI_MR3,  /**< EXTI_MR3 */
	EXTI_MR4,  /**< EXTI_MR4 */
	EXTI_MR5,  /**< EXTI_MR5 */
	EXTI_MR6,  /**< EXTI_MR6 */
	EXTI_MR7,  /**< EXTI_MR7 */
	EXTI_MR8,  /**< EXTI_MR8 */
	EXTI_MR9,  /**< EXTI_MR9 */
	EXTI_MR10, /**< EXTI_MR10 */
	EXTI_MR11, /**< EXTI_MR11 */
	EXTI_MR12, /**< EXTI_MR12 */
	EXTI_MR13, /**< EXTI_MR13 */
	EXTI_MR14, /**< EXTI_MR14 */
	EXTI_MR15, /**< EXTI_MR15 */
	EXTI_MR16, /**< EXTI_MR16 */
	EXTI_MR17, /**< EXTI_MR17 */
	EXTI_MR18, /**< EXTI_MR18 */
	EXTI_MR19, /**< EXTI_MR19 */
	EXTI_MR20, /**< EXTI_MR20 */
	EXTI_MR21, /**< EXTI_MR21 */
	EXTI_MR22, /**< EXTI_MR22 */

}EXTI_IMR_AND_EMR_BitNum_t;




/**
 *  @brief : this enum to carry BIT NUM
 */
typedef enum
{
	EXTI_SWIER_OR_PR0=0,/**< EXTI_SWIER_OR_PR0 */
	EXTI_SWIER_OR_PR1,  /**< EXTI_SWIER_OR_PR1 */
	EXTI_SWIER_OR_PR2,  /**< EXTI_SWIER_OR_PR2 */
	EXTI_SWIER_OR_PR3,  /**< EXTI_SWIER_OR_PR3 */
	EXTI_SWIER_OR_PR4,  /**< EXTI_SWIER_OR_PR4 */
	EXTI_SWIER_OR_PR5,  /**< EXTI_SWIER_OR_PR5 */
	EXTI_SWIER_OR_PR6,  /**< EXTI_SWIER_OR_PR6 */
	EXTI_SWIER_OR_PR7,  /**< EXTI_SWIER_OR_PR7 */
	EXTI_SWIER_OR_PR8,  /**< EXTI_SWIER_OR_PR8 */
	EXTI_SWIER_OR_PR9,  /**< EXTI_SWIER_OR_PR9 */
	EXTI_SWIER_OR_PR10, /**< EXTI_SWIER_OR_PR10 */
	EXTI_SWIER_OR_PR11, /**< EXTI_SWIER_OR_PR11 */
	EXTI_SWIER_OR_PR12, /**< EXTI_SWIER_OR_PR12 */
	EXTI_SWIER_OR_PR13, /**< EXTI_SWIER_OR_PR13 */
	EXTI_SWIER_OR_PR14, /**< EXTI_SWIER_OR_PR14 */
	EXTI_SWIER_OR_PR15, /**< EXTI_SWIER_OR_PR15 */
	EXTI_SWIER_OR_PR16, /**< EXTI_SWIER_OR_PR16 */
	EXTI_SWIER_OR_PR17, /**< EXTI_SWIER_OR_PR17 */
	EXTI_SWIER_OR_PR18, /**< EXTI_SWIER_OR_PR18 */
	EXTI_SWIER_OR_PR19, /**< EXTI_SWIER_OR_PR19 */
	EXTI_SWIER_OR_PR20, /**< EXTI_SWIER_OR_PR20 */
	EXTI_SWIER_OR_PR21, /**< EXTI_SWIER_OR_PR21 */
	EXTI_SWIER_OR_PR22, /**< EXTI_SWIER_OR_PR22 */

}EXTI_SWIER_AND_PR_BitNum_t;


/**
 * @brief this is the configuration struct
 */
typedef struct
{
	EXTI_Lines_t   EXTI_Line;
	EdgeTrigger_t  EdgeTriggerSource;
	EXTI_State_t   EXTI_State;
	void (*CallBackFunc)(void);
}EXTI_Config_t;


/**
 * @brief : this function to initiate EXTI
 * @param[in] Copy_psEXTIConfig : pointer from struct which carrying EXTI registers
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t EXTI_u8Init(EXTI_Config_t *Copy_psEXTIConfig);

/**
 * @brief : this function to Enable Interrupt
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8EnableInterrupt(EXTI_IMR_AND_EMR_BitNum_t Copy_EnumEXTIBitNum);


/**
 * @brief : this function to Disable Interrupt
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8DisableInterrupt(EXTI_IMR_AND_EMR_BitNum_t Copy_EnumEXTIBitNum);
/**
 * @brief : this function to Clear Pending Flag
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8ClearPendingFlag(EXTI_SWIER_AND_PR_BitNum_t Copy_EnumEXTIBitNum);

/**
 * @brief : this function to Read Pending Flag
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @param[out] Copy_pu8PendingFlagValue this enum to carry Pending Flag Value
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8ReadPendingFlag(EXTI_SWIER_AND_PR_BitNum_t Copy_EnumEXTIBitNum , uint8_t* Copy_pu8PendingFlagValue);

/**
 * @brief : this function to Sense Control
 * @param[in] Copy_EnumSenseCTRL This enum to carry edge trigger options
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8SenseControl(EdgeTrigger_t Copy_EnumSenseCTRL, EXTI_FALLING_AND_RISING_BitNum_t Copy_EnumEXTIBitNum);

/**
 * @brief : this function to generate Software Interrupt Event
 * @param[in] Copy_EnumEXTIBitNum this enum to carry EXTI Bit Num
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t  EXTI_u8SoftwareInterruptEvent(EXTI_SWIER_AND_PR_BitNum_t Copy_EnumEXTIBitNum);


/**
 * @brief: This function to Set Call Back for EXTI from user by send address of the function which writting in APP
 * @param[in] Copy_EnumEXTI_Line : this enum to carry EXTI_Line
 * @param[in] Copy_pfFuncPtr : this is a pointer to function which carry address of the function which writting in APP
 * @return Local_u8ErrorState : this variable to carry ErrorState value
 */
uint8_t EXTI_u8SetCallBack(EXTI_Lines_t  Copy_EnumEXTI_Line ,void (*Copy_pfFuncPtr)(void));


#endif /* EXTI_INTERFACE_H_ */
