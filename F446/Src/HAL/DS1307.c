/***********************************************************
* @file DS1307.c
* @Author Abdullah AlsharQawy
* @Brief The main file for the real time clock driver RTC
***********************************************************/

#include <stdint.h>
#include <ErrType.h>

#include <I2C_Interface.h>
#include <GPIO_Interface.h>
#include <DMA_Interface.h>
#include <RCC_Interface.h>
#include <NVIC_Interface.h>
#include <RTC_Wrapper.h>

#include <DS1307_Interface.h>
#include <DS1307_prv.h>
#include <DS1307_cfg.h>


/**********************************		GLOBAL VARIABLES	 ********************************/
static DS_Time_t DS_Time;
static 	NVIC_IRQ_t I2C_EV_IRQ, I2C_ER_IRQ;


/***********************************************************
* @fn DS1307_voidInit
* @brief Initializing the I2C peripheral connected to the DS1307 RTC
* @param[in] OwnAddress : The address of the I2C peripheral in the network
* @param[in] F_SCL_HZ : The frequency of the communication clock in the bus
* @retval void
***********************************************************/
void DS1307_Init(uint8_t OwnAddress, uint32_t F_SCL_HZ)
{
	/*Enabling clock at GPIO peripheral of the SDA pin*/
	switch(DS_SDA_PORT)
	{
		case PORTA:
			RCC_AHB1EnableClock(AHB1_GPIOA);
			break;
		case PORTB:
			RCC_AHB1EnableClock(AHB1_GPIOB);
			break;
		case PORTC:
			RCC_AHB1EnableClock(AHB1_GPIOC);
			break;
		case PORTD:
			RCC_AHB1EnableClock(AHB1_GPIOD);
			break;
		case PORTE:
			RCC_AHB1EnableClock(AHB1_GPIOE);
			break;
		case PORTF:
			RCC_AHB1EnableClock(AHB1_GPIOF);
			break;
		case PORTG:
			RCC_AHB1EnableClock(AHB1_GPIOG);
			break;
		case PORTH:
			RCC_AHB1EnableClock(AHB1_GPIOH);
			break;
	}
	/*Enabling clock at GPIO peripheral of the SCL pin*/
	switch(DS_SCL_PORT)
	{
		case PORTA:
			RCC_AHB1EnableClock(AHB1_GPIOA);
			break;
		case PORTB:
			RCC_AHB1EnableClock(AHB1_GPIOB);
			break;
		case PORTC:
			RCC_AHB1EnableClock(AHB1_GPIOC);
			break;
		case PORTD:
			RCC_AHB1EnableClock(AHB1_GPIOD);
			break;
		case PORTE:
			RCC_AHB1EnableClock(AHB1_GPIOE);
			break;
		case PORTF:
			RCC_AHB1EnableClock(AHB1_GPIOF);
			break;
		case PORTG:
			RCC_AHB1EnableClock(AHB1_GPIOG);
			break;
		case PORTH:
			RCC_AHB1EnableClock(AHB1_GPIOH);
			break;
	}
	/*Enabling clock at DMA peripheral*/
	switch(DS_DMA_RX)
	{
		case DMA_1:
			RCC_AHB1EnableClock(AHB1_DMA1);
			break;
		case DMA_2:
			RCC_AHB1EnableClock(AHB1_DMA2);
			break;
	}

	/*Configuring the SDA pin at GPIO peripheral*/
	PinConfig_t SDA_Config=
	{
		.Port=DS_SDA_PORT,
		.Pin=DS_SDA_PIN,
		.Mode=ALTERNATE_FUNCTION,
		.Speed=LOW_SPEED,
		.OutputType=OPEN_DRAIN,
		.PullType=PULL_UP,
		.AltFunc=DS_ALT_FUNC
	};
	GPIO_u8PinInit(&SDA_Config);

	/*Configuring the SCL pin at GPIO peripheral*/
	PinConfig_t SCL_Config=
	{
		.Port=DS_SCL_PORT,
		.Pin=DS_SCL_PIN,
		.Mode=ALTERNATE_FUNCTION,
		.Speed=LOW_SPEED,
		.OutputType=OPEN_DRAIN,
		.PullType=PULL_UP,
		.AltFunc=DS_ALT_FUNC
	};
	GPIO_u8PinInit(&SCL_Config);

	/*Enabling clock at the I2C peripheral*/
	switch(DS_I2C)
	{
		case I2C_1:
			RCC_APB1EnableClock(APB1_I2C1);
			I2C_EV_IRQ=I2C1_EV_IRQ;
			I2C_ER_IRQ=I2C1_ER_IRQ;
			break;
		case I2C_2:
			RCC_APB1EnableClock(APB1_I2C2);
			I2C_EV_IRQ=I2C2_EV_IRQ;
			I2C_ER_IRQ=I2C2_ER_IRQ;
			break;
		case I2C_3:
			RCC_APB1EnableClock(APB1_I2C3);
			I2C_EV_IRQ=I2C3_EV_IRQ;
			I2C_ER_IRQ=I2C3_ER_IRQ;
			break;
	}

	/*Configuring the I2C peripheral*/
	I2C_Config_t DS_I2C_Cfg=
	{
		.I2C=DS_I2C,
		.Own_Address=OwnAddress,
		.GeneralCall=GCALL_DISABLE,
		.SCL_Freq_HZ=F_SCL_HZ,
		.Mode=SM
	};
	I2C_voidInit(&DS_I2C_Cfg);

	/*Configuring the DMA peripheral*/
	DMAStreamConfig_t DS_DMA_RX_Cfg=
	{
		.DMA=DS_DMA_RX,
		.Stream=DS_RX_STREAM,
		.Channel=DS_RX_CHANNEL,
		.Mode=DMA_DIRECT,
		.FIFO_Threshold=FIFO_1_4,
		.Direction=PER_TO_MEM,
		.Per_Inc=FIXED_PER_ADDRESS,
		.Mem_Inc=INCREMENT_MEM_ADDRESS,
		.Priority=ST_PRIORITY_MEDIUM,
		.Itmes_Size=DS_RECEIVE_BYTES,
		.Per_Address=(uint32_t*)I2C_DataRegisterAddress(DS_I2C),
		.Mem_Address=(uint8_t*)(&DS_Time.Seconds),
		.Mem_Size=MEMSIZE_BYTE,
		.Per_Size=PERSIZE_BYTE,
		.Circular_Mode=DMA_CIRCULAR_ENABLE,
		.Fptr=DMA_Master_CallBack_I2C3
	};
	DMA_StreamInit(&DS_DMA_RX_Cfg);
}

