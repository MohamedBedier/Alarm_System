/*************************************************************/
/*************************************************************/
/**                                                         **/
/**  LayerArchitecture : APP                                **/
/** File Name : LED_Program.c                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <stdint.h>
#include "BIT_MATH.h"
#include "ErrType.h"

#include "GPIO_interface.h"

#include "LED_Private.h"
#include "LED_Interface.h"


/**
 * @brief: this a function to initiate LED Pin configuration its [PORT , PinNum , Mode , CNF_Output]
 * @param[in] PinConfig :this is a pointer from PinConfig_t struct which carry PinConfiguration
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t LED_u8PinInit(PinConfig_t *PinConfig)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState =OK;

	/* check on pointer 'PinConfig' if not refer to NULL  */
	if(PinConfig !=NULL)
	{
		/* set Direction of LED Pins */
		GPIO_u8PinInit(PinConfig);
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: this a function to Turn Led ON
 * @param[in] Copy_EnumLedPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumLedPin : This is an enum which carrying Led Pin
 * @param[in] Copy_EnumLED_u8ConnectionType : THIS enum which carrying connection type of the led
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnON(Port_t  Copy_EnumLedPort ,Pin_t  Copy_EnumLedPin , LED_u8ConnectionType_t Copy_EnumLED_u8ConnectionType)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState = OK;

	/* Check on port and pin range  */
	if((Copy_EnumLedPort >= PORTA && Copy_EnumLedPort <= PORTG )&& (Copy_EnumLedPin >= PIN0 && Copy_EnumLedPin <= PIN15 ))
	{
		/* Check on Led connection  SOURCE_CONNECTION or SINK_CONNECTION */
		if(Copy_EnumLED_u8ConnectionType == SOURCE_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from MC) */
			GPIO_u8SetPinValue(Copy_EnumLedPort , Copy_EnumLedPin ,PIN_HIGH);

		}else if (Copy_EnumLED_u8ConnectionType == SINK_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from external component) */
			GPIO_u8SetPinValue(Copy_EnumLedPort , Copy_EnumLedPin , PIN_LOW);

		}else
		{
			/* Update Local_u8ErrorState */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NOK;
	}

	return Local_u8ErrorState ;
}

/**
 * @brief: this a function to Turn Led off
 * @param[in] Copy_EnumLedPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumLedPin : This is an enum which carrying Led Pin
 * @param[in] Copy_EnumLED_u8ConnectionType : THIS enum which carrying connection type of the led
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnOff(Port_t  Copy_EnumLedPort ,Pin_t  Copy_EnumLedPin, LED_u8ConnectionType_t Copy_EnumLED_u8ConnectionType)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState = OK;

	/* Check on port and pin range  */
	if((Copy_EnumLedPort >= PORTA && Copy_EnumLedPort <= PORTG )&& (Copy_EnumLedPin >= PIN0 && Copy_EnumLedPin <= PIN15 ))
	{
		/* Check on Led connection  SOURCE_CONNECTION or SINK_CONNECTION */
		if(Copy_EnumLED_u8ConnectionType == SOURCE_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from MC) */
			GPIO_u8SetPinValue(Copy_EnumLedPort , Copy_EnumLedPin ,PIN_LOW );

		}else if (Copy_EnumLED_u8ConnectionType == SINK_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from external component) */
			GPIO_u8SetPinValue(Copy_EnumLedPort , Copy_EnumLedPin ,PIN_HIGH );

		}else
		{
			/* Update Local_u8ErrorState */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NOK;
	}
	return Local_u8ErrorState ;
}

/**
 * @brief: this a function to toggle Led
 * @param[in] Copy_EnumLedPort : This is an enum which carrying Led Port
 * @param[in] Copy_EnumLedPin : This is an enum which carrying Led Pin
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t LED_u8ToggleLed(Port_t  Copy_EnumLedPort ,Pin_t  Copy_EnumLedPin)
{

	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState = OK;

	/* Check on port and pin range  */
	if((Copy_EnumLedPort >= PORTA && Copy_EnumLedPort <= PORTG )&& (Copy_EnumLedPin >= PIN0 && Copy_EnumLedPin <= PIN15 ))
	{
		/* toggle led if it is high convert to low and if it is low convert to high */
		GPIO_u8TogglePinValue(Copy_EnumLedPort,Copy_EnumLedPin);
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState =NOK;
	}
	return Local_u8ErrorState;
}
