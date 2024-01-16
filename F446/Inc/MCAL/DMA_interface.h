/*************************************************************/
/*************************************************************/
/**                                                         **/
/** LayerArchitect: MCAL                                    **/
/** File Name : DMA_interface.h                             **/
/** Auther    : MOHAMED BEDIER MOHAMED                      **/
/** Verision :  1.00                                        **/
/**                                                         **/
/*************************************************************/
/*************************************************************/
#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

/**
 * @brief this is an enum which carrying DMA low interrupt status register Bit's Name
 */
typedef enum
{
	FEIF0=0,   /**< stream 0 FIFO error interrupt flag  */
	DMEIF0=2,  /**< stream 0 direct mode error interrupt flag */
	TEIF0,     /**< stream 0 transfer error interrupt flag */
	HTIF0,     /**< stream 0 half transfer interrupt flag */
	TCIF0,     /**< stream 0 transfer complete interrupt flag */
	FEIF1,     /**< stream 1 FIFO error interrupt flag  */
	DMEIF1=8,  /**< stream 1 direct mode error interrupt flag */
	TEIF1 ,    /**< stream 1 transfer error interrupt flag */
	HTIF1,     /**< stream 1 half transfer interrupt flag */
	TCIF1,     /**< stream 1 transfer complete interrupt flag */
	FEIF2=16,  /**< stream 2 FIFO error interrupt flag  */
	DMEIF2=18, /**< stream 2 direct mode error interrupt flag */
	TEIF2,     /**< stream 2 transfer error interrupt flag */
	HTIF2,     /**< stream 2 half transfer interrupt flag */
	TCIF2,     /**< stream 2 transfer complete interrupt flag */
	FEIF3,     /**< stream 3 FIFO error interrupt flag  */
	DMEIF3=24, /**< stream 3 direct mode error interrupt flag */
	TEIF3,     /**< stream 3 transfer error interrupt flag */
	HTIF3,     /**< stream 3 half transfer interrupt flag */
	TCIF3      /**< stream 3 transfer complete interrupt flag */
}DMA_LISR_t;


/**
 * @brief this is an enum which carrying DMA high interrupt status register Bit's Name
 */
typedef enum
{
	FEIF4=0,   /**< stream 4 FIFO error interrupt flag  */
	DMEIF4=2,  /**< stream 4 direct mode error interrupt flag */
	TEIF4,     /**< stream 4 transfer error interrupt flag */
	HTIF4,     /**< stream 4 half transfer interrupt flag */
	TCIF4,     /**< stream 4 transfer complete interrupt flag */
	FEIF5,     /**< stream 5 FIFO error interrupt flag  */
	DMEIF5=8,  /**< stream 5 direct mode error interrupt flag */
	TEIF5 ,    /**< stream 5 transfer error interrupt flag */
	HTIF5,     /**< stream 5 half transfer interrupt flag */
	TCIF5,     /**< stream 1 transfer complete interrupt flag */
	FEIF6=16,  /**< stream 6 FIFO error interrupt flag  */
	DMEIF6=18, /**< stream 6 direct mode error interrupt flag */
	TEIF6,     /**< stream 6 transfer error interrupt flag */
	HTIF6,     /**< stream 6 half transfer interrupt flag */
	TCIF6,     /**< stream 6 transfer complete interrupt flag */
	FEIF7,     /**< stream 7 FIFO error interrupt flag  */
	DMEIF7=24, /**< stream 7 direct mode error interrupt flag */
	TEIF7,     /**< stream 7 transfer error interrupt flag */
	HTIF7,     /**< stream 7 half transfer interrupt flag */
	TCIF7      /**< stream 7 transfer complete interrupt flag */
}DMA_HISR_t;


/**
 * @brief this is an enum which carrying DMA low interrupt flag clear register Bit's Name
 */
