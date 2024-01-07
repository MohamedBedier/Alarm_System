## Direct Memory Access(DMA) for STM32F446RE Driver:

## *********  Overview  *********  
The STM32F446RE DMA (Direct Memory Access) Driver facilitates efficient data  
transfer between peripherals and memory without CPU intervention. This driver 
provides a set of functions to configure and manage DMA channels and streams on the 
STM32F446RE microcontroller. Users can leverage this driver for both polling and 
interrupt-driven data transfer operations.

## *********  Functions  *********  
1- **DMA_u8SetChannel:**
Brief: Set DMA channel configuration.
	**parameters:
	- 'Copy_psDMA': Pointer to a struct carrying DMA configurations.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

2- **DMA_u8SetStreamPrioirty:**
Brief: SetStreamPrioirty DMA.
	**parameters:
	- 'Copy_psDMA' : Pointer to a struct carrying DMA configurations.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

3- **DMA_u8EnabledInt:**
Brief: Enable DMA interrupt.
	**parameters:
	- 'Copy_EnumDMANum' :   Enum carrying the DMA number.
	- 'Copy_EnumStreamNum' : Enum carrying the stream number.
	- 'Copy_EnumInterrupt_Name' : this is an enum which using to interrupt name
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

4- **DMA_u8DisabledInt:**
Brief: Disable DMA interrupt.
	**parameters:
	- 'Copy_EnumDMANum' :   Enum carrying the DMA number.
	- 'Copy_EnumStreamNum' : Enum carrying the stream number.
	- 'Copy_EnumInterrupt_Name' : this is an enum which using to interrupt name
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.


5- **DMA_u8Init:**
Brief: Initialize DMA configurations.
	**parameters:
	- 'Copy_psDMA' : Pointer to a struct carrying DMA configurations.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

6- **DMA_u8DMAEnable:**
Brief: Ensable DMA.
	**parameters:
	- 'Copy_EnumDMANum' :   Enum carrying the DMA number.
	- 'Copy_EnumStreamNum' : Enum carrying the stream number.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

7- **DMA_u8DMADisable:**
Brief: Disable DMA.
	**parameters:
	- 'Copy_EnumDMANum' :   Enum carrying the DMA number.
	- 'Copy_EnumStreamNum' : Enum carrying the stream number.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

8- **DMA_u8ReadFlag:**
Brief: read DMA flag value.
	**parameters:
	- 'Copy_EnumDMANum' :   Enum carrying the DMA number.
	- 'Copy_EnumStreamNum' : Enum carrying the stream number.
	- 'Copy_u8FlagName' : Variable carrying the flag bit number.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
9- **DMA_u8ClearFlag:**
Brief: Clear DMA flag value.
	**parameters:
	- 'Copy_EnumDMANum' :   Enum carrying the DMA number.
	- 'Copy_EnumStreamNum' : Enum carrying the stream number.
	- 'Copy_u8FlagName' : Variable carrying the flag bit number.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

10- **DMA_u8StartTransfer_Polling:**
Brief: Start DMA transfer using polling.
	**parameters:
	- 'Copy_psDMA' : Pointer to a struct carrying DMA configurations.
	- 'Copy_u32SrcAddress' : Source address.
	- 'Copy_u32DstAddress' : Destination address.
	- 'Copy_u32DataLength' : Data length to be transferred.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
11- **DMA_u8StartTransfer_IT:**
Brief: Start DMA transfer using interrupts.
	**parameters:
	- 'Copy_psDMA' : Pointer to a struct carrying DMA configurations.
	- 'Copy_u32SrcAddress' : Source address.
	- 'Copy_u32DstAddress' : Destination address.
	- 'Copy_u32DataLength' : Data length to be transferred.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.

12- **DMA_u8SetCallBack:**
Brief: Set DMA ISR (Interrupt Service Routine).
	**parameters:
	- 'Copy_EnumDMANum' :   Enum carrying the DMA number.
	- 'Copy_EnumStreamNum' : Enum carrying the stream number.
	- 'Copy_pfFuncPtr' : Array of pointers to functions carrying the address of ISR.
	- **Returns:**  'Local_u8ErrorState'  indicating any errors during execution.
	
	
## *********  Usage  ********* 
To utilize the STM32F446RE DMA Driver, include the necessary files in your project 
and call the appropriate functions with the required parameters. Ensure proper error 
handling based on the returned Local_u8ErrorState value.