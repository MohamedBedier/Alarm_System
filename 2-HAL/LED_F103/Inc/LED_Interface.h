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

#define  SOURCE_CONNECTION    0u
#define  SINK_CONNECTION      1u



typedef struct
{
	uint8_t LED_u8ConnectionType;
	uint8_t LED_u8PORT;
	uint8_t LED_u8PIN;
}LED_Struct;


/**
 * @brief: this a function to initiate LED Pin configuration its [PORT , PinNum , Mode , CNF_Output]
 * @param[in] PinConfig :this is a pointer from PinConfig_t struct which carry PinConfiguration
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t LED_u8PinInit(PinConfig_t *PinConfig);

/**
 * @brief: this a function to Turn Led ON
 * @param[in] puFrom_LED_Struct : pointer from LED_Struct to configure led port and pin and connection type
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnON(LED_Struct *puFrom_LED_Struct);
/**
 * @brief: this a function to Turn Led off
 * @param[in] puFrom_LED_Struct : pointer from LED_Struct to configure led port and pin and connection type
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnOff(LED_Struct *puFrom_LED_Struct);

/**
 * @brief: this a function to toggle Led
 * @param[in] puFrom_LED_Struct : pointer from LED_Struct to configure led port and pin and connection type
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t LED_u8ToggleLed(LED_Struct *puFrom_LED_Struct);



#endif /* LED_INTERFACE_H_ */
