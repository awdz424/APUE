#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/*
date:2015.11.15
Author:louxj
description:
an example for atexit which can call at most 32 exit handlers before the main function exit,
these exit handlers will be called by exit automaticly.
*/
static void my_exit1(void);
static void my_exit2(void);

int main(int argc, char const *argv[])
{
	if(atexit(my_exit2)!=0)//register exit handler my_exit2
		fprintf(stderr, "atexit(my_exit2):%d\n", strerror(errno));	

	if(atexit(my_exit1)!=0)//register exit handler my_exit1
		fprintf(stderr, "atexit(my_exit1):%d\n", strerror(errno));

	if(atexit(my_exit1)!=0)//register exit handler my_exit1
		fprintf(stderr, "atexit(my_exit1):%d\n", strerror(errno));
	printf("main is done.\n");
	return 0;
}

static void my_exit1(void)
{
	printf("first exit handler\n");
}

static void my_exit2(void)
{
	printf("second exit handler\n");
}

/*
[Output]
louxj@louxj:~/workspace/c/APUE/charpter7$ gcc -o atexit atexit.c 
louxj@louxj:~/workspace/c/APUE/charpter7$ ./atexit 
main is done.
first exit handler
first exit handler
second exit handler

*/