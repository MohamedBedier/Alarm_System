/*************************************************************/
/*************************************************************/
/**                                                         **/
/** @file GPIO_interface.h                                  **/
/** @author MOHAMED BEDIER MOHAMED                          **/
/** @brief  the GPIO interface file,						**/
/**           Including function's prototype and enum       **/
/** @version 1.00                                           **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef  GPIO_INTERFACE_H_
#define  GPIO_INTERFACE_H_

/**
 * @brief this enum carries name of ports
 */
typedef enum 
{
	PORTA=0,/**< PORTA */
	PORTB,  /**< PORTB */
	PORTC,  /**< PORTC */
	PORTD,  /**< PORTD */
	PORTE,  /**< PORTE */
	PORTF,  /**< PORTF */
	PORTG   /**< PORTG */

}Port_t;


/**
 * @brief this enum carries name of PINs
 */
typedef enum 
{
	PIN0=0,/**< PIN0 */
	PIN1,  /**< PIN1 */
	PIN2,  /**< PIN2 */
	PIN3,  /**< PIN3 */
	PIN4,  /**< PIN4 */
	PIN5,  /**< PIN5 */
	PIN6,  /**< PIN6 */
	PIN7,  /**< PIN7 */
	PIN8,  /**< PIN8 */
	PIN9,  /**< PIN9 */
	PIN10, /**< PIN10 */
	PIN11, /**< PIN11 */
	PIN12, /**< PIN12 */
	PIN13, /**< PIN13 */
	PIN14, /**< PIN14 */
	PIN15  /**< PIN15 */
}Pin_t;


/**
 * @brief this enum carries options of mode of MC pins
 */
typedef enum 
{
	INPUT=0,              /**< INPUT */
	OUTPUT_MAXSPEED_10MHZ,/**< OUTPUT_MAXSPEED_10MHZ */
	OUTPUT_MAXSPEED_2MHZ, /**< OUTPUT_MAXSPEED_2MHZ */
	OUTPUT_MAXSPEED_50MHZ /**< OUTPUT_MAXSPEED_50MHZ */
}Mode_t;

/**
 * @brief this enum carries options of CNF AS input of MC pins
 */
typedef enum
{
	 ANALOG_MODE=0, /**< ANALOG_MODE */
	 FLOATING_INPUT,/**< FLOATING_INPUT */
	INPUT_PU_OR_PD, /**< INPUT_PU_OR_PD */
	Reserved_CFR    /**< Reserved_CFR */
}CNF_InputMode_t;

/**
 * @brief this enum carries options of CNF AS output of MC pins
 */
typedef enum
{
	PUSH_PULL=0,       /**< PUSH_PULL */
	OPEN_DRAIN,        /**< OPEN_DRAIN */
	ALT_FUNC_PUSH_PULL,/**< ALT_FUNC_PUSH_PULL */
	ALT_FUNC_OPEN_DRAIN/**< ALT_FUNC_OPEN_DRAIN */
}CNF_OutputMode_t;


/**
 * @brief this enum carries options of pin Value (PIN_LOW,PIN_HIGH)
 */
typedef enum 
{
	PIN_LOW=0,/**< PIN_LOW */
	PIN_HIGH  /**< PIN_HIGH */
}PinVal_t;

/**
 * @brief this struct to carries all parameter which sending to function to save stack consumption
 */

typedef struct
{
	Port_t  Port;
	Pin_t   PinNum;
	Mode_t  Mode;
	CNF_InputMode_t  CNF_InputMode;
	CNF_OutputMode_t  CNF_OutputMode;

}PinConfig_t;

/**
 * @fn GPIO_u8PinInit
 * @brief the function initializes the GPIO pin according to the input parameter
 * @param[in] PinConfig : the initialization value of the pin
 * @retval Local_u8ErrorState
 */

uint8_t  GPIO_u8PinInit(const PinConfig_t* PinConfig);
/**
 *   @fn         GPIO_u8SetPinValue
 *   @brief      The function puts a value on a specific output pin
 *   @param[in]  Port: The port number, get options @Port_t enum
 *   @param[in]  PinNum: The pin number, get options @pin_t enum
 *   @param[in]  PinVal: The output value, get options @PinVal_t enum
 *   @retVal     Local_u8ErrorState
 */
uint8_t  GPIO_u8SetPinValue(Port_t Port , Pin_t PinNum ,PinVal_t PinVal);
/**
 *   @fn         GPIO_u8TogglePinValue
 *   @brief      The function Toggles a value on a specific output pin
 *   @param[in]  Port: The port number, get options @Port_t enum
 *   @retVal     Local_u8ErrorState
 */
uint8_t  GPIO_u8TogglePinValue(Port_t Port , Pin_t PinNum );
/**
 *   @fn         GPIO_u8ReadPinValue
 *   @brief      The function Toggles a value on a specific output pin
 *   @param[in]  Port: The port number, get options @Port_t enum
 *   @param[in]  PinNum: The pin number, get options @Pin_t enum
 *   @param[out] PinVal: this is var pass by reference to carry the value of a specific bit
 *   @retVal     Local_u8ErrorState
 */
uint8_t  GPIO_u8ReadPinValue(Port_t Port , Pin_t PinNum ,PinVal_t* PinVal);


#endif
