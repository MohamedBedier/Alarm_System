/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : RCC_Private.h                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#define  RCC_TIMEOUT  50000u

#define RCC_CFGR_PLLMUL_MASK   0xFFC3FFFF
#define RCC_CFGR_PLLMUL_POS    18u

#define FLAG_RAISED  1u


#define PLLM_FACT_MAX        63u
#define PLLM_FACT_MIN        2u

#define PLLN_FACT_MAX        432u
#define PLLN_FACT_MIN        50u


#define PLLP_DIV2        2u
#define PLLP_DIV4        4u
#define PLLP_DIV6        6u
#define PLLP_DIV8        8u

#define PLLR_DIV2   2u
#define PLLR_DIV7   7u

#define PLLQ_DIV2   2u
#define PLLQ_DIV15   15u

#define  PLLM_MASK       0b11111
#define  PLLN_MASK       0b11111111
#define  PLLP_MASK       0b11
#define  PLLQ_MASK       0b1111
#define  PLLR_MASK       0b111

#define  PLLN_POS_IN_CFGR    6u
#define  PLLP_POS_IN_CFGR    16u
#define  PLLSRC_POS_IN_CFGR  22u
#define  PLLQ_POS_IN_CFGR    24u
#define  PLLR_POS_IN_CFGR    28u



#endif /* RCC_PRIVATE_H_ */
