/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : HAL                                **/
/** File Name : BZR_program.c                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/
#include "stdint.h"
#include "ErrType.h"

#include "GPIO_interface.h"
#include "BZR_interface.h"

/**
 * @brief : This function is used to turn on buzzer
 * @param[in] : BUZZER_Configs : this pointer of struct is used to inform about Port of BZR and Pin
 * @return : Local_u8ErrorState
 */
uint8_t BZR_u8TurnOn(PinConfig_t * BUZZER_Configs)
{
	/* define the Error State variable */
	uint8_t Local_u8ErrorState =OK;

	/* check on pointer is equal null or not */
	if (BUZZER_Configs != NULL )
	{
		/* initialize Bzr pin */
		GPIO_u8PinInit(BUZZER_Configs);

		/* Turn on  Buzzer on by put on its pin high */
		GPIO_u8SetPinValue(BUZZER_Configs->Port, BUZZER_Configs->PinNum, PIN_HIGH);
	}
	else
	{
		/* UPdate the Error State value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


/**
 * @brief : This function is used to turn off  buzzer
 * @param[in] : BUZZER_Configs : this pointer of struct is used to inform about Port of BZR and Pin
 * @return : Local_u8ErrorState
 */
uint8_t BZR_u8TurnOff(PinConfig_t * BUZZER_Configs)
{
	/* define the Error State variable */
	uint8_t Local_u8ErrorState =OK;

	/* check on pointer is equal null or not */
	if (BUZZER_Configs != NULL )
	{
		/* initialize Bzr pin */
		GPIO_u8PinInit(BUZZER_Configs);

		/* Turn on  Buzzer on by put on its pin high */
		GPIO_u8SetPinValue(BUZZER_Configs->Port, BUZZER_Configs->PinNum, PIN_LOW);
	}
	else
	{
		/* UPdate the Error State value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}
