#ifndef __5110_H__
#define __5110_H__

#include "MCF52259.h"
#include "gpio.h"
  

//-------------------------------------------------------------------------------------------*
//函数声明区
//-------------------------------------------------------------------------------------------*
 void nk5110_init();  //初始化5110
 void Delay_ms(uint16 ms);
 void LCD_write_byte(unsigned char dat, unsigned char command);
 void LCD_init(void);
 void LCD_set_XY(unsigned char X, unsigned char Y);
 void LCD_write_char(unsigned char c);
 void LCD_write_str(unsigned char *p);
 void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char hhh,uint8*Image_,uint8 r);
 void LCD_clear(void);
 void LCD_write_1_num(unsigned char X,unsigned char Y,signed int s);
 void LCD_write_2_num(unsigned char X,unsigned char Y,signed int s);
 void LCD_write_3_num(unsigned char X,unsigned char Y,signed int s);
 void LCD_write_4_num(unsigned char X,unsigned char Y,signed int s);
 
 void show_lcd(uint8*I,uint8 R);
// const unsigned char font6x8[][6];
 //*********************************************************************************************
 
 
 
 #endif