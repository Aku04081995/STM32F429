#include "led.h"


char str[30];
float TemperatureValue ;

int main()
{
	TM_STMPE811_TouchData touchData;
	touchData.orientation = TM_STMPE811_Orientation_Landscape_2;
	board_init();
	tempsense();
	TM_ILI9341_Puts(80,60,"Welcome!!",&TM_Font_16x26,ILI9341_COLOR_RED,ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(60,100,"Today's Temprature",&TM_Font_11x18,ILI9341_COLOR_RED,ILI9341_COLOR_WHITE);
	printtemp(0);
	led_blinkALT(5);
	TM_ILI9341_Puts(5,150,"PRESS THE BUTTON TO CONTINUE",&TM_Font_11x18,ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
	led_blinkRed(1);
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(10,60,"PRINTING......",&TM_Font_11x18,ILI9341_COLOR_RED,ILI9341_COLOR_WHITE);
	printtemp(1);
	usart_Tx_str("Hello!");
	led_blinkGreen(2);
	delay1(50000000);
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(0,60,"TOUCH TO CONTINUE",&TM_Font_11x18,ILI9341_COLOR_RED,ILI9341_COLOR_WHITE);
	printtemp(1);
	while(TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Released)
	led_blinkRed(1);
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	led_blinkGreen(2);
	//while(1)
	//	TIMER_Capture();
	//led_blinkGreen(2);
	//tempsense();
		LCD();
	while(1);
}

void TIMER_Capture(void)
{
	while(CaptureNumber !=2)
	{
		if(TIM_GetFlagStatus(TIM2,TIM_FLAG_CC1)==SET)
		{
			TIM_ClearFlag(TIM2,TIM_FLAG_CC1);
			if(CaptureNumber == 0)
			{
				counter = TIM_GetCapture1(TIM2); 
				CaptureNumber = 1;
			}
			else if(CaptureNumber == 1) 
			{
				if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) != SET)
				{
					Time = TIM_GetCapture1(TIM2);
					Time = Time - counter;
				}
				else
				{
					TIM_ClearFlag(TIM2,TIM_FLAG_Update);   
					Time = 0xFFFF - counter + TIM_GetCapture1(TIM2)+1;  
				}
				//CaptureNumber = 0;
				if(Time!=0)
				{
					f= 45000000/Time;
					usart_Tx(f);
					usart_Tx_str("Hz");
					CaptureNumber++;
				}	
			}
		}
	}	
}
	


void USART1_IRQHandler(void)
{
	if( USART_GetITStatus(USART1, USART_IT_RXNE) )
	{
		t = USART1->DR; // the character from the USART1 data register is saved in t
		usart_Tx(t);
	}
}

void LCD(void)
{
    //FIll lcd with color
    TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
    //Draw white circle
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(75, 60, "Hello World", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(75, 80, "Aakash Singh", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
    //Draw line with custom color 0x0005
    TM_ILI9341_DrawLine(10, 120, 310, 120, 0xFFFF);
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(65, 130, "STM32F4 Discovery", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(60, 150, "ILI9341 LCD Module", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
	delay1(500000000);
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);	
	TM_ILI9341_Puts(75, 60, "Hello World", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(75, 80, "Aakash Singh", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
    //Draw line with custom color 0x0005
    TM_ILI9341_DrawLine(10, 120, 310, 120, 0xFFFF);
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(65, 130, "Standby In", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
		TM_ILI9341_Puts(70, 150, ".......3", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
		delay1(50000000);
		TM_ILI9341_Puts(70, 150, ".......2", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
		delay1(50000000);
		TM_ILI9341_Puts(70, 150, ".......1", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
		delay1(50000000);
		TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
		
	
}
void board_init(void)
{
	GPIO_init();
	USART_init();
	TIMER_init();
	TM_ILI9341_Init();
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
	TM_STMPE811_Init();
	ADC_init();
	
}
void GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitDef;
	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); 
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitDef);
 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitDef);
				
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
		GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitDef);
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_TIM4);
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitDef);
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART1);
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_10;
		GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
		GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitDef);

		
	/*
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource2, GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_TIM2);
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitDef);*/
		
}		



void USART_init(void)
{	
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		USART_InitStruct.USART_BaudRate = 9600;
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStruct.USART_Parity = USART_Parity_No;
		USART_InitStruct.USART_StopBits = USART_StopBits_1;
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;
		USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
		USART_Init(USART1, &USART_InitStruct);
		USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
 

	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
 

}



void TIMER_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_BaseStruct;
	TIM_ICInitTypeDef			TIM_ICDef;
	TIM_OCInitTypeDef TIM_OCStruct;	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		TIM_BaseStruct.TIM_Prescaler = 0;
		TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseStruct.TIM_Period = 45000; /* 1kHz PWM */
		TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_BaseStruct.TIM_RepetitionCounter = 0;
		TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);
		TIM_Cmd(TIM4, ENABLE);
		
		TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCStruct.TIM_Pulse = (45000/2); //50% duty cycle
		TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM4, &TIM_OCStruct);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		TIM_BaseStruct.TIM_Prescaler = 0;
		TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseStruct.TIM_Period = 0xFFFF; 
		TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_BaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
	
		TIM_ICDef.TIM_Channel = TIM_Channel_1;
		TIM_ICDef.TIM_ICFilter = 0;
		TIM_ICDef.TIM_ICPolarity = TIM_ICPolarity_Rising;
		TIM_ICDef.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		TIM_ICDef.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2, &TIM_ICDef);
	TIM_Cmd(TIM2, ENABLE);
		
}

void ADC_init(void)
{
	ADC_InitTypeDef	ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
		ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
		ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div8;
		ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
		ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInit(&ADC_CommonInitStruct);
		ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
		ADC_InitStruct.ADC_ScanConvMode = DISABLE;
		ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStruct.ADC_NbrOfConversion = 1;
		ADC_Init(ADC1, &ADC_InitStruct);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 1, ADC_SampleTime_144Cycles);
		ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
}
int tempsense(void)
{
	ADC_SoftwareStartConv(ADC1); 
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
	TemperatureValue = ADC_GetConversionValue(ADC1);
	TemperatureValue *= (3.0f / 4096.0f);
	TemperatureValue -= (float)0.760; 		// Subtract the reference voltage at 25°C
	TemperatureValue /= (float).0025; 		// Divide by slope 2.5mV
	TemperatureValue += (float)25.0;
	return (TemperatureValue);
}
void printtemp(int page)
{
	sprintf(str,"%f C",TemperatureValue);
	if(page==0)
	{
		if (TemperatureValue<20)
			TM_ILI9341_Puts(100,120,str,&TM_Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
		else if (TemperatureValue>35)
			TM_ILI9341_Puts(100,120,str,&TM_Font_11x18,ILI9341_COLOR_RED,ILI9341_COLOR_WHITE);
		else
			TM_ILI9341_Puts(100,120,str,&TM_Font_11x18,ILI9341_COLOR_ORANGE,ILI9341_COLOR_WHITE);
	}
	else if(page==1)
	{
		if (TemperatureValue<20)
			TM_ILI9341_Puts(240, 225,str,&TM_Font_7x10,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
		else if (TemperatureValue>35)
			TM_ILI9341_Puts(240,225,str,&TM_Font_7x10,ILI9341_COLOR_RED,ILI9341_COLOR_WHITE);
		else
			TM_ILI9341_Puts(240,225,str,&TM_Font_7x10,ILI9341_COLOR_ORANGE,ILI9341_COLOR_WHITE);
	}
}

