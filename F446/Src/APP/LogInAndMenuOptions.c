/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: APP                                     **/
/** File Name : App.c                                       **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/

#include <LogInAndMenuOptions.h>
#include <stdint.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "Stm32F446xx.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "RCC_Interface.h"

NowTimeStruct_t NowTimeStruct_instance;

NowTimeStruct_t AlarmsArr[TOTAL_ALARMS];

char AlarmNamesArr[TOTAL_ALARMS][15] = {0};

/**
 * @brief: this function is used to send "Welcome to our project" to the user
 */
void  Welcome_Message(void)
{
	/* define of string array which carrying welcome message for the user */
	uint8_t Welcome_StringArr[] ="\n***************************************************************\n\
******************  Welcome To Our Project  *******************\n\
***************************************************************\n";

	/* this is a variable which carrying Welcome String array Length */
	uint8_t Welcome_StringDataLength= sizeof(Welcome_StringArr);

	/* Send to usart Welcome message array to display it on the screen */
	UART_u8SendBufferSynch(USART2_peri,Welcome_StringArr,Welcome_StringDataLength);

}

/**
 * @brief: this function is used to ask the User_ID and take it
 * 			note that : User_ID must consist of max 4 digits only
 * @return: this function will return User_ID
 */
uint32_t  AskAndTakeUserIdThenCheckIsValid(void)
{
	/* define a variable to carry the receiving data from the user */
	uint8_t Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
	/* define a variable to carry the final User_ID which sending from the user */
	uint32_t Local_u32ID_Digits= INIT_VALUE_BY_ZERO ;
	/* define a variable to count until max 4 digits of the User_ID */
	uint8_t Local_u8FourDigitID = INIT_VALUE_BY_ZERO ;

	/* define an array to ask the user to enter id */
	uint8_t AskId_StrArr[] = "Please,Enter your ID: ";

	/* define an array to Tell the user wrong id */
	uint8_t WrongID_StrArr[] = "\nSorry you entered wrong ID\n******  SYSTEM SHUTDOWN  ******\n";

	/* this is a variable which carrying ASK_ID String array Length */
	uint8_t AskId_StringDataLength= sizeof(AskId_StrArr);

	/* this is a variable which carrying WrongID String array Length */
	uint8_t WrongID_StringDataLength= sizeof(WrongID_StrArr);

	/* tell the user to enter ID */
	UART_u8SendBufferSynch(USART2_peri,AskId_StrArr,AskId_StringDataLength);

	/* looping until take 4 digits of User_ID */
	do{
		/* receive User_ID digits */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
		if(Local_u8ReceivedDataFromUser >= '1' && Local_u8ReceivedDataFromUser <= '9')
		{
			/* save the digit which taking from User */
			Local_u32ID_Digits = Local_u32ID_Digits * 10 + Local_u8ReceivedDataFromUser - '0';
		}

		/* increment Local_u8FourDigitID by 1 */
		Local_u8FourDigitID++;

	}while(Local_u8FourDigitID < MAX_ID_DIGITS); /* check on the User_ID digits */

	/* check on User ID is valid or not */
	if(Local_u32ID_Digits != 1234 && Local_u32ID_Digits != 5678)
	{
		/* tell the user wrong Id and shut down the system */
		UART_u8SendBufferSynch(USART2_peri,WrongID_StrArr,WrongID_StringDataLength);
		/* system shut down */
		SystemShutDown();
	}

	return Local_u32ID_Digits;
}


/**
 * @brief: this function is used to take the User_PassWord for max 3 times
 * @return: this function will return User_password
 */