/***********************************************************
* @fn DS1307_Enable_RX
* @brief Starting communication with DS1307 RTC through DMA to get current time
* @param[in] TimeOut : Run time out for protection from blocking
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t DS1307_Enable_RX(uint32_t TimeOut)
{
	ErrorStatus_t ErrorState=OK;

	/*Enabling I2C peripheral*/
	I2C_Enable(DS_I2C);

	/*Initializing a variable with a value of zero*/
	uint8_t Local_u8ZeroVariable=0;
	/*Sending one byte first of value zero without a stop bit to reset the DS1307
	  pointer to make it points to the first byte, next start bit will be a repeated start*/
	ErrorState=I2C_RepeatedStartSendSynch(DS_I2C, DS_SLAVE_ADDRESS, &Local_u8ZeroVariable, 1, TimeOut);

	/*Checking for Timeout*/
	if(ErrorState!=RUNTIME_OUT)
	{
		/*Enabling NVIC event interrupt*/
		NVIC_EnableInterrupt(I2C_EV_IRQ);
		/*Enabling NVIC error interrupt*/
		NVIC_EnableInterrupt(I2C_ER_IRQ);
		/*Enabling NVIC interrupt of the used DMA stream*/
		NVIC_EnableInterrupt(DS_DMA_STREAM_NVIC_IRQ_RX);

		/*Enabling DMA stream*/
		DMA_StreamEnable(DS_DMA_RX, DS_RX_STREAM);
		/*Enabling full transfer interrupt of DMA*/
		DMA_FullTransfer_InterruptEnable(DS_DMA_RX, DS_RX_STREAM);
		/*Enabling DMA receiving using DMA by sending a repeated start*/
		ErrorState=I2C_EnableMasterDMA(DS_I2C, DS_SLAVE_ADDRESS, I2C_READ, TimeOut);
	}
	/*Checking for Timeout*/
	if(ErrorState==RUNTIME_OUT)
	{
		/*Terminate communication*/
		DS1307_Disable_RX();
	}

	return ErrorState;
}

