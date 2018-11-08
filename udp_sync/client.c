#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <complex.h>
#include <fftw3.h>
#include <fcntl.h>
#define MAXBUF 30
#define SERVER "10.28.4.99"
#define PORT 8888   
typedef struct buf {
float data[MAXBUF];
int n;//channel no.
}buf;
int val,result;
void die(char *s)
{
    perror(s);
    exit(1);
}

int main(void)
{
	struct sockaddr_in si_other, si_me;
	int s, slen=sizeof(si_other);
	int returnStatus;
	int addrlen;
	char buffer[MAXBUF],ref[MAXBUF];
	strcpy(ref, "START");
	int counter;
	struct buf * packets;
	packets = malloc(sizeof(buf));
	// variables of fft
	int i;
	int m,t;
        float f,g;
	fftw_plan p;
	fftw_complex in[MAXBUF/2][2];
	fftw_complex out[MAXBUF][2];
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}

	si_me.sin_family= AF_INET;
	si_me.sin_port = htons(11000);
	si_me.sin_addr.s_addr=htonl(INADDR_ANY);

	memset((char *) &si_other, 0, sizeof(si_other));
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
	}


/*	ptr_myfile=fopen("New2.txt","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	} */
	while(1)
	{
		recvfrom(s,buffer,MAXBUF,0,(struct sockaddr *)&si_other, &slen);
		if(strcmp(ref,buffer)==0)
		{
			/* read the file from the socket as long as there is data */
			if(recvfrom(s, packets, sizeof(buf), 0,(struct sockaddr *) &si_other, &slen))
			{ 
				if(packets->n == 1)
				{
					for(i=0;i<MAXBUF/2;i++)
					{
						m= packets->data[i];
					        t= m%10;	
					        if(t<0)
				        	{
				                	t=-1*t;
				        	}
					        f= (t*1)+(t*0.1)+(t*0.01);
						g= (t*1)+(t*0.1)+(t*0.01)+(t*0.001); /*creating a random Float*/
						in[i][0]=f;
						in[i][1]=g;
					}	
					p = fftw_plan_dft_1d(MAXBUF, (fftw_complex *)&in, (fftw_complex*)&out, FFTW_FORWARD, FFTW_ESTIMATE);
				        fftw_execute(p);   /* repeat as needed */
					for(i =0; i < MAXBUF/2; i++)
					printf("%f \t %fj \n", out[i][0], out[i][1]);
				}	
			}
			fftw_destroy_plan(p);
			continue;
		}
	}
	close(s);
	return 0;
}
