#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "usart2.h"
#include "usart.h"
#include "usart3.h"
#include "EdpKit.h"
#include "esp8266.h"
#include "delay.h"
#include "string.h"
#include "time2.h"
#include "24l01.h"
void esp8266()
{
 u3_printf(AT);
	  delay_ms(500);
	 u3_printf(CWMODE);
	 delay_ms(500);
	 u3_printf(RST);
	 delay_ms(500);
	 u3_printf(CIFSR);
	delay_ms(500);
	 u3_printf(CWJAP);
	delay_ms(1000);
	delay_ms(1000);
		delay_ms(1000);
			delay_ms(1000);
		delay_ms(1000);
				delay_ms(1000);
			delay_ms(1000);
		delay_ms(1000);
	 u3_printf(CIPSTART);
		delay_ms(1000);
		delay_ms(1000);	
	// u3_printf(CIPMODE);
		delay_ms(1000);
		delay_ms(1000);
		u3_printf(CIPMODE);
   delay_ms(1000);
   delay_ms(1000);
   delay_ms(1000);
    delay_ms(1000);
		ESP8266_DevLink(DEVICEID,APIKEY,20);
		delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);
    delay_ms(1000);  
}

int main()
{
	//i=0;
	tmp_buf_RX[0]='2';
	tmp_buf_RX[1]='1';
	tmp_buf_RX[2]='1';
	tmp_buf_RX[3]=0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	INIT_KEY();
	uart_init(115200);
	usart2_init(115200);
  usart3_init(115200);
  esp8266();
	//ESP8266_DevLink(DEVICEID,APIKEY,20);    //和平台建立设备连接
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
  GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	TIM2_Int_Init(999,7200-1);
	 NRF24L01_Init();
			while(NRF24L01_Check())
		printf("24L01 IS ERROR\r\n");
		printf("24L01 IS SUCCESS\r\n");
	while(1)
	{ 

			if(!(ESP8266_CheckStatus(30)))    
			{
				ESP8266_SendDat(); 
        printf("%s\r\n",send_buf);				
			}
			else
			{
			 esp8266();
	     ESP8266_DevLink(DEVICEID,APIKEY,20);    //和平台建立设备连接
			}
			//delay_ms(500);	
	}
}

