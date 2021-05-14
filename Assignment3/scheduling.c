
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct SJF
{
	char pid[2];
	int at;
	int bt;
	int tt;
	int wt;
	int rt;
	int flag;
	
}sjf;


void sjf_nonpreemptive(sjf *p[20],int n);
void fcfs_scheduling(sjf *p[20],int n);


void main()
{
	sjf *p[20];
	int ch,n,i;
	

	for(i=0;i<20;i++)
	{
	
		p[i]=(sjf*)malloc(sizeof(sjf));
		p[i]->flag=0;
	}


	printf("MENU\n");
	printf("1.FCFS\n");
	printf("2.SJF\n");
	printf("Enter choice:");
	scanf("%d",&ch);

	

	printf("\nEnter the no. of processes:");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		printf("\nEnter Process ID:");
		scanf("%s",p[i]->pid);
		printf("Enter arrival time:");
		scanf("%d",&p[i]->at);
		printf("Enter burst time:");
		scanf("%d",&p[i]->bt);

		p[i]->rt=0;
		p[i]->tt=0;
		p[i]->wt=0;

	}
		
	
	switch(ch)
	{
		case 1:fcfs_scheduling(p,n);
				break;
		case 2:sjf_nonpreemptive(p,n);
				break;
	}	

}

sjf* shortest_at(sjf *p[20],int n)
{
	
	int i,j;
	sjf *temp;
	sjf *p1[20];
	for(i=0;i<n;i++)
	{
		p1[i]=p[i];
	}

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p1[i]->at>p1[j]->at)
			{
				temp=p1[i];
				p1[i]=p1[j];
				p1[j]=temp;
			}
		}
	}
	i=0;
	while(p1[i]->flag!=0)
	{
		i++;
	}

	return p1[i];
}

int remaining_process(sjf *p[20],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(p[i]->flag==0)
			return 1;
	}
	return 0;
}
void printChart(sjf *p[20],int n)
{
	
	int i,t;
	int time=0,total_time=0;

	for(i=0;i<n;i++)
	{
	
		p[i]->flag=0;
		
	}
	printf("--------------------------------------------------------\n");
	for(i=0;remaining_process(p,n)!=0;i++)
	{
		
		if(time<p[i]->at)
		{
			printf("   %s    ","idle");
			t=(p[i]->at-time);
			time+=t;
			continue;
		}
			
		printf("   %s    ",p[i]->pid);
		time+=p[i]->bt;
		p[i]->flag=1;
	} 
	printf("\n");
	printf("--------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
	
		p[i]->flag=0;
		
	}
	time=0;

	for(i=0;remaining_process(p,n)!=0;i++)
	{
		if(time<p[i]->at)
		{
			t=(p[i]->at-time);
			time+=t;
		}
		printf("%d       ",time);
		time+=p[i]->bt;
		p[i]->flag=1;
	}  
	printf("%d",time);
}

void wait_time(sjf *p[20],int n)
{
	int i,time=0,t;

	for(i=0;i<n;i++)
	{
	
		p[i]->flag=0;
		
	}

	for(i=0;remaining_process(p,n)!=0;i++)
	{
		p[i]->wt=time-p[i]->at;
		if(time<p[i]->at)
		{
			t=(p[i]->at-time);
			time+=t;
		}
		
		time+=p[i]->bt;
		p[i]->flag=1;
	}  
}

void turaround_time(sjf *p[20],int n)
{
	int i,time=0;

	for(i=0;i<n;i++)
	{
		p[i]->tt=p[i]->wt+p[i]->bt;
	} 

}

void response_time(sjf *p[20],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		p[i]->rt=p[i]->wt;
	}
}
void print_Table(sjf *p[20],int n)
{

	int i;
	float avg_wt=0,avg_rt=0,avg_tt=0;

	
	wait_time(p,n);
	turaround_time(p,n);
	response_time(p,n);


	printf("\n\n---------------------------------------------------------------------------------------------\n");
	printf("Process ID	Arrival Time  Burst Time   TurnaroundTime   Waiting Time   Response Time\n");
	printf("---------------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("%-11s%14d%13d%17d%15d%13d\n",p[i]->pid,p[i]->at,p[i]->bt,p[i]->tt,p[i]->wt,p[i]->rt);         
		avg_wt+=p[i]->wt;
		avg_rt+=p[i]->rt;
		avg_tt+=p[i]->tt;	
	}
	avg_wt/=n;
	avg_rt/=n;
	avg_tt/=n;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("                              Average            %.2f              %.2f          %.2f\n",avg_tt,avg_wt,avg_rt);
}

