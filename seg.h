#ifndef __SEG_H
#define __SEG_H
#define uchar unsigned char
#define uint unsigned int
void P0_Out(uchar addr,uchar dat);//P0���
void LED_Disp(unsigned char led);
void Close_Peripheral();//�ر�����
void Uln_Ctrl(uchar uln);//���Ƽ̵�����1����0�ء�
void LED_Disp(uchar led);//����LED:1����0�أ�0xff��ȫ��
void Seg_Tran(uchar *seg_char,uchar *seg_code);//�����ת������
void seg_disp(uchar seg_code,uchar seg_pos);//�����չʾ
#endif