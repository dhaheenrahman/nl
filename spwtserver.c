#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame{
    int frame_kind; //ACK:0, SEQ:1 FIN:2
    int sq_no;
    int ack;
    Packet packet;
}Frame;

int main(int argc, char** argv){

	if (argc != 2){
		printf("Usage: %s <port>", argv[0]);
		exit(0);	
	}

	int sockfd,portno;
	struct sockaddr_in serv_addr, newAddr;
	char buffer[1024];
	socklen_t addr_size;

	int frame_id=0;
	Frame frame_recv;
	Frame frame_send;	

	
	//creating socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	portno = atoi(argv[1]);//portno saved to portno
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(portno);
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	
	//binding 
	bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	addr_size = sizeof(newAddr);

	while(1)
	{
		//recieve from client
		int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, (struct sockaddr*)&newAddr, &addr_size);
		
		if (f_recv_size > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == frame_id)
		{
			printf(" Frame Received: %s\n", frame_recv.packet.data);
			
			frame_send.sq_no = 0;
			frame_send.frame_kind = 0;
			frame_send.ack = frame_recv.sq_no + 1;
			//send to client
			sendto(sockfd, &frame_send, sizeof(frame_send), 0, (struct sockaddr*)&newAddr, addr_size);
			printf(" Ack Send\n");
		}
		else
		{
			printf(" Frame Not Received\n");
		}
		frame_id++;	
	}
	
	close(sockfd);
	return 0;
}
