#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#define PORT 8888   //The port on which to listen for incoming data
#define MAXBUF 30
#define TOTALSENSORS 2

typedef struct buf {
float data[MAXBUF];
int n; //channel no.
}buf;
void die(char *s)
{
	perror(s);
		exit(1);
}
	
int main(void)
{
	struct sockaddr_in si_me, si_other;
	int s,slen = sizeof(si_other) , recv_len;
	int udpSocket;
	int returnStatus = 0;
	int addrlen = 0;
	struct buf * packets;
	FILE *ptr_myfile;
	int result,i;
	int readCounter =0,writeCounter;
	int val;
		packets = malloc(sizeof(buf));
		//create a UDP socket
		if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		{
			die("socket");
		}

		// zero out the structure
		memset((char *) &si_me, 0, sizeof(si_me));
		
		//si_me.sin_family = AF_INET;
		//si_me.sin_port = htons(PORT);
		//si_me.sin_addr.s_addr = inet_addr("10.28.4.88");
		
		val = 1;
		result = setsockopt(s,SOL_SOCKET, SO_BROADCAST, &val,sizeof(val));
		if (result < 0) {
			perror("error1");
			return 0;
		}
		//bind socket to port
		//if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
		//{
		//	die("bind");
		//}


		si_other.sin_family = AF_INET;
		si_other.sin_port = htons(11000);
		si_other.sin_addr.s_addr = inet_addr("10.28.4.255");
		
		i=0;
		ptr_myfile=fopen("sensor.txt","rb");
		if (!ptr_myfile)
		{
		printf("Unable to open file!");
				return 1;
		}
		while(1)
		{
			readCounter = fread(packets,sizeof(buf),1,ptr_myfile);
			packets->n= (i % TOTALSENSORS);
			i++;	
			writeCounter = sendto(s, packets, sizeof(buf)+1, 0,(struct sockaddr*)&si_other, slen);
			if (writeCounter == -1 || readCounter ==-1) 
			{
				fprintf(stderr, "Could not send message!\n");
			}
			else
			{
				printf("\nBroadcast msg Sent");
				sleep (1);
			}

		
		}
	close(s);
	return 0;
	}
