
#ifndef  STM32F446xx_H_
#define  STM32F446xx_H_



/************************		NVIC Peripheral Definitions		************************/
#define NVIC_ISER      ((volatile uint32_t*)0xE000E100)
#define NVIC_ICER      ((volatile uint32_t*)0XE000E180)
#define NVIC_ISPR      ((volatile uint32_t*)0XE000E200)
#define NVIC_ICPR      ((volatile uint32_t*)0XE000E280)
#define NVIC_IABR      ((volatile uint32_t*)0xE000E300)
#define NVIC_IPR       ((volatile uint8_t*) 0xE000E400)
#define NVIC_STIR      ((volatile uint32_t*)0xE000EF00)



#endif
