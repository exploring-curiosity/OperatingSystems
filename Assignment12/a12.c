#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct 
{
    char dname[20][20];
    int noOfDir;
}MFD;


typedef struct 
{
    char dirname[15];
    int noOffiles;
    char fileName[15][15];
}dir;

typedef struct 
{
    char fname[10];
}file;

typedef struct Treedir
{
    
    char dname[10];
    struct Treedir *dir1,*dir2,*dir3;
    file *file1,*file2;

}Treedir;

Treedir *t=NULL;



void single_level();
void two_level();
Treedir* init();
void insertDirectory(char pname[],char dirname[]);
void insertFile(char pname[],char filename[]);
void displayContents(Treedir *root, char path[]);
void tree();
file *getFilePointer(char path[]);
Treedir *getDirectoryPointer(char path[]);
void createLink(char path[], char dir_name[]);
void DAG();


void main()
{
    int choice;
    char c;


    do
    {
        printf("\n\t\tFILE ORGANISATION TECHNIQUES\n");
        printf("1.Single Level Directory\n");
        printf("2.Two Level Directory\n");
        printf("3.Tree structures directory\n");
        printf("4.DAG\n");

        printf("Enter choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:single_level();
                    break;

            case 2:
                    two_level();
                    break;
            case 3:
                    tree();
                    break;
            case 4:
                    DAG();
                    break;
        }

        printf("\nDo you wish to continue?");
        scanf("%s",&c);
    } while (c=='y');
    


}

void single_level()
{
    int choice,i;
    char name[15];
    dir d;
		
    printf("\nEnter directory name:");
    scanf("%s",&d.dirname);
    d.noOffiles=0;

    do
    {
        menu:

        printf("\n1.Create file\n");
        printf("2.Display file\n");
        printf("3.Exit\n");
        
        printf("Enter choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                    printf("Enter fileName:");
                    scanf("%s",&name);
    
                    for(i=0;i<d.noOffiles;i++)
                    {
                        if(strcmp(name,d.fileName[i])==0)//if file already exists, goto menu
                        {
                            printf("File already exists!\n");
                            goto menu;
                        }
                    }

                    strcpy(d.fileName[i],name);
                    d.noOffiles++;
                    printf("\nFile created!\n");

                    break;

            case 2:
                    printf("\n\tContents of Directory:%s\n\n",d.dirname);
                    printf("\tFile Name\tPath\n");
                    for(i=0;i<d.noOffiles;i++)
                    {
                        printf("\t%s\t\t%s/%s\n",d.fileName[i],d.dirname,d.fileName);
                    }
                    break;

            case 3:
                    break;

        }
        
    } while(choice!=3);
    
}

void two_level()
{

    int i,choice,dirno,j;


    char name[20];

    MFD mdir;
    mdir.noOfDir=0;
    dir d[10];

    do
    {
        menu:

        printf("\n1.Create Directory\n");
        printf("2.Create file\n");
        printf("3.Display file\n");
        printf("4.Search File\n");
        printf("5.Exit\n");
        
        printf("Enter choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                    printf("\nEnter the name of the directory:");
                    scanf("%s",&mdir.dname[mdir.noOfDir]);
                    d[mdir.noOfDir].noOffiles=0;
                    mdir.noOfDir++;
                    printf("Directory created!\n");
                    break;

            case 2:
                    printf("Enter the directory in which you want to create a file:");
                    scanf("%s",&name);

                    for(i=0;i<mdir.noOfDir;i++)
                    {
                        if(strcmp(name,mdir.dname[i])==0)
                        {
                            dirno=i;
                            break;
                        }
                    }

                    printf("Enter fileName:");
                    scanf("%s",&name);
    
                    for(i=0;i<d[dirno].noOffiles;i++)
                    {
                        if(strcmp(name,d[dirno].fileName[i])==0)//if file already exists, goto menu
                        {
                            printf("File already exists!\n");
                            goto menu;
                        }
                    }

                    

                    strcpy(d[dirno].fileName[i],name);
                    d[dirno].noOffiles++;
                    printf("\nFile created!\n");

                    break;
            case 3:
                    printf("\tFile Name\tPath\n");
                    for(j=0;j<mdir.noOfDir;j++)
                    {
                        
                        for(i=0;i<d[j].noOffiles;i++)
                        {
                            printf("\t%s\t\t%s/%s\n",d[j].fileName[i],mdir.dname[j],d[j].fileName[i]);
                        }
                   
                    }
                    
                    break;

            case 4:
                    printf("\nEnter the file name to search for:");
                    scanf("%s",&name);

                    printf("\n\tFile name\tPath\n");
                    for(i=0;i<mdir.noOfDir;i++)
                    {
                        for(j=0;j<d[i].noOffiles;j++)
                        {
                            if(strcmp(name,d[i].fileName[j])==0)
                            {
                                printf("\t%s\t\t%s/%s\n",d[i].fileName[j],mdir.dname[i],d[i].fileName[j]);
                            }
                        }
                    }
            case 5:
                    break;


        }

    
    }while(choice!=5);
    
}


