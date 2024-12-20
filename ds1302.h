#ifndef __DS1302_H
#define __DS1302_H
#define uchar unsigned char
#define uint unsigned int
void Write_Ds1302(unsigned  char temp); 
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte ( unsigned char address );
void DS1302_SetRtc(uchar *Date);//设置时间
void DS1302_GetRtc(uchar *Date);//读取时间
#endif