#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>
#include <sys/time.h>

sem_t sem;
struct timeval tv1;

void *handler(void *p){
    struct timeval tv2;
    do{
        gettimeofday(&tv2, NULL);
    }while(tv2.tv_usec - tv1.tv_usec<1e5);
    sem_wait(&sem);
    char *a = (char *)p;
    printf("%s", a);
    pthread_exit(NULL);
}

int main(){
    pthread_t p1, p2, p3;
#if 1
    void *result1, *result2, *result3;
    char s1[100], s2[100], s3[100];
    if(sem_init(&sem, 0, 2))
        exit(-1);
    gettimeofday(&tv1, NULL);    
   
    strcpy(s1, "thread 1 has one ticket\n");
    if(pthread_create(&p1, NULL, handler, (void *)(s1)))
        exit(-1);      
    strcpy(s2, "thread 2 has one ticket\n");
    if(pthread_create(&p2, NULL, handler, (void *)(s2)))
        exit(-1);
    strcpy(s3, "thread 3 has one ticket\n");
    if(pthread_create(&p3, NULL, handler, (void *)(s3)))
        exit(-1);
   
    pthread_join(p1, &result1);
    pthread_join(p2, &result2);
    pthread_join(p3, &result3);
    while(1);
#endif
    exit(0);
}
