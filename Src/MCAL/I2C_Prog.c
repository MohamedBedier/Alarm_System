/***********************************************************
* @file I2C_Prog
* @Author Abdullah AlsharQawy
* @Brief The main file for I2C peripheral
***********************************************************/

#include <stdint.h>
#include <cnfg.h>
#include <Stm32F446xx.h>
#include <ErrType.h>
#include <I2C_Wrapper.h>

#include <I2C_Interface.h>
#include <I2C_prv.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
static uint8_t Slave_Per_TransmitIndexs[TOTAL_I2C], Slave_Per_ReceiveIndexs[TOTAL_I2C];
static volatile uint8_t Slave_IT_TransmitIndexs[TOTAL_I2C], Slave_IT_ReceiveIndexs[TOTAL_I2C];
static volatile uint8_t *Slave_IT_PdataTransmit[TOTAL_I2C], *Slave_IT_PdataReceive[TOTAL_I2C];
static uint8_t Slave_IT_SizeTransmit[TOTAL_I2C], Slave_IT_SizeReceive[TOTAL_I2C];
static volatile uint8_t DMA_EOT_I2C1_Flag, DMA_EOT_I2C2_Flag, DMA_EOT_I2C3_Flag;


/***********************************************************
* @fn I2C_voidInit
* @brief The I2C peripheral initialization function
* @param[in] I2CConfig : The initialization parameters struct for the I2C peripheral
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t I2C_voidInit(const I2C_Config_t* I2C_Config)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the I2C_Config pointer*/
	if(I2C_Config==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on the I2C_Config parameters values*/
	else if(I2C_Config->I2C>=TOTAL_I2C|| I2C_Config->GeneralCall>GCALL_ENABLE || I2C_Config->Mode>FM)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(I2C_Config->I2C);

		/*Clear this bit to work as 7-Bit address mode*/
		I2C->I2C_OAR1&=~(0b1<<ADDMODE_BIT_ACCESS);
		/*Set this bit as required from reference manual*/
		I2C->I2C_OAR1|= (0b1<<14);
		/*Configure Own Slave Address*/
		I2C->I2C_OAR1&=~(ADDRESS_BIT_MASK<<ADDRESS_BIT_ACCESS);
		I2C->I2C_OAR1|= (I2C_Config->Own_Address)<<ADDRESS_BIT_ACCESS;

		/*Configure General Call*/
		I2C->I2C_CR1&=~(0b1<<GCALL_BIT_ACCESS);
		I2C->I2C_CR1|= (I2C_Config->GeneralCall)<<GCALL_BIT_ACCESS;

		/*Setting Peripheral clock of APB1 after transferring it from MHZ to HZ*/
		I2C->I2C_CR2&=~(FREQ_BIT_MASK<<FREQ_BIT_ACCESS);
		I2C->I2C_CR2|= ((APB1_CLK/1000000)<<FREQ_BIT_ACCESS);

		/*Configure Mode (SM or FM)*/
		I2C->I2C_CCR&=~(0b1<<MODE_BIT_ACCESS);
		I2C->I2C_CCR|= (I2C_Config->Mode)<<MODE_BIT_ACCESS;

		/*Setting the value of T-low and T-high of SCL depending on the wanted frequency*/
		uint16_t ccr= (uint16_t)((APB1_CLK/(I2C_Config->SCL_Freq_HZ))/2);
		I2C->I2C_CCR&=~(CCR_BIT_MASK<<CCR_BIT_ACCESS);
		I2C->I2C_CCR|= ccr<<CCR_BIT_ACCESS;

		/*Enable Clock Stretching*/
		I2C->I2C_CR1&=~(0b1<<NOSTRETCH_BIT_ACCESS);

		ErrorState=OK;
	}
	return ErrorState;
}

/***********************************************************
* @fn I2C_SelcetPeripheral
* @brief Selection of I2C peripheral
* @param[in] i2c : The i2c peripheral, Option at @I2C_t enum
* @retval I2C_RegDef_t : the address of the I2C peripheral
***********************************************************/
static I2C_RegDef_t* I2C_SelcetPeripheral(I2C_t i2c)
{
	I2C_RegDef_t* I2C=NullPtr;
	/*Select the desired I2C*/
	switch(i2c)
	{
		case I2C_1:
			I2C=I2C1;
			break;
		case I2C_2:
			I2C=I2C2;
			break;
		case I2C_3:
			I2C=I2C3;
			break;
		default:
			I2C=NullPtr;
	}
	return I2C;
}

/***********************************************************
* @fn I2C_Enable
* @brief To enable the I2C peripheral
* @param[in] i2c : The i2c peripheral, Option at @I2C_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t I2C_Enable(I2C_t i2c)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the i2c value*/
	if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
		/*Enable I2C Peripheral*/
		I2C->I2C_CR1|=(0b1<<I2C_EN_BIT_ACCESS);
		/*Enabling acknowledgment*/
		I2C_EnableACK(I2C);
		ErrorState=OK;
	}
	return ErrorState;
}

/***********************************************************
* @fn I2C_Disable
* @brief To disable the I2C peripheral
* @param[in] i2c : The i2c peripheral, Option at @I2C_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t I2C_Disable(I2C_t i2c)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the i2c value*/
	if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
		/*Disable I2C Peripheral*/
		I2C->I2C_CR1&=~(0b1<<I2C_EN_BIT_ACCESS);

		ErrorState=OK;
	}
	return ErrorState;
}

/***********************************************************
* @fn I2C_EnableEventInterrupts
* @brief To enable the event interrupt of I2C peripheral
* @param[in] I2C : the address of the I2C peripheral
* @retval void
***********************************************************/
static void I2C_EnableEventInterrupts(I2C_RegDef_t* I2C)
{
	/*Setting the event interrupt enable bit*/
	I2C->I2C_CR2|=(0b1<<EVENT_IT_BIT_ACCESS);
}

/***********************************************************
* @fn I2C_EnableBufferInterrupts
* @brief To enable the buffer interrupt of I2C peripheral
* @param[in] I2C : the address of the I2C peripheral
* @retval void
***********************************************************/
static void I2C_EnableBufferInterrupts(I2C_RegDef_t* I2C)
{
	/*Setting the buffer interrupt enable bit for TXE and RXE*/
	I2C->I2C_CR2|=(0b1<<BUFFER_IT_BIT_ACCESS);
}

/***********************************************************
* @fn I2C_EnableErrorInterrupts
* @brief To enable the error interrupt of I2C peripheral
* @param[in] I2C : the address of the I2C peripheral
* @retval void
***********************************************************/
static void I2C_EnableErrorInterrupts(I2C_RegDef_t* I2C)
{
	/*Setting the error interrupt enable bit*/
	I2C->I2C_CR2|=(0b1<<ERROR_IT_BIT_ACCESS);
}

/***********************************************************
* @fn I2C_DisableEventInterrupts
* @brief To disable the event interrupt of I2C peripheral
* @param[in] I2C : the address of the I2C peripheral
* @retval void
***********************************************************/
static void I2C_DisableEventInterrupts(I2C_RegDef_t* I2C)
{
	/*Clearing the event interrupt enable bit*/
	I2C->I2C_CR2&=~(0b1<<EVENT_IT_BIT_ACCESS);
}

/***********************************************************
* @fn I2C_DisableBufferInterrupts
* @brief To disable the buffer interrupt of I2C peripheral
* @param[in] I2C : the address of the I2C peripheral
* @retval void
***********************************************************/
static void I2C_DisableBufferInterrupts(I2C_RegDef_t* I2C)
{
	/*Clearing the event interrupt enable bit*/
	I2C->I2C_CR2&=~(0b1<<EVENT_IT_BIT_ACCESS);
}

/***********************************************************
* @fn I2C_DisableErrorInterrupts
* @brief To disable the error interrupt of I2C peripheral
* @param[in] I2C : the address of the I2C peripheral
* @retval void
***********************************************************/
static void I2C_DisableErrorInterrupts(I2C_RegDef_t* I2C)
{
	/*Clearing the error interrupt enable bit*/
	I2C->I2C_CR2&=~(0b1<<ERROR_IT_BIT_ACCESS);
}

/***********************************************************
 * @fn I2C_MasterTransmitSynch
 * @brief To send data through i2c in master mode synchronously
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param[in] SlaveAddress : The I2C slave address in the network
 * @param[in] Pdata : The buffer of data to be sent
 * @param[in] Size : The size of the data to be sent
 * @param[in] TimeOut : Time out for protection
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
 ***********************************************************/
