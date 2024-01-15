
#ifndef  STM32F446XX_H_
#define  STM32F446XX_H_




/******************************    Various Memory Base Addresses    ******************************/

#define  FLASH_BASE_ADDRESS         0x08000000UL  
#define  SRAM_BASE_ADDRESS          0x20000000UL  
#define  ROM_BASE_ADDRESS           0x1FFF0000UL


/******************************    AHB1 Peripheral Base Addresses       ******************************/

#define  USART2_BASE_ADDRESS        0x40004400UL
#define  USART3_BASE_ADDRESS        0x40004800UL
#define  UART4_BASE_ADDRESS         0x40004C00UL
#define  UART5_BASE_ADDRESS         0x40005000UL

#define  SCB_BASE_ADDRESS           0xE000ED00UL

#define  GPIOA_BASE_ADDRESS         0x40020000UL
#define  GPIOB_BASE_ADDRESS         0x40020400UL
#define  GPIOC_BASE_ADDRESS         0x40020800UL
#define  GPIOD_BASE_ADDRESS         0x40020C00UL
#define  GPIOE_BASE_ADDRESS         0x40021000UL
#define  GPIOF_BASE_ADDRESS         0x40021400UL
#define  GPIOG_BASE_ADDRESS         0x40021800UL
#define  GPIOH_BASE_ADDRESS         0x40021C00UL

#define  RCC_BASE_ADDRESS           0x40023800U

#define  DMA1_BASE_ADDRESS          0x40026000UL
#define  DMA2_BASE_ADDRESS          0x40026400UL

#define  SYSTICK_BASE_ADDRESS       0xE000E010U

#define  I2C1_BASE_ADDRESS          0x40005400U
#define  I2C2_BASE_ADDRESS          0x40005800U
#define  I2C3_BASE_ADDRESS          0x40005C00U

/************************		APB1 BASE ADRESSES		************************/

#define   SPI2_BASE_ADDRESS         0x40003800U
#define   SPI3_BASE_ADDRESS         0x40003C00U

/******************************    APB2 Peripheral Base Addresses       ******************************/

#define   USART1_BASE_ADDRESS       0x40011000UL
#define   USART6_BASE_ADDRESS       0x40010400UL

#define   SPI1_BASE_ADDRESS         0x40013000U
#define   SPI4_BASE_ADDRESS         0x40013400U


/******************************    GPIO Register Definitions Structure  ******************************/

typedef  struct
{
	volatile  uint32_t  MODER;            /*GPIO PORT Mode Register*/
	volatile  uint32_t  OTYPER;           /*GPIO PORT Output Type Register*/
	volatile  uint32_t  OSPEEDR;          /*GPIO PORT Output speed Register*/
	volatile  uint32_t  PUPDR;            /*GPIO PORT Pull up/down Register*/
	volatile  uint32_t  IDR;              /*GPIO PORT input data Register*/
	volatile  uint32_t  ODR;              /*GPIO PORT Output data Register*/
	volatile  uint32_t  BSRR;             /*GPIO PORT Bit set/Reset Register*/
	volatile  uint32_t  LCKR;             /*GPIO PORT Lock Register*/
	volatile  uint32_t  AFR[2];           /*GPIO PORT Alternate function Register*/

}GPIO_RegDef_t;

/******************************    USART Register Definitions   ******************************/
typedef struct
{
	volatile uint32_t  USART_SR;     /* Status register */
	volatile uint32_t  USART_DR;     /* Data register */
	volatile uint32_t  USART_BRR;    /* Baud rate register  */
	volatile uint32_t  USART_CR1;  /* Control register 1 */
	volatile uint32_t  USART_CR2;  /* Control register 2 */
	volatile uint32_t  USART_CR3;  /* Control register 3 */
	volatile uint32_t  USART_GTPR;   /* Guard time and prescaler register */
}USART_RegDef_t;

/******************************    SCB Register Definitions   ******************************/
typedef struct
{
	volatile  uint32_t   CPUID;
	volatile  uint32_t   ICSR;
	volatile  uint32_t   VTOR;
	volatile  uint32_t   AIRCR;
	volatile  uint32_t   SCR;
	volatile  uint32_t   CCR;
	volatile  uint32_t   SHPR1;
	volatile  uint32_t   SHPR2;
	volatile  uint32_t   SHPR3;
	volatile  uint32_t   SHCSR;
	volatile  uint32_t   CFSR;
	volatile  uint32_t   HFSR;
	volatile  uint32_t   MMAR;
	volatile  uint32_t   BFAR;
	volatile  uint32_t   AFSR;
}SCB_Reg_t;

