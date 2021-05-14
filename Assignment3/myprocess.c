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
typedef struct
{
	char ppid[100];
	int start,end;
}gantt; 
void input(proces *p,int n);
void schedule_fcfs(proces *p,int n);
void schedule_sjf_np(proces *p,int n);
void schedule_sjf_p(proces *p,int n);
void display(proces *p,int n);

int smallest_process(proces *p,int n);
void main()
{
	proces *p;
	int n;
	int ch=0;
	char cho;
	while(ch!=3)
	{
		printf(" 1.FCFS \n 2.SJF\n 3.EXIT\n\n Choice : ");
		scanf("%d",&ch);
		if(ch==1)
		{
			printf("Enter the no. of proceses : ");
			scanf("%d",&n);
			p=(proces*)malloc(sizeof(proces)*n);
			input(p,n);
			schedule_fcfs(p,n);
			display(p,n);
			free(p);
		}
		else if(ch==2)
		{
			printf("\ta.Non-preemtive \n\tb.Preemtive\n\tChoice : ");
			scanf(" %c",&cho);
			if(cho=='a')
			{
				printf("Enter the no. of proceses : ");
				scanf("%d",&n);
				p=(proces*)malloc(sizeof(proces)*n);
				input(p,n);
				schedule_sjf_np(p,n);
				display(p,n);
				free(p);
			}
			else if(cho=='b')
			{
				printf("Enter the no. of proceses : ");
				scanf("%d",&n);
				p=(proces*)malloc(sizeof(proces)*n);
				input(p,n);
				schedule_sjf_p(p,n);
				display(p,n);
				free(p);
			}
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
	}
}
void schedule_fcfs(proces *t,int n)
{
	proces p[n];
	int i,j,a=-1;
	for(i=0;i<n;i++)
	{
		if(t[i].at>a)
			a=t[i].at;
	}
	int k=0;
	proces *temp;
	for(i=0;i<=a;i++)
	{
		for(j=0;j<n;j++)
		{
			if(t[j].at==i)
			{
				p[k]=t[j];
				k++;
				if(k>=n)
				break;
			}
		}
	}
	int gun[20];
	k=0;
	gun[k]=p[0].at;
	k++;
	for(i=0;i<n;i++)
	{
		if(gun[k-1]>=p[i].at)
		{
			gun[k]=p[i].bt+gun[k-1];
			k++;
		}
		else
		{
			gun[k]=p[i].at;
			k++;
			gun[k]=p[i].bt+gun[k-1];
			k++;
		}
		p[i].wt=gun[k-2]-p[i].at;
		if(p[i].wt<0)
		p[i].wt=0;
		p[i].tat=gun[k-1]-p[i].at;
		p[i].rt=p[i].wt;
		for(j=0;j<n;j++)
		{
			if(!strcmp(p[i].ppid,t[j].ppid))
			{
				t[j]=p[i];
			}
		}	
	}
	printf("\n\n          \t GANTT CHART\n\n\t : ");
	k=0;
	for(i=0;i<n;i++)
	{
		if(gun[k]>=p[i].at)
		{
			printf("%d %s %d : ",gun[k],p[i].ppid,gun[k+1]);
			k++;
		}
		else
		{
			printf("%d idle %d : ",gun[k],gun[k+1]);
			k++;
			i-=1;
		}
	}
	printf("\n\n");
}
void schedule_sjf_np(proces *t,int n)
{
	proces p[n],*temp;
	int i,j,k=0,m=0,flag[n];
	int a=0,b=0;
	char f[10];
	for(i=0;i<n;i++)
	{
		flag[i]=0;
		if(t[i].bt>b)
		b=t[i].bt;
	}
	while(k<n)
	{
		printf("a: %d\n",a);
		temp=(proces*)malloc(sizeof(proces)*n);
		for(i=0;i<n;i++)
		{
			if(t[i].at<=a && flag[i]==0)
			{

				temp[m]=t[i];
				m++;
			}
		}
		if(m==0)
		a++;
		for(j=0;j<=b;j++)
		{
			for(i=0;i<m;i++)
			{
				if(temp[i].bt==j)
				{
					p[k]=temp[i];
					k++;
					strcpy(f,temp[i].ppid);
					a+=temp[i].bt;
					goto loop;
				}
			}
		}
		loop:
		m=0;
		free(temp);
		for(i=0;i<n;i++)
		{
			if(!strcmp(f,t[i].ppid))
			{
				flag[i]=1;
			}
		}
	}

	int gun[20];
	k=0;
	gun[k]=p[0].at;
	k++;
	for(i=0;i<n;i++)
	{
		if(gun[k-1]>=p[i].at)
		{
			gun[k]=p[i].bt+gun[k-1];
			k++;
		}
		else
		{
			gun[k]=p[i].at;
			k++;
			gun[k]=p[i].bt+gun[k-1];
			k++;
		}
		p[i].wt=gun[k-2]-p[i].at;
		if(p[i].wt<0)
		p[i].wt=0;
		p[i].tat=gun[k-1]-p[i].at;
		p[i].rt=p[i].wt;
		for(j=0;j<n;j++)
		{
			if(!strcmp(p[i].ppid,t[j].ppid))
			{
				t[j]=p[i];
			}
		}	
	}
	printf("\n\n          \t GANTT CHART\n\n\t : ");
	k=0;
	for(i=0;i<n;i++)
	{
		if(gun[k]>=p[i].at)
		{
			printf("%d %s %d : ",gun[k],p[i].ppid,gun[k+1]);
			k++;
		}
		else
		{
			printf("%d idle %d : ",gun[k],gun[k+1]);
			k++;
			i-=1;
		}
	}
	printf("\n\n");
}
void schedule_sjf_p(proces *t,int n)
{
	proces p[n];
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
	proces temp[n];
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
	int gun[100],count=0,stop=0,index;
	a=0;
	proces temporary[n],small,previous;
	j=0;
	proces idle;
	strcpy(idle.ppid,"idle");
	idle.at=-1;
	idle.bt=-1;
	int f=0;
	gantt g[100]; 
	printf("\t\t GANTT CHART\n\t");
	while(a<max)
	{
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
		gun[count]=a;
		count++;
		if(strcmp(previous.ppid,small.ppid))
		{
			printf(" : %d %s ",gun[count-1],small.ppid);
			strcpy(g[f].ppid,small.ppid);
			g[f].start=gun[count-1];
		}
		a++;
		previous=small;
				
		if(j!=0)
		{
			temporary[index].bt--;
			for(k=0;k<j;k++)
			{	
				for(i=0;i<n;i++)
				{
					if(!strcmp(temporary[k].ppid,temp[i].ppid))
					{
						temp[i]=temporary[k];
					}
				}
			}
			for(i=0;i<n;i++)
			{
				if(strcmp(temp[i].ppid,small.ppid))
				temp[i].wt++;
				else if(temporary[index].bt==0)
				{
					temp[i].tat=a-temp[i].at;
				}
			}
		}
		j=0;
		b=temp[0].bt;
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
		gun[count]=a;
		count++;
		if(strcmp(previous.ppid,small.ppid))
		{
			printf("%d :",gun[count-1]);
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
	int b=p[0].bt;
	int index=0;
	int i;
	for(i=0;i<n;i++)
	{
		if(p[i].bt<b)
		{
			b=p[i].bt;
			index=i;
		}
	}
	return index;
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
	
		
			
/*

PS F:\SEM4\OS\Assignment3> gcc -o a myprocess.c
PS F:\SEM4\OS\Assignment3> ./a
 1.FCFS
 2.SJF
 3.EXIT

 Choice : 2
        a.Non-preemtive
        b.Preemtive
        Choice : b
Enter the no. of proceses : 5


Enter proces 1
Enter proces id   : p1
Enter arrival time : 0
Enter burst time   : 8


Enter proces 2
Enter proces id   : p2
Enter arrival time : 1
Enter burst time   : 6


Enter proces 3
Enter proces id   : p3
Enter arrival time : 2
Enter burst time   : 1


Enter proces 4
Enter proces id   : p4
Enter arrival time : 3
Enter burst time   : 9


Enter proces 5
Enter proces id   : p5
Enter arrival time : 4
Enter burst time   : 3
                 GANTT CHART
         : 0 p1 1 : : 1 p2 2 : : 2 p3 3 : : 3 p2 4 : : 4 p5 7 : : 7 p2 11 : : 11 p1 18 : : 18 p4 27 :
---------------------------------------------------------------------------------------------
proces ID       Arrival Time    Burst Time      TurnaroundTime  Waiting Time    Response Time
---------------------------------------------------------------------------------------------
p1                    0             8               18             10              0
p2                    1             6               10             4              0
p3                    2             1               1             0              0
p4                    3             9               24             15              15
p5                    4             3               3             0              0
---------------------------------------------------------------------------------------------
                                                  Average        5.800000              3.000000
 1.FCFS
 2.SJF
 3.EXIT

 Choice : 3
PS F:\SEM4\OS\Assignment3> ./a
 1.FCFS
 2.SJF
 3.EXIT

 Choice : 2
        a.Non-preemtive
        b.Preemtive
        Choice : b
Enter the no. of proceses : 7


Enter proces 1
Enter proces id   : p1
Enter arrival time : 2
Enter burst time   : 3


Enter proces 2
Enter proces id   : p2
Enter arrival time : 4
Enter burst time   : 2


Enter proces 3
Enter proces id   : p3
Enter arrival time : 5
Enter burst time   : 1


Enter proces 4
Enter proces id   : p4
Enter arrival time : 7
Enter burst time   : 4


Enter proces 5
Enter proces id   : p5
Enter arrival time : 9
Enter burst time   : 2


Enter proces 6
Enter proces id   : p6
Enter arrival time : 15
Enter burst time   : 6


Enter proces 7
Enter proces id   : p7
Enter arrival time : 16
Enter burst time   : 8
                 GANTT CHART
         : 0 idle 2 : : 2 p1 5 : : 5 p3 6 : : 6 p2 8 : : 8 p4 9 : : 9 p5 11 : : 11 p4 14 : : 14 idle 15 : : 15 p6 21 : : 21 p7 29 :
---------------------------------------------------------------------------------------------
proces ID       Arrival Time    Burst Time      TurnaroundTime  Waiting Time    Response Time
---------------------------------------------------------------------------------------------
p1                    2             3               3             0              0
p2                    4             2               4             2              2
p3                    5             1               1             0              0
p4                    7             4               7             3              1
p5                    9             2               2             0              0
p6                    15             6               6             0              0
p7                    16             8               13             5              5
---------------------------------------------------------------------------------------------
                                                  Average        1.428571              1.142857
 1.FCFS
 2.SJF
 3.EXIT

 Choice : 2
        a.Non-preemtive
        b.Preemtive
        Choice : a
Enter the no. of proceses : 7


Enter proces 1
Enter proces id   : p1
Enter arrival time : 2
Enter burst time   : 3


Enter proces 2
Enter proces id   : p2
Enter arrival time : 4
Enter burst time   : 2


Enter proces 3
Enter proces id   : p3
Enter arrival time : 5
Enter burst time   : 1


Enter proces 4
Enter proces id   : p4
Enter arrival time : 7
Enter burst time   : 4


Enter proces 5
Enter proces id   : p5
Enter arrival time : 9
Enter burst time   : 2


Enter proces 6
Enter proces id   : p6
Enter arrival time : 15
Enter burst time   : 6


Enter proces 7
Enter proces id   : p7
Enter arrival time : 16
Enter burst time   : 8
a: 0
a: 1
a: 2
a: 5
a: 6
a: 8
a: 12
a: 14
a: 15
a: 21


                 GANTT CHART

         : 2 p1 5 : 5 p3 6 : 6 p2 8 : 8 p4 12 : 12 p5 14 : 14 idle 15 : 15 p6 21 : 21 p7 29 :

---------------------------------------------------------------------------------------------
proces ID       Arrival Time    Burst Time      TurnaroundTime  Waiting Time    Response Time
---------------------------------------------------------------------------------------------
p1                    2             3               3             0              0
p2                    4             2               4             2              2
p3                    5             1               1             0              0
p4                    7             4               5             1              1
p5                    9             2               5             3              3
p6                    15             6               6             0              0
p7                    16             8               13             5              5
---------------------------------------------------------------------------------------------
                                                  Average        1.571429              1.571429
 1.FCFS
 2.SJF
 3.EXIT

 Choice : 1
Enter the no. of proceses : 7


Enter proces 1
Enter proces id   : p1
Enter arrival time : 2
Enter burst time   : 3


Enter proces 2
Enter proces id   : p2
Enter arrival time : 4
Enter burst time   : 2


Enter proces 3
Enter proces id   : p3
Enter arrival time : 5
Enter burst time   : 1


Enter proces 4
Enter proces id   : p4
Enter arrival time : 7
Enter burst time   : 4


Enter proces 5
Enter proces id   : p5
Enter arrival time : 9
Enter burst time   : 2


Enter proces 6
Enter proces id   : p6
Enter arrival time : 15
Enter burst time   : 6


Enter proces 7
Enter proces id   : p7
Enter arrival time : 16
Enter burst time   : 8


                 GANTT CHART

         : 2 p1 5 : 5 p2 7 : 7 p3 8 : 8 p4 12 : 12 p5 14 : 14 idle 15 : 15 p6 21 : 21 p7 29 :

---------------------------------------------------------------------------------------------
proces ID       Arrival Time    Burst Time      TurnaroundTime  Waiting Time    Response Time
---------------------------------------------------------------------------------------------
p1                    2             3               3             0              0
p2                    4             2               3             1              1
p3                    5             1               3             2              2
p4                    7             4               5             1              1
p5                    9             2               5             3              3
p6                    15             6               6             0              0
p7                    16             8               13             5              5
---------------------------------------------------------------------------------------------
                                                  Average        1.714286              1.714286
 1.FCFS
 2.SJF
 3.EXIT

 Choice : 3
PS F:\SEM4\OS\Assignment3>

*/