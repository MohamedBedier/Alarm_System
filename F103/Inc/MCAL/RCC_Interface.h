/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : RCC_Interface.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/**
 * @brief: This is an enum to Configure System CLOCK Type [HSE,HSI,PLL]
 */
typedef enum
{
	HSE=0,/**< HSE */
	HSI,  /**< HSI */
	PLL   /**< PLL */
}ClkType_t;

/**
 * @brief: This is an enum to carry Type of CLock status
 */
typedef enum
{
	CLK_ON=0,/**< Clock is enable */
	CLK_OFF  /**< Clock is disable */
}ClkStatus_t;


/**
 * @brief: define enum to carry PLL multiplication factors
 */
typedef enum
{
	PLL_INPUT_CLK_X2=0,/**< PLL_INPUT_CLK_X2 */
	PLL_INPUT_CLK_X3,  /**< PLL_INPUT_CLK_X3 */
	PLL_INPUT_CLK_X4,  /**< PLL_INPUT_CLK_X4 */
	PLL_INPUT_CLK_X5,  /**< PLL_INPUT_CLK_X5 */
	PLL_INPUT_CLK_X6,  /**< PLL_INPUT_CLK_X6 */
	PLL_INPUT_CLK_X7,  /**< PLL_INPUT_CLK_X7 */
	PLL_INPUT_CLK_X8,  /**< PLL_INPUT_CLK_X8 */
	PLL_INPUT_CLK_X9,  /**< PLL_INPUT_CLK_X9 */
	PLL_INPUT_CLK_X10, /**< PLL_INPUT_CLK_X10 */
	PLL_INPUT_CLK_X11, /**< PLL_INPUT_CLK_X11 */
	PLL_INPUT_CLK_X12, /**< PLL_INPUT_CLK_X12 */
	PLL_INPUT_CLK_X13, /**< PLL_INPUT_CLK_X13 */
	PLL_INPUT_CLK_X14, /**< PLL_INPUT_CLK_X14 */
	PLL_INPUT_CLK_X15, /**< PLL_INPUT_CLK_X15 */
	PLL_INPUT_CLK_X16, /**< PLL_INPUT_CLK_X16 */

}PLL_MULTI_Factor_t;

/**
 * @brief: define enum to work on Bit 17 PLLXTPRE: HSE divider for PLL entry
 */
typedef enum
{
	HSE_NOT_DIVIDED=0,/**< HSE_NOT_DIVIDED */
	HSE_DIVIDED_BY_2  /**< HSE_DIVIDED_BY_2 */
}HSE_InputForPLL_t;

/**
 * @brief: This is an enum to Configure PLL CLOCK SRC [HSE,HSI]
 */
typedef enum
{
	HSI_SRC_FOR_PLL=0,/**< HSI_SRC_FOR_PLL */
	HSE_SRC_FOR_PLL   /**< HSE_SRC_FOR_PLL */
}PLL_CLK_SRC_t;


/**
 * @brief: This is an enum to configure APB2 high-speed prescaler
 */
typedef enum
{
	APB2_HCLK_NOT_DIVIDED=3,/**< APB2_HCLK_NOT_DIVIDED */
	APB2_HCLK_DIVIDED_BY_2, /**< APB2_HCLK_DIVIDED_BY_2 */
	APB2_HCLK_DIVIDED_BY_4, /**< APB2_HCLK_DIVIDED_BY_4 */
	APB2_HCLK_DIVIDED_BY_8, /**< APB2_HCLK_DIVIDED_BY_8 */
	APB2_HCLK_DIVIDED_BY_16,/**< APB2_HCLK_DIVIDED_BY_16 */
}APB_2_Precaler_t;
/**
 * @brief: This is an enum to configure APB1 high-speed prescaler
 */
typedef enum
{
	APB1_HCLK_NOT_DIVIDED=3,/**< APB1_HCLK_NOT_DIVIDED */
	APB1_HCLK_DIVIDED_BY_2, /**< APB1_HCLK_DIVIDED_BY_2 */
	APB1_HCLK_DIVIDED_BY_4, /**< APB1_HCLK_DIVIDED_BY_4 */
	APB1_HCLK_DIVIDED_BY_8, /**< APB1_HCLK_DIVIDED_BY_8 */
	APB1_HCLK_DIVIDED_BY_16,/**< APB1_HCLK_DIVIDED_BY_16 */
}APB1_Precaler_t;