ErrorStatus_t I2C_MasterTransmitSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
	uint32_t Localu32TimeOut;

	/*Saving the values of interrupts flags before disabling them*/
	uint32_t I2C_Interrupts_Status=I2C->I2C_CR2;
	/*Disabling the Event, Buffer and Error interrupts*/
	I2C_DisableEventInterrupts(I2C);
	I2C_DisableBufferInterrupts(I2C);
	I2C_DisableErrorInterrupts(I2C);

	/*Checking on Pdata if it is null*/
	if(Pdata==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on i2c value*/
	else if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Initializing the time out variable with the sent time out value*/
		Localu32TimeOut=TimeOut;
		/*Waiting for the transmission line to not be busy except by myself to initiate communication*/
		while((((I2C->I2C_SR2)>>BUSY_BIT_ACCESS)&1) && Localu32TimeOut
		  && !(((I2C->I2C_SR2)>>MASTER_SLAVE_BIT)&1))
		{
			/*Decrementing the time out*/
			Localu32TimeOut--;
		}
		/*Checking if the time out reach zero or not*/
		if(Localu32TimeOut)
		{
			/*Initiation the communication by sending a start bit*/
			I2C_Master_StartBit(I2C);
			/*Waiting for the start bit to be sent to the line*/
			I2C_Master_PollStartBit(I2C);
			/*Sending the slave address with the LSB equal to zero to transmit data*/
			I2C_Master_SendAddress(I2C, I2C_WRITE, SlaveAddress);

			/*Initializing the time out variable with the sent time out value*/
			Localu32TimeOut=TimeOut;
			/*Waiting for the slave to send ACK showing that it exists in the network*/
			while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
			{
				/*Decrementing the time out*/
				Localu32TimeOut--;
			}
			/*Checking if the time out reach zero or not*/
			if(Localu32TimeOut)
			{
				/*Writing to SR2 register to clear the ADDR flag*/
				I2C->I2C_SR2=I2C->I2C_SR2;
				/*Loop over the sent data array*/
				for(uint8_t i=0; i<Size; i++)
				{
					/*Sending data by assigning it to the data register*/
					I2C->I2C_DR=Pdata[i];
					/*Waiting for the slave to send ACK showing that it received the data*/
					I2C_PollBTF(I2C);
				}
				/*Sending stop bit to close the communication*/
				I2C_Master_StopBit(I2C);
				/*Making sure that you are now returned to slave*/
				while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
				ErrorState=OK;
			}
			/*If the slave did not answer or it is not exist*/
			else
			{
				/*Sending stop bit to close the communication*/
				I2C_Master_StopBit(I2C);
				/*Making sure that you are now returned to slave*/
				while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
				/*Returning the error state that you get out because of the time out*/
				ErrorState=RUNTIME_OUT;
			}
		}
		/*If the bus is still busy for long time*/
		else
		{
			/*Returning the error state that you get out because of the time out*/
			ErrorState=RUNTIME_OUT;
		}
	}
	/*Re-assigning the values of interrupts flags*/
	I2C->I2C_CR2=I2C_Interrupts_Status;

	return ErrorState;
}

/***********************************************************
 * @fn I2C_MasterReceiveSynch
 * @brief To receive data through i2c in master mode synchronously
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param[in] SlaveAddress : The I2C slave address in the network
 * @param[out] Pdata : A buffer to receive data into
 * @param[in] Size : The size of the data to be received
 * @param[in] TimeOut : Time out for protection
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
 ***********************************************************/
ErrorStatus_t I2C_MasterReceiveSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut)
{
	ErrorStatus_t ErrorState=UNKNOWN;

	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
	uint32_t Localu32TimeOut;

	/*Saving the values of interrupts flags before disabling them*/
	uint32_t I2C_Interrupts_Status=I2C->I2C_CR2;
	/*Disabling the Event, Buffer and Error interrupts*/
	I2C_DisableEventInterrupts(I2C);
	I2C_DisableBufferInterrupts(I2C);
	I2C_DisableErrorInterrupts(I2C);

	/*Checking on Pdata if it is null*/
	if(Pdata==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on i2c value*/
	else if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Initializing the time out variable with the sent time out value*/
		Localu32TimeOut=TimeOut;
		/*Waiting for the transmission line to not be busy except by myself to initiate communication*/
		while((((I2C->I2C_SR2)>>BUSY_BIT_ACCESS)&1) && Localu32TimeOut
			&& !(((I2C->I2C_SR2)>>MASTER_SLAVE_BIT)&1))
		{
			/*Decrementing the time out*/
			Localu32TimeOut--;
		}
		/*Checking if the time out reach zero or not*/
		if(Localu32TimeOut)
		{
			/*Initiation the communication by sending a start bit*/
			I2C_Master_StartBit(I2C);
			/*Waiting for the start bit to be sent to the line*/
			I2C_Master_PollStartBit(I2C);
			/*Sending the slave address with the LSB equal to one to receive data*/
			I2C_Master_SendAddress(I2C, I2C_READ, SlaveAddress);

			/*if you want to receive only one byte of data*/
			if(Size==1)
			{
				/*Disable auto acknowledgment to not ask for more data*/
				I2C_DisableACK(I2C);
				/*Initializing the time out variable with the sent time out value*/
				Localu32TimeOut=TimeOut;
				/*Waiting for the slave to send ACK showing that it exists in the network*/
				while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
				{
					/*Decrementing the time out*/
					Localu32TimeOut--;
				}
				/*Checking if the time out reach zero or not*/
				if(Localu32TimeOut)
				{
					/*Writing to SR2 register to clear the ADDR flag*/
					I2C->I2C_SR2=I2C->I2C_SR2;
					/*Waiting for the slave to send data*/
					I2C_R_PollDataAck(I2C);
					/*Receive the one sent byte of data*/
					Pdata[0]=I2C->I2C_DR;
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Re-enable auto acknowledgment*/
					I2C_EnableACK(I2C);
					ErrorState=OK;
				}
				/*If the slave did not send data or it is not exist*/
				else
				{
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Returning the error state that you get out because of the time out*/
					ErrorState=RUNTIME_OUT;
				}
			}
			/*if you want to receive only two bytes of data*/
			else if(Size==2)
			{
				/*Initializing the time out variable with the sent time out value*/
				Localu32TimeOut=TimeOut;
				/*Waiting for the slave to send ACK showing that it exists in the network*/
				while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
				{
					/*Decrementing the time out*/
					Localu32TimeOut--;
				}
				/*Checking if the time out reach zero or not*/
				if(Localu32TimeOut)
				{
					/*Disable auto acknowledgment to not ask for more data*/
					I2C_DisableACK(I2C);
					/*To give NACK after the next byte reception to only receive 2 bytes*/
					I2C_SetPos(I2C);
					/*Writing to SR2 register to clear the ADDR flag*/
					I2C->I2C_SR2=I2C->I2C_SR2;
					/*Waiting for the slave to send two bytes of data*/
					I2C_PollBTF(I2C);
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Receiving the first byte of data*/
					Pdata[0]=I2C->I2C_DR;
					/*Receiving the second byte of data*/
					Pdata[1]=I2C->I2C_DR;
					/*Re-enable auto acknowledgment*/
					I2C_EnableACK(I2C);
					ErrorState=OK;
				}
				/*If the slave did not send data or it is not exist*/
				else
				{
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Returning the error state that you get out because of the time out*/
					ErrorState=RUNTIME_OUT;
				}
			}
			/*if you want to receive more than two bytes of data*/
			else
			{
				/*Initializing the time out variable with the sent time out value*/
				Localu32TimeOut=TimeOut;
				/*Waiting for the slave to send ACK showing that it exists in the network*/
				while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
				{
					/*Decrementing the time out*/
					Localu32TimeOut--;
				}
				if(Localu32TimeOut)
				{
					/*Writing to SR2 register to clear the ADDR flag*/
					I2C->I2C_SR2=I2C->I2C_SR2;
					/*Waiting for the slave to send a byte of data*/
					I2C_R_PollDataAck(I2C);
					/*Loop over the size of data you want to receive*/
					for(uint8_t i=0; i<Size; i++)
					{
						/*If there are only two bytes remaining to receive*/
						if(i==Size-2)
						{
							/*Disable auto acknowledgment to not ask for more data*/
							I2C_DisableACK(I2C);
							/*Receiving the second last byte of data*/
							Pdata[i]=I2C->I2C_DR;
							/*Waiting for the slave to send the last byte of data*/
							I2C_R_PollDataAck(I2C);
							/*Receiving the last of data*/
							Pdata[i+1]=I2C->I2C_DR;
							/*End the loop*/
							break;
						}
						/*If there are more two bytes remaining to receive*/
						else
						{
							/*Assigning the received data to the receiving buffer and giving auto ACK to receive more*/
							Pdata[i]=I2C->I2C_DR;
							/*Waiting for the slave to send another byte of data*/
							I2C_R_PollDataAck(I2C);
						}
					}
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Re-enable auto acknowledgment*/
					I2C_EnableACK(I2C);
					ErrorState=OK;
				}
				/*If the slave did not send data or it is not exist*/
				else
				{
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Returning the error state that you get out because of the time out*/
					ErrorState=RUNTIME_OUT;
				}
			}
		}
		/*If the bus is still busy for long time*/
		else
		{
			/*Returning the error state that you get out because of the time out*/
			ErrorState=RUNTIME_OUT;
		}
	}
	/*Re-assigning the values of interrupts flags*/
	I2C->I2C_CR2=I2C_Interrupts_Status;

	return ErrorState;
}

