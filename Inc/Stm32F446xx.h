
#ifndef  STM32F446xx_H_
#define  STM32F446xx_H_



/************************		SCB Peripheral Definitions		************************/
#define SCB_ACTLR      (*(volatile uint32_t*)0xE000E008)
#define SCB_CPUID      (*(volatile uint32_t*)0xE000ED00)
#define SCB_ICSR       (*(volatile uint32_t*)0xE000ED04)
#define SCB_VTOR       (*(volatile uint32_t*)0xE000ED08)
#define SCB_AIRCR      (*(volatile uint32_t*)0xE000ED0C)
#define SCB_SCR        (*(volatile uint32_t*)0xE000ED10)
#define SCB_CCR        (*(volatile uint32_t*)0xE000ED14)
#define SCB_SHPR       ((volatile uint8_t*)0xE000ED18)
#define SCB_SHCSR      (*(volatile uint32_t*)0xE000ED24)
#define SCB_CFSR       (*(volatile uint32_t*)0xE000ED28)
#define SCB_MMSR       (*(volatile uint32_t*)0xE000ED28)
#define SCB_BFSR       (*(volatile uint32_t*)0xE000ED29)
#define SCB_UFSR       (*(volatile uint32_t*)0xE000ED2A)
#define SCB_HFSR       (*(volatile uint32_t*)0xE000ED2C)
#define SCB_MMAR       (*(volatile uint32_t*)0xE000ED34)
#define SCB_BFAR       (*(volatile uint32_t*)0xE000ED38)
#define SCB_AFSR       (*(volatile uint32_t*)0xE000ED3C)





#endif
