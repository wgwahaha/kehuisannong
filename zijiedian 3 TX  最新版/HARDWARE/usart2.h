#ifndef __USART2_H
#define __USART2_H

#define USART2_MAX_RECV_LEN		64					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		64					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.
void usart2_init(unsigned int bound);
void u2_printf(char* fmt,...);
extern unsigned char  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern unsigned char   USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern unsigned int USART2_RX_STA;   						//��������״̬
#endif
