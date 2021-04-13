/*
 * ADA181.h
 *
 *  Created on: Apr 12, 2021
 *      Author: charl
 */

#ifndef INC_ADA181_H_
#define INC_ADA181_H_

void LCD_PutNibble(uint8_t);
void LCD_Pulse(void);
void LCD_SendCmd(char);
void LCD_SendData(char);
void LCD_Init(void);
void LCD_SendString(char*);

#endif /* INC_ADA181_H_ */
