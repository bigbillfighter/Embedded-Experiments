#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int global = 22;
char buf[] = "the test content!\n";

int main(void){
    int test = 0, stat;
    pid_t pid;
    if(write(STDOUT_FILENO, buf, sizeof(buf))!=sizeof(buf)){
        perror("write error!");
    }
    printf(" fork test!\n");
    //fork
    pid = fork();
    if(pid==-1){ // fail to build child process
        perror("fork");
        exit(0);
    }else if(pid==0){ // child process
        global++, test++;
        printf("global=%d test=%d Child, my PID is %d\n", global, test, getpid());
        exit(0);
    }else{ //parent process
        global+=2, test+=2;
        printf("global=%d test=%d Parent, my PID is %d\n", global, test, getpid());
        exit(0);
    }
    // The "global" is copied in child process, and are independent from each other. 
    return 0;
}
