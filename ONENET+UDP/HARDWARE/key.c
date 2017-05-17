#include "stm32f10x.h"
#include "key.h"
void INIT_KEY()
{
	GPIO_InitTypeDef GPIO_struct_key;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE,ENABLE );
	
	GPIO_struct_key.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_struct_key.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;
	GPIO_struct_key.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_struct_key);
	
}

