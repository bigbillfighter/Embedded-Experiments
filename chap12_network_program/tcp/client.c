#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define N 64

int main(int argc, char *argv[]) { //./server ip port
	int sockfd;
	struct sockaddr_in servaddr, myaddr;
	char buf[N] = {0};
	
	if (argc < 3) {
		printf("usage:%s ip port\n", argv[0]);
		return 0;
	}
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(-1);
	}
	
#if 0
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8000);//"6000"--6000 htons(6000);
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
		perror("bind");
		exit(-1);
	}
	
#endif
	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));//"6000"--6000 htons(6000);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
		perror("connect");
		exit(-1);
	}
	
	printf(">");
	while (fgets(buf, N, stdin) != NULL) {
//abc\n --- a b c \n \0----
		send(sockfd, buf, strlen(buf), 0);
		memset(buf, 0, sizeof(buf));
		recv(sockfd, buf, N, 0);
		printf("%s\n", buf);
		printf(">");
	}
	close(sockfd);
	
	return 0;
}