/******************************    RCC Register Definitions Structure  ******************************/
typedef struct
{
	volatile uint32_t RCC_CR;           /* RCC Clock control register */
	volatile uint32_t RCC_PLLCFGR;      /* RCC PLL configuration register */
	volatile uint32_t RCC_CFGR;         /* RCC clock configuration register  */
	volatile uint32_t RCC_CIR;          /* RCC Clock interrupt register */
	volatile uint32_t RCC_AHB1RSTR;     /* RCC AHB1 peripheral reset register   */
	volatile uint32_t RCC_AHB2RSTR;     /* RCC AHB2 peripheral reset register   */
	volatile uint32_t RCC_AHB3RSTR;     /* RCC AHB3 peripheral reset register   */
	volatile uint32_t Reserved;         /* Reserved */
	volatile uint32_t RCC_APB1RSTR;     /* RCC APB1 peripheral reset register  */
	volatile uint32_t RCC_APB2RSTR;     /* RCC APB2 peripheral reset register */
	volatile uint32_t Reserved1[2];         /* Reserved */
	volatile uint32_t RCC_AHB1ENR;      /* RCC AHB1 peripheral clock enable register  */
	volatile uint32_t RCC_AHB2ENR;      /* RCC AHB2 peripheral clock enable register */
	volatile uint32_t RCC_AHB3ENR;      /* RCC AHB3 peripheral clock enable register  */
	volatile uint32_t Reserved2;         /* Reserved  */
	volatile uint32_t RCC_APB1ENR;      /* RCC APB1 peripheral clock enable register  */
	volatile uint32_t RCC_APB2ENR;      /* RCC APB2 peripheral clock enable register */
	volatile uint32_t Reserved3[2];         /* Reserved  */
	volatile uint32_t RCC_AHB1LPENR;    /* RCC AHB1 peripheral clock enable in low power mode register */
	volatile uint32_t RCC_AHB2LPENR;    /* RCC AHB2 peripheral clock enable in low power mode register */
	volatile uint32_t RCC_AHB3LPENR;    /* RCC AHB3 peripheral clock enable in low power mode register */
	volatile uint32_t Reserved4;         /* Reserved */
	volatile uint32_t RCC_APB1LPENR;    /* RCC APB1 peripheral clock enable in low power mode register */
	volatile uint32_t RCC_APB2LPENR;    /* RCC APB2 peripheral clock enable in low power mode register  */
	volatile uint32_t Reserved5[2];         /* Reserved */
	volatile uint32_t RCC_BDCR;         /* RCC Backup domain control register  */
	volatile uint32_t RCC_CSR;          /* RCC clock control _ status register */
	volatile uint32_t Reserved6[2];         /* Reserved */
	volatile uint32_t RCC_SSCGR;        /* RCC spread spectrum clock generation register  */
	volatile uint32_t RCC_PLL12SCFGR;   /* RCC PLLI2S configuration register */
	volatile uint32_t RCC_PLLSAICFGR;   /* RCC PLL configuration register  */
	volatile uint32_t RCC_DCKCFGR;      /* RCC dedicated clock configuration register */
	volatile uint32_t RCC_CKGATENR;     /* RCC clocks gated enable register */
	volatile uint32_t RCC_DCKCFGR2;     /* RCC dedicated clocks configuration register 2  */
}RCC_Reg_t;

******************************    DMA Register Definitions   ******************************/

typedef struct
{
	volatile uint32_t DMA_SxCR;    /* DMA stream x configuration register */
	volatile uint32_t DMA_SxNDTR;  /* DMA stream x number of data register */
	volatile uint32_t DMA_SxPAR;   /* DMA stream x peripheral address register */
	volatile uint32_t DMA_SxM0AR;  /* DMA stream x memory 0 address register */
	volatile uint32_t DMA_SxM1AR;  /* DMA stream x memory 1 address register */
	volatile uint32_t DMA_SxFCR;   /* DMA stream x FIFO control register */
}DMA_Stream_RegDef_t;


typedef struct
{
	volatile uint32_t   DMA_ISR[2];      /* DMA low,high interrupt status register */
	volatile uint32_t   DMA_IFCR[2];     /* DMA low,High interrupt flag clear register */
	volatile DMA_Stream_RegDef_t  DMA_Stream[8]; /* array from DMA_Stream_RegDef_t which carrying DMA Stream from 0 to 7 Registers */
}DMA_RegDef_t;


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



/******************************    GPIO Peripheral Definitions       ******************************/

#define   GPIOA     ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define   GPIOB     ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define   GPIOC     ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define   GPIOD     ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define   GPIOE     ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define   GPIOF     ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define   GPIOG     ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define   GPIOH     ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)


/******************* USART structure pointer **********************/

#define    USART1	((USART_RegDef_t*)(USART1_BASE_ADDRESS))
#define    USART2	((USART_RegDef_t*)(USART2_BASE_ADDRESS))
#define    USART3	((USART_RegDef_t*)(USART3_BASE_ADDRESS))
#define    UART4	((USART_RegDef_t*)(UART4_BASE_ADDRESS))
#define    UART5	((USART_RegDef_t*)(UART5_BASE_ADDRESS))
#define    USART6	((USART_RegDef_t*)(USART6_BASE_ADDRESS))

/******************************    SCB structure pointer **********************/
#define    SCB		((SCB_Reg_t *)(SCB_BASE_ADDRESS))

/******************************    RCC structure pointer **********************/
#define    RCC      (RCC_Reg_t*)RCC_BASE_ADDRESS

/******************* DMAs structure pointer **********************/
#define    DMA1		((DMA_RegDef_t*)(DMA1_BASE_ADDRESS))
#define    DMA2		((DMA_RegDef_t*)(DMA2_BASE_ADDRESS))

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
