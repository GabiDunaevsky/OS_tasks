#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define SA struct sockaddr
#include <arpa/inet.h>
#include <signal.h>
#include <sys/un.h>
#include <netinet/in.h>
#define MAX 1024 



void func(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
	  bzero(buff, sizeof(buff));
	}
}


int main(int argc, char *argv[])
{
    int opt = getopt(argc, argv, "L");
    if(opt -= -1){
        if (argc != 3){
            printf("You have to provide a port number\n");
            exit(1);
        }
        int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   char buff[MAX];
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        exit(0);
    }
    else
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[2]));
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        exit(0);
    }

   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        exit(0);
    }
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        exit(0);
    }
    while (1)
    {    
        read(connfd, buff, sizeof(buff));
        printf("OUTPUT:%s",buff);
    }
   
    // After chatting close the socket
    close(sockfd);

    }
    else{
        char buffer[MAX] = {0};
        int n = 0;
        int sockfd, connfd;
        struct sockaddr_in servaddr, cli;
 
        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            exit(0);
        }
        else
        bzero(&servaddr, sizeof(servaddr));
    
        // assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(argv[1]);
        servaddr.sin_port = htons(atoi(argv[2]));
    
        // connect the client socket to server socket
        if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
            != 0) {
            exit(0);
        }
        else

            func(sockfd);
        close(sockfd);
}
}

