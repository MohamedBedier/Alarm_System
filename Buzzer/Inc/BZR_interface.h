/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : HAL                                **/
/** File Name : BZR_interface.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef BZR_INTERFACE_H_
#define BZR_INTERFACE_H_

/**
 * @brief : This function is used to Initialize Buzzer
 * @param[in] : BUZZER_Configs : this pointer of struct is used to inform about Port of BZR and Pin
 * @return : Local_u8ErrorState : this variable is used to carry error state value
 */
uint8_t BZR_u8Init(PinConfig_t * BUZZER_Configs);

/**
 * @brief : This function is used to turn on buzzer
 * @param[in] Copy_EnumBZRPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumBZRPin : This is an enum which carrying Led Pin
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t BZR_u8TurnOn(Port_t  Copy_EnumBZRPort ,Pin_t  Copy_EnumBZRPin);

/**
 * @brief : This function is used to turn off  buzzer
 * @param[in] Copy_EnumBZRPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumBZRPin : This is an enum which carrying Led Pin
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t BZR_u8TurnOff(Port_t  Copy_EnumBZRPort ,Pin_t  Copy_EnumBZRPin);

#endif /* BZR_INTERFACE_H_ */
