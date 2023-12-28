/*************************************************************/
/*************************************************************/
/**                                                         **/
/** @file GPIO_Prog.c                                       **/
/** @author MOHAMED BEDIER MOHAMED                          **/
/** @brief  the GPIO main source file,						**/
/**           Including function' definitions               **/
/** @version 1.00                                           **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F103xx.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

/* according to least privilege make it static to save it private for this file only */
static GPIO_RegDef_t* GPIOPORT[GPIO_PERIPHERAL_NUM] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};


/**
 * @fn GPIO_u8PinInit
 * @brief the function initializes the GPIO pin according to the input parameter
 * @param[in] PinConfig : the initialization value of the pin
 * @retval Local_u8ErrorState
 */

uint8_t  GPIO_u8PinInit(const PinConfig_t* PinConfig)
{
	/* define error state variable */
	uint8_t Local_u8ErrorState=OK;

	/* check on pointer not equal NULL */
	if(PinConfig != NULL)
	{
		/* protect our program by : make a condition to save our program from passing any error values from user */
		if((PinConfig->Port >= PORTA) && (PinConfig->Port <= PORTG) && (PinConfig->PinNum <= PIN15) && (PinConfig->PinNum >= PIN0))
		{
			/* this variable to determine which register work on it and our result in range [0,1] : 0 refer to Low register and 1  refer to high register */
			uint8_t Local_u8RegNum =(PinConfig->PinNum) / CR_PIN_SHIFTING;

			/* this variable to determine which pin work on it and our result in range [0,15]  refers to our 15 pins  */
			uint8_t Local_u8BitNum =(PinConfig->PinNum) % CR_PIN_SHIFTING;

			/* Select GPIO mode : Input , Output with 10MHZ , Output with 2MHZ , Output with 50MHZ  */
			((GPIOPORT[PinConfig->Port] -> CR[Local_u8RegNum])  &= ~(MODE_MASK << (Local_u8BitNum  * MODE_PIN_ACCESS)));/* clear the MODE bits */
			((GPIOPORT[PinConfig->Port] -> CR[Local_u8RegNum])  |= ((PinConfig->Mode) << (Local_u8BitNum  * MODE_PIN_ACCESS)));/* SET the MODE bits */

			/* check on mode of pin is input or output[MAXSPEED_10MHZ , MAXSPEED_2MHZ, MAXSPEED_50MHZ] */
			if((PinConfig->Mode)== INPUT)
			{
				/* Select GPIO CNF if mode is INPUT : Analog mode ,  Floating input , Input with pull-up / pull-down  */
				((GPIOPORT[PinConfig->Port] -> CR[Local_u8RegNum])  &= ~(CNF_MASK << (Local_u8BitNum  * CNF_SHIFTING_PIN_ACCESS + CNF_PIN_ACCESS)));/* clear the CNF INPUT bits */
				((GPIOPORT[PinConfig->Port] -> CR[Local_u8RegNum])  |= ((PinConfig->CNF_InputMode) << (Local_u8BitNum  * CNF_SHIFTING_PIN_ACCESS + CNF_PIN_ACCESS)));/* SET the CNF INPUT bits */

			}else if(((PinConfig->Mode)== OUTPUT_MAXSPEED_10MHZ )|| ((PinConfig->Mode)== OUTPUT_MAXSPEED_2MHZ ) || ((PinConfig->Mode)== OUTPUT_MAXSPEED_50MHZ ))
			{
				/* Select GPIO CNF OUTPUT :  PUSH_PULL ,  OPEN_DRAIN input , ALT_FUNC_PUSH_PULL , ALT_FUNC_OPEN_DRAIN*/
				((GPIOPORT[PinConfig->Port] -> CR[Local_u8RegNum])  &= ~(CNF_MASK << (Local_u8BitNum  * CNF_SHIFTING_PIN_ACCESS + CNF_PIN_ACCESS)));/* clear the CNF OUTPUT bits */
				((GPIOPORT[PinConfig->Port] -> CR[Local_u8RegNum])  |= ((PinConfig->CNF_OutputMode) << (Local_u8BitNum  * CNF_SHIFTING_PIN_ACCESS + CNF_PIN_ACCESS)));/* SET the CNF OUTPUT bits */

			}else
			{
				/* update error state */
				Local_u8ErrorState=NOK;
			}
		}else
		{
			/* update error state */
			Local_u8ErrorState=NOK;
		}

	}else
	{
		/* pointer equal NULL update error state */
		Local_u8ErrorState=NULL_PTR_ERR;
	}

	/* return error state variable and end function */
	return Local_u8ErrorState;
}


