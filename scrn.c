#include "mem.h"
#include "basicio.h"
#include<stdint.h>
#define COLOURS 0xF0
#define COLS 80
#define ROWS 25
#define VGA_START 0xB8000
#define PRINTABLE(c) (c>=' ')
#define NULL ((void *)0)
uint16_t *Scrn;
int Curx = 0, Cury = 0;

void scroll(){
	if(Cury==ROWS){
		int temp = 1;
		Curx = 0;
		
		uint16_t *addr, *new_addr;
		
		while(temp<ROWS){
			while(Curx<COLS){
			addr = (Scrn + ((temp) * COLS + Curx++));
			new_addr = addr - COLS;
			*new_addr = *addr;	
			}
			Curx=0;
			temp++;
		}
		temp--;
		new_addr++;
		while(Curx<COLS){
			*new_addr = (COLOURS<<8)| ' ';
			new_addr++;
			Curx++;
		}
		Curx=0;
		Cury--;
	}
	
}

void putchar(uint8_t c){

	
	uint16_t *addr;
	
	if(c=='\t') Curx = ((Curx + 4)/4)*4;
	else if(c=='\r') Curx=0;
	else if(c=='\n')
	{
		Curx=0;
		Cury++;
	}
	else if(PRINTABLE(c))
	{
		addr = Scrn + (Cury * COLS + Curx);
		*addr = (COLOURS<<8)|c;
		Curx++;
	}

	if(Curx >= COLS)
	{
		Curx = 0;
		Cury++;
		if(Cury==ROWS)
			scroll();
	}
	
}

void puts(unsigned char *str)
{
	while(*str) { putchar(*str); str++;}
}

void itoa(char *buf, int base, int d){

	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;
	
	if(base == 'd'&& d<0)
	{
		*p++ = '-';
		buf++;
		ud = -d;
	}
	
	else if(base == 'x')
		divisor = 16;
	
	do{
		int remainder = ud%divisor;
		*p++ = (remainder<10)?remainder+'0':remainder+'a'-10;
	}while(ud/=divisor);

	*p=0;
	
	p1 = buf;
	p2 = p-1;
	while(p1<p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

void printf(const char *format, ...)
{
	char **arg = (char **) &format;
	int c;
	char buf[20];
	
	arg++;
	
	while((c = *format++)!=0)
	{
		if(c!='%')
			putchar(c);
		else
		{
			char *p;
			c = *format++;
			switch(c)
			{
				case 'd':
				case 'u':
				case 'x':
					itoa(buf,c,*((int *) arg++));
					p = buf;
					goto string;
					break;
				case 's':
					p = *arg++;
					if(p == NULL)
						p="(null)";
					string:
						while(*p)
							putchar(*p++);
						break;
				default:
					putchar(*((int *) arg++));
					break;
			}
		}
	}
}

void clear(){
	int i;
	for(i=0; i<ROWS*COLS; i++) putchar(' ');
	Curx = Cury = 0;
}

void vga_init(void){
	Scrn = (unsigned short *) VGA_START;
	clear();
}

