#ifndef __USART3_h
#define __USART3_h
#include "stm32f10x.h"
#define USART3_MAX_RECV_LEN		1024					//�����ջ����ֽ���
#define USART3_MAX_RECV_comLEN 256
#define USART3_MAX_SEND_LEN		1024				//����ͻ����ֽ���
#define USART3_RX_EN 			1					//0,������;1,����.
void usart3_init(u32 bound);
void u3_printf(char* fmt,...);
void usart3_write(USART_TypeDef* USARTx, uint8_t *Data,uint32_t len);
extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern unsigned int USART3_RX_STA;   						//��������״̬
extern unsigned char USART3_RX_comBUF[USART3_MAX_RECV_comLEN]; 
extern unsigned int USART3_RX_comSTA;
extern volatile unsigned char  rcv_cmd_start;
extern volatile unsigned char  rcv_cmd_flag;
#endif