uint32_t  ThreeTimesForPassWord(void)
{
	uint8_t  Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
	uint32_t Local_u32PasswordDigits= INIT_VALUE_BY_ZERO;
	uint8_t  Local_u8FourDigitPassword = INIT_VALUE_BY_ZERO;
	uint8_t  Local_u8TryCount = INIT_VALUE_BY_ZERO;

	/* define an array to Tell the user wrong PassWord And have 3 times only */
	uint8_t PWWrongTryAgain_StrArr[] = "\n\tSorry you entered wrong PassWord\n******  Try again you have 3 times only ******";

	/* define an array to Tell the user wrong PassWord */
	uint8_t PWWrongTryAgain1_StrArr[] = "\n\tSorry you entered wrong PassWord";

	/* define an array to ask the user to enter PassWord */
	uint8_t AskPassWord_StrArr[] = "\nPlease,Enter your PassWord: ";

	/* this is a variable which carrying ASK_ID String array Length */
	uint8_t WrongPW_TryAgain_StringDataLength= sizeof(PWWrongTryAgain_StrArr);

	/* this is a variable which carrying ASK_PassWord String array Length */
	uint8_t AskPassWord_StringDataLength= sizeof(AskPassWord_StrArr);

	uint8_t WrongPW_TryAgain1_StringDataLength= sizeof(PWWrongTryAgain1_StrArr);

	/* message for the user */
	UART_u8SendBufferSynch(USART2_peri,PWWrongTryAgain_StrArr,WrongPW_TryAgain_StringDataLength);
	UART_u8SendBufferSynch(USART2_peri,AskPassWord_StrArr,AskPassWord_StringDataLength);

	while(Local_u8TryCount < MAX_3TIMES_ENTERING_PASSWORD )
	{
		/* looping until take 4 digits */
		do{
			/* receive the next digit */
			USART_u8ReceiveData(USART2_peri, &Local_u8ReceivedDataFromUser);

			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '1' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u32PasswordDigits = Local_u32PasswordDigits * 10 + Local_u8ReceivedDataFromUser - '0';
			}

			/* increment Local_u8FourDigitID by 1 */
			Local_u8FourDigitPassword++;
		}while(Local_u8FourDigitPassword < MAX_PASSWORD_DIGITS);

		/* check if the user entered valid password or end the valid times */
		if (Local_u8TryCount == 3 || Local_u32PasswordDigits == 8765 || Local_u32PasswordDigits == 4321)
		{
			break;
		}
		/* increment Local_u8TryCount by one , in this case the user entered incorrect password */
		Local_u8TryCount++;

		if(Local_u8TryCount < MAX_3TIMES_ENTERING_PASSWORD)
		{
			UART_u8SendBufferSynch(USART2_peri,PWWrongTryAgain1_StrArr,WrongPW_TryAgain1_StringDataLength);
			UART_u8SendBufferSynch(USART2_peri,AskPassWord_StrArr,AskPassWord_StringDataLength);
		}
		/* re initiate these variables */
		Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
		Local_u32PasswordDigits= INIT_VALUE_BY_ZERO;
		Local_u8FourDigitPassword = INIT_VALUE_BY_ZERO;

	}
	return Local_u32PasswordDigits;
}

/**
 * @brief: this function is used to take the User_PassWord and it consists from 4 digits
 * @return: this function will return User_password
 */
