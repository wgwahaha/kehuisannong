#include "led.h"  
#include "string.h"
#include "usart3.h"
#include "usart.h"
//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��

u8 flag_led0=0;
u8 flag_led1=0;
u8 flag_motor=2;
u8 flag_feng=0;
u8 flag_beng=0;
u8 flag_hot=0;
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
}

void get_shidukey()
{
    if((NULL != strstr((const char *)USART3_RX_comBUF, "led1")))
		{
			 flag_led1=1;
		   GPIO_SetBits(GPIOE,GPIO_Pin_5);
       GPIO_ResetBits(GPIOB,GPIO_Pin_5);	
       printf("led is 1\r\n");			
		}
		else if((NULL != strstr((const char *)USART3_RX_comBUF, "led0")))
		{
			 flag_led1=0;
		   GPIO_SetBits(GPIOB,GPIO_Pin_5);
       GPIO_ResetBits(GPIOE,GPIO_Pin_5);	
      printf("led is 0\r\n");				
		}
		if((NULL != strstr((const char *)USART3_RX_comBUF, "motor1")))
		{
		   flag_motor=1;
			printf("motor is 1\r\n");	
		}
		else if((NULL != strstr((const char *)USART3_RX_comBUF, "motor0")))
		{
		    flag_motor=0;
			printf("motor is 0\r\n");	
		}
		else if((NULL != strstr((const char *)USART3_RX_comBUF, "motor2")))
		{
			    flag_motor=2;//���ͣ
			printf("motor is 2\r\n");	
		}
		if((NULL != strstr((const char *)USART3_RX_comBUF, "shui0")))
		{
		   flag_beng=0;
			printf("shuibeng is 1\r\n");	
		}
		else if((NULL != strstr((const char *)USART3_RX_comBUF, "shui1")))
		{
			    flag_beng=1;
			printf("shuibeng is 2\r\n");	
		}
		if((NULL != strstr((const char *)USART3_RX_comBUF, "feng1")))
		{
		   flag_feng=1;
			printf("feng is 1\r\n");	
		}
		else if((NULL != strstr((const char *)USART3_RX_comBUF, "feng0")))
		{
		    flag_feng=0;
			printf("feng is 0\r\n");	
		}
		if((NULL != strstr((const char *)USART3_RX_comBUF, "hot1")))
		{
		   flag_hot=1;
			printf("hot is 1\r\n");	
		}
		else if((NULL != strstr((const char *)USART3_RX_comBUF, "hot0")))
		{
		    flag_hot=0;
			printf("hot is 0\r\n");	
		}
}
