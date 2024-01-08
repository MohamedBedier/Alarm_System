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




#define    SCB_BASE_ADDRESS      0xE000ED00UL



/******************************    SCB Register Definitions   ******************************/
typedef struct
{
	volatile  uint32_t   CPUID;
	volatile  uint32_t   ICSR;
	volatile  uint32_t   VTOR;
	volatile  uint32_t   AIRCR;
	volatile  uint32_t   SCR;
	volatile  uint32_t   CCR;
	volatile  uint32_t   SHPR1;
	volatile  uint32_t   SHPR2;
	volatile  uint32_t   SHPR3;
	volatile  uint32_t   SHCSR;
	volatile  uint32_t   CFSR;
	volatile  uint32_t   HFSR;
	volatile  uint32_t   MMAR;
	volatile  uint32_t   BFAR;
	volatile  uint32_t   AFSR;
}SCB_Reg_t;

/******************************    SCB structure pointer **********************/
#define      SCB		((SCB_Reg_t *)(SCB_BASE_ADDRESS))


#endif
