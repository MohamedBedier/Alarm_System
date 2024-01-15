/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : RCC_Program.c                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "RCC_Private.h"
#include "RCC_Interface.h"


/**
 * @brief this function is used to set clock type(HSE,HSI,PLL) and Set its status (on or off)
 * @param[IN] Copy_EnumCLkType : This is an argument which carrying Clock options
 * @param[IN] Copy_EnumCLkStatus : This is an argument which carrying status options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetClkSts(ClkType_t Copy_EnumCLkType ,ClkStatus_t Copy_EnumCLkStatus )
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* This variable for TimeOutCounter */
	uint32_t Local_u32TimeOutCounter=0u;

	/* check on clock source options */
	if(Copy_EnumCLkType == HSE)
	{
		/* check on clock status */
		if(Copy_EnumCLkStatus == CLK_ON)
		{
			/* enable HSE */
			SET_BIT((RCC->RCC_CR),HSE_ON);

			/* Polling method : waiting until the HSE_RDY or the timeout is passed  */
			while((GET_BIT((RCC->RCC_CR),HSE_RDY) == FLAG_RAISED) && (Local_u32TimeOutCounter <= RCC_TIMEOUT))
			{
				/* increment by 1 */
				Local_u32TimeOutCounter++;
			}

			/* check if loop ended because RCC_TIMEOUT is passed or the flag is raised */
			if(Local_u32TimeOutCounter > RCC_TIMEOUT)
			{
				/* loop is broken because flag isn't raised until timeout is passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}else
			{
				/* loop is broken because flag is raised , and we have another func to enable peripheral */
			}
		}else if (Copy_EnumCLkStatus == CLK_OFF)
		{
			/* disable HSE */
			CLR_BIT((RCC->RCC_CR),HSE_ON);

		}else
		{
			/* if the user send invalid options update error state value */
			Local_u8ErrorState =NOK;
		}
	}else if (Copy_EnumCLkType == HSI)
	{
		/* check on clock status */
		if(Copy_EnumCLkStatus == CLK_ON)
		{
			/* enable HSI */
			SET_BIT((RCC->RCC_CR),HSI_ON);

			/* Polling method : waiting until the HSI_RDY or the timeout is passed  */
			while((GET_BIT((RCC->RCC_CR),HSI_RDY) == FLAG_RAISED) && (Local_u32TimeOutCounter <= RCC_TIMEOUT))
			{
				/* increment by 1 */
				Local_u32TimeOutCounter++;
			}

			/* check if loop ended because RCC_TIMEOUT is passed or the flag is raised */
			if(Local_u32TimeOutCounter > RCC_TIMEOUT)
			{
				/* loop is broken because flag isn't raised until timeout is passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}else
			{
				/* loop is broken because flag is raised , and we have another func to enable peripheral */
			}
		}else if (Copy_EnumCLkStatus == CLK_OFF)
		{
			/* disable HSI */
			CLR_BIT((RCC->RCC_CR),HSI_ON);

		}else
		{
			/* if the user send invalid options update error state value */
			Local_u8ErrorState =NOK;
		}
	}else if (Copy_EnumCLkType == PLL)
	{
		/* check on clock status */
		if(Copy_EnumCLkStatus == CLK_ON)
		{
			/* enable PLL */
			SET_BIT((RCC->RCC_CR),PLL_ON);

			/* Polling method : waiting until the PLL_RDY or the timeout is passed  */
			while((GET_BIT((RCC->RCC_CR),PLL_RDY) == FLAG_RAISED) && (Local_u32TimeOutCounter <= RCC_TIMEOUT))
			{
				/* increment by 1 */
				Local_u32TimeOutCounter++;
			}

			/* check if loop ended because RCC_TIMEOUT is passed or the flag is raised */
			if(Local_u32TimeOutCounter > RCC_TIMEOUT)
			{
				/* loop is broken because flag isn't raised until timeout is passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}else
			{
				/* loop is broken because flag is raised , and we have another func to enable peripheral */
			}
		}else if (Copy_EnumCLkStatus == CLK_OFF)
		{
			/* disable PLL */
			CLR_BIT((RCC->RCC_CR),PLL_ON);

		}else
		{
			/* if the user send invalid options update error state value */
			Local_u8ErrorState =NOK;
		}
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}