uint32_t  TakeUserPassWord(void)
{
	/* define a variable to carry the receiving data from the user */
	uint8_t Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
	/* define a variable to carry the final User_PassWord which sending from the user */
	uint32_t  Local_u32PasswordDigits= INIT_VALUE_BY_ZERO ;
	/* define a variable to count until max 4 digits of the User_PassWord */
	uint8_t Local_u8FourDigitPassword = INIT_VALUE_BY_ZERO ;

	/* define an array to ask the user to enter PassWord */
	uint8_t AskPassWord_StrArr[] = "\nPlease,Enter your PassWord: ";

	/* define an array to Tell the user you finished 3 times */
	uint8_t WrongPW_3Times_StrArr[] = "\n\tSorry you entered 3 times wrong PassWord\n******  SYSTEM SHUTDOWN  ******";

	/* this is a variable which carrying WrongPW_3Times String array Length */
	uint8_t WrongPW_3Times_StringDataLength= sizeof(WrongPW_3Times_StrArr);

	/* this is a variable which carrying ASK_PassWord String array Length */
	uint8_t AskPassWord_StringDataLength= sizeof(AskPassWord_StrArr);

	/* tell the user to enter PassWord */
	UART_u8SendBufferSynch(USART2_peri,AskPassWord_StrArr,AskPassWord_StringDataLength);

	/* looping until take 4 digits */
	do{
		/* receive User_PassWord digits */
		USART_u8ReceiveData(USART2_peri, &Local_u8ReceivedDataFromUser);

		/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
		if(Local_u8ReceivedDataFromUser >= '1' && Local_u8ReceivedDataFromUser <= '9')
		{
			/* save the digit which taking from User */
			Local_u32PasswordDigits = Local_u32PasswordDigits * 10 + Local_u8ReceivedDataFromUser - '0';
		}

		/* increment Local_u8FourDigitID by 1 */
		Local_u8FourDigitPassword++;
	}while(Local_u8FourDigitPassword < MAX_PASSWORD_DIGITS);


	if(Local_u32PasswordDigits != 4321 && Local_u32PasswordDigits != 8765)
	{
		Local_u32PasswordDigits = ThreeTimesForPassWord();

		if(Local_u32PasswordDigits != 4321 && Local_u32PasswordDigits != 8765)
		{
			/*  Tell the user you finished 3 times and exti the system */
			UART_u8SendBufferSynch(USART2_peri,WrongPW_3Times_StrArr,WrongPW_3Times_StringDataLength);
			SystemShutDown();
		}
	}

	return Local_u32PasswordDigits;
}

/**
 * @brief : this function is used to Shut down our system by Disable usart2 clock in two cases
 * 			1st: if the user entered Incorrect ID.
 * 			2nd: if the user entered Incorrect password for 3 times not included the first one
 */
void  SystemShutDown(void)
{
	/* disable the peripheral clock */
	RCC_u8APB_1_DisableClk(USART2_EN);
}

/**
 * @brief: this function is used to show menu options
 */
void  ShowMenu(void)
{
	/* define an array to show menu options */
	uint8_t Menu_Options_StrArr[] = "\n\n********  Welcom To My Clock  ********\n\
Menu Options are :\n\
1- DisPlay time and date\n\
2- Set time and date\n\
3- Set alarm\n\
4- Shutdown the System\n\
Please,Choice a number from this options : ";

	/* this is a variable which carrying show menu String array Length */
	uint8_t Menu_Options_StringDataLength= sizeof(Menu_Options_StrArr);

	/* Display menu options */
	UART_u8SendBufferSynch(USART2_peri,Menu_Options_StrArr,Menu_Options_StringDataLength);
}

/**
 * @brief: this function is used to take a number from the menu
 * @return: this function will return number from menu
 */
uint8_t Rececive_An_Option(void)
{
	/* define a variable to carry receive number */
	uint8_t Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;

	USART_u8ReceiveData(USART2_peri, &Local_u8ReceivedDataFromUser);

	/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
	if(Local_u8ReceivedDataFromUser >= '1' && Local_u8ReceivedDataFromUser <= '9')
	{
		/* save the digit which taking from User */
		Local_u8ReceivedDataFromUser = Local_u8ReceivedDataFromUser - '0';
	}

	return Local_u8ReceivedDataFromUser;
}

/**
 * @brief : this function is used in main to run Log in system
 * @return: this function will return number from menu
 */
