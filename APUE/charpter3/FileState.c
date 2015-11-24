#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int val;
	if (argc!=2)
	{
		perror("usage:<description>\n");
		exit(-1);
	}

	if ((val=fcntl(atoi(argv[1]),F_GETFL,0))==-1)
	{
		perror("fcntl error!\n");
		exit(-1);
	}

	switch(val&O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only.\n");
			break;
		case O_WRONLY:
			printf("write only.\n");
			break;
		case O_RDWR:
			printf("read and write.\n");
			break;
		default:
			printf("Unknown access mode.\n");
	}

	if (val&O_APPEND)
	{
		printf(",append\n");
	}

	if (val&O_NONBLOCK)
	{
		printf(",noblocking");
		putchar('\n');
	}
	return 0;
}