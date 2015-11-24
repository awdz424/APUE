#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (chdir("/tmp")<0)
	{
		fprintf(stderr, "chadir:%s\n",strerror(errno));
	}
	printf("chdir to /tmp successfully!\n");
	return 0;
}