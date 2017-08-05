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
  /* GRAMɨ�跽��Ϊ���½�->���Ͻ� */
  Lcd_GramScan(2);
  LCD_Clear(0, 0, 320, 240, RED);
  
/*------------------------------------------------------------------------------------------------------*/
  
  /* ������IO���жϳ�ʼ�� */
  Touch_Init();

	while(Touch_Calibrate());
  
	while( 1 )
  {
     LCD_Clear(0, 0, 160, 240, WHITE);
		 LCD_Clear(160, 0, 320, 240, BLACK);
		
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

