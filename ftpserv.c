#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

void main(int argc,char* argv[]){
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        printf("Error in socket creation!!");
        exit(0);
    }
    int portno=atoi(argv[1]);
    struct sockaddr_in servaddr,cliaddr;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(portno);
    int servlen=sizeof(servaddr);
    int clilen=sizeof(clilen);
    if(bind(sock,(struct sockaddr*)&servaddr,servlen)<0){
        printf("Error in binding !!");
        exit(0);
    }
    listen(sock,5);
    int newsock=accept(sock,(struct sockaddr*)&cliaddr,&clilen);
    if(newsock<0){
        printf("Error in accepting connection!!");
        exit(0);
    }
    char command[5],filename[15];
    if(read(newsock,command,5)<0){
        printf("Error in reading command from client!!");
        exit(0);
    }
    if(read(newsock,filename,15)<0){
        printf("Error in reading filename from client!!");
        exit(0);
    }
    if(strcmp(command,"get")==0){
        FILE *fp;
        fp=fopen(filename,"r");
        char buffer[50];
        fgets(buffer,50,fp);
        if(write(newsock,buffer,50)<0){
            printf("Error in writing buffer content to client!!");
            exit(0);
        }


    }
    else if(strcmp(command,"put")==0){
        FILE *fp;
        fp=fopen("putfile.txt","w");
        char buffer[50];
        if(read(newsock,buffer,50)<0){
            printf("Error in reading buffer content from client!!");
            exit(0);
        }
        fprintf(fp,"%s",buffer);

    }
}