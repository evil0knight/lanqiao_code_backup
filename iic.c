/*	#   I2C代码片段说明
	1. 	本文件夹中提供的驱动代码供参赛选手完成程序设计参考。
	2. 	参赛选手可以自行编写相关代码或以该代码为基础，根据所选单片机类型、运行速度和试题
		中对单片机时钟频率的要求，进行代码调试和修改。
*/
#include <intrins.h>
#include <STC15F2K60S2.H>
#define uchar unsigned char
#define uint unsigned int
#define DELAY_TIME	10
sbit scl=P2^0;
sbit sda=P2^1;
//
static void I2C_Delay(unsigned char n)
{
    do
    {
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();
        _nop_();_nop_();_nop_();_nop_();_nop_();		
    }
    while(n--);      	
}

//
void I2CStart(void)
{
    sda = 1;
    scl = 1;
	I2C_Delay(DELAY_TIME);
    sda = 0;
	I2C_Delay(DELAY_TIME);
    scl = 0;    
}

//
void I2CStop(void)
{
    sda = 0;
    scl = 1;
	I2C_Delay(DELAY_TIME);
    sda = 1;
	I2C_Delay(DELAY_TIME);
}

//
void I2CSendByte(unsigned char byt)
{
    unsigned char i;
	
    for(i=0; i<8; i++){
        scl = 0;
		I2C_Delay(DELAY_TIME);
        if(byt & 0x80){
            sda = 1;
        }
        else{
            sda = 0;
        }
		I2C_Delay(DELAY_TIME);
        scl = 1;
        byt <<= 1;
		I2C_Delay(DELAY_TIME);
    }
	
    scl = 0;  
}

//
unsigned char I2CReceiveByte(void)
{
	unsigned char da;
	unsigned char i;
	for(i=0;i<8;i++){   
		scl = 1;
		I2C_Delay(DELAY_TIME);
		da <<= 1;
		if(sda) 
			da |= 0x01;
		scl = 0;
		I2C_Delay(DELAY_TIME);
	}
	return da;    
}

//
unsigned char I2CWaitAck(void)
{
	unsigned char ackbit;
	
    scl = 1;
	I2C_Delay(DELAY_TIME);
    ackbit = sda; 
    scl = 0;
	I2C_Delay(DELAY_TIME);
	
	return ackbit;
}

//
void I2CSendAck(unsigned char ackbit)
{
    scl = 0;
    sda = ackbit; 
	I2C_Delay(DELAY_TIME);
    scl = 1;
	I2C_Delay(DELAY_TIME);
    scl = 0; 
	sda = 1;
	I2C_Delay(DELAY_TIME);
}
//*buf数据，addr数据地址，num数据个数

void ATC24C02_WriteBuffer(uchar *buf,uchar addr,uchar num){
	I2CStart();
	I2CSendByte(0XA0);
	I2CWaitAck();
	
	I2CSendByte(addr);
	I2CWaitAck();
	
	while(num--){
		I2CSendByte(*buf++);
		I2CWaitAck();
		I2C_Delay(DELAY_TIME*4);
	}
	I2CStop();
}
//AT24C02缓存器读：buf数据，addr地址，num数量
void ATC24C02_ReadBuffer(uchar *buf,uchar addr,uchar num){
	I2CStart();
	I2CSendByte(0XA0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	I2CStart();
	I2CSendByte(0XA1);
	I2CWaitAck();
	while(num--){
		*buf++=I2CReceiveByte();
		if(num) I2CSendAck(0);
		else I2CSendAck(1);
	}
	I2CStop();
}
//模拟量转数字量adc接收
uchar PCF8591_ADC(uchar ain){
	uchar adc;
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x40+ain);
	I2CWaitAck();
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();
	adc=I2CReceiveByte();
	I2CSendAck(1);
	I2CStop();
	return adc;
}
//数字量转模拟量输出
void PCF8591_DAC(uchar dac){
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x40);
	I2CWaitAck();
	I2CSendByte(dac);
	I2CWaitAck();
	I2CStop();
}