typedef enum
{
	CFEIF0=0,  /**< stream 0 clear FIFO error interrupt flag */
	CDMEIF0=2,   /**< stream 0 clear direct mode error interrupt flag */
	CTEIF0,    /**< Stream 0 clear transfer error interrupt flag */
	CHTIF0,    /**< stream 0 clear half transfer interrupt flag  */
	CTCIF0,    /**< stream 0 clear transfer complete interrupt flag  */
	CFEIF1,    /**< stream 1 clear FIFO error interrupt flag  */
	CDMEIF1=8,   /**< stream 1 clear direct mode error interrupt flag */
	CTEIF1,    /**< Stream 1 clear transfer error interrupt flag */
	CHTIF1,    /**< stream 1 clear half transfer interrupt flag  */
	CTCIF1,    /**< stream 1 clear transfer complete interrupt flag  */
	CFEIF2=16,    /**< stream 2 clear FIFO error interrupt flag */
	CDMEIF2=18,   /**< stream 2 clear direct mode error interrupt flag */
	CTEIF2,    /**< Stream 2 clear transfer error interrupt flag */
	CHTIF2,    /**< stream 2 clear half transfer interrupt flag  */
	CTCIF2,    /**< stream 2 clear transfer complete interrupt flag  */
	CFEIF3,    /**< stream 3 clear FIFO error interrupt flag */
	CDMEIF3=24,   /**< stream 3 clear direct mode error interrupt flag */
	CTEIF3,    /**< Stream 3 clear transfer error interrupt flag */
	CHTIF3,    /**< stream 3 clear half transfer interrupt flag  */
	CTCIF3     /**< stream 3 clear transfer complete interrupt flag  */
}DMA_LIFCR_t;

/**
 * @brief this is an enum which carrying DMA high interrupt flag clear register Bit's Name
 */
typedef enum
{
	CFEIF4=0,  /**< stream 4 clear FIFO error interrupt flag */
	CDMEIF4=2,   /**< stream 4 clear direct mode error interrupt flag */
	CTEIF4,    /**< Stream 4 clear transfer error interrupt flag */
	CHTIF4,    /**< stream 4 clear half transfer interrupt flag  */
	CTCIF4,    /**< stream 4 clear transfer complete interrupt flag  */
	CFEIF5,    /**< stream 5 clear FIFO error interrupt flag  */
	CDMEIF5=8,   /**< stream 5 clear direct mode error interrupt flag */
	CTEIF5,    /**< Stream 5 clear transfer error interrupt flag */
	CHTIF5,    /**< stream 5 clear half transfer interrupt flag  */
	CTCIF5,    /**< stream 5 clear transfer complete interrupt flag  */
	CFEIF6=16,    /**< stream 6 clear FIFO error interrupt flag */
	CDMEIF6=18,   /**< stream 6 clear direct mode error interrupt flag */
	CTEIF6,    /**< Stream 6 clear transfer error interrupt flag */
	CHTIF6,    /**< stream 6 clear half transfer interrupt flag  */
	CTCIF6,    /**< stream 6 clear transfer complete interrupt flag  */
	CFEIF7,    /**< stream 7 clear FIFO error interrupt flag */
	CDMEIF7=24,   /**< stream 7 clear direct mode error interrupt flag */
	CTEIF7,    /**< Stream 7 clear transfer error interrupt flag */
	CHTIF7,    /**< stream 7 clear half transfer interrupt flag  */
	CTCIF7     /**< stream 7 clear transfer complete interrupt flag  */
}DMA_HIFCR_t;

/**
 * @brief this is an enum which carrying DMA stream x configuration register Bit's Name
 */
typedef enum
{
	EN=0,       /**< stream enable / flag stream ready when read low */
	DMEIE,      /**< direct mode error interrupt enable */
	TEIE,       /**< transfer error interrupt enable */
	HTIE,       /**< half transfer interrupt enable */
	TCIE,       /**< transfer complete interrupt enable */
	PFCTRL,     /**< peripheral flow controller */
	DIR_BIT0,       /**< data transfer direction 0 */
	DIR_BIT1,       /**< data transfer direction 1 */
	CIRC,       /**< circular mode */
	PINC,       /**< peripheral increment mode */
	MINC,       /**< memory increment mode */
	PSIZE_BIT0,     /**< peripheral data size 0 */
	PSIZE_BIT1,     /**< peripheral data size 1 */
	MSIZE_BIT0,     /**< memory data size 0 */
	MSIZE_BIT1,     /**< memory data size 1 */
	PINCOS,     /**< peripheral increment offset size */
	PL_BIT0,        /**< priority level 0 */
	PL_BIT1,        /**< priority level 1 */
	DBM,        /**< double-buffer mode */
	CT,         /**< current target (only in double-buffer mode) */
	PBURST_BIT0=21,    /**< peripheral burst transfer configuration 0 */
	PBURST_BIT1,    /**< peripheral burst transfer configuration 1 */
	MBURST_BIT0,    /**< memory burst transfer configuration 0 */
	MBURST_BIT01,    /**< memory burst transfer configuration 1 */
	CHSEL_BIT0,     /**< channel selection 0 */
	CHSEL_BIT1,     /**< channel selection 1 */
	CHSEL_BIT2      /**< channel selection 2 */
}DMA_SxCR_t;


