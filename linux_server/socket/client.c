#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFFSIZE 100
#define NAMESIZE 20

char message[BUFFSIZE];

int main(int argc, char **argv){
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) printf("socket() error\n");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1 ");
    serv_addr.sin_port = htons(atoi("8080"));

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1){
            printf("connect() error");
    }

    char msg[20] = "YONGARIGARIGARI!!";
    char greeting[20] = {'h','e','l','l','o'};
    while(1){

            write(sock,msg,20);
            sleep(1);
            write(sock, greeting,20);
            sleep(1);


    }
}