Treedir* init()
{ //initialising root directory
    Treedir *root;
    root = (Treedir *)malloc(sizeof(Treedir));

    strcpy(root->dname, "root");
    root->dir1 = NULL;
    root->dir2 = NULL;
    root->dir3 = NULL;
    root->file1 = NULL;
    root->file2 = NULL;

    return root;
}

void insertDirectory(char path[],char dirname[])
{ 
    Treedir *temp = t;
    Treedir *tmp;
    char *pname = strtok(path, "/");
    pname = strtok(NULL, "/");
    

    while (pname != NULL)
    { //moving to the specified sub-directory
        
        if (temp->dir1 != NULL && strcmp(pname,(tmp=temp->dir1)->dname)==0)
        {

             temp = temp->dir1;
        }
        else if (temp->dir2 != NULL && strcmp(pname,(tmp=temp->dir2)->dname)==0)
        {
              
            temp = temp->dir2;
        }
        else if (temp->dir3 != NULL && strcmp(pname,(tmp=temp->dir3)->dname)==0)
        {
           
            
            temp = temp->dir3;
        }

        pname = strtok(NULL, "/");

       
    }

    
    if (temp->dir1 == NULL || temp->dir2 == NULL || temp->dir3 == NULL)
    { //if space exists in the specified sub-directory
        

        Treedir *new_dir = (Treedir *)malloc(sizeof(Treedir));
        new_dir->dir1 = NULL;
        new_dir->dir2 = NULL;
        new_dir->dir3 = NULL;
        new_dir->file1 = NULL;
        new_dir->file2 = NULL;
        strcpy(new_dir->dname,dirname);

        //connecting it to a free pointer of the parent directory
        if (temp->dir1 == NULL)
        {
           
            temp->dir1 = new_dir;
            printf("Directory created!\n");
        }
        else if (temp->dir2 == NULL )
        {
            
            tmp=temp->dir1;
            if(strcmp(dirname,tmp->dname)!=0)
                temp->dir2 = new_dir;
            printf("Directory created!\n");
        }
        else if (strcmp(dirname, (tmp=temp->dir1)->dname) != 0 && strcmp(dirname, (tmp=temp->dir2)->dname) != 0)
        {
            temp->dir3 = new_dir;
            printf("Directory created!\n");
        }
        else if (strcmp(dirname, (tmp=temp->dir1)->dname) == 0 || strcmp(dirname, (tmp=temp->dir2)->dname) == 0)
        { //if it already exists
            printf("\nDirectory %s already exists!\n", dirname);
        }
        else
        { //if no space is free in the sub-directory
            printf("\nMAX limit reached. Only 3 subdirectories are allowed.\n");
        }
    }
    
}

void insertFile(char path[],char filename[])
{
    
    Treedir *temp = t;
    Treedir *tmp;

    char *pname = strtok(path, "/");
    pname = strtok(NULL, "/");

    while (pname != NULL)
    { 
        
        //moving to specified sub-directory
        if (temp->dir1 != NULL && strcmp(pname, (tmp=temp->dir1)->dname) == 0)
        {
            
            temp = temp->dir1;
        }
        else if (temp->dir2 != NULL && strcmp(pname, (tmp=temp->dir2)->dname) == 0)
        {
         
            temp = temp->dir2;
        }
        else if (temp->dir3 != NULL && strcmp(pname, (tmp=temp->dir3)->dname) == 0)
        {
            
            temp = temp->dir3;
        }
        
        pname = strtok(NULL, "/");
        
    }

   
    if (temp->file1 == NULL || temp->file2 == NULL)
    { 
        //if the sub-directory has space for files
        
        file *new_file = (file *)malloc(sizeof(file));
        strcpy(new_file->fname,filename);

        if (temp->file1 == NULL)
        {
            temp->file1 = new_file;
        }
        else if (temp->file2 == NULL)
        {
            temp->file2 = new_file;
        }
        printf("\nFile created!\n");
    }
    else
    { 
        //if it doesn't have space for files
        printf("\nMAX limit reached. Only 2 files are allowed per directory.\n");
    }
    

}

void displayContents(Treedir *root, char path[])
{ //to display the contents of the directory
    char temp[50];

    if (root != NULL)
    {
        strcat(path,root->dname);
        strcat(path, "/");
        if (root->file1 != NULL)
        {
            printf("%s\t\t\t\t%s\n", root->file1->fname, path);
        }
        if (root->file2 != NULL)
        {
            printf("%s\t\t\t\t%s\n", root->file2->fname, path);
        }
        if (root->dir1 != NULL)
        {
            strcpy(temp,path);
            displayContents(root->dir1,path);
        }
        if (root->dir2 != NULL)
        {
            strcpy(temp,path);
            displayContents(root->dir2, temp);
        }
        if (root->dir3 != NULL)
        {
            strcpy(temp, path);
            displayContents(root->dir3, temp);
        }
    }
}

