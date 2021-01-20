#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;
#define N 64

int main(int argc, char *argv[]){
    int sockfd;
    ssize_t n;
    struct sockaddr_in servaddr;
    char buf[N] = {0};

    if(argc<3){
        fprintf(stdout, "usage:%s ip port\n", argv[0]);
        exit(0);
    }
    if((sockfd=socket(PF_INET, SOCK_STREAM, 0))==-1){
        perror("socket");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = PF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) == -1){
        perror("connect");
        exit(-1);
    }

    printf(">");
    while(fgets(buf, N, stdin) != NULL){
        buf[strlen(buf)-1] = 0;
        send(sockfd, buf, N, 0);
        bzero(buf, sizeof(buf));
        n = recv(sockfd, buf, N, 0);
        printf("n=%d buf=%s\n", n, buf);
        printf(">");
    }
    close(sockfd);
    exit(0);
}