uint8_t  SystemLogIn(void)
{
	/* this variable is used to carry return value from Ask_And_TakeUserId */
	uint32_t Local_u32UserID = INIT_VALUE_BY_ZERO;

	/* this variable is used to carry return value from TakeUserPassWord */
	uint32_t Local_u32UserPassWord = INIT_VALUE_BY_ZERO;

	/* define a variable to carry receive number */
	uint8_t Local_u8ReceivedDataFromMenu = INIT_VALUE_BY_ZERO;

	Welcome_Message();

	Local_u32UserID = AskAndTakeUserIdThenCheckIsValid();

	Local_u32UserPassWord = TakeUserPassWord();

	if(Local_u32UserID == 1234 && Local_u32UserPassWord == 4321)
	{
		/* Show the menu */
		ShowMenu();
		Local_u8ReceivedDataFromMenu = Rececive_An_Option();

	}else if(Local_u32UserID == 5678 && Local_u32UserPassWord == 8765)
	{
		/* Show the menu */
		ShowMenu();
		Local_u8ReceivedDataFromMenu = Rececive_An_Option();
	}

	return Local_u8ReceivedDataFromMenu;
}

/**
 * @brief: this function is used to display time and date
 */
void DisplayTimeAndDate(void)
{
	/* define an array to tell the user that he entered Display Date and Time Mode */
	uint8_t DisplayDateAndTime_StrArr[] = "\nWelcom to Display Date and Time Mode";
	/* this is a variable which carrying Display Date And Time String array Length */
	uint8_t DisplayDateAndTime_StringDataLength= sizeof(DisplayDateAndTime_StrArr);

	/* send this message to console window */
	UART_u8SendBufferSynch(USART2_peri,DisplayDateAndTime_StrArr,DisplayDateAndTime_StringDataLength);

	/* Display time and date ON CLCD */

}

