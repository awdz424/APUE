#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

//this is an example for access or faccessat

int main(int argc, char const *argv[])
{
	if (argc!=2)
	{
		perror("usage:./access <pathname>");
		exit(-1);
	}

	if (access(argv[1],F_OK)<0)
	{
		perror("file error");
	}else
	{
		printf("the file exits for %s\n", argv[1]);
	}

	if (access(argv[1],R_OK)<0)
	{
		perror("access error");
	}else
	{
		printf("read access OK for %s\n", argv[1]);
	}

	if (open(argv[1],O_RDONLY)<0)
	{
		perror("open error");
	}else
	{
		printf("open for reading OK.\n");
	}
	return 0;
}

/*
[Test]
gcc -o access access.c


[Output]
louxj@louxj:~/workspace/c/APUE/chapter4$ ls -l access
-rwxrwxr-x 1 louxj louxj 7346 11月 15 19:20 access
louxj@louxj:~/workspace/c/APUE/chapter4$ ./access access
the file exits for access
read access OK for access
open for reading OK.
louxj@louxj:~/workspace/c/APUE/chapter4$ ls -l /etc/shadow 
-r-------- 1 root shadow 1069 10月 24 21:40 /etc/shadow
louxj@louxj:~/workspace/c/APUE/chapter4$ ./access /etc/shadow
the file exits for /etc/shadow
access error: Permission denied
open error: Permission denied


*/