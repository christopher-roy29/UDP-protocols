#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <complex.h>
#include <fftw3.h>
#include <fcntl.h>
#define MAXBUF 1024
int main()
{
	int i,udpSocket;
	int returnStatus = 0;
	int addrlen = 0;
	struct sockaddr_in udpServer, udpClient;
	fftw_complex out[MAXBUF][2];
        FILE *ptr_myfile;
	/* create a socket */
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udpSocket == -1)
	{
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}	
	else 
	{
		printf("Socket created.\n");
	}
	/* set up the server address and port */
	/* use INADDR_ANY to bind to all local addresses */
	udpServer.sin_family = AF_INET;
	udpServer.sin_addr.s_addr = inet_addr("10.28.4.99");
	udpServer.sin_port = htons(8888);
	/* bind to the socket */
	returnStatus = bind(udpSocket, (struct sockaddr*)&udpServer,sizeof(udpServer));
	if (returnStatus == 0)
	{
		fprintf(stderr, "Bind completed!\n");
	}
	else 
	{
		fprintf(stderr, "Could not bind to address!\n");
		close(udpSocket);
		exit(1);
	}
	ptr_myfile=fopen("Node.txt","wb");
        if (!ptr_myfile)
        {
                printf("Unable to open file!");
                return 1;
        } 
	while (1)
	{
		addrlen = sizeof(udpClient);
		returnStatus = recvfrom(udpSocket, &out, sizeof(out), 0,(struct sockaddr*)&udpClient,&addrlen);
		if (returnStatus == -1) 
		{
			fprintf(stderr, "Could not receive message!\n");
		}
		for(i =0; i < MAXBUF/2; i++)
		{
                printf("%f \t %fj \n", out[i][0], out[i][1]);
                fwrite(&(out[i][0]),sizeof(out[i][0]),1, ptr_myfile);
                fwrite(&(out[i][1]),sizeof(out[i][1]),1, ptr_myfile);
                } 
	}
	close(udpSocket);
return 0;
}