/**
 * @brief this is an enum which carrying DMA stream x FIFO control register Bit's Name
 */
typedef enum
{
	FTH_BIT0=0,     /**< FIFO threshold selection 0 */
	FTH_BIT1,       /**< FIFO threshold selection 1 */
	DMDIS=2,      /**< direct mode disable */
	FS_BIT0,        /**< FIFO status 0 */
	FS_BIT1,        /**< FIFO status 1 */
	FS_BIT2,		/**< FIFO status 2 */
	FEIE =7       /**< FIFO error interrupt enable */
}DMA_SxFCR_t;

/**
 * @brief this is an enum which carrying DMA Data transfer Direction
 */
typedef enum
{
	PERIPHERAL_TO_MEMORY=0,/**< PERIPHERAL_TO_MEMORY */
	MEMORY_TO_PERIPHERAL,  /**< MEMORY_TO_PERIPHERAL */
	MEMORY_TO_MEMORY       /**< MEMORY_TO_MEMORY */
}DataTransDirection_t;

/**
 * @brief this is an enum which carrying peripheral flow controller
 */
typedef enum
{
	DMA_FLOW_CTRL=0,   /**< DMA_FLOW_CTRL */
	PERIPERAL_FLOW_CTRL /**< PERIPERAL_FLOW_CTRL */
}PERI_FLOW_CTRL_t;

/**
 * @brief this is an enum which carrying peripheral increment status enabled or disabled
 */
typedef enum
{
	PINC_DISABLED=0, /**< PINC_DISABLED */
	PINC_ENABLED     /**< PINC_ENABLED */
}PINC_Status_t;

/**
 * @brief this is an enum which carrying  memory increment status enabled or disabled
 */
typedef enum
{
	MINC_DISABLED=0, /**< PINC_DISABLED */
	MINC_ENABLED     /**< PINC_ENABLED */
}MINC_Status_t;


/**
 * @brief this is an enum which carrying Double_BUF_And_CIRMode_Status enabled or disabled
 */
typedef enum
{
	DOUBLE_BUF_DISABLED=0,   /**< DOUBLE_BUF_DISABLED */
	DOUBLE_BUF_ENABLED      /**< DOUBLE_BUF_ENABLED */

}Double_BUF_Status_t;

/**
 * @brief this is an enum which carrying CIRMode_Status enabled or disabled
 */
typedef enum
{
	CIRMODE_DISABLED =0,      /**< CIRMODE_DISABLED */
	CIRMODE_ENABLED           /**< CIRMODE_ENABLED */
}CIRMode_Status_t;


/**
 * @brief this is an enum which carrying FIFO_Status enabled or disabled
 */
typedef enum
{
	FIFOMODE_DISABLED = 0,/**< FIFOMODE_DISABLED */
	FIFOMODE_ENABLED      /**< FIFOMODE_ENABLED */
}FIFO_Status_t;

/**
 * @brief this is an enum which carrying DIRECT_MODE_BIT_Status  enabled or disabled
 */
typedef enum
{
	DIR_MODE_BIT_DISABLED = 0,/**< DIR_MODE_BIT_DISABLED */
	DIR_MODE_BIT_ENABLED      /**< DIR_MODE_BIT_ENABLED */
}DIRECT_MODE_BIT_Status_t;

/**
 * @brief this is an enum which carrying Channel selected
 */
typedef enum
{
	DMA_CH0=0,/**<  channel 0 selected */
	DMA_CH1,  /**<  channel 1 selected */
	DMA_CH2,  /**<  channel 2 selected */
	DMA_CH3,  /**<  channel 3 selected */
	DMA_CH4,  /**<  channel 4 selected */
	DMA_CH5,  /**<  channel 5 selected */
	DMA_CH6,  /**<  channel 6 selected */
	DMA_CH7   /**<  channel 7 selected */
}Channel_Selected_t;

/**
 * @brief this is an enum which carrying stream selected
 */
