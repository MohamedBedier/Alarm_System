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
 * @brief: This is an enum to Configure PLL CLOCK SRC [HSE,HSI]
 */
typedef enum
{
	HSI_SRC_FOR_PLL=0,/**< HSI_SRC_FOR_PLL */
	HSE_SRC_FOR_PLL   /**< HSE_SRC_FOR_PLL */
}PLL_CLK_SRC_t;

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
 * @brief: This is an enum to carry system CLock source
 */
typedef enum
{
	HSE_AS_SYSCLK=0,/**< HSE_AS_SYSCLK */
	HSI_AS_SYSCLK,  /**< HSI_AS_SYSCLK */
	PLL_P,          /**< PLL_P */
	PLL_R           /**< PLL_R */
}SysClk_t;

/**
 * @brief: This is an enum to carry Type of CLock status
 */
typedef enum
{
	CLK_ON=0,/**< Clock is enable */
	CLK_OFF  /**< Clock is disable */
}ClkStatus_t;

/**
 * @brief: This is an enum to Configure CSS Status
 */
typedef enum
{
	CSS_ENABLED=0,/**< CSS_ENABLED */
	CSS_DISABLED  /**< CSS_DISABLED */
}CSS_Sts_t;

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
	PLL_RDY,    /**< Main PLL (PLL) clock ready flag */
	PLL12S_ON,  /**<  PLLI2S enable */
	PLL12S_RDY, /**< PLLI2S clock ready flag */
	PLLSAI_ON,  /**< PLLSAI enable */
	PLLSAI_RDY  /**< PLLSAI clock ready flag */
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
	PPRE1_BIT0=10,   /**< APB Low speed prescaler bit 0 */
	PPRE1_BIT1,      /**< APB Low speed prescaler bit 1 */
	PPRE1_BIT2,      /**< APB Low speed prescaler bit 2 */
	PPRE2_BIT0,      /**< APB high-speed prescaler bit 0 */
	PPRE2_BIT1,      /**< APB high-speed prescaler bit 1 */
	PPRE2_BIT2,      /**< APB high-speed prescaler bit 2 */
	RTCPRE_BIT0,     /**< HSE division factor for RTC clock bit 0 */
	RTCPRE_BIT1,     /**< HSE division factor for RTC clock bit 1 */
	RTCPRE_BIT2,     /**< HSE division factor for RTC clock bit 2 */
	RTCPRE_BIT3,     /**< HSE division factor for RTC clock bit 3 */
	RTCPRE_BIT4,     /**< HSE division factor for RTC clock bit 4 */
	MCO1_BIT0,       /**< Microcontroller clock output 1 bit 0 */
	MCO1_BIT1,       /**< Microcontroller clock output 1 bit 1 */
	MCO1_PRE_BIT0=24,/**< MCO1 prescaler bit 0 */
	MCO1_PRE_BIT1,   /**< MCO1 prescaler bit 1 */
	MCO1_PRE_BIT2,   /**< MCO1 prescaler bit 2 */
	MCO2_PRE_BIT0,   /**< MCO2 prescaler bit 0 */
	MCO2_PRE_BIT1,   /**< MCO2 prescaler bit 1 */
	MCO2_PRE_BIT2,   /**< MCO2 prescaler bit 2 */
	MCO2_BIT0,       /**< Microcontroller clock output 2 bit 0 */
	MCO2_BIT1,       /**< Microcontroller clock output 2 bit 1 */
}RCC_CFGR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_AHB_1_RSTR register
 */
typedef enum
{
	GPIOA_RST=0,/**< IO port A reset */
	GPIOB_RST,  /**< IO port B reset */
	GPIOC_RST,  /**< IO port C reset */
	GPIOD_RST,  /**< IO port D reset */
	GPIOE_RST,  /**< IO port E reset */
	GPIOF_RST,  /**< IO port F reset */
	GPIOG_RST,  /**< IO port G reset */
	GPIOH_RST,  /**< IO port H reset */
	CRC_RST=12, /**< CRC reset */
	DMA1_RST=21,/**< DMA1_reset */
	DMA2_RST,   /**< DMA2 reset */
	OTGHS_RST=29/**< USB OTG HS module reset */
}RCC_AHB_1_RSTR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_AHB_2_RSTR register
 */
typedef enum
{
	DCMI_RST=0, /**< Camera interface reset */
	OTGFS_RST=7 /**< USB OTG FS module reset */
}RCC_AHB_2_RSTR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_AHB_3_RSTR register
 */

typedef enum
{
	FMC_RST=0, /**< Flexible memory controller module reset */
	QSPI_RST   /**< QUADSPI module reset */
}RCC_AHB_3_RSTR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_APB_1_RSTR register
 */
