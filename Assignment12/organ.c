#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct myfile{
	char filename[20];
	int address;
}file;
typedef struct mydirectory{
	int id;
	char dirname[20];
	char parentdir[20];
	char childdir[2][20];
	int childid[2];
	int ch;
	char filename[2][20];
	int fil;
	int disp;
}directory;
directory x[100];
int createfile(file table[],int n);
void displaytable(file table[],int n);
void createdirectory(directory x[],int y);
void createdirectoryfile(directory x[],int y);
void print(int array[],int size,int number);
void main(){
	file table[100];
	
	int choice,ch,n=0,y=0;
	do{
		printf("\n1.Single level directory\n2.Tree structures directory\n3.Exit");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("\n1.Create a file\n2.List the files");
				scanf("%d",&ch);
				if(ch==1)
					n=createfile(table,n);
				else if(ch==2)
					displaytable(table,n);
				break;
			case 2:
				do{
					for(int i=0;i<y;i++)
						x[i].disp=0;
					printf("\n1.Create a directory\n2.Create a file\n3.Display the tree\n4.Exit");
					scanf("%d",&ch);
					if(ch==1){
						createdirectory(x,y);
						y++;
					}
					else if(ch==2)
						createdirectoryfile(x,y);
					else if(ch==3){
						for(int i=0;i<y;i++){
							if(x[i].disp==0){
								printf("\n+%s(D)",x[i].dirname);
								x[i].disp=1;
								for(int j=0;j<x[i].fil;j++){
									printf("\n\t%s(F)",x[i].filename[j]);
								}
								print(x[i].childid,x[i].ch,1);
							}
						}
					}
			}while(ch!=4);
		}
	}while(choice!=3);
}

int createfile(file table[],int n){
	char name[20];
	int flag=0;
	printf("\nEnter the new filename");
	scanf("%s",name);
	for(int i=0;i<n;i++){
		if(strcmp(table[i].filename,name)==0){
			printf("\nFile name already exist");
			flag=1;
			break;
		}
	}
	if(flag==0){
		strcpy(table[n].filename,name);
		printf("\nEnter the file location");
		scanf("%d",&table[n].address);
		n++;
	}
	return n;
}


void displaytable(file table[],int n){
	printf("\nFile Name    Location");
	for(int i=0;i<n;i++){
		printf("\n%s            %d",table[i].filename,table[i].address);
	}
}

void createdirectory(directory x[],int y){
	directory temp;
	int ch;
	printf("\nEnter the directory name");
	scanf("%s",temp.dirname);
	temp.ch=0;
	temp.fil=0;
	temp.disp=0;
	temp.id=y;
	for(int i=0;i<3;i++)
		temp.childid[i]=0;
	printf("\nDoes the directory has a parent directory?1.Yes 2.No");
	scanf("%d",&ch);
	if(ch==1){
		printf("\nEnter the parent directory name");
		scanf("%s",temp.parentdir);
		for(int i=0;i<y;i++){
			if(strcmp(x[i].dirname,temp.parentdir)==0){
				if(x[i].ch<=2){
					strcpy(x[i].childdir[x[i].ch],temp.dirname);
					x[i].childid[x[i].ch]=temp.id;
					//printf("\n%d",temp.id);
					x[i].ch+=1;
				}
				else{
					printf("\nMax capacity reached");
					break;
				}
			}
		}
	}
	x[y]=temp;
}
void createdirectoryfile(directory x[],int y){
	char name[20];
	printf("\nEnter the Parent directory name");
	scanf("%s",name);
	for(int i=0;i<y;i++){
		if(strcmp(x[i].dirname,name)==0){
			if(x[i].fil<=2){
				printf("\nEnter the filename");
				scanf("%s",x[i].filename[x[i].fil]);
				x[i].fil+=1;
			}
			else{
				printf("\nMax capacity reached");
				break;
			}
		}
	}
}


void print(int array[],int size,int number){
	if(size==0)
		return;
	else{
		for(int i=0;i<size;i++){
			printf("\n");
			for(int z=0;z<number;z++){
				printf("\t");
			}
			printf("+%s(D)",x[array[i]].dirname);
			for(int j=0;j<x[array[i]].fil;j++){
				printf("\n");
				for(int z=0;z<number+1;z++)
					printf("\t");
				printf("%s(F)",x[array[i]].filename[j]);
			}
			x[array[i]].disp=1;
			print(x[array[i]].childid,x[array[i]].ch,number+1);
		}
	}

}
