#include "stm32f4xx.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defines.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include "tm_stm32f4_stmpe811.h"
#include <stdio.h>
#include "common.h"

int CaptureNumber,counter,Time,capture,f,t;

void GPIO_init(void);
void USART_init(void);
void TIMER_init(void);
void board_init(void);
void TIMER_Capture(void);
void LCD_config(void);
void LCD_GPIOConfig(void);
void LCD(void);
void ADC_init(void);
int tempsense(void);
void printtemp(int page);
