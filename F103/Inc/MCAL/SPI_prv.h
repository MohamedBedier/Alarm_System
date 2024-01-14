/*
 * SPI_prv.h
 *
 *  Created on: Dec 15, 2023
 *      Author: AlsharQawy
 */

#ifndef SPI_PRV_H_
#define SPI_PRV_H_


#define   MASTER_BIT_ACCESS        2
#define   DATAFRAME_BIT_ACCESS     11
#define   FIRSTLSB_BIT_ACCESS      7
#define   PRESCALER_BIT_ACCESS     3
#define   SWSLVMNG_BIT_ACCESS      9

#define   SPI_ENABLE_BIT_ACCESS    6

#define   SPI_NSS_BIT_ACCESS       8

#define   SPI_TRAN_IT_EN_BIT_ACCESS     7
#define   SPI_RECE_IT_EN_BIT_ACCESS     6

#define   SPI_TRAN_DMA_EN_BIT_ACCESS     1
#define   SPI_RECE_DMA_EN_BIT_ACCESS     0

#define   SPI_TRAN_BUFFER_EMPTY_BIT_ACCESS     1
#define   SPI_RECE_BUFFER_FULL_BIT_ACCESS      0




static SPI_RegDef_t* SPI_SelcetPeripheral(SPI_t SPI);
static void SPI_ReceiveNoBlock(SPI_t spi);
static void SPI_TransmitNoBlock(SPI_t spi);


#endif /* SPI_PRV_H_ */
