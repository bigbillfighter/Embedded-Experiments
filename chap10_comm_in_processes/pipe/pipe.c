#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int pid1, pid2;

int main(){
    int fd[2];
    char outpipe[100], inpipe[100];
    pipe(fd);
    while((pid1=fork())==-1);
    if(pid1==0){
        lockf(fd[1], 1, 0);
        sprintf(outpipe, "child 1 process is sending message!"); // send string to outpipe
        write(fd[1], outpipe, 50); //write 50 charactes to pip
        sleep(2);
        lockf(fd[1], 0, 0);
        exit(0);
    }else{
        while((pid2=fork())==-1);
        if(pid2==0){
            lockf(fd[1], 1, 0); //mutual exclusive
            sprintf(outpipe, "child 2 process is sending message!");
            write(fd[1], outpipe, 50);
            sleep(2);
            lockf(fd[1], 0, 0);
            exit(0);
        }else{
            wait(NULL); //synchronization
            read(fd[0], inpipe, 50); //read 50 characters from pipe
            printf("%s\n", inpipe);
            wait(NULL);
            read(fd[0], inpipe, 50);
            printf("%s\n", inpipe);
            exit(0);
        }
    }
}