typedef enum
{
	DMA_STR0=0,/**<  Stream 0 selected */
	DMA_STR1,  /**<  Stream 1 selected */
	DMA_STR2,  /**<  Stream 2 selected */
	DMA_STR3,  /**<  Stream 3 selected */
	DMA_STR4,  /**<  Stream 4 selected */
	DMA_STR5,  /**<  Stream 5 selected */
	DMA_STR6,  /**<  Stream 6 selected */
	DMA_STR7   /**<  Stream 7 selected */
}Stream_Selected_t;

/**
 * @brief this is an enum which carrying FIFO Threshold
 */
typedef enum
{
	QUART_FULL_FIFO =0,   /**< QUART_FULL_FIFO */
	HALF_FULL_FIFO,       /**< HALF_FULL_FIFO */
	THREE_QUART_FULL_FIFO,/**< THREE_QUART_FULL_FIFO */
	FULL_FIFO             /**< FULL_FIFO */
}FIFOThreshold_t;

/**
 * @brief this is an enum which carrying DMA_PeriperalDataAlignment (word,half word , byte)
 */
typedef enum
{
	PDATAALIAGN_BYTE=0,  /**< PDATAALIAGN_BYTE */
	PDATAALIAGN_HALFWORD,/**< PDATAALIAGN_HALFWORD */
	PDATAALIAGN_WORD     /**< PDATAALIAGN_WORD */
}DMA_PeriperalDataAlignment_t;

/**
 * @brief this is an enum which carrying DMA_MemoeryDataAlignment (word,half word , byte)
 */
typedef enum
{
	MDATAALIAGN_BYTE=0,  /**< MDATAALIAGN_BYTE */
	MDATAALIAGN_HALFWORD,/**< MDATAALIAGN_HALFWORD */
	MDATAALIAGN_WORD     /**< MDATAALIAGN_WORD */
}DMA_MemoeryDataAlignment_t;

/**
 * @brief this is an enum which carrying Priority options
 */
typedef enum
{
	PL_LOW=0,   /**< PRIORITY_LOW */
	PL_MEDIUM,  /**< PRIORITY_MEDIUM */
	PL_HIGH,    /**< PRIORITY_HIGH */
	PL_VERY_HIGH/**< PRIORITY_VERY_HIGH */
}Priority_t;

/**
 * @brief this is an enum which carrying DMA OPTIONS DMA1 OR DMA2
 */
typedef enum
{
	DMA1_SEL =0,/**< DMA1_SEL */
	DMA2_SEL    /**< DMA2_SEL */
}DMA_NUM_t;

/**
 * @brief this is an enum which carrying MEMORY_BURST Beats OPTIONS
 */
typedef enum
{
	MEM_SINGLE_TRANS=0,/**< SINGLE_TRANS */
	MEM_INCR4,         /**< incremental burst of 4 beats */
	MEM_INCR8,         /**< incremental burst of 8 beats */
	MEM_INCR16         /**< incremental burst of 16 beats */

}MEMORY_BURST_t;

/**
 * @brief this is an enum which carrying PERIPHERAL_BURST Beats OPTIONS
 */
typedef enum
{
	PERI_SINGLE_TRANS=0,/**< SINGLE_TRANS */
	PERI_INCR4,         /**< incremental burst of 4 beats */
	PERI_INCR8,         /**< incremental burst of 8 beats */
	PERI_INCR16         /**< incremental burst of 16 beats */

}PERIPHERAL_BURST_t;

/**
 * @brief: this is an enum which using to Carry initiate interrupt status
 */
typedef enum
{
	DMA_INT_DISABLED=0,/**< DMA_INT_DISABLED */
	DMA_INT_ENABLED    /**< DMA_INT_ENABLED */
}DMA_INT_Initial_Sts_t;

/**
 * @brief: this is an enum which using to carry interrupt name
 */
typedef enum
{
	  DirectMode_Error_IT = 1, /**< DirectMode_Error_IT */
	  Transfer_Error_IT,       /**< Transfer_Error_IT */
	  HalfTransfer_IT,         /**< HalfTransfer_IT */
	  TransferComplete_IT,     /**< TransferComplete_IT */
	  FIFO_Error_IT = 7        /**< FIFO_Error_IT */
}DMA_Int_Name_t;