/**
 * @brief: this function is used to Take date
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t Take_Date(NowTimeStruct_t* Copy_FSNowTimeStruct)
{
	/* define a variable to carry Error State Value */
	uint8_t Local_u8ErrorStateVal = INIT_VALUE_BY_ZERO;

	/* check on the pointer */
	if(Copy_FSNowTimeStruct != NULL)
	{
		/* define a variable to carry data from user */
		uint8_t Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
		/* define a variable to count digits */
		uint8_t Local_u8CountDigit = INIT_VALUE_BY_ZERO;


		/* this variable is used to carry  Year */
		uint16_t Local_u16DateYear = INIT_VALUE_BY_ZERO;
		/* this variable is used to carry Month */
		uint16_t Local_u16DateMonth = INIT_VALUE_BY_ZERO;
		/* this variable is used to carry Day */
		uint16_t Local_u16DateDay = INIT_VALUE_BY_ZERO;

		/* define an array to tell the user that he entered Set Date and Time Mode */
		uint8_t AskDateAndTime_StrArr[] = "\nPlease,Enter the Date and time only in this formula\n\
1- Sun\t2- Mon\t3- Tue\n4- Wed\t5- Thr\t6- Fri\t7- Sat\n\n0- AM\t1- PM\n\
mm-dd-yy (1:7 that is the number of day name) HH:MM:SS AM or PM\n(For ex: 01-13-2023 (1) 12:51:00 (1)\n";

		/* this is a variable which Asking Date And Time String array Length */
		uint8_t AskDateAndTime_StringDataLength= sizeof(AskDateAndTime_StrArr);


		/* send this message to console window */
		UART_u8SendBufferSynch(USART2_peri,AskDateAndTime_StrArr,AskDateAndTime_StringDataLength);

		/* looping until take 2 digits */
		do
		{
			/* receive Month number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);
			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16DateMonth = Local_u16DateMonth * 10 + Local_u8ReceivedDataFromUser - '0';
			}

			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_MONTH_DIGITS);

		Copy_FSNowTimeStruct->NowTimeMONTH = Local_u16DateMonth;

		/* receive - */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		/* Reset counter value */
		Local_u8CountDigit = ZERO_VALUE;
		/* looping until take 2 digits */
		do
		{
			/* receive Day number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);
			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16DateDay = Local_u16DateDay * 10 + Local_u8ReceivedDataFromUser - '0';
			}

			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_DAY_DIGITS);

		Copy_FSNowTimeStruct->NowTimeDAY = Local_u16DateDay;

		/* receive - */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		/* Reset counter value */
		Local_u8CountDigit = ZERO_VALUE;
		/* looping until take 2 digits */
		do
		{
			/* receive Month number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);
			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16DateYear = Local_u16DateYear * 10 + Local_u8ReceivedDataFromUser - '0';
			}

			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_YEAR_DIGITS);

		Copy_FSNowTimeStruct->NowTimeYEAR = Local_u16DateYear;
	}else
	{
		Local_u8ErrorStateVal = NULL_PTR_ERR;
	}
	return Local_u8ErrorStateVal;
}

/**
 * @brief: this function is used to Take Day
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t Take_Day(NowTimeStruct_t* Copy_FSNowTimeStruct)
{
	/* define a variable to carry Error State Value */
	uint8_t Local_u8ErrorStateVal = INIT_VALUE_BY_ZERO;

	/* check on the pointer */
	if(Copy_FSNowTimeStruct != NULL)
	{
		/* define a variable to carry data from user */
		uint8_t Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
		/* define a variable to count digits */
		uint8_t Local_u8CountDigit = INIT_VALUE_BY_ZERO;

		/* this variable is used to carry  Year */
		uint16_t Local_u16DayName = INIT_VALUE_BY_ZERO;

		/* receive space */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		/* receive ( */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);
		/* looping until take 2 digits */
		do
		{
			/* receive Month number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16DayName = Local_u8ReceivedDataFromUser - '0';
			}
			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_DATE_DIGITS);

		Copy_FSNowTimeStruct->NowTimeDATE = Local_u16DayName;

		/* receive ) */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);
		/* receive space */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);


	}else
	{
		Local_u8ErrorStateVal = NULL_PTR_ERR;
	}
	return Local_u8ErrorStateVal;
}

/**
 * @brief: this function is used to Take Time
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t Take_Time(NowTimeStruct_t* Copy_FSNowTimeStruct)
{

	/* define a variable to carry Error State Value */
	uint8_t Local_u8ErrorStateVal = INIT_VALUE_BY_ZERO;

	/* check on the pointer */
	if(Copy_FSNowTimeStruct != NULL)
	{
		uint8_t SuccessfullyDateAndTimeSetting_StrArr[] = "\n Successfully Date And Time Setting ";
		uint8_t SuccessfullyDateAndTimeSetting_StringDataLength= sizeof(SuccessfullyDateAndTimeSetting_StrArr);
		/* define a variable to carry data from user */
		uint8_t Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
		/* define a variable to count digits */
		uint8_t Local_u8CountDigit = INIT_VALUE_BY_ZERO;

		/* this variable is used to carry  hours */
		uint16_t Local_u16Hours = INIT_VALUE_BY_ZERO;
		/* this variable is used to carry  mins */
		uint16_t Local_u16Mins = INIT_VALUE_BY_ZERO;
		/* this variable is used to carry  secs */
		uint16_t Local_u16Seconds = INIT_VALUE_BY_ZERO;

		/* this variable is used to carry  secs */
		uint16_t Local_u16Am_Pm = INIT_VALUE_BY_ZERO;


		/* looping until take 2 digits */
		do
		{
			/* receive Month number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16Hours = Local_u16Hours*10 + Local_u8ReceivedDataFromUser - '0';
			}
			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_HRS_DIGITS);

		Copy_FSNowTimeStruct->NowTimeHOUR = Local_u16Hours;

		/* receive : */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		Local_u8CountDigit = ZERO_VALUE;


		/* looping until take 2 digits */
		do
		{
			/* receive Month number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16Mins = Local_u16Mins*10 + Local_u8ReceivedDataFromUser - '0';
			}
			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_MINS_DIGITS);

		Copy_FSNowTimeStruct->NowTimeMIN = Local_u16Mins;

		/* receive : */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		Local_u8CountDigit = ZERO_VALUE;


		/* looping until take 2 digits */
		do
		{
			/* receive Month number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16Seconds = Local_u16Seconds*10 + Local_u8ReceivedDataFromUser - '0';
			}
			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_SECS_DIGITS);

		Copy_FSNowTimeStruct->NowTimeSEC = Local_u16Seconds;

		/* receive Space */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		Local_u8CountDigit = ZERO_VALUE;

		/* receive ( */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		/* looping until take 1 digits */
		do
		{
			/* receive Month number and this is consist of 2 digits */
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

			/* Check if the pressed key is a digit (0 to 9) Not unsigned number */
			if(Local_u8ReceivedDataFromUser >= '0' && Local_u8ReceivedDataFromUser <= '9')
			{
				/* save the digit which taking from User */
				Local_u16Am_Pm = Local_u8ReceivedDataFromUser - '0';
			}
			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountDigit++;
		}while(Local_u8CountDigit < MAX_AM_PM_DIGITS);

		Copy_FSNowTimeStruct->Now_pm_am = Local_u16Am_Pm;

		/* receive ) */
		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		/* send this message to console window */
		UART_u8SendBufferSynch(USART2_peri,SuccessfullyDateAndTimeSetting_StrArr,SuccessfullyDateAndTimeSetting_StringDataLength);

	}else
	{
		Local_u8ErrorStateVal = NULL_PTR_ERR;
	}
	return Local_u8ErrorStateVal;
}

/**
 * @brief: this function is used to set time and date
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t SetTimeAndDate(NowTimeStruct_t* Copy_FSNowTimeStruct)
{
	/* define a variable to carry Error State Value */
	uint8_t Local_u8ErrorStateVal = INIT_VALUE_BY_ZERO;

	/* check on the pointer */
	if(Copy_FSNowTimeStruct != NULL)
	{
		/* define an array to tell the user that he entered Set Date and Time Mode */
		uint8_t SetDateAndTime_StrArr[] = "\nWelcom to Set Time and Date Mode";

		/* this is a variable which Asking Date And Time String array Length */
		uint8_t SetDateAndTime_StringDataLength= sizeof(SetDateAndTime_StrArr);

		/* send this message to console window */
		UART_u8SendBufferSynch(USART2_peri,SetDateAndTime_StrArr,SetDateAndTime_StringDataLength);

		/* Set time and date here */
		Take_Date(Copy_FSNowTimeStruct);
		Take_Day(Copy_FSNowTimeStruct);
		Take_Time(Copy_FSNowTimeStruct);
	}else
	{
		/* update error state value */
		Local_u8ErrorStateVal = NULL_PTR_ERR;
	}
	return Local_u8ErrorStateVal;
}

/**
 * @brief: this function is used to take alarm name
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t AlarmName(char *Copy_pu8ArrName)
{
	uint8_t Local_u8ErrorStateVal = INIT_VALUE_BY_ZERO;

	if(Copy_pu8ArrName !=NULL)
	{
		uint8_t Local_u8ReceivedDataFromUser = INIT_VALUE_BY_ZERO;
		uint8_t Local_u8CountAlarmChar = INIT_VALUE_BY_ZERO;

		USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

		while(Local_u8ReceivedDataFromUser != 0x0D && Local_u8CountAlarmChar < MAX_ALARM_NAME_CHAR)
		{
			/* receive Month number and this is consist of 2 digits */
			Copy_pu8ArrName[Local_u8CountAlarmChar] = Local_u8ReceivedDataFromUser;
			USART_u8ReceiveData(USART2_peri,&Local_u8ReceivedDataFromUser);

			/* increment Local_u8FourDigitID by 1 */
			Local_u8CountAlarmChar++;
		}
		Copy_pu8ArrName[Local_u8CountAlarmChar] = '\0';
	}else
	{
		/* update error state value */
		Local_u8ErrorStateVal = NULL_PTR_ERR;
	}
	return Local_u8ErrorStateVal;
}
/**
 * @brief: this function is used to Set alarm
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t SetAlarm(NowTimeStruct_t* Copy_FSNowTimeStruct)
{
	/* define a variable to carry Error State Value */
	uint8_t Local_u8ErrorStateVal = INIT_VALUE_BY_ZERO;

	/* check on the pointer */
	if(Copy_FSNowTimeStruct != NULL)
	{

		/* define an array to tell the user that he entered Set Date and Time Mode */
		uint8_t SetAlarm_StrArr[] = "\nWelcom to Set alarm Mode";
		/* this is a variable which carrying Display Date And Time String array Length */
		uint8_t SetAlarm_StringDataLength= sizeof(SetAlarm_StrArr);

		uint8_t AskAlarmName[] = "\nPlease,Enter alarm name and it must end with enter : ";
		uint8_t AskAlarmName_StringDataLength= sizeof(AskAlarmName);

		uint8_t FullAlarms[] = "\nAll alarms are busy ";
		uint8_t FullAlarm_StringDataLength= sizeof(FullAlarms);

		/* send this message to console window */
		UART_u8SendBufferSynch(USART2_peri,SetAlarm_StrArr,SetAlarm_StringDataLength);


		uint8_t Alarm = INIT_VALUE_BY_ZERO;

		/* size of alarm name?  */
		for(Alarm=0 ; Alarm< TOTAL_ALARMS ; Alarm++ )
		{
			if((AlarmsArr[Alarm].NowTimeYEAR) == 0)
			{
				/* send this message to console window */
				UART_u8SendBufferSynch(USART2_peri,AskAlarmName,AskAlarmName_StringDataLength);

				AlarmName(AlarmNamesArr[Alarm]);
				/* Set time and date here */
				Take_Date(Copy_FSNowTimeStruct);
				Take_Day(Copy_FSNowTimeStruct);
				Take_Time(Copy_FSNowTimeStruct);
				AlarmsArr[Alarm] = *Copy_FSNowTimeStruct;
				break;
			}
		}

		if(Alarm == TOTAL_ALARMS)
		{
			UART_u8SendBufferSynch(USART2_peri,FullAlarms,FullAlarm_StringDataLength);
		}
		/************** flag check if 5 alarms are busy **********************/
	}else
	{
		/* update error state value */
		Local_u8ErrorStateVal = NULL_PTR_ERR;
	}
	return Local_u8ErrorStateVal;
	/* Set alarm here */

}

