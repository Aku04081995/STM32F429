#include "stm32f4xx.h"


#define led_red							GPIO_Pin_14
#define led_green						GPIO_Pin_13


int usart_Tx(int ch);
void usart_Tx_str(char *str);
void delay1(int a);
void led_blinkALT(int x);
void led_blinkGreen(int x);
void led_blinkRed(int x);
void led_redON(void);
void led_redOFF(void);
void led_greenON(void);
void led_greenOFF(void);

