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
 * @brief : This function is used to turn on buzzer
 * @param[in] : BUZZER_Configs : this pointer of struct is used to inform about Port of BZR and Pin
 * @return : Local_u8ErrorState
 */
uint8_t BZR_u8TurnOn(PinConfig_t * BUZZER_Configs);
/**
 * @brief : This function is used to turn off buzzer
 * @param[in] : BUZZER_Configs : this pointer of struct is used to inform about Port of BZR and Pin
 * @return : Local_u8ErrorState
 */
uint8_t BZR_u8TurnOff(PinConfig_t * BUZZER_Configs);

#endif /* BZR_INTERFACE_H_ */
