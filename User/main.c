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
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;

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
	uint16_t index;
	/* ϵͳ��ʱ�� 1us ��ʱ��ʼ�� */
  SysTick_Init();
	LCD_Init();	
	
	USART1_Config();
	ADC1_Init();
	DS18B20_Init();
	
  /* GRAMɨ�跽��Ϊ���½�->���Ͻ� */
  //Lcd_GramScan(2);
  //LCD_Clear(0, 0, 320, 240, RED);
	
	  /* ������IO���жϳ�ʼ�� */
 // Touch_Init();
  
/*------------------------------------------------------------------------------------------------------*/
  		
	while(1)
	{
		printf("\r\n this is debug info \r\n");
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
		printf("\r\n CO2: %lf \r\n", ADC_ConvertedValueLocal);
		
		printf("\r\n Temp: %.1f \r\n", DS18B20_Get_Temp());
		Delay(0xffffff);
	}
		
	while(Touch_Calibrate());
  
	while( 1 )
  {
     LCD_Clear(0, 0, 160, 240, WHITE);
		 LCD_Clear(160, 0, 320, 240, BLACK);
		
		while(1)
		{
			ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
			LCD_DisNum(100, 100, ADC_ConvertedValueLocal, RED);
			Delay(0xfffff);
			LCD_DisNum(60, 60, 11111, RED);
		}
		
		/*��ȡ�������*/
      if(Get_touch_point(&display, Read_2046_2(), &touch_para ) !=DISABLE)      
      {					
        if(display.x>0 && display.x<160)
				{
					for(index=100;index>0;index--)
					{	}
					if(display.x>0 && display.x<160)
					{	
					while(1)
					{
							LCD_Clear(0, 0, 320, 240, BLUE);
							display.x=0;
							Get_touch_point(&display, Read_2046_2(), &touch_para );
							if(display.x>0 && display.x<160)
							{
								break;
							}
					}
				}
				}
				
				if(display.x>160 && display.x<320)
				{
					for(index=100;index>0;index--)
					{	}
					if(display.x>0 && display.x<160)
					{
					while(1)
					{
							LCD_Clear(0, 0, 320, 240, GREEN);
						  display.x=0;
							Get_touch_point(&display, Read_2046_2(), &touch_para );
							if(display.x>160 && display.x<320)
							{
								break;
							}
					}
				}
				}
					
      }

  }
}

/* ------------------------------------------end of file---------------------------------------- */

