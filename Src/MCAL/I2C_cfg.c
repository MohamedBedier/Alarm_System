/***********************************************************
* @file I2C_cfg.c
* @Author Abdullah AlsharQawy
* @Brief The main file for the real time clock driver RTC
***********************************************************/
#include <stdint.h>
#include <Stm32F446xx.h>
#include <ErrType.h>
#include <I2C_Wrapper.h>
#include <I2C_Interface.h>


/************************************************************
 * @fn DMA_I2C1_CallOut_Func
 * @brief This function you implement at it the wanted code you want to execute when
 *        the DMA finishes transferring the data in the EOT interrupt, for I2C1 peripheral
 * @param void
 * @retval void
************************************************************/
void DMA_I2C1_CallOut_Func(void)
{

}



/************************************************************
 * @fn DMA_I2C2_CallOut_Func
 * @brief This function you implement at it the wanted code you want to execute when
 *        the DMA finishes transferring the data in the EOT interrupt, for I2C2 peripheral
 * @param void
 * @retval void
************************************************************/
void DMA_I2C2_CallOut_Func(void)
{

}



/************************************************************
 * @fn DMA_I2C3_CallOut_Func
 * @brief This function you implement at it the wanted code you want to execute when
 *        the DMA finishes transferring the data in the EOT interrupt, for I2C3 peripheral
 * @param void
 * @retval void
************************************************************/
void DMA_I2C3_CallOut_Func(void)
{
	MCAL_DMA_I2C3_CallOut_WrapperFunc();
}





/*	DMA_StreamEnable(DMA_1, DMA_STREAM_2);
	I2C_EnableMasterDMA(I2C_3, 0b1101000, I2C_READ, 10000);*/

/*
	#include<DMA_Interface.h>
	#include<I2C_Interface.h>
	DMA_StreamEnable(DMA_1, DMA_STREAM_4);
	I2C_EnableMasterDMA(I2C_3, 15, I2C_WRITE, 10000);*/
