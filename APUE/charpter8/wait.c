#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/*
Date:2015.11.17
Author:louxj
Description:
	An example for a test by using wait to collect termination info from child process 
and display them. 

*/

void pr_exit(int status);

int main(int argc, char const *argv[])
{
	pid_t pid;
	int status;

	//test 1
	if ((pid=fork())<0)
	{
		fprintf(stderr, "fork():%s\n", strerror(errno));
	}
	else if(pid==0)
	{
		exit(7);
	}
	if (wait(&status)!=pid)
	{
		fprintf(stderr, "wait:%s\n", strerror(errno));
	}
	pr_exit(status);

	//test 2
	if ((pid=fork())<0)
	{
		fprintf(stderr, "fork():%s\n", strerror(errno));
	}
	else if(pid==0)
	{
		abort();
	}
	if (wait(&status)!=pid)
	{
		fprintf(stderr, "wait:%s\n", strerror(errno));
	}
	pr_exit(status);

	//test 3
	if ((pid=fork())<0)
	{
		fprintf(stderr, "fork():%s\n", strerror(errno));
	}
	else if(pid==0)
	{
		status/=0;
	}
	if (wait(&status)!=pid)
	{
		fprintf(stderr, "wait:%s\n", strerror(errno));
	}
	pr_exit(status);

	exit(0);
}


void pr_exit(int status)
{
	if(WIFEXITED(status))
	{
		printf("normal termination,exit status=%d\n",WEXITSTATUS(status));
	}else if (WIFSIGNALED(status))
	{
		printf("abnormal termination,signal number=%d%s\n", WTERMSIG(status),
			#ifdef WCOREDUMP
				WCOREDUMP(status)?"(core file generated)":"");
			#else
				);
			#endif
			
	}else if (WIFSTOPPED(status))
	{
		printf("child stopped,signal number=%d\n",WSTOPSIG(status));
	}
}

/*
[Test]
gcc -Wall -o wait wait.c
./wait

[Output]
normal termination,exit status=7
abnormal termination,signal number=6(core file generated)  --6 SIGABRT
abnormal termination,signal number=8(core file generated)  --8 SIGFPE


*/