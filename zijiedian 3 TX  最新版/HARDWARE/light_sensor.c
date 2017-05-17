#include "light_sensor.h"

BYTE    BUF[8];                         //�������ݻ�����      	
uchar   ge,shi,bai,qian,wan;            //��ʾ����
int     dis_data; //����


uchar CY; //��Դ��51psw�Ĵ���������״̬�֣���һ��λ

void conversion(uint temp_data)  //  ����ת���� ����ʮ���٣�ǧ����
{  
    wan=temp_data/10000;//+0x30 ;
    temp_data=temp_data%10000;   //ȡ������
	qian=temp_data/1000;//+0x30 ;
    temp_data=temp_data%1000;    //ȡ������
    bai=temp_data/100;//+0x30   ;
    temp_data=temp_data%100;     //ȡ������
    shi=temp_data/10;//+0x30    ;
    temp_data=temp_data%10;      //ȡ������
    ge=temp_data;//+0x30; 	
}



void BH1750_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void BH1750_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(uchar ack)
{
	SDA=ack;                    //����if�����Զ�ת�����ͣ�����ֱ�ӰѰ�λ����һλ�����������Ŀ�����if��ֵ
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
uchar BH1750_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
	
	SDA_Init();                 //����������ģʽ
    CY = SDA_IN;                  //��Ӧ���ź�
	LED_Init();                 //�����������ģʽ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void BH1750_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
		if(0X80&dat)
        SDA=1;
		else
        SDA=0;//�����ǹؼ���cy��51���Ǳ�����λ�����Ľ������������ֲ�滻��cy��������Ҫ�ֶ���ֵ
		
        dat <<= 1;              //�Ƴ����ݵ����λ
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    BH1750_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE BH1750_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1; 
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
		
		SDA_Init();            //����������ģʽ
        dat |= SDA_IN;             //������   
        LED_Init();                 //�����������ģʽ
		
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}

//*********************************

void Single_Write_BH1750(uchar REG_Address)
{
    BH1750_Start();                  //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
  //  BH1750_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    BH1750_Stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ*****************************************
/*
uchar Single_Read_BH1750(uchar REG_Address)
{  uchar REG_data;
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=BH1750_RecvByte();              //�����Ĵ�������
	BH1750_SendACK(1);   
	BH1750_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
*/
//*********************************************************
//
//��������BH1750�ڲ�����
//
//*********************************************************
void Multiple_Read_BH1750()//..\OBJ\led.axf: Error: L6218E: Undefined symbol Multiple_Read_BH1750 (referred from main.o).   ԭ�����Сд����
{   
	uchar i;	
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	
	 for (i=0; i<3; i++)                      //������ȡ2����ַ���ݣ��洢��BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 3)
        {

           BH1750_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {		
          BH1750_SendACK(0);                //��ӦACK
       }
   }

    BH1750_Stop();                          //ֹͣ�ź�
    Delay5ms();
}


//��ʼ��BH1750��������Ҫ��ο�pdf�����޸�****
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
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}

	 
}


void light_sensor_init()
{
	  LED_Init();
    Init_BH1750();       //��ʼ��BH1750
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	 //uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
}
void light_cal()
{
	  float temp;
      Single_Write_BH1750(0x01);   // power on
      Single_Write_BH1750(0x10);   // H- resolution mode

      delay_nms(180);              //��ʱ180ms

      Multiple_Read_BH1750();       //�����������ݣ��洢��BUF��

      dis_data=BUF[0];
      dis_data=(dis_data<<8)+BUF[1];//�ϳ����ݣ�����������
    
      temp=(float)dis_data/1.2;

      conversion(temp);         //�������ݺ���ʾ
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

