## Buzzer Driver :

## *********  Overview  *********
The Buzzer Driver provides functions to control the state of a buzzer, making it easy to
integrate and manage within embedded systems. The driver includes two functions, 
each dedicated to turning the buzzer on or off.

## *********   Function Descriptions  *********  
1- **BZR_u8Init:**
This function configures the buzzer to Initialization buzzer based on the provided buzzer configuration struct. 
	## parameter:
	- 'BUZZER_Configs' : this is a pointer of struct which carrying buzzer configuration.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

2- **BZR_u8TurnOn:**
This function configures the buzzer to turn ON.
	## parameter:
	- 'Copy_EnumBZRPort' : This is an enum which carrying buzzer Port.
	- 'Copy_EnumBZRPin'  : This is an enum which carrying buzzer Pin.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

3- **BZR_u8TurnOff:** 
This function configures the buzzer to turn OFF.
	## parameter:
	- 'Copy_EnumBZRPort' : This is an enum which carrying buzzer Port.
	- 'Copy_EnumBZRPin'  : This is an enum which carrying buzzer Pin.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
 
## *********  Usage  ********* 
To use the Buzzer Driver, include the appropriate header file and link 
the corresponding source file in your project. Before calling the buzzer functions, ensure 
that the buzzer configuration is appropriately initialized.