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


/******************************    APB1 Peripheral Base Addresses       ******************************/

#define    USART2_BASE_ADDRESS      0x40004400UL
#define    USART3_BASE_ADDRESS      0x40004800UL
#define    UART4_BASE_ADDRESS       0x40004C00UL
#define    UART5_BASE_ADDRESS       0x40005000UL

/******************************    APB2 Peripheral Base Addresses       ******************************/

#define    USART1_BASE_ADDRESS      0x40011000UL
#define    USART6_BASE_ADDRESS      0x40010400UL

/******************************    USART Register Definitions   ******************************/
typedef struct
{
	volatile uint32_t  USART_SR;     /* Status register */
	volatile uint32_t  USART_DR;     /* Data register */
	volatile uint32_t  USART_BRR;    /* Baud rate register  */
	volatile uint32_t  USART_CR1;  /* Control register 1 */
	volatile uint32_t  USART_CR2;  /* Control register 2 */
	volatile uint32_t  USART_CR3;  /* Control register 3 */
	volatile uint32_t  USART_GTPR;   /* Guard time and prescaler register */
}USART_RegDef_t;

/******************* USART structure pointer **********************/

#define    USART1	((USART_RegDef_t*)(USART1_BASE_ADDRESS))
#define    USART2	((USART_RegDef_t*)(USART2_BASE_ADDRESS))
#define    USART3	((USART_RegDef_t*)(USART3_BASE_ADDRESS))
#define    UART4	((USART_RegDef_t*)(UART4_BASE_ADDRESS))
#define    UART5	((USART_RegDef_t*)(UART5_BASE_ADDRESS))
#define    USART6	((USART_RegDef_t*)(USART6_BASE_ADDRESS))

#endif
