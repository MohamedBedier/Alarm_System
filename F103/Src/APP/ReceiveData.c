/***********************************************************
* @file ReceiveData.c
* @Author Abdullah AlsharQawy
* @Brief The main file for the functions of sending data to the other MCU over SPI communication
***********************************************************/


#include <stdint.h>
#include <ErrType.h>
#include <cnfg.h>

#include <SPI_Interface.h>
#include <GPIO_Interface.h>
#include <NVIC_Interface.h>
#include <RCC_Interface.h>
#include <EXTI_Interface.h>
#include <SysTick_Interface.h>

#include <DoTasks_cfg.h>
#include <ReceiveData_prv.h>
#include <ReceiveData.h>
#include <ReceiveData_cfg.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
NowTimeStruct_t NowTime_Struct;
uint16_t Rece_Ins=TOTAL_INS;
char AlarmName[ALARM_LETTERS_NUM+1];



/***********************************************************
* @fn ReceData_Init
* @Brief Function for initialization of the SPI peripheral used in receiving data form the master MCU
* @Param void
* @retval void
***********************************************************/
void ReceData_Init(void)
{
	/*Enabling clock on port of the SCK pin*/
	switch(SPI_SCK_PORT)
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
	/*Enabling clock on port of the MOSI pin*/
	switch(SPI_MOSI_PORT)
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
	/*Enabling clock on port of the external interrupt pin*/
	switch(EXT_PORT)
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

	/*Enabling clock on SPI peripheral*/
	NVIC_IRQ_t ReceDataSPI_IRQ;
	switch(RECEIVE_DATA_SPI)
	{
		case SPI_1:
			RCC_u8APB_2_EnableClk(SPI1_EN);
			ReceDataSPI_IRQ=SPI1_IRQ;
			break;
		case SPI_2:
			RCC_u8APB_1_EnableClk(SPI2_EN);
			ReceDataSPI_IRQ=SPI2_IRQ;
			break;
	}


	/*Saving the values of the external interrupt pin Line and global interrupt*/
	NVIC_IRQ_t EXTI_Line_IRQ;
	EXTI_Lines_t EXTI_Line_SysCfg;
	EXTI_Line_t EXTI_Line;
	switch(EXT_PIN)
	{
		case PIN0:
			EXTI_Line_IRQ=EXTI0_IRQ;       EXTI_Line_SysCfg=Line0;    EXTI_Line=EXTI0;   break;
		case PIN1:
			EXTI_Line_IRQ=EXTI1_IRQ;       EXTI_Line_SysCfg=Line1;    EXTI_Line=EXTI1;   break;
		case PIN2:
			EXTI_Line_IRQ=EXTI2_IRQ;       EXTI_Line_SysCfg=Line2;    EXTI_Line=EXTI2;   break;
		case PIN3:
			EXTI_Line_IRQ=EXTI3_IRQ;       EXTI_Line_SysCfg=Line3;    EXTI_Line=EXTI3;   break;
		case PIN4:
			EXTI_Line_IRQ=EXTI4_IRQ;       EXTI_Line_SysCfg=Line4;    EXTI_Line=EXTI4;   break;
		case PIN5:
			EXTI_Line_IRQ=EXTI9_5_IRQ;     EXTI_Line_SysCfg=Line5;    EXTI_Line=EXTI5;   break;
		case PIN6:
			EXTI_Line_IRQ=EXTI9_5_IRQ;     EXTI_Line_SysCfg=Line6;    EXTI_Line=EXTI6;   break;
		case PIN7:
			EXTI_Line_IRQ=EXTI9_5_IRQ;     EXTI_Line_SysCfg=Line7;    EXTI_Line=EXTI7;   break;
		case PIN8:
			EXTI_Line_IRQ=EXTI9_5_IRQ;     EXTI_Line_SysCfg=Line8;    EXTI_Line=EXTI8;   break;
		case PIN9:
			EXTI_Line_IRQ=EXTI9_5_IRQ;     EXTI_Line_SysCfg=Line9;    EXTI_Line=EXTI9;   break;
		case PIN10:
			EXTI_Line_IRQ=EXTI15_10_IRQ;   EXTI_Line_SysCfg=Line10;   EXTI_Line=EXTI10;   break;
		case PIN11:
			EXTI_Line_IRQ=EXTI15_10_IRQ;   EXTI_Line_SysCfg=Line11;   EXTI_Line=EXTI11;   break;
		case PIN12:
			EXTI_Line_IRQ=EXTI15_10_IRQ;   EXTI_Line_SysCfg=Line12;   EXTI_Line=EXTI12;   break;
		case PIN13:
			EXTI_Line_IRQ=EXTI15_10_IRQ;   EXTI_Line_SysCfg=Line13;   EXTI_Line=EXTI13;   break;
		case PIN14:
			EXTI_Line_IRQ=EXTI15_10_IRQ;   EXTI_Line_SysCfg=Line14;   EXTI_Line=EXTI14;   break;
		case PIN15:
			EXTI_Line_IRQ=EXTI15_10_IRQ;   EXTI_Line_SysCfg=Line15;   EXTI_Line=EXTI15;   break;
	}

	/*Enabling clock on AFIO peripheral*/
	RCC_u8APB_2_EnableClk(AFIO_EN);
	/*Configuring the external interrupt pin*/
	PinConfig_t EXT_Pin=
	{
		.Port=EXT_PORT,
		.PinNum=EXT_PIN,
		.Mode=INPUT,
		.CNF_InputMode=INPUT_PU_OR_PD,
	};
	GPIO_u8PinInit(&EXT_Pin);
	/*Making it as Input Pull-up*/
	GPIO_u8SetPinValue(EXT_PORT, EXT_PIN, PIN_HIGH);

	/*Configuring the MOSI pin*/
	PinConfig_t SPI_MOSI=
	{
		.Mode=INPUT,
		.Port=SPI_MOSI_PORT,
		.PinNum=SPI_MOSI_PIN,
		.CNF_InputMode=FLOATING_INPUT,
	};
	GPIO_u8PinInit(&SPI_MOSI);

	/*Configuring the SCK pin*/
	PinConfig_t SPI_SCK=
	{
		.Mode=INPUT,
		.Port=SPI_SCK_PORT,
		.PinNum=SPI_SCK_PIN,
		.CNF_InputMode=FLOATING_INPUT,
	};
	GPIO_u8PinInit(&SPI_SCK);

	/*Configuring the SPI peripheral*/
	SPIConfig_t SPI_Config=
	 {
		.SPI=RECEIVE_DATA_SPI,
		.DataFrame=SPI_8_BITS,
		.First_LSB=MSB_FIRST,
		.Master=SPI_SLAVE,
		.SW_SlvMng=SW_SLV_MNG_ENABLE,
		.Prescaler=FCLK_256
	 };
	SPI_voidInit(&SPI_Config);
	/*making my self a slave*/
	SPI_SW_NSS_Pin(RECEIVE_DATA_SPI, SW_NSS_LOW);
	/*Enabling SPI interrupt*/
	SPI_Enable(RECEIVE_DATA_SPI);

	/*Configuring the external interrupt pin to be interrupted on falling edges*/
	EXTIConfig_t EX_lineConfig=
	{
		.Edge=FALLING_EDGE,
		.Line=EXTI_Line,
		.Mask=EXTI_UNMASKED,
		.FPtr=ReceiveData_DoInstruction
	};
	EXTI_voidLineConfig(&EX_lineConfig);
	/*Setting the value of the line on the AFIO peripheral*/
	GPIO_u8SetEXTIPort(EXTI_Line_SysCfg , EXT_PORT);
	/*Enable this line on EXTI*/
	EXTI_voidEnableLine(EXTI_Line);

	/*Enabling global interrupt of the SPI peripheral*/
	NVIC_EnableInterrupt(ReceDataSPI_IRQ);
	/*Enabling global interrupt of the used line of EXTI peripheral*/
	NVIC_EnableInterrupt(EXTI_Line_IRQ);
	/*Enabling receiving data over SPI via interrupt, received data will be loaded to the
	 *NowTime_Struct struct and when it finished it will restart it self to keep receiving
	 *new data bytes*/
	SPI_ReceiveInterruptEnable(RECEIVE_DATA_SPI, &(NowTime_Struct.NowTimeSEC), RECEIVE_TIME_BYTES, CIRCULAR_ENABLE);
}

