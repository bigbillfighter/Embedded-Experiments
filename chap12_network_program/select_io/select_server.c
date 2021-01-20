#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N 64
typedef struct sockaddr SA;

int main(int argc, char *argv[]){
    int listenfd, connfd, maxfd, i;
    struct sockaddr_in servaddr, peeraddr;
    socklen_t len;
    char buf[N]= {0};
    fd_set rdfs, bakrdfs;
    ssize_t n;

    if(argc < 3){
        fprintf(stdout, "usage%s <ip> <port>\n", argv[0]);
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));

    if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(-1);
    }

    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    if(bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) == -1){
        perror("bind");
        exit(-1);
    }

    listen(listenfd, 5);
    maxfd = listenfd;

    FD_ZERO(&bakrdfs);
    FD_SET(listenfd, &bakrdfs);

    len = sizeof(peeraddr);
    while(1){
        rdfs = bakrdfs;
        if(select(maxfd+1, &rdfs, NULL, NULL, NULL) == -1){
            perror("select");
            exit(-1);
        }

        for(i=0; i<=maxfd; i++){
            if(FD_ISSET(i, &rdfs)){
                if(i==listenfd){
                    if((connfd = accept(i, (SA *)&peeraddr, &len))==-1){
                        perror("accept");
                        exit(-1);
                    }
                    fprintf(stdout, "welcome %s %d\n", inet_ntoa(peeraddr.sin_addr),
                            ntohs(peeraddr.sin_port));
                    FD_SET(connfd, &bakrdfs);
                    maxfd = (maxfd > connfd) ? maxfd : connfd;
                }else{
                    bzero(buf, sizeof(buf));
                    if((n=recv(i, buf, N, 0)) == 0){
                        close(i);
                        FD_CLR(i, &bakrdfs);
                    }else{
                        printf("n=%d %s\n", n, buf);
                        send(i, buf, N, 0);
                    }
                }
        
            }
        }
    }
    exit(0);
}