/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : USART_program.c                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <ErrType.h>
#include <stdint.h>
#include "BIT_MATH.h"
#include "Stm32F446xx.h"

#include "USART_interface.h"
#include "USART_CFG.h"
#include "USART_private.h"


/* according to least privilege make it static to save it private for this file only */
/* This is an array from USART_RegDef_t struct which carrying USART Numbers */
static USART_RegDef_t* USART[USART_PERIPHERAL_NUM] = {USART1,USART2,USART3,UART4,UART5,USART6};

/* THIS is an array of pointers to functions to hold ISR  Callbacks */
static void(*USART_puNotificationFunc[USART_PERIPHERAL_NUM])(void) = {NULL};

/* this is a Global variable which carrying Flag status FLAG_IS_IDLE OR FLAG_IS_BUSY */
static uint8_t USART_u8BusyFlag = FLAG_IS_IDLE;


/**
 * @brief: this static function is used to Set Baud Rate
 * @param USRAT_PinConfig : this is a pointer of struct which carrying usart configuration
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
static uint8_t  USART_u8SetBaudRate(USRAT_PinConfig_t* USRAT_PinConfig)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;

	/* This is a variable which carrying the result of (8 * (2 - oversampling option(0 or 1)) * baud rate) */
	uint32_t Local_u32DemoOfUSART_Div = INIT_VALUE_BY_ZERO;

	/* This is a variable which carrying the result of ( (float) F_PLK /(float)(Local_u32DemoOfUSART_Div) ) */
	float Local_floatUSART_DIV ;

	/* This is a variable which carrying MintissaPart */
	uint32_t Local_u32MintissaPart = INIT_VALUE_BY_ZERO;
	/* This is a variable which carrying FractionPart*/
	uint32_t Local_u32FractionPart = INIT_VALUE_BY_ZERO;

	/* check on the pointer of struct is equal NULL or Not equal NULL */
	if(USRAT_PinConfig != NULL)
	{

		/* calculate the value of USART_DIV before divided it into (MintissaPart,FractionPart) */
		Local_u32DemoOfUSART_Div =(uint32_t)(EIGHT_VAL*(TWO_VAL - (USRAT_PinConfig->OverSampling))*(USRAT_PinConfig->BaudRate));
		Local_floatUSART_DIV = (((float)F_PCLK /(float)Local_u32DemoOfUSART_Div));
		Local_floatUSART_DIV *= ONE_THOUSAND_VAL;

		/* calculate the value of MintissaPart and Put it into the MintissaPart bits */
		Local_u32MintissaPart = (uint32_t)Local_floatUSART_DIV / ONE_THOUSAND_VAL ;
		USART[USRAT_PinConfig->USART_Num]->USART_BRR = Local_u32MintissaPart << DIV_MANTISSA;

		/* calculate the value of FractionPart and Put it into the FractionPart bits */
		Local_u32FractionPart = (uint32_t)Local_floatUSART_DIV % ONE_THOUSAND_VAL ;

		/* check on Oversamoling , work as over16 or over8 */
		if(USRAT_PinConfig->OverSampling == ZERO_VALUE)
		{
			Local_u32FractionPart *= SIXTEEN_VAL;

			Local_u32FractionPart += HALF_THOUSAND_VAL;

			Local_u32FractionPart /=ONE_THOUSAND_VAL;

			USART[USRAT_PinConfig->USART_Num]->USART_BRR |= Local_u32FractionPart << DIV_FRACTION;
		}else
		{
			Local_u32FractionPart *= EIGHT_VAL;

			Local_u32FractionPart += HALF_THOUSAND_VAL;

			Local_u32FractionPart /=ONE_THOUSAND_VAL;

			USART[USRAT_PinConfig->USART_Num]->USART_BRR |= Local_u32FractionPart << DIV_FRACTION;
		}
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function is used to enable usart interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_EnumInterrupt_Name : this is an enum which carrying interrupt name
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t USART_u8EnableInt(USART_Num_t Copy_EnumUSART_Num ,USART_Int_t  Copy_EnumInterrupt_Name)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on USART Interrupt Name */
	if(Copy_EnumInterrupt_Name == ERROR_INT_EN)
	{
		/* Clear bit Of the interrupt before you work on it */
		USART[Copy_EnumUSART_Num]->USART_CR3 &=(~(SET_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of Copy_EnumInterrupt_Name */
		USART[Copy_EnumUSART_Num]->USART_CR3 |= (SET_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name);


	}else if((Copy_EnumInterrupt_Name == IDLE_INT_EN) || (Copy_EnumInterrupt_Name == TC_INT_EN)
			|| (Copy_EnumInterrupt_Name == RXNE_INT_EN) || (Copy_EnumInterrupt_Name == TXE_INT_EN)
			|| (Copy_EnumInterrupt_Name == PE_INT_EN) || (Copy_EnumInterrupt_Name == CTS_INT_EN))
	{

		/* Clear bit Of the interrupt before you work on it */
		USART[Copy_EnumUSART_Num]->USART_CR1 &=(~(SET_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of Copy_EnumInterrupt_Name */
		USART[Copy_EnumUSART_Num]->USART_CR1 |= (SET_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name);

	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NOK;
	}

	return Local_u8ErrorState;
}

/**
 * @brief this function is used to Disable usart interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_EnumInterrupt_Name : this is an enum which carrying interrupt name
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t USART_u8DisableInt(USART_Num_t Copy_EnumUSART_Num ,USART_Int_t  Copy_EnumInterrupt_Name)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on USART Interrupt Name */
	if(Copy_EnumInterrupt_Name == ERROR_INT_EN)
	{
		/* Clear bit Of the interrupt before you work on it */
		USART[Copy_EnumUSART_Num]->USART_CR3 &=(~(SET_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of Copy_EnumInterrupt_Name */
		USART[Copy_EnumUSART_Num]->USART_CR3 |= (CLR_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name);


	}else if((Copy_EnumInterrupt_Name == IDLE_INT_EN) || (Copy_EnumInterrupt_Name == TC_INT_EN)
			|| (Copy_EnumInterrupt_Name == RXNE_INT_EN) || (Copy_EnumInterrupt_Name == TXE_INT_EN)
			|| (Copy_EnumInterrupt_Name == PE_INT_EN) || (Copy_EnumInterrupt_Name == CTS_INT_EN))
	{

		/* Clear bit Of the interrupt before you work on it */
		USART[Copy_EnumUSART_Num]->USART_CR1 &=(~(SET_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of Copy_EnumInterrupt_Name */
		USART[Copy_EnumUSART_Num]->USART_CR1 |= (CLR_USART_INTERRUPT_MASK << Copy_EnumInterrupt_Name);

	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NOK;
	}

	return Local_u8ErrorState;
}
/**
 * @brief: this function is used to initiate USART
 * @param USRAT_PinConfig : this is a pointer of struct which carrying usart configuration
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8Init(USRAT_PinConfig_t* USRAT_PinConfig)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;

	/* check on the pointer of struct is equal NULL or Not equal NULL */
	if(USRAT_PinConfig != NULL)
	{
		/* check on usart number range */
		if((USRAT_PinConfig->USART_Num >= USART1_peri) && (USRAT_PinConfig->USART_Num <= USART6_peri))
		{
			/* check on WordLength of usart data and parity */
			switch(USRAT_PinConfig->WordLength)
			{
			case EIGHT_BIT:CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,M);break;/* WordLength by 8 */
			case NINE_BIT:SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,M);break;/* WordLength by 9 */
			default: Local_u8ErrorState =NOK;break;/* UPDATE Error state value */
			}


			/* check on Parity Selection enabled or disabled of usart farme */
			if (USRAT_PinConfig->Parity == PARITY_ENABLED)
			{
				/* Parity enabled */
				SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,PCE);

				/* parity is enabled  this option is valid [even,odd] parity */
				if(USRAT_PinConfig->Parity_Sel == EVEN_PARITY)
				{
					/* even parity */
					CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,PS);
				}else if (USRAT_PinConfig->Parity_Sel == ODD_PARITY)
				{
					/* odd parity */
					SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,PS);
				}else
				{
					/* UPDATE Error state value */
					Local_u8ErrorState =NOK;
				}
			}else if(USRAT_PinConfig->Parity == PARITY_DISABLED)
			{
				/* parity disabled */
				CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,PCE);
			}else
			{
				/* UPDATE Error state value */
				Local_u8ErrorState =NOK;
			}

			/* check on StopBit of usart Frame */
			if((USRAT_PinConfig->StopBit >= ONE_BIT) && (USRAT_PinConfig->StopBit <= ONE_AND_HALF_BIT))
			{
				USART[USRAT_PinConfig->USART_Num]->USART_CR2 &= (~(STOP_BITS_MASK_VAL << STOP_BIT0));
				USART[USRAT_PinConfig->USART_Num]->USART_CR2 |= ((USRAT_PinConfig->StopBit) << STOP_BIT0);
			}else
			{
				/* UPDATE Error state value */
				Local_u8ErrorState =NOK;
			}


			/* if you want to work with interrupt */
			if(USRAT_PinConfig->USART_Int_Sts == USART_INT_ENABLED)
			{
				USART_u8EnableInt(USRAT_PinConfig->USART_Num,USRAT_PinConfig->USART_Int_Name);
			}


			/* check on DMA_ Selection For transmit or receive*/
			switch(USRAT_PinConfig->DMA_Sel)
			{
			case DMA_FOR_TRANSMIT:
				CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,DMAR);
				SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,DMAT);
				break;
			case DMA_FOR_RECEIVE:
				CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,DMAT);
				SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,DMAR);
				break;
			case DMA_DISABLED:
				CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,DMAT);
				CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,DMAR);
				break;
			default: Local_u8ErrorState =NOK;break;/* UPDATE Error state value */
			}

			/* Set baud rate */
			USART_u8SetBaudRate(USRAT_PinConfig);


			/* check on mode of usart RE , TE and RE_TE */
			switch(USRAT_PinConfig->Mode)
			{
			case RX_MODE:
				CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,TE);/* Transmit line disabled */
				SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,RE);/* Receive line enabled */
				break;
			case TX_MODE:
				CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,RE);/* Receive line disabled */
				SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,TE);/* Transmit line enabled */
				break;
			case RX_AND_TX_MODE:
				SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,RE);/* Receive line enabled */
				SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,TE);/* Transmit line enabled */
				break;
			default: Local_u8ErrorState =NOK;break;/* UPDATE Error state value */
			}


			/* check on OverSampling of usart in Receove mode */
			switch(USRAT_PinConfig->OverSampling)
			{
			case OVER16_EN:CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,OVER8);break;/* oversampling by 16 */
			case OVER8_EN:SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,OVER8);break;/* oversampling by 8 */
			default: Local_u8ErrorState =NOK;break;/* UPDATE Error state value */
			}

			/* When only SYNCHRONOUS mode is enabled  this option is valid [CTS,RTS] */
			if (USRAT_PinConfig->Synch_Asynch == SYNCHRONOUS)
			{
				/* check on HardWare_FlowControl Selection  */
				switch(USRAT_PinConfig->HardWare_FlowControl)
				{
				case H_W_FLOW_CTRL_DISABLED:
					CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,CTSE);
					CLR_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,RTSE);
					break;
				case H_W_FLOW_CTRL_ENABLED:
					SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,CTSE);
					SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR3,RTSE);
					break;
				default: Local_u8ErrorState =NOK;break;/* UPDATE Error state value */
				}
			}

			/* Enable usart */
			SET_BIT(USART[USRAT_PinConfig->USART_Num]->USART_CR1,UE);
		}else
		{
			/* UPDATE Error state value */
			Local_u8ErrorState =NOK;
		}


	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to send data using USART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_u8Data : this variable is used to carry data
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8SendData(USART_Num_t Copy_EnumUSART_Num ,uint8_t Copy_u8Data)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;

	/* this is a variable to count until timeout value */
	uint32_t Local_u32TimeOutCounter=INIT_VALUE_BY_ZERO;

	/* check on Copy_EnumUSART_Num Range */
	if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
	{
		/* Clear flags before working on them */
		CLR_BIT(USART[Copy_EnumUSART_Num]->USART_SR,TC);

		/* wait until transmit buffer is ready */
		while((GET_BIT(USART[Copy_EnumUSART_Num]->USART_SR,TXE)) != FLAG_RAISED  && (Local_u32TimeOutCounter < UART_TIME_OUT_VAL ))
		{
			/* increment Local_u32TimeOutCounter by 1 */
			Local_u32TimeOutCounter++;
		}

		if(Local_u32TimeOutCounter >= UART_TIME_OUT_VAL)
		{
			/* loop is broken because UART isn't Transmit data until timeout is passed */
			Local_u8ErrorState = TIMEOUT_ERR;
		}else
		{
			/* put data into data register */
			USART[Copy_EnumUSART_Num]->USART_DR = Copy_u8Data;

			/* wait until transmit buffer is ready */
			while((GET_BIT(USART[Copy_EnumUSART_Num]->USART_SR,TC)) != FLAG_RAISED);

			/* Clear flags */
			CLR_BIT(USART[Copy_EnumUSART_Num]->USART_SR,TC);
		}
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to send data using Interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_u8Data : this variable is used to carry data
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8SendData_IT(USART_Num_t Copy_EnumUSART_Num ,uint8_t Copy_u8Data)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumUSART_Num Range */
	if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
	{
		/* Clear flags before working on them */
		CLR_BIT(USART[Copy_EnumUSART_Num]->USART_SR,TC);

		/* put data into data register */
		USART[Copy_EnumUSART_Num]->USART_DR = Copy_u8Data;

	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to send array of data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t UART_u8SendBufferSynch(USART_Num_t Copy_EnumUSART_Num , uint8_t *Copy_pu8BufferArr,uint8_t Copy_u8SizeOfArr)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;
	/* this variable is used to count up size of array to have the next element */
	uint8_t Local_u8Count = INIT_VALUE_BY_ZERO;

	/* check on Copy_EnumUSART_Num Range */
	if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
	{
		/* if UART is not BUSY */
		if(USART_u8BusyFlag == FLAG_IS_IDLE)
		{
			/* UART is now BUSY  */
			USART_u8BusyFlag = FLAG_IS_BUSY;

			/* Send buffer */
			for(Local_u8Count = ZERO_VALUE ; Local_u8Count <Copy_u8SizeOfArr ; Local_u8Count++)
			{
				/* send buffer array */
				USART_u8SendData(Copy_EnumUSART_Num, (Copy_pu8BufferArr[Local_u8Count]));
			}
			/* UART Is now IDLE */
			USART_u8BusyFlag = FLAG_IS_IDLE;
		}
		else
		{
			/* UART was busy , assign the error state */
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NOK;
	}

	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to send array of data using Interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t UART_u8SendBufferSynch_IT(USART_Num_t Copy_EnumUSART_Num  , uint8_t *Copy_pu8BufferArr,uint8_t Copy_u8SizeOfArr)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;
	/* this variable is used to count up size of array to have the next element */
	uint8_t Local_u8Count = INIT_VALUE_BY_ZERO;

	/* check on Copy_EnumUSART_Num Range */
	if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
	{
		/* if UART is not BUSY */
		if(USART_u8BusyFlag == FLAG_IS_IDLE)
		{
			/* UART is now BUSY  */
			USART_u8BusyFlag = FLAG_IS_BUSY;

			/* send buffer array */
			USART_u8SendData_IT(Copy_EnumUSART_Num, (Copy_pu8BufferArr[Local_u8Count]));

			/* UART Is now IDLE */
			USART_u8BusyFlag = FLAG_IS_IDLE;
		}
		else
		{
			/* UART was busy , assign the error state */
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
/**
 * @brief: this function is used to Receive data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8Received_Data : this is a pointer of uint16 which carrying data received by usart.
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8ReceiveData(USART_Num_t Copy_EnumUSART_Num ,uint8_t *Copy_pu8Received_Data)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumUSART_Num Range */
	if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
	{
		/* clear the flag before working on it */
		//CLR_BIT(USART[Copy_EnumUSART_Num]->USART_SR,RXNE);

		/* wait until transmit buffer is ready */
		while((GET_BIT(USART[Copy_EnumUSART_Num]->USART_SR,RXNE)) != FLAG_RAISED);

		/* read data from USART_DR register */
		*Copy_pu8Received_Data =  USART[Copy_EnumUSART_Num]->USART_DR;


		/* clear flag  */
		CLR_BIT(USART[Copy_EnumUSART_Num]->USART_SR,RXNE);
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to Receive data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8Received_Data : this is a pointer of uint16 which carrying data received by usart.
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8ReceiveDataAsynch(USART_Num_t Copy_EnumUSART_Num ,uint8_t *Copy_pu8Received_Data)
{

	/* wait until transmit buffer is ready */
	if((GET_BIT(USART[Copy_EnumUSART_Num]->USART_SR,RXNE)) == FLAG_RAISED)
	{
		/* read data from USART_DR register */
		*Copy_pu8Received_Data =  USART[Copy_EnumUSART_Num]->USART_DR;

		/* clear flag  */
		CLR_BIT(USART[Copy_EnumUSART_Num]->USART_SR,RXNE);
		return 1;
	}
	return 0;

}

/**
 * @brief: this function is used to Receive data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8Received_Data : this is a pointer of uint16 which carrying data received by usart.
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8ReceiveData_IT(USART_Num_t Copy_EnumUSART_Num ,uint8_t *Copy_pu8Received_Data)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;

	/* check on the pointer of uint8 is equal NULL or Not equal NULL */
	if(Copy_pu8Received_Data != NULL )
	{
		/* check on Copy_EnumUSART_Num Range */
		if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
		{
			/* read data from USART_DR register */
			*Copy_pu8Received_Data = USART[Copy_EnumUSART_Num]->USART_DR;
		}else
		{
			/* UPDATE Error state value */
			Local_u8ErrorState = NOK;
		}
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to receive array of data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t USART_u8ReceiveBufferSynch(USART_Num_t Copy_EnumUSART_Num , uint8_t *Copy_pu8BufferArr,uint8_t Copy_u8SizeOfArr)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;
	/* this variable is used to count up size of array to have the next element */
	static uint8_t Local_u8Count = INIT_VALUE_BY_ZERO;

	/* check on the pointer of uint8 is equal NULL or Not equal NULL */
	if(Copy_pu8BufferArr != NULL )
	{
		/* check on Copy_EnumUSART_Num Range */
		if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
		{
			/* if UART is not BUSY */
			if(USART_u8BusyFlag == FLAG_IS_IDLE)
			{
				/* UART is now BUSY  */
				USART_u8BusyFlag = FLAG_IS_BUSY;

				for(Local_u8Count = ZERO_VALUE ; Local_u8Count <Copy_u8SizeOfArr ; Local_u8Count++)
				{
					/* Question why? */
					USART_u8ReceiveData(Copy_EnumUSART_Num, (&Copy_pu8BufferArr[Local_u8Count]));
				}

				/* UART Is now IDLE */
				USART_u8BusyFlag = FLAG_IS_IDLE;
			}else
			{
				/* UART was busy , assign the error state */
				Local_u8ErrorState = BUSY_STATE_ERR;
			}
		}else
		{
			/* UPDATE Error state value */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to receive array of data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t UART_u8ReceiveBufferSynch_IT(USART_Num_t Copy_EnumUSART_Num , uint8_t *Copy_pu8BufferArr,uint8_t Copy_u8SizeOfArr)
{
	/* this is a variable to arry error state value */
	uint8_t Local_u8ErrorState = OK;

	/* check on the pointer of uint8 is equal NULL or Not equal NULL */
	if(Copy_pu8BufferArr != NULL)
	{
		/* check on Copy_EnumUSART_Num Range */
		if(Copy_EnumUSART_Num >= USART1_peri  && Copy_EnumUSART_Num <= USART6_peri)
		{
			/* if UART is not BUSY */
			if(USART_u8BusyFlag == FLAG_IS_IDLE)
			{
				/* UART is now BUSY  */
				USART_u8BusyFlag = FLAG_IS_BUSY;

				USART_u8ReceiveData_IT(Copy_EnumUSART_Num, Copy_pu8BufferArr);

				/* UART Is now IDLE */
				USART_u8BusyFlag = FLAG_IS_IDLE;
			}else
			{
				/* UART was busy , assign the error state */
				Local_u8ErrorState = BUSY_STATE_ERR;
			}
		}else
		{
			/* UPDATE Error state value */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* UPDATE Error state value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


/**
 * @brief This function is used to Set USART ISR
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param[in] Copy_pfFuncPtr :  this is an array of pointer to function which carrying the address of ISR
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t USART_u8SetCallBack(USART_Num_t Copy_EnumUSART_Num , void (*Copy_pfFuncPtr)(void))
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_pfFuncPtr != NULL)
	{
		if(Copy_EnumUSART_Num >= USART1_peri && Copy_EnumUSART_Num >= USART6_peri)
		{
			USART_puNotificationFunc[Copy_EnumUSART_Num] = Copy_pfFuncPtr ;
		}else
		{
			/* UPdate Error State Value */
			Local_u8ErrorState= NOK;
		}
	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

void  USART1_IRQHandler()
{
	/* Clear TC flag */
	CLR_BIT((USART[USART1_peri]->USART_DR),TC);

	if(USART_puNotificationFunc != NULL)
	{
		USART_puNotificationFunc[USART1_peri]();
	}
}

void  USART2_IRQHandler()
{
	/* Clear TC flag */
	CLR_BIT((USART[USART2_peri]->USART_DR),TC);

	if(USART_puNotificationFunc != NULL)
	{
		USART_puNotificationFunc[USART2_peri]();
	}
}
void  USART3_IRQHandler()
{
	/* Clear TC flag */
	CLR_BIT((USART[USART3_peri]->USART_DR),TC);

	if(USART_puNotificationFunc != NULL)
	{
		USART_puNotificationFunc[USART3_peri]();
	}
}
void  UART4_IRQHandler()
{
	/* Clear TC flag */
	CLR_BIT((USART[UART4_peri]->USART_DR),TC);

	if(USART_puNotificationFunc != NULL)
	{
		USART_puNotificationFunc[UART4_peri]();
	}
}
void  UART5_IRQHandler()
{
	/* Clear TC flag */
	CLR_BIT((USART[UART5_peri]->USART_DR),TC);

	if(USART_puNotificationFunc != NULL)
	{
		USART_puNotificationFunc[UART5_peri]();
	}
}
void  USART6_IRQHandler()
{
	/* Clear TC flag */
	CLR_BIT((USART[USART6_peri]->USART_DR),TC);

	if(USART_puNotificationFunc != NULL)
	{
		USART_puNotificationFunc[USART6_peri]();
	}
}
