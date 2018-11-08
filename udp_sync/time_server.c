#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define MAXBUF 30
int main()
{
int udpSocket;
int returnStatus = 0;
int addrlen = 0;
int result;
int val;
int t=0,w;
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
/*setting the socket option to broadcast*/

val = 1;
result = setsockopt(udpSocket,SOL_SOCKET, SO_BROADCAST, &val,sizeof(val));
if (result < 0) {
perror("error1");
return 0;
}
udpClient.sin_family = AF_INET;
udpClient.sin_addr.s_addr = inet_addr("10.28.4.255");
udpClient.sin_port = htons(11000);


/* sending broadcast message */

strcpy(buf, "START");
while(1)
{
returnStatus = sendto(udpSocket, buf, strlen(buf)+1, 0,(struct sockaddr*)&udpClient,sizeof(udpClient));
if (returnStatus == -1) {
fprintf(stderr, "Could not send Broadcast message!\n");
}
else {
printf("Broadcast message sent.\n");
//w=t%2;
//t++;
//if(w==1)
//sleep(29);
//else
sleep(30);
}
}
/*cleanup */
close(udpSocket);
return 0;
}