/***********************************************************
* @fn DS1307_Disable_RX
* @brief Terminate communication with DS1307 RTC
* @param void
* @retval void
***********************************************************/
void DS1307_Disable_RX(void)
{
	/*Disabling I2C peripheral*/
	I2C_Disable(DS_I2C);
	/*Disabling NVIC event interrupt*/
	NVIC_DisableInterrupt(I2C_EV_IRQ);
	/*Disabling NVIC error interrupt*/
	NVIC_DisableInterrupt(I2C_ER_IRQ);
	/*Disabling NVIC interrupt of the used DMA stream*/
	NVIC_DisableInterrupt(DS_DMA_STREAM_NVIC_IRQ_RX);

	/*Disabling DMA stream*/
	DMA_StreamDisable(DS_DMA_RX, DS_RX_STREAM);
	/*Disabling full transfer interrupt of DMA*/
	DMA_FullTransfer_InterruptDisable(DS_DMA_RX, DS_RX_STREAM);
	/*Disabling DMA receiving using DMA*/
	I2C_DisableDMA(DS_I2C);
}

/***********************************************************
* @fn DS1307_TimeSetting_Init
* @brief Initializing the I2C peripheral connected to the DS1307 to adjust it time
*        Use this function only at very first time to adjust the time!
* @param[in] OwnAddress : The address of the I2C peripheral in the network
* @param[in] F_SCL_HZ : The frequency of the communication clock in the bus
* @retval void
***********************************************************/
void DS1307_TimeSetting_Init(uint8_t OwnAddress, uint32_t F_SCL_HZ)
{
	/*Enabling clock at GPIO peripheral of the SDA pin*/
	switch(DS_SDA_PORT)
	{
		case PORTA:
			RCC_AHB1EnableClock(AHB1_GPIOA);
			break;
		case PORTB:
			RCC_AHB1EnableClock(AHB1_GPIOB);
			break;
		case PORTC:
			RCC_AHB1EnableClock(AHB1_GPIOC);
			break;
		case PORTD:
			RCC_AHB1EnableClock(AHB1_GPIOD);
			break;
		case PORTE:
			RCC_AHB1EnableClock(AHB1_GPIOE);
			break;
		case PORTF:
			RCC_AHB1EnableClock(AHB1_GPIOF);
			break;
		case PORTG:
			RCC_AHB1EnableClock(AHB1_GPIOG);
			break;
		case PORTH:
			RCC_AHB1EnableClock(AHB1_GPIOH);
			break;
	}
	/*Enabling clock at GPIO peripheral of the SCL pin*/
	switch(DS_SCL_PORT)
	{
		case PORTA:
			RCC_AHB1EnableClock(AHB1_GPIOA);
			break;
		case PORTB:
			RCC_AHB1EnableClock(AHB1_GPIOB);
			break;
		case PORTC:
			RCC_AHB1EnableClock(AHB1_GPIOC);
			break;
		case PORTD:
			RCC_AHB1EnableClock(AHB1_GPIOD);
			break;
		case PORTE:
			RCC_AHB1EnableClock(AHB1_GPIOE);
			break;
		case PORTF:
			RCC_AHB1EnableClock(AHB1_GPIOF);
			break;
		case PORTG:
			RCC_AHB1EnableClock(AHB1_GPIOG);
			break;
		case PORTH:
			RCC_AHB1EnableClock(AHB1_GPIOH);
			break;
	}

	/*Configuring the SDA pin at GPIO peripheral*/
	PinConfig_t SDA_Config=
	{
		.Port=DS_SDA_PORT,
		.Pin=DS_SDA_PIN,
		.Mode=ALTERNATE_FUNCTION,
		.Speed=LOW_SPEED,
		.OutputType=OPEN_DRAIN,
		.PullType=PULL_UP,
		.AltFunc=DS_ALT_FUNC
	};
	GPIO_u8PinInit(&SDA_Config);

	/*Configuring the SCL pin at GPIO peripheral*/
	PinConfig_t SCL_Config=
	{
		.Port=DS_SCL_PORT,
		.Pin=DS_SCL_PIN,
		.Mode=ALTERNATE_FUNCTION,
		.Speed=LOW_SPEED,
		.OutputType=OPEN_DRAIN,
		.PullType=PULL_UP,
		.AltFunc=DS_ALT_FUNC
	};
	GPIO_u8PinInit(&SCL_Config);

	/*Enabling clock at the I2C peripheral*/
	switch(DS_I2C)
	{
		case I2C_1:
			RCC_APB1EnableClock(APB1_I2C1);
			break;
		case I2C_2:
			RCC_APB1EnableClock(APB1_I2C2);
			break;
		case I2C_3:
			RCC_APB1EnableClock(APB1_I2C3);
			break;
	}

	/*Configuring the I2C peripheral*/
	I2C_Config_t DS_I2C_Cfg=
	{
		.I2C=DS_I2C,
		.Own_Address=OwnAddress,
		.GeneralCall=GCALL_DISABLE,
		.SCL_Freq_HZ=F_SCL_HZ,
		.Mode=SM
	};
	I2C_voidInit(&DS_I2C_Cfg);
}

