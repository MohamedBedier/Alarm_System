/***********************************************************
* @file LCD_Prog.c
* @Author Abdullah AlsharQawy
* @Brief The main file for the LCD driver
***********************************************************/

#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "cnfg.h"

#include "SysTick_Interface.h"
#include "RCC_Interface.h"
#include "GPIO_interface.h"
#include "LCD_Interface.h"
#include "LCD_cfg.h"


static void WriteIns(uint8_t ins)
{
	GPIO_u8SetPinValue(RS_PORT , RS_PIN , PIN_LOW);
	GPIO_u8SetPinValue(LCD_DATA_PORT, D4, GET_BIT(ins, 4));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D5, GET_BIT(ins, 5));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D6, GET_BIT(ins, 6));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D7, GET_BIT(ins, 7));
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_HIGH);
	SysTick_Delayms(1);
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_LOW);

	GPIO_u8SetPinValue(LCD_DATA_PORT, D4, GET_BIT(ins, 0));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D5, GET_BIT(ins, 1));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D6, GET_BIT(ins, 2));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D7, GET_BIT(ins, 3));
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_HIGH);
	SysTick_Delayms(1);
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_LOW);
	SysTick_Delayms(1);
}

static void WriteData(uint8_t data)
{
	GPIO_u8SetPinValue(RS_PORT , RS_PIN , PIN_HIGH);
	GPIO_u8SetPinValue(LCD_DATA_PORT, D4, GET_BIT(data, 4));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D5, GET_BIT(data, 5));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D6, GET_BIT(data, 6));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D7, GET_BIT(data, 7));
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_HIGH);
	SysTick_Delayms(1);
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_LOW);

	GPIO_u8SetPinValue(LCD_DATA_PORT, D4, GET_BIT(data, 0));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D5, GET_BIT(data, 1));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D6, GET_BIT(data, 2));
	GPIO_u8SetPinValue(LCD_DATA_PORT, D7, GET_BIT(data, 3));
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_HIGH);
	SysTick_Delayms(1);
	GPIO_u8SetPinValue(EN_PORT, EN_PIN, PIN_LOW);
	SysTick_Delayms(1);
}


void LCD_Init(void)
{
	switch(LCD_DATA_PORT)
	{
		case PORTA:
			RCC_u8APB_2_EnableClk(IOPA_EN);			break;
		case PORTB:
			RCC_u8APB_2_EnableClk(IOPB_EN);			break;
		case PORTC:
			RCC_u8APB_2_EnableClk(IOPC_EN);			break;
		case PORTD:
			RCC_u8APB_2_EnableClk(IOPD_EN);			break;
		case PORTE:
			RCC_u8APB_2_EnableClk(IOPE_EN);			break;
		case PORTF:
			RCC_u8APB_2_EnableClk(IOPF_EN);			break;
		case PORTG:
			RCC_u8APB_2_EnableClk(IOPG_EN);			break;
	}
	switch(RS_PORT)
	{
		case PORTA:
			RCC_u8APB_2_EnableClk(IOPA_EN);			break;
		case PORTB:
			RCC_u8APB_2_EnableClk(IOPB_EN);			break;
		case PORTC:
			RCC_u8APB_2_EnableClk(IOPC_EN);			break;
		case PORTD:
			RCC_u8APB_2_EnableClk(IOPD_EN);			break;
		case PORTE:
			RCC_u8APB_2_EnableClk(IOPE_EN);			break;
		case PORTF:
			RCC_u8APB_2_EnableClk(IOPF_EN);			break;
		case PORTG:
			RCC_u8APB_2_EnableClk(IOPG_EN);			break;
	}
	switch(EN_PORT)
	{
		case PORTA:
			RCC_u8APB_2_EnableClk(IOPA_EN);			break;
		case PORTB:
			RCC_u8APB_2_EnableClk(IOPB_EN);			break;
		case PORTC:
			RCC_u8APB_2_EnableClk(IOPC_EN);			break;
		case PORTD:
			RCC_u8APB_2_EnableClk(IOPD_EN);			break;
		case PORTE:
			RCC_u8APB_2_EnableClk(IOPE_EN);			break;
		case PORTF:
			RCC_u8APB_2_EnableClk(IOPF_EN);			break;
		case PORTG:
			RCC_u8APB_2_EnableClk(IOPG_EN);			break;
	}



	/* CNTRL PINS RS ===>PINA8 AND EN ===> PINA11 */
	PinConfig_t RS_PA11 = {.Port = RS_PORT,.PinNum =RS_PIN , .Mode = OUTPUT_MAXSPEED_2MHZ ,.CNF_OutputMode=PUSH_PULL};
	PinConfig_t EN_PA8  = {.Port = EN_PORT,.PinNum =EN_PIN , .Mode = OUTPUT_MAXSPEED_2MHZ ,.CNF_OutputMode=PUSH_PULL};

	/* DATA PINS D7 ===> PINB15 ,D6 ===> PINB14 ,D5 ===> PINB13 ,D4 ===> PINB12 */
	PinConfig_t Data_PinB15 = {.Port = LCD_DATA_PORT,.PinNum =D4 , .Mode = OUTPUT_MAXSPEED_2MHZ ,.CNF_OutputMode=PUSH_PULL};
	PinConfig_t Data_PinB14 = {.Port = LCD_DATA_PORT,.PinNum =D5 , .Mode = OUTPUT_MAXSPEED_2MHZ ,.CNF_OutputMode=PUSH_PULL};
	PinConfig_t Data_PinB13 = {.Port = LCD_DATA_PORT,.PinNum =D6 , .Mode = OUTPUT_MAXSPEED_2MHZ ,.CNF_OutputMode=PUSH_PULL};
	PinConfig_t Data_PinB12 = {.Port = LCD_DATA_PORT,.PinNum =D7 , .Mode = OUTPUT_MAXSPEED_2MHZ ,.CNF_OutputMode=PUSH_PULL};

	/* CALL the function of GPIO_u8PinInit */
	GPIO_u8PinInit(&RS_PA11);
	GPIO_u8PinInit(&EN_PA8 );

	GPIO_u8PinInit(&Data_PinB15);
	GPIO_u8PinInit(&Data_PinB14);
	GPIO_u8PinInit(&Data_PinB13);
	GPIO_u8PinInit(&Data_PinB12);

	SysTick_Delayms(40);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0C);
	WriteIns(0x01);
	SysTick_Delayms(1);
	WriteIns(0x06);
}


void LCD_Clear(void)
{
	WriteIns(0x01);
	SysTick_Delayms(1);
}


void LCD_WriteNumber(int32_t num)
{
	uint8_t i=0, str[16];
	int8_t j=0;
	if(num==0)
	{
		LCD_WriteChar('0');
		return;
	} 
	if(num<0)
	{
		LCD_WriteChar('-');
		num*=-1;
	}
	
	while(num)
	{
		str[i]=num%10+'0';
		num/=10;
		i++;
	}
	for(j=i-1; j>=0; j--)
	{
		LCD_WriteChar(str[j]);
	}
}


void LCD_WriteChar(uint8_t ch)
{
	WriteData(ch);
}


void LCD_WriteString(char* str)
{
	for(uint8_t i=0; str[i]; i++)
	{
		WriteData(str[i]);
	}
}


void LCD_SetCursor(uint8_t row, uint8_t col)
{
	WriteIns(0x80+row*0x40+col);
}



void LCD_WriteNumberInTwoDigits(uint8_t num)
{
	if(num>99) num=99;

	LCD_WriteNumber(num/10);
	LCD_WriteNumber(num%10);
}



