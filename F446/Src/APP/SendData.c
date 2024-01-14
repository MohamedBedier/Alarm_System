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
			RCC_AHB1EnableClock(AHB1_GPIOA);     break;
		case PORTB:
			RCC_AHB1EnableClock(AHB1_GPIOB);     break;
		case PORTC:
			RCC_AHB1EnableClock(AHB1_GPIOC);     break;
		case PORTD:
			RCC_AHB1EnableClock(AHB1_GPIOD);     break;
		case PORTE:
			RCC_AHB1EnableClock(AHB1_GPIOE);     break;
		case PORTF:
			RCC_AHB1EnableClock(AHB1_GPIOF);     break;
		case PORTG:
			RCC_AHB1EnableClock(AHB1_GPIOG);     break;
		case PORTH:
			RCC_AHB1EnableClock(AHB1_GPIOH);     break;
	}
	/*Enabling clock on the port of the SPI SCK pin*/
	switch(SPI_SCK_PORT)
	{
		case PORTA:
			RCC_AHB1EnableClock(AHB1_GPIOA);     break;
		case PORTB:
			RCC_AHB1EnableClock(AHB1_GPIOB);     break;
		case PORTC:
			RCC_AHB1EnableClock(AHB1_GPIOC);     break;
		case PORTD:
			RCC_AHB1EnableClock(AHB1_GPIOD);     break;
		case PORTE:
			RCC_AHB1EnableClock(AHB1_GPIOE);     break;
		case PORTF:
			RCC_AHB1EnableClock(AHB1_GPIOF);     break;
		case PORTG:
			RCC_AHB1EnableClock(AHB1_GPIOG);     break;
		case PORTH:
			RCC_AHB1EnableClock(AHB1_GPIOH);     break;
	}
	/*Enabling clock on the port of the EXTI pin*/
	switch(EXT_PORT)
	{
		case PORTA:
			RCC_AHB1EnableClock(AHB1_GPIOA);     break;
		case PORTB:
			RCC_AHB1EnableClock(AHB1_GPIOB);     break;
		case PORTC:
			RCC_AHB1EnableClock(AHB1_GPIOC);     break;
		case PORTD:
			RCC_AHB1EnableClock(AHB1_GPIOD);     break;
		case PORTE:
			RCC_AHB1EnableClock(AHB1_GPIOE);     break;
		case PORTF:
			RCC_AHB1EnableClock(AHB1_GPIOF);     break;
		case PORTG:
			RCC_AHB1EnableClock(AHB1_GPIOG);     break;
		case PORTH:
			RCC_AHB1EnableClock(AHB1_GPIOH);     break;
	}

	NVIC_IRQ_t SendDataSPI_IRQ;
	/*Enabling clock on the the SPI peripheral*/
	switch(SEND_DATA_SPI)
	{
		case SPI_1:
			RCC_APB2EnableClock(APB2_SPI1);
			SendDataSPI_IRQ=SPI1_IRQ;
			break;
		case SPI_2:
			RCC_APB1EnableClock(APB1_SPI2);
			SendDataSPI_IRQ=SPI2_IRQ;
			break;
		case SPI_3:
			RCC_APB1EnableClock(APB1_SPI2);
			SendDataSPI_IRQ=SPI3_IRQ;
			break;
		case SPI_4:
			RCC_APB2EnableClock(APB2_SPI4);
			SendDataSPI_IRQ=SPI4_IRQ;
			break;
	}

	/*Configuring the MOSI pin*/
	PinConfig_t SPI_MOSI=
	{
		.Port=SPI_MOSI_PORT,
		.Pin=SPI_MOSI_PIN,
		.AltFunc=SPI_ALT_FUNC,
		.Mode=ALTERNATE_FUNCTION,
		.OutputType=PUSH_PULL,
		.PullType=NO_PULL,
		.Speed=LOW_SPEED,
	};
	GPIO_u8PinInit(&SPI_MOSI);

	/*Configuring the SCK pin*/
	PinConfig_t SPI_SCK=
	{
		.Port=SPI_SCK_PORT,
		.Pin=SPI_SCK_PIN,
		.AltFunc=SPI_ALT_FUNC,
		.Mode=ALTERNATE_FUNCTION,
		.OutputType=PUSH_PULL,
		.PullType=NO_PULL,
		.Speed=LOW_SPEED,
	};
	GPIO_u8PinInit(&SPI_SCK);

	/*Configuring the EXTI pin*/
	PinConfig_t EXT_Pin=
	{
		.Port=EXT_PORT,
		.Pin=EXT_PIN,
		.Mode=OUTPUT,
		.OutputType=OPEN_DRAIN,
		.PullType=NO_PULL,
		.Speed=LOW_SPEED,
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