/**
 * @brief: This is an enum to configure AHB prescaler
 */
typedef enum
{
	SYSCLK_NOT_DIVIDED=7, /**< SYSCLK_NOT_DIVIDED */
	SYSCLK_DIVIDED_BY_2,  /**< SYSCLK_DIVIDED_BY_2 */
	SYSCLK_DIVIDED_BY_4,  /**< SYSCLK_DIVIDED_BY_4 */
	SYSCLK_DIVIDED_BY_8,  /**< SYSCLK_DIVIDED_BY_8 */
	SYSCLK_DIVIDED_BY_16, /**< SYSCLK_DIVIDED_BY_16 */
	SYSCLK_DIVIDED_BY_64, /**< SYSCLK_DIVIDED_BY_64 */
	SYSCLK_DIVIDED_BY_128,/**< SYSCLK_DIVIDED_BY_128 */
	SYSCLK_DIVIDED_BY_256,/**< SYSCLK_DIVIDED_BY_256 */
	SYSCLK_DIVIDED_BY_512 /**< SYSCLK_DIVIDED_BY_512 */
}AHB_Precaler_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_CR register
 */
typedef enum
{
	HSI_ON=0,   /**< Internal high-speed clock enable */
	HSI_RDY,    /**< Internal high-speed clock ready flag */
	HSI_TRIM0=3,/**< Internal high-speed clock trimming bit 0 */
	HSI_TRIM1,  /**< Internal high-speed clock trimming bit 1 */
	HSI_TRIM2,  /**< Internal high-speed clock trimming bit 2 */
	HSI_TRIM3,  /**< Internal high-speed clock trimming bit 3 */
	HSI_TRIM4,  /**< Internal high-speed clock trimming bit 4 */
	HSICAL0,    /**< Internal high-speed clock calibration bit 0 */
	HSICAL1,    /**< Internal high-speed clock calibration bit 1 */
	HSICAL2,    /**< Internal high-speed clock calibration bit 2 */
	HSICAL3,    /**< Internal high-speed clock calibration bit 3 */
	HSICAL4,    /**< Internal high-speed clock calibration bit 4 */
	HSICAL5,    /**< Internal high-speed clock calibration bit 5 */
	HSICAL6,    /**< Internal high-speed clock calibration bit 6 */
	HSICAL7,    /**< Internal high-speed clock calibration bit 7 */
	HSE_ON,     /**< HSE clock enable */
	HSE_RDY,    /**< HSE clock ready flag */
	HSE_BYP,    /**< HSE clock bypass */
	CSS_ON ,    /**< Clock security system enable */
	PLL_ON=24,  /**< Main PLL (PLL) enable */
	PLL_RDY    /**< Main PLL (PLL) clock ready flag */
}RCC_CR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_CFGR register
 */
typedef enum
{
	SW0=0,           /**< System clock switch bit 0 */
	SW1,             /**< System clock switch bit 1  */
	SWS0,            /**< System clock switch status bit 0 */
	SWS1,            /**< System clock switch status bit 1 */
	HPRE0,           /**< AHB prescaler bit 0 */
	HPRE1,           /**< AHB prescaler bit 1 */
	HPRE2,           /**< AHB prescaler bit 2 */
	HPRE3,           /**< AHB prescaler bit 3 */
	PPRE1_BIT0,      /**< APB Low speed prescaler bit 0 */
	PPRE1_BIT1,      /**< APB Low speed prescaler bit 1 */
	PPRE1_BIT2,      /**< APB Low speed prescaler bit 2 */
	PPRE2_BIT0,      /**< APB high-speed prescaler bit 0 */
	PPRE2_BIT1,      /**< APB high-speed prescaler bit 1 */
	PPRE2_BIT2,      /**< APB high-speed prescaler bit 2 */
	ADCPRE0,         /**< ADC prescaler bit 0 */
	ADCPRE1,		 /**< ADC prescaler bit 1 */
	PLLSRC,			 /**< PLL entry clock source */
	PLLXTPRE,		 /**< HSE divider for PLL entry */
	PLLMUL0,		 /**< PLL multiplication factor bit 0 */
	PLLMUL1,		 /**< PLL multiplication factor bit 1 */
	PLLMUL2,		 /**< PLL multiplication factor bit 2 */
	PLLMUL3,		 /**< PLL multiplication factor bit 3 */
	USBPRE,			 /**< USB prescaler */
	MCO_0=24,		 /**< Microcontroller clock output bit 0 */
	MCO_1,			 /**< Microcontroller clock output bit 1 */
	MCO_2 			 /**< Microcontroller clock output bit 2 */
}RCC_CFGR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_APB_2_RSTR register
 */