/**
 *   @fn         GPIO_u8SetPinValue
 *   @brief      The function puts a value on a specific output pin
 *   @param[in]  Port: The port number, get options @Port_t enum
 *   @param[in]  PinNum: The pin number, get options @pin_t enum
 *   @param[in]  PinVal: The output value, get options @PinVal_t enum
 *   @retVal     Local_u8ErrorState
 */
uint8_t  GPIO_u8SetPinValue(Port_t Port , Pin_t PinNum ,PinVal_t PinVal)
{
	/* define error state variable */
	uint8_t Local_u8ErrorState=OK;

	/* protect our program by : make a condition to save our program from passing any error values from user */
	if((Port >= PORTA) && (Port <= PORTG) && (PinNum <= PIN15) && (PinNum >= PIN0))
	{
		if(PinVal == PIN_LOW)
		{
			/* put in PinNum in ODR  0 */
			GPIOPORT[Port]->ODR &= ~(ODR_MASK<< PinNum );
			/* another method and it is faster than method one bec it is an assignment operation only */
			/* GPIOPORT[Port]->BSRR = ODR_MASK << (16 + PinNum); */

		}else if(PinVal == PIN_HIGH)
		{
			/* put in  PinNum in ODR 1 */
			GPIOPORT[Port]->ODR |= (ODR_MASK<< PinNum );
			/* another method and it is faster than method one bec it is an assignment operation only */
			/* GPIOPORT[Port]->BSRR = 1 << PinNum; */
		}else
		{
			/* update error state */
			Local_u8ErrorState=NOK;
		}

	}else
	{
		/* update error state */
		Local_u8ErrorState=NOK;
	}

	/* return error state variable and end function */
	return Local_u8ErrorState;
}

/**
 *   @fn         GPIO_u8SetPinValue
 *   @brief      The function Toggles a value on a specific output pin
 *   @param[in]  Port: The port number, get options @Port_t enum
 *   @param[in]  PinNum: The pin number, get options @Pin_t enum
 *   @retVal     Local_u8ErrorState
 */

uint8_t  GPIO_u8TogglePinValue(Port_t Port , Pin_t PinNum )
{
	/* define error state variable */
	uint8_t Local_u8ErrorState=OK;

	/* protect our program by : make a condition to save our program from passing any error values from user */
	if((Port >= PORTA) && (Port <= PORTG) && (PinNum <= PIN15) && (PinNum >= PIN0))
	{
		/* toggle our pin */
		GPIOPORT[Port]->ODR ^= (ODR_MASK<<PinNum);

	}else
	{
		/* update error state */
		Local_u8ErrorState=NOK;
	}

	/* return error state variable and end function */
	return Local_u8ErrorState;
}

/**
 *   @fn         GPIO_u8SetPinValue
 *   @brief      The function Toggles a value on a specific output pin
 *   @param[in]  Port: The port number, get options @Port_t enum
 *   @param[in]  PinNum: The pin number, get options @Pin_t enum
 *   @param[out] PinVal: this is var pass by reference to carry the value of a specific bit
 *   @retVal     Local_u8ErrorState
 */
uint8_t  GPIO_u8ReadPinValue(Port_t Port , Pin_t PinNum ,PinVal_t* PinVal)
{
	/* define error state variable */
	uint8_t Local_u8ErrorState=OK;
	if(PinVal != NULL)
	{
		/* protect our program by : make a condition to save our program from passing any error values from user */
		if((Port >= PORTA) && (Port <= PORTG) && (PinNum <= PIN15) && (PinNum >= PIN0))
		{
			if(PinVal != NULL)
			{
				/* read our pin and put the result into PinVal [pointer] */
				*PinVal =((GPIOPORT[Port]->IDR >>PinNum)&IDR_MASK);
			}else
			{
				/* update error state */
				Local_u8ErrorState=NOK;
			}

		}else
		{
			/* update error state */
			Local_u8ErrorState=NOK;
		}
	}else
	{
		/* pointer equal NULL update error state */
			Local_u8ErrorState=NULL_PTR_ERR;
	}
	/* return error state variable and end function */
	return Local_u8ErrorState;
}
