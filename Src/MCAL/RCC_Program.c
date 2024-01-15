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
#include "Stm32F103xx.h"
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
 * @param Copy_EnumClkType[IN] : This is an argument which carrying system Clock options
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetSysClk(ClkType_t Copy_EnumClkType)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* configure system clk */
	switch(Copy_EnumClkType)
	{
	case HSE:CLR_BIT((RCC->RCC_CFGR),SW1);CLR_BIT((RCC->RCC_CFGR),SW0);break;
	case HSI:CLR_BIT((RCC->RCC_CFGR),SW1);SET_BIT((RCC->RCC_CFGR),SW0);break;
	case PLL:SET_BIT((RCC->RCC_CFGR),SW1);CLR_BIT((RCC->RCC_CFGR),SW0);break;
	default:Local_u8ErrorState=NOK;break;/* if the user send invalid options update error state value */
	}
	return Local_u8ErrorState;
}


/**
 * @brief this function to configure PLL SRC and PLLMUL
 * @param Copy_EnumPLLSRC: This is an argument which carrying PLL Src
 * @param Copy_EnumPLLMul: This is an argument which carrying PLL Multiple factor
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8PLLConfig(PLL_CLK_SRC_t Copy_EnumPLLSRC ,PLL_MULTI_Factor_t Copy_EnumPLLMul)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* configure  which CLK entering to PLL */
	switch(Copy_EnumPLLSRC)
	{
	case HSI_SRC_FOR_PLL:CLR_BIT((RCC->RCC_CFGR),PLLSRC);break;
	case HSE_SRC_FOR_PLL:SET_BIT((RCC->RCC_CFGR),PLLSRC);break;
	default:Local_u8ErrorState=NOK;break;/* if the user send invalid options update error state value */
	}

	/* clear only PLLMUL Bits in CFGR  */
	RCC->RCC_CFGR &= RCC_CFGR_PLLMUL_MASK;
	/* set the factor */
	RCC->RCC_CFGR |= Copy_EnumPLLMul;

	return Local_u8ErrorState;
}

/**
 * @brief this function to set input which entering to PLL with divided factor 2 or no divide factor
 * @param Copy_EnumHSE_Division_Fact: This is an argument which carrying HSE CLOCK configuration
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8SetHSEConfig(HSE_InputForPLL_t Copy_EnumHSE_Division_Fact)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* configure which HSE CLK Configuration you want */
	switch(Copy_EnumHSE_Division_Fact)
	{
	case HSE_NOT_DIVIDED: CLR_BIT((RCC->RCC_CFGR),PLLXTPRE);break;
	case HSE_DIVIDED_BY_2:SET_BIT((RCC->RCC_CFGR),PLLXTPRE);break;
	default:Local_u8ErrorState=NOK;break;/* if the user send invalid options update error state value */
	}
	return Local_u8ErrorState;

}

/**
 * @brief this function to ENABLE peripheral clk on AHB
 * @param Copy_EnumAHB_Peripheral[IN] : This is an argument which carrying AHB Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_EnableClk(RCC_AHB_ENR_t  Copy_EnumAHB_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB_Peripheral options to protect your function */
	if((Copy_EnumAHB_Peripheral >= DMA1_EN) && (Copy_EnumAHB_Peripheral <= SDIO_EN))
	{
		/* enable the clk on this peripheral */
		SET_BIT((RCC->RCC_AHBENR),Copy_EnumAHB_Peripheral);
	}else
	{
		/* if the user send invalid options update error state value */
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}

/**
 * @brief this function to DISABLE peripheral clk on AHB
 * @param Copy_EnumAHB_Peripheral[IN] : This is an argument which carrying AHB Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8AHB_DisableClk(RCC_AHB_ENR_t  Copy_EnumAHB_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAHB_Peripheral options to protect your function */
	if((Copy_EnumAHB_Peripheral >= DMA1_EN) && (Copy_EnumAHB_Peripheral <= SDIO_EN))
	{
		/* Disable the clk on this peripheral */
		CLR_BIT((RCC->RCC_AHBENR),Copy_EnumAHB_Peripheral);
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
	if(Copy_EnumAPB_1_Peripheral >= TIM2_EN && Copy_EnumAPB_1_Peripheral <= DAC_EN)
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
	if(Copy_EnumAPB_1_Peripheral >= TIM2_EN && Copy_EnumAPB_1_Peripheral <= DAC_EN)
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
 * @param Copy_EnumAPB_2_Peripheral[IN] : This is an argument which carrying APB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_EnableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAPB_2_Peripheral options to protect your function */
	if(Copy_EnumAPB_2_Peripheral >= AFIO_EN && Copy_EnumAPB_2_Peripheral <= TIM11_EN)
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
 * @param Copy_EnumAPB_2_Peripheral[IN] : This is an argument which carrying APB 2 Peripherals
 * @return Local_u8ErrorState : this is a variable which carrying error state value
 */
uint8_t RCC_u8APB_2_DisableClk(RCC_APB_2_ENR_t  Copy_EnumAPB_2_Peripheral)
{
	/* define variable to carry ErrorState */
	uint8_t Local_u8ErrorState = OK;

	/* check on Copy_EnumAPB_2_Peripheral options to protect your function */
	if(Copy_EnumAPB_2_Peripheral >= AFIO_EN && Copy_EnumAPB_2_Peripheral <= TIM11_EN)
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



