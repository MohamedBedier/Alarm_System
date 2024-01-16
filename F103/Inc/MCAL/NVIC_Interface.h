/*
 * NVIC_Interface.h
 *
 *  Created on: Nov 30, 2023
 *      Author: AlsharQawy
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include <cnfg.h>

/*@NVIC_IRQ_t*/
typedef enum
{
	WWDG_IRQ=0,
	PVD_IRQ,
	TAMPER_IRQ,
	RTC_IRQ,
	FLASH_IRQ,
	RCC_IRQ,
	EXTI0_IRQ,
	EXTI1_IRQ,
	EXTI2_IRQ,
	EXTI3_IRQ,
	EXTI4_IRQ,
	DMA1_Stream1_IRQ,
	DMA1_Stream2_IRQ,
	DMA1_Stream3_IRQ,
	DMA1_Stream4_IRQ,
	DMA1_Stream5_IRQ,
	DMA1_Stream6_IRQ,
	DMA1_Stream7_IRQ,
	ADC1_2_IRQ,
	USB_HP_CAN_TX_IRQ,
	USB_LP_CAN_RX0_IRQ,
	CAN_RX1_IRQ,
	CAN_SCE_IRQ,
	EXTI9_5_IRQ,
	TIM1_BRK_TIM9_IRQ,
	TIM1_UP_TIM10_IRQ,
	TIM1_TRG_COM_TIM11_IRQ,
	TIM1_CC_IRQ,
	TIM2_IRQ,
	TIM3_IRQ,
	TIM4_IRQ,
	I2C1_EV_IRQ,
	I2C1_ER_IRQ,
	I2C2_EV_IRQ,
	I2C2_ER_IRQ,
	SPI1_IRQ,
	SPI2_IRQ,
	USART1_IRQ,
	USART2_IRQ,
	USART3_IRQ,
	EXTI15_10_IRQ,
	RTC_Alarm_IRQ,
	USBWakeUp_IRQ,
	TIM8_BRK_TIM12_IRQ,
	TIM8_UP_TIM13_IRQ,
	TIM8_TRG_COM_TIM14_IRQ,
	TIM8_CC_IRQ,
	ADC3_IRQ,
	FSMC_IRQ,
	SDIO_IRQ,
	TIM5_IRQ,
	SPI3_IRQ,
	UART4_IRQ,
	UART5_IRQ,
	TIM6_IRQ,
	TIM7_IRQ,
	DMA2_Stream1_IRQ,
	DMA2_Stream2_IRQ,
	DMA2_Stream3_IRQ,
	DMA2_Stream4_5_IRQ,
	TOTAL_IRQS
}NVIC_IRQ_t;

/*@ActiveInterrrupt_t*/
typedef enum
{
	INTERRUPT_NOT_ACTIVE=0,
	INTERRUPT_ACTIVE,
}ActiveInterrrupt_t;


ErrorStatus_t NVIC_EnableInterrupt(NVIC_IRQ_t IQR_Num);
ErrorStatus_t NVIC_DisableInterrupt(NVIC_IRQ_t IQR_Num);
ErrorStatus_t NVIC_SetPenddingFlag(NVIC_IRQ_t IQR_Num);
ErrorStatus_t NVIC_ClearPenddingFlag(NVIC_IRQ_t IQR_Num);
ActiveInterrrupt_t NVIC_GetActiveFlag(NVIC_IRQ_t IRQ_Name);
ErrorStatus_t NVIC_voidSetPriority(NVIC_IRQ_t IRQ_Name, SupGroupPriority_t priority);


#endif /* NVIC_INTERFACE_H_ */
