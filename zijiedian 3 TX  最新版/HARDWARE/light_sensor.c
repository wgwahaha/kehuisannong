#include "light_sensor.h"

BYTE    BUF[8];                         //接收数据缓存区      	
uchar   ge,shi,bai,qian,wan;            //显示变量
int     dis_data; //变量


uchar CY; //来源于51psw寄存器（程序状态字）的一个位

void conversion(uint temp_data)  //  数据转换出 个，十，百，千，万
{  
    wan=temp_data/10000;//+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000;//+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100;//+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10;//+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data;//+0x30; 	
}



void BH1750_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void BH1750_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(uchar ack)
{
	SDA=ack;                    //无需if，会自动转换类型，可以直接把八位赋给一位，但若不放心可先用if赋值
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
uchar BH1750_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
	
	SDA_Init();                 //换上拉输入模式
    CY = SDA_IN;                  //读应答信号
	LED_Init();                 //换回推挽输出模式
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void BH1750_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
		if(0X80&dat)
        SDA=1;
		else
        SDA=0;//这里是关键，cy在51里是保存移位计算后的结果，而这里移植替换成cy变量就需要手动赋值
		
        dat <<= 1;              //移出数据的最高位
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    BH1750_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE BH1750_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1; 
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
		
		SDA_Init();            //换上拉输入模式
        dat |= SDA_IN;             //读数据   
        LED_Init();                 //换回推挽输出模式
		
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}

//*********************************

void Single_Write_BH1750(uchar REG_Address)
{
    BH1750_Start();                  //起始信号
    BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
    BH1750_SendByte(REG_Address);    //内部寄存器地址，
  //  BH1750_SendByte(REG_data);       //内部寄存器数据，
    BH1750_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
/*
uchar Single_Read_BH1750(uchar REG_Address)
{  uchar REG_data;
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress);           //发送设备地址+写信号
    BH1750_SendByte(REG_Address);                   //发送存储单元地址，从0开始	
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=BH1750_RecvByte();              //读出寄存器数据
	BH1750_SendACK(1);   
	BH1750_Stop();                           //停止信号
    return REG_data; 
}
*/
//*********************************************************
//
//连续读出BH1750内部数据
//
//*********************************************************
void Multiple_Read_BH1750()//..\OBJ\led.axf: Error: L6218E: Undefined symbol Multiple_Read_BH1750 (referred from main.o).   原代码大小写错误
{   
	uchar i;	
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	
	 for (i=0; i<3; i++)                      //连续读取2个地址数据，存储中BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 3)
        {

           BH1750_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {		
          BH1750_SendACK(0);                //回应ACK
       }
   }

    BH1750_Stop();                          //停止信号
    Delay5ms();
}


//初始化BH1750，根据需要请参考pdf进行修改****
void Init_BH1750()
{
   Single_Write_BH1750(0x01);  

}

void serial_send()
{
    u8 t;
	u8 len;	
    USART_RX_BUF[0]=wan;
	USART_RX_BUF[1]=qian;
	 USART_RX_BUF[2]=bai;
	 USART_RX_BUF[3]=shi;
	 USART_RX_BUF[4]=ge;
	USART_RX_BUF[5]='\n';
	len=6;
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}

	 
}


void light_sensor_init()
{
	  LED_Init();
    Init_BH1750();       //初始化BH1750
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	 //uart_init(9600);	 //串口初始化为9600
}
void light_cal()
{
	  float temp;
      Single_Write_BH1750(0x01);   // power on
      Single_Write_BH1750(0x10);   // H- resolution mode

      delay_nms(180);              //延时180ms

      Multiple_Read_BH1750();       //连续读出数据，存储在BUF中

      dis_data=BUF[0];
      dis_data=(dis_data<<8)+BUF[1];//合成数据，即光照数据
    
      temp=(float)dis_data/1.2;

      conversion(temp);         //计算数据和显示
	  //serial_send();
}

void get_light_data(u8 sensor_data[])
{
	light_cal();
    sensor_data[4]='l';
	sensor_data[5]=wan+'0';
	sensor_data[6]=qian+'0';
	sensor_data[7]=bai+'0';
	sensor_data[8]=shi+'0';
	sensor_data[9]=ge+'0';
}

