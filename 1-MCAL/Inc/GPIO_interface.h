/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : GPIO_interface.h                            **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.01                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef  GPIO_INTERFACE_H_
#define  GPIO_INTERFACE_H_

/**
 * @brief: this is an enum which carrying PORT options from PORTA TO PORTH
 */
typedef enum 
{
	PORTA=0,/**< PORTA */
	PORTB,  /**< PORTB */
	PORTC,  /**< PORTC */
	PORTD,  /**< PORTD */
	PORTE,  /**< PORTE */
	PORTF,  /**< PORTF */
	PORTG,  /**< PORTG */
	PORTH   /**< PORTH */
}Port_t;


/**
 * @brief: this is an enum which carrying PIN options from PIN0 TO PIN15
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
 * @brief: this is an enum which carrying PIN Configurations
 */
typedef enum 
{
	INPUT=0,           /**< INPUT */
	OUTPUT,            /**< OUTPUT */
	ALTERNATE_FUNCTION,/**< ALTERNATE_FUNCTION */
	ANALOG             /**< ANALOG */
}Mode_t;

/**
 * @brief: this is an enum which carrying output speed options
 */
typedef enum 
{
	LOW=0, /**< LOW */
	MEDIUM,/**< MEDIUM */
	FAST,  /**< FAST */
	HIGH   /**< HIGH */
}OutputSpeed_t;


/**
 * @brief: this is an enum which carrying PIN Configurations state in output mode
 */
typedef enum 
{
	PUSH_PULL=0,/**< PUSH_PULL */
	OPEN_DRAIN  /**< OPEN_DRAIN */
}OutputType_t;

/**
 * @brief: this is an enum which carrying PIN Configurations state
 */
typedef enum 
{
	NOPULL=0,/**< NOPULL */
	PULLUP,  /**< PULLUP */
	PULLDOWN /**< PULLDOWN */
}PullUpDown_t;

/**
 * @brief: this is an enum which carrying PIN state [LOW or HIGH]
 */
typedef enum 
{
	PIN_LOW=0,/**< PIN_LOW */
	PIN_HIGH  /**< PIN_HIGH */
}PinVal_t;

/**
 * @brief: this is an enum which carrying Alternative Function options
 */
typedef enum 
{
	AF0=0,/**< AF0 */
	AF1,  /**< AF1 */
	AF2,  /**< AF2 */
	AF3,  /**< AF3 */
	AF4,  /**< AF4 */
	AF5,  /**< AF5 */
	AF6,  /**< AF6 */
	AF7,  /**< AF7 */
	AF8,  /**< AF8 */
	AF9,  /**< AF9 */
	AF10, /**< AF10 */
	AF11, /**< AF11 */
	AF12, /**< AF12 */
	AF13, /**< AF13 */
	AF14, /**< AF14 */
	AF15  /**< AF15 */
}AltFunc_t;

/**
 * @brief: this is a struct which carrying Pin Configurations
 */
typedef struct
{
	Port_t  Port;
	Pin_t   PinNum;
	Mode_t  Mode;
	OutputSpeed_t Speed;
	OutputType_t OutputType;
	PullUpDown_t PullType;
	AltFunc_t AltFunc;
}PinConfig_t;

/**
 * @fn GPIO_u8PinInit
 * @brief the function initializes the GPIO pin according to the input parameter
 * @param[in] PinConfig : the initialization value of the pin and this is a pointer of PinConfig_t struct
 * @retval Local_u8ErrorState : this variable is used to carry error state value
 */
uint8_t  GPIO_u8PinInit(const PinConfig_t* PinConfig);

/**
 * @fn GPIO_u8SetPinValue
 * @brief the function is used to set pin state value high or low according to the input parameter
 * @param[in] Port: this variable is used to determine port name.
 * @param[in] PinNum: this variable is used to determine pin name.
 * @param[in] PinVal: this variable is used to determine pin state value high or low.
 * @retval Local_u8ErrorState : this variable is used to carry error state value
 */
uint8_t  GPIO_u8SetPinValue(Port_t Port , Pin_t PinNum ,PinVal_t PinVal);

/**
 * @fn GPIO_u8TogglePinValue
 * @brief the function initializes the GPIO pin according to the input parameter
 * @param[in] Port: this variable is used to determine port name.
 * @param[in] PinNum: this variable is used to determine pin name.
 * @retval Local_u8ErrorState : this variable is used to carry error state value
 */
uint8_t  GPIO_u8TogglePinValue(Port_t Port , Pin_t PinNum );

/**
 * @fn GPIO_u8ReadPinValue
 * @brief the function initializes the GPIO pin according to the input parameter
 * @param[in] Port: this variable is used to determine port name.
 * @param[in] PinNum: this variable is used to determine pin name.
 * @param[out] PinVal: this is a pointer to carry pin value state.
 * @retval Local_u8ErrorState : this variable is used to carry error state value
 */
uint8_t  GPIO_u8ReadPinValue(Port_t Port , Pin_t PinNum ,PinVal_t* PinVal);


#endif
