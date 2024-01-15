/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : DMA_private.h                               **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/
#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

#define  DMA_PERIPHERAL_NUM  2u
#define  DMA_STREAM_NUM      8u


#define  DMA_DIR_MASK_START_BIT  6u

#define  DMA_CHSEL_STR_BIT   25u
#define  DMA_CHSEL_MASK      7u

#define  DMA_PL_STR_BIT   16u
#define  DMA_PL_MASK      3u


#define  DMA_PSIZE_MASK_START_BIT    11u
#define  DMA_MSIZE_MASK_START_BIT    13u
#define  DMA_PBURST_MASK_START_BIT   21u
#define  DMA_MBURST_MASK_START_BIT   23u


#define   DMA_NUM_SxCR   (DMA[Copy_psDMA->DMA_NUM]->DMA_Stream[Copy_psDMA->Stream_NUM].DMA_SxCR)




#define   CHSEL_BITS_MASK  0b111
#define   PL_BITS_MASK  0b11
#define   SET_INTERRUPT_MASK  1u
#define   CLR_INTERRUPT_MASK  0u
#define   ISR_LOW_REG         0u
#define   ISR_HIGH_REG        1u
#define   IFCR_LOW_REG        0u
#define   IFCR_HIGH_REG       1u
#define   DIV_FACT_4          4u
#define   DIR_MODE_BITS_MASK  0b11
#define   FIFO_BIT_MASK  0b1
#define   FIFO_THRESHOLD_BITS_MASK  0b11
#define   PDATAALIAGN_BITS_MASK  0b11
#define   MDATAALIAGN_BITS_MASK  0b11
#define   CIRC_MODE_BIT_MASK  0b1


#define  TIME_OUT_VAL     50000U

#endif /* DMA_PRIVATE_H_ */