void fcfs_scheduling(sjf *p[20],int n)
{
	int i,j;
	sjf *temp;

	printf("FCFS SCHEDULING\n");
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p[i]->at>p[j]->at)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}

	int bTime,aTime;

	for(i=0,j=1;i<n-1;i++,j++)
	{
		aTime = p[i]->at;
		bTime = p[i]->bt;
		
		if(aTime == p[j]->at && bTime > p[j]->bt)
		{	
			temp=p[j];
			p[j]=p[i];
			p[i]=temp;
		}
	}

	printChart(p,n);
	print_Table(p,n);

}

void sjf_nonpreemptive(sjf *p[20],int n)
{
		
	int time=0,j=0,i,k,t;
	sjf *ptr[20];


	sjf *temp;

	printf("SJF NON PREEMPTIVE SCHEDULING\n");

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p[i]->bt>p[j]->bt)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}
	
	for(i=0;i<20;i++)
	{
	
		ptr[i]=(sjf*)malloc(sizeof(sjf));
		ptr[i]->flag=0;
		
	}

	j=0;
	
	
	
	for(i=0;remaining_process(p,n)!=0;)
	{
		
		if(time<p[i]->at)
		{	
			
			ptr[j]=shortest_at(p,n);
			
			
			for(k=0;k<n;k++)
			{
				if(strcmp(ptr[j]->pid,p[k]->pid)==0)
				{
					p[k]->flag=1;
					break;
				}
			}

			time+=ptr[j]->bt;

			if(time<ptr[j]->at)
			{
				t=(ptr[j]->at-time);
				time+=t;
			
			}
				
				
			j++;
		}
			
		else 
		{
		
			if(p[i]->flag==0)
			{
				
				ptr[j++]=p[i];
				p[i]->flag=1;
				time+=p[i]->bt;
				
			}
			i++;
		}
	}
		
	printChart(ptr,n);
	print_Table(ptr,n);
		
	
	
}
	
				
/*
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A3>gcc -o a scheduling.c

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A3>a
MENU
1.FCFS
2.SJF
Enter choice:1

Enter the no. of processes:5

Enter Process ID:p1
Enter arrival time:0
Enter burst time:8

Enter Process ID:p2
Enter arrival time:1
Enter burst time:6

Enter Process ID:p3
Enter arrival time:2
Enter burst time:1

Enter Process ID:p4
Enter arrival time:3
Enter burst time:9

Enter Process ID:p5
Enter arrival time:4
Enter burst time:3
FCFS SCHEDULING
--------------------------------------------------------
   p1       p2       p3       p4       p5
--------------------------------------------------------
0       8       14       15       24       27

---------------------------------------------------------------------------------------------
Process ID      Arrival Time  Burst Time   TurnaroundTime   Waiting Time   Response Time
---------------------------------------------------------------------------------------------
p1                      0            8                8              0            0
p2                      1            6               13              7            7
p3                      2            1               13             12           12
p4                      3            9               21             12           12
p5                      4            3               23             20           20
---------------------------------------------------------------------------------------------
                              Average            15.60              10.20          10.20


MENU
1->FCFS
2->SJF
Enter choice:2

Enter the no-> of processes:5

Enter Process ID:p1
Enter arrival time:0
Enter burst time:8

Enter Process ID:p2
Enter arrival time:1
Enter burst time:6

Enter Process ID:p3
Enter arrival time:2
Enter burst time:1

Enter Process ID:p4
Enter arrival time:3
Enter burst time:8

Enter Process ID:p5
Enter arrival time:4
Enter burst time:3
SJF NON PREEMPTIVE SCHEDULING
--------------------------------------------------------
   p1       p3       p5       p2       p4
--------------------------------------------------------
0       8       9       12       18       26

---------------------------------------------------------------------------------------------
Process ID      Arrival Time  Burst Time   TurnaroundTime   Waiting Time   Response Time
---------------------------------------------------------------------------------------------
p1                      0            8                8              0            0
p3                      2            1                7              6            6
p5                      4            3                8              5            5
p2                      1            6               17             11           11
p4                      3            8               23             15           15
---------------------------------------------------------------------------------------------
                              Average            12->60              7->40          7->40

*/







