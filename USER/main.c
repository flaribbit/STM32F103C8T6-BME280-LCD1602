#include "sys.h"
#include "usart.h"
#include "lcd1602.h"

int main(void)
{
	char buf[20];
	int t=0;
	delay_init();
	//uart_init(115200);
	//GPIO_Configuration();
	LCD1602_Init();
	for(;;t++){
		buf[0]='0'+t/100%10;
		buf[1]='0'+t/10%10;
		buf[2]='0'+t%10;
		buf[3]=0;
		LCD1602_WriteCmd(0x80);
		LCD1602_Print(buf);
		delay_ms(100);
	}
}
