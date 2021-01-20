#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/input.h>

#define IOCTL_MAGIC 	'Z'
#define SET_VAL _IO(IOCTL_MAGIC, 0)
#define GET_KEY	_IO(IOCTL_MAGIC, 1)

int main(int argc, const char *argv[])
{
	int key = 0,i = 0;
	unsigned char buf[8];
	int value = 0;
	int fd = open("/dev/zlg7290", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	while(1) {
		ioctl(fd, GET_KEY, &key);
		switch (key) {
		case 1: value = '1'; break;
		case 2: value = '2'; break;
		case 3: value = '3'; break;
		case 4: value = '4'; break;
		default: value = 0x00; break;
		}
		printf ("get value : %d\n ",key);
		for (i = 0;i < 8;i++)
			buf[i] = value;
		ioctl(fd, SET_VAL, buf);
	}

	return 0;
}

