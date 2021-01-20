#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void init_daemon(void){
    int pid, i;
    if(pid=fork()){ // if is parent
        exit(0);
    }else if(pid<0){ // fail to fork
        exit(-1);
    }
    setsid();

    if(pid=fork()){ //first child process
        exit(0);
    }else if(pid<0){ // fail to fork
        exit(1);
    }
    for(i=0; i<getdtablesize(); i++) close(i); //close all of the open file description character
    chdir("/tmp"); // change the working dictionary to '/tmp'
    umask(0); // reset the mask
    return ;

}
