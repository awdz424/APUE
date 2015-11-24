#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*
Data:2015.11.17
Author:louxj
Descriptiin:
	An example for how to use vfork.

*/

int golbalvar=6;//external variable in initialized data
char buf[]="a write to stdout\n";

int main(int argc, char const *argv[])
{
	int localvar=8;//automatic variable on the stack
	pid_t pid;
	if (write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1)
	{
		fprintf(stderr, "write:%s\n",strerror(errno));
	}
	printf("before vfork.\n");

	if ((pid=vfork())<0)
	{
		fprintf(stderr, "vfork():%s\n", strerror(errno));
	}else if (pid==0)//child process
	{
		golbalvar++;//modify parent's variables
		localvar++;
		printf("child:pid=%ld,golbalvar=%d,localvar=%d\n",(long)getpid(),golbalvar,localvar);
		_exit(0);//child process terminates
	}

	//parent continues here
	printf("parent:pid=%ld,golbalvar=%d,localvar=%d\n",(long)getpid(),golbalvar,localvar);
	exit(0);
}

/*
[Test]
gcc -Wall -o vfork vfork.c
./vfork

[Output]
a write to stdout
before vfork.
child:pid=2924,golbalvar=7,localvar=9
parent:pid=2923,golbalvar=7,localvar=9

*/