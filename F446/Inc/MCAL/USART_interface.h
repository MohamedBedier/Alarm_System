/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : USART_interface.h                           **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/**
 * @brief: this is an enum which carrying USART_SR naming bits
 */
typedef  enum
{
	PE =0,/**< Parity error flag */
	FE,   /**< Framing error flag */
	NE,   /**< Noise detected flag */
	ORE,  /**< Overrun error flag */
	IDLE, /**< IDLE line detected flag */
	RXNE, /**< Read data register not empty flag */
	TC,   /**< Transmission complete  */
	TXE,  /**< Transmit data register empty flag */
	LBD,  /**< LIN break detection flag */
	CTS   /**< CTS flag */
}USART_SR_t;


/**
 * @brief: this is an enum which carrying USART_CR1 naming bits
 */
typedef  enum
{
	SBK =0,     /**< Send break */
	RWU,        /**< Receiver wakeup */
	RE,         /**< Receiver enable */
	TE,         /**< Transmitter enable */
	IDLEIE,     /**< IDLE interrupt enable */
	RXNEIE,     /**< RXNE interrupt enable */
	USART_TCIE,       /**< Transmission complete interrupt enable */
	TXEIE,      /**< TXE interrupt enable */
	PEIE,       /**< PE interrupt enable */
	PS,         /**< Parity selection */
	PCE,        /**< Parity control enable */
	WAKE,       /**< Wakeup method */
	M,          /**< Word length */
	UE,         /**< USART enable */
	OVER8=15       /**< Oversampling mode */
}USART_CR1_t;


/**
 * @brief: this is an enum which carrying USART_CR2 naming bits
 */
typedef  enum
{
	ADD_BIT0 =0,/**< Address of the USART node BIT 0 */
	ADD_BIT1,   /**< Address of the USART node BIT 1 */
	ADD_BIT2,   /**< Address of the USART node BIT 2 */
	ADD_BIT3,   /**< Address of the USART node BIT 3 */
	LBDL =5,    /**< lin break detection length */
	LBDIE,      /**< LIN break detection interrupt enable */
	LBCL=8,     /**< Last bit clock pulse */
	CPHA,       /**< Clock phase */
	CPOL,       /**< Clock polarity */
	CLKEN,      /**< Clock enable */
	STOP_BIT0,  /**< STOP bits BIT 0*/
	STOP_BIT1,  /**< STOP bits BIT 1*/
	LINEN=14    /**< LIN mode enable */
}USART_CR2_t;


/**
 * @brief: this is an enum which carrying USART_CR3 naming bits
 */
typedef  enum
{
	EIE =0, /**< Error interrupt enable */
	IREN,   /**< IrDA mode enable */
	IRLP,   /**< IrDA low-power */
	HDSEL,  /**< Half-duplex selection */
	NACK,   /**< Smartcard NACK enable */
	SCEN,   /**< Smartcard mode enable */
	DMAR,   /**< DMA enable receiver */
	DMAT,   /**< DMA enable transmitter */
	RTSE,   /**< RTS enable */
	CTSE,   /**< CTS enable */
	CTSIE,  /**< CTS interrupt enable */
	ONEBIT  /**< One sample bit method enable */
}USART_CR3_t;


/**
 * @brief: this is an enum which carrying USART Mode options
 */
typedef  enum
{
	RX_MODE = 0,  /**< RX_MODE */
	TX_MODE,      /**< TX_MODE */
	RX_AND_TX_MODE/**< RX_AND_TX_MODE */
}USART_Mode_t;

/**
 * @brief: this is an enum which carrying over sampling options
 */
typedef  enum
{
	OVER16_EN = 0,/**< OVER16_EN */
	OVER8_EN      /**< OVER8_EN */
}OverSampling_t;


/**
 * @brief: this is an enum which carrying stop bit options
 */
