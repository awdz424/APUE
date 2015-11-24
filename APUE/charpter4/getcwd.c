#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	char *ptr;
	size_t size;
	if (chdir("/usr/spool/uucppublic")<0)
	{
		fprintf(stderr, "chadir:%s\n",strerror(errno));
	}
	ptr=path_alloc(&size);
	if (getcwd(ptr,size)==NULL)
	{
		fprintf(stderr, "getcwd:%s\n",strerror(errno));
	}
	printf("cwd=%s\n",ptr);

	return 0;
}