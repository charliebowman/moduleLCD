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
void LCD_SendCmd(uint8_t);
void LCD_SendData(uint8_t);
void LCD_Init(void);

#endif /* INC_ADA181_H_ */
