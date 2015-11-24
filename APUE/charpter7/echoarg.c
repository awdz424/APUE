#include <stdio.h>

/*
date:2015.11.15
author:louxj
description:
	an example for echo command line arguments to the standard output.

*/

//traditional type 
/*int main(int argc, char const *argv[])
{
	int i;
	for (i = 0; i < argc; ++i)
	{
		printf("argv[%d]:%s\n",i,argv[i]);
	}
	return 0;
}*/

//another type
int main(int argc, char const *argv[])
{
	int i;
	for (i = 0; argv[i]!=NULL; i++)
	{
		printf("argv[%d]:%s\n",i,argv[i]);
	}
	return 0;
}

/*
[Output]
louxj@louxj:~/workspace/c/APUE/charpter7$ gcc -Wall -o echoarg echoarg.c 
louxj@louxj:~/workspace/c/APUE/charpter7$ ./echoarg haha xixi hehe
argv[0]:./echoarg
argv[1]:haha
argv[2]:xixi
argv[3]:hehe

*/