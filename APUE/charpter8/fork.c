#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/*
Data:2015.11.17
Author:louxj
Descriptiin:
	the variable change in the child process deesn't affect the coresponding variable in the parent process 

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
	printf("before fork.\n");

	if ((pid=fork())<0)
	{
		fprintf(stderr, "fork():%s\n", strerror(errno));
	}else if (pid==0)//child process
	{
		golbalvar++;
		localvar++;
	}else//parent process
	{
		sleep(2);
	}
	printf("pid=%ld,golbalvar=%d,localvar=%d\n",(long)getpid(),golbalvar,localvar);
	exit(0);
}

/*
[Test]
gcc -Wall -o fork fork.c
./fork

[Output]
a write to stdout
before fork.
pid=2655,golbalvar=7,localvar=9
pid=2654,golbalvar=6,localvar=8


*/