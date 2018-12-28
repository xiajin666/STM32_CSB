#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"
#include "beep.h"
#include "lcd.h"
#include "timer.h"
#include "wave.h"
#include "wai_bian.h"
#include "wdg.h"




 int main(void)
 {		
 
	uint16_t wdg;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();		  		//初始化与LED连接的硬件接口
	BEEP_Init();         	//初始化蜂鸣器端口
	KEY_Init();         	//初始化与按键连接的硬件接口
	LCD_Init();	
	//EXTIX_Init();		 	//外部中断初始化
	//LED0=0;					//点亮LED0
	Timer_SRD_Init(5000,7199);
	Wave_SRD_Init();
	IWDG_Init(4,625);
	 
	 
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(20,50,200,16,16,"JIANGHUAICHUANGXISHIYANSHI");	
	POINT_COLOR=GREEN;
	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2018/10/19");	
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,"Distance:000.000cm");	      
	//LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");
	TIM4_PWM_Init(899,0);	
	 
	while(1)
	{	    
		Wave_SRD_Strat();	
        //LED1=!LED1;
        delay_ms(2000);
		if(Distance_zhen>20||Distance_zhen<5)
		{
			TIM_SetCompare3(TIM4,899);
		}
		else
		{
			TIM_SetCompare3(TIM4,300);
		}
		if(wdg==1)
		{
			IWDG_Feed();//如果WK_UP按下,则喂狗
		}
		delay_ms(10);
    wdg=1;    	
	}
 }
