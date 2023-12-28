## Buzzer Driver :

## *********  Overview  *********
The Buzzer Driver provides functions to control the state of a buzzer, making it easy to
integrate and manage within embedded systems. The driver includes two functions, 
each dedicated to turning the buzzer on or off.

## *********   Function Descriptions  *********  
1- **BZR_u8TurnOn:**
This function is designed to turn on the buzzer.
	## parameters:
	- 'BUZZER_Configs' : is a pointer to structure that contains information about the buzzer's port and pin.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

2- **BZR_u8TurnOff:**
This function is designed to turn off the buzzer.
	## parameters:
	- 'BUZZER_Configs' : is a pointer to structure that contains information about the buzzer's port and pin.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
## *********  Usage  ********* 
To use the Buzzer Driver, include the appropriate header file and link 
the corresponding source file in your project. Before calling the buzzer functions, ensure 
that the buzzer configuration is appropriately initialized.