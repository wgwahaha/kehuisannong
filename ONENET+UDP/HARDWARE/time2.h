#ifndef _TIME2_H
#define _TIME2_H
#include "sys.h"	
extern int s;
void TIM2_Int_Init(u16 arr,u16 psc);
extern u8  tmp_buf_RX[14];
extern u8 tmp_buf_TX0[2];
extern u8 tmp_buf_TX1[11];
extern u8 flag_date;
#endif
