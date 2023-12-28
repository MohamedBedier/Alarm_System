

#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_


#include <cnfg.h>

/*@SCB_IRQ_t*/
typedef enum
{
	MemManage_IRQ=0,
	BusFault_IRQ,
	UsageFault,
	SVC_IRQ=7,
	PendSV_IRQ=10,
	SysTick_IRQ
}SCB_IRQ_t;


void SCB_voidInit(void);
void SCB_voidEnableZeroDivTrap(void);
void SCB_voidDisableZeroDivTrap(void);
void SCB_voidEnableUnalignTrap(void);
void SCB_voidDisableUnalignTrap(void);
ErrorStatus_t SCB_voidSetPriority(SCB_IRQ_t IRQ_Name, Priority_t priority);
void SCB_voidEnableUsageFault(void);
void SCB_voidDisableUsageFault(void);
void SCB_voidEnableBusFault(void);
void SCB_voidDisableBusFault(void);
void SCB_voidEnableMemManageFault(void);
void SCB_voidDisableMemManageFault(void);

#endif /* SCB_INTERFACE_H_ */