typedef enum
{
	TIM2_RST=0, /**< TIM2 reset */
	TIM3_RST,   /**< TIM3 reset */
	TIM4_RST,   /**< TIM4 reset */
	TIM5_RST,   /**< TIM5 reset */
	TIM6_RST,   /**< TIM6 reset */
	TIM7_RST,   /**< TIM7 reset */
	TIM12_RST,  /**< TIM12 reset */
	TIM13_RST,  /**< TIM13 reset */
	TIM14_RST,  /**< TIM14 reset */
	WWDG_RST=11,/**< Window watchdog reset */
	SPI2_RST=14,/**< SPI2 reset */
	SPI3_RST,   /**< SPI3 reset */
	SPDIFRX_RST,/**< SPDIF-Rx reset */
	UART2_RST,  /**< UART2 reset */
	UART3_RST,  /**< UART3 reset */
	UART4_RST,  /**< UART4 reset */
	UART5_RST,  /**< UART5 reset */
	I2C1_RST,   /**< I2C1 reset */
	I2C2_RST,   /**< I2C2 reset */
	I2C3_RST,   /**< I2C3 reset */
	FMPI2C1_RST,/**< FMPI2C1 reset */
	CAN1_RST,   /**< CAN1 reset */
	CAN2_RST,   /**< CAN2 reset */
	CEC_RST,    /**< CEC reset */
	PWP_RST,    /**< Power interface reset */
	DAC_RST     /**< DAC reset */
}RCC_APB_1_RSTR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_APB_2_RSTR register
 */
typedef enum
{
	TIM1_RST=0,  /**< TIM1 reset */
	TIM8_RST,    /**< TIM8 reset */
	USART1_RST=4,/**< USART1 reset */
	USART6_RST,  /**< USART6 reset */
	ADC_RST=8,   /**< ADC interface reset (common to all ADCs) */
	SDIO_RST=11, /**< SDIO reset */
	SPI1_RST,    /**< SPI1 reset */
	SPI4_RST,    /**< SPI4 reset */
	SYSCFG_RST,  /**< System configuration controller reset */
	TIM9_RST=16, /**< TIM9 reset */
	TIM10_RST,   /**< TIM10 reset */
	TIM11_RST,   /**< TIM11 reset */
	SAI1_RST=22, /**< SAI1 reset */
	SAI2_RST     /**< SAI2 reset */
}RCC_APB_2_RSTR_t;

/**
 * @brief: This is an enum to carry bits' name of RCC_AHB_1_ENR register
 */
typedef enum
{
	GPIOA_EN=0,/**< IO port A enable */
	GPIOB_EN,  /**< IO port B enable */
	GPIOC_EN,  /**< IO port C enable */
	GPIOD_EN,  /**< IO port D enable */
	GPIOE_EN,  /**< IO port E enable */
	GPIOF_EN,  /**< IO port F enable */
	GPIOG_EN,  /**< IO port G enable */
	GPIOH_EN,  /**< IO port H enable */
	CRC_EN=12, /**< CRC enable */
	DMA1_EN=21,/**< DMA1_enable */
	DMA2_EN,   /**< DMA2 enable */
	OTGHS_EN=29/**< USB OTG HS module enable */
}RCC_AHB_1_ENR_t;


/**
 * @brief: This is an enum to carry bits' name of RCC_AHB_2_ENR register
 */
typedef enum
{
	DCMI_EN=0, /**< Camera interface enable*/
	OTGFS_EN=7 /**< USB OTG FS module enable */
}RCC_AHB_2_ENR_t;


/**
 * @brief: This is an enum to carry bits' name of RCC_AHB_3_ENR register
 */
typedef enum
{
	FMC_EN=0, /**< Flexible memory controller module enable */
	QSPI_EN   /**< QUADSPI module enable */
}RCC_AHB_3_ENR_t;


/**
 * @brief: This is an enum to carry bits' name of RCC_APB_1_ENR register
 */
typedef enum
{
	TIM2_EN=0,  /**< TIM2 enable */
	TIM3_EN,    /**< TIM3 enable */
	TIM4_EN,    /**< TIM4 enable */
	TIM5_EN,    /**< TIM5 enable */
	TIM6_EN,    /**< TIM6 enable */
	TIM7_EN,    /**< TIM7 enable */
	TIM12_EN,   /**< TIM12 enable */
	TIM13_EN,   /**< TIM13 enable */
	TIM14_EN,   /**< TIM14 enable */
	WWDG_EN=11, /**< Window watchdog enable */
	SPI2_EN=14, /**< SPI2 enable */
	SPI3_EN,    /**< SPI3 enable */
	SPDIFRX_EN, /**< SPDIF-Rx enable */
	UART2_EN,   /**< UART2 enable */
	UART3_EN,   /**< UART3 enable */
	UART4_EN,   /**< UART4 enable */
	UART5_EN,   /**< UART5 enable */
	I2C1_EN,    /**< I2C1 enable */
	I2C2_EN,    /**< I2C2 enable */
	I2C3_EN,    /**< I2C3 enable */
	FMPI2C1_EN, /**< FMPI2C1 enable */
	CAN1_EN,    /**< CAN1 enable */
	CAN2_EN,    /**< CAN2 enable */
	CEC_EN,     /**< CEC enable */
	PWP_EN,     /**< Power interface enable */
	DAC_EN      /**< DAC enable */
}RCC_APB_1_ENR_t;


