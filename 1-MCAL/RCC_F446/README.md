## Rest and Clock Control(RCC) for STM32F446RE Driver:

## *********  Overview  *********  
The STM32F446RE Rest and Clock Control (RCC) Driver provides a set of functions to configure 
the clock settings for the STM32F446RE microcontroller. These functions enable the user to set
various clock types, control their status (on or off), and configure the PLL (Phase-Locked Loop)
for precise clock generation. The driver supports the activation and deactivation of peripheral 
clocks on different AHB (Advanced High-Performance Bus) and APB (Advanced Peripheral Bus) buses.

## *********  Functions  *********  
1- **RCC_u8SetClkSts:**
Configure clock type (HSE, HSI, PLL) and set its status (on or off)..
	*parameters:
	- 'Copy_EnumCLkType' : Clock type options..
	- 'Copy_EnumCLkStatus' Status options.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

2- **RCC_u8PLLCLKConfig:**
Configure PLL parameters (PLL_M_Factor, PLL_N_Factor, PLL_P_Factor, PLL_CLK_SRC_t).
	*parameters:
	- 'Copy_PS_PLLCLK_Cfg' : Pointer to a struct carrying PLL Clock configuration options.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

3- **RCC_u8AHB_1_EnableClk:**
Enable peripheral clock on AHB1.
	*parameters:
	- 'Copy_EnumAHB1Peripheral' : AHB1 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

4- **RCC_u8AHB_1_DisableClk:**
Disable peripheral clock on AHB1.
	*parameters:
	- 'Copy_EnumAHB1Peripheral' : AHB1 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.


5- **RCC_u8AHB_2_EnableClk:**
Enable peripheral clock on AHB2.
	*parameters:
	- 'Copy_EnumAHB2Peripheral' : AHB2 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

6- **RCC_u8AHB_2_DisableClk:**
Disable peripheral clock on AHB2.
	*parameters:
	- 'Copy_EnumAHB2Peripheral' : AHB2 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

7- **RCC_u8AHB_3_EnableClk:**
Enable peripheral clock on AHB3.
	*parameters:
	- 'Copy_EnumAHB3Peripheral' : AHB3 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

8- **RCC_u8AHB_3_DisableClk:**
Disable peripheral clock on AHB3.
	*parameters:
	- 'Copy_EnumAHB3Peripheral' : AHB3 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
9- **RCC_u8APB_1_EnableClk:**
Enable peripheral clock on APB1.
	*parameters:
	- 'Copy_EnumAPB1Peripheral' : APB1 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

10- **RCC_u8APB_1_DisableClk:**
Disable peripheral clock on APB1.
	*parameters:
	- 'Copy_EnumAPB1Peripheral' :  APB1 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
11- **RCC_u8APB_2_EnableClk:**
Enable peripheral clock on APB2.
	*parameters:
	- 'Copy_EnumAPB2Peripheral' :  APB2 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

12- **RCC_u8APB_2_DisableClk:**
Disable peripheral clock on APB2.
	*parameters:
	- 'Copy_EnumAPB2Peripheral' :  APB2 Peripherals.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
13- **RCC_u8CSSPinState:**
 this function to enable Or disable CSS Pin.
	*parameters:
	- 'Copy_EnumCSS_Sts' : Enum carrying the state of the CSS Pin.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
14- **RCC_u8SetSysClk:**
Set the system clock type (HSE, HSI, PLL).
	*parameters:
	- 'Copy_EnumSysClk' : System Clock options.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
## *********  Usage  ********* 
To use this RCC Driver, include the necessary files in your project and call
the appropriate functions with the required parameters. Ensure proper error handling 
based on the returned Local_u8ErrorState value.