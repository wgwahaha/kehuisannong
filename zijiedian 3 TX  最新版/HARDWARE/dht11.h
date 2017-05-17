#ifndef __DHT11_H__
#define __HDT11_H__
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
//设定标志(static unsigned char status)的宏值
void get_RH_data(u8 sensor_data[]); 
#endif
