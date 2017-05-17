#include "light_sensor_io.h"

void LED_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA,PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//传地址   地址所代表的数据类型一致即可
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_5);	
}
void SDA_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能Pd端口时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//传地址   地址所代表的数据类型一致即可
	//GPIO_SetBits(GPIOA,GPIO_Pin_15);
}
