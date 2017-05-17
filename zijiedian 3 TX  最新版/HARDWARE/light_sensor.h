#include "usart.h"
#include "light_sensor_io.h"
#include "sys.h"
#include "delay.h"

#define   uchar unsigned char
#define   uint unsigned int	
#define SCL PAout(4)
#define SDA PAout(5)      //IIC�������Ŷ���
#define SDA_IN PAin(5)      //IIC�������Ŷ���

#define	  SlaveAddress   0x46 //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                              //ALT  ADDRESS���Žӵ�ʱ��ַΪ0x46���ӵ�Դʱ��ַΪ0xB8
typedef   unsigned char BYTE;

extern BYTE    BUF[8];                         //�������ݻ�����      	
extern uchar   ge,shi,bai,qian,wan;            //��ʾ����
extern int     dis_data; //����


extern uchar CY; //��Դ��51psw�Ĵ���������״̬�֣���һ��λ

//void delay_nms();
#define delay_nms(n) delay_ms(n)

void Init_BH1750(void);
void conversion(uint temp_data);
void  Single_Write_BH1750(uchar REG_Address);               //����д������
uchar Single_Read_BH1750(uchar REG_Address);                //������ȡ�ڲ��Ĵ�������
void  Multiple_Read_BH1750(void);                               //�����Ķ�ȡ�ڲ��Ĵ�������

//void Delay5us();
#define Delay5us() delay_us(5)
//void Delay5ms();
#define Delay5ms() delay_ms(5)


void BH1750_Start(void);                    //��ʼ�ź�
void BH1750_Stop(void);                     //ֹͣ�ź�
void BH1750_SendACK(uchar ack);           //Ӧ��ACK
uchar  BH1750_RecvACK(void);                  //��ack
void BH1750_SendByte(BYTE dat);         //IIC�����ֽ�д
BYTE BH1750_RecvByte(void);                 //IIC�����ֽڶ�

void light_sensor_init(void);
void light_cal(void);
void get_light_data(u8 tmp[]);
