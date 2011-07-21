/*
 * libusb_adk.c
 *
 * Copyright (C) 2011 - Hisayoshi Suehiro
 * Copyright (C) 2011 - Manuel Di Cerbo
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <usb.h>
#include "libusb_adk.h"

#define VID 0x22b8
//#define VID 0x18D1
#define GOOGLE_VID 0x18D1
#define PID 0x70a8

#define ACCESSORY_PID 0x2D00
#define ACCESSORY_PID_ALT 0x2D01

#define LEN 2

static void status(int code);
//static
static usb_dev_handle* handle;
static char stop;
static char success = 0;
int open_accesory_dev(){
 if(open_accesory_dev_from_id(VID,PID) == 0){return 0;}
 if(open_accesory_dev_from_id(GOOGLE_VID,PID) == 0){return 0;}
	return -1;
}

int open_accesory_dev_from_id(int vid,int pid)
{
	struct usb_bus *bus;
	struct usb_device *dev;

	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{	
			struct usb_device_descriptor desc = dev->descriptor;
			if(desc.idVendor == vid && desc.idProduct == pid){
				handle = usb_open(dev);
				return 0;
			}else if(desc.idVendor == GOOGLE_VID && desc.idProduct == pid){
				handle = usb_open(dev);
				return 0;
			}
		}
	}
	return -1;
}

void print_devs()
{
	struct usb_bus *bus;
	struct usb_device *dev;
	int i=0;
	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		printf("bus_num \n",i++);
		for (dev = bus->devices; dev; dev = dev->next)
		{
			struct usb_device_descriptor desc = dev->descriptor;
			printf("%04x:%04x \n",desc.idVendor, desc.idProduct);
		}
	}
}

int init()
{
	usb_init();
	usb_find_busses();
	usb_find_devices();
	return 0;
}

int closeHandle()
{
	if(handle != NULL)
		usb_release_interface (handle, 0);
	return 0;
}

int chAccessoryMode(
		const char* manufacturer,
		const char* modelName,
		const char* description,
		const char* version,
		const char* url,
		const char* serialNumber)
{

	unsigned char ioBuffer[2];
	int devVersion;
	int response;
	int tries = 5;

	response = usb_control_msg(handle, 0xC0, 51, 0, 0, ioBuffer, 2, 0 );

	if(response < 0){return-1;}

	devVersion = ioBuffer[1] << 8 | ioBuffer[0];
	fprintf(stdout,"Verion Code Device: %d\n", devVersion);

	usleep(1000);

	response |= usb_control_msg(handle,0x40,52,0,0,manufacturer,strlen(manufacturer),0);
	response |= usb_control_msg(handle,0x40,52,0,1,modelName,strlen(modelName)+1,0);
	response |= usb_control_msg(handle,0x40,52,0,2,description,strlen(description)+1,0);
	response |= usb_control_msg(handle,0x40,52,0,3,version,strlen(version)+1,0);
	response |= usb_control_msg(handle,0x40,52,0,4,url,strlen(url)+1,0);
	response |= usb_control_msg(handle,0x40,52,0,5,serialNumber,strlen(serialNumber)+1,0);
	if(response < 0){return -1;}

	response = usb_control_msg(handle,0x40,53,0,0,NULL,0,0);
	if(response < 0){return -1;}

	for(;;){//attempt to connect to new PID, if that doesn't work try ACCESSORY_PID_ALT
		tries--;
		if(open_accesory_dev_from_id(GOOGLE_VID,ACCESSORY_PID) == 0){
			break;
		}else if(open_accesory_dev_from_id(GOOGLE_VID,ACCESSORY_PID_ALT) == 0){
			break;
		}else{
			if(tries < 0){
				usb_claim_interface(handle, 0);
				return -1;
			}
		}
		usleep(1000000);
	}

	if(handle != NULL){
		usb_release_interface (handle, 0);
	}
	return 0;
}

