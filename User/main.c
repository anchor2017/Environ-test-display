/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   Һ����������ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_SysTick.h"
#include "bsp_touch.h"
#include "bsp_adc.h"
#include "bsp_usart1.h"
#include "bsp_ds18b20.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL];

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

extern volatile unsigned char touch_flag;

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	LCD_Init();
	
	/* ϵͳ��ʱ�� 1us ��ʱ��ʼ�� */
  SysTick_Init();
	Delay(0xff);
	
	USART1_Config();
	ADCx_Init();
	DS18B20_Init();
	
  /* GRAMɨ�跽��Ϊ���½�->���Ͻ� */
  Lcd_GramScan(2);
	Delay(0xff);
  LCD_Clear(0, 0, 320, 240, BACKGROUND);
	
	  /* ������IO���жϳ�ʼ�� */
	Touch_Init();
  
/*------------------------------------------------------------------------------------------------------*/
	
/*
		printf("\r\n this is debug info \r\n");
		
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		
			printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
			printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);	
		
		printf("\r\n Temp: %.1f \r\n", DS18B20_Get_Temp());
		Delay(0xffffff);
*/
		
	while(Touch_Calibrate());
	LCD_Clear(0, 0, 320, 240, BACKGROUND);
  
	while( 1 )
  {
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3*100;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3*100;
		
		LCD_DisNum(10, 10, ADC_ConvertedValueLocal[0], RED);
		LCD_DisNum(10, 50, ADC_ConvertedValueLocal[1], RED);
		LCD_DisNum(10, 100, DS18B20_Get_Temp(), RED);
		
		Delay(0xfffff);
//------------------------		
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3*100;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3*100;
		
		LCD_DisNum(100, 10, ADC_ConvertedValueLocal[0], RED);
		LCD_DisNum(100, 50, ADC_ConvertedValueLocal[1], RED);
		LCD_DisNum(100, 100, DS18B20_Get_Temp(), RED);
		
		Delay(0xfffff);
//--------------------------		
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3*100;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3*100;
		
		LCD_DisNum(200, 10, ADC_ConvertedValueLocal[0], RED);
		LCD_DisNum(200, 50, ADC_ConvertedValueLocal[1], RED);
		LCD_DisNum(200, 100, DS18B20_Get_Temp(), RED);
		
		Delay(0xfffff);
//--------------------------
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3*100;
		ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3*100;
		
		LCD_DisNum(300, 10, ADC_ConvertedValueLocal[0], RED);
		LCD_DisNum(300, 50, ADC_ConvertedValueLocal[1], RED);
		LCD_DisNum(300, 100, DS18B20_Get_Temp(), RED);
		
		Delay(0xfffff );
		
		/*
      if(Get_touch_point(&display, Read_2046_2(), &touch_para ) !=DISABLE)      
      {					
        if(display.x>0 && display.x<160)
				{
					while(1)
					{
							LCD_Clear(0, 0, 320, 240, BLUE);
							display.x=0;
							if(Get_touch_point(&display, Read_2046_2(), &touch_para ) !=DISABLE) 
							{
								if(display.x>160 && display.x<320)
								{
									break;
								}
							}
					}
			}
				
				if(display.x>160 && display.x<320)
				{
					
					while(1)
					{
							LCD_Clear(0, 0, 320, 240, GREEN);
						  display.x=0;
							if(Get_touch_point(&display, Read_2046_2(), &touch_para ) !=DISABLE) 
							{
								if(display.x>160 && display.x<320)
								{
									break;
								}
							}
					}

				}
					
      }
		*/
  }
}

/* ------------------------------------------end of file---------------------------------------- */

