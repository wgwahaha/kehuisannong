#include "usart.h"
#include "light_sensor_io.h"
#include "sys.h"
#include "delay.h"

#define   uchar unsigned char
#define   uint unsigned int	
#define SCL PAout(4)
#define SDA PAout(5)      //IIC数据引脚定义
#define SDA_IN PAin(5)      //IIC数据引脚定义

#define	  SlaveAddress   0x46 //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0x46，接电源时地址为0xB8
typedef   unsigned char BYTE;

extern BYTE    BUF[8];                         //接收数据缓存区      	
extern uchar   ge,shi,bai,qian,wan;            //显示变量
extern int     dis_data; //变量


extern uchar CY; //来源于51psw寄存器（程序状态字）的一个位

//void delay_nms();
#define delay_nms(n) delay_ms(n)

void Init_BH1750(void);
void conversion(uint temp_data);
void  Single_Write_BH1750(uchar REG_Address);               //单个写入数据
uchar Single_Read_BH1750(uchar REG_Address);                //单个读取内部寄存器数据
void  Multiple_Read_BH1750(void);                               //连续的读取内部寄存器数据

//void Delay5us();
#define Delay5us() delay_us(5)
//void Delay5ms();
#define Delay5ms() delay_ms(5)


void BH1750_Start(void);                    //起始信号
void BH1750_Stop(void);                     //停止信号
void BH1750_SendACK(uchar ack);           //应答ACK
uchar  BH1750_RecvACK(void);                  //读ack
void BH1750_SendByte(BYTE dat);         //IIC单个字节写
BYTE BH1750_RecvByte(void);                 //IIC单个字节读

void light_sensor_init(void);
void light_cal(void);
void get_light_data(u8 tmp[]);
