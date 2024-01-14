/*
 * I2C_Interface.h
 *
 *  Created on: Dec 17, 2023
 *      Author: AlsharQawy
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

/*@I2C_t*/
typedef enum
{
	I2C_1,
	I2C_2,
	I2C_3,
	TOTAL_I2C
}I2C_t;

/*@GeneralCall_t*/
typedef enum
{
	GCALL_DISABLE,
	GCALL_ENABLE,
}GeneralCall_t;

/*@I2C_Mode_t*/
typedef enum
{
	SM,
	FM,
}I2C_Mode_t;

/*@I2C_ReadWrite_t*/
typedef enum
{
	I2C_WRITE,
	I2C_READ,
}I2C_ReadWrite_t;


typedef struct
{
	I2C_t I2C;
	uint8_t Own_Address;
	GeneralCall_t GeneralCall;
	uint32_t SCL_Freq_HZ;
	I2C_Mode_t Mode;
}I2C_Config_t;




ErrorStatus_t I2C_voidInit(const I2C_Config_t* I2C_Config);
ErrorStatus_t I2C_Enable(I2C_t i2c);
ErrorStatus_t I2C_Disable(I2C_t i2c);
ErrorStatus_t I2C_MasterTransmitSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut);
ErrorStatus_t I2C_MasterReceiveSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut);
uint8_t I2C_MasterTransmitPeriodic(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size);
uint8_t I2C_MasterReceivePeriodic(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size);
uint8_t I2C_SlavePeriodic(I2C_t i2c, uint8_t* PdataTransmit, uint8_t SizeTransmit, uint8_t* PdataReceive, uint8_t SizeReceive );
ErrorStatus_t I2C_SlaveInterruptEnable(I2C_t i2c, uint8_t* PdataTransmit, uint8_t SizeTransmit, uint8_t* PdataReceive, uint8_t SizeReceive);
ErrorStatus_t I2C_SlaveInterruptDisable(I2C_t i2c);
ErrorStatus_t I2C_EnableMasterDMA(I2C_t i2c, uint8_t SlaveAddress, I2C_ReadWrite_t RW, uint32_t TimeOut);
ErrorStatus_t I2C_EnableSlaveDMA(I2C_t i2c);
ErrorStatus_t I2C_DisableDMA(I2C_t i2c);
ErrorStatus_t I2C_RepeatedStartSendSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut);
ErrorStatus_t I2C_RepeatedStartReceiveSynch(I2C_t i2c, uint8_t SlaveAddress, uint8_t* Pdata, uint8_t Size, uint32_t TimeOut);
uint32_t* I2C_DataRegisterAddress(I2C_t i2c);
void DMA_Master_CallBack_I2C1(void);
void DMA_Master_CallBack_I2C2(void);
void DMA_Master_CallBack_I2C3(void);


/////////////////	I2C_cfg.c  Functions	/////////////////
void DMA_I2C1_CallOut_Func(void);
void DMA_I2C2_CallOut_Func(void);
void DMA_I2C3_CallOut_Func(void);

#endif /* I2C_INTERFACE_H_ */
