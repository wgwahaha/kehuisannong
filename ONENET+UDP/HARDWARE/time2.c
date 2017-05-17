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
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//��ʱ��2�жϷ������
int s=0;
u8 tmp_buf_RX[14];
u8 tmp_buf_TX0[2];
u8 tmp_buf_TX1[11];
u8 flag_date=20;
//void TIM2_IRQHandler(void)
//{
//    static int i=0;


//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//�Ǹ����ж�
//    {
//        if(++i>=10)
//        {
//            i=0;
//					  if(++s>=60)
//                 s=0;
//         
//            if(s%30<=10)
//            {
//							if(flag_led0==1)
//							{
//							  tmp_buf_TX0[0]='S';
//                tmp_buf_TX0[1]=0;
//							}
//							else
//							{
//							  tmp_buf_TX0[0]='0';
//                tmp_buf_TX0[1]=0;							
//							}
//							  if(s%30>=0&&s%30<3)
//								    delay_ms(1000),NRF24L01_TX_Mode0();

//                if(NRF24L01_TxPacket(tmp_buf_TX0)==TX_OK)
//                    printf("TX0 IS %c\r\n",tmp_buf_TX0[0]);
//                else
//                    printf("ERROR");
//            }
//            else if(s%30>10&&s%30<=20)
//            {
//							if(flag_led1==1)
//							{
//							  tmp_buf_TX1[0]='1';
//                tmp_buf_TX1[1]=0;
//							}
//							else
//							{
//							  tmp_buf_TX1[0]='2';
//                tmp_buf_TX1[1]=0;							
//							}
//							  if(s%30>=11&&s%30<14)
//                NRF24L01_TX_Mode1();
//                if(NRF24L01_TxPacket(tmp_buf_TX1)==TX_OK)
//                    printf("TX1 IS %c\r\n",tmp_buf_TX1[0]);
//                else
//                    printf("ERROR");
//            }
//            else if(s%30>20)
//            {
//							   if(s%30>=20&&s%30<24)
//                NRF24L01_RX_Mode();
//								 delay_ms(200);
//                if(NRF24L01_RxPacket(tmp_buf_RX)==0)//һ�����յ���Ϣ,����ʾ����.
//                {
//                    tmp_buf_RX[6]=0;//�����ַ���������
//                    printf("RX IS %s\r\n",tmp_buf_RX);
//                }
//                else
//                    printf("RX is ERROR");	
//						}	
//				}						
//    }
//    
//			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIM2�����жϱ�־
//}
//[0]Ϊ�� [2]Ϊ��� [4] Ϊˮ�� [6]Ϊ���� [8]Ϊ���ȹ�
void TIM2_IRQHandler(void)
{
      static u8 i=0;
	    static u8 flag_flag=0;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//�Ǹ����ж�
    {
			  i++;
        if(i>2)
        {
            i=0;
					   s++;
					  if(s>=10)
                 s=0;   
            if(s%10<=6)
            {
								if(flag_led1==1)  //���ڿ��Ƶ�
								{
									tmp_buf_TX1[0]='L';
									tmp_buf_TX1[1]='K';
									//tmp_buf_TX1[2]=0;	
								}
								else if(flag_led1==0)//�ƹ�
								{
									tmp_buf_TX1[0]='L';
									tmp_buf_TX1[1]='G';
									//tmp_buf_TX1[2]=0;							
								}							
								if(flag_motor==1)  //���
								{
									tmp_buf_TX1[2]='M';
									tmp_buf_TX1[3]='K';
								//	tmp_buf_TX1[2]=0;							   
								}
								else if(flag_motor==0)
								{
									tmp_buf_TX1[2]='M';
									tmp_buf_TX1[3]='G';
								//	tmp_buf_TX1[2]=0;							
								}
								else if(flag_motor==2)
								{
										tmp_buf_TX1[2]='M';
										tmp_buf_TX1[3]='S';
								//		 tmp_buf_TX1[2]=0;							
								}							
								if(flag_beng==1)   //ˮ��
								{
											tmp_buf_TX1[4]='B';
											tmp_buf_TX1[5]='K';
									//		tmp_buf_TX1[2]=0;									
								}
								else if(flag_beng==0)
								{
											tmp_buf_TX1[4]='B';
											tmp_buf_TX1[5]='G';
									//		tmp_buf_TX1[2]=0;									  
								}
								if(flag_feng==1)   //����
								{
											tmp_buf_TX1[6]='F';
											tmp_buf_TX1[7]='K';
									//		tmp_buf_TX1[2]=0;									
								}
								else if(flag_feng==0)
								{
											tmp_buf_TX1[6]='F';
											tmp_buf_TX1[7]='G';
									//		tmp_buf_TX1[2]=0;									  
								}							

								if(flag_hot==1) // ���ȹ�
								{
											tmp_buf_TX1[8]='H';
											tmp_buf_TX1[9]='K';
									//		tmp_buf_TX1[2]=0;									
								}
								else if(flag_hot==0)
								{
											tmp_buf_TX1[8]='H';
											tmp_buf_TX1[9]='G';
									//		tmp_buf_TX1[2]=0;									  
								}								
								tmp_buf_TX1[10]=0;
								if(s%10>=0&&s%10<3)
								NRF24L01_TX_Mode1();
								if(NRF24L01_TxPacket(tmp_buf_TX1)==TX_OK)
										printf("TX1 IS %s\r\n",tmp_buf_TX1);
								else
										printf("ERROR\r\n");
            }
            else if(s%10>6)
            {
							  // if(s%10>=5&&s%10<8)
                NRF24L01_RX_Mode();
								 delay_ms(50);
                if(NRF24L01_RxPacket(tmp_buf_RX)==0)//һ�����յ���Ϣ,����ʾ����.
                {
									  if(flag_flag==0)
									  flag_date=0,flag_flag=20;
                    tmp_buf_RX[13]=0;//�����ַ���������
                    printf("RX IS %s\r\n",tmp_buf_RX);
                }
                else
                    printf("RX is ERROR\r\n");	
						}	
						
				}	
									
    }  
		 TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIM2�����жϱ�־				 //  printf("time is %d\r\n",s);	
}
//ͨ�ö�ʱ��2�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ42M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʼ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
    void TIM2_Int_Init(u16 arr,u16 psc)
    {
        NVIC_InitTypeDef NVIC_InitStructure;
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//TIM7ʱ��ʹ��

        //��ʱ��TIM2��ʼ��
        TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
        TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

        TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM7�ж�,��������ж�

        TIM_Cmd(TIM2,ENABLE);//������ʱ��2

        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�0
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�2
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
        NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

    }
    /*
    	}*/
