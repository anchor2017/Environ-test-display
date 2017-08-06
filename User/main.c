/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   液晶触摸画板实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
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

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal;

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

extern volatile unsigned char touch_flag;

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	uint16_t index;
	/* 系统定时器 1us 定时初始化 */
  SysTick_Init();
	LCD_Init();	
	
	USART1_Config();
	ADC1_Init();
	DS18B20_Init();
	
  /* GRAM扫描方向为左下脚->右上角 */
  //Lcd_GramScan(2);
  //LCD_Clear(0, 0, 320, 240, RED);
	
	  /* 触摸屏IO和中断初始化 */
 // Touch_Init();
  
/*------------------------------------------------------------------------------------------------------*/
  		
	while(1)
	{
		printf("\r\n this is debug info \r\n");
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
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
			ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
			LCD_DisNum(100, 100, ADC_ConvertedValueLocal, RED);
			Delay(0xfffff);
			LCD_DisNum(60, 60, 11111, RED);
		}
		
		/*获取点的坐标*/
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

