#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv){
    int fd;
    if(argc<2){
        fprintf(stdout, "Usage: %s <filename>\n", argv[0]);
        exit(1);        
    }
    if((fd=open(argv[1], O_RDONLY)) < 0){
        fprintf(stdout, "open fifo %s for reading failed: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    fprintf(stdout, "open fifo %s for reading successed.\n", argv[0]);
    
    char buffer[BUFFER_SIZE];
    ssize_t n;
    while(1){
again:
        if((n=read(fd, buffer, BUFFER_SIZE))<0){
            if(errno==EINTR) goto again;
            else{
                fprintf(stderr, "read failed on %s: %s\n", argv[1], strerror(errno));
                exit(1);
            }
        }else if(n==0){
            fprintf(stderr, "peer closed fifo.\n");
            
            break;
        }else{
            buffer[n] = '\0';
            fprintf(stdout, "read %d bytes from fifo: %s\n", n, buffer);
        }
    }
    return 0;
}
