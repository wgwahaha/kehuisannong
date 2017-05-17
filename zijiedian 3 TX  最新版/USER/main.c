#include "stm32f10x.h"
#include "24l01.h"
#include "usart.h"
#include "delay.h"
#include "usart2.h"
#include "led.h"
#include "light_sensor.h"
#include "adc.h"
#include "ds18b20.h"
#include "dht11.h"
u8 sensor_data[4+6+3+1]={'t','0','0','0','l','0','0','0','0','0','h','0','0',0};
int main()
{
		delay_init();
	  DS18B20_Init();
    uart_init(115200);
    usart2_init(115200);
	 light_sensor_init();
		NRF24L01_Init();
		while(NRF24L01_Check())
	  printf("24L01 IS ERROR");
		
	  printf("24L01 IS SUCCESS");
		
		NRF24L01_TX_Mode();
   while(1)
	 {
		    get_light_data(sensor_data);
		    get_temp(sensor_data);
		    get_RH_data(sensor_data); 				
				if(NRF24L01_TxPacket(sensor_data)==TX_OK)
				{						
						printf("TX IS %s\r\n",sensor_data);
				}
				else
				printf("ERROR");
       delay_ms(500);	
		} 
}

