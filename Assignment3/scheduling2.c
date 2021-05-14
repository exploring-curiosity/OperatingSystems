#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
	char ppid[10];
	int at;
	int bt;
	int wt,tat,rt;
	int pr;
}proces;
typedef struct
{
	char ppid[100];
	int start,end;
}gantt;
void input(proces *p,int n);
void display(proces *p,int n);
void schedule_priority_np(proces *t,int n);
void schedule_priority_p(proces *t,int n);
int smallest_process(proces *p,int n);
void main()
{
	proces *p;
	int n;
	int ch=0;
	char cho;
	while(ch!=3)
	{
		printf(" 1.Priority_Non_preemtive \n 2.Priority_Preemtive\n 3.EXIT\n\n Choice : ");
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("Enter the no. of proceses : ");
			scanf("%d",&n);
			p=(proces*)malloc(sizeof(proces)*n);
			input(p,n);
			schedule_priority_np(p,n);
			display(p,n);
			free(p);
		}
		else if(ch==2)
		{
			printf("Enter the no. of proceses : ");
			scanf("%d",&n);
			p=(proces*)malloc(sizeof(proces)*n);
			input(p,n);
			schedule_priority_p(p,n);
			display(p,n);
			free(p);
		}
	}
}
void input(proces *p,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("\n\nEnter proces %d\n",i+1);
		printf("Enter proces id   : ");
		scanf("%s",p[i].ppid);
		printf("Enter arrival time : ");
		scanf("%d",&(p[i].at));
		printf("Enter burst time   : ");
		scanf("%d",&(p[i].bt));
		printf("Enter priority     : ");
		scanf("%d",&(p[i].pr));
	}
}
void display(proces *p,int n)
{	
	int i;
	float avg_wt=0,avg_rt=0,avg_tat=0;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("proces ID	Arrival Time	Burst Time	TurnaroundTime	Waiting Time	Response Time\n");
	printf("---------------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("%s                    %d             %d               %d             %d              %d          \n",p[i].ppid,p[i].at,p[i].bt,p[i].tat,p[i].wt,p[i].rt);         
		avg_wt+=p[i].wt;
		avg_rt+=p[i].rt;
		avg_tat+=p[i].tat;	
	}
	avg_wt/=n;
	avg_rt/=n;
	avg_tat/=n;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("                               Average      %f             %f              %f\n",avg_tat,avg_wt,avg_rt);
}
void schedule_priority_np(proces *t,int n)
{
	proces temp[n];
	int i,j,a=-1,b=0;
	for(i=0;i<n;i++)
	{
		if(t[i].at>a)
			a=t[i].at;
		t[i].wt=0;
		t[i].rt=-1;
		t[i].tat=0;
	}
	int k=0;
	for(i=0;i<=a;i++)
	{
		for(j=0;j<n;j++)
		{
			if(t[j].at==i)
			{
				temp[k]=t[j];
				k++;
				if(k>=n)
				break;
			}
		}
	}
	k=0;
	int max=temp[0].at;
	for(i=0;i<n;i++)
	{
		if(t[i].at>max)
		max=t[i].at;
		max+=t[i].bt;
	}
	a=0;
	proces temporary[n];
	j=0;
	proces idle,small,previous;
	strcpy(idle.ppid,"idle");
	idle.at=-1;
	idle.bt=-1;
	idle.pr=-1;
	int f=0;
	gantt g[100];
	int index,count=0,gun[100];
	j=0;
		for(i=0;i<n;i++)
		{
			if(temp[i].at<=a && temp[i].bt>0)
			{
				temporary[j]=temp[i];
				j++;
			}
		}
		if(j==0)
		{
			small=idle;
		}
		else
		{
			index=smallest_process(temporary,j);
			small=temporary[index];
		}

		printf("\t\t GANTT CHART\n\t");
	while(a<max)
	{
		
		if(strcmp(small.ppid,previous.ppid))
		{
			gun[count]=a;
			count++;
			printf(" : %d %s ",gun[count-1],small.ppid);
			g[f].start=gun[count-1];
			strcpy(g[f].ppid,small.ppid);
		}
		
		if(!strcmp(small.ppid,idle.ppid))
		{
			a++;
		}
		else
		{
			a+=small.bt;
			temporary[index].bt=0;
		}
		if(j!=0)
		{
			for(i=0;i<n;i++)
			{
				if(!strcmp(temporary[index].ppid,temp[i].ppid))
				{
					temp[i]=temporary[index];
				}
			}
		}
		previous=small;
		j=0;
		for(i=0;i<n;i++)
		{
			if(temp[i].at<=a && temp[i].bt>0)
			{
				temporary[j]=temp[i];
				j++;
			}
		}
		if(j==0)
		{
			small=idle;
		}
		else
		{
			index=smallest_process(temporary,j);
			small=temporary[index];
		}
		if(strcmp(small.ppid,previous.ppid))
		{
			gun[count]=a;
			printf("%d :",gun[count]);
			count++;
			g[f].end=gun[count-1];
			f++;
		}
	}
	printf("\n");

	for(i=0;i<f;i++)
	{
		for(j=0;j<n;j++)
		{
			if(!strcmp(temp[j].ppid,g[i].ppid))
			{
				if(temp[j].rt==-1)
				{
					temp[j].rt=g[i].start-temp[j].at;
					temp[j].wt=temp[j].rt;
					temp[j].tat=g[i].end-temp[j].at;
				}
			}
		}
	}
	
	for(k=0;k<n;k++)
	{	
		for(i=0;i<n;i++)
		{
			if(!strcmp(temp[k].ppid,t[i].ppid))
			{
				t[i].rt=temp[k].rt;
				t[i].tat=temp[k].tat;
				t[i].wt=temp[k].wt;
			}
		}
	}
}
void schedule_priority_p(proces *t,int n)
{
	proces temp[n];
	int i,j,a=-1,b=0;
	for(i=0;i<n;i++)
	{
		if(t[i].at>a)
			a=t[i].at;
		t[i].wt=0;
		t[i].rt=-1;
		t[i].tat=0;
	}
	int k=0;
	for(i=0;i<=a;i++)
	{
		for(j=0;j<n;j++)
		{
			if(t[j].at==i)
			{
				temp[k]=t[j];
				k++;
				if(k>=n)
				break;
			}
		}
	}
	k=0;
	int max=temp[0].at;
	for(i=0;i<n;i++)
	{
		if(t[i].at>max)
		max=t[i].at;
		max+=t[i].bt;
	}
	a=0;
	proces temporary[n];
	j=0;
	proces idle,small,previous;
	strcpy(idle.ppid,"idle");
	idle.at=-1;
	idle.bt=-1;
	idle.pr=-1;
	int f=0;
	gantt g[100];
	int index,count=0,gun[100];
	j=0;
		for(i=0;i<n;i++)
		{
			if(temp[i].at<=a && temp[i].bt>0)
			{
				temporary[j]=temp[i];
				j++;
			}
		}
		if(j==0)
		{
			small=idle;
		}
		else
		{
			index=smallest_process(temporary,j);
			small=temporary[index];
		}
	
		printf("\t\t GANTT CHART\n\t");
	while(a<max)
	{
		
		if(strcmp(small.ppid,previous.ppid))
		{
			gun[count]=a;
			count++;
			printf(" : %d %s ",gun[count-1],small.ppid);
			g[f].start=gun[count-1];
			strcpy(g[f].ppid,small.ppid);
		}
		
		if(!strcmp(small.ppid,idle.ppid))
		{
			a++;
		}
		else
		{
			a++;
			temporary[index].bt--;
		}
		if(j!=0)
		{
			for(i=0;i<n;i++)
			{
				if(!strcmp(temporary[index].ppid,temp[i].ppid))
				{
					temp[i]=temporary[index];
				}
			}
		}
		previous=small;
		j=0;
		for(i=0;i<n;i++)
		{
			if(temp[i].at<=a && temp[i].bt>0)
			{
				temporary[j]=temp[i];
				j++;
			}
		}
		if(j==0)
		{
			small=idle;
		}
		else
		{
			index=smallest_process(temporary,j);
			small=temporary[index];
		}
		if(strcmp(small.ppid,previous.ppid))
		{
			gun[count]=a;
			printf("%d :",gun[count]);
			count++;
			g[f].end=gun[count-1];
			f++;
		}
	}
	printf("\n");

	for(i=0;i<f;i++)
	{
		for(j=0;j<n;j++)
		{
			if(!strcmp(temp[j].ppid,g[i].ppid))
			{
				if(temp[j].rt==-1)
				{
					temp[j].rt=g[i].start-temp[j].at;	
				}
				temp[j].tat=g[i].end-temp[j].at;
				
			}
		}
	}
	
	for(k=0;k<n;k++)
	{	
		for(i=0;i<n;i++)
		{
			if(!strcmp(temp[k].ppid,t[i].ppid))
			{
				t[i].rt=temp[k].rt;
				t[i].tat=temp[k].tat;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		t[i].wt=t[i].tat-t[i].bt;
	}

}
int smallest_process(proces *p,int n)
{
	int b=p[0].pr;
	int index=0;
	int i;
	for(i=0;i<n;i++)
	{
		if(p[i].pr<b)
		{
			b=p[i].pr;
			index=i;
		}
	}
	return index;
}

/*

gml29:Desktop cse29$ gcc -o k scheduling2.c
gml29:Desktop cse29$ ./k
 1.Priority_Non_preemtive 
 2.Priority_Preemtive
 3.EXIT

 Choice : 1
Enter the no. of proceses : 3


Enter proces 1
Enter proces id   : p1
Enter arrival time : 0
Enter burst time   : 3
Enter priority     : 3


Enter proces 2
Enter proces id   : p2
Enter arrival time : 2
Enter burst time   : 1
Enter priority     : 2


Enter proces 3
Enter proces id   : p3
Enter arrival time : 3
Enter burst time   : 5
Enter priority     : 1
		 GANTT CHART
	 : 0 p1 3 : : 3 p3 8 : : 8 p2 9 :
---------------------------------------------------------------------------------------------
proces ID	Arrival Time	Burst Time	TurnaroundTime	Waiting Time	Response Time
---------------------------------------------------------------------------------------------
p1                    0             3               3             0              0          
p2                    2             1               7             6              6          
p3                    3             5               5             0              0          
---------------------------------------------------------------------------------------------
                                       Average     5.000000       2.000000              2.000000
 1.Priority_Non_preemtive 
 2.Priority_Preemtive
 3.EXIT

 Choice : 2
Enter the no. of proceses : 3


Enter proces 1
Enter proces id   : p1
Enter arrival time : 0
Enter burst time   : 3
Enter priority     : 3


Enter proces 2
Enter proces id   : p2
Enter arrival time : 1
Enter burst time   : 5
Enter priority     : 2


Enter proces 3
Enter proces id   : p3
Enter arrival time : 2
Enter burst time   : 4
Enter priority     : 1
		 GANTT CHART
	 : 0 p1 1 : : 1 p2 2 : : 2 p3 6 : : 6 p2 10 : : 10 p1 12 :
---------------------------------------------------------------------------------------------
proces ID	Arrival Time	Burst Time	TurnaroundTime	Waiting Time	Response Time
---------------------------------------------------------------------------------------------
p1                    0             3               12             9              0          
p2                    1             5               9             4              0          
p3                    2             4               4             0              0          
---------------------------------------------------------------------------------------------
                                      Average      8.333333     4.333333              0.000000
 1.Priority_Non_preemtive 
 2.Priority_Preemtive
 3.EXIT

 Choice : 3
gml29:Desktop cse29$

*/