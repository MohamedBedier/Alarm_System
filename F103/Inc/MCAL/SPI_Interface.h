/*
 * SPI_Interface.h
 *
 *  Created on: Dec 15, 2023
 *      Author: AlsharQawy
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/*@SPI_t*/
typedef enum
{
	SPI_1=0,
	SPI_2,
}SPI_t;

/*@SPI_DataFormat_t*/
typedef enum
{
	SPI_8_BITS=0,
	SPI_16_BITS,
}SPI_DataFormat_t;

/*@SPI_LSBFirst_t*/
typedef enum
{
	MSB_FIRST=0,
	LSB_FIRST,
}SPI_LSBFirst_t;

/*@SPI_Master_t*/
typedef enum
{
	SPI_SLAVE=0,
	SPI_MASTER,
}SPI_Master_t;

/*@SPI_SW_SlvMng_t*/
typedef enum
{
	SW_SLV_MNG_DISABLE=0,
	SW_SLV_MNG_ENABLE,
}SPI_SW_SlvMng_t;

/*@SPI_SW_NSS_Pin_t*/
typedef enum
{
	SW_NSS_LOW=0,
	SW_NSS_HIGH,
}SPI_SW_NSS_Pin_t;

/*@SPI_Prescaler_t*/
typedef enum
{
	FCLK_2=0,
	FCLK_4,
	FCLK_8,
	FCLK_16,
	FCLK_32,
	FCLK_64,
	FCLK_128,
	FCLK_256,
}SPI_Prescaler_t;


/*@SPI_Circular_t*/
typedef enum
{
	CIRCULAR_ENABLE=0,
	CIRCULAR_DISABLE,
}SPI_Circular_t;


typedef struct
{
	SPI_t SPI;
	SPI_DataFormat_t DataFrame;
	SPI_LSBFirst_t First_LSB;
	SPI_Prescaler_t Prescaler;
	SPI_Master_t Master;
	SPI_SW_SlvMng_t SW_SlvMng;
}SPIConfig_t;



ErrorStatus_t SPI_voidInit(const SPIConfig_t* SPIConfig);
ErrorStatus_t SPI_Enable(SPI_t spi);
ErrorStatus_t SPI_Disable(SPI_t spi);
ErrorStatus_t SPI_SW_NSS_Pin(SPI_t spi, SPI_SW_NSS_Pin_t nssPin);
ErrorStatus_t SPI_DMA_TransmitEnable(SPI_t spi);
ErrorStatus_t SPI_DMA_ReceiveEnable(SPI_t spi);
ErrorStatus_t SPI_SendSync(SPI_t spi, uint16_t data);
ErrorStatus_t SPI_ReceiveSync(SPI_t spi, uint16_t* data);
uint8_t SPI_SendPeriodic(SPI_t spi, uint16_t data);
uint8_t SPI_ReceivePeriodic(SPI_t spi, uint16_t* data);
ErrorStatus_t SPI_TransmitInterruptEnable(SPI_t spi, uint16_t* DataPtr, uint32_t DataSize, SPI_Circular_t Cir);
ErrorStatus_t SPI_TransmitInterruptDisable(SPI_t spi);
ErrorStatus_t SPI_ReceiveInterruptEnable(SPI_t spi, uint16_t* DataPtr, uint32_t DataSize, SPI_Circular_t Cir);
ErrorStatus_t SPI_ReceiveInterruptDisable(SPI_t spi);

#endif /* SPI_INTERFACE_H_ */
