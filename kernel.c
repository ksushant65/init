#include<stdint.h>
#include "scrn.h"
void kernel_main(unsigned long magic, unsigned long addr){
	vga_init();
	int i;
	for(i=0;i<100 ; i++)
	printf("%d, ",i);
	//for(;;);
}
