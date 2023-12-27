## Rest and Clock Control(RCC) for STM32F103C8T6 Driver:

## *********  Overview  *********  
The STM32F103C8T6 Rest and Clock Control (RCC) Driver provides a set of functions to configure 
the clock settings for the STM32F103C8T6 microcontroller. These functions enable the user to set
various clock types, control their status (on or off), and configure the PLL (Phase-Locked Loop)
for precise clock generation. Additionally, the driver supports the activation and deactivation 
of peripheral clocks on both AHB (Advanced High-Performance Bus) and APB (Advanced Peripheral Bus) buses.

## *********  Functions  *********  
1- **RCC_u8SetClkSts:**
Configure clock type (HSE, HSI, PLL) and set its status (on or off)..
	*parameters:
	- 'Copy_EnumCLkType' : Clock type options..
	- 'Copy_EnumCLkStatus' Status options.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

2- **RCC_u8PLLCLKConfig:**
Configure PLL SRC and PLLMUL.
	*parameters:
	- 'Copy_EnumPLLSRC' : PLL Source.
	- 'Copy_EnumPLLMul' : PLL Multiple factor.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

3- **RCC_u8AHB_EnableClk:**
Enable peripheral clock on AHB.
	*parameters:
	- 'Copy_EnumAHB_Peripheral' : AHB Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

4- **RCC_u8AHB_DisableClk:**
Disable peripheral clock on AHB.
	*parameters:
	- 'Copy_EnumAHB_Peripheral' : AHB Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

5- **RCC_u8APB_1_EnableClk:**
Enable peripheral clock on APB1.
	*parameters:
	- 'Copy_EnumAPB_1_Peripheral' : APB1 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

6- **RCC_u8APB_1_DisableClk:**
Disable peripheral clock on APB1.
	*parameters:
	- 'Copy_EnumAPB_1_Peripheral' :  APB1 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
7- **RCC_u8APB_2_EnableClk:**
Enable peripheral clock on APB2.
	*parameters:
	- 'Copy_EnumAPB_2_Peripheral' :  APB2 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

8- **RCC_u8APB_2_DisableClk:**
Disable peripheral clock on APB2.
	*parameters:
	- 'Copy_EnumAPB_2_Peripheral' :  APB2 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	

9- **RCC_u8SetSysClk:**
Set the system clock type (HSE, HSI, PLL).
	*parameters:
	- 'Copy_EnumSysClk' : System Clock options.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
10- **RCC_u8SetHSEConfig:**
Set the input entering the PLL with a divided factor of 2 or no divide factor.
	*Parameters:
	- 'Copy_EnumHSE_Division_Fact' : HSE CLOCK configuration.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
## *********  Usage  ********* 
To utilize the STM32F103C8T6 RCC Driver, include the necessary files in your project 
and call the appropriate functions with the required parameters. Ensure proper error
handling based on the returned 'Local_u8ErrorState' value.