typedef  enum
{
	ONE_BIT = 0,    /**< ONE_BIT */
	TWO_BIT,        /**< TWO_BIT */
	HALF_BIT,       /**< HALF_BIT */
	ONE_AND_HALF_BIT/**< ONE_AND_HALF_BIT */
}StopBit_t;

/**
 * @brief: this is an enum which carrying word length options
 */
typedef  enum
{
	EIGHT_BIT = 0,/**< EIGHT_BIT */
	NINE_BIT      /**< NINE_BIT */

}WordLength_t;

/**
 * @brief: this is an enum which carrying Parity options enabled or disabled
 */
typedef  enum
{
	PARITY_DISABLED = 0,/**< PARITY_DISABLED */
	PARITY_ENABLED      /**< PARITY_ENABLED */
}Parity_t;

/**
 * @brief: this is an enum which carrying USART NUMBERS
 */
typedef  enum
{
	USART1_peri = 0,/**< USART1_peri */
	USART2_peri,    /**< USART2_peri */
	USART3_peri,    /**< USART3_peri */
	UART4_peri,     /**< UART4_peri */
	UART5_peri,     /**< UART5_peri */
	USART6_peri     /**< USART6_peri */

}USART_Num_t;

/**
 * @brief: this is an enum which carrying If you work as synchronous or Asynchronous
 */
typedef  enum
{
	ASYNCHRONOUS = 0,
	SYNCHRONOUS
}Synch_Asynch_t;

/**
 * @brief: this is an enum which carrying Parity options even or odd
 */
typedef  enum
{
	EVEN_PARITY = 0,/**< EVEN_PARITY */
	ODD_PARITY      /**< ODD_PARITY */
}Parity_Sel_t;

/**
 * @brief: this is an enum which carrying If you want hardware flow control if you work as synchronous
 */
typedef  enum
{
	H_W_FLOW_CTRL_DISABLED = 0,/**< H_W_FLOW_CTRL_DISABLED */
	H_W_FLOW_CTRL_ENABLED      /**< H_W_FLOW_CTRL_ENABLED */
}HardWare_FlowControl_t;

/**
 * @brief: this is an enum which carrying If you want DMA or Not to transfer data
 */
typedef  enum
{
	DMA_FOR_TRANSMIT = 0,/**< DMA_FOR_TRANSMIT */
	DMA_FOR_RECEIVE,     /**< DMA_FOR_RECEIVE */
	DMA_DISABLED         /**< DMA_DISABLED */
}DMA_Sel_t;

/**
 * @brief: this is an enum which carrying USART interrupt status
 */
typedef  enum
{
	USART_INT_DISABLED = 0,/**< USART_INT_DISABLED */
	USART_INT_ENABLED      /**< USART_INT_ENABLED */
}USART_Int_Sts_t;

/**
 * @brief: this is an enum which carrying USART Interrupt enable bits' name
 */
typedef  enum
{
	ERROR_INT_EN = 0,/**< ERROR_INT_EN */
	IDLE_INT_EN = 4 ,/**< IDLE_INT_EN */
	RXNE_INT_EN,     /**< RXNE_INT_EN */
	TC_INT_EN,       /**< TC_INT_EN */
	TXE_INT_EN,      /**< TXE_INT_EN */
	PE_INT_EN,       /**< PE_INT_EN */
	CTS_INT_EN       /**< CTS_INT_EN */
}USART_Int_t;

/**
 * @brief: this is an enum which carrying baud rate options
 */
typedef enum
{
	BaudRate_9600 = 9600,   /**< BaudRate_9600 */
	BaudRate_115200 = 115200/**< BaudRate_115200 */
}BaudRate_t;

/**
 * @brief: this is a struct which carrying the configuration of USART to initialize it.
 */
