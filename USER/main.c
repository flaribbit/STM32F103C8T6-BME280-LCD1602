#include "sys.h"
#include <stdio.h>
#include "usart.h"
#include "lcd1602.h"
#include "bme280.h"

int main(void)
{
	char buf[20];
	int t=0;
	double a,b,c;
	delay_init();
	//uart_init(115200);
	//GPIO_Configuration();
	LCD1602_Init();
	LCD1602_Print("LCD Init");
	bme280_setup();
	LCD1602_Print("BME Init");
	for(;;t++){
		getdata(&a,&b,&c);
		sprintf(buf,"T=%4.1lfC H=%4.1lf%%",a,c);
		LCD1602_WriteCmd(0x80);
		LCD1602_Print(buf);
		sprintf(buf,"P=%6.0lfPa",b);
		LCD1602_WriteCmd(0xC0);
		LCD1602_Print(buf);
		delay_ms(500);
	}
}
