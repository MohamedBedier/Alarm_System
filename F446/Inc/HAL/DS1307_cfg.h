/*
 * DS1307_cfg.h
 *
 *  Created on: Dec 28, 2023
 *      Author: AlsharQawy
 */

#ifndef DS1307_CFG_H_
#define DS1307_CFG_H_


/*Choose between (DMA1_SEL, DMA2_SEL)*/
#define  DS_DMA_RX  DMA1_SEL


/*Choose between (DMA_STR0, DMA_STR1, DMA_STR2, DMA_STR3,
                * DMA_STR4, DMA_STR5, DMA_STR6, DMA_STR7)*/
#define  DS_RX_STREAM   DMA_STR2


/*Choose between (DMA_CH0, DMA_CH1, DMA_CH2, DMA_CH3,
                * DMA_CH4, DMA_CH5, DMA_CH6, DMA_CH7)*/
#define  DS_RX_CHANNEL   DMA_CH3


/*Choose between (I2C_1, I2C_2, I2C_3)*/
#define  DS_I2C  I2C_3


/*Choose between (PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG, PORTH)*/
#define  DS_SCL_PORT   PORTA
#define  DS_SDA_PORT   PORTC


/*Choose between (PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8,
 *                PIN9, PIN10, PIN11, PIN112, PIN13, PIN14, PIN15)*/
#define  DS_SCL_PIN   PIN8
#define  DS_SDA_PIN   PIN9


/*Choose between (AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8,
 *                AF9, AF10, AF11, AF12, AF13, AF14, AF15)*/
#define  DS_ALT_FUNC   AF4




/*Choose between
(DMA1_Stream0_IRQ, DMA1_Stream1_IRQ, DMA1_Stream2_IRQ, DMA1_Stream3_IRQ, DMA1_Stream4_IRQ,
 DMA1_Stream5_IRQ, DMA1_Stream6_IRQ, DMA1_Stream7_IRQ,
 DMA2_Stream0_IRQ, DMA2_Stream1_IRQ, DMA2_Stream2_IRQ, DMA2_Stream3_IRQ, DMA2_Stream4_IRQ,
 DMA2_Stream5_IRQ, DMA2_Stream6_IRQ, DMA2_Stream7_IRQ)*/
#define  DS_DMA_STREAM_NVIC_IRQ_RX   DMA1_Stream2_IRQ



/**********************		NOW TIME SETTINGS	 **********************/

#define  NOW_SECONDS    5
#define  NOW_MINUTES    7
#define  NOW_HOURS      1
#define  NOW_DAY        1
#define  NOW_DATE       7
#define  NOW_MONTH      1
#define  NOW_YEAR       2024

/*Choose between (STYELE_24H, STYELE_12H)*/
#define  NOW_HOURS_STYLE     STYELE_12H
/*Choose between (NOW_AM, NOW_PM) -> only if the style is 12H style*/
#define  NOW_AM_PM    NOW_PM


#endif /* DS1307_CFG_H_ */