typedef  struct
{
	USART_Num_t  USART_Num;
	USART_Mode_t  Mode;
	Parity_t  Parity;
	Parity_Sel_t  Parity_Sel;
	WordLength_t  WordLength;
	StopBit_t  StopBit;
	OverSampling_t  OverSampling;
	Synch_Asynch_t  Synch_Asynch;
	HardWare_FlowControl_t  HardWare_FlowControl;
	USART_Int_Sts_t  USART_Int_Sts;
	USART_Int_t  USART_Int_Name;
	DMA_Sel_t DMA_Sel;
	BaudRate_t BaudRate;
}USRAT_PinConfig_t;


/**
 * @brief: this function is used to initiate USART
 * @param USRAT_PinConfig : this is a pointer of struct which carrying usart configuration
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8Init(USRAT_PinConfig_t* USRAT_PinConfig);

/**
 * @brief this function is used to enable usart interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_EnumInterrupt_Name : this is an enum which carrying interrupt name
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t USART_u8EnableInt(USART_Num_t Copy_EnumUSART_Num ,USART_Int_t  Copy_EnumInterrupt_Name);

/**
 * @brief this function is used to Disable usart interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_EnumInterrupt_Name : this is an enum which carrying interrupt name
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t USART_u8DisableInt(USART_Num_t Copy_EnumUSART_Num ,USART_Int_t  Copy_EnumInterrupt_Name);

/**
 * @brief: this function is used to send data using USART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_u8Data : this variable is used to carry data
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8SendData(USART_Num_t Copy_EnumUSART_Num ,uint8_t Copy_u8Data);

/**
 * @brief: this function is used to send data using Interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_u8Data : this variable is used to carry data
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8SendData_IT(USART_Num_t Copy_EnumUSART_Num ,uint8_t Copy_u8Data);

/**
 * @brief: this function is used to send array of data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t UART_u8SendBufferSynch(USART_Num_t Copy_EnumUSART_Num , uint8_t *Copy_pu8BufferArr , uint8_t Copy_u8SizeOfArr);

/**
 * @brief: this function is used to send array of data using Interrupt
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t UART_u8SendBufferSynch_IT(USART_Num_t Copy_EnumUSART_Num  , uint8_t *Copy_pu8BufferArr,uint8_t Copy_u8SizeOfArr);
/**
 * @brief: this function is used to Receive data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8Received_Data : this is a pointer of uint16 which carrying data received by usart.
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8ReceiveData(USART_Num_t Copy_EnumUSART_Num ,uint8_t *Copy_pu8Received_Data);

/**
 * @brief: this function is used to Receive data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8Received_Data : this is a pointer of uint16 which carrying data received by usart.
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t  USART_u8ReceiveData_IT(USART_Num_t Copy_EnumUSART_Num ,uint8_t *Copy_pu8Received_Data);

/**
 * @brief: this function is used to receive array of data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t USART_u8ReceiveBufferSynch(USART_Num_t Copy_EnumUSART_Num , uint8_t *Copy_pu8BufferArr,uint8_t Copy_u8SizeOfArr);

/**
 * @brief: this function is used to receive array of data using UART
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param Copy_pu8BufferArr : this pointer is used to carry the address of the buffer
 * @param Copy_u8SizeOfArr : this variable is used to carry size of the array
 * @return Local_u8ErrorState: this is a variable to carry error state value.
 */
uint8_t UART_u8ReceiveBufferSynch_IT(USART_Num_t Copy_EnumUSART_Num , uint8_t *Copy_pu8BufferArr,uint8_t Copy_u8SizeOfArr);

uint8_t  USART_u8ReceiveDataAsynch(USART_Num_t Copy_EnumUSART_Num ,uint8_t *Copy_pu8Received_Data);
/**
 * @brief This function is used to Set USART ISR
 * @param Copy_EnumUSART_Num : this is an enum which carrying usart number
 * @param[in] Copy_pfFuncPtr :  this is an array of pointer to function which carrying the address of ISR
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t USART_u8SetCallBack(USART_Num_t Copy_EnumUSART_Num , void (*Copy_pfFuncPtr)(void));

#endif /* USART_INTERFACE_H_ */