/***********************************************************
 * @fn I2C_MasterTransmitPeriodic
 * @brief To send data through i2c in master mode by periodically checking on the bus to be free then send data synchronously
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param[in] SlaveAddress : The I2C slave address in the network
 * @param[in] Pdata : The buffer of data to be sent
 * @param[in] Size : The size of the data to be sent
 * @retval uint32_t status of data whether it was sent or not
 ***********************************************************/
uint8_t I2C_MasterTransmitPeriodic(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size)
{
	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);

	/*Checking for the transmission line to not be busy to initiate communication*/
	if((((I2C->I2C_SR2)>>BUSY_BIT_ACCESS)&1)==0)
	{
		/*Saving the values of interrupts flags before disabling them*/
		uint32_t I2C_Interrupts_Status=I2C->I2C_CR2;
		/*Disabling the Event, Buffer and Error interrupts*/
		I2C_DisableEventInterrupts(I2C);
		I2C_DisableBufferInterrupts(I2C);
		I2C_DisableErrorInterrupts(I2C);

		/*Initiation the communication by sending a start bit*/
		I2C_Master_StartBit(I2C);
		/*Waiting for the start bit to be sent to the line*/
		I2C_Master_PollStartBit(I2C);
		/*Sending the slave address with the LSB equal to zero to transmit data*/
		I2C_Master_SendAddress(I2C, I2C_WRITE, SlaveAddress);

		/*Initiating a static counter to limit the time we wait for the slave to release the communication line to prevent starvation*/
		uint32_t static StaticCounter=0;
		/*Checking for the slave to send ACK showing that it exists in the network*/
		if((((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1))
		{
			/*Writing to SR2 register to clear the ADDR flag*/
			I2C->I2C_SR1=I2C->I2C_SR1;
			/*Loop over the sent data array*/
			for(uint8_t i=0; i<Size; i++)
			{
				/*Sending data by assigning it to the data register*/
				I2C->I2C_DR=Pdata[i];
				/*Waiting for the slave to send ACK showing that it received the data*/
				I2C_PollBTF(I2C);
			}
			/*Sending stop bit to close the communication*/
			I2C_Master_StopBit(I2C);
			/*Making sure that you are now returned to slave*/
			while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
			/*Re-assigning the values of interrupts flags*/
			I2C->I2C_CR2=I2C_Interrupts_Status;
			/*Re-initiating the counter to zero*/
			StaticCounter=0;
			/*Returning that the date was sent successfully*/
			return 1;
		}
		/*If the slave did not answer yet*/
		else
		{
			/*Incrementing the counter of starvation limit*/
			StaticCounter++;
			/*Checking on the static counter to release the communication bus*/
			if(StaticCounter==100U)
			{
				/*Sending stop bit to close the communication*/
				I2C_Master_StopBit(I2C);
				/*Making sure that you are now returned to slave*/
				while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
				/*Re-assigning the values of interrupts flags*/
				I2C->I2C_CR2=I2C_Interrupts_Status;
				/*Re-initiating the counter to zero*/
				StaticCounter=0;
			}
			/*Returning that the date was not sent yet*/
			return 0;
		}
	}
	/*If the communication line is busy now*/
	else
	{
		/*Returning that the date was not sent yet*/
		return 0;
	}
}

/***********************************************************
 * @fn I2C_MasterReceivePeriodic
 * @brief To receive data through i2c in master mode by periodically checking on the bus to be free then receive data synchronously
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param[in] SlaveAddress : The I2C slave address in the network
 * @param[out] Pdata : A buffer to receive data into
 * @param[in] Size : The size of the data to be received
 * @retval uint32_t status of data whether it was received or not
 ************************************************************/
uint8_t I2C_MasterReceivePeriodic(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size)
{
	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);

	/*Checking for the transmission line to not be busy to initiate communication*/
	if((((I2C->I2C_SR2)>>BUSY_BIT_ACCESS)&1)==0)
	{
		/*Saving the values of interrupts flags before disabling them*/
		uint32_t I2C_Interrupts_Status=I2C->I2C_CR2;
		/*Disabling the Event, Buffer and Error interrupts*/
		I2C_DisableEventInterrupts(I2C);
		I2C_DisableBufferInterrupts(I2C);
		I2C_DisableErrorInterrupts(I2C);

		/*Initiation the communication by sending a start bit*/
		I2C_Master_StartBit(I2C);
		/*Waiting for the start bit to be sent to the line*/
		I2C_Master_PollStartBit(I2C);
		/*Sending the slave address with the LSB equal to one to receive data*/
		I2C_Master_SendAddress(I2C, I2C_READ, SlaveAddress);

		/*if you want to receive only one byte of data*/
		if(Size==1)
		{
			/*Disable auto acknowledgment to not ask for more data*/
			I2C_DisableACK(I2C);
			/*Waiting for the slave to send ACK showing that it exists in the network and to clear the ADDR flag*/
			I2C_PollClrAddressAck(I2C);
			/*Waiting for the slave to send data*/
			I2C_R_PollDataAck(I2C);
			/*Receive the one sent byte of data*/
			Pdata[0]=I2C->I2C_DR;
			/*Sending stop bit to close the communication*/
			I2C_Master_StopBit(I2C);
			/*Making sure that you are now returned to slave*/
			while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
		}
		/*if you want to receive only two bytes of data*/
		else if(Size==2)
		{
			/*Waiting for the slave to send ACK showing that it exists in the network*/
			while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1));
			/*Disable auto acknowledgment to not ask for more data*/
			I2C_DisableACK(I2C);
			/*To give NACK after the next byte reception to only receive 2 bytes*/
			I2C_SetPos(I2C);
			/*Writing to SR2 register to clear the ADDR flag*/
			I2C->I2C_SR2=I2C->I2C_SR2;
			/*Waiting for the slave to send two bytes of data*/
			I2C_PollBTF(I2C);
			/*Sending stop bit to close the communication*/
			I2C_Master_StopBit(I2C);
			/*Receiving the first byte of data*/
			Pdata[0]=I2C->I2C_DR;
			/*Receiving the second byte of data*/
			Pdata[1]=I2C->I2C_DR;
		}
		/*if you want to receive more than two bytes of data*/
		else
		{
			/*Waiting for the slave to send ACK showing that it exists in the network and to clear the ADDR flag*/
			I2C_PollClrAddressAck(I2C);
			/*Waiting for the slave to send a byte of data*/
			I2C_R_PollDataAck(I2C);
			/*Loop over the size of data you want to receive*/
			for(uint8_t i=0; i<Size; i++)
			{
				if(i==Size-2)
				{
					/*Disable auto acknowledgment to not ask for more data*/
					I2C_DisableACK(I2C);
					/*Receiving the second last byte of data*/
					Pdata[i]=I2C->I2C_DR;
					/*Waiting for the slave to send the last byte of data*/
					I2C_R_PollDataAck(I2C);
					/*Receiving the last of data*/
					Pdata[i+1]=I2C->I2C_DR;
					/*End the loop*/
					break;
				}
				/*If there are more two bytes remaining to receive*/
				else
				{
					/*Assigning the received data to the receiving buffer and giving auto ACK to receive more*/
					Pdata[i]=I2C->I2C_DR;
					/*Waiting for the slave to send another byte of data*/
					I2C_R_PollDataAck(I2C);
				}
			}
			/*Sending stop bit to close the communication*/
			I2C_Master_StopBit(I2C);
			/*Making sure that you are now returned to slave*/
			while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
		}
		/*Re-enable auto acknowledgment*/
		I2C_EnableACK(I2C);
		/*Re-assigning the values of interrupts flags*/
		I2C->I2C_CR2=I2C_Interrupts_Status;

		/*Returning that the date was received successfully*/
		return 1;
	}
	/*If the communication line is busy now*/
	else
	{
		/*Returning that the date was not received yet without enabling the ACK nor retaining interrupt flags*/
		return 0;
	}
}

/************************************************************
 * @fn I2C_SlavePeriodic
 * @brief To receive and transmit data in slave mode by periodically checking for a signal from the master to initiate communication
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param PdataTransmit[in] : The buffer of data to transmit
 * @param SizeTransmit[in] : The size of the transmit data buffer
 * @param PdataReceive[in] : The buffer to receive data into
 * @param SizeReceive[in] : The size of the receive data buffer
 * @retval uint32_t status of communication whether it received of transmitted data or not
 ************************************************************/
