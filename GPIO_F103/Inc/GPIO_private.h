/*************************************************************/
/*************************************************************/
/**                                                         **/
/** @file GPIO_Private.h                                    **/
/** @author MOHAMED BEDIER MOHAMED                          **/
/** @brief the GPIO private file,Including private macros   **/
/** @version 1.00                                           **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef  GPIO_PRIVATE_H_
#define  GPIO_PRIVATE_H_

/* macro for array size */
#define GPIO_PERIPHERAL_NUM  7u


#define MODE_MASK   0b11
#define MODE_PIN_ACCESS  4u

#define CR_PIN_SHIFTING    8u

#define CNF_MASK   0b11
#define CNF_PIN_ACCESS  2u
#define CNF_SHIFTING_PIN_ACCESS  4u


#define CNF_PIN_SHIFTING    8u


#define ODR_MASK  1u
#define IDR_MASK  1u


#endif
