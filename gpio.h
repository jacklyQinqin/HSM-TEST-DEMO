#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdlib.h>  
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define GPIO_IN	  		0x80
#define GPIO_OUT	 	0x40


typedef struct {
	int pin;
	int value;
	unsigned char flags;
} mesg;

int gpio_unexport(mesg* mesg);
int gpio_read(mesg* mesg);
int gpio_write(mesg* mesg, int value);
int gpio_direction(mesg* mesg);
int gpio_export(mesg* mesg);

#endif
