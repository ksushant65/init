#include<stdint.h>

extern void scroll(void);
extern void putchar(uint8_t c);
extern void puts(unsigned char *str);
extern void itoa(char *buf, int base, int d);
extern void printf(const char *format, ...);
extern void clear();
extern void vga_init(void);