/***********************************************************
* @fn ReceiveData_DoInstruction
* @Brief This function will be called when an interrupt occurs on the external interrupt pin
* @Param void
* @retval void
***********************************************************/
static void ReceiveData_DoInstruction(void)
{
	/*Stop receiving data over interrupt*/
	SPI_ReceiveInterruptDisable(RECEIVE_DATA_SPI);

	/*Receiving the last byte of data was stored in the master buffer*/
	SPI_ReceiveSync(RECEIVE_DATA_SPI, &Rece_Ins);
	/*Receiving the number of the instruction wanted to be executed now*/
	SPI_ReceiveSync(RECEIVE_DATA_SPI, &Rece_Ins);

	/*If the function wanted to be run is to alert for an alarm*/
	if(Rece_Ins==ALARM_ON_INS)
	{
		/*Making a string to hold the received name but of 16Bit step size to be suitable with the SPI 16Bit reception*/
		uint16_t AlarmNameReceived[ALARM_LETTERS_NUM+1];
		/*Loop till you reach the end of the accepted number of letters for an alarm name*/
		for(uint8_t i=0; i<ALARM_LETTERS_NUM; i++)
		{
			/*Receiving the next letter*/
			SPI_ReceiveSync(RECEIVE_DATA_SPI, &AlarmNameReceived[i]);
			/*Saving it to the global variable*/
			AlarmName[i]=(int8_t)AlarmNameReceived[i];
			/*If the last received letter was the NULL operator*/
			if(AlarmName[i]=='\0') 	 break;
		}
	}
	/*Re-Enabling receiving data over SPI via interrupt*/
	SPI_ReceiveInterruptEnable(RECEIVE_DATA_SPI, &(NowTime_Struct.NowTimeSEC), RECEIVE_TIME_BYTES, CIRCULAR_ENABLE);
}





