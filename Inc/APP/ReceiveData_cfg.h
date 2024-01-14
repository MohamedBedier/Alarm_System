/*
 * SendData_cfg.h
 *
 *  Created on: Jan 9, 2024
 *      Author: AlsharQawy
 */

#ifndef APP_SENDDATA_CFG_H_
#define APP_SENDDATA_CFG_H_



/*Choose between (SPI_1, SPI_2)*/
#define  RECEIVE_DATA_SPI   SPI_1


/*Choose between (PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG)*/
#define  SPI_SCK_PORT    PORTA
#define  SPI_MOSI_PORT   PORTA
#define  EXT_PORT        PORTA


/*Choose between (PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7, PIN8,
 *                PIN9, PIN10, PIN11, PIN112, PIN13, PIN14, PIN15)*/
#define  SPI_SCK_PIN     PIN5
#define  SPI_MOSI_PIN    PIN7
#define  EXT_PIN         PIN10








#endif /* APP_SENDDATA_CFG_H_ */
