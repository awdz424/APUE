#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

/*
Time:2015.11.15
Author:louxj
Desctription:
	This source code aim at the target that firstly,open a file and truncate the file content to 0,
	and then we use the function futimens to reset the time to the originator time when the file 
	was crated.
*/

int main(int argc, char const *argv[])
{
	int i;
	int fd;
	struct stat statbuf;
	struct timespec times[2];
	for (i = 1; i < argc; ++i)
	{
		if (stat(argv[i],&statbuf)<0)//fetch current time
		{
			fprintf(stderr, "stat:%s\n",strerror(errno));
			continue;
		}

		if ((fd=open(argv[i],O_RDWR|O_TRUNC))<0)//truncate
		{
			fprintf(stderr, "open:%s\n",strerror(errno));
			continue;
		}

		times[0]=statbuf.st_atim;//get the time of last access 
		times[1]=statbuf.st_mtim;//get the time of last modification

		if (futimens(fd,times)<0)//reset times
		{
			fprintf(stderr, "futimens:%s\n",strerror(errno));
		}
		close(fd);
	}
	return 0;
}

/*
[Test]
gcc -o futimens futimens.c


[Output]
louxj@louxj:~/workspace/c/APUE/chapter4$ ls -l changemod times 
-rw-rw-r-- 1 louxj louxj 51 11月 16 16:49 changemod
-rw-rw-r-- 1 louxj louxj 64 11月 16 16:49 times
louxj@louxj:~/workspace/c/APUE/chapter4$ date
2015年 11月 16日 星期一 16:49:56 CST
louxj@louxj:~/workspace/c/APUE/chapter4$ ./futimens changemod times 
louxj@louxj:~/workspace/c/APUE/chapter4$ ls -l changemod times 
-rw-rw-r-- 1 louxj louxj 0 11月 16 16:49 changemod
-rw-rw-r-- 1 louxj louxj 0 11月 16 16:49 times
louxj@louxj:~/workspace/c/APUE/chapter4$ ls -lu changemod times 
-rw-rw-r-- 1 louxj louxj 0 11月 16 16:49 changemod
-rw-rw-r-- 1 louxj louxj 0 11月 16 16:49 times
louxj@louxj:~/workspace/c/APUE/chapter4$ ls -lc changemod times 
-rw-rw-r-- 1 louxj louxj 0 11月 16 16:50 changemod
-rw-rw-r-- 1 louxj louxj 0 11月 16 16:50 times


*/