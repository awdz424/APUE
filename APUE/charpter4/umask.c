#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char const *argv[])
{
	//shield no visiting bit in the current process 
	umask(0);
	if (creat("./foo",RWRWRW)<0)//create file foo in the current directory
	{
		perror("create error for file foo");
	}

	//shield read and write visiting bit for user group and other group in the current process
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);//set the correspoing visiting bit to zero
	if (creat("./bar",RWRWRW)<0)//create file bar in the current directory
	{
		perror("create error for file bar");
	}
	return 0;
}


/*
[Test]
gcc -o umask umask.c

[Output]
louxj@louxj:~/workspace/c/APUE/chapter4$ umask
0002
louxj@louxj:~/workspace/c/APUE/chapter4$ ./umask 
louxj@louxj:~/workspace/c/APUE/chapter4$ ls -l foo bar
-rw------- 1 louxj louxj 0 11月 15 19:38 bar
-rw-rw-rw- 1 louxj louxj 0 11月 15 19:38 foo


*/