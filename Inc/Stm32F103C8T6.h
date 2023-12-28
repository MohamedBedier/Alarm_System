
#ifndef  STM32F103C8T6_H_
#define  STM32F103C8T6_H_


/************************		APB1 BASE ADRESSES		************************/

#define     SPI2_BASE_ADDRESS        0x40003800U

/************************		APB2 BASE ADRESSES		************************/

#define     SPI1_BASE_ADDRESS        0x40013000U

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




#endif