/**
 * @brief: This is an enum to carry bits' name of RCC_APB_2_ENR register
 */
typedef enum
{
	TIM1_EN=0,    /**< TIM1 enable */
	TIM8_EN,      /**< TIM8 enable */
	USART1_EN=4,  /**< USART1 enable */
	USART6_EN,    /**< USART6 enable */
	ADC_EN=8,     /**< ADC interface enable (common to all ADCs) */
	SDIO_EN=11,   /**< SDIO enable */
	SPI1_EN,      /**< SPI1 enable */
	SPI4_EN,      /**< SPI4 enable */
	SYSCFG_EN,    /**< System configuration controller enable */
	TIM9_EN=16,   /**< TIM9 enable */
	TIM10_EN,     /**< TIM10 enable */
	TIM11_EN,     /**< TIM11 enable */
	SAI1_EN=22,   /**< SAI1 enable */
	SAI2_EN       /**< SAI2 enable */
}RCC_APB_2_ENR_t;


/**
 * @brief:This is an enum to carry  the BusName
 */
typedef enum
{
	APB1=0,/**< APB1 Bus */
	APB2,  /**< APB2 Bus */
	AHB1,  /**< AHB1 Bus */
	AHB2,  /**< AHB2 Bus */
	AHB3   /**< AHB3 Bus */
}BusName_t;

/**
 * @brief: define struct to carry PLL configuration (PLL_R_Factor,PLL_Q_Factor,PLL_P_Factor,PLL_N_Factor,PLL_M_Factor,PLL_CLK_SRC_t)
 */
typedef struct
{
	PLL_CLK_SRC_t  PLL_CLK_SRC;
	uint8_t  PLL_R_Factor;
	uint8_t  PLL_Q_Factor;
	uint8_t  PLL_P_Factor;
	uint16_t PLL_N_Factor;
	uint16_t PLL_M_Factor;

}PLLCLK_Cfg_t;


/**
 * @brief this function is used to set clock type(HSE,HSI,PLL) and Set its status (on or off)
 * @param[IN] Copy_EnumCLkType : This is an argument which carrying Clock options
 * @param[IN] Copy_EnumCLkStatus : This is an argument which carrying status options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetClkSts(ClkType_t Copy_EnumCLkType ,ClkStatus_t Copy_EnumCLkStatus );

/**
 * @brief this function is used to set system clock type(HSE,HSI,PLL)
 * @param Copy_EnumSysClk[IN] : This is an argument which carrying system Clock options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetSysClk(SysClk_t Copy_EnumSysClk);

/**
 * @brief this function to configure (PLL_M_Factor,PLL_N_Factor,PLL_P_Factor,PLL_CLK_SRC_t)
 * @param Copy_PS_PLLCLK_Cfg[IN] : This is a pointer to struct which carrying PLL Clock configuration options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8PLLCLKConfig(const PLLCLK_Cfg_t* Copy_PS_PLLCLK_Cfg);

/**
 * @brief this function to ENABLE peripheral clk on AHB
 * @param Copy_EnumAHBPeripheral[IN] : This is an argument which carrying AHB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_1_EnableClk(RCC_AHB_1_ENR_t  Copy_EnumAHB1Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on AHB1
 * @param Copy_EnumAHBPeripheral[IN] : This is an argument which carrying AHB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_1_DisableClk(RCC_AHB_1_ENR_t  Copy_EnumAHB1Peripheral);

/**
 * @brief this function to enable peripheral clk on AHB2
 * @param Copy_EnumAHB2Peripheral[IN] : This is an argument which carrying AHB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_2_EnableClk(RCC_AHB_2_ENR_t  Copy_EnumAHB2Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on AHB2
 * @param Copy_EnumAHB2Peripheral[IN] : This is an argument which carrying AHB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_2_DisableClk(RCC_AHB_2_ENR_t  Copy_EnumAHB2Peripheral);

/**
 * @brief this function to enable peripheral clk on AHB3
 * @param Copy_EnumAHB3Peripheral[IN] : This is an argument which carrying AHB 3 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_3_EnableClk(RCC_AHB_3_ENR_t  Copy_EnumAHB3Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on AHB3
 * @param Copy_EnumAHB3Peripheral[IN] : This is an argument which carrying AHB 3 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_3_DisableClk(RCC_AHB_3_ENR_t  Copy_EnumAHB3Peripheral);

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
 * @param Copy_EnumAPB_2_Peripheral[IN] :
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_EnableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral);

/**
 * @brief this function to DISABLE peripheral clk on APB2
 * @param Copy_EnumAPB_2_Peripheral[IN] :
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_DisableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral);

/**
 * @brief this function to enable Or disable CSS Pin
 * @param Copy_EnumCSS_Sts[IN] : this is an enum which carrying state of CSS PIN
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8CSSPinState(CSS_Sts_t Copy_EnumCSS_Sts);


#endif /* RCC_INTERFACE_H_ */
