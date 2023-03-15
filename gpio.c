#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>     
#include <sys/stat.h>       
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include "gpio.h"

int gpio_export(mesg* mesg)
{  
	char name[16] = {0};  
	int fd = -1;
	int len = 0;  
	int ret = 0;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		return(-1);
	}
	sprintf(name, "%d", mesg->pin);  
	len = strlen(name);
	/*MizarSysLog(LOG_TYPE_DEBUG, "    gpio_export gpiopin = gpio%s", name);*/
	ret = write(fd, name, len);
	close(fd);
	
	if (ret < 0) 
	{
		/* GPIO errno=16, Device or resource busy, already exist*/
		if (errno == 16)
		{
			return 0;
		}
		else
		{
			return -1;  
		}
	}  
	
	return 0;  
} 

int gpio_direction(mesg* mesg)
{  
	char path[64] = {0};  
	int fd = -1;
	int res = -1;
	char *dir;
	if(mesg->flags & GPIO_IN)
		dir = "in";

	if(mesg->flags & GPIO_OUT)
		dir = "out";
	
	sprintf(path,"/sys/class/gpio/gpio%d/direction", mesg->pin);
	fd = open(path, O_WRONLY);
	if (fd < 0) {
		return -1;  
	}  
	res = write(fd, dir, sizeof(dir));
	close(fd);  
	if (res <= 0) {
		return -1;
	}
	
	return 0;
}

int gpio_read(mesg* mesg)
{
	char path[64] = {0};
	char value_str[4] = {0};
	int value = -1;
	int fd = -1;
	sprintf(path, "/sys/class/gpio/gpio%d/value", mesg->pin);  
	fd = open(path, O_RDONLY);
	if (fd < 0) {  
		return -1;  
	}
	
	if (read(fd, value_str, 3) < 0) {  
		close(fd);  
		return -1;
	}

	value = atoi(value_str);
	close(fd);
	return value;
}

int gpio_write(mesg* mesg, int value)
{  
	char path[128] = {0};  
	int fd = -1;  
	char value_str[16] = {0};
	
	sprintf(path, "/sys/class/gpio/gpio%d/value", mesg->pin);
	sprintf(value_str, "%d", value);

	fd = open(path, O_RDWR);
	if (fd < 0) {  
		printf("gpio_write  open failed\n");
		return -1;  
	}

	int res = write(fd, value_str, strlen(value_str));
	if (res <= 0) {
		close(fd);  
		printf("gpio_write failed\n");
		return -1;
	}
	close(fd);  
	return 0;  
}

int gpio_unexport(mesg* mesg)  
{  
	char name[4] = {0};  
	int len = 0;  
	int fd = -1;  
	
	fd = open("/sys/class/gpio/unexport", O_WRONLY);  
	if (fd < 0) {  
		printf("GPIO open unexport error: %d\n", fd);
		return -1;  
	}  
	len = sprintf(name, "%d", mesg->pin);
	if (write(fd, name, len) < 0) {  
		close(fd);  
		printf("write failed fd is %d\n", fd);
		return -1;  
	}  
	close(fd);  
	return 0;  
}



