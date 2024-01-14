/***********************************************************
* @file DoTasks_cfg.c
* @Author Abdullah AlsharQawy
* @Brief Here you can implement the tasks you want to perform based on the related received instruction form the master MCU
***********************************************************/


#include <stdint.h>
#include <ErrType.h>

#include <SysTick_Interface.h>
#include <RCC_Interface.h>
#include <GPIO_Interface.h>
#include <BZR_interface.h>
#include <LED_Interface.h>

#include <Screen_Wrapper.h>
#include <ReceiveData.h>
#include <DoTasks_cfg.h>
#include <DoTasks_prv.h>
#include <DoTasks.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
Fptr InstructionsArr[TOTAL_INS]={InsTask1, InsTask2, InsTask3};
extern char AlarmName[ALARM_LETTERS_NUM+1];



/***********************************************************
* @fn InsTask1
* @Brief Function you want to run when the first instruction is received
* @Param void
* @retval void
***********************************************************/
static void InsTask1(void)
{
	LED_u8LedTurnON(RED_LED_PORT, RED_LED_PIN , SOURCE_CONNECTION);
}

/***********************************************************
* @fn InsTask2
* @Brief Function you want to run when the second instruction is received
* @Param void
* @retval void
***********************************************************/
static void InsTask2(void)
{
	LED_u8LedTurnON(GREEN_LED_PORT, GREEN_LED_PIN , SOURCE_CONNECTION);
}

/***********************************************************
* @fn InsTask3
* @Brief Function you want to run when the third instruction is received
* @Param void
* @retval void
***********************************************************/
static void InsTask3(void)
{
	Screen_Clear();
	Screen_SetCursor(0, 0);
	Screen_WriteString("Alarm Name:");
	uint8_t size;
	for(size=0; AlarmName[size]; size++);
	Screen_SetCursor(1, (16-size)/2);
	Screen_WriteString(AlarmName);

	PinVal_t PB_State=PIN_HIGH;
	while(PB_State==PIN_HIGH)
	{
		BZR_u8TurnOn(BUZZER_PORT,  BUZZER_PIN);
		GPIO_u8ReadPinValue(STOP_ALARM_PORT, STOP_ALARM_PIN, &PB_State);
	}

	Screen_Clear();
}


/***********************************************************
* @fn UserTask_Init
* @Brief in this function you do the configuration and initialization of the tasks you added
* @Param void
* @retval void
***********************************************************/
void UserTask_Init(void)
{
	switch(RED_LED_PORT)
	{
		case PORTA:
			RCC_u8APB_2_EnableClk(IOPA_EN);      break;
		case PORTB:
			RCC_u8APB_2_EnableClk(IOPB_EN);      break;
		case PORTC:
			RCC_u8APB_2_EnableClk(IOPC_EN);      break;
		case PORTD:
			RCC_u8APB_2_EnableClk(IOPD_EN);      break;
		case PORTE:
			RCC_u8APB_2_EnableClk(IOPE_EN);      break;
		case PORTF:
			RCC_u8APB_2_EnableClk(IOPF_EN);      break;
		case PORTG:
			RCC_u8APB_2_EnableClk(IOPG_EN);      break;
	}
	PinConfig_t RedLedConfig=
	{
		.Port=RED_LED_PORT,
		.PinNum=RED_LED_PIN,
		.Mode=OUTPUT_MAXSPEED_10MHZ,
		.CNF_OutputMode=PUSH_PULL
	};
	LED_u8PinInit(&RedLedConfig);
	LED_u8LedTurnOff(RED_LED_PORT, RED_LED_PIN , SOURCE_CONNECTION);

	switch(GREEN_LED_PORT)
	{
		case PORTA:
			RCC_u8APB_2_EnableClk(IOPA_EN);      break;
		case PORTB:
			RCC_u8APB_2_EnableClk(IOPB_EN);      break;
		case PORTC:
			RCC_u8APB_2_EnableClk(IOPC_EN);      break;
		case PORTD:
			RCC_u8APB_2_EnableClk(IOPD_EN);      break;
		case PORTE:
			RCC_u8APB_2_EnableClk(IOPE_EN);      break;
		case PORTF:
			RCC_u8APB_2_EnableClk(IOPF_EN);      break;
		case PORTG:
			RCC_u8APB_2_EnableClk(IOPG_EN);      break;
	}
	PinConfig_t GreenLedConfig=
	{
		.Port=GREEN_LED_PORT,
		.PinNum=GREEN_LED_PIN,
		.Mode=OUTPUT_MAXSPEED_10MHZ,
		.CNF_OutputMode=PUSH_PULL
	};
	LED_u8PinInit(&GreenLedConfig);
	LED_u8LedTurnOff(GREEN_LED_PORT, GREEN_LED_PIN , SOURCE_CONNECTION);

	switch(BUZZER_PORT)
	{
		case PORTA:
			RCC_u8APB_2_EnableClk(IOPA_EN);      break;
		case PORTB:
			RCC_u8APB_2_EnableClk(IOPB_EN);      break;
		case PORTC:
			RCC_u8APB_2_EnableClk(IOPC_EN);      break;
		case PORTD:
			RCC_u8APB_2_EnableClk(IOPD_EN);      break;
		case PORTE:
			RCC_u8APB_2_EnableClk(IOPE_EN);      break;
		case PORTF:
			RCC_u8APB_2_EnableClk(IOPF_EN);      break;
		case PORTG:
			RCC_u8APB_2_EnableClk(IOPG_EN);      break;
	}
	PinConfig_t BuzzerConfig=
	{
		.Port=BUZZER_PORT,
		.PinNum=BUZZER_PIN,
		.Mode=OUTPUT_MAXSPEED_10MHZ,
		.CNF_OutputMode=PUSH_PULL
	};
	BZR_u8Init(&BuzzerConfig);
	BZR_u8TurnOff(BUZZER_PORT, BUZZER_PIN);

	switch(STOP_ALARM_PORT)
	{
		case PORTA:
			RCC_u8APB_2_EnableClk(IOPA_EN);      break;
		case PORTB:
			RCC_u8APB_2_EnableClk(IOPB_EN);      break;
		case PORTC:
			RCC_u8APB_2_EnableClk(IOPC_EN);      break;
		case PORTD:
			RCC_u8APB_2_EnableClk(IOPD_EN);      break;
		case PORTE:
			RCC_u8APB_2_EnableClk(IOPE_EN);      break;
		case PORTF:
			RCC_u8APB_2_EnableClk(IOPF_EN);      break;
		case PORTG:
			RCC_u8APB_2_EnableClk(IOPG_EN);      break;
	}
	PinConfig_t StopAlarmConfig=
	{
		.Port=STOP_ALARM_PORT,
		.PinNum=STOP_ALARM_PIN,
		.Mode=INPUT,
		.CNF_InputMode=FLOATING_INPUT
	};
	BZR_u8Init(&StopAlarmConfig);
}



/*You can add any number of tasks you want you just need to:
 * -Implement the function
 * -Add the used peripheral initialization if exists in UserTask_Init function
 * -Add its name to the InstructionsArr array of functions
 * -Add the instruction name to the ReceInstruc_t enum in DOTasks_cfg.h above the TOTAL_INS according to the order you want
 * -Repeat the last step with the TransInstruc_t enum in the master*/


