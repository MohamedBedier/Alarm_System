/***********************************************************
* @file SCB_Prog
* @Author Abdullah AlsharQawy
* @Brief The main file for SCB peripheral
***********************************************************/
#include <stdint.h>
#include <Stm32F103xx.h>
#include <ErrType.h>
#include <cnfg.h>

#include <SCB_Interface.h>
#include <SCB_prv.h>


/***********************************************************
* @fn SCB_voidInit
* @Brief Function for setting exceptions priorities
* @Param void
* @retval void
***********************************************************/
void SCB_voidInit(void)
{
	/*Taking the SCB_AIRCR value*/
	uint32_t u8SCB_AIRCR=SCB_AIRCR;
	/*Clearing the key value*/
	u8SCB_AIRCR&=~(VECTKEY_MASK<<VECTKEY_ACCESS);
	/*Assigning the Priority Group value that you configure in cnfg,h file*/
	u8SCB_AIRCR&=~(PRIGROUP_MASK<<PRIGROUP_ACCESS);
	/*Re-Assigning the value to SCB_AIRCR*/
	SCB_AIRCR=u8SCB_AIRCR|(VECTKEY<<VECTKEY_ACCESS)|(PRIGROUP_BITS<<PRIGROUP_ACCESS);
}

/***********************************************************
* @fn SCB_voidEnableZeroDivTrap
* @Brief Function for Enable Zero Division Trap
* @Param void
* @retval void
***********************************************************/
void SCB_voidEnableZeroDivTrap(void)
{
	/*Setting the enable bit*/
	SCB_CCR|=(1<<DIV_0_TRP_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidDisableZeroDivTrap
* @Brief Function for Disable Zero Division Trap
* @Param void
* @retval void
***********************************************************/
void SCB_voidDisableZeroDivTrap(void)
{
	/*Clearing the enable bit*/
	SCB_CCR&=~(1<<DIV_0_TRP_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidEnableUnalignTrap
* @Brief Function for Enable unaligned access Trap
* @Param void
* @retval void
***********************************************************/
void SCB_voidEnableUnalignTrap(void)
{
	/*Setting the enable bit*/
	SCB_CCR|=(1<<UNALIGN_TRP_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidDisableUnalignTrap
* @Brief Function for Disable unaligned access
* @Param void
* @retval void
***********************************************************/
void SCB_voidDisableUnalignTrap(void)
{
	/*Clearing the enable bit*/
	SCB_CCR&=~(1<<UNALIGN_TRP_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidSetPriority
* @Brief Function to assign priority to a certain IRQ
* @Param[in] IRQ_Name : The system exception request number, Options at @NSCB_IRQ_t enum
* @Param[in] priority : The system exception priority Options at @Priority_t enum
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t SCB_voidSetPriority(SCB_IRQ_t IRQ_Name, SupGroupPriority_t priority)
{
	ErrorStatus_t ErrorState=UNKNOWN;
	/*Checking on the IRQ_Name value*/
	if(IRQ_Name!=MemManage_IRQ || IRQ_Name!=BusFault_IRQ || IRQ_Name!=UsageFault ||
	   IRQ_Name!=SVC_IRQ || IRQ_Name!=PendSV_IRQ || IRQ_Name!=SysTick_IRQ)
	{
		ErrorState=NOK;
	}
	/*Checking on the priority value*/
	else if(priority>TOTAL_PRIORITIES)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Assigning the priority value to this IRQ priority*/
		SCB_SHPR[IRQ_Name]=priority<<SCB_PRIORITY_ACCESS;
		ErrorState=OK;
	}

	return ErrorState;
}

/***********************************************************
* @fn SCB_voidEnableUsageFault
* @Brief Function for Enable usage fault exception
* @Param void
* @retval void
***********************************************************/
void SCB_voidEnableUsageFault(void)
{
	/*Setting the enable bit*/
	SCB_SHCSR|=(1<<USGFAULTENA_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidDisableUsageFault
* @Brief Function for Disable usage fault exception
* @Param void
* @retval void
***********************************************************/
void SCB_voidDisableUsageFault(void)
{
	/*Clearing the enable bit*/
	SCB_SHCSR&=~(1<<USGFAULTENA_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidEnableBusFault
* @Brief Function for Enable bus fault exception
* @Param void
* @retval void
***********************************************************/
void SCB_voidEnableBusFault(void)
{
	/*Setting the enable bit*/
	SCB_SHCSR|=(1<<BUSFAULTENA_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidDisableBusFault
* @Brief Function for Disable bus fault exception
* @Param void
* @retval void
***********************************************************/
void SCB_voidDisableBusFault(void)
{
	/*Clearing the enable bit*/
	SCB_SHCSR&=~(1<<BUSFAULTENA_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidEnableMemManageFault
* @Brief Function for Enable MemManage fault exception
* @Param void
* @retval void
***********************************************************/
void SCB_voidEnableMemManageFault(void)
{
	/*Setting the enable bit*/
	SCB_SHCSR|=(1<<MEMFAULTENA_BIT_ACCESS);
}

/***********************************************************
* @fn SCB_voidDisableMemManageFault
* @Brief Function for Disable MemManage fault exception
* @Param[in] void
* @retval void
***********************************************************/
void SCB_voidDisableMemManageFault(void)
{
	/*Clearing the enable bit*/
	SCB_SHCSR&=~(1<<MEMFAULTENA_BIT_ACCESS);
}




