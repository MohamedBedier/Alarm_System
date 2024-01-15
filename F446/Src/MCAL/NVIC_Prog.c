/***********************************************************
* @file NVIC_Prog
* @Author Abdullah AlsharQawy
* @Brief The main file for The nested vectored interrupt controller "NVIC"
***********************************************************/

#include <stdint.h>
#include <Stm32F446xx.h>
#include <ErrType.h>
#include <cnfg.h>

#include <NVIC_Interface.h>
#include <NVIC_prv.h>



/***********************************************************
* @fn NVIC_EnableInterrupt
* @Brief Enabling interrupt for a certain IRQ
* @Param[in] IRQ_Name : The interrupt request number, Options at @NVIC_IRQ_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t NVIC_EnableInterrupt(NVIC_IRQ_t IRQ_Name)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the IRQ value*/
	if(IRQ_Name>=TOTAL_IRQS)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		uint8_t RegNum, BitNum;
		/*Calculating the register number of the IRQ enable bit*/
		RegNum=IRQ_Name/NVIC_REGNUM_ASCCESS;
		/*Calculating the bit number of the IRQ enable bit*/
		BitNum=IRQ_Name%NVIC_BITNUM_ASCCESS;

		/*Setting the interrupt set bit to enable the interrupt*/
		NVIC_ISER[RegNum]=(1<<BitNum);

		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn NVIC_DisableInterrupt
* @Brief Disabling interrupt for a certain IRQ
* @Param[in] IRQ_Name : The interrupt request number, Options at @NVIC_IRQ_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t NVIC_DisableInterrupt(NVIC_IRQ_t IRQ_Name)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the IRQ value*/
	if(IRQ_Name>=TOTAL_IRQS)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		uint8_t RegNum, BitNum;
		/*Calculating the register number of the IRQ disable bit*/
		RegNum=IRQ_Name/NVIC_REGNUM_ASCCESS;
		/*Calculating the bit number of the IRQ disable bit*/
		BitNum=IRQ_Name%NVIC_BITNUM_ASCCESS;

		/*Setting the interrupt clear bit to disable the interrupt*/
		NVIC_ICER[RegNum]=(NVIC_BIT_ASCCESS<<BitNum);

		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn NVIC_SetPenddingFlag
* @Brief Setting the pending flag for a certain IRQ
* @Param[in] IRQ_Name : The interrupt request number, Options at @NVIC_IRQ_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t NVIC_SetPenddingFlag(NVIC_IRQ_t IRQ_Name)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the IRQ value*/
	if(IRQ_Name>=TOTAL_IRQS)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		uint8_t RegNum, BitNum;
		/*Calculating the register number of the IRQ pending enable bit*/
		RegNum=IRQ_Name/NVIC_REGNUM_ASCCESS;
		/*Calculating the bit number of the IRQ pending enable bit*/
		BitNum=IRQ_Name%NVIC_BITNUM_ASCCESS;

		/*Setting the pending flag set bit to set the pending flag*/
		NVIC_ISPR[RegNum]=(NVIC_BIT_ASCCESS<<BitNum);

		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn NVIC_ClearPenddingFlag
* @Brief Clearing the pending flag for a certain IRQ
* @Param[in] IRQ_Name : The interrupt request number, Options at @NVIC_IRQ_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t NVIC_ClearPenddingFlag(NVIC_IRQ_t IRQ_Name)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the IRQ value*/
	if(IRQ_Name>=TOTAL_IRQS)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		uint8_t RegNum, BitNum;
		/*Calculating the register number of the IRQ pending disable bit*/
		RegNum=IRQ_Name/NVIC_REGNUM_ASCCESS;
		/*Calculating the bit number of the IRQ pending disable bit*/
		BitNum=IRQ_Name%NVIC_BITNUM_ASCCESS;

		/*Setting the pending flag clear bit to clear the pending flag*/
		NVIC_ICPR[RegNum]=(NVIC_BIT_ASCCESS<<BitNum);

		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn NVIC_GetActiveFlag
* @Brief Reading the acrive flag for a certain IRQ
* @Param[in] IRQ_Name : The interrupt request number, Options at @NVIC_IRQ_t enum
* @retval ActiveInterrrupt_t : Interrupt status, Options at @ActiveInterrrupt_t enum
***********************************************************/
ActiveInterrrupt_t NVIC_GetActiveFlag(NVIC_IRQ_t IRQ_Name)
{
	uint8_t RegNum, BitNum;
	/*Calculating the register number of the IRQ active flag bit*/
	RegNum=IRQ_Name/NVIC_REGNUM_ASCCESS;
	/*Calculating the bit number of the IRQ active flag bit*/
	BitNum=IRQ_Name%NVIC_BITNUM_ASCCESS;

	/*Reading and returning the IRQ active flag status*/
	return ((NVIC_IABR[RegNum]>>BitNum)&NVIC_BIT_ASCCESS);
}

/***********************************************************
* @fn NVIC_voidSetPriority
* @Brief Setting the priority of a certain IRQ
* @Param[in] IRQ_Name : The interrupt request number, Options at @NVIC_IRQ_t enum
* @Param[in] priority : The interrupt priority Options at @Priority_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t NVIC_voidSetPriority(NVIC_IRQ_t IRQ_Name, Priority_t priority)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the IRQ value*/
	if(IRQ_Name>=TOTAL_IRQS || priority>TOTAL_PRIORITIES)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Setting IRQ Priority depending on the configuration in cnfg file*/
		NVIC_IPR[IRQ_Name]=priority<<NVIC_PRIORITY_ACCESS;

		ErrorState=OK;
	}

	return ErrorState;
}







