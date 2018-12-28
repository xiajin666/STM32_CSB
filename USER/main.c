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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init();         	//��ʼ���������˿�
	KEY_Init();         	//��ʼ���밴�����ӵ�Ӳ���ӿ�
	LCD_Init();	
	//EXTIX_Init();		 	//�ⲿ�жϳ�ʼ��
	//LED0=0;					//����LED0
	Timer_SRD_Init(5000,7199);
	Wave_SRD_Init();
	IWDG_Init(4,625);
	 
	 
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(20,50,200,16,16,"JIANGHUAICHUANGXISHIYANSHI");	
	POINT_COLOR=GREEN;
	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2018/10/19");	
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
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
			IWDG_Feed();//���WK_UP����,��ι��
		}
		delay_ms(10);
    wdg=1;    	
	}
 }
