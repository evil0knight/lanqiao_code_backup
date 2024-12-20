#include <STC15F2K60S2.H>
#include "seg.h"
#include "tim.h"
#include <stdio.h>
#include "key.h"
#include "iic.h"
#include <string.h>
#include <intrins.h>
#include "ds1302.h"
#include "onewire.h"
uchar seg_pos=0;
uchar seg_code[8];
uchar seg_char[10];
uint uitms=0;
uint uiseg_Dly=0;
uchar ucseg_Dly=0;
uchar key_valu[3];
uchar rtc[3]={0x20,0x41,0x30};
uchar mode=0;
void Seg_Proc();//数码管显示函数
void Key_proc();//按键检测函数
void Delay1000ms();		//@12.000MHz
void main(){
  Close_Peripheral();
	Timer1Init();
	DS1302_SetRtc(rtc);
	while(1){
		Seg_Proc();
		Key_proc();
	}
}
void T0_Proc()interrupt 3{
	uitms++;
	uiseg_Dly++;
	ucseg_Dly++;
}
void Seg_Proc(){//数码管显示函数
	if(uiseg_Dly>500){
		uiseg_Dly=0;
		switch(mode){
			case 0:
				DS1302_GetRtc(rtc);
				sprintf(seg_char,"1 %02x.%02x.%02x",(uint)rtc[0],(uint)rtc[1],(uint)rtc[2]);
				break;
			case 1:
				sprintf(seg_char,"2   %04.2f",Temp_Read()/16.0);
				break;
			case 2:
				sprintf(seg_char,"3   %04u",(uint)PCF8591_ADC(3));//滑动电阻
				break;
			case 3:
				sprintf(seg_char,"4   %04u",(uint)PCF8591_ADC(2));//
				break;
			case 4:
				sprintf(seg_char,"5   %04u",(uint)PCF8591_ADC(1));//光敏电阻
				break;
		}
		Seg_Tran(seg_char,seg_code);
	}
	if(ucseg_Dly>1){
		ucseg_Dly=0;
		seg_disp(seg_code[seg_pos],seg_pos);
		seg_pos=++seg_pos&7;//数码管循环显示
	}
}
void Key_proc(){//按键检测函数+键值控制函数
	if(uitms<10){
		return;
	}
	uitms=0;
	key_read(key_valu);
	switch(key_valu[0]){
	case 4:mode=0;break;
	case 5:mode=1;break;
	case 6:;break;
	case 7:;break;
	case 8:mode=2;break;
	case 9:mode=3;break;
	case 10:mode=4;break;
	case 11:;break;
	case 12:;break;
	case 13:;break;
	case 14:;break;
	case 15:;break;
	case 16:break;
	case 17:break;
	case 18:break;
	case 19:break;
	}
}


void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}