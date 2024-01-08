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


#define  DMA1_BASE_ADDRESS    0x40026000UL

#define  DMA2_BASE_ADDRESS    0x40026400UL



/******************************    DMA Register Definitions   ******************************/

typedef struct
{
	volatile uint32_t DMA_SxCR;    /* DMA stream x configuration register */
	volatile uint32_t DMA_SxNDTR;  /* DMA stream x number of data register */
	volatile uint32_t DMA_SxPAR;   /* DMA stream x peripheral address register */
	volatile uint32_t DMA_SxM0AR;  /* DMA stream x memory 0 address register */
	volatile uint32_t DMA_SxM1AR;  /* DMA stream x memory 1 address register */
	volatile uint32_t DMA_SxFCR;   /* DMA stream x FIFO control register */
}DMA_Stream_RegDef_t;


typedef struct
{
	volatile uint32_t   DMA_ISR[2];      /* DMA low,high interrupt status register */
	volatile uint32_t   DMA_IFCR[2];     /* DMA low,High interrupt flag clear register */
	volatile DMA_Stream_RegDef_t  DMA_Stream[8]; /* array from DMA_Stream_RegDef_t which carrying DMA Stream from 0 to 7 Registers */
}DMA_RegDef_t;

/******************* DMAs structure pointer **********************/
#define    DMA1		((DMA_RegDef_t*)(DMA1_BASE_ADDRESS))
#define    DMA2		((DMA_RegDef_t*)(DMA2_BASE_ADDRESS))


#endif
