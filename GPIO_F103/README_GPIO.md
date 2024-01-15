## GPIO Driver for STM32F103C8T6:

## *********  Overview  *********  
This GPIO (General Purpose Input/Output) driver for the STM32F103C8T6 
microcontroller provides a set of functions to initialize, set values, toggle states, and 
read values of GPIO pins. These functions are designed to facilitate easy and efficient 
GPIO usage in embedded systems.

## *********  Function Descriptions  *********  
1- **GPIO_u8PinInit:**
This function initializes a GPIO pin based on the provided configuration..
	## parameters:
	- 'PinConfig' : is a pointer to a PinConfig_t structure containing the initialization values for the pin..
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

2- **GPIO_u8SetPinValue:**
This function sets the state of a GPIO pin to either high or low.
	## parameters:
	- 'Port' : to determine the port Name.
	- 'PinNum' : to determine the Pin Name.
	- 'PinVal' : to determine the pin value high or low.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

3- **GPIO_u8TogglePinValue:**
This function toggles the state of a GPIO pin.
	## parameters:
	- 'Port' : to determine the port Name.
	- 'PinNum' : to determine the Pin Name.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

4- **GPIO_u8ReadPinValue:**
This function reads the current state of a GPIO pin.
	## parameters:
	- 'Port' : to determine the port Name.
	- 'PinNum' : to determine the Pin Name.
	- 'PinVal' : this is a pointer to uint8_t to carry value of pin
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
5- **GPIO_u8SetPortValue:**
The function is used to set value on a complete port.
	## parameters:
	- 'Port' : to determine the port Name.
	- 'Copy_u32Value' : this variable is used to carry the value which put into port.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
6- **GPIO_u8SetEXTIPort:**
This function to Set EXTI port AND line.
	## parameters:
	- 'Port' : to determine the port Name.
	- 'Copy_EnumExti_Line' : this enum to carry options of EXTI lines options from line 0 to line 19 totally 20 EXTI_lines.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
		

	
## *********  Usage  ********* 
To use this GPIO driver, include the appropriate header file and 
link the corresponding source file in your STM32F103C8T6 project 
Make sure to initialize the GPIO pins before using other functions in your application.

