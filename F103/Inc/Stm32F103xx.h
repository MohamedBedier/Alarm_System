

#ifndef  STM32F103XX_H_
#define  STM32F103XX_H_


/******************************    Various Memory Base Addresses    ******************************/

#define  FLASH_BASE_ADDRESS   0x08000000UL  
#define  SRAM_BASE_ADDRESS    0x20000000UL  
#define  ROM_BASE_ADDRESS     0x1FFFB000UL

/******************************    AHB Peripheral Base Addresses    ******************************/

#define  RCC_BASE_ADDRESS      0x40021000U

#define  SYSTICK_BASE_ADDRESS  0xE000E010U

/******************************    APB1 Peripheral Base Addresses       ******************************/

#define  SPI2_BASE_ADDRESS     0x40003800U

/******************************    APB2 Peripheral Base Addresses       ******************************/

#define  GPIOA_BASE_ADDRESS   0x40010800U
#define  GPIOB_BASE_ADDRESS   0x40010C00U
#define  GPIOC_BASE_ADDRESS   0x40011000U
#define  GPIOD_BASE_ADDRESS   0x40011400U
#define  GPIOE_BASE_ADDRESS   0x40011800U
#define  GPIOF_BASE_ADDRESS   0x40011C00U
#define  GPIOG_BASE_ADDRESS   0x40012000U

#define  AFIO_BASE_ADDRESS     0x40010000U

#define  SPI1_BASE_ADDRESS    0x40013000U




/******************************    GPIO Register Definitions Structure  ******************************/

typedef  struct
{
	volatile  uint32_t  CR[2];          /*Port configuration register low , High */
	volatile  uint32_t  IDR;            /*GPIO PORT input data Register*/
	volatile  uint32_t  ODR;            /*GPIO PORT Output data Register*/
	volatile  uint32_t  BSRR;           /*GPIO PORT Bit set/Reset Register*/
	volatile  uint32_t  BRR;            /*GPIO PORT Bit Reset Register*/
	volatile  uint32_t  LCKR;           /*GPIO PORT Lock Register*/
}GPIO_RegDef_t;


/******************************    AFIO Register Definitions Structure  ******************************/

typedef  struct
{
	volatile  uint32_t  AFIO_EVCR;      /* Event control register  */
	volatile  uint32_t  AFIO_MAPR;      /* AF remap and debug I/O configuration register */
	volatile  uint32_t  AFIO_EXTICR[4]; /* External interrupt configuration register 1,2,3,4 */
	volatile  uint32_t  AFIO_MAPR2;     /* AF remap and debug I/O configuration register2  */
}AFIO_RegDef_t;


/******************************    RCC Register Definitions Structure  ******************************/

typedef struct
{
	volatile uint32_t RCC_CR;        /* Clock control register */
	volatile uint32_t RCC_CFGR;      /* Clock configuration register */
	volatile uint32_t RCC_CIR;       /* Clock interrupt register */
	volatile uint32_t RCC_APB2RSTR;  /* APB2 peripheral reset register  */
	volatile uint32_t RCC_APB1RSTR;  /* APB1 peripheral reset register  */
	volatile uint32_t RCC_AHBENR;    /* AHB peripheral clock enable register */
	volatile uint32_t RCC_APB2ENR;   /* APB2 peripheral clock enable register  */
	volatile uint32_t RCC_APB1ENR;   /* APB1 peripheral clock enable register  */
	volatile uint32_t RCC_BDCR;      /* Backup domain control register */
	volatile uint32_t RCC_CSR;       /* Control/status register */
}RCC_Reg_t;


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





/******************************    RCC Peripheral Definitions       ******************************/
#define  RCC        ((RCC_Reg_t*)RCC_BASE_ADDRESS)

/******************************    GPIO Peripheral Definitions       ******************************/
#define   GPIOA     ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define   GPIOB     ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define   GPIOC     ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define   GPIOD     ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define   GPIOE     ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define   GPIOF     ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define   GPIOG     ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)

/******************************    AFIO Peripheral Definitions       ******************************/
#define   AFIO      ((AFIO_RegDef_t*)AFIO_BASE_ADDRESS)

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
