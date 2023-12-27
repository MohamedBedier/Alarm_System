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

#define  RCC_BASE_ADDRESS    (RCC_Reg_t*)0x40021000U

/******************************    GPIO Register Definitions Structure  ******************************/


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

/* define a pointer from type of struct [RCC_Reg_t] which carry the base address of RCC
			   Don't forget to cast it to (RCC_Reg_t* ) */

RCC_Reg_t* RCC = RCC_BASE_ADDRESS;

/******************************    APB1 Peripheral Base Addresses       ******************************/

/******************************    APB2 Peripheral Base Addresses       ******************************/


/******************************    GPIO Peripheral Definitions       ******************************/


#endif
