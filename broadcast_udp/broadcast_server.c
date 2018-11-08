#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define MAXBUF 1024
int main()
{
int udpSocket;
int returnStatus = 0;
int addrlen = 0;
int result;
int val;
struct sockaddr_in udpServer, udpClient;
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
/* set up the server address and port */
udpServer.sin_family = AF_INET;
udpServer.sin_addr.s_addr = inet_addr("10.28.4.88");
udpServer.sin_port = htons(11000);


/* bind to the socket */

returnStatus = bind(udpSocket, (struct sockaddr*)&udpServer,sizeof(udpServer));
if (returnStatus == 0)
{
fprintf(stderr, "Bind completed!\n");
}
else {
fprintf(stderr, "Could not bind to address!\n");
close(udpSocket);
exit(1);
}

/*setting the socket option to broadcast*/

val = 1;
result = setsockopt(udpSocket,SOL_SOCKET, SO_BROADCAST, &val,sizeof(val));
if (result < 0) {
perror("error1");
return 0;
}
udpClient.sin_family = AF_INET;
udpClient.sin_addr.s_addr = inet_addr("10.28.4.255");
udpClient.sin_port = htons(36000);


/* sending broadcast message */

strcpy(buf, "FIND ME\n");
while(1)
{
returnStatus = sendto(udpSocket, buf, strlen(buf)+1, 0,(struct sockaddr*)&udpClient,sizeof(udpClient));
if (returnStatus == -1) {
fprintf(stderr, "Could not send Broadcast message!\n");
}
else {
printf("Broadcast message sent.\n");
sleep(10);
}
}
/*cleanup */
close(udpSocket);
return 0;
}

