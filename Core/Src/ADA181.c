/*
 * ADA181.c
 *
 *  Created on: Apr 12, 2021
 *      Author: charl
 */


#include "stm32l4xx_hal.h"
#define LCD_Port GPIOA

#define LCD_RS 1 	// RS (Register Select): 0 = command, 1 = data
#define LCD_RW 3	// R/W ----------------- Connected to ground
#define LCD_EN 4	// Enable Pin

#define LCD_D4 5 	// GPIO pin for DB 4
#define LCD_D5 6 	// GPIO pin for DB 5
#define LCD_D6 7 	// GPIO pin for DB 6
#define LCD_D7 2 	// GPIO pin for DB 7

void LCD_PutNibble(uint8_t c) {

	if (c & 0x08)
		LCD_Port->ODR |= 1<<LCD_D7;
	else
		LCD_Port->ODR &= ~(1<<LCD_D7);

	if (c & 0x04)
		LCD_Port->ODR |= 1<<LCD_D6;
	else
		LCD_Port->ODR &= ~(1<<LCD_D6);

	if (c & 0x02)
		LCD_Port->ODR |= 1<<LCD_D5;
	else
		LCD_Port->ODR &= ~(1<<LCD_D5);

	if (c & 0x01)
		LCD_Port->ODR |= 1<<LCD_D4;
	else
		LCD_Port->ODR &= ~(1<<LCD_D4);

}

void LCD_Pulse(void) {

	LCD_Port->ODR |= 1<<LCD_EN;
	HAL_Delay(4);
	LCD_Port->ODR &= ~(1<<LCD_EN);
	HAL_Delay(4);
}

void LCD_SendCmd(char c) {

	// RS: 0 = command, 1 = data
	LCD_Port->ODR &= ~(1<<LCD_RS);

	// Send Upper 4 bits
	LCD_PutNibble( c >> 4 );
	LCD_Pulse();

	// Send Lower 4 bits
	LCD_PutNibble( c & 0x0F );
	LCD_Pulse();

	// Return to default
	LCD_Port->ODR |= 1<<LCD_RS;
}

void LCD_SendData(char c) {

	// RS defaults to 1
	// No need to change RS

	// Send Upper 4 bits
	LCD_PutNibble( c >> 4 );
	LCD_Pulse();

	// Send Lower 4 bits
	LCD_PutNibble( c & 0x0F );
	LCD_Pulse();


}

void LCD_Init(void) {

	HAL_Delay(50);
	GPIOA->ODR |= 1 << 5;
	GPIOA->ODR |= 1 << 6;
	LCD_Pulse();
	GPIOA->ODR &= ~( 1<< 5);
	GPIOA->ODR &= ~( 1<< 6);
	HAL_Delay(5);
	GPIOA->ODR |= 1 << 5;
	GPIOA->ODR |= 1 << 6;
	LCD_Pulse();
	GPIOA->ODR &= ~( 1<< 5);
	GPIOA->ODR &= ~( 1<< 6);
	HAL_Delay(1);
	GPIOA->ODR |= 1 << 5;
	GPIOA->ODR |= 1 << 6;
	LCD_Pulse();
	GPIOA->ODR &= ~( 1<< 5);
	GPIOA->ODR &= ~( 1<< 6);

	// 4 bit mode
	HAL_Delay(1);
	GPIOA->ODR |= 1 << 6;
	LCD_Pulse();
	GPIOA->ODR &= ~( 1<< 6);

	// Initialisation
	HAL_Delay(1);
	LCD_SendCmd(0x2C);
	HAL_Delay(5);
	LCD_SendCmd(0x08);
	HAL_Delay(5);
	LCD_SendCmd(0x01);
	HAL_Delay(5);
	LCD_SendCmd(0x06);
	HAL_Delay(5);

	// Turn display on
	LCD_SendCmd(0x0C);

}

void LCD_SendString (char *str) {
	while (*str) LCD_SendData(*str++);
}

