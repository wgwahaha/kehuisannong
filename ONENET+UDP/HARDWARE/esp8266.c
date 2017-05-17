#include "stm32f10x.h"
//#include "usart2.h"
#include "esp8266.h"
#include "string.h"
#include "delay.h"
#include "edpkit.h"
#include "stdio.h"
#include "usart3.h"
#include "time2.h"
EdpPacket* send_pkg;
char send_buf[MAX_SEND_BUF_LEN];
void ESP8266_Init()
{
   u3_printf(AT);
	
	 u3_printf(CWMODE);
	
	 u3_printf(RST);
	 
	 u3_printf(CIFSR);
	
	 u3_printf(CWJAP);
	
	 u3_printf(CIPSTART);
	
	 u3_printf(CIPMODE);

}
void SendCmd(char* cmd, char* result, int timeOut)
{
    while(1)
    {
        memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
				USART3_RX_STA=0;
        usart3_write(USART2, (unsigned char *)cmd, strlen((const char *)cmd));
        delay_ms(timeOut);
       
        if((NULL != strstr((const char *)USART3_RX_BUF, result)))	//判断是否有预期的结果
        {
            break;
        }
        else
        {
            delay_ms(100);
        }
    }
}
void ESP8266_DevLink(const char* devid, const char* auth_key, int timeOut)
{
		int count=0;
	
		memset(USART3_RX_BUF,0,strlen((const char *)USART3_RX_BUF));
		USART3_RX_STA=0;			
		
	  usart3_write(USART3,CIPSEND,strlen(CIPSEND));  //向ESP8266发送数据透传指令
		  
		for(count=0;count<timeOut;count++)
		{
				delay_ms(100);
				if((NULL != strstr((const char *)USART3_RX_BUF,">")))
				{
						break;
				}
		}	
		send_pkg = PacketConnect1(devid,auth_key);
		delay_ms(200);
		usart3_write(USART3,send_pkg->_data,send_pkg->_write_pos);  //发送设备连接请求数据
		delay_ms(500);
		DeleteBuffer(&send_pkg);
		delay_ms(200);
		usart3_write(USART2,"+++",3);   //向ESP8266发送+++结束透传，使ESP8266返回指令模式 
		delay_ms(50);
}
void SEND_DATA()
{
	 char text[25] = {0},i;
   	memset(send_buf,0,MAX_SEND_BUF_LEN);	
		strcat(send_buf, ",;");
   	 
	 if(flag_date==0)
	 {
		   
	     strcat(send_buf, "wendu,");
		   for(i=1;i<4;i++)
	  	 text[i-1]=tmp_buf_RX[i];	
       flag_date=1;
	 }
	 else if(flag_date==1)
	 {
	  strcat(send_buf, "shidu,");
		 for(i=1;i<3;i++)
	  	 text[i-1]=tmp_buf_RX[i+10];	
     flag_date=2;	
	 }
	 else if(flag_date==2)
	 {
	  strcat(send_buf, "light,");
		  for(i=1;i<6;i++)
	  	 text[i-1]=tmp_buf_RX[i+4];	
        flag_date=0;	
	 }
	 else
	 {
	  strcat(send_buf, "chushi,");
		 	for(i=1;i<4;i++)
	  	 text[i-1]=tmp_buf_RX[i];	
         flag_date=20;
	 }		
	 
		strcat(send_buf, text);
		strcat(send_buf, ";");	 
	 

}
void ESP8266_SendDat(void)
{		
		int32 count=0;

		memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
		USART3_RX_STA=0;			

	//	usart3_write(USART3,CIPSEND,strlen(CIPSEND));  //向ESP8266发送数据透传指令
		for(count=0;count<40;count++)
		{
				delay_ms(100);
				if((NULL != strstr((const char *)USART3_RX_BUF,">")))
				{
						break;
				}
		}	
			SEND_DATA();
		send_pkg = PacketSavedataSimpleString(DEVICEID,send_buf);   
		usart3_write(USART3,send_pkg->_data,send_pkg->_write_pos);	//向平台上传数据点
		DeleteBuffer(&send_pkg);
		delay_ms(500);
    
	//	usart3_write(USART3,"+++",3);  //向ESP8266发送+++结束透传，使ESP8266返回指令模式
		delay_ms(200);
	
}
int ESP8266_CheckStatus(int timeOut)
{
		int32 res=0;
		int32 count=0;
	
		memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
		USART3_RX_STA=0;
	
		usart3_write(USART2,CIPSTATUS,strlen(CIPSTATUS));
		for(count=0;count<timeOut;count++)
		{
				delay_ms(100);
				if((NULL != strstr((const char *)USART3_RX_BUF,"STATUS:4")))  //失去连接
				{
						res=-4;
						break;
				}
				else if((NULL != strstr((const char *)USART3_RX_BUF,"STATUS:3")))  //建立连接
				{
						res=0;	
						break;
				}
				else if((NULL != strstr((const char *)USART3_RX_BUF,"STATUS:2")))  //获得IP
				{
						res=-2;
						break;				
				}
				else if((NULL != strstr((const char *)USART3_RX_BUF,"STATUS:5")))  //物理掉线
				{
						res=-5;
						break;
				}
				else if((NULL != strstr((const char *)USART3_RX_BUF,"ERROR")))   
				{
						res=-1;
						break;
				}
				else
				{
						;
				}
		}	
		return res;	
}





