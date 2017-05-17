#include "usart3.h"
#include "delay.h"
#include "usart.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"
#include "timer.h"
#include "led.h"
unsigned char USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
unsigned char  USART3_TX_BUF[USART3_MAX_SEND_LEN];
unsigned int USART3_RX_STA=0; 
unsigned char USART3_RX_comBUF[USART3_MAX_RECV_comLEN]; 
unsigned int USART3_RX_comSTA=0;
volatile unsigned char  rcv_cmd_start=0;
volatile unsigned char  rcv_cmd_flag=0;
void usart3_write(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len)
{
    uint32_t i;
		USART_ClearFlag(USART3,USART_FLAG_TC); 
    for(i=0; i<len; i++)
    {                                         
        USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}




void USART3_IRQHandler(void)
{
		unsigned int data;

    if(USART3->SR & 0x0F)
    {
        data = USART3->DR;
    }
		else if(USART3->SR & USART_FLAG_RXNE)   //Receive Data Reg Full Flag
    {		
        data = USART3->DR;
				USART3_RX_BUF[USART3_RX_STA++]=data;
				
				if(data=='{') //约定平台下发的控制命令以'{'为开始符，‘}’为控制命令结束符，读者可以自定义自己的开始符合结束符
				{					
						rcv_cmd_start=1;
				}
				if(rcv_cmd_start==1)
				{
						USART3_RX_comBUF[USART3_RX_comSTA++]=data;
						if((data=='}')||(USART3_RX_comSTA>=USART3_MAX_RECV_comLEN-1))
						{
								rcv_cmd_start=0;
							 printf("%s",USART3_RX_comBUF);
								get_shidukey();
								memset(USART3_RX_comBUF,0,USART3_RX_comSTA);
        				USART3_RX_comSTA=0;
						}
				}	  
    }
		else
		{
				;
		}
}

void usart3_init(u32 bound)
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //串口3时钟使能

 	USART_DeInit(USART3);  //复位串口3
		 //USART3_TX   PB10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
    //USART3_RX	  PB11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11
	
	USART_InitStructure.USART_BaudRate = bound;//波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART3, &USART_InitStructure); //初始化串口	3
  

	USART_Cmd(USART3, ENABLE);                    //使能串口 
	
	//使能接收中断
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断   
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	TIM7_Int_Init(1000-1,7200-1);		//10ms中断
	USART3_RX_STA=0;		//清零
	TIM_Cmd(TIM7,DISABLE);			//关闭定时器7
	
}
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}
