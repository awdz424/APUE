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
	An example for how to avoid zombie status for the child process
*/

int main(int argc, char const *argv[])
{
	pid_t pid;
	if ((pid=fork())<0)
	{
		fprintf(stderr, "fork:\n",strerror(errno));
	}else if (pid==0)//first child 
	{
		if ((pid=fork())<0)
		{
			fprintf(stderr, "fork:\n",strerror(errno));
		}else if (pid>0)//first child 
			exit(0);
		
		//second child 
		/*
		*We are the second child;our parent becomes init as 
		*soon as our real parent call exit() in the statemnet above.
		*Here's where we'd continue executing ,konwing that when 
		*we're done,init will reap our status.
		*/
		sleep(2);//ensure the first child exit
		printf("second child,parent pid=%ld\n",(long)getppid());
		exit(0);
	
	}

	if (waitpid(pid,NULL,0)!=pid)//wait for the first child 
	{
		fprintf(stderr, "waitpid:\n",strerror(errno));
	}

	/*
	*We are the parent process (the original process);We continue executing,
	*knowing that we're not the parent of the second child as the second child's 
	*parent was dead and the init 1 is the parent of the second child now.
	*/
	exit(0);

}

/*
[Test]
gcc -o avoidzombie avoidzombie.c
./avoidzombie

[Output]
second child,parent pid=1

*/