typedef enum
{
	AFIO_RST=0, /**< Alternate function IO reset */
	IOPA_RST=2, /**< IO port A reset */
	IOPB_RST,   /**< IO port B reset  */
	IOPC_RST,   /**< IO port C reset  */
	IOPD_RST,   /**< IO port D reset  */
	IOPE_RST,   /**< IO port E reset  */
	IOPF_RST,   /**< IO port F reset  */
	IOPG_RST,   /**< IO port G reset  */
	ADC1_RST,   /**< ADC 1 interface reset */
	ADC2_RST,   /**< ADC 2 interface reset */
	TIM1_RST,   /**< TIM1 timer reset */
	SPI1_RST,   /**< SPI1 reset */
	TIM8_RST,   /**< TIM8 timer reset */
	USART1_RST, /**< USART1 reset */
	ADC3_RST,   /**< ADC3 interface reset */
	TIM9_RST=19,/**< TIM9 timer reset */
	TIM10_RST,  /**< TIM10 timer reset */
	TIM11_RST   /**< TIM11 timer reset */
}RCC_APB_2_RSTR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_APB_1_RSTR register
 */
typedef enum
{
	TIM2_RST=0,   /**< TIM2 timer reset*/
	TIM3_RST,     /**< TIM3 timer reset*/
	TIM4_RST,     /**< TIM4 timer reset*/
	TIM5_RST,     /**< TIM5 timer reset*/
	TIM6_RST,     /**< TIM6 timer reset*/
	TIM7_RST,     /**< TIM7 timer reset*/
	TIM12_RST,    /**< TIM12 timer reset */
	TIM13_RST,    /**< TIM13 timer reset */
	TIM14_RST,    /**< TIM14 timer reset */
	WWDG_RST=11,  /**< Window watchdog reset */
	SPI2_RST=14,  /**< SPI2 reset */
	SPI3_RST,     /**< SPI3 reset */
	USART2_RST=17,/**< USART2 reset */
	USART3_RST,   /**< USART3 reset */
	USART4_RST,   /**< USART4 reset */
	USART5_RST,   /**< USART5 reset */
	I2C1_RST,     /**< I2C1 reset */
	I2C2_RST,     /**< I2C1 reset */
	USB_RST,      /**< USB reset */
	CAN_RST,      /**< CAN reset */
	BKP_RST=27,   /**< Backup interface reset */
	PWR_RST,      /**< Power interface reset */
	DAC_RST       /**< DAC interface reset */
}RCC_APB_1_RSTR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_AHB_ENR register
 */
typedef enum
{
	DMA1_EN=0, /**< DMA1 clock enable */
	DMA2_EN,   /**< DMA2 clock enable */
	SRAM_EN,   /**< SRAM interface clock enable */
	FLITF_EN=4,/**< FLITF clock enable */
	CRC_EN=6,  /**< CRC clock enable */
	FSMC_EN=8, /**< FSMC clock enable */
	SDIO_EN=10 /**< SDIO clock enable */
}RCC_AHB_ENR_t;


/**
 * @brief: This is an enum to carry bits' name of RCC_APB_2_ENR register
 */
typedef enum
{
	AFIO_EN=0,  /**< Alternate function IO enable */
	IOPA_EN=2,  /**< IO port A enable */
	IOPB_EN,    /**< IO port B enable  */
	IOPC_EN,    /**< IO port C enable  */
	IOPD_EN,    /**< IO port D enable  */
	IOPE_EN,    /**< IO port E enable  */
	IOPF_EN,    /**< IO port F enable  */
	IOPG_EN,    /**< IO port G enable  */
	ADC1_EN,    /**< ADC 1 interface enable */
	ADC2_EN,    /**< ADC 2 interface enable */
	TIM1_EN,    /**< TIM1 timer enable */
	SPI1_EN,    /**< SPI1 enable */
	TIM8_EN,    /**< TIM8 timer enable */
	USART1_EN,  /**< USART1 enable */
	ADC3_EN,    /**< ADC3 interface enable */
	TIM9_EN=19, /**< TIM9 timer enable */
	TIM10_EN,   /**< TIM10 timer enable */
	TIM11_EN    /**< TIM11 timer enable */
}RCC_APB_2_ENR_t;