uint8_t I2C_SlavePeriodic(I2C_t i2c, uint8_t* PdataTransmit, uint8_t SizeTransmit, uint8_t* PdataReceive, uint8_t SizeReceive)
{
	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
	static uint32_t I2C_Interrupts_Status;

	/*Saving the values of interrupts flags before disabling them*/
	I2C_Interrupts_Status=I2C->I2C_CR2;
	/*Disabling the Event, Buffer and Error interrupts*/
	I2C_SlaveInterruptDisable(i2c);

	/*Checking if someone called my address*/
	if(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1)
	{
		/*Clearing the ADDR flag*/
		I2C_PollClrAddressAck(I2C);
		/*If you were addressed as a transmitter slave*/
		if(((I2C->I2C_SR2)>>TRA_BIT_ACCESS)&1)
		{
			/*While no stop bit was sent yet*/
			while(!(((I2C->I2C_SR1)>>STOPF_BIT_ACCESS)&1))
			{
				/*Transmitting the next data in the transmission buffer*/
				I2C->I2C_DR=PdataTransmit[Slave_Per_TransmitIndexs[i2c]];
				/*Incrementing the transmission buffer index*/
				Slave_Per_TransmitIndexs[i2c]++;
				/*Checking on the transmission buffer index if reached maximum size*/
				if(Slave_Per_TransmitIndexs[i2c]==SizeTransmit)
				{
					/*Re-initilazing the transmission buffer index to enable circular data transfer*/
					Slave_Per_TransmitIndexs[i2c]=0;
				}
				/*Waiting the data to be sent successfully*/
				I2C_PollBTF(I2C);
			}
		}
		/*If you were addressed as a receiver slave*/
		else
		{
			/*Waiting to receive new data*/
			I2C_R_PollDataAck(I2C);
			/*While no stop bit was sent yet*/
			while(!(((I2C->I2C_SR1)>>STOPF_BIT_ACCESS)&1))
			{
				/*Receiving the received data in the reception buffer*/
				PdataReceive[Slave_Per_ReceiveIndexs[i2c]]=I2C->I2C_DR;
				/*Incrementing the reception buffer index*/
				Slave_Per_ReceiveIndexs[i2c]++;
				/*Checking on the reception buffer index if reached maximum size*/
				if(Slave_Per_ReceiveIndexs[i2c]==SizeReceive)
				{
					/*Re-initilazing the reception buffer index to enable circular data transfer*/
					Slave_Per_ReceiveIndexs[i2c]=0;
				}
				/*Waiting to receive new data*/
				I2C_R_PollDataAck(I2C);
			}
			/*Receiving the last received data byte after the last previous ACK from the slave*/
			PdataReceive[Slave_Per_ReceiveIndexs[i2c]]=I2C->I2C_DR;
			/*Incrementing the reception buffer index*/
			Slave_Per_ReceiveIndexs[i2c]++;
			/*Checking on the reception buffer index if reached maximum size*/
			if(Slave_Per_ReceiveIndexs[i2c]==SizeReceive)
			{
				/*Re-initilazing the reception buffer index to enable circular data transfer*/
				Slave_Per_ReceiveIndexs[i2c]=0;
			}
		}

		/*Re-assigning the values of interrupts flags*/
		I2C->I2C_CR2=I2C_Interrupts_Status;

		/*Returning that there was transferred date*/
		return 1;
	}
	/*If none called my address*/
	else
	{
		/*Returning that no data was transferred without retaining interrupt flags*/
		return 0;
	}
}

/************************************************************
 * @fn I2C_SlaveInterruptEnable
 * @brief To receive and transmit data in slave mode in interrupt by enabling interrupts
 *        and by assigning the transmission and reception data buffers to the global arrays
 *        to be handled in the interrupt
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param PdataTransmit[in] : The buffer of data to transmit
 * @param SizeTransmit[in] : The size of the transmit data buffer
 * @param PdataReceive[in] : The buffer to receive data into
 * @param SizeReceive[in] : The size of the receive data buffer
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
 ************************************************************/
ErrorStatus_t I2C_SlaveInterruptEnable(I2C_t i2c, uint8_t* PdataTransmit, uint8_t SizeTransmit, uint8_t* PdataReceive, uint8_t SizeReceive)
{
	ErrorStatus_t ErrorState=UNKNOWN;

	/*Checking on i2c value*/
	if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Checking on the pointer to the transmitted data*/
		if(PdataTransmit!=NullPtr)
		{
			/*Assigning the transmission data buffer to the global transmission buffer*/
			Slave_IT_PdataTransmit[i2c]=PdataTransmit;
			/*Assigning the transmission data buffer size to the global transmission buffer of sizes*/
			Slave_IT_SizeTransmit[i2c]=SizeTransmit;
			/*Assigning the transmission data buffer index to zero*/
			Slave_IT_TransmitIndexs[i2c]=0;
		}
		/*Checking on the pointer to the received data*/
		if(PdataReceive!=NullPtr)
		{
			/*Assigning the reception data buffer to the global reception buffer*/
			Slave_IT_PdataReceive[i2c]=PdataReceive;
			/*Assigning the reception data buffer size to the global reception buffer of sizes*/
			Slave_IT_SizeReceive[i2c]=SizeReceive;
			/*Assigning the reception data buffer index to zero*/
			Slave_IT_ReceiveIndexs[i2c]=0;
		}
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
		/*Enabling Event interrupts to have interrupt at addressing and in stop bit detection*/
		I2C_EnableEventInterrupts(I2C);
		/*Enabling Error interrupts to have interrupt at NACK when transmitting data to release the bus and to not transmit any further data*/
		I2C_EnableErrorInterrupts(I2C);
		/*Enabling Buffer interrupts to have interrupt at successful data transferring*/
		I2C_EnableBufferInterrupts(I2C);

		/*Enabling auto acknowledgment*/
		I2C_EnableACK(I2C);

		ErrorState=OK;
	}

	return ErrorState;
}

/************************************************************
 * @fn I2C_SlaveInterruptDisable
 * @brief To disable all peripheral interrupts
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
 ************************************************************/
ErrorStatus_t I2C_SlaveInterruptDisable(I2C_t i2c)
{
	ErrorStatus_t ErrorState=UNKNOWN;

	/*Checking on i2c value*/
	if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);

		/*Disabling the Event, Buffer and Error interrupts*/
		I2C_DisableEventInterrupts(I2C);
		I2C_DisableBufferInterrupts(I2C);
		I2C_DisableErrorInterrupts(I2C);
		ErrorState=OK;
	}

	return ErrorState;
}

/************************************************************
 * @fn I2C_EnableMasterDMA
 * @brief To enable transferring data by DMA in master mode after initiating the communication
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param[in] SlaveAddress : The I2C slave address in the network
 * @param[in] RW : Read or Write, Options at @I2C_ReadWrite_t enum
 * @param[in] TimeOut : Time out for protection
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
************************************************************/
ErrorStatus_t I2C_EnableMasterDMA(I2C_t i2c, uint8_t SlaveAddress, I2C_ReadWrite_t RW, uint32_t TimeOut)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	uint32_t Localu32TimeOut;

	/*Checking on i2c and RW values*/
	if(i2c>=TOTAL_I2C || RW>I2C_READ)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);

		/*Disabling the Event and Buffer interrupts*/
		I2C_DisableEventInterrupts(I2C);
		I2C_DisableBufferInterrupts(I2C);

		/*Enabling the I2C DMA bit*/
		I2C->I2C_CR2|=0b1<<DMA_EN_BIT_ACCESS;
		/*Enabling LAST bit so that DMA sends NACK at the last data reception*/
		I2C->I2C_CR2|=0b1<<LAST_BIT_ACCESS;
		/*Initializing the time out with the sent value of time out*/
		Localu32TimeOut=TimeOut;
		/*Waiting till the bus become free except if it was busy by myself*/
		while((((I2C->I2C_SR2)>>BUSY_BIT_ACCESS)&1) && Localu32TimeOut
		  && !(((I2C->I2C_SR2)>>MASTER_SLAVE_BIT)&1))
		{
			/*Decrementing the time out*/
			Localu32TimeOut--;
		}
		/*Checking if the time out reach zero or not*/
		if(Localu32TimeOut)
		{
			/*Initiation the communication by sending a start bit*/
			I2C_Master_StartBit(I2C);
			/*Waiting for the start bit to be sent to the line*/
			I2C_Master_PollStartBit(I2C);
			/*Sending the slave address with the LSB equal to RW value*/
			I2C_Master_SendAddress(I2C, RW, SlaveAddress);

			/*Re-Initializing the time out with the sent value of time out*/
			Localu32TimeOut=TimeOut;
			/*Waiting for the slave to send ACK showing that it exists in the network*/
			while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
			{
				/*Decrementing the time out*/
				Localu32TimeOut--;
			}
			/*Checking if the time out reach zero or not*/
			if(Localu32TimeOut)
			{
				/*Writing to SR2 register to clear the ADDR flag*/
				I2C->I2C_SR2=I2C->I2C_SR2;
				ErrorState=OK;
			}
			/*If the slave was not existed*/
			else
			{
				/*Releasing the transmission bus*/
				I2C_Master_StopBit(I2C);
				/*Making sure that you are now returned to slave*/
				while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
				/*Returning the error state that you get out because of the time out*/
				ErrorState=RUNTIME_OUT;
			}
		}
		/*If the bus was busy for long time*/
		else
		{
			/*Returning the error state that you get out because of the time out*/
			ErrorState=RUNTIME_OUT;
		}
	}

	return ErrorState;
}

/************************************************************
 * @fn I2C_EnableSlaveDMA
 * @brief To enable transferring data by DMA in slave mode
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
************************************************************/
ErrorStatus_t I2C_EnableSlaveDMA(I2C_t i2c)
{
	ErrorStatus_t ErrorState=UNKNOWN;

	/*Checking on i2c value*/
	if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
		/*Setting the I2C DMA enable bit*/
		I2C->I2C_CR2|=0b1<<DMA_EN_BIT_ACCESS;
		/*Enabling the Event interrupt to get at stop bit detection*/
		I2C_EnableEventInterrupts(I2C);
		ErrorState=OK;
	}

	return ErrorState;
}

