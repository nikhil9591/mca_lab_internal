#include<lpc214x.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include "uart.h"
#include "pll.h"

void delay_ms(int count)
{
	int i,j;
	for(i=0; i<count; i++)
	{
		for(j=0; j<3000; j++);
	}
}

void lcd_cmd(char cmd)
{
	IO0PIN = ((IO0PIN & 0xFFFF00FF)|(cmd<<8));
	IO0SET = 0x00000040;
	IO0CLR = 0x00000030;
	delay_ms(2);
	IO0CLR = 0x00000040;
	delay_ms(5);
}

void lcd_init()
{
	//PINSEL0 = 0x00000000;
	IO0DIR = 0x0000FFF0;
	delay_ms(20);
	lcd_cmd(0x38);
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01); 
	lcd_cmd(0x80);
}

void lcd_string(char* str)
{
	int i=0;
	
	while(str[i]!='\0')
	{
		IO0PIN = ((IO0PIN & 0xffff00ff)|(str[i]<<8));
		IO0SET = 0x00000050;
		IO0CLR = 0x00000020;
		delay_ms(2);
		IO0CLR = 0x00000040;
		delay_ms(5);
		i++;
	}
}
void uart_call()
{
  char temp;
	char arr[10];
  init_pll();
	init_uart0();
	
  while(1) {
		 temp  = receive_char_uart0();
    sprintf(arr,"%c",temp);
    lcd_string(arr);
		//delay_ms(20);
		//lcd_cmd(0x01);
  }
}

int main()
{
	lcd_init();
	uart_call();
	return 0;
}