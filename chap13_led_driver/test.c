#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "fs6818_led.h"

int main(int argc, char **argv)
{
	int fd;
	int i = 1;

	fd = open("/dev/led", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	while(1)
	{
		ioctl(fd, LED_ON, &i);
		usleep(500000);
		ioctl(fd, LED_OFF, &i);
		sleep(1);
		if (++i > 9)
			i = 1;
	}

	return 0;
}
