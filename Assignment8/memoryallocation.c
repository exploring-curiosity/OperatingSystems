#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure to sstore the details of a process represented as a node in the list

typedef struct 
{
	int start,end;
	char id[5];
}proc;

//structure to store the linked list
typedef struct node node;
struct node
{
	proc p;
	node *left,*right;  
};

//structure to store the linked list
typedef struct 
{
	int size;
	node *head,*tail;
}ll;


//initialise the head and tail of the linked list
void initialise(ll *l);
//insert a node into a list at the end
void insert_into_ll(ll *l,proc t);
//insert a node in the list according to its startinf and ending address
void insert_at_pos(ll *l,proc t);
//delete a node from the list given its process id
node * delete_node(ll *l,char id[5]);
//display the alloted linked list according to the addresses that are alloted to a process
void display_l(ll *l);
//display the physical mem
void display_pl(ll *al,ll *fl);
//display function calls all the other display functions
void display(ll *alloted,ll *freehole);
//given the node address delete it from the list
node * delete_address(ll *l,node *add);
//find the hole that best fits the needed size of memory for the process
node * find_best(ll *l,int len);
//find the hole that is largest in the list of holes and return its address
node * find_worst(ll *l);
//allocate the hole to the process accoring to the algorithm chosen by the user
void allocate(ll *allot,ll *freehole,char id[5],int len,int option);
//Deallocate the memory of the process 
void deallocate(ll *allot,ll *freehole,char id[5]);
//merge all the holes which are adjascent to each other
void coalescing(ll *freehole);



void main()
{
	int part,option,choice,len;
	char id[5];
	proc pt;
	ll *alloted,*freehole;
	alloted=(ll *)malloc(sizeof(ll));
	freehole=(ll *)malloc(sizeof(ll));
	initialise(alloted);
	initialise(freehole);
	printf("\nPROGRAM TO IMPLEMENT MEMORY ALLOCATION TECHNIQUES:\n");
	printf("\nEnter the memory representation:");
	printf("\nEnter the no of partitions:");
	scanf("%d",&part);
	for (int i = 0; i < part; ++i)
	{
		strcpy(pt.id,"hole");
		printf("starting and ending address of partition %d :",i+1);
		scanf("%d%d",&pt.start,&pt.end);
		insert_into_ll(freehole,pt);
	}
	display(alloted,freehole);
	A:
	printf("\n\nMemory Allocation Algorithm:\n1.First Fit\n2.Best Fit\n3.Worst Fit\n4.Exit from the program\nEnter choice:");
	scanf("%d",&option);
	if(option!=4)
	{
		choice=1;
		switch (option)
		{
			case 1: printf("\nFirst Fit Memory allocation Algorithm\n");break;
			case 2: printf("\nBest Fit Memory allocation Algorithm\n");break;
			case 3: printf("\nWorst Fit Memory allocation Algorithm\n");break;
			default:goto A;
		}
		while(choice!=0)
		{
			printf("\n1.Entry/Allocate\n2.Exit/Deallocate\n3.Display\n4.Coalescing of Holes\n5.Back to algorithm\n0.exit\nEnter choice:");
			scanf("%d",&choice);
			switch (choice)
			{
				case 1:
					printf("\nEnter process id:");
					scanf("%s",id);
					printf("Enter the size needed:");
					scanf("%d",&len);
					allocate(alloted,freehole,id,len,option);
					break;
				case 2:
					printf("\nEnter process id:");
					scanf("%s",id);
					deallocate(alloted,freehole,id);
					break;
				case 3:
					display(alloted,freehole);
					break;
				case 4:
					coalescing(freehole);
					break;
				case 5:
					goto A;
					break;
				case 0:
					break;
				default:printf("invalid option\n");
			}
		}
	}
	printf("exiting...\n");
}


//initialise the head and tail of the linked list
void initialise(ll *l)
{
	l->head=(node *)malloc(sizeof(node));
	l->tail=(node *)malloc(sizeof(node));
	l->head->left=NULL;
	l->tail->right=NULL;
	l->head->right=l->tail;
	l->tail->left=l->head;
	l->size=0;
}

//insert a node into a list at the end
void insert_into_ll(ll *l,proc t)
{
	node *temp=(node *)malloc(sizeof(node));
	temp->p=t;
	temp->left=l->tail->left;
	temp->right=l->tail;
	l->tail->left=temp;
	temp->left->right=temp;
	l->size++;
}

//insert a node in the list according to its startinf and ending address
void insert_at_pos(ll *l,proc t)
{
	node *temp=(node *)malloc(sizeof(node));
	temp->p=t;
	node *point=l->head->right,*prev=l->head;
	//search for exact position
	while((point->p.start<t.end) && (point->right!=NULL))
	{
		prev=point;
		point=point->right;
	}
	temp->right=prev->right;
	point->left=temp;
	temp->left=prev;
	prev->right=temp;
	l->size++;
}

//delete a node from the list given its process id
node * delete_node(ll *l,char id[5])
{
	node *temp,*prev;
	temp=l->head->right;
	prev=l->head;
	while(temp->right!=NULL)
	{
		//find the node
		if(strcmp(temp->p.id,id)==0)
		{
			prev->right=temp->right;
			temp->right->left=prev;
			l->size--;
			return temp;
		}
		prev=temp;
		temp=temp->right;
	}
	return NULL;
}

