/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: Library                                 **/
/** File Name : Stm32F446xx.h                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef  STM32F446XX_H_
#define  STM32F446XX_H_

/******************************    AHB1 Peripheral Base Addresses    ******************************/

#define  GPIOA_BASE_ADDRESS   0x40020000UL
#define  GPIOB_BASE_ADDRESS   0x40020400UL
#define  GPIOC_BASE_ADDRESS   0x40020800UL
#define  GPIOD_BASE_ADDRESS   0x40020C00UL
#define  GPIOE_BASE_ADDRESS   0x40021000UL
#define  GPIOF_BASE_ADDRESS   0x40021400UL
#define  GPIOG_BASE_ADDRESS   0x40021800UL
#define  GPIOH_BASE_ADDRESS   0x40021C00UL


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

/******************************    GPIO Peripheral Definitions       ******************************/

#define   GPIOA     ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define   GPIOB     ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define   GPIOC     ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define   GPIOD     ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define   GPIOE     ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define   GPIOF     ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define   GPIOG     ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define   GPIOH     ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)

#endif
