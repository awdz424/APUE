#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
 
int main(int argc, char const *argv[])
{
	char *filename="./file";
	char buf[100];
	int fd;
	memset(buf,0,100);//inlizalize the buf to zero
	printf("open the file to read.\n");
	//open the file,create the file if it doesn't exit
	if ((fd=open(filename,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH))==-1)
	{
		perror("Cann't open the file");
		exit(1);
	}
	printf("open the file successfully!\n");
	printf("Please input a string:\n");
	gets(buf);

	//write a string to the file
	write(fd,buf,strlen(buf));
	close(fd);
	printf("open the file to read.\n");
	if ((fd=open(filename,O_RDONLY))==-1)
	{
		perror("Cann't open the file");
		exit(1);
	}

	//read from the file
	memset(buf,0,100);
	read(fd,buf,100);
	printf("The content read from the file is %s:\n",buf);
	close(fd);
	return 0;
}
