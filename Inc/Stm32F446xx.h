
#ifndef  STM32F446xx_H_
#define  STM32F446xx_H_




/************************		APB1 BASE ADRESSES		************************/

#define     I2C1_BASE_ADDRESS        0x40005400U
#define     I2C2_BASE_ADDRESS        0x40005800U
#define     I2C3_BASE_ADDRESS        0x40005C00U


/************************		I2C RESISTER STRUCTURE		************************/

typedef struct
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
	volatile uint32_t I2C_FLTR;
}I2C_RegDef_t;


/************************		I2C Peripheral Definitions		************************/
#define I2C1          ((I2C_RegDef_t*)I2C1_BASE_ADDRESS)
#define I2C2          ((I2C_RegDef_t*)I2C2_BASE_ADDRESS)
#define I2C3          ((I2C_RegDef_t*)I2C3_BASE_ADDRESS)







#endif
