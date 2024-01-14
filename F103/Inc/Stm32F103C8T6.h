
#ifndef  STM32F103C8T6_H_
#define  STM32F103C8T6_H_


/************************		AHB BASE ADRESSES		************************/

#define  SYSTICK_BASE_ADDRESS  0xE000E010U

/************************		APB1 BASE ADRESSES		************************/

#define     SPI2_BASE_ADDRESS        0x40003800U

/************************		APB2 BASE ADRESSES		************************/

#define     SPI1_BASE_ADDRESS        0x40013000U



/************************		SysTick RESISTER STRUCTURE		************************/

typedef struct
{
	volatile uint32_t SYST_CSR;
	volatile uint32_t SYST_RVR;
	volatile uint32_t SYST_CVR;
	volatile uint32_t SYST_CALIB;
}SysTick_RegDef_t;

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

/************************		SPI Peripheral Definitions		************************/
#define SPI1          ((SPI_RegDef_t*)SPI1_BASE_ADDRESS)
#define SPI2          ((SPI_RegDef_t*)SPI2_BASE_ADDRESS)

/************************		SCB Peripheral Definitions		************************/
#define SCB_ACTLR      (*(volatile uint32_t*)0xE000E008)
#define SCB_CPUID      (*(volatile uint32_t*)0xE000ED00)
#define SCB_ICSR       (*(volatile uint32_t*)0xE000ED04)
#define SCB_VTOR       (*(volatile uint32_t*)0xE000ED08)
#define SCB_AIRCR      (*(volatile uint32_t*)0xE000ED0C)
#define SCB_SCR        (*(volatile uint32_t*)0xE000ED10)
#define SCB_CCR        (*(volatile uint32_t*)0xE000ED14)
#define SCB_SHPR       ((volatile uint8_t*)0xE000ED18)
#define SCB_SHCSR      (*(volatile uint32_t*)0xE000ED24)
#define SCB_CFSR       (*(volatile uint32_t*)0xE000ED28)
#define SCB_MMSR       (*(volatile uint32_t*)0xE000ED28)
#define SCB_BFSR       (*(volatile uint32_t*)0xE000ED29)
#define SCB_UFSR       (*(volatile uint32_t*)0xE000ED2A)
#define SCB_HFSR       (*(volatile uint32_t*)0xE000ED2C)
#define SCB_MMAR       (*(volatile uint32_t*)0xE000ED34)
#define SCB_BFAR       (*(volatile uint32_t*)0xE000ED38)
#define SCB_AFSR       (*(volatile uint32_t*)0xE000ED3C)

/************************		EXTI Peripheral Definitions		************************/
#define EXTI_IMR      (*(volatile uint32_t*)0x40010400)
#define EXTI_EMR      (*(volatile uint32_t*)0x40010404)
#define EXTI_RTSR     (*(volatile uint32_t*)0x40010408)
#define EXTI_FTSR     (*(volatile uint32_t*)0x4001040C)
#define EXTI_SWIER    (*(volatile uint32_t*)0x40010410)
#define EXTI_PR       (*(volatile uint32_t*)0x40010414)
#endif
