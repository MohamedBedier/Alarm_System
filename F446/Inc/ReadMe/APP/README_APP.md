## Alarm System which Based on STM32F446RE and STM32F103C8T6

## **********  Overview  ********** 
This project involves the development of a real-time alarm clock 
system using two STM32 microcontrollers: STM32F446RE and STM32F103C8T6.
The system is designed to accurately keep track of time.The project starts
with log in system [ASK USER_ID And USER_PassWord].If ID is correct,it will 
ask Password.If ID and Password are matching a Green led is on then allow 
the user to Display Date and Time, set Date and Time and Set alarm.
The system supports up to five alarms. When the alarm time arrives, 
a buzzer sounds through an external trigger on the STM32F103C8T6.
it is going to generate EXTI to STM32F103C8T6 and buzzer will be on. 
if the ID and password are incorrect, the system shuts down, 
and a red LED indicates the authentication failure.

## **********  Features  ********** 

1- We can tracing Time and Date accurately.
2- we can set time and date for RTC.
3- we can set diferent alarms,We can handle up to 5 alarms.
4- Security on the system by using Log in system.

## **********  HardWare components  ********** 

1- Nucleo[STM32F446RE] board.
2- Panda board (based on STM32F103C8T6 MCU ).
3- DS1307 RTC module.
4- LCD display.
5- Buzzer.
6- Red Led.
7- Green Led.

## **********  Communication between our components  ********** 

1 - Nucleo[STM32F446RE] board and RTC Module [DS1307] Using I2C.
2 - Nucleo[STM32F446RE] board and Blue Pill Board [STM32F103C8T6] Using SPI.
3 - Nucleo[STM32F446RE] board and PC Using UART sending and receiving via serial monitor.

## **********  Usage ********** 

To make effective use of the Alarm System.

1- Login: Enter your user ID and password when prompted.

2- A successful login will be indicated by the green LED
on the Panda board, while a red LED will signal a login failure.

3- After login the menu options are appeared on the terminal and you must 
following the instructions on the terminal.

4- When the time arrives for an alarm, the buzzer will sound,
accompanied by the display of the alarm name and alarm number on the LCD screen.

5- If 5 alarms are busy system will inform you and shut down the terminal.