/**
 * @brief: this function is used to check on received option from menu and work on it
 * @param[in] Copy_u8ReceivedDataFromMenu : this variable is used to carry the menu number which send from the user
 */
void WorkingOnMenuOptions(uint8_t Copy_u8ReceivedDataFromMenu)
{
	/* define an array to Tell  System Shut Down */
	uint8_t SystemShutDown_StrArr[] = "\n\n******  SYSTEM SHUTDOWN  ******\n";

	/* this is a variable which carrying SystemShutDown String array Length */
	uint8_t SystemShutDown_StringDataLength= sizeof(SystemShutDown_StrArr);

	/* check on menu options :  DisplayTimeAndDateMode or SetTimeAndDateMode or SetAlarmMode  */
	if(Copy_u8ReceivedDataFromMenu == DisplayTimeAndDateMode)
	{
		/* call DisplayTimeAndDate function  */
		DisplayTimeAndDate();

	}else if(Copy_u8ReceivedDataFromMenu == SetTimeAndDateMode)
	{
		/* call DisplayTimeAndDate function */
		SetTimeAndDate(&NowTimeStruct_instance);

	}else if (Copy_u8ReceivedDataFromMenu == SetAlarmMode)
	{
		/* call SetAlarm function */
		SetAlarm(&NowTimeStruct_instance);

	}else
	{
		/* exti the system */
		UART_u8SendBufferSynch(USART2_peri,SystemShutDown_StrArr,SystemShutDown_StringDataLength);
		SystemShutDown();
	}

}

