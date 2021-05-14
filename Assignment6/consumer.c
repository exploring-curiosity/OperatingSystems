#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>
#include<fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include<time.h>
extern int errno;
#define SIZE 20 /* size of the shared buffer*/

#define SHMPERM 0666
int shmid; /* id for shared memory bufer */
int empty_id;
int full_id;
int mutex_id;
int *buff;

sem_t *empty;
sem_t *full;
sem_t *mutex;

void consume()
{
	int i=1,n;
	n=buff[0];
	while (1)
	{
		if(i>n-1)
		{
			printf("\n Consumer exited \n");
			exit(1);
		}
		printf("\nConsumer trying to aquire Semaphore Full \n");
		sem_wait(full);
		printf("\nConsumer successfully aquired Semaphore Full \n");
		printf("\nConsumer trying to aquire Semaphore Mutex \n");
		sem_wait(mutex);
		printf("\nConsumer successfully aquired Semaphore Mutex\n");
		printf("\nConsumer Consumed Item [ %d ] \n",buff[i]);
		// buff[i]=' ';
		i++;
		printf("\nItems in Buffer %d\n",n);
		sem_post(mutex);
		printf("\nConsumer released Semaphore Mutex \n");
		sem_post(empty);
		printf("\nConsumer released Semaphore Empty \n");
	}
}

int main()
{
	shmid = shmget (111,SIZE,0);
	empty_id=shmget(112,sizeof(sem_t),0);
	full_id=shmget(113,sizeof(sem_t),0);
	mutex_id=shmget(114,sizeof(sem_t),0);
	buff = shmat(shmid,NULL,0);
	empty = shmat(empty_id,(char *)0,0);
	full = shmat(full_id,(char *)0,0);
	mutex = shmat(mutex_id,(char *)0,0);

	printf("Consuming\n");
	consume();
	shmdt(buff);
	shmdt(empty);
	shmdt(full);
	shmdt(mutex);
	shmctl(shmid, IPC_RMID, NULL);
	semctl( empty_id, 0, IPC_RMID, NULL);
	semctl( full_id, 0, IPC_RMID, NULL);
	semctl( mutex_id, 0, IPC_RMID, NULL);
	sem_destroy(empty);
	sem_destroy(full);
	sem_destroy(mutex);
	printf("\n Server process exited \n\n");
	return(0);
}
/*

[csec173@sel-28 Assignment6]$ ./c
Consuming

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 6 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 4 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 49 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 48 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 5 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 24 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 18 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 19 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

Consumer trying to aquire Semaphore Full 

Consumer successfully aquired Semaphore Full 

Consumer trying to aquire Semaphore Mutex 

Consumer successfully aquired Semaphore Mutex

Consumer Consumed Item [ 42 ] 

Items in Buffer 10

Consumer released Semaphore Mutex 

Consumer released Semaphore Empty 

 Consumer exited 


*/
