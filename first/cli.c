#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#define PORT 8081
int main()
{
 int sockfd,n;
 struct sockaddr_in serv_addr;
 struct hostent *server;
 char buffer[256];
 sockfd = socket(AF_INET,SOCK_STREAM,0);
 if(sockfd < 0)
 {
   perror("error in socket");
   exit(1);
 }
 server = gethostbyname("localhost");
   // Get server address
    server = gethostbyname("localhost");
    if (server == NULL) {
        perror("Error, no such host");
        exit(1);
    }
 memset((char *)&serv_addr,0,sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 memcpy((char *)&serv_addr.sin_addr.s_addr,(char *)&server->h_addr,server->h_length);
 serv_addr.sin_port = htons(PORT);
 if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
 {
   perror("error connection");
   exit(1);
 }

 printf("enter the name");
 bzero(buffer,256);
 fgets(buffer,256,stdin);
 n = write(sockfd,buffer,strlen(buffer));
 if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }

 printf("server respon\n");
 while( (n = read(sockfd,buffer,256))> 0)
 {
  printf("%s",buffer);
  bzero(buffer,256);
 }
 
close(sockfd);
return 0;

}