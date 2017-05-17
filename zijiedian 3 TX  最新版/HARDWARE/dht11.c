#include "dht11.h"
//u8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;  
u8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;  
  
#define BOOL unsigned char  
  
#ifndef TRUE  
#define TRUE 1  
#endif  
  
#ifndef FALSE  
#define FALSE 0  
#endif  
  
static void DHT11_DataPin_Configure_Output(void)  
{  
     GPIO_InitTypeDef  GPIO_InitStructure;  
      
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, DISABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     //使能PC端口时钟  
                  
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;                 //PC.0 端口配置  
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          //推挽输出  
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
     GPIO_Init(GPIOA, &GPIO_InitStructure);  
}  
  
static void DHT11_DataPin_Configure_Input(void)  
{  
       GPIO_InitTypeDef  DataPin;       
      
     DataPin.GPIO_Pin = GPIO_Pin_6;                  
     DataPin.GPIO_Mode = GPIO_Mode_IN_FLOATING;         //悬空       
     DataPin.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &DataPin);  
}  
BOOL DHT11_get_databit(void)  
{  
    uint8_t val;  
      
     val = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);  
    if(val == Bit_RESET){  
        return FALSE;  
    }else{  
        return TRUE;  
    }  
}  
  
void DHT11_set_databit(BOOL level)  
{  
    if(level == TRUE){  
        GPIO_SetBits(GPIOA, GPIO_Pin_6);  
    }else{  
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);  
    }  
}  
  
void mdelay(u16 ms)    
{  
    if(ms != 0){  
        delay_ms(ms);  
    }  
}  
  
void udelay(u16 us)    
{  
    if(us != 0){  
        delay_us(us);  
    }  
}  
static uint8_t DHT11_read_byte(void)  
{       
    uint8_t i;    
    uint8_t data = 0;      
                         
    for(i = 0; i < 8; i++)         
    {      
        data <<= 1;          
           while((!DHT11_get_databit()));  
        udelay(10);  
        udelay(10);  
        udelay(10);  
  
        if(DHT11_get_databit())    {  
            data |= 0x1;  
            while(DHT11_get_databit());  
        } else{  
          
        }   
  
     }  
                           
     return data;  
}  
    
static uint8_t DHT11_start_sampling(void)  
{  
    DHT11_DataPin_Configure_Output();  
      //主机拉低18ms     
    DHT11_set_databit(FALSE);  
    mdelay(18);  
    DHT11_set_databit(TRUE);  
     //总线由上拉电阻拉高 主机延时20us  
    udelay(10);  
    udelay(10);  
//    udelay(10);  
//    udelay(10);  
     //主机设为输入 判断从机响应信号   
    DHT11_set_databit(TRUE);  
  
    DHT11_DataPin_Configure_Input();  
  
     //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行        
    if(!DHT11_get_databit())         //T !        
    {  
     //判断从机是否发出 80us 的低电平响应信号是否结束       
       while((!DHT11_get_databit()));  
      // printf("DHT11 answers.\r\n");  
     //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态  
       while((DHT11_get_databit()));  
       return 1;  
    }  
  
    return 0;                 
}  
  
void DHT11_get_data(void)  
{        
//    u8 temp;  
    if(DHT11_start_sampling()){  
        //printf("DHT11 is ready to transmit data\r\n");  
        //数据接收状态           
        U8RH_data_H_temp = DHT11_read_byte();  
//        U8RH_data_L_temp = DHT11_read_byte();  
//        U8T_data_H_temp     = DHT11_read_byte();  
//        U8T_data_L_temp     = DHT11_read_byte();  
//        U8checkdata_temp = DHT11_read_byte();  
  
        /* Data transmission finishes, pull the bus high */  
        DHT11_DataPin_Configure_Output();     
        DHT11_set_databit(TRUE);  
        //数据校验   
  
//        temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);  
//        if(temp==U8checkdata_temp)  
//        {  
//            U8RH_data_H=U8RH_data_H_temp;  
//            U8RH_data_L=U8RH_data_L_temp;  
//            U8T_data_H=U8T_data_H_temp;  
//            U8T_data_L=U8T_data_L_temp;  
//            U8checkdata=U8checkdata_temp;  
//  
//            printf("DHT11 tempature %d.%d  humidity %d.%d \r\n",   
//                U8T_data_H,  
//                U8T_data_L,  
//                U8RH_data_H,  
//                U8T_data_L);  
//  
//       }else{  
//            printf("checksum failure \r\n");  
//       }   
    }
//	else{  
//        printf("DHT11 didn't answer. Sampling failed. \r\n");  
//    }  
}  
  
void get_RH_data(u8 sensor_data[])  
{  
    DHT11_get_data();  
    sensor_data[11]=U8RH_data_H_temp/10+'0';
	sensor_data[12]=U8RH_data_H_temp%10+'0';
}