/************************************************************
 * @fn I2C_DisableDMA
 * @brief To disable transferring data by DMA
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
************************************************************/
ErrorStatus_t I2C_DisableDMA(I2C_t i2c)
{
	ErrorStatus_t ErrorState=UNKNOWN;

	/*Checking on i2c value*/
	if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Select the desired I2C*/
		I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);

		/*Clearing the I2C DMA enable bit*/
		I2C->I2C_CR2&=~(0b1<<DMA_EN_BIT_ACCESS);
		/*Clearing the LAST bit*/
		I2C->I2C_CR2&=~(0b1<<LAST_BIT_ACCESS);

		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
 * @fn I2C_RepeatedStartSendSynch
 * @brief Used in sending a repeated start, use this function if you want to send data
 *        synchronously without sending a stop bit so you can use it or any other
 *        previously provided functions to send the repeated start with the same slave
 *        or with a different one to keep sending data.
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param[in] SlaveAddress : The I2C slave address in the network
 * @param[in] Pdata : The buffer of data to be sent
 * @param[in] Size : The size of the data to be sent
 * @param[in] TimeOut : Time out for protection
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
 ***********************************************************/
ErrorStatus_t I2C_RepeatedStartSendSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
	uint32_t Localu32TimeOut;

	/*Saving the values of interrupts flags before disabling them*/
	uint32_t I2C_Interrupts_Status=I2C->I2C_CR2;
	/*Disabling the Event, Buffer and Error interrupts*/
	I2C_DisableEventInterrupts(I2C);
	I2C_DisableBufferInterrupts(I2C);
	I2C_DisableErrorInterrupts(I2C);

	/*Checking on Pdata if it is null*/
	if(Pdata==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on i2c value*/
	else if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Initializing the time out variable with the sent time out value*/
		Localu32TimeOut=TimeOut;
		/*Waiting for the transmission line to not be busy except by myself to initiate communication*/
		while((((I2C->I2C_SR2)>>BUSY_BIT_ACCESS)&1) && Localu32TimeOut
		  && !(((I2C->I2C_SR2)>>MASTER_SLAVE_BIT)&1))
		{
			/*Decrementing the time out*/
			Localu32TimeOut--;
		}
		/*Checking if the time out reach zero or not*/
		if(Localu32TimeOut)
		{
			/*Initiation the communication by sending a start bit*/
			I2C_Master_StartBit(I2C);
			/*Waiting for the start bit to be sent to the line*/
			I2C_Master_PollStartBit(I2C);
			/*Sending the slave address with the LSB equal to zero to transmit data*/
			I2C_Master_SendAddress(I2C, I2C_WRITE, SlaveAddress);

			/*Initializing the time out variable with the sent time out value*/
			Localu32TimeOut=TimeOut;
			/*Waiting for the slave to send ACK showing that it exists in the network*/
			while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
			{
				/*Decrementing the time out*/
				Localu32TimeOut--;
			}
			/*Checking if the time out reach zero or not*/
			if(Localu32TimeOut)
			{
				/*Writing to SR2 register to clear the ADDR flag*/
				I2C->I2C_SR2=I2C->I2C_SR2;
				/*Loop over the sent data array*/
				for(uint8_t i=0; i<Size; i++)
				{
					/*Sending data by assigning it to the data register*/
					I2C->I2C_DR=Pdata[i];
					/*Waiting for the slave to send ACK showing that it received the data*/
					I2C_PollBTF(I2C);
				}

				ErrorState=OK;
			}
			/*If the slave did not answer or it is not exist*/
			else
			{
				/*Sending stop bit to close the communication just in case the slave didn't respond*/
				I2C_Master_StopBit(I2C);
				/*Making sure that you are now returned to slave*/
				while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
				/*Returning the error state that you get out because of the time out*/
				ErrorState=RUNTIME_OUT;
			}
		}
		/*If the bus is still busy for long time*/
		else
		{
			/*Returning the error state that you get out because of the time out*/
			ErrorState=RUNTIME_OUT;
		}
	}
	/*Re-assigning the values of interrupts flags*/
	I2C->I2C_CR2=I2C_Interrupts_Status;

	return ErrorState;
}

/***********************************************************
 * @fn I2C_RepeatedStartReceiveSynch
 * @brief Used in sending a repeated start, use this function if you want to receive data
 *        synchronously without sending a stop bit so you can use it or any other
 *        previously provided functions to send the repeated start with the same slave
 *        or with a different one to keep receiving data.
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @param[in] SlaveAddress : The I2C slave address in the network
 * @param[out] Pdata : A buffer to receive data into
 * @param[in] Size : The size of the data to be received
 * @param[in] TimeOut : Time out for protection
 * @retval ErrorStatus_t, Options at @ErrorStatus_t enum
 ***********************************************************/
ErrorStatus_t I2C_RepeatedStartReceiveSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut)
{
	ErrorStatus_t ErrorState=UNKNOWN;

	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
	uint32_t Localu32TimeOut;

	/*Saving the values of interrupts flags before disabling them*/
	uint32_t I2C_Interrupts_Status=I2C->I2C_CR2;
	/*Disabling the Event, Buffer and Error interrupts*/
	I2C_DisableEventInterrupts(I2C);
	I2C_DisableBufferInterrupts(I2C);
	I2C_DisableErrorInterrupts(I2C);

	/*Checking on Pdata if it is null*/
	if(Pdata==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on i2c value*/
	else if(i2c>=TOTAL_I2C)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Initializing the time out variable with the sent time out value*/
		Localu32TimeOut=TimeOut;
		/*Waiting for the transmission line to not be busy except by myself to initiate communication*/
		while((((I2C->I2C_SR2)>>BUSY_BIT_ACCESS)&1) && Localu32TimeOut
		  && !(((I2C->I2C_SR2)>>MASTER_SLAVE_BIT)&1))
		{
			/*Decrementing the time out*/
			Localu32TimeOut--;
		}
		/*Checking if the time out reach zero or not*/
		if(Localu32TimeOut)
		{
			/*Initiation the communication by sending a start bit*/
			I2C_Master_StartBit(I2C);
			/*Waiting for the start bit to be sent to the line*/
			I2C_Master_PollStartBit(I2C);
			/*Sending the slave address with the LSB equal to one to receive data*/
			I2C_Master_SendAddress(I2C, I2C_READ, SlaveAddress);

			/*if you want to receive only one byte of data*/
			if(Size==1)
			{
				/*Disable auto acknowledgment to not ask for more data*/
				I2C_DisableACK(I2C);
				/*Initializing the time out variable with the sent time out value*/
				Localu32TimeOut=TimeOut;
				/*Waiting for the slave to send ACK showing that it exists in the network*/
				while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
				{
					/*Decrementing the time out*/
					Localu32TimeOut--;
				}
				/*Checking if the time out reach zero or not*/
				if(Localu32TimeOut)
				{
					/*Writing to SR2 register to clear the ADDR flag*/
					I2C->I2C_SR2=I2C->I2C_SR2;
					/*Waiting for the slave to send data*/
					I2C_R_PollDataAck(I2C);
					/*Receive the one sent byte of data*/
					Pdata[0]=I2C->I2C_DR;
					/*Re-enable auto acknowledgment*/
					I2C_EnableACK(I2C);
					ErrorState=OK;
				}
				/*If the slave did not send data or it is not exist*/
				else
				{
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Returning the error state that you get out because of the time out*/
					ErrorState=RUNTIME_OUT;
				}
			}
			/*if you want to receive only two bytes of data*/
			else if(Size==2)
			{
				/*Initializing the time out variable with the sent time out value*/
				Localu32TimeOut=TimeOut;
				/*Waiting for the slave to send ACK showing that it exists in the network*/
				while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
				{
					/*Decrementing the time out*/
					Localu32TimeOut--;
				}
				/*Checking if the time out reach zero or not*/
				if(Localu32TimeOut)
				{
					/*Disable auto acknowledgment to not ask for more data*/
					I2C_DisableACK(I2C);
					/*To give NACK after the next byte reception to only receive 2 bytes*/
					I2C_SetPos(I2C);
					/*Writing to SR2 register to clear the ADDR flag*/
					I2C->I2C_SR2=I2C->I2C_SR2;
					/*Waiting for the slave to send two bytes of data*/
					I2C_PollBTF(I2C);
					/*Receiving the first byte of data*/
					Pdata[0]=I2C->I2C_DR;
					/*Receiving the second byte of data*/
					Pdata[1]=I2C->I2C_DR;
					/*Re-enable auto acknowledgment*/
					I2C_EnableACK(I2C);
					ErrorState=OK;
				}
				/*If the slave did not send data or it is not exist*/
				else
				{
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Returning the error state that you get out because of the time out*/
					ErrorState=RUNTIME_OUT;
				}
			}
			/*if you want to receive more than two bytes of data*/
			else
			{
				/*Initializing the time out variable with the sent time out value*/
				Localu32TimeOut=TimeOut;
				/*Waiting for the slave to send ACK showing that it exists in the network*/
				while(!(((I2C->I2C_SR1)>>ADDR_BIT_ACCESS)&1) && Localu32TimeOut)
				{
					/*Decrementing the time out*/
					Localu32TimeOut--;
				}
				if(Localu32TimeOut)
				{
					/*Writing to SR2 register to clear the ADDR flag*/
					I2C->I2C_SR2=I2C->I2C_SR2;
					/*Waiting for the slave to send a byte of data*/
					I2C_R_PollDataAck(I2C);
					/*Loop over the size of data you want to receive*/
					for(uint8_t i=0; i<Size; i++)
					{
						/*If there are only two bytes remaining to receive*/
						if(i==Size-2)
						{
							/*Disable auto acknowledgment to not ask for more data*/
							I2C_DisableACK(I2C);
							/*Receiving the second last byte of data*/
							Pdata[i]=I2C->I2C_DR;
							/*Waiting for the slave to send the last byte of data*/
							I2C_R_PollDataAck(I2C);
							/*Receiving the last of data*/
							Pdata[i+1]=I2C->I2C_DR;
							/*End the loop*/
							break;
						}
						/*If there are more two bytes remaining to receive*/
						else
						{
							/*Assigning the received data to the receiving buffer and giving auto ACK to receive more*/
							Pdata[i]=I2C->I2C_DR;
							/*Waiting for the slave to send another byte of data*/
							I2C_R_PollDataAck(I2C);
						}
					}
					/*Re-enable auto acknowledgment*/
					I2C_EnableACK(I2C);
					ErrorState=OK;
				}
				/*If the slave did not send data or it is not exist*/
				else
				{
					/*Sending stop bit to close the communication*/
					I2C_Master_StopBit(I2C);
					/*Making sure that you are now returned to slave*/
					while((((I2C)->I2C_SR2)>>MASTER_SLAVE_BIT)&1);
					/*Returning the error state that you get out because of the time out*/
					ErrorState=RUNTIME_OUT;
				}
			}
		}
		/*If the bus is still busy for long time*/
		else
		{
			/*Returning the error state that you get out because of the time out*/
			ErrorState=RUNTIME_OUT;
		}
	}
	/*Re-assigning the values of interrupts flags*/
	I2C->I2C_CR2=I2C_Interrupts_Status;

	return ErrorState;
}

