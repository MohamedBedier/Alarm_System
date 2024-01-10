## **********  LED Driver  **********   

## **********  Overview  **********  
The LED Driver presented here is designed to provide a simple and effective means of configuring LEDs.
 This driver includes three functions, each tailored for specific LED operations. 
 It ensures seamless integration and ease of use within embedded systems.
 
## **********  Function Descriptions  **********  

1- **LED_u8PinInit:**
This function configures the LED to Initialization Led based on the provided LED configuration struct. 
	## parameter:
	- 'PinConfig' : this is a pointer of struct which carrying LED configuration.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

2- **LED_u8LedTurnON:**
This function configures the LED to turn ON.
	## parameter:
	- 'Copy_EnumLedPort' : This is an enum which carrying Led Port.
	- 'Copy_EnumLedPin'  : This is an enum which carrying Led Pin.
	- 'Copy_EnumLED_u8ConnectionType' : THIS enum which carrying connection type of the led.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

3- **LED_u8LedTurnOff:** 
This function configures the LED to turn OFF.
	## parameter:
	- 'Copy_EnumLedPort' : This is an enum which carrying Led Port.
	- 'Copy_EnumLedPin'  : This is an enum which carrying Led Pin.
	- 'Copy_EnumLED_u8ConnectionType' : THIS enum which carrying connection type of the led.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
 
4- **LED_u8LEDToggle:** 
This function toggles the state of the LED.
	## parameter:
	- 'Copy_EnumLedPort' : This is an enum which carrying Led Port.
	- 'Copy_EnumLedPin'  : This is an enum which carrying Led Pin.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
 
## **********  Usage ********** 
To utilize the LED Driver, include the appropriate header file 
and link the corresponding source file in your project.
Before calling the LED functions,ensure that the LED configuration is appropriately initialized.