void tree()
{
    int choice;

    char name[20];
    char path[20];

    t=init();
    do
    {
        
        printf("\n1.Create Directory\n");
        printf("2.Create file\n");
        printf("3.Display file\n");
        printf("4.Exit\n");
        
        printf("Enter choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: 
                    printf("\nEnter the name of the directory:");
                    scanf("%s",&name);
                    
                    printf("Enter the path where you want to store the directory:");
                    scanf("%s",&path);
 
                    insertDirectory(path,name);
                    
                    break;

            case 2:
                    printf("\nEnter the name of the file:");
                    scanf("%s",&name);
                    
                    printf("Enter the path where you want to store the file:");
                    scanf("%s",&path);

                    insertFile(path,name);

                    break;

            case 3: 
                    strcpy(path, "");
                    printf("\nFile\t\t\t\tPath\n\n");
                    displayContents(t,path);
                    break;

            case 4:
                    break;

        }

    }while(choice!=4);
    
}

file *getFilePointer(char path[])
{ //to return the file pointer to the specified file
    Treedir *temp = t;
    Treedir *tmp;
    file *f;
    char *split = strtok(path, "/");
    char *fname;

    while (split != NULL)
    {   //traversing to the specified sub-directory
        if (temp->dir1 != NULL && strcmp(split,(tmp=temp->dir1)->dname) == 0)
        {
            temp = temp->dir1;
        }
        else if (temp->dir2 != NULL && strcmp(split,(tmp=temp->dir2)->dname) == 0)
        {
            temp = temp->dir2;
        }
        else if (temp->dir3 != NULL && strcmp(split, (tmp=temp->dir3)->dname) == 0)
        {
            temp = temp->dir3;
        }
        fname = split;
        split = strtok(NULL, "/");
        if (split == NULL)
        {   //reached the parent directory of the file
            if (strcmp((f=temp->file1)->fname, fname) == 0)
            {
                return temp->file1;
            }
            else if (strcmp((f=temp->file2)->fname,fname) == 0)
            {
                return temp->file2;
            }
            else
            {
                printf("\nThe specified file does not exist.\n");
                return NULL;
            }
        }
    }
    return NULL;
}


Treedir *getDirectoryPointer(char path[])
{ //to return the directory pointer to the specified directory
    char *split = strtok(path, "/");
    Treedir *temp = t;
    Treedir *tmp;

    while (split != NULL)
    {   //traversing to the specified sub-directory
        if (temp->dir1 != NULL && strcmp(split,(tmp=temp->dir1)->dname) == 0)
        {
            temp = temp->dir1;
        }
        else if (temp->dir2 != NULL && strcmp(split,(tmp=temp->dir2)->dname) == 0)
        {
            temp = temp->dir2;
        }
        else if (temp->dir3 != NULL && strcmp(split, (tmp=temp->dir3)->dname) == 0)
        {
            temp = temp->dir3;
        }

        split = strtok(NULL, "/");

        if (split == NULL)
        {   //reached the required directory
            return temp;
        }
    }
    return NULL;
}

void createLink(char path[], char dir_name[])
{   //creating a link to existing file to another directory
    
    file *temp_file = getFilePointer(path);
    
    Treedir *temp_dir = getDirectoryPointer(dir_name);

    if (temp_file != NULL)
    {
        if (temp_dir->file1 == NULL)
        {
            temp_dir->file1 = temp_file;
        }
        else if (temp_dir->file2 == NULL)
        {
            temp_dir->file2 = temp_file;
        }
        else
        {
            printf("\nLink cannot be created.\n");
        }
    }
}

void DAG()
{
    int choice;

    char name[20];
    char path[20];

    t=init();
    do
    {
        
        printf("\n1.Create Directory\n");
        printf("2.Create file\n");
        printf("3.Create a link to a file\n");
        printf("4.Display file\n");
        printf("5.Exit\n");
        
        printf("Enter choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: 
                    printf("\nEnter the name of the directory:");
                    scanf("%s",&name);
                    
                    printf("Enter the path where you want to store the directory:");
                    scanf("%s",&path);
 
                    insertDirectory(path,name);
                    
                    break;

            case 2:
                    printf("\nEnter the name of the file:");
                    scanf("%s",&name);
                    
                    printf("Enter the path where you want to store the file:");
                    scanf("%s",&path);

                    insertFile(path,name);

                    break;

            case 3:
                    printf("\nEnter the Path of File (Including File Name): ");
                    scanf("%s", path);
                    printf("\nEnter the Path of Directory to Create Link in: ");
                    scanf("%s",name);
                    createLink(path,name);
                    break;

            case 4: 
                    strcpy(path, "");
                    printf("\nFile\t\t\t\tPath\n\n");
                    displayContents(t,path);
                    break;

            case 5:
                    break;

        }

    }while(choice!=5);
    
}



