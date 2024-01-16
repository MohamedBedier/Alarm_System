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
 * @brief : This function is used to Initialize Buzzer
 * @param[in] : BUZZER_Configs : this pointer of struct is used to inform about Port of BZR and Pin
 * @return : Local_u8ErrorState : this variable is used to carry error state value
 */
uint8_t BZR_u8Init(PinConfig_t * BUZZER_Configs)
{
	/* define the Error State variable */
	uint8_t Local_u8ErrorState =OK;

	/* check on pointer is equal null or not */
	if (BUZZER_Configs != NULL )
	{
		/* initialize Bzr pin */
		GPIO_u8PinInit(BUZZER_Configs);
	}
	else
	{
		/* UPdate the Error State value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief : This function is used to turn on buzzer
 * @param[in] Copy_EnumBZRPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumLedPin : This is an enum which carrying Led Pin
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t BZR_u8TurnOn(Port_t  Copy_EnumBZRPort, Pin_t  Copy_EnumBZRPin)
{
	/* define the Error State variable */
	uint8_t Local_u8ErrorState =OK;

	if((Copy_EnumBZRPort >= PORTA && Copy_EnumBZRPort <= PORTG ) && (Copy_EnumBZRPin >= PIN0 && Copy_EnumBZRPin <= PIN15))
	{
		/* Turn on  Buzzer on by put on its pin high */
		GPIO_u8SetPinValue(Copy_EnumBZRPort,Copy_EnumBZRPin, PIN_HIGH);
	}else
	{
		/* update error state value */
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief : This function is used to turn off  buzzer
 * @param[in] Copy_EnumBZRPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumBZRPin : This is an enum which carrying Led Pin
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t BZR_u8TurnOff(Port_t  Copy_EnumBZRPort ,Pin_t  Copy_EnumBZRPin)
{
	/* define the Error State variable */
	uint8_t Local_u8ErrorState =OK;

	if((Copy_EnumBZRPort >= PORTA && Copy_EnumBZRPort <= PORTG ) && (Copy_EnumBZRPin >= PIN0 && Copy_EnumBZRPin <= PIN15))
	{
		/* Turn on  Buzzer on by put on its pin high */
		GPIO_u8SetPinValue(Copy_EnumBZRPort,Copy_EnumBZRPin, PIN_LOW);
	}else
	{
		/* update error state value */
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
