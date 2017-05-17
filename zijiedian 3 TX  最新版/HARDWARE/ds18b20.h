#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32开发板
//DS18B20驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/12
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO方向设置
#define DS18B20_IO_IN()  {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=8<<20;}
#define DS18B20_IO_OUT() {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=3<<20;}
////IO操作函数											   
#define	DS18B20_DQ_OUT PCout(13) //数据端口	PA0
#define	DS18B20_DQ_IN  PCin(13)  //数据端口	PA0 
   	
u8 DS18B20_Init(void);			//初始化DS18B20
u8 DS18B20_Get_Temp(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);		//读出一个字节
u8 DS18B20_Read_Bit(void);		//读出一个位
u8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20   
void get_temp(u8 tmp[]);
#endif















