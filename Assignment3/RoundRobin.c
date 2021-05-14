#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
	char ppid[10];
	int at;
	int bt;
	int wt,tat,rt;
}proces;
int Quantum=0;
typedef struct
{
	char ppid[100];
	int start,end;
}gantt;
void input(proces *p,int n);
void display(proces *p,int n);
void RoundRobin(proces *p,int n);
int main()
{
	proces *p;
	int n;
	int ch=0;
	char cho;
	while(ch!=2)
	{
		printf(" 1.RoundRobin \n 2.EXIT\n\n Choice : ");
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("Enter the no. of proceses : ");
			scanf("%d",&n);
			p=(proces*)malloc(sizeof(proces)*n);
			input(p,n);
			RoundRobin(p,n);
			display(p,n);
			free(p);
		}
		
	}
	return 0;
}
void input(proces *p,int n)
{
	int i;
	printf("Enter Time Slice : ");
	scanf("%d",&Quantum);
	for(i=0;i<n;i++)
	{
		printf("\n\nEnter proces %d\n",i+1);
		printf("Enter proces id   : ");
		scanf("%s",p[i].ppid);
		printf("Enter arrival time : ");
		scanf("%d",&(p[i].at));
		printf("Enter burst time   : ");
		scanf("%d",&(p[i].bt));
	}
}
void display(proces *p,int n)
{	
	int i;
	float avg_wt=0,avg_rt=0;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("proces ID	Arrival Time	Burst Time	TurnaroundTime	Waiting Time	Response Time\n");
	printf("---------------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("%s                    %d             %d               %d             %d              %d          \n",p[i].ppid,p[i].at,p[i].bt,p[i].tat,p[i].wt,p[i].rt);         
		avg_wt+=p[i].wt;
		avg_rt+=p[i].rt;	
	}
	avg_wt/=n;
	avg_rt/=n;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("                                                  Average        %f              %f\n",avg_wt,avg_rt);
}
void RoundRobin(proces *t,int n)
{
	proces temp[n],p[n];
	int i,j,k,a=t[0].at;
	for(i=0;i<n;i++)
	{
		if(t[i].at<a)
		{
			a=t[i].at;
		}
	}
	k=0;
	for(i=0;i<=a;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==t[j].at)
			{
				temp[k]=t[j];
				k++;
				if(k==n)
					break;
			}
		}
	}
	int max=temp[0].at;
	int flag[n];
	for(i=0;i<n;i++)
	{
		flag[i]=0;
		if(t[i].at>max)
		max=t[i].at;
		max+=t[i].bt;
	}
	a=0;
	j=0;
	int l=0;
	gantt g[100];
	int gun[100],count=0;
	int index=0;
	int pr_j=0;
	while(a<max)
	{
		j=0;
		for(i=index;i<n;i++)
		{
			if(temp[i].at<=a && temp[i].bt>0)
			{
				p[j]=temp[i];
				j++;
			}
		}
		gun[count]=a;
		count++;

		if(j==0&&pr_j==0)
		{
			a++;
			gun[count]=a;
			printf(": %d idle %d :",gun[count-1],gun[count]);
			count++;
			index=0;
		}
		else if(j==0)
		{
			index=0;
			pr_j=0;
		}
		else 
		{
			pr_j=j;
			if(p[index].bt>=Quantum)
			{
				p[k-index].bt-=Quantum;
				a+=Quantum;
				gun[count]=a;
				printf(": %d %s %d :",gun[count-1],p[index].ppid,gun[count]);
				strcpy(g[l].ppid,p[index].ppid);
				g[l].start=gun[count-1];
				g[l].end=gun[count];
				count++;
				l++;
			}
			else
			{
				a+=p[index].bt;
				p[k-index].bt=0;
				gun[count]=a;
				printf(": %d %s %d :",gun[count-1],p[index].ppid,gun[count]);
				strcpy(g[l].ppid,p[index].ppid);
				g[l].start=gun[count-1];
				g[l].end=gun[count];
				count++;
				l++;
			}
			for(i=0;i<n;i++)
			{
				if(!strcmp(temp[i].ppid,p[index].ppid))
				{
					temp[i].bt=p[index].bt;
				}
			}
			index++;
			if(index==n)
			{
				index=0;
			}
		}
	}
	for(i=0;i<l;i++)
	{
		for(j=0;j<n;j++)
		{
			if(!strcmp(g[i].ppid,t[j].ppid))
			{
				if(flag[j]==0)
				{
					flag[j]=1;
					t[j].rt=g[i].start;
					
				}
				t[j].tat=g[i].end-t[j].at;
				t[j].wt=t[j].tat-t[j].bt;	
			}	
		}
	}
	printf("\n");
}