/*
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A12>gcc -o c a12.c
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A12>c

                FILE ORGANISATION TECHNIQUES
1.Single Level Directory
2.Two Level Directory
3.Tree structures directory
4.DAG
Enter choice:1

Enter directory name:root

1.Create file
2.Display file
3.Exit
Enter choice:1
Enter fileName:file1

File created!

1.Create file
2.Display file
3.Exit
Enter choice:1
Enter fileName:file2

File created!

1.Create file
2.Display file
3.Exit
Enter choice:2

        Contents of Directory:root

        File Name       Path
        file1           root/file1
        file2           root/file1

1.Create file
2.Display file
3.Exit
Enter choice:3

Do you wish to continue?y

                FILE ORGANISATION TECHNIQUES
1.Single Level Directory
2.Two Level Directory
3.Tree structures directory
4.DAG
Enter choice:2

1.Create Directory
2.Create file
3.Display file
4.Search File
5.Exit
Enter choice:1

Enter the name of the directory:user1
Directory created!

1.Create Directory
2.Create file
3.Display file
4.Search File
5.Exit
Enter choice:1

Enter the name of the directory:user2
Directory created!

1.Create Directory
2.Create file
3.Display file
4.Search File
5.Exit
Enter choice:2
Enter the directory in which you want to create a file:user1
Enter fileName:file1

File created!

1.Create Directory
2.Create file
3.Display file
4.Search File
5.Exit
Enter choice:2
Enter the directory in which you want to create a file:user2
Enter fileName:file1

File created!

1.Create Directory
2.Create file
3.Display file
4.Search File
5.Exit
Enter choice:3
        File Name       Path
        file1           user1/file1
        file1           user2/file1

1.Create Directory
2.Create file
3.Display file
4.Search File
5.Exit
Enter choice:4

Enter the file name to search for:file1

        File name       Path
        file1           user1/file1
        file1           user2/file1

1.Create Directory
2.Create file
3.Display file
4.Search File
5.Exit
Enter choice:5

Do you wish to continue?y

                FILE ORGANISATION TECHNIQUES
1.Single Level Directory
2.Two Level Directory
3.Tree structures directory
4.DAG
Enter choice:3

1.Create Directory
2.Create file
3.Display file
4.Exit
Enter choice:1

Enter the name of the directory:sub1
Enter the path where you want to store the directory:root/
Directory created!

1.Create Directory
2.Create file
3.Display file
4.Exit
Enter choice:1

Enter the name of the directory:ssub1
Enter the path where you want to store the directory:root/sub1
Directory created!

1.Create Directory
2.Create file
3.Display file
4.Exit
Enter choice:2

Enter the name of the file:file1
Enter the path where you want to store the file:root/

File created!

1.Create Directory
2.Create file
3.Display file
4.Exit
Enter choice:2

Enter the name of the file:file2
Enter the path where you want to store the file:root/sub1/ssub1

File created!

1.Create Directory
2.Create file
3.Display file
4.Exit
Enter choice:3

File                            Path

file1                           root/
file2                           root/sub1/ssub1/

1.Create Directory
2.Create file
3.Display file
4.Exit
Enter choice:4

Do you wish to continue?y

                FILE ORGANISATION TECHNIQUES
1.Single Level Directory
2.Two Level Directory
3.Tree structures directory
4.DAG
Enter choice:4

1.Create Directory
2.Create file
3.Create a link to a file
4.Display file
5.Exit
Enter choice:1

Enter the name of the directory:sub
Enter the path where you want to store the directory:root/
Directory created!

1.Create Directory
2.Create file
3.Create a link to a file
4.Display file
5.Exit
Enter choice:2

Enter the name of the file:f1
Enter the path where you want to store the file:root/

File created!

1.Create Directory
2.Create file
3.Create a link to a file
4.Display file
5.Exit
Enter choice:2

Enter the name of the file:f2
Enter the path where you want to store the file:root/sub

File created!

1.Create Directory
2.Create file
3.Create a link to a file
4.Display file
5.Exit
Enter choice:3

Enter the Path of File (Including File Name): root/f1

Enter the Path of Directory to Create Link in: root/sub

1.Create Directory
2.Create file
3.Create a link to a file
4.Display file
5.Exit
Enter choice:4

File                            Path

f1                              root/
f2                              root/sub/
f1                              root/sub/

1.Create Directory
2.Create file
3.Create a link to a file
4.Display file
5.Exit
Enter choice:5

Do you wish to continue?n

*/