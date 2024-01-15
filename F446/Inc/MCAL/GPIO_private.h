/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : GPIO_private.h                              **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef  GPIO_PRIVATE_H_
#define  GPIO_PRIVATE_H_

#define GPIO_PERIPHERAL_NUM  8u


#define MODER_MASK  0b11
#define MODER_PIN_ACCESS  2u

#define PUPDR_MASK  0b11
#define PUPDR_PIN_ACCESS  2u


#define OTYPER_MASK  1u

#define OSPEEDR_MASK  0b11
#define OSPEEDR_PIN_ACCESS  2u


#define AFR_MASK   0b1111
#define AFR_PIN_ACCESS  4u

#define AFR_PIN_SHIFTING    8u

#define ODR_MASK  1u
#define IDR_MASK  1u
#endif
