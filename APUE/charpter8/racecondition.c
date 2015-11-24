#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/*
Date:2015.11.17
Author:louxj
DEscription:
	the programme output two string,one is outputed by child process ,and other is outputed 
by parent process.the result of output is random.

*/

static void charatatime(char*);

int main(int argc, char const *argv[])
{
	pid_t pid;
	if ((pid=fork())<0)
	{
		fprintf(stderr, "fork:\n",strerror(errno));
	}else if (pid==0)
	{
		charatatime("output from child\n");
	}else
	{
		charatatime("output from parent\n");
	}
	exit(0);
}

static void charatatime(char *str)
{
	char *ptr;
	int c;
	setbuf(stdout,NULL);//set unbuffered	

	for (ptr = str; (c=*ptr++)!='\0'; )//output the char one by one with write
	{
		putc(c,stdout);
	}
}

/*
[Test]
gcc -o racecondition racedition.c
./racecondition

[Output]
louxj@louxj:~/workspace/c/APUE/charpter8$ ./racecondition 
output frooumt ppuatr efnrto
m child
louxj@louxj:~/workspace/c/APUE/charpter8$ gcc -o racecondition racecondition.c 
louxj@louxj:~/workspace/c/APUE/charpter8$ ./racecondition 
output frooumt ppuatr efnrto
m child
louxj@louxj:~/workspace/c/APUE/charpter8$ gcc -o racecondition racecondition.c 
louxj@louxj:~/workspace/c/APUE/charpter8$ ./racecondition 
outpuoutputt  ffrroomm  pcahrielndt

louxj@louxj:~/workspace/c/APUE/charpter8$ gcc -o racecondition racecondition.c 
louxj@louxj:~/workspace/c/APUE/charpter8$ ./racecondition 
output from parent
output from child

*/