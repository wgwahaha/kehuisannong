#ifndef __USART3_h
#define __USART3_h
#include "stm32f10x.h"
#define USART3_MAX_RECV_LEN		1024					//最大接收缓存字节数
#define USART3_MAX_RECV_comLEN 256
#define USART3_MAX_SEND_LEN		1024				//最大发送缓存字节数
#define USART3_RX_EN 			1					//0,不接收;1,接收.
void usart3_init(u32 bound);
void u3_printf(char* fmt,...);
void usart3_write(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);
extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern unsigned int USART3_RX_STA;   						//接收数据状态
extern unsigned char USART3_RX_comBUF[USART3_MAX_RECV_comLEN]; 
extern unsigned int USART3_RX_comSTA;
extern volatile unsigned char  rcv_cmd_start;
extern volatile unsigned char  rcv_cmd_flag;
#endif
