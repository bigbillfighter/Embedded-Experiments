#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <time.h>

#define SET_VAL _IO('Z', 0)

int main(int argc, const char *argv[])
{
	time_t t;
	struct tm *tm;
	
	char buf[8] = "8765 321";

	int fd = open("/dev/zlg7290", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	while(1) {
		time(&t);
		tm = localtime(&t);
		sprintf(buf, "%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
		printf("%s\n", buf);

		ioctl(fd, SET_VAL, buf);

		sleep(1);
	}

	return 0;
}