/**
 * @brief: This is an enum to carry bits' name of RCC_APB_1_ENR register
 */
typedef enum
{
	TIM2_EN=0,    /**< TIM2 timer enable*/
	TIM3_EN,      /**< TIM3 timer enable*/
	TIM4_EN,      /**< TIM4 timer enable*/
	TIM5_EN,      /**< TIM5 timer enable*/
	TIM6_EN,      /**< TIM6 timer enable*/
	TIM7_EN,      /**< TIM7 timer enable*/
	TIM12_EN,     /**< TIM12 timer enable */
	TIM13_EN,     /**< TIM13 timer enable */
	TIM14_EN,     /**< TIM14 timer enable */
	WWDG_EN=11,   /**< Window watchdog enable */
	SPI2_EN=14,   /**< SPI2 enable */
	SPI3_EN,      /**< SPI3 enable */
	USART2_EN=17, /**< USART2 enable */
	USART3_EN,    /**< USART3 enable */
	USART4_EN,    /**< USART4 enable */
	USART5_EN,    /**< USART5 enable */
	I2C1_EN,      /**< I2C1 enable */
	I2C2_EN,      /**< I2C1 enable */
	USB_EN,       /**< USB enable */
	CAN_EN,       /**< CAN enable */
	BKP_EN=27,    /**< Backup interface enable */
	PWR_EN,       /**< Power interface enable */
	DAC_EN        /**< DAC interface enable */
}RCC_APB_1_ENR_t;

/**
 * @brief:This is an enum to carry  the BusName
 */
typedef enum
{
	APB1=0,/**< APB1 */
	APB2,  /**< APB2 */
	AHB    /**< AHB */
}BusName_t;


/**
 * @brief this function is used to set clock type(HSE,HSI,PLL) and Set its status (on or off)
 * @param[IN] Copy_EnumCLkType : This is an argument which carrying Clock options
 * @param[IN] Copy_EnumCLkStatus : This is an argument which carrying status options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetClkSts(ClkType_t Copy_EnumCLkType ,ClkStatus_t Copy_EnumCLkStatus );

/**
 * @brief this function is used to set system clock type(HSE,HSI,PLL)
 * @param Copy_EnumClkType[IN] : This is an argument which carrying system Clock options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetSysClk(ClkType_t Copy_EnumClkType);

/**
 * @brief this function to configure PLL SRC and PLLMUL
 * @param Copy_EnumPLLSRC: This is an argument which carrying PLL Src
 * @param Copy_EnumPLLMul: This is an argument which carrying PLL Multiple factor
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8PLLConfig(PLL_CLK_SRC_t Copy_EnumPLLSRC ,PLL_MULTI_Factor_t Copy_EnumPLLMul);

/**
 * @brief this function to set input which entering to PLL with divided factor 2 or no divide factor
 * @param Copy_EnumHSE_Division_Fact: This is an argument which carrying HSE CLOCK configuration
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetHSEConfig(HSE_InputForPLL_t Copy_EnumHSE_Division_Fact);

/**
 * @brief this function to ENABLE peripheral clk on AHB
 * @param Copy_EnumAHB_Peripheral[IN] : This is an argument which carrying AHB Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_EnableClk(RCC_AHB_ENR_t  Copy_EnumAHB_Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on AHB
 * @param Copy_EnumAHB_Peripheral[IN] : This is an argument which carrying AHB Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_DisableClk(RCC_AHB_ENR_t  Copy_EnumAHB_Peripheral);

/**
 * @brief this function to ENABLE peripheral clk on APB1
 * @param Copy_EnumAPB_1_Peripheral[IN] : This is an argument which carrying APB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_1_EnableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on APB1
 * @param Copy_EnumAPB_1_Peripheral[IN] : This is an argument which carrying APB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_1_DisableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral);

/**
 * @brief this function to ENABLE peripheral clk on APB2
 * @param Copy_EnumAPB_2_Peripheral[IN] : This is an argument which carrying APB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_EnableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on APB2
 * @param Copy_EnumAPB_2_Peripheral[IN] : This is an argument which carrying APB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_DisableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral);

#endif /* RCC_INTERFACE_H_ */
