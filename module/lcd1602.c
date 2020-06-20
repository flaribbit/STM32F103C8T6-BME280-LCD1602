#include "lcd1602.h"

#define LCD_RS PCout(13)
#define LCD_RW PCout(14)
#define LCD_EN PCout(15)

void LCD1602_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);

    //控制线
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //数据线
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=0x00FF;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	LCD1602_WriteCmd(0x38);
	LCD1602_WriteCmd(0x0C);
	LCD1602_WriteCmd(0x06);
	LCD1602_WriteCmd(0x01);
}

void LCD1602_WriteData(u8 dat){
    LCD_RS=1;
    LCD_RW=0;
	GPIO_Write(GPIOA,(GPIO_ReadOutputData(GPIOA)&0xFF00)|dat);
    LCD_EN=1;
    delay_ms(1);
    LCD_EN = 0;
}

void LCD1602_WriteCmd(u8 cmd){
    LCD_RS = 0;
    LCD_RW = 0;
    GPIO_Write(GPIOA,(GPIO_ReadOutputData(GPIOA)&0xFF00)|cmd);
    LCD_EN = 1;
    delay_ms(1);
    LCD_EN = 0;
}

void LCD1602_Print(char *str){
    while(*str){
		LCD1602_WriteData(*str++);
	}
}
