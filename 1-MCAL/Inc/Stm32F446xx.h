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


/******************************    Various Memory Base Addresses    ******************************/

#define  FLASH_BASE_ADDRESS   0x08000000UL  
#define  SRAM_BASE_ADDRESS    0x20000000UL  
#define  ROM_BASE_ADDRESS     0x1FFF0000UL


/******************************    AHB1 Peripheral Base Addresses    ******************************/


/******************************    RCC Peripheral Base Addresses        ******************************/
#define  RCC_BASE_ADDRESS     (RCC_Reg_t*)0x40023800U

/******************************    SYSTICK Peripheral Base Addresses    ******************************/


/******************************    AHB2 Peripheral Base Addresses       ******************************/


/******************************    AHB3 Peripheral Base Addresses       ******************************/


/******************************    APB1 Peripheral Base Addresses       ******************************/

/******************************    APB2 Peripheral Base Addresses       ******************************/


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

/* define a pointer from type of struct [RCC_Reg_t] which carry the base address of RCC
			   Don't forget to cast it to (RCC_Reg_t* ) */

RCC_Reg_t* RCC = RCC_BASE_ADDRESS;

/******************************    GPIO Register Definitions Structure  ******************************/



/******************************    Systick Register Definitions Structure  ******************************/



/******************************    GPIO Peripheral Definitions       ******************************/







#endif
