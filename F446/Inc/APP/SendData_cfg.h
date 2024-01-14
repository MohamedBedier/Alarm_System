/*
 * SendData_cfg.h
 *
 *  Created on: Jan 9, 2024
 *      Author: AlsharQawy
 */

#ifndef APP_SENDDATA_CFG_H_
#define APP_SENDDATA_CFG_H_


/*Choose between (SPI_1, SPI_2, SPI_3, SPI_4)*/
#define  SEND_DATA_SPI   SPI_1


/*Choose between (PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG, PORTH)*/
#define  SPI_SCK_PORT    PORTB
#define  SPI_MOSI_PORT   PORTB
#define  EXT_PORT        PORTA


/*Choose between (PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8,
 *                PIN9, PIN10, PIN11, PIN112, PIN13, PIN14, PIN15)*/
#define  SPI_SCK_PIN    PIN3
#define  SPI_MOSI_PIN   PIN5
#define  EXT_PIN        PIN10


/*Choose between (AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8,
 *                AF9, AF10, AF11, AF12, AF13, AF14, AF15)*/
#define  SPI_ALT_FUNC   AF5


#endif /* APP_SENDDATA_CFG_H_ */
