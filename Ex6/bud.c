#include<sys/ipc.h>
# define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<stdio_ext.h>
#include<ctype.h>
// parent writing a char in shared memory and child reads it and prints it.
int main()
{
	int pid;
	char *a,*b,c;
	int id,n,i;
	// you can create a shared memory between parent and child here or you can //create inside them separately.
	id=shmget(111,50,IPC_CREAT | 00666);
	pid=fork();
	if(pid>0) //parent
	{
		// id=shmget(111,50,IPC_CREAT | 00666);
		a=shmat(id,NULL,0);
		printf("Parent :\nEnter a word :");
		scanf(" %[^\n]",a);
		wait(NULL);
		shmdt(a);
	}
	else //child
	{
		sleep(3);
		//id=shmget(111,50,0);
		b=shmat(id,NULL,0);
		int len=strlen(b);
		int i;
		for(i=0;i<len;i++)
		{
			if(b[i]>=97 && b[i]<=123)
				b[i]=b[i]-32;
		}
		printf("\nChild :\n%s\n",b);
		shmdt(b);
	}
	shmctl(id, IPC_RMID,NULL);
}