//display the linked list
void display_fl(ll *l)
{
	node *temp;
	if(l->head->right==l->tail)
	{
		printf("----->NULL\n");
		return;
	}
	temp=l->head->right;
	for(int i=0;i<l->size;i++)printf("---------");printf("\n");
	printf("|");
	while(temp->right!=NULL)
	{
		printf("%-8s|",temp->p.id);
		temp=temp->right;
		
	}
	printf("\n");
	for(int i=0;i<l->size;i++)printf("---------");printf("\n");
	temp=l->head->right;
	while(temp->right!=NULL)
	{
		printf("%-9d",temp->p.start);
		temp=temp->right;
	}
	printf("%d\n",temp->left->p.end);

}


//display the alloted linked list according to the addresses that are alloted to a process
void display_l(ll *l)
{
	node *temp;
	if(l->head->right==l->tail)
	{
		printf("----->NULL\n");
		return;
	}
	temp=l->head->right;
	for(int i=0;i<l->size;i++)printf("---------");printf("\n");
	printf("|");
	while(temp->right!=NULL)
	{
		printf("%-8s|",temp->p.id);
		if(temp->right!=l->tail)
		{
			if(temp->p.end!=temp->right->p.start)printf("________|");
		}
		temp=temp->right;
	}
	printf("\n");
	for(int i=0;i<l->size;i++)printf("---------");printf("\n");
	temp=l->head->right;
	while(temp->right!=NULL)
	{
		printf("%-9d",temp->p.start);
		
		if((temp->right==l->tail) || (temp->p.end!=temp->right->p.start))
		{
			printf("%-9d",temp->p.end);
		}
		temp=temp->right;
	}
	printf("\n");

}

//display the physical memory by merging the alloted and the free memory
void display_pl(ll *al,ll *fl)
{
	if((al->head->right==al->tail) && (fl->head->right==fl->tail))
	{	printf("--------->NULL\n");return;	}
	node *at,*ft;
	at=al->head->right;
	ft=fl->head->right;
	for(int i=0;i<al->size +fl->size;i++)printf("---------");printf("\n");
	printf("|");
	while((at->right!=NULL) && (ft->right!=NULL))
	{
		if(at->p.start<ft->p.start)
		{	printf("%-8s|",at->p.id);
			at=at->right;	}
		else
		{	printf("%-8s|",ft->p.id);
			ft=ft->right;	}
	}
	if(at->right==NULL)
	{	while(ft->right!=NULL)
		{
			printf("%-8s|",ft->p.id);
			ft=ft->right;
		}
	}
	else if(ft->right==NULL)
	{
		while(at->right!=NULL)
		{
			printf("%-8s|",at->p.id);
			at=at->right;
		}
	}
	printf("\n");
	for(int i=0;i<al->size + fl->size;i++)printf("---------");printf("\n");
	at=al->head->right;
	ft=fl->head->right;
	while((at->right!=NULL) && (ft->right!=NULL))
	{
		if(at->p.start<ft->p.start)
		{
			printf("%-9d",at->p.start);
			at=at->right;
		}
		else
		{
			printf("%-9d",ft->p.start);
			ft=ft->right;
		}
	}
	if(at->right==NULL)
	{
		while(ft->right!=NULL)
		{
			printf("%-9d",ft->p.start);
			ft=ft->right;
		}printf("%d\n",ft->left->p.end);
	}
	else if(ft->right==NULL)
	{
		while(at->right!=NULL)
		{
			printf("%-8d",at->p.start);
			at=at->right;
		}printf("%d\n",at->left->p.end);
	}
}

//call the other display the function
void display(ll *alloted,ll *freehole)
{
	printf("\nalloted memory:\n");
	display_l(alloted);
	printf("\nfree pool:\n");
	display_l(freehole);
	printf("\nphysical memory:\n");
	display_pl(alloted,freehole);
}

//delete the node in the list given the address
node * delete_address(ll *l,node *add)
{
	node *temp,*prev;
	temp=l->head->right;
	prev=l->head;
	while(temp->right!=NULL)
	{
		//find the address
		if(temp==add)
		{
			prev->right=temp->right;
			temp->right->left=prev;
			l->size--;
			return temp;
		}
		prev=temp;
		temp=temp->right;
	}
	return NULL;
}

//find the hole that best fits the requirement
node * find_best(ll *l,int len)
{
	node *temp,*best=NULL;int len1,blen=999;
	temp=l->head->right;
	while(temp!=l->tail)
	{
		len1=temp->p.end-temp->p.start;
		if((len1>=len) && (len1<blen))
		{
			blen=len1;
			best=temp;
		}
		temp=temp->right;
	}
	if(best==NULL)printf("There is no best fit hole found\n");
	return best;
}

