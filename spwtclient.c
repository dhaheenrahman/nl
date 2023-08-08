#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame{
    int frame_kind; //ACK:0, SEQ:1 FIN:2
    int sq_no;
    int ack;
    Packet packet;
}Frame;

int main(int argc, char *argv[]){
    if (argc != 2){
		printf("Usage: %s <portno>", argv[0]);
		exit(0);	
	}

	int sockfd,portno;
	struct sockaddr_in serv_addr;
	char buffer[1024];
	socklen_t addr_size;

	int frame_id = 0;
	Frame frame_send;
	Frame frame_recv;
	int ack_recv = 1;
	
	//creating socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	portno = atoi(argv[1]);//portno saved to portno
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(portno);
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	
	//infinite loop
	while(1)
	{
		
		if(ack_recv == 1)
		{
			frame_send.sq_no = frame_id;
			frame_send.frame_kind = 1;
			frame_send.ack = 0;		
			
			//input the data
			printf("Enter Data: ");
			scanf("%s", buffer);
			//copy data
			strcpy(frame_send.packet.data, buffer);
			// send to server
			sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
			printf(" Frame Send\n");
		}
		int addr_size = sizeof(serv_addr);
		// recieve from server
		int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(frame_recv), 0 ,(struct sockaddr*)&serv_addr, &addr_size);
		
		//checking whether acknowledgement recieved or not
		if( f_recv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id+1)
		{
			printf(" Ack Received\n");
			ack_recv = 1;
		}else
		{
			printf(" Ack Not Received\n");
			ack_recv = 0;
		}	
  			
		frame_id++;		
	}
	
	close(sockfd);
	return 0;
}
