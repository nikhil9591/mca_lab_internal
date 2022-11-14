#include <lpc214x.h>
#include "uart.h"

void init_uart0()
{
	 PINSEL0=0X5;
   U0LCR=0X83;						//8-data bits, 1 stop bit, disable parity and 
   U0DLL=0x87;						//buad rate of 9600
   U0DLM=1;
   U0LCR=0X03;						//clear DLAB
}
void transmit_char_uart0(unsigned char c)
{
	while((U0LSR&(1<<5))==0);
  U0THR = c;
}
char receive_char_uart0()
{
	unsigned char temp_recv_var;
  while((U0LSR&(1<<0))==0);
  temp_recv_var = U0RBR;
  return temp_recv_var;
}