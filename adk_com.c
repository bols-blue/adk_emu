#include <stdio.h>
#include "libusb_adk.h"

int main(int argc,char **argv)
{
	init();
	if(open_accesory_com_dev()){
		return -1;
	}
	printf("open\n");
	data_read();
	return 0;
}
