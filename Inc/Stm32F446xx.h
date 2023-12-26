
#ifndef  STM32F446xx_H_
#define  STM32F446xx_H_


/************************		AHB1 BASE ADRESSES		************************/

#define  SYSTICK_BASE_ADDRESS  0xE000E010U

/************************		SysTick RESISTER STRUCTURE		************************/

typedef struct
{
	volatile uint32_t SYST_CSR;
	volatile uint32_t SYST_RVR;
	volatile uint32_t SYST_CVR;
	volatile uint32_t SYST_CALIB;
}SysTick_RegDef_t;


/************************		SysTick Peripheral Definitions		************************/
#define SYSTICK        ((SysTick_RegDef_t*)SYSTICK_BASE_ADDRESS)









#endif
