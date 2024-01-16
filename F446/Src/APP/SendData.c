/***********************************************************
* @file SendData.c
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
#include <SysTick_Interface.h>
#include <GetTime.h>
#include <DoTasks_cfg.h>
#include <SendData.h>
#include <SendData_cfg.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
extern NowTimeStruct_t NowTime_Struct;
extern char* AlarmName;


/***********************************************************
* @fn SendData_Init
* @brief Function for initiation of the SPI peripheral and the pin connected to the external interrupt of the other MCU
* @param void
* @retval void
***********************************************************/
void SendData_Init(void)
{
	/*Enabling clock on the port of the SPI MOSI pin*/
	switch(SPI_MOSI_PORT)
	{
		case PORTA:
			RCC_u8AHB_1_EnableClk(GPIOA_EN);     break;
		case PORTB:
			RCC_u8AHB_1_EnableClk(GPIOB_EN);     break;
		case PORTC:
			RCC_u8AHB_1_EnableClk(GPIOC_EN);     break;
		case PORTD:
			RCC_u8AHB_1_EnableClk(GPIOD_EN);     break;
		case PORTE:
			RCC_u8AHB_1_EnableClk(GPIOE_EN);     break;
		case PORTF:
			RCC_u8AHB_1_EnableClk(GPIOF_EN);     break;
		case PORTG:
			RCC_u8AHB_1_EnableClk(GPIOG_EN);     break;
		case PORTH:
			RCC_u8AHB_1_EnableClk(GPIOH_EN);     break;
	}
	/*Enabling clock on the port of the SPI SCK pin*/
	switch(SPI_SCK_PORT)
	{
		case PORTA:
			RCC_u8AHB_1_EnableClk(GPIOA_EN);     break;
		case PORTB:
			RCC_u8AHB_1_EnableClk(GPIOB_EN);     break;
		case PORTC:
			RCC_u8AHB_1_EnableClk(GPIOC_EN);     break;
		case PORTD:
			RCC_u8AHB_1_EnableClk(GPIOD_EN);     break;
		case PORTE:
			RCC_u8AHB_1_EnableClk(GPIOE_EN);     break;
		case PORTF:
			RCC_u8AHB_1_EnableClk(GPIOF_EN);     break;
		case PORTG:
			RCC_u8AHB_1_EnableClk(GPIOG_EN);     break;
		case PORTH:
			RCC_u8AHB_1_EnableClk(GPIOH_EN);     break;
	}
	/*Enabling clock on the port of the EXTI pin*/
	switch(EXT_PORT)
	{
		case PORTA:
			RCC_u8AHB_1_EnableClk(GPIOA_EN);     break;
		case PORTB:
			RCC_u8AHB_1_EnableClk(GPIOB_EN);     break;
		case PORTC:
			RCC_u8AHB_1_EnableClk(GPIOC_EN);     break;
		case PORTD:
			RCC_u8AHB_1_EnableClk(GPIOD_EN);     break;
		case PORTE:
			RCC_u8AHB_1_EnableClk(GPIOE_EN);     break;
		case PORTF:
			RCC_u8AHB_1_EnableClk(GPIOF_EN);     break;
		case PORTG:
			RCC_u8AHB_1_EnableClk(GPIOG_EN);     break;
		case PORTH:
			RCC_u8AHB_1_EnableClk(GPIOH_EN);     break;
	}

	NVIC_IRQ_t SendDataSPI_IRQ;
	/*Enabling clock on the the SPI peripheral*/
	switch(SEND_DATA_SPI)
	{
		case SPI_1:
			RCC_u8APB_2_EnableClk(SPI1_EN);
			SendDataSPI_IRQ=SPI1_IRQ;
			break;
		case SPI_2:
			RCC_u8APB_1_EnableClk(SPI2_EN);
			SendDataSPI_IRQ=SPI2_IRQ;
			break;
		case SPI_3:
			RCC_u8APB_1_EnableClk(SPI3_EN);
			SendDataSPI_IRQ=SPI3_IRQ;
			break;
		case SPI_4:
			RCC_u8APB_2_EnableClk(SPI4_EN);
			SendDataSPI_IRQ=SPI4_IRQ;
			break;
	}

	/*Configuring the MOSI pin*/
	PinConfig_t SPI_MOSI=
	{
		.Port=SPI_MOSI_PORT,
		.PinNum=SPI_MOSI_PIN,
		.Mode=ALTERNATE_FUNCTION,
		.Speed=LOW,
		.OutputType=PUSH_PULL,
		.PullType=NOPULL,
		.AltFunc=SPI_ALT_FUNC
	};
	GPIO_u8PinInit(&SPI_MOSI);

	/*Configuring the SCK pin*/
	PinConfig_t SPI_SCK=
	{
		.Port=SPI_SCK_PORT,
		.PinNum=SPI_SCK_PIN,
		.Mode=ALTERNATE_FUNCTION,
		.Speed=LOW,
		.OutputType=PUSH_PULL,
		.PullType=NOPULL,
		.AltFunc=SPI_ALT_FUNC
	};
	GPIO_u8PinInit(&SPI_SCK);

	/*Configuring the EXTI pin*/
	PinConfig_t EXT_Pin=
	{
		.Port=EXT_PORT,
		.PinNum=EXT_PIN,
		.Mode=OUTPUT,
		.Speed=LOW,
		.OutputType=OPEN_DRAIN,
		.PullType=NOPULL,
	};
	GPIO_u8PinInit(&EXT_Pin);
	/*Starting it with high as we will make in the other MCU as pull-up*/
	GPIO_u8SetPinValue(EXT_PORT, EXT_PIN, PIN_HIGH);

	/*Configuring the SPI peripheral*/
	SPIConfig_t SPI_Config=
	{
		.SPI=SEND_DATA_SPI,
		.DataFrame=SPI_8_BITS,
		.First_LSB=MSB_FIRST,
		.Master=SPI_MASTER,
		.SW_SlvMng=SW_SLV_MNG_ENABLE,
		.Prescaler=FCLK_256
	};
	SPI_voidInit(&SPI_Config);
	/*Making it master*/
	SPI_SW_NSS_Pin(SEND_DATA_SPI, SW_NSS_HIGH);
	/*Enabling SPI peripheral*/
	SPI_Enable(SEND_DATA_SPI);
	/*Enabling the  global interrupt of the SPI*/
	NVIC_EnableInterrupt(SendDataSPI_IRQ);
}

