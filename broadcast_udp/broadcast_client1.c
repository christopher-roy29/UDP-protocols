#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#define MAXBUF 1024
int main()
{	
	int udpSocket;
	int returnStatus;
	int addrlen;
	int fd;
	int counter;
	struct sockaddr_in udpClient, udpServer;
	char buf[MAXBUF];
	/* create a socket */
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSocket == -1)
	{
	fprintf(stderr, "Could not create a socket!\n");
	exit(1);
	}
	else {
	printf("Socket created.\n");
	}
	/* client address */
	/* use INADDR_ANY to use all local addresses */
	udpClient.sin_family = AF_INET;
	udpClient.sin_addr.s_addr = INADDR_ANY;
	//udpClient.sin_addr.s_addr = inet_addr("10.28.4.88");
	udpClient.sin_port = htons(35000);
	returnStatus = bind(udpSocket,(struct sockaddr*)&udpClient,sizeof(udpClient));
	if (returnStatus == 0) {
	fprintf(stderr, "Bind completed!\n");
	}
	else {
	fprintf(stderr, "Could not bind to address!\n");
	close(udpSocket);
	exit(1);
	}
	/* server address */
/*	udpServer.sin_family = AF_INET;
	udpServer.sin_addr.s_addr = inet_addr("10.28.4.88");
	udpServer.sin_port =htons(11000); */
	addrlen = sizeof(udpServer); 
	/* open up a handle to our destination file to receive the contents */
	/* from the server */
	fd = open ("New2.txt", O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
	{
	fprintf(stderr, "Could not open destination file, using stdout.\n");
	fd = 1;
	}
	/* read the file from the socket as long as there is data */
	while((counter = recvfrom(udpSocket, buf, MAXBUF, 0,(struct sockaddr*)&udpServer, &addrlen))>0)
	{ 
	/* send the contents to stdout */
	write(fd, buf, counter);
	}
	if (counter == -1)
	{
	fprintf(stderr, "Could not read file from socket!\n");
	exit(1);
	}
	else{
	printf("Received: %s \n",buf); 
	}	
	close(fd);
	close(udpSocket);
	return 0;
}