/**
 * @brief: this function is used to Ask if the user want to return to menu or not
 */
void ReturnToMenu(void)
{
	static uint8_t Local_u8Flag = INIT_VALUE_BY_ZERO;
	static uint8_t Local_u8YesFlag = INIT_VALUE_BY_ZERO;

	if(Local_u8Flag == ZERO_VALUE)
	{
		uint16_t Local_u16TIME_OUT_Counter= INIT_VALUE_BY_ZERO;

		/* define a variable to carry data from user */
		uint8_t Local_u8ReceivedDataFromUser = 0xff;

		/* define an array to tell the user that he entered Set Date and Time Mode */
		uint8_t Contine_StrArr[] = "\nDo You want to continue? [y/n] : ";

		/* define an array to Tell  System Shut Down */
		uint8_t SystemShutDown_StrArr[] = "\n\n******  SYSTEM SHUTDOWN  ******\n";

		/* this is a variable which carrying SystemShutDown String array Length */
		uint8_t SystemShutDown_StringDataLength= sizeof(SystemShutDown_StrArr);

		/* this is a variable which Asking Date And Time String array Length */
		uint8_t Continue_StringDataLength= sizeof(Contine_StrArr);
		if(Local_u8YesFlag == ZERO_VALUE)
		{
			UART_u8SendBufferSynch(USART2_peri,Contine_StrArr,Continue_StringDataLength);
			Local_u8YesFlag = ONE_VALUE;
		}

		while(USART_u8ReceiveDataAsynch(USART2_peri,&Local_u8ReceivedDataFromUser) != 1 && Local_u16TIME_OUT_Counter< UART_TIME_OUT_VAL)
		{
			SYSTICK_u8Delay_MS(1);
			Local_u16TIME_OUT_Counter++;
		}


		if(Local_u8ReceivedDataFromUser == 'y')
		{
			Local_u8YesFlag = ZERO_VALUE;
			ShowMenu();
			Local_u8ReceivedDataFromUser = Rececive_An_Option();
			WorkingOnMenuOptions(Local_u8ReceivedDataFromUser);
		}else if(Local_u8ReceivedDataFromUser == 'n')
		{
			Local_u8Flag = ONE_VALUE;
			/* exti the system */
			UART_u8SendBufferSynch(USART2_peri,SystemShutDown_StrArr,SystemShutDown_StringDataLength);
			SystemShutDown();
		}
	}
}

void SystemInit(void)
{
	RCC_u8APB_1_EnableClk(USART2_EN);
	RCC_u8AHB_1_EnableClk(GPIOA_EN);

	USRAT_PinConfig_t  USART_Config_Struct ={.USART_Num = USART2_peri,.Mode=RX_AND_TX_MODE,.WordLength =EIGHT_BIT,.USART_Int_Sts = USART_INT_DISABLED,
			.DMA_Sel=DMA_DISABLED,.BaudRate=BaudRate_9600,.OverSampling=OVER8_EN,.Parity=PARITY_DISABLED,.StopBit =ONE_BIT,
	};


	PinConfig_t	Pin2_t ={.Port= PORTA ,.PinNum =PIN2,.Mode = ALTERNATE_FUNCTION,.OutputType = OPEN_DRAIN,.AltFunc = AF7,
	};

	PinConfig_t	Pin3_t ={.Port= PORTA ,.PinNum =PIN3,.Mode = ALTERNATE_FUNCTION,.OutputType = OPEN_DRAIN,.AltFunc = AF7,
	};

	GPIO_u8PinInit(&Pin2_t);
	GPIO_u8PinInit(&Pin3_t);

	USART_u8Init(&USART_Config_Struct);
}

