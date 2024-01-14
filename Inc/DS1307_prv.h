/*
 * DS1307_prv.h
 *
 *  Created on: Dec 28, 2023
 *      Author: AlsharQawy
 */

#ifndef DS1307_PRV_H_
#define DS1307_PRV_H_

typedef struct
{
	uint8_t PointerRegister;
	uint8_t Seconds;
	uint8_t Minutes;
	uint8_t Hours;
	uint8_t Day;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
}DS_Time_t;


#define  DS_SLAVE_ADDRESS     0b01101000U
#define  DS_RECEIVE_BYTES     7U
#define  DS_TRANSMIT_BYTES    8U

#define  STYELE_12H    1
#define  STYELE_24H    0

#define  NOW_AM   0
#define  NOW_PM   1

#endif /* DS1307_PRV_H_ */
