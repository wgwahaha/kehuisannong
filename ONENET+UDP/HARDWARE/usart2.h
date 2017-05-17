#ifndef __USART2_H
#define __USART2_H

#define USART2_MAX_RECV_LEN		600					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		600					//最大发送缓存字节数
#define USART2_RX_EN 			1					//0,不接收;1,接收.
void usart2_init(unsigned int bound);
extern void u2_printf(char* fmt,...);
extern unsigned char  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern unsigned char   USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern unsigned int USART2_RX_STA;   						//接收数据状态
extern void usart2_write(USART_TypeDef* USARTx, unsigned char *Data,unsigned int len);
#endif
