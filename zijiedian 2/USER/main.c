#include "stm32f10x.h"
#include "24l01.h"
#include "usart.h"
#include "delay.h"
#include "usart2.h"
#include "led.h"
int main()
{
	  u8 tmp_buf[11];
		delay_init();
	
    uart_init(115200);
    usart2_init(115200);
	  init_led();
			NRF24L01_Init();
		while(NRF24L01_Check())
	  printf("24L01 IS ERROR");
		
	  printf("24L01 IS SUCCESS");
		
		NRF24L01_RX_Mode();
   while(1)
	 {
	    if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				tmp_buf[10]=0;//�����ַ���������
        if(tmp_buf[0]=='L') //��
				{
				    if(tmp_buf[1]=='K')
						{
						    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
						}
						else 
						{
							
							
						    GPIO_SetBits(GPIOA,GPIO_Pin_4);
						}
						printf("light is %s\n",tmp_buf);
				}
				if(tmp_buf[2]=='M')//���
				{
				    if(tmp_buf[3]=='K')  //��
						{
						    GPIO_SetBits(GPIOA,GPIO_Pin_5);
							  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
						}
						else if(tmp_buf[3]=='G')  //��
						{
						    GPIO_ResetBits(GPIOA,GPIO_Pin_5);
							  GPIO_SetBits(GPIOA,GPIO_Pin_6);
						}	
            else if(tmp_buf[3]=='S')	
						{
						    GPIO_ResetBits(GPIOA,GPIO_Pin_5);
							  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
						}	
            printf("motor is %s\n",tmp_buf);						
				} 
				if(tmp_buf[4]=='B')//ˮ��
				{
				    if(tmp_buf[5]=='K')  //��
						{
						    GPIO_ResetBits(GPIOC,GPIO_Pin_1);
						}
						else if(tmp_buf[5]=='G')  //��
						{
						    GPIO_SetBits(GPIOC,GPIO_Pin_1);
						}	
            printf("shuibeng is %s\n",tmp_buf);						
				} 
				if(tmp_buf[6]=='F')//����
				{
				    if(tmp_buf[7]=='K')  //��
						{
						    GPIO_SetBits(GPIOC,GPIO_Pin_2);
							 GPIO_ResetBits(GPIOC,GPIO_Pin_4);
						}
						else if(tmp_buf[7]=='G')  //��
						{
							  GPIO_ResetBits(GPIOC,GPIO_Pin_2);
							  GPIO_ResetBits(GPIOC,GPIO_Pin_4);
						}	
            printf("fengshan is %s\n",tmp_buf);						
				} 
				if(tmp_buf[8]=='H')//���ȹ�
				{
				    if(tmp_buf[9]=='K')  //��
						{
						    GPIO_ResetBits(GPIOC,GPIO_Pin_3);
						}
						else if(tmp_buf[9]=='G')  //��
						{
							  GPIO_SetBits(GPIOC,GPIO_Pin_3);
						}	
            printf("jiareguan is %s\n",tmp_buf);						
				} 				
			}
	 }
}

