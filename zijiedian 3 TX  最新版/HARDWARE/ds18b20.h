#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32������
//DS18B20��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
#define DS18B20_IO_IN()  {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=8<<20;}
#define DS18B20_IO_OUT() {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=3<<20;}
////IO��������											   
#define	DS18B20_DQ_OUT PCout(13) //���ݶ˿�	PA0
#define	DS18B20_DQ_IN  PCin(13)  //���ݶ˿�	PA0 
   	
u8 DS18B20_Init(void);			//��ʼ��DS18B20
u8 DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20   
void get_temp(u8 tmp[]);
#endif