/************************************************************
 * @fn I2C_DataRegisterAddress
 * @brief To return the data register address of the wanted I2C peripheral
 * @param[in] i2c : The I2C peripheral, Option at @I2C_t enum
 * @retval uint32_t* address of the data register
************************************************************/
uint32_t* I2C_DataRegisterAddress(I2C_t i2c)
{
	/*Select the desired I2C*/
	I2C_RegDef_t* I2C=I2C_SelcetPeripheral(i2c);
	/*Returning the data register address*/
	return (uint32_t*)(&(I2C->I2C_DR));

}

/************************************************************
 * @fn DMA_Master_CallBack_I2C1
 * @brief This function should be called at end of transmission interrupt of DMA specific for the I2C1 peripheral
 * @param void
 * @retval void
************************************************************/
void DMA_Master_CallBack_I2C1(void)
{
	/*Disabling transferring data by DM*/
	I2C_DisableDMA(I2C_1);
	if((((I2C1->I2C_SR2)>>TRA_BIT_ACCESS)&1))
	{
		/*Giving indication to the ISR that we are working on DMA mode*/
		DMA_EOT_I2C1_Flag=1;
		/*Enabling Event interrupt to get interrupt when BTF is set*/
		I2C_EnableEventInterrupts(I2C1);
	}
	else
	{
		/*Sending stop bit to close the communication*/
		I2C_Master_StopBit(I2C1);
		/*Making sure that you are now returned to slave*/
		while((((I2C1->I2C_SR2)>>MASTER_SLAVE_BIT)&1));

		/*Disabling the event interrupts to have no further interrupts*/
		I2C_DisableEventInterrupts(I2C1);

		/*Calling the call out function that you can implement at the I2C_cfg.c to choose what to do
		  after finishing transferring through the DMA, you can Re-enable transferring in it my setting
		  a flag in this call-out function and checking on it periodically*/
		DMA_I2C1_CallOut_Func();
	}
}

/************************************************************
 * @fn DMA_Master_CallBack_I2C2
 * @brief This function should be called at end of transmission interrupt of DMA specific for the I2C2 peripheral
 * @param void
 * @retval void
************************************************************/
void DMA_Master_CallBack_I2C2(void)
{
	/*Disabling transferring data by DM*/
	I2C_DisableDMA(I2C_2);
	if((((I2C2->I2C_SR2)>>TRA_BIT_ACCESS)&1))
	{
		/*Giving indication to the ISR that we are working on DMA mode*/
		DMA_EOT_I2C2_Flag=1;
		/*Enabling Event interrupt to get interrupt when BTF is set*/
		I2C_EnableEventInterrupts(I2C2);
	}
	else
	{
		/*Sending stop bit to close the communication*/
		I2C_Master_StopBit(I2C2);
		/*Making sure that you are now returned to slave*/
		while((((I2C2->I2C_SR2)>>MASTER_SLAVE_BIT)&1));

		/*Disabling the event interrupts to have no further interrupts*/
		I2C_DisableEventInterrupts(I2C2);

		/*Calling the call out function that you can implement at the I2C_cfg.c to choose what to do
		  after finishing transferring through the DMA, you can Re-enable transferring in it my setting
		  a flag in this call-out function and checking on it periodically*/
		DMA_I2C2_CallOut_Func();
	}
}

/************************************************************
 * @fn DMA_Master_CallBack_I2C3
 * @brief This function should be called at end of transmission interrupt of DMA specific for the I2C3 peripheral
 * @param void
 * @retval void
************************************************************/
void DMA_Master_CallBack_I2C3(void)
{
	/*Disabling transferring data by DM*/
	I2C_DisableDMA(I2C_3);
	if((((I2C3->I2C_SR2)>>TRA_BIT_ACCESS)&1))
	{
		/*Giving indication to the ISR that we are working on DMA mode*/
		DMA_EOT_I2C3_Flag=1;
		/*Enabling Event interrupt to get interrupt when BTF is set*/
		I2C_EnableEventInterrupts(I2C3);
	}
	else
	{
		/*Sending stop bit to close the communication*/
		I2C_Master_StopBit(I2C3);
		/*Making sure that you are now returned to slave*/
		while((((I2C3->I2C_SR2)>>MASTER_SLAVE_BIT)&1));

		/*Disabling the event interrupts to have no further interrupts*/
		I2C_DisableEventInterrupts(I2C3);

		/*Calling the call out function that you can implement at the I2C_cfg.c to choose what to do
		  after finishing transferring through the DMA, you can Re-enable transferring in it my setting
		  a flag in this call-out function and checking on it periodically*/
		DMA_I2C3_CallOut_Func();
	}
}






/***********************************	IRQs	***********************************/
static I2C_IT_States_t I2C1_State=STOP_STATE;
static I2C_IT_States_t I2C2_State=STOP_STATE;
static I2C_IT_States_t I2C3_State=STOP_STATE;


