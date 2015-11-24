#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

/*
Time:2015.11.15
Author:louxj
Desctription:
	This source code aim at the target that provided that this is a directory,and we need to 
	serach through to find all the directory and file
*/

void showAllFile(const char * filepath);

int main(int argc, char const *argv[])
{
	if (argc!=2)
	{
		perror("Usage:./directory /home/louxj/workspace/");
		exit(-1);
	}
	showAllFile(argv[1]);
	return 0;
}

void showAllFile(const char* filepath)
{
	struct stat st;
	DIR *dp;
	struct dirent * dirp;
	char* pstr;
	if (lstat(filepath,&st)==-1)
	{
		perror("lstat() error");
		exit(-1);
	}

	//adjust the wether the file is a directory file
	if (S_ISDIR(st.st_mode)==0)
	{
		//it is a file
		printf("File:%s\n",filepath );
	}
	else
	{
		//it is directory and need operation to read the directory
		printf("Directory:%s\n",filepath );
		pstr=filepath+strlen(filepath);
		*pstr++='/';
		*pstr=0;

		//open the directory
		if ((dp=opendir(filepath))==NULL)
		{
			printf("opendir() error");
			exit(-1);
		}

		//read the content of the directory
		while((dirp=readdir(dp))!=NULL)
		{
			if (strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
			{
				continue;
			}
			strcpy(pstr,dirp->d_name);
			//repeatedly call
			showAllFile(filepath);
		}
	}

}

/*
[test]
gcc -o directory directory.c
./directory /home/louxj/workspace/

[Output]
Directory:/home/louxj/workspace/
Directory:/home/louxj/workspace//cpp
Directory:/home/louxj/workspace//cpp/chapter9
File:/home/louxj/workspace//cpp/chapter9/ex14.cpp
Directory:/home/louxj/workspace//networking
File:/home/louxj/workspace//networking/set_msgquene.c~
Directory:/home/louxj/workspace//networking/pipe
File:/home/louxj/workspace//networking/pipe/pipe_test2.c
File:/home/louxj/workspace//networking/pipe/pipe_test3.c
File:/home/louxj/workspace//networking/pipe/fifo_read.c
File:/home/louxj/workspace//networking/pipe/pipe_test1.c
File:/home/louxj/workspace//networking/pipe/fifo_write.c
File:/home/louxj/workspace//networking/set_msgquene.c
Directory:/home/louxj/workspace//networking/socket
File:/home/louxj/workspace//networking/socket/tcp_time_server.c
File:/home/louxj/workspace//networking/socket/tcp_time_server
Directory:/home/louxj/workspace//python
Directory:/home/louxj/workspace//c
Directory:/home/louxj/workspace//c/APUE
Directory:/home/louxj/workspace//c/APUE/chapter3
File:/home/louxj/workspace//c/APUE/chapter3/FileState.c
File:/home/louxj/workspace//c/APUE/chapter3/FileState
File:/home/louxj/workspace//c/APUE/chapter3/file
File:/home/louxj/workspace//c/APUE/chapter3/ReadWrite.c
File:/home/louxj/workspace//c/APUE/chapter3/temp.foo
Directory:/home/louxj/workspace//c/APUE/chapter4
File:/home/louxj/workspace//c/APUE/chapter4/directory.c
File:/home/louxj/workspace//c/APUE/chapter4/directory
Directory:/home/louxj/workspace//shell

*/