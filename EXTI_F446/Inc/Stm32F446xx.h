/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: Library                                 **/
/** File Name : Stm32F446xx.h                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef  STM32F446XX_H_
#define  STM32F446XX_H_


/******************************    AHB2 Peripheral Base Addresses       ******************************/

#define    EXTI_BASE_ADDRESS     0x40013C00UL


/******************************    EXTII Register Definitions   ******************************/
typedef struct
{
	volatile uint32_t EXTI_IMR; /* Interrupt mask register */
	volatile uint32_t EXTI_EMR; /* Event mask register  */
	volatile uint32_t EXTI_RTSR; /* Rising trigger selection register */
	volatile uint32_t EXTI_FTSR; /* Falling trigger selection register */
	volatile uint32_t EXTI_SWIER; /* Software interrupt event register */
	volatile uint32_t EXTI_PR;   /* Pending register */
}EXTI_Reg_t;
/******************* EXTI structure pointer **********************/
#define    EXTI		((EXTI_Reg_t *)(EXTI_BASE_ADDRESS))





#endif
