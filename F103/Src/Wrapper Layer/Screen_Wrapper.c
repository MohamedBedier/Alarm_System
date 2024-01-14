/***********************************************************
* @file Screen_Wrapper.c
* @Author Abdullah AlsharQawy
* @Brief Functions for the Screen driver wrapper functions
***********************************************************/
#include <stdint.h>
#include <ErrType.h>

#include <DoTasks.h>
#include <LCD_Interface.h>
#include <Screen_Wrapper.h>


void Screen_Init(void)
{
	LCD_Init();
}

void Screen_Clear(void)
{
	LCD_Clear();
}

void Screen_SetCursor(uint8_t row, uint8_t col)
{
	LCD_SetCursor(row, col);
}

void Screen_WriteString(char* str)
{
	LCD_WriteString(str);
}

void Screen_WriteNumber(uint8_t num)
{
	LCD_WriteNumber(num);
}

void Screen_WriteNumberInTwoDigits(uint8_t num)
{
	LCD_WriteNumberInTwoDigits(num);
}









