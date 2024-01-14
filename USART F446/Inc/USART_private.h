/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : USART_private.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_



#define  USART_PERIPHERAL_NUM  6u
#define  EIGHT_BIT_MASK_VAL    0x7F
#define  NINE_BIT_MASK_VAL     0xFF

#define  DIV_MANTISSA  4u
#define  DIV_FRACTION  0u
#define  ONE_THOUSAND_VAL   1000UL
#define  HALF_THOUSAND_VAL  500UL
#define  EIGHT_VAL   8u
#define  SIXTEEN_VAL   16u
#define  TWO_VAL   2u

#define  UART_TIME_OUT_VAL   90000UL

#define STOP_BITS_MASK_VAL  0b11
#define SET_USART_INTERRUPT_MASK  1u
#define CLR_USART_INTERRUPT_MASK  0u

#endif /* USART_PRIVATE_H_ */
