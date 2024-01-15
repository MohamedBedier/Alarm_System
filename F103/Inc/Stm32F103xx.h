/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: Library                                 **/
/** File Name : Stm32F103xx.h                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef  STM32F103XX_H_
#define  STM32F103XX_H_


/******************************    Various Memory Base Addresses    ******************************/

#define  FLASH_BASE_ADDRESS   0x08000000UL  
#define  SRAM_BASE_ADDRESS    0x20000000UL  
#define  ROM_BASE_ADDRESS     0x1FFFB000UL

/******************************    AHB Peripheral Base Addresses    ******************************/

#define  RCC_BASE_ADDRESS     0x40021000U

/******************************    APB1 Peripheral Base Addresses       ******************************/


/******************************    APB2 Peripheral Base Addresses       ******************************/

#define  GPIOA_BASE_ADDRESS   0x40010800U
#define  GPIOB_BASE_ADDRESS   0x40010C00U
#define  GPIOC_BASE_ADDRESS   0x40011000U
#define  GPIOD_BASE_ADDRESS   0x40011400U
#define  GPIOE_BASE_ADDRESS   0x40011800U
#define  GPIOF_BASE_ADDRESS   0x40011C00U
#define  GPIOG_BASE_ADDRESS   0x40012000U




/******************************    GPIO Register Definitions Structure  ******************************/

typedef  struct
{
	volatile  uint32_t  CR[2];          /*Port configuration register low , High */
	volatile  uint32_t  IDR;            /*GPIO PORT input data Register*/
	volatile  uint32_t  ODR;            /*GPIO PORT Output data Register*/
	volatile  uint32_t  BSRR;           /*GPIO PORT Bit set/Reset Register*/
	volatile  uint32_t  BRR;            /*GPIO PORT Bit Reset Register*/
	volatile  uint32_t  LCKR;           /*GPIO PORT Lock Register*/
	volatile  uint32_t  AFIO_EVCR;      /* Event control register  */
	volatile  uint32_t  AFIO_MAPR;      /* AF remap and debug I/O configuration register */
	volatile  uint32_t  AFIO_EXTICR[4]; /* External interrupt configuration register 1,2,3,4 */	
	volatile  uint32_t  AFIO_MAPR2;     /* AF remap and debug I/O configuration register2  */

}GPIO_RegDef_t;	

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


/******************************    RCC Peripheral Definitions       ******************************/
#define  RCC     (RCC_Reg_t*)RCC_BASE_ADDRESS

/******************************    GPIO Peripheral Definitions       ******************************/

#define   GPIOA     ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define   GPIOB     ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define   GPIOC     ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define   GPIOD     ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define   GPIOE     ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define   GPIOF     ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define   GPIOG     ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)



#endif