//find the hole that is the largest
node * find_worst(ll *l)
{
	node *temp,*worst=NULL;
	int wlen=0,len1;
	temp=l->head->right;
	while(temp!=l->tail)
	{
		len1=temp->p.end-temp->p.start;
		if(len1>wlen)
		{
			worst=temp;
			wlen=len1;
		}
		temp=temp->right;
	}
	if(worst==NULL) printf("There is no worst fit hole found\n");
	return worst;
}

//allocate the hole selescted according to the algorithm to the process
void allocate(ll *allot,ll *freehole,char id[5],int len,int option)
{
	int max=0,flag=0;
	proc p;
	node *temp,*del;
	temp=freehole->head;
	switch (option)
	{
		case 1:
		//for first fit
		del=NULL;
		temp=freehole->head->right;
		//choose the hole
		while(temp!=freehole->tail)
		{
			if(len<=temp->p.end-temp->p.start)
			{
				del=delete_address(freehole,temp);
				break;
			}
			temp=temp->right;
		}
		if(del==NULL) printf("There is no first fit hole found\n");
		break;
		case 2:
		//choose the hole for best fit
		del=find_best(freehole,len);
		if(del!=NULL)del=delete_address(freehole,del);
		break;
		case 3:
		//choose the hole for worst fit
		del=find_worst(freehole);
		if(del!=NULL)del=delete_address(freehole,del);
		break;

	}
	if(del==NULL) //if there is no hole available
		printf("\nThere is no hole to accomodate the process\n");
	else
	{
		//if the hole is available
		p=del->p;
		strcpy(p.id,id);
		//remove del from free pool
		free(del);
		//insert the node into the alloted list
		insert_at_pos(allot,p);
	}
	
}

//Desllocate the memore for the given process
void deallocate(ll *allot,ll *freehole,char id[5])
{
	node *del;
	if(allot->head->right==allot->tail) //if the alloted list is empty
	{
		printf("\nThere are is no memory allocated to any of the processes\n");
		return;
	}
	del=delete_node(allot,id);
	if(del!=NULL)
	{
		strcpy(del->p.id,"hole");
		insert_at_pos(freehole,del->p);
		free(del);
		printf("\nthe process memory has been deallocated\n");
	}
	else
	{
		printf("\nThere is no process with that id\n");
	}
}

//merge the adjascent holes
void coalescing(ll *freehole)
{
	node *temp,*next;
	temp=freehole->head->right;
	while(temp->right!=freehole->tail)
	{
		next=temp->right;
		if(temp->p.end==next->p.start)
		{
			temp->p.end=next->p.end;
			temp->right=next->right;
			next->right->left=temp;
			freehole->size--;
			free(next);
		}
		else
			temp=temp->right;
	}
}





/*
output:
C:\Users\VAISHNAVI M R\Desktop\os\ex8>p

PROGRAM TO IMPLEMENT MEMORY ALLOCATION TECHNIQUES:

Enter the memory representation:
Enter the no of partitions:3
starting and ending address of partition 1 :100
105
starting and ending address of partition 2 :105
110
starting and ending address of partition 3 :110
115

alloted memory:
----->NULL

free pool:
---------------------------
|hole    |hole    |hole    |
---------------------------
100      105      110      115

physical memory:
---------------------------
|hole    |hole    |hole    |
---------------------------
100      105      110      115


Memory Allocation Algorithm:
1.First Fit
2.Best Fit
3.Worst Fit
4.Exit from the program
Enter choice:1

First Fit Memory allocation Algorithm

1.Entry/Allocate
2.Exit/Deallocate
3.Display
4.Coalescing of Holes
5.Back to algorithm
0.exit
Enter choice:1

Enter process id:p1
Enter the size needed:4

1.Entry/Allocate
2.Exit/Deallocate
3.Display
4.Coalescing of Holes
5.Back to algorithm
0.exit
Enter choice:3

alloted memory:
---------
|p1      |
---------
100
free pool:
------------------
|hole    |hole    |
------------------
105      110      115

physical memory:
---------------------------
|p1      |hole    |hole    |
---------------------------
100      105      110      115

1.Entry/Allocate
2.Exit/Deallocate
3.Display
4.Coalescing of Holes
5.Back to algorithm
0.exit
Enter choice:2

Enter process id:p1
the process memory has been deallocated

1.Entry/Allocate
2.Exit/Deallocate
3.Display
4.Coalescing of Holes
5.Back to algorithm
0.exit
Enter choice:3

alloted memory:
----->NULL

free pool:
---------------------------
|hole    |hole    |hole    |
---------------------------
100      105      110      115

physical memory:
---------------------------
|hole    |hole    |hole    |
---------------------------
100      105      110      115

1.Entry/Allocate
2.Exit/Deallocate
3.Display
4.Coalescing of Holes
5.Back to algorithm
0.exit
Enter choice:4

1.Entry/Allocate
2.Exit/Deallocate
3.Display
4.Coalescing of Holes
5.Back to algorithm
0.exit
Enter choice:3

alloted memory:
----->NULL

free pool:
---------
|hole    |
---------
100      115

physical memory:
---------
|hole    |
---------
100      115

1.Entry/Allocate
2.Exit/Deallocate
3.Display
4.Coalescing of Holes
5.Back to algorithm
0.exit
Enter choice:0
exiting...

*/