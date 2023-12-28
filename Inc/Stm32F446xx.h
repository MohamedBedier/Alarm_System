
#ifndef  STM32F446xx_H_
#define  STM32F446xx_H_


/************************		APB1 BASE ADRESSES		************************/

#define     SPI2_BASE_ADDRESS        0x40003800U
#define     SPI3_BASE_ADDRESS        0x40003C00U

/************************		APB2 BASE ADRESSES		************************/

#define     SPI1_BASE_ADDRESS        0x40013000U
#define     SPI4_BASE_ADDRESS        0x40013400U

/************************		SPI RESISTER STRUCTURE		************************/

typedef struct
{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
}SPI_RegDef_t;

/************************		SPI Peripheral Definitions		************************/
#define SPI1          ((SPI_RegDef_t*)SPI1_BASE_ADDRESS)
#define SPI2          ((SPI_RegDef_t*)SPI2_BASE_ADDRESS)
#define SPI3          ((SPI_RegDef_t*)SPI3_BASE_ADDRESS)
#define SPI4          ((SPI_RegDef_t*)SPI4_BASE_ADDRESS)






#endif
