#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10

int g_clnt_socks[CLNT_MAX];
int g_clnt_count = 0;

int main(int argc, char** argv){

   //socket
   int serv_sock;
   int clnt_sock;

   struct sockaddr_in clnt_addr;
   int clnt_addr_size;
  
   struct sockaddr_in serv_addr;
   serv_sock = socket(PF_INET, SOCK_STREAM, 0);

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(atoi("8080"));

   //bind
   if(bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){
      printf("bind error\n");
   }

   //listen
   if(listen(serv_sock,5) == -1){
      printf("listen error\n");
   }

   char buff[200];
   int recv_len = 0;

   while(1){
      //accept 
      clnt_addr_size = sizeof(clnt_addr);
      clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

      while(1){
         recv_len = read(clnt_sock, buff, 200);


         for(int i = 0;i<recv_len;i++){
            printf("%c",(unsigned char)buff[i]);
         }
         printf("\n");
      }

   }

}





