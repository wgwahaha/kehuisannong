#ifndef __ESP8266_H
#define __ESP8266_H	

#define   MAX_SEND_BUF_LEN  1024
#define   DEVICEID   "4071496"
#define   APIKEY     "Y=njEFTB0IjVksqWftEMJfgetUs="

#define   AT          "AT\r\n"	
#define   CWMODE      "AT+CWMODE=1\r\n"  
#define   RST         "AT+RST\r\n"
#define   CIFSR       "AT+CIFSR\r\n"
#define   CWJAP       "AT+CWJAP=\"电子创新实验室\",\"1234567890\"\r\n"
//#define   CWJAP       "AT+CWJAP=\"ss203\",\"xxyliu203\"\r\n"
#define   CIPSTART    "AT+CIPSTART=\"TCP\",\"jjfaedp.hedevice.com\",876\r\n"
#define   CIPMODE     "AT+CIPMODE=1\r\n"
#define   CIPSEND     "AT+CIPSEND\r\n"
#define   CIPSTATUS   "AT+CIPSTATUS\r\n"

extern char send_buf[MAX_SEND_BUF_LEN];
void ESP8266_Init(void);

void SEND_DATA(void);

void ESP8266_SendDat(void);

extern void ESP8266_DevLink(const char* devid, const char* auth_key, int timeOut);

int ESP8266_CheckStatus(int timeOut);

void SendCmd(char* cmd, char* result, int timeOut);
#endif

