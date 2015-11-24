#include <stdio.h>

main()
{
	printf("hello,world\n");	
}


/*

louxj@louxj:~/workspace/c/APUE/charpter7$ gcc -std=c99 -o hello hello.c
hello.c:3:1: 警告： 返回类型默认为‘int’ [默认启用]
louxj@louxj:~/workspace/c/APUE/charpter7$ ./hello 
hello,world
louxj@louxj:~/workspace/c/APUE/charpter7$ echo $?
0


louxj@louxj:~/workspace/c/APUE/charpter7$ gcc -Wall -o hello hello.c
hello.c:3:1: 警告： 返回类型默认为‘int’ [-Wreturn-type]
hello.c: 在函数‘main’中:
hello.c:7:1: 警告： 在有返回值的函数中，控制流程到达函数尾 [-Wreturn-type]

*/