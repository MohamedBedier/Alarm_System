/*
 * LogIn.h
 *
 *  Created on: Jan 9, 2024
 *      Author: DeLL
 */

#ifndef LOGINANDMENUOPTIONS_H_
#define LOGINANDMENUOPTIONS_H_

#define  UART_TIME_OUT_VAL     100UL
#define  INITIAL_VAL_0XFF      0XFF
#define  MAX_ID_DIGITS         4u
#define  MAX_PASSWORD_DIGITS   4u

#define  MAX_MONTH_DIGITS      2u
#define  MAX_DAY_DIGITS        2u
#define  MAX_YEAR_DIGITS       4u

#define  MAX_DATE_DIGITS        1u
#define  MAX_AM_PM_DIGITS        1u

#define  MAX_HRS_DIGITS         2u
#define  MAX_MINS_DIGITS        2u
#define  MAX_SECS_DIGITS        2u

#define  MAX_3TIMES_ENTERING_PASSWORD   3u
#define  DisplayTimeAndDateMode   1u
#define  SetTimeAndDateMode   2u
#define  SetAlarmMode   3u

#define   TOTAL_ALARMS    5U
#define  MAX_ALARM_NAME_CHAR        15u

#define  TERMINATE_SYSTEM       10U


/**
 * @brief: this function is used to send "Welcome to our project" to the user
 */
void  Welcome_Message(void);

/**
 * @brief : this function is used in main to run Log in system
 * @return: this function will return number from menu
 */
uint8_t  SystemLogIn(void);
/**
 * @brief : this function is used to Shut down our system by Disable usart2 clock in two cases
 * 			1st: if the user entered Incorrect ID.
 * 			2nd: if the user entered Incorrect password for 3 times not included the first one
 */
void  SystemShutDown(void);

/**
 * @brief: this function is used to ask the User_ID and take it
 * 			note that : User_ID must consist of max 4 digits only
 * @return: this function will return User_ID
 */
uint32_t  Ask_And_TakeUserId(void);


/**
 * @brief: this function is used to take the User_PassWord and it consists from 4 digits
 * @return: this function will return User_password
 */
uint32_t  TakeUserPassWord(void);

/**
 * @brief: this function is used to take the User_PassWord for max 3 times
 * @return: this function will return User_password
 */
uint32_t  ThreeTimesForPassWord(void);

/**
 * @brief: this function is used to show menu options
 */
void  ShowMenu(void);

/**
 * @brief: this function is used to take a number from the menu
 * @return: this function will return number from menu
 */
uint8_t Rececive_An_Option(void);

/**
 * @brief: this function is used to check on received option from menu and work on it
 * @param[in] Copy_u8ReceivedDataFromMenu : this variable is used to carry the menu number which send from the user
 */
void WorkingOnMenuOptions(uint8_t Copy_u8ReceivedDataFromMenu);

/**
 * @brief: this function is used to display time and date
 */
void DisplayTimeAndDate(void);

/**
 * @brief: this function is used to set time and date
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t SetTimeAndDate(NowTimeStruct_t* Copy_FSNowTimeStruct);

/**
 * @brief: this function is used to date
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t Take_Date(NowTimeStruct_t* Copy_FSNowTimeStruct);

/**
 * @brief: this function is used to Take Day
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t Take_Day(NowTimeStruct_t* Copy_FSNowTimeStruct);

/**
 * @brief: this function is used to Take Time
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t Take_Time(NowTimeStruct_t* Copy_FSNowTimeStruct);


/**
 * @brief: this function is used to take alarm name
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t ReceiveAlarmName(char *Copy_pu8ArrName);

/**
 * @brief: this function is used to Set alarm
 * @param[out] Copy_FSNowTimeStruct: this is a pointer to struct which carrying details of alarm setting
 * @return: this function will return Error State Value
 */
uint8_t SetAlarm(NowTimeStruct_t* Copy_FSNowTimeStruct);

/**
 * @brief: this function is used to Ask if the user want to return to menu or not
 */
void ReturnToMenu(void);

void System_Init(void);


#endif /* LOGINANDMENUOPTIONS_H_ */