/***********************************************************
* @fn DS1307_RunTimeSetting
* @brief Starting adjusting the DS1307 RTC time, depending on the values given at DS1307_cfg.h.
* 		 Use this function only at very first time to adjust the time!
* @param[in] TimeOut : Run time out for protection from blocking
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t DS1307_RunTimeSetting(DS_Time_t SetTime, DS1307_AmPm_t AmPM, DS1307_Style_t HourStyle, uint32_t TimeOut)
{
	ErrorStatus_t ErrorState=OK;

	/*Adjusting the time data provided by the user in the DS1307_cfg.h file to be readable by
	  The RTC driver as provided in the dataSheet*/
	DS_Time_t NowTime=
	{
		.PointerRegister=0,
		.Seconds=(SetTime.Seconds%10)|((SetTime.Seconds/10)<<4),
		.Minutes=(SetTime.Minutes%10)|((SetTime.Minutes/10)<<4),
		.Hours=(NOW_HOURS_STYLE==STYELE_12H)?\
			   (SetTime.Hours%10)|((SetTime.Hours/10)<<4)|(AmPM<<5)|(STYELE_12H<<6):\
			   (SetTime.Hours%10)|((SetTime.Hours/10)<<4),
		.Day=SetTime.Day,
		.Date=(SetTime.Date%10)|((SetTime.Date/10)<<4),
		.Month=(SetTime.Month%10)|((SetTime.Month/10)<<4),
		.Year=((SetTime.Year)%10)|(((SetTime.Year)/10)<<4)
	};

	/*Enabling I2C peripheral*/
	I2C_Enable(DS_I2C);
	/*Star transmitting time to RTC to adjust its time*/
	ErrorState=I2C_MasterTransmitSynch(DS_I2C,  DS_SLAVE_ADDRESS, (uint8_t*)&NowTime, DS_TRANSMIT_BYTES, TimeOut);
	/*Disabling I2C peripheral*/
	I2C_Disable(DS_I2C);

	return ErrorState;
}

/***********************************************************
* @fn DS1307_GetNowTime
* @brief Returning the time now for the chosen time type
* @param[in] TimeType : The type of time wanted, Options at @NowTime_t
* @param[out] NowTime : The time now of the chosen time type
* @param[out] Now_pm_am : Am or Pm, only when 12H style is used, Options at @Now_AM_PM_t
* @retval ErrorStatus_t, Options at @ErrorStatus_t enum
***********************************************************/
ErrorStatus_t DS1307_GetNowTime(NowTime_t TimeType, uint16_t* NowTime, uint16_t* Now_pm_am)
{
	ErrorStatus_t ErrorState=UNKNOWN;

	/*Checking on the NowTime and Now_pm_am pointers*/
	if(NowTime==NullPtr || Now_pm_am==NullPtr)
	{
		ErrorState=NULLPTR;
	}
	/*Checking on the TimeType value*/
	else if(TimeType>NOW_TIME_YEAR)
	{
		ErrorState=OUT_OF_RANGE;
	}
	else
	{
		/*Making pointer to the time struct to step over it using index*/
		uint8_t* DS_TimePtr=(uint8_t*)&DS_Time;
		/*checking if the time style was 12H*/
		if((TimeType==NOW_TIME_HOURS) && (NOW_HOURS_STYLE==STYELE_12H))
		{
			/*Returning the value whether it was Am or Pm*/
			*Now_pm_am=((DS_TimePtr[TimeType])>>5)&1;
			/*Clearing the Am_Pm and 12/24 time style bits to not get them into calculation of time*/
			DS_TimePtr[TimeType]&=~(0b1<<5);
			DS_TimePtr[TimeType]&=~(0b1<<6);
		}

		/*Retrieving the time values to its normal form*/
		*NowTime=((DS_TimePtr[TimeType]&0x0F) + ((DS_TimePtr[TimeType]>>4)*10));

		ErrorState=OK;
	}

	return ErrorState;
}








