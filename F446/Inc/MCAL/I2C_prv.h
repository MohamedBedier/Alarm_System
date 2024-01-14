/*
 * I2C_prv.h
 *
 *  Created on: Dec 17, 2023
 *      Author: AlsharQawy
 */

#ifndef I2C_PRV_H_
#define I2C_PRV_H_


#define     I2C_Master_StartBit(I2C)                     ((I2C)->I2C_CR1)|=(0b1<<8)

#define     I2C_Master_PollStartBit(I2C)                 while(!((((I2C)->I2C_SR1)>>0)&1))

#define     I2C_Master_SendAddress(I2C, RW, Address)     (Address)=(((Address)<<0b1) | (RW));\
														 ((I2C)->I2C_DR)=(Address)

#define     I2C_PollClrAddressAck(I2C)         	         while(!(((I2C->I2C_SR1)>>1)&1)){}\
														 ((I2C)->I2C_SR2)=((I2C)->I2C_SR2)

#define     I2C_R_PollDataAck(I2C)                       while(!((((I2C)->I2C_SR1)>>6)&1))

#define     I2C_Master_StopBit(I2C)                      ((I2C)->I2C_CR1)|=(0b1<<9)

#define     I2C_EnableACK(I2C)                           ((I2C)->I2C_CR1)|= (0b1<<10)
#define     I2C_DisableACK(I2C)                          ((I2C)->I2C_CR1)&=~(0b1<<10)

#define     I2C_SetPos(I2C)                              ((I2C)->I2C_CR1)|=(0b1<<11)

#define     I2C_PollBTF(I2C)                             while(!((((I2C)->I2C_SR1)>>2)&1))



#define  I2C_EN_BIT_ACCESS      0U
#define  GCALL_BIT_ACCESS       6U
#define  NOSTRETCH_BIT_ACCESS   7U

#define  FREQ_BIT_MASK          0b111111UL
#define  FREQ_BIT_ACCESS        0U
#define  BUFFER_IT_BIT_ACCESS   10U
#define  EVENT_IT_BIT_ACCESS    9U
#define  ERROR_IT_BIT_ACCESS    8U
#define  DMA_EN_BIT_ACCESS      11U
#define  LAST_BIT_ACCESS        12U

#define  ADDMODE_BIT_ACCESS     15U
#define  ADDRESS_BIT_MASK       0b1111111UL
#define  ADDRESS_BIT_ACCESS     1U

#define  START_BIT_ACCESS       0U
#define  ADDR_BIT_ACCESS        1U
#define  BTF_BIT_ACCESS         2U
#define  STOPF_BIT_ACCESS       4U
#define  RXNE_BIT_ACCESS        6U
#define  TXE_BIT_ACCESS         7U
#define  ACKF_BIT_ACCESS        10U

#define  MASTER_SLAVE_BIT       0U
#define  BUSY_BIT_ACCESS        1U
#define  TRA_BIT_ACCESS         2U

#define  CCR_BIT_ACCESS         0UL
#define  CCR_BIT_MASK           0b111111111111UL
#define  MODE_BIT_ACCESS        15U







static I2C_RegDef_t* I2C_SelcetPeripheral(I2C_t i2c);
static void I2C_EnableEventInterrupts(I2C_RegDef_t* I2C);
static void I2C_EnableBufferInterrupts(I2C_RegDef_t* I2C);
static void I2C_EnableErrorInterrupts(I2C_RegDef_t* I2C);
static void I2C_DisableEventInterrupts(I2C_RegDef_t* I2C);
static void I2C_DisableErrorInterrupts(I2C_RegDef_t* I2C);
static void I2C_DisableBufferInterrupts(I2C_RegDef_t* I2C);
void DMA_I2C1_CallOut_Func(void);
void DMA_I2C2_CallOut_Func(void);
void DMA_I2C3_CallOut_Func(void);



typedef enum
{
	DATA_T_ACK_STATE,
	DATA_R_ACK_STATE,
	STOP_STATE
}I2C_IT_States_t;





#endif /* I2C_PRV_H_ */
