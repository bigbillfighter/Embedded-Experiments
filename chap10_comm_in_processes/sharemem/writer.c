#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define N 64

typedef struct{
    int pid;
    char buf[N];
}shmbuf;

void handler(int signo){
    return ;
}

int main(int argc, char *argv[]){
    int shmid;
    key_t key;
    pid_t pid;  
    shmbuf *shmaddr;
    signal(SIGUSR1, handler);
    if((key = ftok(".", 'a'))<0){
        perror("fail to ftok");
        exit(-1);
    }
    if((shmid=shmget(key, sizeof(shmbuf), IPC_CREAT | IPC_EXCL | 0x66))<0)
