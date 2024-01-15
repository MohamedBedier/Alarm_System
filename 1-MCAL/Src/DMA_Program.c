/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : DMA_Program.c                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "RCC_Interface.h"
#include "DMA_CFG.h"
#include "DMA_Private.h"
#include "DMA_interface.h"

/************** cir mode  ****************************/

/* This is a global pointer to array from 2 elements [DMA1,DMA2] from DMA_Reg_t type */
/* according to least privilege make it static to save it private for this file only */
static DMA_RegDef_t* DMA[DMA_PERIPHERAL_NUM] = {DMA1,DMA2};

static uint8_t DMA_u8BusyFlag = FLAG_IS_IDLE;

/* THIS is an array of pointers to functions to hold ISR  Callbacks */
static void(*DMA_puNotificationFunc[DMA_PERIPHERAL_NUM][DMA_STREAM_NUM])(void) = {NULL};

/* this is a prototype of static function */
/**
 * @brief: This function is used to Set some of DMA Transfer parameter
 * @param[in] Copy_psDMA : this is a pointer to struct which carrying Configuration the configuration information for the specified DMA Stream.
 * @param[in] Copy_u32SrcAddress : This is a variable which carrying source address
 * @param[in] Copy_u32DstAddress : This is a variable which carrying destination address
 * @param[in] Copy_u32DataLength : This is a variable which carrying Data length to be transferred from source to destination
 * @return Local_u8ErrorState this variable to carry Error State value
 */
static uint8_t DMA_u8SetConfig(DMA_Config_t *Copy_psDMA, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint32_t Copy_u32DataLength);

/**
 * @brief: This function is used to Set some of DMA Transfer parameter
 * @param[in] Copy_psDMA : this is a pointer to struct which carrying Configuration the configuration information for the specified DMA Stream.
 * @param[in] Copy_u32SrcAddress : This is a variable which carrying source address
 * @param[in] Copy_u32DstAddress : This is a variable which carrying destination address
 * @param[in] Copy_u32DataLength : This is a variable which carrying Data length to be transferred from source to destination
 * @return Local_u8ErrorState this variable to carry Error State value
 */
