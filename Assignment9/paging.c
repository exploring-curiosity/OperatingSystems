#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int Free[20];
int alloc[20];
int alloc_index=0;
int free_index=0;
int noOfProcess=0;
int k=0;

typedef struct 
{
    int noOfPages;
    int pid;
}process;
process *p[20];



void Allocation(int ps);
void display_FreeFrame();
void display_pageTable();
void Deallocation();

void main()
{
    int page_size,mem_size,noOfFrames;
    int i,ch,r,j;
    char c;

    for(i=0;i<20;i++)
    {
        p[i]=(process*)malloc(sizeof(process));
    }

    printf("Enter the physical memory size(in KB):");
    scanf("%d",&mem_size);

    printf("Enter the page size(in KB):");
    scanf("%d",&page_size);
   

    noOfFrames=mem_size/page_size;

    srand(time(0));

    for(i=0;i<noOfFrames/2;i++)
    {
        r=rand()%(32)+1;
        for (j = 0; j < i;j++) 
        {
            if ( Free[j]== r )
                break;
        }
 
  
        if ( j == i )
        {
            Free[free_index++]=r;
        }          
    }

    do
    {
        printf("\nMenu\n");
        printf("1.Process request\n");
        printf("2.Deallocation\n");
        printf("3.Page table display\n");
        printf("4.Free frames display\n");

        printf("Enter choice:");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:  Allocation(page_size);
                    break;

            case 2: Deallocation();
                    break;
            case 3:
                    display_pageTable();
                    break;
            case 4:
                    display_FreeFrame();
                    break;

        }

        printf("Do you want to continue?");
        scanf("%s",&c);
    } while(c=='y');
    
}

void Allocation(int ps)
{

    int size,i,a,n;
    

    printf("Enter the process id:");
    scanf("%d",&p[k]->pid);

    printf("Enter the process size(in KB):");
    scanf("%d",&size);
    noOfProcess++;

    p[k]->noOfPages=size/ps;
    n=p[k]->noOfPages;

    for(i=0;i<n;i++)
    {
        alloc[alloc_index++]=Free[i];  
        printf("Page %d:Frame %d\n",i,Free[i]); 
    }
    

    for(i=0;i<free_index-n+1;i++)
    {
        Free[i]=Free[n+i];
    }
    free_index-=n;
    k++;
   

}

void Deallocation()
{
    int i,id,n,skip=0;

    printf("Enter process id to deallocate:");
    scanf("%d",&id);

    n=p[id-1]->noOfPages;

    for(i=0;i<id-1;i++)
    {
        skip+=p[i]->noOfPages;
    }


    for(i=skip;i<skip+n;i++)
    {
        Free[free_index++]=alloc[i];
    }

    for(i=skip;i<skip+n;i++)
    {
        alloc[i]=0;
    }

}

void display_pageTable()
{
    int i,j=0,x=0;

    while(j<noOfProcess)
    {
        printf("\nProcess p%d\n",j+1);
        for(i=0;i<p[j]->noOfPages;i++)
        {
            if(alloc[x]==0)
            {
                x=x+p[j]->noOfPages;
                break;
            }
              
            printf("Page %d:Frame %d\n",i,alloc[x]); 
            x++;
        }
        j++;
    }
}

void display_FreeFrame()
{
    int i;

    printf("Free frame list:");
    for(i=0;i<free_index;i++)
    {
        printf("%d  ",Free[i]);
    }
    printf("\n");
}

/*
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A9>gcc -o a paging.c

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A9>a
Enter the physical memory size(in KB):32
Enter the page size(in KB):1

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:1
Enter the process id:1
Enter the process size(in KB):4
Page 0:Frame 2
Page 1:Frame 14
Page 2:Frame 22
Page 3:Frame 12
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:1
Enter the process id:2
Enter the process size(in KB):2
Page 0:Frame 15
Page 1:Frame 4
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:4
Free frame list:25  8  3  7  23  13
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:2
Enter process id to deallocate:2
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:4
Free frame list:25  8  3  7  23  13  15  4
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:3

Process p1
Page 0:Frame 2
Page 1:Frame 14
Page 2:Frame 22
Page 3:Frame 12

Process p2
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:1
Enter the process id:3
Enter the process size(in KB):3
Page 0:Frame 25
Page 1:Frame 8
Page 2:Frame 3
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:4
Free frame list:7  23  13  15  4
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:2
Enter process id to deallocate:1
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:4
Free frame list:7  23  13  15  4  2  14  22  12
Do you want to continue?y

Menu
1.Process request
2.Deallocation
3.Page table display
4.Free frames display
Enter choice:3

Process p1

Process p2

Process p3
Page 0:Frame 25
Page 1:Frame 8
Page 2:Frame 3
Do you want to continue?n
*/