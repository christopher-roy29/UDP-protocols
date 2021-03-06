/*
    Simple udp client
    Silver Moon (m00n.silv3r@gmail.com)
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#define MAXBUF 1024
typedef struct buf {
char buffer[MAXBUF];
int n;
}buf;
#define SERVER "10.28.4.88"
#define BUFLEN 512  
#define PORT 8888   
int val,result;
void die(char *s)
{
    perror(s);
    exit(1);
}

int main(void)
{
	struct sockaddr_in si_other, si_me;
	int s, i, slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	int returnStatus;
	int addrlen;
	FILE *ptr_myfile;
	int counter;
	struct buf * packets;
	packets = malloc(sizeof(buf));
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}

	si_me.sin_family= AF_INET;
	si_me.sin_port = htons(11000);
	si_me.sin_addr.s_addr=htonl(INADDR_ANY);

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
	
	//val = 1;
	//result = setsockopt(s,SOL_SOCKET, SO_BROADCAST, &val,sizeof(val));
	
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
	}


	ptr_myfile=fopen("New2.txt","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}
	memset(buf,'\0', BUFLEN);
	//try to receive some data, this is a blocking call
//	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
//	{
//		die("recvfrom()");
//	}
//	puts(buf); 
	while(1)
	{
		/* read the file from the socket as long as there is data */
		while(recvfrom(s, packets, sizeof(buf), 0,(struct sockaddr *) &si_other, &slen))
		{ 
			if(packets->n == 0)
			{	
				fwrite(&(packets),sizeof(buf),1, ptr_myfile);
				printf("\nID: %d", packets->n);
			}
		}
	}
	close(s);
	return 0;
}
