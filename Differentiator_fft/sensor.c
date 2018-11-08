#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int counter; float p;
	FILE *ptr_myfile;
	ptr_myfile=fopen("sensor.txt","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}
	for (counter=1;;counter++)
	{
		p=rand();
		fwrite(&p, sizeof(p), 1, ptr_myfile);
		printf("Writing data \n");
	}
	fclose(ptr_myfile);
	return 0;
}



