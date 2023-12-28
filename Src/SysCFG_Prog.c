/***********************************************************
* @file SysCFG_Prog
* @Author Abdullah AlsharQawy
* @Brief The main file for System configuration peripheral
***********************************************************/
#include <stdint.h>
#include <Stm32F446xx.h>
#include <ErrType.h>

#include <SysCFG_Interface.h>
#include <SysCFG_prv.h>


/***********************************************************
* @fn SysCFG_voidSetEXTI_Port
* @Brief Function for selecting which port to connect to a certain line of external interrupt
* @Param[in] line : The line of the external interrupt, Options at @EXTI_line_t enum
* @Param[in] port : The port of the external interrupt, Options at @SysCFGPort_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SysCFG_voidSetEXTI_Port(EXTI_line_t line, SysCFGPort_t port)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	if(line>=SYSCFG_TOTAL_LINES || port>=SYSCFG_TOTAL_PORTS)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Selecting the port to be connect to a certain line of external interrupt*/
		SYSCFG_EXTICR[line/SCFG_OF_LINES] &= ~(SCFG_BIT_MASK<<((line%SCFG_OF_LINES)*SCFG_NUM_OF_BITS));
		SYSCFG_EXTICR[line/SCFG_OF_LINES] |=  (port<<((line%SCFG_OF_LINES)*SCFG_NUM_OF_BITS));

		ErrorState=OK;
	}

	return ErrorState;
}
