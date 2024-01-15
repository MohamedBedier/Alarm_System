/***********************************************************
* @file I2C_Wrapper.c
* @Author Abdullah AlsharQawy
* @Brief Functions for the I2C module wrapper functions
***********************************************************/
#include <stdint.h>
#include <ErrType.h>

#include <GetTime.h>
#include <I2C_Interface.h>
#include <I2C_Wrapper.h>


/***********************************************************
* @fn MCAL_DMA_I2C3_CallOut_WrapperFunc
* @brief The function that will be called when the DMA interface with the I2C finishes transferring the data
* @param void
* @retval void
***********************************************************/
void MCAL_DMA_I2C3_CallOut_WrapperFunc(void)
{
	voidFinishTransFlag_Setter();
}