/**
 * @brief this function is used to set system clock type(HSE,HSI,PLL)
 * @param Copy_EnumSysClk[IN] : This is an argument which carrying system Clock options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetSysClk(SysClk_t Copy_EnumSysClk)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* configure system clk */
	switch(Copy_EnumSysClk)
	{
	case HSE:CLR_BIT((RCC->RCC_CFGR),SW1);CLR_BIT((RCC->RCC_CFGR),SW0);break;
	case HSI:CLR_BIT((RCC->RCC_CFGR),SW1);SET_BIT((RCC->RCC_CFGR),SW0);break;
	case PLL_P:SET_BIT((RCC->RCC_CFGR),SW1);CLR_BIT((RCC->RCC_CFGR),SW0);break;
	case PLL_R:SET_BIT((RCC->RCC_CFGR),SW1);SET_BIT((RCC->RCC_CFGR),SW0);break;
	default:Local_u8ErrorState=NOK;break;/* if the user send invalid options update error state value */
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to configure (PLL_M_Factor,PLL_N_Factor,PLL_P_Factor,PLL_CLK_SRC_t)
 * @param Copy_PS_PLLCLK_Cfg[IN] : This is a pointer to struct which carrying PLL Clock configuration options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8PLLCLKConfig(const PLLCLK_Cfg_t* Copy_PS_PLLCLK_Cfg)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check if the not equal NULL or not  */
	if(Copy_PS_PLLCLK_Cfg != NULL)
	{
		/* if pointer not equal NULL check on the factor if anyone of them not equal its micro change the Local_u8ErrorState to NOK */
		if(((Copy_PS_PLLCLK_Cfg -> PLL_M_Factor) < PLLM_FACT_MIN) || ((Copy_PS_PLLCLK_Cfg -> PLL_M_Factor) > PLLM_FACT_MAX)
				||((Copy_PS_PLLCLK_Cfg -> PLL_N_Factor) < PLLN_FACT_MIN) ||((Copy_PS_PLLCLK_Cfg -> PLL_N_Factor) > PLLN_FACT_MAX)
				||((Copy_PS_PLLCLK_Cfg -> PLL_P_Factor) != PLLP_DIV2) ||((Copy_PS_PLLCLK_Cfg -> PLL_P_Factor) != PLLP_DIV4)
				||((Copy_PS_PLLCLK_Cfg -> PLL_P_Factor) != PLLP_DIV6)||((Copy_PS_PLLCLK_Cfg -> PLL_P_Factor) != PLLP_DIV8)
				||((Copy_PS_PLLCLK_Cfg -> PLL_R_Factor) < PLLR_DIV2) || ((Copy_PS_PLLCLK_Cfg -> PLL_R_Factor) > PLLR_DIV7)
				||((Copy_PS_PLLCLK_Cfg -> PLL_Q_Factor) < PLLQ_DIV2) || ((Copy_PS_PLLCLK_Cfg -> PLL_Q_Factor) < PLLQ_DIV15))

		{
			Local_u8ErrorState =NOK;/* if the user send invalid options */
		}else
		{
			/* Configure PLL M Factor using pointer from struct Copy_PS_PLLCLK_Cfg */
			(RCC ->RCC_PLLCFGR) &= (~PLLM_MASK);
			(RCC ->RCC_PLLCFGR) |= (Copy_PS_PLLCLK_Cfg -> PLL_M_Factor);

			/* Configure PLL N Factor using pointer from struct Copy_PS_PLLCLK_Cfg */
			(RCC ->RCC_PLLCFGR) &= (~(PLLN_MASK << PLLN_POS_IN_CFGR));
			(RCC ->RCC_PLLCFGR) |= ((Copy_PS_PLLCLK_Cfg -> PLL_N_Factor) << PLLN_POS_IN_CFGR);

			/* Configure PLL P Factor using pointer from struct Copy_PS_PLLCLK_Cfg */
			(RCC ->RCC_PLLCFGR) &= (~(PLLP_MASK << PLLP_POS_IN_CFGR));
			(RCC ->RCC_PLLCFGR) |= ((Copy_PS_PLLCLK_Cfg -> PLL_P_Factor) << PLLP_POS_IN_CFGR);

			/* Configure PLL Clock source if it HSE OR HSI using pointer from struct Copy_PS_PLLCLK_Cfg */
			(RCC ->RCC_PLLCFGR) &= (~(ONE_VALUE<< PLLSRC_POS_IN_CFGR));
			(RCC ->RCC_PLLCFGR) |= ((Copy_PS_PLLCLK_Cfg -> PLL_CLK_SRC) << PLLSRC_POS_IN_CFGR);


			/* Configure PLL Q Factor using pointer from struct Copy_PS_PLLCLK_Cfg */
			(RCC ->RCC_PLLCFGR) &= (~(PLLQ_MASK << PLLQ_POS_IN_CFGR));
			(RCC ->RCC_PLLCFGR) |= ((Copy_PS_PLLCLK_Cfg -> PLL_Q_Factor) << PLLQ_POS_IN_CFGR);

			/* Configure PLL R Factor using pointer from struct Copy_PS_PLLCLK_Cfg */
			(RCC ->RCC_PLLCFGR) &= (~(PLLR_MASK << PLLR_POS_IN_CFGR));
			(RCC ->RCC_PLLCFGR) |= ((Copy_PS_PLLCLK_Cfg -> PLL_R_Factor) << PLLR_POS_IN_CFGR);
		}
	}else
	{
		/* POINTER equal NULL update error state value */
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to ENABLE peripheral clk on AHB
 * @param Copy_EnumAHBPeripheral[IN] : This is an argument which carrying AHB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_1_EnableClk(RCC_AHB_1_ENR_t  Copy_EnumAHB1Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB1Peripheral options to protect your function */
	if(Copy_EnumAHB1Peripheral>= GPIOA_EN && Copy_EnumAHB1Peripheral <= OTGHS_EN )
	{
		/* enable the clk on this peripheral */
		SET_BIT((RCC->RCC_AHB1ENR),Copy_EnumAHB1Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to DISABLE peripheral clk on AHB1
 * @param Copy_EnumAHBPeripheral[IN] : This is an argument which carrying AHB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_1_DisableClk(RCC_AHB_1_ENR_t  Copy_EnumAHB1Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB1Peripheral options to protect your function */
	if(Copy_EnumAHB1Peripheral>= GPIOA_EN && Copy_EnumAHB1Peripheral <= OTGHS_EN )
	{
		/* Disable the clk on this peripheral */
		CLR_BIT((RCC->RCC_AHB1ENR),Copy_EnumAHB1Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to enable peripheral clk on AHB2
 * @param Copy_EnumAHB2Peripheral[IN] : This is an argument which carrying AHB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_2_EnableClk(RCC_AHB_2_ENR_t  Copy_EnumAHB2Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB2Peripheral options to protect your function */
	if(Copy_EnumAHB2Peripheral== DCMI_EN || Copy_EnumAHB2Peripheral == OTGFS_EN )
	{
		/* enable the clk on this peripheral */
		SET_BIT((RCC->RCC_AHB2ENR),Copy_EnumAHB2Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;

}

/**
 * @brief this function to DISABLE peripheral clk on AHB2
 * @param Copy_EnumAHB2Peripheral[IN] : This is an argument which carrying AHB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_2_DisableClk(RCC_AHB_2_ENR_t  Copy_EnumAHB2Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB2Peripheral options to protect your function */
	if(Copy_EnumAHB2Peripheral== DCMI_EN || Copy_EnumAHB2Peripheral == OTGFS_EN )
	{
		/* Disable the clk on this peripheral */
		CLR_BIT((RCC->RCC_AHB2ENR),Copy_EnumAHB2Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to enable peripheral clk on AHB3
 * @param Copy_EnumAHB3Peripheral[IN] : This is an argument which carrying AHB 3 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_3_EnableClk(RCC_AHB_3_ENR_t  Copy_EnumAHB3Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB3Peripheral options to protect your function */
	if(Copy_EnumAHB3Peripheral == FMC_EN || Copy_EnumAHB3Peripheral == QSPI_EN )
	{
		/* enable the clk on this peripheral */
		SET_BIT((RCC->RCC_AHB3ENR),Copy_EnumAHB3Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;

}

/**
 * @brief this function to DISABLE peripheral clk on AHB3
 * @param Copy_EnumAHB3Peripheral[IN] : This is an argument which carrying AHB 3 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_3_DisableClk(RCC_AHB_3_ENR_t  Copy_EnumAHB3Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB3Peripheral options to protect your function */
	if(Copy_EnumAHB3Peripheral == FMC_EN || Copy_EnumAHB3Peripheral == QSPI_EN )
	{
		/* Disable the clk on this peripheral */
		CLR_BIT((RCC->RCC_AHB3ENR),Copy_EnumAHB3Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to ENABLE peripheral clk on APB1
 * @param Copy_EnumAPB_1_Peripheral[IN] : This is an argument which carrying APB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_1_EnableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAPB_1_Peripheral options to protect your function */
	if(Copy_EnumAPB_1_Peripheral >= TIM2_EN && Copy_EnumAPB_1_Peripheral <= DAC_EN )
	{
		/* enable the clk on this peripheral */
		SET_BIT((RCC->RCC_APB1ENR),Copy_EnumAPB_1_Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to DISABLE peripheral clk on APB1
 * @param Copy_EnumAPB_1_Peripheral[IN] : This is an argument which carrying APB 1 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_1_DisableClk(RCC_APB_1_ENR_t  Copy_EnumAPB_1_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAPB_1_Peripheral options to protect your function */
	if(Copy_EnumAPB_1_Peripheral >= TIM2_EN && Copy_EnumAPB_1_Peripheral <= DAC_EN )
	{
		/* Disable the clk on this peripheral */
		CLR_BIT((RCC->RCC_APB1ENR),Copy_EnumAPB_1_Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to ENABLE peripheral clk on APB2
 * @param Copy_EnumAPB_2_Peripheral[IN] :
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_EnableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAPB_2_Peripheral options to protect your function */
	if(Copy_EnumAPB_2_Peripheral>= TIM1_EN && Copy_EnumAPB_2_Peripheral <= SAI2_EN )
	{
		/* enable the clk on this peripheral */
		SET_BIT((RCC->RCC_APB2ENR),Copy_EnumAPB_2_Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to DISABLE peripheral clk on APB2
 * @param Copy_EnumAPB_2_Peripheral[IN] :
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_DisableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAPB_2_Peripheral options to protect your function */
	if(Copy_EnumAPB_2_Peripheral>= TIM1_EN && Copy_EnumAPB_2_Peripheral <= SAI2_EN )
	{
		/* Disable the clk on this peripheral */
		CLR_BIT((RCC->RCC_APB2ENR),Copy_EnumAPB_2_Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to enable Or disable CSS Pin
 * @param Copy_EnumCSS_Sts[IN] : this is an enum which carrying state of CSS PIN
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8CSSPinState(CSS_Sts_t Copy_EnumCSS_Sts)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumCSS_Sts options to protect your function */
	if(Copy_EnumCSS_Sts == CSS_ENABLED)
	{
		/* enable the clk on this Pin */
		SET_BIT((RCC->RCC_CR),CSS_ON);

	}else if(Copy_EnumCSS_Sts == CSS_DISABLED)
	{
		/* Disable the clk on this Pin */
		CLR_BIT((RCC->RCC_CR),CSS_ON);

	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

