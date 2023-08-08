#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>

void main(int argc,char * argv[]){
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    int portno=atoi(argv[1]);
    struct sockaddr_in servaddr,cliaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(portno);
    int servlen=(sizeof(servaddr));

    int num1,num2,sum;
    printf("Enter two numbers: \n");
    scanf("%d%d",&num1,&num2);
    sendto(sock,&num1,sizeof(num1),0,(struct sockaddr*)&servaddr,servlen);
    sendto(sock,&num2,sizeof(num2),0,(struct sockaddr*)&servaddr,servlen);
    recvfrom(sock,&sum,sizeof(sum),0,(struct sockaddr*)&servaddr,&servlen);
    printf("%d",sum);
}