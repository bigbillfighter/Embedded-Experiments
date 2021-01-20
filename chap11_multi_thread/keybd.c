#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void *handler1(void *p){
    char le;    
    while(scanf(" %c", &le)){
        if(le=='x') break;
    }
    pthread_cancel((pthread_t)p);
    pthread_exit(NULL);
}

void *handler2(void *p){
    int i;
    for(i=0; i<=100; i++){
        printf("%d\n", i);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t p1, p2;

#if 1    
    char *s = NULL;
    void *result1, *result2;
    if(pthread_create(&p2, NULL, handler2, (void *)s))
        exit(-1);
    if(pthread_create(&p1, NULL, handler1, (void *)p2))
        exit(-1);
    pthread_join(p2, &result2);
    pthread_join(p1, &result1);

    while(1);
#endif 
    exit(0);
}
