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
 * @param[in] puFrom_LED_Struct : pointer from LED_Struct to configure led port and pin and connection type
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnON(LED_Struct *puFrom_LED_Struct)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState = OK;

	/* check on pointer 'puFrom_LED_Struct' if not refer to NULL  */
	if(puFrom_LED_Struct != NULL)
	{
		/* Check on Led connection  SOURCE_CONNECTION or SINK_CONNECTION */
		if((puFrom_LED_Struct -> LED_u8ConnectionType) == SOURCE_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from MC) */
			GPIO_u8SetPinValue((puFrom_LED_Struct -> LED_u8PORT) , (puFrom_LED_Struct -> LED_u8PIN) ,PIN_HIGH);

		}else if (puFrom_LED_Struct -> LED_u8ConnectionType == SINK_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from external component) */
			GPIO_u8SetPinValue((puFrom_LED_Struct -> LED_u8PORT) , (puFrom_LED_Struct -> LED_u8PIN) , PIN_LOW);

		}else
		{
			/* Update Local_u8ErrorState */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState ;
}

/**
 * @brief: this a function to Turn Led off
 * @param[in] puFrom_LED_Struct : pointer from LED_Struct to configure led port and pin and connection type
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t  LED_u8LedTurnOff(LED_Struct *puFrom_LED_Struct)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState = OK;

	/* check on pointer 'puFrom_LED_Struct' if not refer to NULL  */
	if(puFrom_LED_Struct != NULL)
	{
		/* Check on Led connection  SOURCE_CONNECTION or SINK_CONNECTION */
		if((puFrom_LED_Struct -> LED_u8ConnectionType) == SOURCE_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from MC) */
			GPIO_u8SetPinValue((puFrom_LED_Struct -> LED_u8PORT) , (puFrom_LED_Struct -> LED_u8PIN) ,PIN_LOW );

		}else if (puFrom_LED_Struct -> LED_u8ConnectionType == SINK_CONNECTION)
		{
			/* set as SOURCE_CONNECTION (power from external component) */
			GPIO_u8SetPinValue((puFrom_LED_Struct -> LED_u8PORT) , (puFrom_LED_Struct -> LED_u8PIN) ,PIN_HIGH );

		}else
		{
			/* Update Local_u8ErrorState */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState ;
}
/**
 * @brief: this a function to toggle Led
 * @param[in] puFrom_LED_Struct : pointer from LED_Struct to configure led port and pin and connection type
 * @retval : Local_u8ErrorState : This is a variable to carry ErrorState value
 */
uint8_t LED_u8ToggleLed(LED_Struct *puFrom_LED_Struct)
{
	/* define a variable to carry ErrorState value */
	uint8_t Local_u8ErrorState = OK;
	/* check on pointer 'puFrom_LED_Struct' if not refer to NULL  */
	if(puFrom_LED_Struct != NULL)
	{
		/* toggle led if it is high convert to low and if it is low convert to high */
		GPIO_u8TogglePinValue((puFrom_LED_Struct->LED_u8PORT),(puFrom_LED_Struct->LED_u8PIN));

	}else
	{
		/* Update Local_u8ErrorState */
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState ;
}