typedef struct
{
	DMA_NUM_t  DMA_NUM;
	Stream_Selected_t  Stream_NUM;
	Channel_Selected_t Channel_NUM;
	DataTransDirection_t  DIRMode;
	PINC_Status_t  PINC_Status;
	MINC_Status_t  MINC_Status;
	DMA_PeriperalDataAlignment_t DMA_PeriperalDataAlignment;
	DMA_MemoeryDataAlignment_t  DMA_MemoeryDataAlignment;
	Priority_t  Priority;
	DMA_INT_Initial_Sts_t  DMA_INT_Initial_Sts;
	DMA_Int_Name_t DMA_Int_Name;
	CIRMode_Status_t CIRMode_Status;
	FIFO_Status_t FIFO_Status;
	FIFOThreshold_t FIFOThreshold;
}DMA_Config_t;


/**
 * @brief This function is used to Set DMA channel
 * @param[IN] Copy_psDMA this parameter is a pointer to struct which Carrying DMA configurations
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8SetChannel(DMA_Config_t* Copy_psDMA);

/**
 * @brief This function is used to Set DMA channel
 * @param[IN] Copy_psDMA this parameter is a pointer to struct which Carrying DMA configurations
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8SetStreamPrioirty(DMA_Config_t* Copy_psDMA);

/**
 * @brief This function is used to Set DMA interrupt
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param Copy_EnumInterrupt_Name : this is an enum which using to interrupt name
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8EnabledInt(DMA_NUM_t Copy_EnumDMA_Num , Stream_Selected_t Copy_EnumStream_Num,DMA_Int_Name_t  Copy_EnumInterrupt_Name);

/**
 * @brief This function is used to disable DMA interrupt
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param Copy_EnumInterrupt_Name : this is an enum which using to interrupt name
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8DisabledInt(DMA_NUM_t Copy_EnumDMA_Num , Stream_Selected_t Copy_EnumStream_Num,DMA_Int_Name_t  Copy_EnumInterrupt_Name);
/**
 * @brief This function to initiate DMA Configurations
 * @param[IN] Copy_psDMA this parameter is a pointer to struct which Carrying DMA configurations
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8Init(DMA_Config_t* Copy_psDMA);

/**
 * @brief: this function is used to enable dma (EN)
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t  DMA_u8DMAEnable(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum);

/**
 * @brief: this function is used to disable dma (EN)
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8DMADisable(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum);

/**
 * @brief This function to read DMA flag value
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param[in] Copy_u8FlagName : this is a variable which carrying flag bit number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8ReadFlag(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum ,uint8_t Copy_u8FlagName);

/**
 * @brief This function to clear DMA flag value
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param[in] Copy_u8FlagName : this is a variable which carrying flag bit number
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8ClearFlag(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum,uint8_t Copy_u8FlagName);

/**
 * @brief This function is used to Start DMA Polling
 * @param[in] Copy_psDMA : this is a pointer to struct which carrying Configuration the configuration information for the specified DMA Stream.
 * @param[in] Copy_u32SrcAddress : This is a variable which carrying source address
 * @param[in] Copy_u32DstAddress : This is a variable which carrying destination address
 * @param[in] Copy_u32DataLength : This is a variable which carrying Data length to be transferred from source to destination
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8StartTransfer_Polling(DMA_Config_t *Copy_psDMA, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint32_t Copy_u32DataLength);


/**
 * @brief This function is used to Start DMA USING INTERRUPT
 * @param[in] Copy_psDMA : this is a pointer to struct which carrying Configuration the configuration information for the specified DMA Stream.
 * @param[in] Copy_u32SrcAddress : This is a variable which carrying source address
 * @param[in] Copy_u32DstAddress : This is a variable which carrying destination address
 * @param[in] Copy_u32DataLength : This is a variable which carrying Data length to be transferred from source to destination
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8StartTransfer_IT(DMA_Config_t *Copy_psDMA, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint32_t Copy_u32DataLength);


/**
 * @brief This function is used to Set DMA ISR
 * @param[in] Copy_EnumDMANum : this is enum is used to carry dma number
 * @param[in] Copy_EnumStreamNum : this is enum is used to carry stream number
 * @param[in] Copy_pfFuncPtr :  this is an array of pointer to function which carrying the address of ISR
 * @return Local_u8ErrorState this variable to carry Error State value
 */
uint8_t DMA_u8SetCallBack(DMA_NUM_t Copy_EnumDMANum,Stream_Selected_t Copy_EnumStreamNum,void (*Copy_pfFuncPtr)(void));


#endif /* DMA_INTERFACE_H_ */
