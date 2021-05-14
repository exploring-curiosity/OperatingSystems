#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char pid[10];
	int alloc[10];
	int need[10];
	int max[10];	
}pro;

typedef struct
{
	pro *p;
	int n;
	int m;
	int avail[10];
	char r[10];
	int req[10];
}process;



process* initialize(process *p1,int n, int m)
{
	p1->p=(pro*)malloc(sizeof(pro)*n);
	p1->n=n;
	p1->m=m;
	return p1;
}

void input(process *p1)
{
	int i,j;
	printf("Enter Process\n");
	strcpy(p1->p[0].pid,"p0");
	strcpy(p1->p[1].pid,"p1");
	strcpy(p1->p[2].pid,"p2");
	strcpy(p1->p[3].pid,"p3");
	strcpy(p1->p[4].pid,"p4");
	
	p1->p[0].max[0]=7;
	p1->p[0].max[1]=5;
	p1->p[0].max[2]=3;
	p1->p[1].max[0]=3;
	p1->p[1].max[1]=2;
	p1->p[1].max[2]=2;
	p1->p[2].max[0]=9;
	p1->p[2].max[1]=0;
	p1->p[2].max[2]=2;
	p1->p[3].max[0]=2;
	p1->p[3].max[1]=2;
	p1->p[3].max[2]=2;
	p1->p[4].max[0]=4;
	p1->p[4].max[1]=3;
	p1->p[4].max[2]=3;
	
	
	
	p1->p[0].alloc[0]=0;
	p1->p[0].alloc[1]=1;
	p1->p[0].alloc[2]=0;
	p1->p[1].alloc[0]=2;
	p1->p[1].alloc[1]=0;
	p1->p[1].alloc[2]=0;
	p1->p[2].alloc[0]=3;
	p1->p[2].alloc[1]=0;
	p1->p[2].alloc[2]=2;
	p1->p[3].alloc[0]=2;
	p1->p[3].alloc[1]=1;
	p1->p[3].alloc[2]=1;
	p1->p[4].alloc[0]=0;
	p1->p[4].alloc[1]=0;
	p1->p[4].alloc[2]=2;

	strcpy(p1->r,"p1");
	for(i=0;i<p1->n;i++)
	{
		for(j=0;j<p1->m;j++)
		{
			p1->p[i].need[j]=p1->p[i].max[j]-p1->p[i].alloc[j];
		}
	}

	p1->avail[0]=3;
	p1->avail[1]=3;
	p1->avail[2]=2;

	p1->req[0]=1;
	p1->req[1]=0;
	p1->req[2]=2;

	
	/*printf("Enter available :");
	for(j=0;j<p1->m;j++)
	{
		scanf("%d",&p1->avail[j]);
	}*/

	/*printf("Process Requesting : ");
	scanf("%s",p1->r);
	
	printf("%s's Request : ",p1->r);
	for(j=0;j<p1->m;j++)
	{
		scanf("%d",&p1->req[j]);
	}*/
	
}


void output(process *p1)
{
	printf("Proc\t Max\t    Alloc\t Need\n");
	int i,j;
	for(i=0;i<p1->n;i++)
	{
		printf("\n%s\t",p1->p[i].pid);
		for(j=0;j<p1->m;j++)
		{
			printf("%d  ",p1->p[i].max[j]);
		}
		printf("   ");
		for(j=0;j<p1->m;j++)
		{
			printf("%d  ",p1->p[i].alloc[j]);
		}
		printf("   ");
		for(j=0;j<p1->m;j++)
		{
			printf("%d  ",p1->p[i].need[j]);
		}
	}
}


int banker(process *p1)
{
	int comp[p1->n];
	int no,count=0;
	int i,j,temp=0;
	for(i=0;i<p1->n;i++)
	{
		comp[i]=0;
	}
	no=0;
	i=0;
	int flag;
	char a[p1->n][10];
	while(no!=p1->n && count<3*p1->n)
	{
		flag=0;
		for(j=0;j<p1->m;j++)
		{
			if(p1->p[i].need[j]>p1->avail[j])
			{
				flag++;
				break;
			}
		}
		
			
		if(flag==0  && comp[i]!=1)
		{
			for(j=0;j<p1->m;j++)
				p1->avail[j]+=p1->p[i].alloc[j];
		
			comp[i]=1;
			strcpy(a[temp],p1->p[i].pid);
			temp++;	
			no++;
		}
				
		i=(i+1)%p1->n;	
		count++;
	}
	if(no==p1->n)
	{
		printf("Safe sequence is : ");
		for(i=0;i<p1->n;i++)
			printf("%s ",a[i]);
		printf("\n");
		return 1;
	}
	else
		printf("The system is not in safe state\n");	
		return 0;
}


void request(process *p1)
{
	int i,j,flag=0;
	for(i=0;i<p1->n;i++)
	{
		if(strcmp(p1->r,p1->p[i].pid)==0)
			break;
	}
	int index=i;
	for(j=0;j<p1->m;j++)
	{
		if(p1->p[index].need[j]<p1->req[j])
		{
			printf("Process exceeds maximum claim\n");
			flag=1;
			break;
		}
	}

	for(j=0;j<p1->m;j++)
	{
		if(p1->avail[j]<p1->req[j] && flag==0)
		{
			printf("Resources are not available. %s should wait\n",p1->p[index].pid);
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		for(j=0;j<p1->m;j++)
		{
			p1->avail[j]-=p1->req[j];
			p1->p[index].alloc[j]+=p1->req[j];
			p1->p[index].need[j]-=p1->req[j];
			
		}
		
		int res=banker(p1);
		if(res==1)
		{
			printf("The %s request can be granted immediately\n",p1->p[index].pid);
		}
		else
			printf("The %s request can not be granted immediately\n",p1->p[index].pid);
	}
}



void main()
{	
	process *p1;
	int ch=1;
	while(ch!=4)
	{
		printf("\n1.Read data\n2.Print Data\n3.Safety Sequence\n4.Exit\n");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
			{
				int n=5,m=3;
			
				p1=initialize(p1,n,m);
				input(p1);
				break;
			}
			case 2:
			{
				output(p1);
				break;
			}
			case 3:
			{
				request(p1);
				break;
			}
			case 4:
			{
				printf("Thank You\n");
				break;
			}
			default:
				printf("Invalid input\n");
		}	
	}	
}