void I2C1_EV_IRQHandler(void)
{
	/*If it is slave*/
	if(!((I2C1->I2C_SR2>>MASTER_SLAVE_BIT)&1))
	{
		/*If a Stop bit is detected*/
		if((((I2C1->I2C_SR1)>>STOPF_BIT_ACCESS)&1))
		{
			/*Changing the global state*/
			I2C1_State=STOP_STATE;
			/*Writing to CR1 register to clear the stop bit*/
			I2C1->I2C_CR1=I2C1->I2C_CR1;
		}

		/*If slave addressing is detected in first time*/
		else if((((I2C1->I2C_SR1)>>ADDR_BIT_ACCESS)&1) &&
				I2C1_State!=DATA_R_ACK_STATE && I2C1_State!=DATA_T_ACK_STATE)
		{
			/*Clearing the ADDR flag*/
			I2C_PollClrAddressAck(I2C1);
			/*If the slave was addressed as a transmitter*/
			if((((I2C1->I2C_SR2)>>TRA_BIT_ACCESS)&1))
			{
				/*Changing the global state*/
				I2C1_State=DATA_T_ACK_STATE;
				/*Sending the first data byte*/
				I2C1->I2C_DR=Slave_IT_PdataTransmit[I2C_1][Slave_IT_TransmitIndexs[I2C_1]];
				/*Incrementing the transmission buffer index*/
				Slave_IT_TransmitIndexs[I2C_1]++;
				/*Checking on the transmission buffer index if reached maximum size*/
				if(Slave_IT_TransmitIndexs[I2C_1]==Slave_IT_SizeTransmit[I2C_1])
				{
					/*Re-initilazing the transmission buffer index to enable circular data transfer*/
					Slave_IT_TransmitIndexs[I2C_1]=0;
				}
			}
			/*If the slave was addressed as a receiver*/
			else
			{
				/*Changing the global state*/
				I2C1_State=DATA_R_ACK_STATE;
			}
		}

		/*If slave addressing is detected in another time in case of a repeated start*/
		else if((((I2C1->I2C_SR1)>>ADDR_BIT_ACCESS)&1) &&
				(I2C1_State!=DATA_R_ACK_STATE || I2C1_State!=DATA_T_ACK_STATE))
		{
			/*Clearing the ADDR flag*/
			I2C_PollClrAddressAck(I2C1);
			/*If the slave was addressed as a transmitter*/
			if((((I2C1->I2C_SR2)>>TRA_BIT_ACCESS)&1))
			{
				/*Changing the global state*/
				I2C1_State=DATA_T_ACK_STATE;
				/*Sending the first data byte*/
				I2C1->I2C_DR=Slave_IT_PdataTransmit[I2C_1][Slave_IT_TransmitIndexs[I2C_1]];
				/*Incrementing the transmission buffer index*/
				Slave_IT_TransmitIndexs[I2C_1]++;
				/*Checking on the transmission buffer index if reached maximum size*/
				if(Slave_IT_TransmitIndexs[I2C_1]==Slave_IT_SizeTransmit[I2C_1])
				{
					/*Re-initilazing the transmission buffer index to enable circular data transfer*/
					Slave_IT_TransmitIndexs[I2C_1]=0;
				}
			}
			/*If the slave was addressed as a receiver*/
			else
			{
				/*Changing the global state*/
				I2C1_State=DATA_R_ACK_STATE;
			}
		}

		/*If it was in Reception state*/
		else if(I2C1_State==DATA_R_ACK_STATE)
		{
			/*Receiving the received data in the reception buffer*/
			Slave_IT_PdataReceive[I2C_1][Slave_IT_ReceiveIndexs[I2C_1]]=(uint8_t)I2C1->I2C_DR;
			/*Incrementing the reception buffer index*/
			Slave_IT_ReceiveIndexs[I2C_1]++;
			/*Checking on the reception buffer index if reached maximum size*/
			if(Slave_IT_ReceiveIndexs[I2C_1]==Slave_IT_SizeReceive[I2C_1])
			{
				/*Re-initilazing the reception buffer index to enable circular data transfer*/
				Slave_IT_ReceiveIndexs[I2C_1]=0;
			}
		}

		/*If it was in Transmission state*/
		else if(I2C1_State==DATA_T_ACK_STATE)
		{
			/*Sending the next data byte*/
			I2C1->I2C_DR=Slave_IT_PdataTransmit[I2C_1][Slave_IT_TransmitIndexs[I2C_1]];
			/*Incrementing the transmission buffer index*/
			Slave_IT_TransmitIndexs[I2C_1]++;
			/*Checking on the transmission buffer index if reached maximum size*/
			if(Slave_IT_TransmitIndexs[I2C_1]==Slave_IT_SizeTransmit[I2C_1])
			{
				/*Re-initilazing the transmission buffer index to enable circular data transfer*/
				Slave_IT_TransmitIndexs[I2C_1]=0;
			}
		}
	}



	/*If it is master*/
	else
	{
		/*if you are working at DMA mode and you finished transferring the whole data*/
		if((((I2C1->I2C_SR1)>>BTF_BIT_ACCESS)&1) && DMA_EOT_I2C1_Flag)
		{
			/*Re-initailizing the flag to zero*/
			DMA_EOT_I2C1_Flag=0;
			/*Sending stop bit to close the communication*/
			I2C_Master_StopBit(I2C1);
			/*Making sure that you are now returned to slave*/
			while((((I2C1->I2C_SR2)>>MASTER_SLAVE_BIT)&1));

			/*Disabling the event interrupts to have no further interrupts*/
			I2C_DisableEventInterrupts(I2C1);

			/*Calling the call out function that you can implement at the I2C_cfg.c to choose what to do
			  after finishing transferring through the DMA, you can Re-enable transferring in it my setting
			  a flag in this call-out function and checking on it periodically*/
			DMA_I2C1_CallOut_Func();
		}
	}
}

void I2C1_ER_IRQHandler(void)
{
	/*If it is slave*/
	if(!((I2C1->I2C_SR2>>MASTER_SLAVE_BIT)&1))
	{
		/*If a NACK is received in case of end of transmission from this slave to the master*/
		if(((I2C1->I2C_SR1)>>ACKF_BIT_ACCESS)&1)
		{
			/*Decrementing the transmission buffer index*/
			Slave_IT_TransmitIndexs[I2C_1]--;
			/*Clearing the ACK Failure flag*/
			I2C1->I2C_SR1&=~(1<<ACKF_BIT_ACCESS);
			/*Changing the global state to stop state as it won't detect the stop bit*/
			I2C1_State=STOP_STATE;
			/*Writing to CR1 register to clear the stop bit*/
			I2C1->I2C_CR1=I2C1->I2C_CR1;
		}
	}

	/*If it is master*/
	else
	{
		//master
	}
}





void I2C2_EV_IRQHandler(void)
{
	/*If it is slave*/
	if(!((I2C2->I2C_SR2>>MASTER_SLAVE_BIT)&1))
	{
		/*If a Stop bit is detected*/
		if((((I2C2->I2C_SR1)>>STOPF_BIT_ACCESS)&1))
		{
			/*Changing the global state*/
			I2C2_State=STOP_STATE;
			/*Writing to CR1 register to clear the stop bit*/
			I2C2->I2C_CR1=I2C2->I2C_CR1;
		}

		/*If slave addressing is detected in first time*/
		else if((((I2C2->I2C_SR1)>>ADDR_BIT_ACCESS)&1) &&
				I2C2_State!=DATA_R_ACK_STATE && I2C2_State!=DATA_T_ACK_STATE)
		{
			/*Clearing the ADDR flag*/
			I2C_PollClrAddressAck(I2C2);
			/*If the slave was addressed as a transmitter*/
			if((((I2C2->I2C_SR2)>>TRA_BIT_ACCESS)&1))
			{
				/*Changing the global state*/
				I2C2_State=DATA_T_ACK_STATE;
				/*Sending the first data byte*/
				I2C2->I2C_DR=Slave_IT_PdataTransmit[I2C_2][Slave_IT_TransmitIndexs[I2C_2]];
				/*Incrementing the transmission buffer index*/
				Slave_IT_TransmitIndexs[I2C_2]++;
				/*Checking on the transmission buffer index if reached maximum size*/
				if(Slave_IT_TransmitIndexs[I2C_2]==Slave_IT_SizeTransmit[I2C_2])
				{
					/*Re-initilazing the transmission buffer index to enable circular data transfer*/
					Slave_IT_TransmitIndexs[I2C_2]=0;
				}
			}
			/*If the slave was addressed as a receiver*/
			else
			{
				/*Changing the global state*/
				I2C2_State=DATA_R_ACK_STATE;
			}
		}

		/*If slave addressing is detected in another time in case of a repeated start*/
		else if((((I2C2->I2C_SR1)>>ADDR_BIT_ACCESS)&1) &&
				(I2C2_State!=DATA_R_ACK_STATE || I2C2_State!=DATA_T_ACK_STATE))
		{
			/*Clearing the ADDR flag*/
			I2C_PollClrAddressAck(I2C2);
			/*If the slave was addressed as a transmitter*/
			if((((I2C2->I2C_SR2)>>TRA_BIT_ACCESS)&1))
			{
				/*Changing the global state*/
				I2C2_State=DATA_T_ACK_STATE;
				/*Sending the first data byte*/
				I2C2->I2C_DR=Slave_IT_PdataTransmit[I2C_2][Slave_IT_TransmitIndexs[I2C_2]];
				/*Incrementing the transmission buffer index*/
				Slave_IT_TransmitIndexs[I2C_2]++;
				/*Checking on the transmission buffer index if reached maximum size*/
				if(Slave_IT_TransmitIndexs[I2C_2]==Slave_IT_SizeTransmit[I2C_2])
				{
					/*Re-initilazing the transmission buffer index to enable circular data transfer*/
					Slave_IT_TransmitIndexs[I2C_2]=0;
				}
			}
			/*If the slave was addressed as a receiver*/
			else
			{
				/*Changing the global state*/
				I2C2_State=DATA_R_ACK_STATE;
			}
		}

		/*If it was in Reception state*/
		else if(I2C2_State==DATA_R_ACK_STATE)
		{
			/*Receiving the received data in the reception buffer*/
			Slave_IT_PdataReceive[I2C_2][Slave_IT_ReceiveIndexs[I2C_2]]=(uint8_t)I2C2->I2C_DR;
			/*Incrementing the reception buffer index*/
			Slave_IT_ReceiveIndexs[I2C_2]++;
			/*Checking on the reception buffer index if reached maximum size*/
			if(Slave_IT_ReceiveIndexs[I2C_2]==Slave_IT_SizeReceive[I2C_2])
			{
				/*Re-initilazing the reception buffer index to enable circular data transfer*/
				Slave_IT_ReceiveIndexs[I2C_2]=0;
			}
		}

		/*If it was in Transmission state*/
		else if(I2C2_State==DATA_T_ACK_STATE)
		{
			/*Sending the next data byte*/
			I2C2->I2C_DR=Slave_IT_PdataTransmit[I2C_2][Slave_IT_TransmitIndexs[I2C_2]];
			/*Incrementing the transmission buffer index*/
			Slave_IT_TransmitIndexs[I2C_2]++;
			/*Checking on the transmission buffer index if reached maximum size*/
			if(Slave_IT_TransmitIndexs[I2C_2]==Slave_IT_SizeTransmit[I2C_2])
			{
				/*Re-initilazing the transmission buffer index to enable circular data transfer*/
				Slave_IT_TransmitIndexs[I2C_2]=0;
			}
		}
	}



	/*If it is master*/
	else
	{
		/*if you are working at DMA mode and you finished transferring the whole data*/
		if((((I2C2->I2C_SR1)>>BTF_BIT_ACCESS)&1) && DMA_EOT_I2C2_Flag)
		{
			/*Re-initailizing the flag to zero*/
			DMA_EOT_I2C2_Flag=0;
			/*Sending stop bit to close the communication*/
			I2C_Master_StopBit(I2C2);
			/*Making sure that you are now returned to slave*/
			while((((I2C2->I2C_SR2)>>MASTER_SLAVE_BIT)&1));

			/*Disabling the event interrupts to have no further interrupts*/
			I2C_DisableEventInterrupts(I2C2);

			/*Calling the call out function that you can implement at the I2C_cfg.c to choose what to do
			  after finishing transferring through the DMA, you can Re-enable transferring in it my setting
			  a flag in this call-out function and checking on it periodically*/
			DMA_I2C2_CallOut_Func();
		}
	}
}