static uint8_t DMA_u8SetConfig(DMA_Config_t *Copy_psDMA, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint32_t Copy_u32DataLength)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_psDMA != NULL)
	{
		if(((Copy_psDMA->Stream_NUM)>= DMA_STR0) && ((Copy_psDMA->Stream_NUM)<= DMA_STR7) && (Copy_psDMA->DMA_NUM >= DMA1_SEL) && (Copy_psDMA->DMA_NUM <= DMA2_SEL))
		{
			/* Clear DBM bit that means no buffer switching at the end of transfer */
			CLR_BIT(DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR,DBM);

			/* Configure DMA Stream data length */
			DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxNDTR = Copy_u32DataLength;

			/* if the direction is Memory to Peripheral */
			if(Copy_psDMA->DIRMode == MEMORY_TO_PERIPHERAL)
			{
				/* Configure DMA Stream destination address [peripheral is the destination ] */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxPAR = Copy_u32DstAddress;

				/* Configure DMA Stream source address [Memory is the source] */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxM0AR = Copy_u32SrcAddress;

			}else if ((Copy_psDMA->DIRMode == PERIPHERAL_TO_MEMORY) || (Copy_psDMA->DIRMode == MEMORY_TO_MEMORY))
			{
				/* Configure DMA Stream destination address [peripheral is the destination ] */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxPAR = Copy_u32SrcAddress;

				/* Configure DMA Stream source address [Memory is the source] */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxM0AR = Copy_u32DstAddress;
			}else
			{
				/* UPdate Error State Value */
				Local_u8ErrorState= NOK;
			}
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

/**
 * @brief This function is used to Set DMA channel
 * @param[IN] Copy_psDMA this parameter is a pointer to struct which Carrying DMA configurations
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8SetChannel(DMA_Config_t* Copy_psDMA)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_psDMA != NULL)
	{
		/* protect our function by checking on DMA_NUM, Stream_NUM Channel_NUM ranges */
		if((Copy_psDMA->Channel_NUM >= DMA_CH0) && (Copy_psDMA->Channel_NUM <= DMA_CH7))
		{
			/* Clear channel select bits before you work on it */
			DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR &=(~(CHSEL_BITS_MASK << CHSEL_BIT0));
			/* set channel which determine it in config struct */
			DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR |= ((Copy_psDMA->Channel_NUM) << CHSEL_BIT0);

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

/**
 * @brief This function is used to Set DMA channel
 * @param[IN] Copy_psDMA this parameter is a pointer to struct which Carrying DMA configurations
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8SetStreamPrioirty(DMA_Config_t* Copy_psDMA)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_psDMA != NULL)
	{
		/* protect our function by checking on DMA_NUM, Stream_NUM Priority ranges */
		if((Copy_psDMA->Priority >= PL_LOW) && (Copy_psDMA->Priority <= PL_VERY_HIGH))
		{
			/* Clear priority bits before you work on it */
			DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR &=(~(PL_BITS_MASK << PL_BIT0));
			/* set Priority which determine it in config struct */
			DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR |= ((Copy_psDMA->Priority) << PL_BIT0);

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

/**
 * @brief This function is used to Enable DMA interrupt
 * @param[IN] Copy_psDMA this parameter is a pointer to struct which Carrying DMA configurations
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8EnabledInt(DMA_NUM_t Copy_EnumDMA_Num , Stream_Selected_t Copy_EnumStream_Num,DMA_Int_Name_t  Copy_EnumInterrupt_Name)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on DMA Interrupt Name */
	if(Copy_EnumInterrupt_Name == FIFO_Error_IT)
	{
		/* Clear FIFO_Error_IT bit before you work on it */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxFCR &=(~(SET_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of FIFO_Error_IT */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxFCR |= (SET_INTERRUPT_MASK << Copy_EnumInterrupt_Name);


	}else if((Copy_EnumInterrupt_Name == DirectMode_Error_IT) || (Copy_EnumInterrupt_Name == HalfTransfer_IT)
			|| (Copy_EnumInterrupt_Name == TransferComplete_IT) || (Copy_EnumInterrupt_Name == Transfer_Error_IT))
	{

		/* Clear FIFO_Error_IT bit before you work on it */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxCR &=(~(SET_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of Copy_psDMA->DMA_Int_Name */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxCR |= (SET_INTERRUPT_MASK << Copy_EnumInterrupt_Name);

	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NOK;
	}

	return Local_u8ErrorState;
}


/**
 * @brief This function is used to disable DMA interrupt
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param Copy_EnumInterrupt_Name : this is an enum which using to interrupt name
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8DisabledInt(DMA_NUM_t Copy_EnumDMA_Num , Stream_Selected_t Copy_EnumStream_Num,DMA_Int_Name_t  Copy_EnumInterrupt_Name)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on DMA Interrupt Name */
	if(Copy_EnumInterrupt_Name == FIFO_Error_IT)
	{
		/* Clear FIFO_Error_IT bit before you work on it */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxFCR &=(~(SET_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of FIFO_Error_IT */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxFCR |= (CLR_INTERRUPT_MASK << Copy_EnumInterrupt_Name);


	}else if((Copy_EnumInterrupt_Name == DirectMode_Error_IT) || (Copy_EnumInterrupt_Name == HalfTransfer_IT)
			|| (Copy_EnumInterrupt_Name == TransferComplete_IT) || (Copy_EnumInterrupt_Name == Transfer_Error_IT))
	{

		/* Clear FIFO_Error_IT bit before you work on it */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxCR &=(~(SET_INTERRUPT_MASK << Copy_EnumInterrupt_Name));
		/* set bit of Copy_psDMA->DMA_Int_Name */
		DMA[Copy_EnumDMA_Num]->DMA_Stream[Copy_EnumStream_Num].DMA_SxCR |= (CLR_INTERRUPT_MASK << Copy_EnumInterrupt_Name);

	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NOK;
	}

	return Local_u8ErrorState;
}
/**
 * @brief This function to initiate DMA Configurations
 * @param[IN] Copy_psDMA this parameter is a pointer to struct which Carrying DMA configurations
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8Init(DMA_Config_t* Copy_psDMA)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_psDMA != NULL)
	{
		/* protect our function by checking on DMA_NUM, Stream_NUM, Copy_EnumChannel_NUM ranges */
		if((Copy_psDMA->DMA_NUM >= DMA1_SEL) && (Copy_psDMA->DMA_NUM <= DMA2_SEL) &&
				(Copy_psDMA->Stream_NUM >= DMA_STR0) && (Copy_psDMA->Stream_NUM  <= DMA_STR7))
		{

			/* Check on Direct mode range*/
			if(((Copy_psDMA-> DIRMode) >= PERIPHERAL_TO_MEMORY)  && ((Copy_psDMA-> DIRMode) <= MEMORY_TO_MEMORY))
			{
				/* Clear Direct mode bits before you work on it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR &=(~(DIR_MODE_BITS_MASK << DIR_BIT0));
				/* Set Direction of DMA,Options are : peripheral-to-memory , memory-to-peripheral , memory-to-memory */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR |= ((Copy_psDMA->DIRMode) << DIR_BIT0);
			}else
			{
				/* UPdate Error State Value */
				Local_u8ErrorState =NOK;
			}

			/* Set if you want to work as FIFO or Direct mode */
			if((Copy_psDMA-> FIFO_Status) == FIFOMODE_DISABLED)
			{
				/* Clear FIFO bit before you work on it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxFCR &=(~(FIFO_BIT_MASK << DMDIS));
				/* Direct mode is enabled */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxFCR |= ((Copy_psDMA->FIFO_Status) << DMDIS);

			}else if((Copy_psDMA-> FIFO_Status) == FIFOMODE_ENABLED)
			{
				/* Clear FIFO bit before you work on it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxFCR &=(~(FIFO_BIT_MASK << DMDIS));
				/* FIFO mode is enabled */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxFCR |= ((Copy_psDMA->FIFO_Status) << DMDIS);

				/* Clear FIFO threshold bits before you work on it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxFCR &=(~(FIFO_THRESHOLD_BITS_MASK << FTH_BIT0));
				/* determine threshold OF FIFO */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxFCR |= ((Copy_psDMA->FIFOThreshold) << FTH_BIT0);

			}else
			{
				/* UPdate Error State Value */
				Local_u8ErrorState =NOK;
			}

			/* Check on Circular mode range*/
			if(((Copy_psDMA-> CIRMode_Status) == CIRMODE_DISABLED)  || ((Copy_psDMA-> CIRMode_Status) == CIRMODE_ENABLED))
			{
				/* Clear Direct mode bits before you work on it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR &=(~(CIRC_MODE_BIT_MASK << CIRC));
				/* enable Circular mode or disable it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR |= ((Copy_psDMA->CIRMode_Status) << CIRC);
			}else
			{
				/* UPdate Error State Value */
				Local_u8ErrorState =NOK;
			}

			/* Set Peripheral increment of DMA,Options are : PINC_DISABLED , PINC_ENABLED */
			switch(Copy_psDMA->PINC_Status)
			{
			case PINC_DISABLED:CLR_BIT(DMA_NUM_SxCR,PINC);break;/* PINC_DISABLED */
			case PINC_ENABLED:SET_BIT(DMA_NUM_SxCR,PINC);break;/* PINC_ENABLED*/
			default:Local_u8ErrorState =NOK;break;/* UPdate Error State Value */
			}

			/* Set Memery increment of DMA,Options are : MINC_DISABLED , MINC_ENABLED */
			switch(Copy_psDMA->MINC_Status)
			{
			case MINC_DISABLED: CLR_BIT(DMA_NUM_SxCR,MINC);break; /* MINC_DISABLED */
			case MINC_ENABLED: SET_BIT(DMA_NUM_SxCR,MINC);break;/* MINC_ENABLED */
			default:Local_u8ErrorState =NOK;break;/* UPdate Error State Value */
			}

			/* check on PeriperalDataAlignment range */
			if(((Copy_psDMA-> DMA_PeriperalDataAlignment) >= PDATAALIAGN_BYTE)  && ((Copy_psDMA-> DMA_PeriperalDataAlignment) <= PDATAALIAGN_WORD))
			{
				/* Clear DMA_PeriperalDataAlignment bits before you work on it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR &=(~(PDATAALIAGN_BITS_MASK << PSIZE_BIT0));
				/* Set DMA Peripheral Data Alignment,Options are : PDATAALIAGN_BYTE, PDATAALIAGN_HALFWORD , PDATAALIAGN_WORD */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR |= ((Copy_psDMA->DMA_PeriperalDataAlignment) << PSIZE_BIT0);
			}else
			{
				/* UPdate Error State Value */
				Local_u8ErrorState =NOK;
			}

			/* check on PeriperalDataAlignment range */
			if(((Copy_psDMA-> DMA_MemoeryDataAlignment) >= MDATAALIAGN_BYTE)  && ((Copy_psDMA-> DMA_MemoeryDataAlignment) <= MDATAALIAGN_WORD))
			{
				/* Clear DMA_PeriperalDataAlignment bits before you work on it */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR &=(~(MDATAALIAGN_BITS_MASK << MSIZE_BIT0));
				/* Set DMA Memory Data Alignment,Options are : MDATAALIAGN_BYTE, MDATAALIAGN_HALFWORD , MDATAALIAGN_WORD */
				DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR |= ((Copy_psDMA->DMA_MemoeryDataAlignment) << MSIZE_BIT0);
			}else
			{
				/* UPdate Error State Value */
				Local_u8ErrorState =NOK;
			}

			/* check on interrupts status */
			if(Copy_psDMA->DMA_INT_Initial_Sts == DMA_INT_ENABLED )
			{
				/* enable the interrupt you want  */
				DMA_u8EnabledInt(Copy_psDMA->DMA_NUM,Copy_psDMA->Stream_NUM,Copy_psDMA->DMA_Int_Name);
			}

			/* Set DMA channal number ,Options are : DMA_CH0,DMA_CH1,DMA_CH2,DMA_CH3,DMA_CH4,DMA_CH5,DMA_CH6,DMA_CH7 */
			DMA_u8SetChannel(Copy_psDMA);

			/* Set DMA stream priority ,Options are : LOW , MEDIUM , HIGH , VERY_HIGH */
			DMA_u8SetStreamPrioirty(Copy_psDMA);

		}else
		{
			/* UPdate Error State Value */
			Local_u8ErrorState = NOK;
		}

	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief This function to read DMA flag value
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param[in] Copy_u8FlagName : this is a variable which carrying flag bit number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8ReadFlag(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum ,uint8_t Copy_u8FlagName)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	uint8_t Local_u8RegNum = INIT_VALUE_BY_ZERO;

	/* protect our function by checking on DMA_NUM, Stream_NUM, Copy_EnumChannel_NUM ranges */
	if((Copy_EnumDMANum >= DMA1_SEL) && (Copy_EnumDMANum <= DMA2_SEL) &&
			(Copy_EnumStreamNum >= DMA_STR0) && (Copy_EnumStreamNum  <= DMA_STR7))
	{

		/* Equation to determine isr low or high register */
		Local_u8RegNum = Copy_EnumStreamNum / DIV_FACT_4 ;

		while(GET_BIT((DMA[Copy_EnumDMANum]->DMA_ISR[Local_u8RegNum]),Copy_u8FlagName) != FLAG_RAISED);
	}
	else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief This function to clear DMA flag value
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param[in] Copy_u8FlagName : this is a variable which carrying flag bit number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8ClearFlag(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum,uint8_t Copy_u8FlagName)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	uint8_t Local_u8RegNum = INIT_VALUE_BY_ZERO;

	/* protect our function by checking on DMA_NUM, Stream_NUM, Copy_EnumChannel_NUM ranges */
	if((Copy_EnumDMANum >= DMA1_SEL) && (Copy_EnumDMANum <= DMA2_SEL) &&
			(Copy_EnumStreamNum >= DMA_STR0) && (Copy_EnumStreamNum  <= DMA_STR7))
	{

		/* Equation to determine isr low or high register */
		Local_u8RegNum = Copy_EnumStreamNum / DIV_FACT_4 ;

		SET_BIT((DMA[Copy_EnumDMANum]->DMA_IFCR[Local_u8RegNum]),Copy_u8FlagName);
	}
	else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NOK;
	}
	return Local_u8ErrorState;
}
/**
 * @brief: this function is used to enable dma (EN)
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8DMAEnable(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;


	/* protect our function by checking on DMA_NUM, Stream_NUM, Copy_EnumChannel_NUM ranges */
	if((Copy_EnumDMANum >= DMA1_SEL) && (Copy_EnumDMANum <= DMA2_SEL) &&
			(Copy_EnumStreamNum >= DMA_STR0) && (Copy_EnumStreamNum  <= DMA_STR7))
	{
		/* enable DMA */
		SET_BIT((DMA[Copy_EnumDMANum]->DMA_Stream[Copy_EnumStreamNum].DMA_SxCR),EN);

	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState =NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief: this function is used to disable dma (EN)
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8DMADisable(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* protect our function by checking on DMA_NUM, Stream_NUM, Copy_EnumChannel_NUM ranges */
	if((Copy_EnumDMANum >= DMA1_SEL) && (Copy_EnumDMANum <= DMA2_SEL) &&
			(Copy_EnumStreamNum >= DMA_STR0) && (Copy_EnumStreamNum  <= DMA_STR7))
	{
		/* disable DMA */
		CLR_BIT((DMA[Copy_EnumDMANum]->DMA_Stream[Copy_EnumStreamNum].DMA_SxCR),EN);

	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState =NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief This function is used to Start DMA
 * @param[in] Copy_psDMA : this is a pointer to struct which carrying Configuration the configuration information for the specified DMA Stream.
 * @param[in] Copy_u32SrcAddress : This is a variable which carrying source address
 * @param[in] Copy_u32DstAddress : This is a variable which carrying destination address
 * @param[in] Copy_u32DataLength : This is a variable which carrying Data length to be transferred from source to destination
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8StartTransfer_Polling(DMA_Config_t *Copy_psDMA, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint32_t Copy_u32DataLength)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_psDMA != NULL)
	{
		/* if DMA global flag is not BUSY */
		if(DMA_u8BusyFlag == FLAG_IS_IDLE)
		{
			/* DMA is now BUSY  */
			DMA_u8BusyFlag = FLAG_IS_BUSY;

			DMA_u8SetConfig(Copy_psDMA, Copy_u32SrcAddress, Copy_u32DstAddress, Copy_u32DataLength);

			/* DMA Enabled */
			DMA_u8DMAEnable(Copy_psDMA->DMA_NUM, Copy_psDMA->Stream_NUM);
			/* read flag */
			DMA_u8ReadFlag(Copy_psDMA->DMA_NUM, Copy_psDMA->Stream_NUM, POLLING_FLAG_ON);
			/* Clear flag */
			DMA_u8ClearFlag(Copy_psDMA->DMA_NUM, Copy_psDMA->Stream_NUM, POLLING_FLAG_ON);

			/* DMA is now IDLE  */
			DMA_u8BusyFlag = FLAG_IS_IDLE;
		}else
		{
			/* UPdate Error State Value */
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


/**
 * @brief This function is used to Start DMA USING INTERRUPT
 * @param[in] Copy_psDMA : this is a pointer to struct which carrying Configuration the configuration information for the specified DMA Stream.
 * @param[in] Copy_u32SrcAddress : This is a variable which carrying source address
 * @param[in] Copy_u32DstAddress : This is a variable which carrying destination address
 * @param[in] Copy_u32DataLength : This is a variable which carrying Data length to be transferred from source to destination
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8StartTransfer_IT(DMA_Config_t *Copy_psDMA, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint32_t Copy_u32DataLength)
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_psDMA != NULL)
	{
		/* if DMA global flag is not BUSY */
		if(DMA_u8BusyFlag == FLAG_IS_IDLE)
		{
			/* DMA is now BUSY  */
			DMA_u8BusyFlag = FLAG_IS_BUSY;

			DMA_u8SetConfig(Copy_psDMA, Copy_u32SrcAddress, Copy_u32DstAddress, Copy_u32DataLength);

			/* DMA is now IDLE  */
			DMA_u8BusyFlag = FLAG_IS_IDLE;
		}else
		{
			/* UPdate Error State Value */
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief This function is used to Set DMA ISR
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param[in] Copy_pfFuncPtr :  this is an array of pointer to function which carrying the address of ISR
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8SetCallBack(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum,void (*Copy_pfFuncPtr)(void))
{
	/* define a variable to carry error status value */
	uint8_t Local_u8ErrorState=OK;

	/* check on the Copy_psDMA pointer is equal null or not to protect our function */
	if(Copy_pfFuncPtr != NULL)
	{
		/* protect our function by checking on DMA_NUM, Stream_NUM, Copy_EnumChannel_NUM ranges */
		if((Copy_EnumDMANum >= DMA1_SEL) && (Copy_EnumDMANum <= DMA2_SEL) &&
				(Copy_EnumStreamNum >= DMA_STR0) && (Copy_EnumStreamNum  <= DMA_STR7))
		{
			/* convert to global */
			DMA_puNotificationFunc[Copy_EnumDMANum][Copy_EnumStreamNum] = Copy_pfFuncPtr ;
		}else
		{
			/* UPdate Error State Value */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* UPdate Error State Value */
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


void  DMA1_Stream0_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR0, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		/* */
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR0]();
	}
}

void  DMA1_Stream1_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR1, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR1]();
	}
}
void  DMA1_Stream2_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR2, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR2]();
	}
}
void  DMA1_Stream3_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR3, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR3]();
	}
}
void  DMA1_Stream4_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR4, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR4]();
	}
}
void  DMA1_Stream5_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR5, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR5]();
	}
}
void  DMA1_Stream6_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR6, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR6]();
	}
}
void  DMA1_Stream7_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA1_SEL, DMA_STR7, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA1_SEL][DMA_STR7]();
	}
}
void  DMA2_Stream0_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR0, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{

		DMA_puNotificationFunc[DMA2_SEL][DMA_STR0]();
	}
}
void  DMA2_Stream1_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR1, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA2_SEL][DMA_STR1]();
	}
}
void  DMA2_Stream2_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR2, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA2_SEL][DMA_STR2]();
	}
}
void  DMA2_Stream3_IRQHandler()
{	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR3, POLLING_FLAG_ON);


	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA2_SEL][DMA_STR3]();
	}
}
void  DMA2_Stream4_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR4, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA2_SEL][DMA_STR4]();
	}
}void  DMA2_Stream5_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR5, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA2_SEL][DMA_STR5]();
	}
}
void  DMA2_Stream6_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR6, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA2_SEL][DMA_STR6]();
	}
}
void  DMA2_Stream7_IRQHandler()
{
	/* CLEAR flag */
	DMA_u8ClearFlag(DMA2_SEL, DMA_STR7, POLLING_FLAG_ON);

	if(DMA_puNotificationFunc != NULL)
	{
		DMA_puNotificationFunc[DMA2_SEL][DMA_STR7]();
	}
}