/***********************************************************
* @fn SendData_Runnable
* @brief Function used to start sending data to the other MCU over SPI
* @param void
* @retval void
***********************************************************/
void SendData_Runnable(void)
{
	/*Enabling transmitting data over SPI interrupt*/
	SPI_TransmitInterruptEnable(SEND_DATA_SPI, &(NowTime_Struct.NowTimeSEC), TRANSMIT_TIME_BYTES, CIRCULAR_DISABLE);
}

/***********************************************************
* @fn SendData_TransmitInstruction
* @brief Function used to send instruction to the other MCU
* @param[in] : Trans_Ins the wanted instruction to be sent to the other MCU, Options at @TransInstruc_t enum
* @retval void
***********************************************************/
void SendData_TransmitInstruction(TransInstruc_t Trans_Ins)
{
	/*Waiting some time to make sure that the last data bytes have been received*/
	SysTick_Delayms(10);
	/*Giving signal to the other MCU to show that I am going to send an instruction*/
    GPIO_u8SetPinValue(EXT_PORT, EXT_PIN, PIN_LOW);
    /*Waiting till the other MCU gets notificated*/
    SysTick_Delayus(10);
    /*Bring the EXTI pin to normal state*/
    GPIO_u8SetPinValue(EXT_PORT, EXT_PIN, PIN_HIGH);

    uint16_t TransInsPtr=(uint16_t)Trans_Ins;
    /*Sending last data was in the buffer*/
	SPI_SendSync(SEND_DATA_SPI, TransInsPtr); ///////////////////
	/*Sending the needed instruction*/
	SPI_SendSync(SEND_DATA_SPI, TransInsPtr);

	/*If the sent instruction was to alert for an alarm*/
	if(Trans_Ins==ALARM_ON_INS)
	{
		/*Loop over the alarm name letters to send them to the other MCU*/
		for(uint8_t i=0; ; i++)
		{
			/*Waiting some time to not overwrite on the buffer*/
			SysTick_Delayus(10);
			/*Send next letter*/
			SPI_SendSync(SEND_DATA_SPI, AlarmName[i]);
			/*Stop sending if the last data you sent was the null operator*/
			if(AlarmName[i]=='\0') 	 break;
		}
		/*Waiting some time to not overwrite on the buffer*/
		SysTick_Delayus(10);
	}

	/*R-Enable transmitting data over SPI interrupt*/
	SPI_TransmitInterruptEnable(SEND_DATA_SPI, &(NowTime_Struct.NowTimeSEC), TRANSMIT_TIME_BYTES, CIRCULAR_DISABLE);
}


