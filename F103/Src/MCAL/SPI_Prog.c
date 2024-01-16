/***********************************************************
* @file SPI_Prog
* @Author Abdullah AlsharQawy
* @Brief The main file for SPI peripheral
***********************************************************/

#include <stdint.h>
#include <Stm32F103xx.h>
#include <ErrType.h>

#include <SPI_Interface.h>
#include <SPI_prv.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
static uint16_t* ReceiveInterrupt_Ptrs_Arr[2];
static uint32_t  ReceiveInterrupt_Size_Arr[2];
static uint32_t  ReceiveInterrupt_Index_Arr[2];
static SPI_Circular_t  ReceiveInterrupt_Circular_Arr[2];

static uint16_t* TransmitInterrupt_Ptrs_Arr[2];
static uint32_t  TransmitInterrupt_Size_Arr[2];
static uint32_t  TransmitInterrupt_Index_Arr[2];
static SPI_Circular_t  TransmitInterrupt_Circular_Arr[2];



/***********************************************************
* @fn SPI_voidInit
* @Brief The Initialization function of SPI peripherals
* @Param[in] SPIConfig : The initialization parameters struct for the SPI peripheral
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_voidInit(const SPIConfig_t* SPIConfig)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the SPIConfig pointer*/
	if(SPIConfig==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on the SPIConfig parameters values*/
	else if(SPIConfig->SPI>SPI_2|| SPIConfig->Prescaler>FCLK_256 || SPIConfig->DataFrame>SPI_16_BITS ||
			SPIConfig->First_LSB>LSB_FIRST || SPIConfig->Master>SPI_MASTER || SPIConfig->SW_SlvMng>SW_SLV_MNG_ENABLE)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(SPIConfig->SPI);

		/*Selecting master or slave configuration*/
		SPI->SPI_CR1&=~(0b1<<MASTER_BIT_ACCESS);
		SPI->SPI_CR1|=(SPIConfig->Master)<<MASTER_BIT_ACCESS;

		/*Selecting the size of data*/
		SPI->SPI_CR1&=~(0b1<<DATAFRAME_BIT_ACCESS);
		SPI->SPI_CR1|=(SPIConfig->DataFrame)<<DATAFRAME_BIT_ACCESS;

		/*Choosing to send the least or most significant bit first*/
		SPI->SPI_CR1&=~(0b1<<FIRSTLSB_BIT_ACCESS);
		SPI->SPI_CR1|=(SPIConfig->First_LSB)<<FIRSTLSB_BIT_ACCESS;

		/*Configure the prescaler of the peripheral*/
		SPI->SPI_CR1&=~(0b111<<PRESCALER_BIT_ACCESS);
		SPI->SPI_CR1|=(SPIConfig->Prescaler)<<PRESCALER_BIT_ACCESS;

		/*Enabling or Disabling the SW control of slave selection*/
		SPI->SPI_CR1&=~(0b1<<SWSLVMNG_BIT_ACCESS);
		SPI->SPI_CR1|=(SPIConfig->SW_SlvMng)<<SWSLVMNG_BIT_ACCESS;

		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_SelcetPeripheral
* @Brief Selection of SPI peripheral
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval SPI_RegDef_t : the address of the SPI peripheral
***********************************************************/
static SPI_RegDef_t* SPI_SelcetPeripheral(SPI_t spi)
{
	SPI_RegDef_t* SPI=NullPtr;
	/*Select the desired SPI*/
	switch(spi)
	{
		case SPI_1:
			SPI=SPI1;
			break;
		case SPI_2:
			SPI=SPI2;
			break;
	}
	return SPI;
}

/***********************************************************
* @fn SPI_Enable
* @Brief Enabling SPI peripheral
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_Enable(SPI_t spi)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Setting the enable bit*/
		SPI->SPI_CR1|=0b1<<SPI_ENABLE_BIT_ACCESS;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_Disable
* @Brief Disabling SPI peripheral
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_Disable(SPI_t spi)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Clearing the enable bit*/
		SPI->SPI_CR1&=~(0b1<<SPI_ENABLE_BIT_ACCESS);
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_SW_NSS_Pin
* @Brief controlling NSS pin -> SSM should be enabled from SPI_voidInit function
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @Param[in] nssPin : The status of the NSS pin, Option at @SPI_SW_NSS_Pin_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_SW_NSS_Pin(SPI_t spi, SPI_SW_NSS_Pin_t nssPin)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi and nssPin values*/
	if(spi>SPI_2 || nssPin>SW_NSS_HIGH)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Writing the NSS Pin*/
		SPI->SPI_CR1&=~(0b1<<SPI_NSS_BIT_ACCESS);
		SPI->SPI_CR1|=nssPin<<SPI_NSS_BIT_ACCESS;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_DMA_TransmitEnable
* @Brief Enabling SPI DMA transferring data to be transmitted by SPI
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_DMA_TransmitEnable(SPI_t spi)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Setting DMA transmit enable bit*/
		SPI->SPI_CR2|=0b1<<SPI_TRAN_DMA_EN_BIT_ACCESS;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_DMA_ReceiveEnable
* @Brief Enabling SPI DMA transferring data received by SPI
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_DMA_ReceiveEnable(SPI_t spi)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Setting DMA receive enable bit*/
		SPI->SPI_CR2|=0b1<<SPI_RECE_DMA_EN_BIT_ACCESS;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_SendSync
* @Brief Sending data by SPI synchronize
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @Param[in] data : the data to be sent
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_SendSync(SPI_t spi, uint16_t data)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Waiting the transmit buffer to be empty meaning it has finished sending previous data*/
		while(!(((SPI->SPI_SR)>>SPI_TRAN_BUFFER_EMPTY_BIT_ACCESS)&1));
		/*Writing the data in the SPI data register*/
		SPI->SPI_DR=data;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_ReceiveSync
* @Brief Receive data by SPI synchronize
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @Param[out] data : the data received
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_ReceiveSync(SPI_t spi, uint16_t* data)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	/*Checking on the data pointer*/
	else if(data==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Waiting the receive buffer to be full meaning it has received data*/
		while(!(((SPI->SPI_SR)>>SPI_RECE_BUFFER_FULL_BIT_ACCESS)&1));
		/*Reading data from SPI data register*/
		*data=SPI->SPI_DR;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_SendPeriodic
* @Brief Sending data by SPI periodic
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @Param[in] data : the data to be sent
* @retval uint8_t status of the sending -> finish sending or not yet
***********************************************************/
uint8_t SPI_SendPeriodic(SPI_t spi, uint16_t data)
{
	/*Select the desired SPI*/
	SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
	/*Checking the transmit buffer to be empty*/
	if((((SPI->SPI_SR)>>SPI_TRAN_BUFFER_EMPTY_BIT_ACCESS)&1)==0)
	{
		return 0;
	}
	else
	{
		/*Writing the data in the SPI data register*/
		SPI->SPI_DR=data;
		return 1;
	}
}

/***********************************************************
* @fn SPI_ReceivePeriodic
* @Brief Receiving data by SPI periodic
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @Param[out] data : the data to be received
* @retval uint8_t status of the receiving -> finish receiving or not yet
***********************************************************/
uint8_t SPI_ReceivePeriodic(SPI_t spi, uint16_t* data)
{
	/*Select the desired SPI*/
	SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
	/*Checking the receive buffer to be full meaning it has received data and Checking on the data pointer*/
	if((((SPI->SPI_DR)>>SPI_RECE_BUFFER_FULL_BIT_ACCESS)&1)==0 || data==NullPtr)
	{
		return 0;
	}
	else
	{
		/*Reading data from SPI data register*/
		*data=SPI->SPI_DR;
		return 1;
	}
}

/***********************************************************
* @fn SPI_TransmitInterruptEnable
* @Brief Enabling SPI Transmission by interrupt
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @Param[in] DataPtr : The pointer to transmit data from
* @Param[in] DataSize : The size of the transmission buffer
* * @Param[in] Cir : Enabling or disabling the continuous circular transmitting by re-assign the index to zero, Optionas at @SPI_Circular_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_TransmitInterruptEnable(SPI_t spi, uint16_t* DataPtr, uint32_t DataSize, SPI_Circular_t Cir)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	/*Checking on the DataPtr pointer*/
	else if(DataPtr==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on the DataSize value as we send data then we check on it*/
	else if(DataSize==0)
	{
		ErrorState=NOK;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Assigning the DataPtr pointer to the array of pointers of transmitting data*/
		TransmitInterrupt_Ptrs_Arr[spi]=DataPtr;
		/*Assigning the DataSize to the array of sizes of transmitting data*/
		TransmitInterrupt_Size_Arr[spi]=DataSize;
		/*Re-intializing the index in the array of indexes of transmitting data*/
		TransmitInterrupt_Index_Arr[spi]=0;
		/*Assigning the circular transmitting enable parameter*/
		TransmitInterrupt_Circular_Arr[spi]=Cir;
		/*Setting transmit interrupt enable bit*/
		SPI->SPI_CR2|=0b1<<SPI_TRAN_IT_EN_BIT_ACCESS;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_TransmitInterruptDisable
* @Brief Disabling SPI Transmission by interrupt
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_TransmitInterruptDisable(SPI_t spi)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Assigning the pointer in the array of pointers of transmitting data to NULL*/
		TransmitInterrupt_Ptrs_Arr[spi]=NullPtr;
		/*Clearing transmit interrupt enable bit*/
		SPI->SPI_CR2&=~(0b1<<SPI_TRAN_IT_EN_BIT_ACCESS);
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_ReceiveInterruptEnable
* @Brief Enabling SPI Receive by interrupt
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @Param[in] DataPtr : The pointer to receive data to
* @Param[in] DataSize : The size of the reception buffer
* @Param[in] Cir : Enabling or disabling the continuous circular receiving by re-assign the index to zero, Optionas at @SPI_Circular_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_ReceiveInterruptEnable(SPI_t spi, uint16_t* DataPtr, uint32_t DataSize, SPI_Circular_t Cir)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	/*Checking on the DataPtr pointer*/
	else if(DataPtr==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on the DataSize value as we send data then we check on it*/
	else if(DataSize==0)
	{
		ErrorState=NOK;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Assigning the DataPtr pointer to the array of pointers of receiving data*/
		ReceiveInterrupt_Ptrs_Arr[spi]=DataPtr;
		/*Assigning the DataSize to the array of sizes of receiving data*/
		ReceiveInterrupt_Size_Arr[spi]=DataSize;
		/*Re-intializing the index in the array of indexes of receiving data*/
		ReceiveInterrupt_Index_Arr[spi]=0;
		/*Assigning the circular receiving enable parameter*/
		ReceiveInterrupt_Circular_Arr[spi]=Cir;
		/*Setting receive interrupt enable bit*/
		SPI->SPI_CR2|=0b1<<SPI_RECE_IT_EN_BIT_ACCESS;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_ReceiveInterruptDisable
* @Brief Disabling SPI Receive by interrupt
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SPI_ReceiveInterruptDisable(SPI_t spi)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on spi value*/
	if(spi>SPI_2)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired SPI peripheral*/
		SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);
		/*Assigning the pointer in the array of pointers of receiving data to NULL*/
		ReceiveInterrupt_Ptrs_Arr[spi]=NullPtr;
		/*Clearing receive interrupt enable bit*/
		SPI->SPI_CR2&=~(0b1<<SPI_RECE_IT_EN_BIT_ACCESS);
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SPI_TransmitNoBlock
* @Brief Writing data to SPI directly from the transmitting buffer TransmitInterrupt_Ptrs_Arr
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval void
***********************************************************/
static void SPI_TransmitNoBlock(SPI_t spi)
{
	/*Checking on the transmit buffer pointer*/
	if(TransmitInterrupt_Ptrs_Arr[spi]==NullPtr)
	{
		return;
	}

	/*Select the desired SPI*/
	SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);

	/*Checking on the index of transmitted data of next transmission if it reached maximum*/
	if(TransmitInterrupt_Index_Arr[spi]>=TransmitInterrupt_Size_Arr[spi])
	{
		/*Re-assigin the index of transmitted data to zero*/
		TransmitInterrupt_Index_Arr[spi]=0;
		/*Checking on the continuous transmitting parameter*/
		if(TransmitInterrupt_Circular_Arr[spi]==CIRCULAR_DISABLE)
		{
			/*Stop transmitting any further data*/
			SPI_TransmitInterruptDisable(spi);
		}
		else
		{
			/*Writing data to SPI data register from the pointer of transmission data*/
			SPI->SPI_DR=TransmitInterrupt_Ptrs_Arr[spi][TransmitInterrupt_Index_Arr[spi]];
			/*Incrementing the index of transmitted data*/
			TransmitInterrupt_Index_Arr[spi]++;
		}
	}
	else
	{
		/*Writing data to SPI data register from the pointer of transmission data*/
		SPI->SPI_DR=TransmitInterrupt_Ptrs_Arr[spi][TransmitInterrupt_Index_Arr[spi]];
		/*Incrementing the index of transmitted data*/
		TransmitInterrupt_Index_Arr[spi]++;
	}
}

/***********************************************************
* @fn SPI_ReceiveNOoBlock
* @Brief reading data from SPI directly to the receiving buffer ReceiveInterrupt_Ptrs_Arr
* @Param[in] spi : The spi peripheral, Option at @SPI_t enum
* @retval void
***********************************************************/
static void SPI_ReceiveNoBlock(SPI_t spi)
{
	/*Checking on the receive buffer pointer*/
	if(ReceiveInterrupt_Ptrs_Arr[spi]==NullPtr)
	{
		return;
	}

	/*Select the desired SPI*/
	SPI_RegDef_t* SPI=SPI_SelcetPeripheral(spi);

	/*Checking on the index of received data of next reception if it reached maximum*/
	if(ReceiveInterrupt_Index_Arr[spi]>=ReceiveInterrupt_Size_Arr[spi])
	{
		/*Re-assigin the index of received data to zero*/
		ReceiveInterrupt_Index_Arr[spi]=0;
		/*Checking on the continuous receiving parameter*/
		if(ReceiveInterrupt_Circular_Arr[spi]==CIRCULAR_DISABLE)
		{
			/*Stop receiving any further data*/
			SPI_ReceiveInterruptDisable(spi);
		}
		else
		{
			/*Reading data from SPI data register to the pointer of reception data*/
			ReceiveInterrupt_Ptrs_Arr[spi][ReceiveInterrupt_Index_Arr[spi]]=(uint16_t)SPI->SPI_DR;
			/*Incrementing the index of received data*/
			ReceiveInterrupt_Index_Arr[spi]++;
		}
	}
	else
	{
		/*Reading data from SPI data register to the pointer of reception data*/
		ReceiveInterrupt_Ptrs_Arr[spi][ReceiveInterrupt_Index_Arr[spi]]=(uint16_t)SPI->SPI_DR;
		/*Incrementing the index of received data*/
		ReceiveInterrupt_Index_Arr[spi]++;
	}
}




/**********************************		IRQs	 ********************************/
void SPI1_IRQHandler(void)
{
	uint32_t SR_Reg=SPI1->SPI_SR;
	uint32_t CR2_Reg=SPI1->SPI_CR2;
	/*Checking the transmit buffer to be empty and Checking on the transmit interrupt enable bit*/
	if((((SR_Reg)>>SPI_TRAN_BUFFER_EMPTY_BIT_ACCESS)&1) &&
	   (((CR2_Reg)>>SPI_TRAN_IT_EN_BIT_ACCESS)&1))
	{
		 SPI_TransmitNoBlock(SPI_1);
	}
	/*Checking the receive buffer to be full and Checking on the receive interrupt enable bit*/
	if((((SR_Reg)>>SPI_RECE_BUFFER_FULL_BIT_ACCESS)&1) &&
	   (((CR2_Reg)>>SPI_RECE_IT_EN_BIT_ACCESS)&1))
	{
		SPI_ReceiveNoBlock(SPI_1);
	}
}

void SPI2_IRQHandler(void)
{
	uint32_t SR_Reg=SPI2->SPI_SR;
	uint32_t CR2_Reg=SPI2->SPI_CR2;
	/*Checking the transmit buffer to be empty and Checking on the transmit interrupt enable bit*/
	if((((SR_Reg)>>SPI_TRAN_BUFFER_EMPTY_BIT_ACCESS)&1) &&
	   (((CR2_Reg)>>SPI_TRAN_IT_EN_BIT_ACCESS)&1))
	{
		 SPI_TransmitNoBlock(SPI_2);
	}
	/*Checking the receive buffer to be full and Checking on the receive interrupt enable bit*/
	if((((SR_Reg)>>SPI_RECE_BUFFER_FULL_BIT_ACCESS)&1) &&
	   (((CR2_Reg)>>SPI_RECE_IT_EN_BIT_ACCESS)&1))
	{
		SPI_ReceiveNoBlock(SPI_2);
	}
}

