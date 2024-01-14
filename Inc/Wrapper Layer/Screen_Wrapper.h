/*
 * Screen_Wrapper.h
 *
 *  Created on: Jan 13, 2024
 *      Author: AlsharQawy
 */

#ifndef WRAPPER_LAYER_SCREEN_WRAPPER_H_
#define WRAPPER_LAYER_SCREEN_WRAPPER_H_

void Screen_Init(void);
void Screen_Clear(void);
void Screen_SetCursor(uint8_t row, uint8_t col);
void Screen_WriteString(char* str);
void Screen_WriteNumber(uint8_t num);
void Screen_WriteNumberInTwoDigits(uint8_t num);


#endif /* WRAPPER_LAYER_SCREEN_WRAPPER_H_ */
