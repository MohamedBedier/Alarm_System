
#ifndef  STM32F446xx_H_
#define  STM32F446xx_H_


/************************		AHB1 BASE ADRESSES		************************/

#define  SYSTICK_BASE_ADDRESS  0xE000E010U

#define     I2C1_BASE_ADDRESS        0x40005400U
#define     I2C2_BASE_ADDRESS        0x40005800U
#define     I2C3_BASE_ADDRESS        0x40005C00U


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

/************************		SysTick RESISTER STRUCTURE		************************/

typedef struct
{
	volatile uint32_t SYST_CSR;
	volatile uint32_t SYST_RVR;
	volatile uint32_t SYST_CVR;
	volatile uint32_t SYST_CALIB;
}SysTick_RegDef_t;

/************************		I2C RESISTER STRUCTURE		************************/

typedef struct
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
	volatile uint32_t I2C_FLTR;
}I2C_RegDef_t;





/************************		SysTick Peripheral Definitions		************************/
#define SYSTICK        ((SysTick_RegDef_t*)SYSTICK_BASE_ADDRESS)

/************************		NVIC Peripheral Definitions		************************/
#define NVIC_ISER      ((volatile uint32_t*)0xE000E100)
#define NVIC_ICER      ((volatile uint32_t*)0XE000E180)
#define NVIC_ISPR      ((volatile uint32_t*)0XE000E200)
#define NVIC_ICPR      ((volatile uint32_t*)0XE000E280)
#define NVIC_IABR      ((volatile uint32_t*)0xE000E300)
#define NVIC_IPR       ((volatile uint8_t*) 0xE000E400)
#define NVIC_STIR      ((volatile uint32_t*)0xE000EF00)

/************************		SysCFG Peripheral Definitions		************************/
#define SYSCFG_EXTICR      ((volatile uint32_t*)0x40013808)

/************************		SPI Peripheral Definitions		************************/
#define SPI1          ((SPI_RegDef_t*)SPI1_BASE_ADDRESS)
#define SPI2          ((SPI_RegDef_t*)SPI2_BASE_ADDRESS)
#define SPI3          ((SPI_RegDef_t*)SPI3_BASE_ADDRESS)
#define SPI4          ((SPI_RegDef_t*)SPI4_BASE_ADDRESS)

/************************		I2C Peripheral Definitions		************************/
#define I2C1          ((I2C_RegDef_t*)I2C1_BASE_ADDRESS)
#define I2C2          ((I2C_RegDef_t*)I2C2_BASE_ADDRESS)
#define I2C3          ((I2C_RegDef_t*)I2C3_BASE_ADDRESS)




#endif
