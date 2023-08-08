#include<stdio.h>
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
    if(connect(sock,(struct sockaddr*)&servaddr,servlen)<0){
        printf("Error in binding !!");
        exit(0);
    }
    char command[5],filename[15];
    printf("Enter command");
    scanf("%s",command);
    printf("Enter filename");
    scanf("%s",filename);
    
    if(write(sock,command,5)<0){
        printf("Error in writing command to server!!");
        exit(0);
    }
    if(write(sock,filename,15)<0){
        printf("Error in writing filename to server!!");
        exit(0);
    }
    if(strcmp(command,"get")==0){
        FILE *fp;
        fp=fopen("getfile.txt","w");
        char buffer[50];
        if(read(sock,buffer,50)<0){
            printf("Error in reading buffer content from server!!");
            exit(0);
        }
        fprintf(fp,"%s",buffer);
    }
    else if(strcmp(command,"put")==0){
        FILE *fp;
        fp=fopen(filename,"r");
        char buffer[50];
        fgets(buffer,50,fp);
        if(write(sock,buffer,50)<0){
            printf("Error in writing buffer content to server!!");
            exit(0);
        }

    }
}