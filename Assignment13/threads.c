#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

float avg;
int max,min;

void *average(void *a)
{
	int s=0,i=1;
	int *arr=(int*)a;
	for(i=1;i<arr[0];i++)
		s+=arr[i];
	avg=s*1.0/(i-1);
	pthread_exit(0);
}

void *maximum(void *a)
{
	int i=2;
	int *arr=(int*)a;
	max=arr[1];
	for(;i<arr[0];i++)
		if(max<arr[i])
			max=arr[i];
	pthread_exit(0);
}

void *minimum(void *a)
{
	int i=2;
	int *arr=(int*)a;
	min=arr[1];
	for(;i<arr[0];i++)
		if(min>arr[i])
			min=arr[i];
	pthread_exit(0);
}

void main(int argc,char* argv[])
{
	pthread_t t1,t2,t3;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	int i=1;
	int *arr=calloc(100,sizeof(int));
	arr[0]=argc;
	for(i=1;i<=argc;i++)
        arr[i]= atoi(argv[i]);
	
	pthread_create(&t1,&attr,average,arr);
	pthread_create(&t2,&attr,maximum,arr);
	pthread_create(&t3,&attr,minimum,arr);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);

	printf("AVG = %0.2f\n",avg);
	printf("MAX = %d\n",max);
	printf("MIN = %d\n",min);
}
	
/*

PS F:\SEM4\OS\Assignment13> gcc -o k threads.c
PS F:\SEM4\OS\Assignment13> ./k 11 12 13 14 15
AVG = 13.00
MAX = 15
MIN = 11
PS F:\SEM4\OS\Assignment13>

*/	
