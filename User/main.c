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
  /* GRAM扫描方向为左下脚->右上角 */
  Lcd_GramScan(2);
  LCD_Clear(0, 0, 320, 240, RED);
  
/*------------------------------------------------------------------------------------------------------*/
  
  /* 触摸屏IO和中断初始化 */
  Touch_Init();

	while(Touch_Calibrate());
  
	while( 1 )
  {
     LCD_Clear(0, 0, 160, 240, WHITE);
		 LCD_Clear(160, 0, 320, 240, BLACK);
		
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

