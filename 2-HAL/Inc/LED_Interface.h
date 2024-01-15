/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : APP                                **/
/** File Name : LED_interface.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/**
 * @brief : this is an enum which carrying connection type of the led
 */
typedef  enum
{
	SOURCE_CONNECTION =0,/**< SOURCE_CONNECTION */
	SINK_CONNECTION      /**< SINK_CONNECTION */
}LED_u8ConnectionType_t;

/**
 * @brief: this a function to initiate LED Pin configuration its [PORT , PinNum , Mode , CNF_Output]
 * @param[in] PinConfig :this is a pointer from PinConfig_t struct which carry PinConfiguration
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t LED_u8PinInit(PinConfig_t *PinConfig);

/**
 * @brief: this a function to Turn Led ON
 * @param[in] Copy_EnumLedPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumLedPin : This is an enum which carrying Led Pin
 * @param[in] Copy_EnumLED_u8ConnectionType : THIS enum which carrying connection type of the led
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnON(Port_t  Copy_EnumLedPort ,Pin_t  Copy_EnumLedPin , LED_u8ConnectionType_t Copy_EnumLED_u8ConnectionType);

/**
 * @brief: this a function to Turn Led off
 * @param[in] Copy_EnumLedPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumLedPin : This is an enum which carrying Led Pin
 * @param[in] Copy_EnumLED_u8ConnectionType : THIS enum which carrying connection type of the led
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnOff(Port_t  Copy_EnumLedPort ,Pin_t  Copy_EnumLedPin, LED_u8ConnectionType_t Copy_EnumLED_u8ConnectionType);

/**
 * @brief: this a function to toggle Led
 * @param[in] Copy_EnumLedPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumLedPin : This is an enum which carrying Led Pin
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t LED_u8ToggleLed(Port_t  Copy_EnumLedPort ,Pin_t  Copy_EnumLedPin);



#endif /* LED_INTERFACE_H_ */
