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
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//定时器2中断服务程序
int s=0;
u8 tmp_buf_RX[14];
u8 tmp_buf_TX0[2];
u8 tmp_buf_TX1[11];
u8 flag_date=20;
//void TIM2_IRQHandler(void)
//{
//    static int i=0;


//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//是更新中断
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
//                if(NRF24L01_RxPacket(tmp_buf_RX)==0)//一旦接收到信息,则显示出来.
//                {
//                    tmp_buf_RX[6]=0;//加入字符串结束符
//                    printf("RX IS %s\r\n",tmp_buf_RX);
//                }
//                else
//                    printf("RX is ERROR");	
//						}	
//				}						
//    }
//    
//			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIM2更新中断标志
//}
//[0]为灯 [2]为电机 [4] 为水泵 [6]为风扇 [8]为加热管
void TIM2_IRQHandler(void)
{
      static u8 i=0;
	    static u8 flag_flag=0;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//是更新中断
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
								if(flag_led1==1)  //关于控制灯
								{
									tmp_buf_TX1[0]='L';
									tmp_buf_TX1[1]='K';
									//tmp_buf_TX1[2]=0;	
								}
								else if(flag_led1==0)//灯关
								{
									tmp_buf_TX1[0]='L';
									tmp_buf_TX1[1]='G';
									//tmp_buf_TX1[2]=0;							
								}							
								if(flag_motor==1)  //电机
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
								if(flag_beng==1)   //水泵
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
								if(flag_feng==1)   //风扇
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

								if(flag_hot==1) // 加热管
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
                if(NRF24L01_RxPacket(tmp_buf_RX)==0)//一旦接收到信息,则显示出来.
                {
									  if(flag_flag==0)
									  flag_date=0,flag_flag=20;
                    tmp_buf_RX[13]=0;//加入字符串结束符
                    printf("RX IS %s\r\n",tmp_buf_RX);
                }
                else
                    printf("RX is ERROR\r\n");	
						}	
						
				}	
									
    }  
		 TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIM2更新中断标志				 //  printf("time is %d\r\n",s);	
}
//通用定时器2中断初始化
//这里时钟选择为APB1的2倍，而APB1为42M
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//通用定时器中断初始化
//这里始终选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
    void TIM2_Int_Init(u16 arr,u16 psc)
    {
        NVIC_InitTypeDef NVIC_InitStructure;
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//TIM7时钟使能

        //定时器TIM2初始化
        TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
        TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

        TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM7中断,允许更新中断

        TIM_Cmd(TIM2,ENABLE);//开启定时器2

        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级0
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
        NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

    }
    /*
    	}*/
