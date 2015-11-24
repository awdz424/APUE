#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	int i;
	//the file type info store in the st_mode of struct stat
	struct stat buf;
	char* ptr=NULL;

	for (i = 1; i < argc; ++i)
	{
		printf("%s:", argv[i]);
		if (lstat(argv[i],&buf)<0)
		{
			perror("lstat error");
			continue;
		}
		if (S_ISREG(buf.st_mode))
		{
			ptr="regular";
		}
		else if(S_ISDIR(buf.st_mode))
		{
			ptr="directory";
		}else if (S_ISCHR(buf.st_mode))
		{
			ptr="character special";
		}else if (S_ISBLK(buf.st_mode))
		{
			ptr="block special";
		}else if (S_ISFIFO(buf.st_mode))
		{
			ptr="fifo";
		}else if (S_ISLNK(buf.st_mode))
		{
			ptr="symbolic link";
		}
		else if (S_ISSOCK(buf.st_mode))
		{
			ptr="socket";
		}else
		{
			ptr="** unknown mode **";
		}
		printf("%s\n",ptr);
	}
	return 0;
}

/*
[test]
gcc -o stat stat.c
./stat /etc/passwd /etc/ /dev/log /dev/tty /tmp/opd_pipe /dev/sr0 /dev/cdrom

[Output]
/etc/passwd:regular
/etc/:directory
/dev/log:socket
/dev/tty:character special
/tmp/opd_pipe:fifo
/dev/sr0:block special
/dev/cdrom:symbolic link


*/