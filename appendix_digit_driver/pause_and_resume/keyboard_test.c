#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/input.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


#define IOCTL_MAGIC 	'Z'
#define SET_VAL _IO(IOCTL_MAGIC, 0)
#define GET_KEY	_IO(IOCTL_MAGIC, 1)

sem_t sem;


void *handler(void *p){
	int key = 0;
	int fd = open("/dev/zlg7290", O_RDWR);
	if (fd<0){
		perror("thread open failed.");
		pthread_exit(p);
	}
	time_t t;
	struct tm *tm;
	while(1){
		ioctl(fd, GET_KEY, &key);
		if(key==1) break;
	}
	sem_wait(&sem);
	time(&t);
	tm = localtime(&t);
	int flag = 0;
	while(1){

		switch (key) {
			case 1:		
				break;
			case 2:
				tm->tm_sec++;
				break;
			case 3: 
				tm->tm_sec--; 
				break;
			case 4: 
				flag = 1;
				break;
			default: 
				break;
		}
		sprintf((char *)p, "%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
		ioctl(fd, SET_VAL, (char *)p);
		sleep(1);
		if(flag) break;
		ioctl(fd, GET_KEY, &key);
	}
	sem_post(&sem);
	pthread_exit(p);
}

int main(int argc, const char *argv[])
{
	char buf[8] = "8765 321";
	int value = 0;
	int fd = open("/dev/zlg7290", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}
	time_t t;
	struct tm *tm;
	

	sem_init(&sem, 0, 1);
	pthread_t thread;
	void *result;

	time(&t);
	tm = localtime(&t);
	sprintf(buf, "%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
	
	if(pthread_create(&thread, NULL, handler, (void *)buf))
		exit(-1);

	pthread_join(thread, &result);
	
	while(1) {

		time(&t);
		tm = localtime(&t);
		sprintf(buf, "%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);

		ioctl(fd, SET_VAL, buf);
		sleep(1);
	}

	return 0;
}

