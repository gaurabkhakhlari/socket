#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 8080

int main()
{

  int sockfd,newsocked,clientlen,n;
  struct sockaddr_in serv_addr,cli_addr;
  char buffer[256];
  sockfd=socket(AF_INET,SOCK_STREAM ,0);
  if(sockfd < 0)
  {
   perror("error opening socket");
   exit(1);
  }
  memset((char *)&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr= INADDR_ANY;
  serv_addr.sin_port = htons(PORT);
  if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
  {


   perror("error binding");
   exit(1);

  }
   listen(sockfd,5);
  printf("server listening on port %d...\n",PORT);
  clientlen=sizeof(cli_addr);
  newsocked = accept(sockfd,(struct sockaddr *)&cli_addr,&clientlen);
 if(newsocked < 0)
 {
  perror("error accepting connection");
  exit(1);

 }

 bzero(buffer,256);
  n =  read(newsocked,buffer,256);
  if( n <  0)
  {
   perror("error reading socket");
  exit(1);
  }
  int num = atoi(buffer);
  printf("recived number from client :%d\n",num);
  for(int i = 0;i<num;i++)
 {
     char respone []="hello world";
     n = write(newsocked,respone,strlen(respone));
  
 }

close(newsocked);
close(sockfd);
}
