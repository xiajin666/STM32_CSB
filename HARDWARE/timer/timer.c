#include "timer.h"
#include "sys.h"
#include "led.h"
#include "wai_bian.h"

void Timer_SRD_Init(u16 arr,u16 psc)				//��ʱ��
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseInitSture;
	NVIC_InitTypeDef           NVIC_InitSture;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM3
	
	//��ʼ����ʱ��
	TIM_TimeBaseInitSture.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitSture.TIM_Period=5000;
	TIM_TimeBaseInitSture.TIM_Prescaler=7199;
	TIM_TimeBaseInitSture.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitSture);
	
	//��������жϣ�������ʽ�ж�
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_Trigger,ENABLE);
	
	//�ж����ȼ�����
	NVIC_InitSture.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitSture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSture.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitSture.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitSture);
	
	//TIM_Cmd(TIM3,ENABLE);
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		
	}
}

void TIM4_PWM_Init(u16 arr,u16 psc)							//����������
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel3. PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2


	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���

	
	
 
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM3
	

}
















