/**
 * @LayerArchitecture : Library
 * @File_Name : defines.h
 * @ Auther: MOHAMED BEDIER MOHAMED
 * Verision :1.00
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define INIT_VALUE_BY_ZERO  0u
#define INIT_VALUE_BY_ONE  1u

#define ZERO_VALUE  0u
#define ONE_VALUE   1u

#define  NULL  ((void*)0)

#define OK             0u
#define NOK  		   1u
#define NULL_PTR_ERR   2u
#define TIMEOUT_ERR    3u
#define BUSY_STATE_ERR 4u

#define FLAG_RAISED  1U

#define FLAG_IS_IDLE   0U
#define FLAG_IS_BUSY   1U

/////////////////////////////////////

//@ErrorStatus_t
typedef enum
{
	_OK=0,
	_NOK,
	NULLPTR,
	OUT_OF_RANGE,
	UNKNOWN,
	RUNTIME_OUT
}ErrorStatus_t;


#define  NullPtr   ((void*)0)

typedef void(*Fptr)(void);


#endif /* DEFINES_H_ */