void I2C2_ER_IRQHandler(void)
{
	/*If it is slave*/
	if(!((I2C2->I2C_SR2>>MASTER_SLAVE_BIT)&1))
	{
		/*If a NACK is received in case of end of transmission from this slave to the master*/
		if(((I2C2->I2C_SR1)>>ACKF_BIT_ACCESS)&1)
		{
			/*Decrementing the transmission buffer index*/
			Slave_IT_TransmitIndexs[I2C_2]--;
			/*Clearing the ACK Failure flag*/
			I2C2->I2C_SR1&=~(1<<ACKF_BIT_ACCESS);
			/*Changing the global state to stop state as it won't detect the stop bit*/
			I2C2_State=STOP_STATE;
			/*Writing to CR1 register to clear the stop bit*/
			I2C2->I2C_CR1=I2C2->I2C_CR1;
		}
	}

	/*If it is master*/
	else
	{
		//master
	}
}





void I2C3_EV_IRQHandler(void)
{
	/*If it is slave*/
	if(!((I2C3->I2C_SR2>>MASTER_SLAVE_BIT)&1))
	{
		/*If a Stop bit is detected*/
		if((((I2C3->I2C_SR1)>>STOPF_BIT_ACCESS)&1))
		{
			/*Changing the global state*/
			I2C3_State=STOP_STATE;
			/*Writing to CR1 register to clear the stop bit*/
			I2C3->I2C_CR1=I2C3->I2C_CR1;
		}

		/*If slave addressing is detected in first time*/
		else if((((I2C3->I2C_SR1)>>ADDR_BIT_ACCESS)&1) &&
				I2C3_State!=DATA_R_ACK_STATE && I2C3_State!=DATA_T_ACK_STATE)
		{
			/*Clearing the ADDR flag*/
			I2C_PollClrAddressAck(I2C3);
			/*If the slave was addressed as a transmitter*/
			if((((I2C3->I2C_SR2)>>TRA_BIT_ACCESS)&1))
			{
				/*Changing the global state*/
				I2C3_State=DATA_T_ACK_STATE;
				/*Sending the first data byte*/
				I2C3->I2C_DR=Slave_IT_PdataTransmit[I2C_3][Slave_IT_TransmitIndexs[I2C_3]];
				/*Incrementing the transmission buffer index*/
				Slave_IT_TransmitIndexs[I2C_3]++;
				/*Checking on the transmission buffer index if reached maximum size*/
				if(Slave_IT_TransmitIndexs[I2C_3]==Slave_IT_SizeTransmit[I2C_3])
				{
					/*Re-initilazing the transmission buffer index to enable circular data transfer*/
					Slave_IT_TransmitIndexs[I2C_3]=0;
				}
			}
			/*If the slave was addressed as a receiver*/
			else
			{
				/*Changing the global state*/
				I2C3_State=DATA_R_ACK_STATE;
			}
		}

		/*If slave addressing is detected in another time in case of a repeated start*/
		else if((((I2C3->I2C_SR1)>>ADDR_BIT_ACCESS)&1) &&
				(I2C3_State!=DATA_R_ACK_STATE || I2C3_State!=DATA_T_ACK_STATE))
		{
			/*Clearing the ADDR flag*/
			I2C_PollClrAddressAck(I2C3);
			/*If the slave was addressed as a transmitter*/
			if((((I2C3->I2C_SR2)>>TRA_BIT_ACCESS)&1))
			{
				/*Changing the global state*/
				I2C3_State=DATA_T_ACK_STATE;
				/*Sending the first data byte*/
				I2C3->I2C_DR=Slave_IT_PdataTransmit[I2C_3][Slave_IT_TransmitIndexs[I2C_3]];
				/*Incrementing the transmission buffer index*/
				Slave_IT_TransmitIndexs[I2C_3]++;
				/*Checking on the transmission buffer index if reached maximum size*/
				if(Slave_IT_TransmitIndexs[I2C_3]==Slave_IT_SizeTransmit[I2C_3])
				{
					/*Re-initilazing the transmission buffer index to enable circular data transfer*/
					Slave_IT_TransmitIndexs[I2C_3]=0;
				}
			}
			/*If the slave was addressed as a receiver*/
			else
			{
				/*Changing the global state*/
				I2C3_State=DATA_R_ACK_STATE;
			}
		}

		/*If it was in Reception state*/
		else if(I2C3_State==DATA_R_ACK_STATE)
		{
			/*Receiving the received data in the reception buffer*/
			Slave_IT_PdataReceive[I2C_3][Slave_IT_ReceiveIndexs[I2C_3]]=(uint8_t)I2C3->I2C_DR;
			/*Incrementing the reception buffer index*/
			Slave_IT_ReceiveIndexs[I2C_3]++;
			/*Checking on the reception buffer index if reached maximum size*/
			if(Slave_IT_ReceiveIndexs[I2C_3]==Slave_IT_SizeReceive[I2C_3])
			{
				/*Re-initilazing the reception buffer index to enable circular data transfer*/
				Slave_IT_ReceiveIndexs[I2C_3]=0;
			}
		}

		/*If it was in Transmission state*/
		else if(I2C3_State==DATA_T_ACK_STATE)
		{
			/*Sending the next data byte*/
			I2C3->I2C_DR=Slave_IT_PdataTransmit[I2C_3][Slave_IT_TransmitIndexs[I2C_3]];
			/*Incrementing the transmission buffer index*/
			Slave_IT_TransmitIndexs[I2C_3]++;
			/*Checking on the transmission buffer index if reached maximum size*/
			if(Slave_IT_TransmitIndexs[I2C_3]==Slave_IT_SizeTransmit[I2C_3])
			{
				/*Re-initilazing the transmission buffer index to enable circular data transfer*/
				Slave_IT_TransmitIndexs[I2C_3]=0;
			}
		}
	}



	/*If it is master*/
	else
	{
		/*if you are working at DMA mode and you finished transferring the whole data*/
		if((((I2C3->I2C_SR1)>>BTF_BIT_ACCESS)&1) && DMA_EOT_I2C3_Flag)
		{
			/*Re-initailizing the flag to zero*/
			DMA_EOT_I2C3_Flag=0;
			/*Sending stop bit to close the communication*/
			I2C_Master_StopBit(I2C3);
			/*Making sure that you are now returned to slave*/
			while((((I2C3->I2C_SR2)>>MASTER_SLAVE_BIT)&1));

			/*Disabling the event interrupts to have no further interrupts*/
			I2C_DisableEventInterrupts(I2C3);

			/*Calling the call out function that you can implement at the I2C_cfg.c to choose what to do
			  after finishing transferring through the DMA, you can Re-enable transferring in it my setting
			  a flag in this call-out function and checking on it periodically*/
			DMA_I2C3_CallOut_Func();
		}
	}
}

void I2C3_ER_IRQHandler(void)
{
	/*If it is slave*/
	if(!((I2C3->I2C_SR2>>MASTER_SLAVE_BIT)&1))
	{
		/*If a NACK is received in case of end of transmission from this slave to the master*/
		if(((I2C3->I2C_SR1)>>ACKF_BIT_ACCESS)&1)
		{
			/*Decrementing the transmission buffer index*/
			Slave_IT_TransmitIndexs[I2C_3]--;
			/*Clearing the ACK Failure flag*/
			I2C3->I2C_SR1&=~(1<<ACKF_BIT_ACCESS);
			/*Changing the global state to stop state as it won't detect the stop bit*/
			I2C3_State=STOP_STATE;
			/*Writing to CR1 register to clear the stop bit*/
			I2C3->I2C_CR1=I2C3->I2C_CR1;
		}
	}

	/*If it is master*/
	else
	{
		//master
	}
}






