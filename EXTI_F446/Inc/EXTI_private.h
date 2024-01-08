/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : EXTI_private.h                              **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define  NUM_OF_EXTI 16u

#define  FLAG_RAISED  1u

#define   EXTI5_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,5)
#define   EXTI6_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,6)
#define   EXTI7_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,7)
#define   EXTI8_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,8)
#define   EXTI9_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,9)


#define   EXTI10_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,10)
#define   EXTI11_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,11)
#define   EXTI12_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,12)
#define   EXTI13_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,13)
#define   EXTI14_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,14)
#define   EXTI15_PENDING_FLAG   GET_BIT(EXTI->EXTI_PR,15)



#endif /* EXTI_PRIVATE_H_ */
