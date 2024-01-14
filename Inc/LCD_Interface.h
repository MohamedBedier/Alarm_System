
#ifndef LCD_H_
#define LCD_H_



void LCD_Init(void);
void LCD_Clear(void);
void LCD_WriteNumber(int32_t num);
void LCD_WriteChar(uint8_t ch);
void LCD_WriteString(char* str);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_WriteNumberInTwoDigits(uint8_t num);




#endif /* LCD_H_ */
