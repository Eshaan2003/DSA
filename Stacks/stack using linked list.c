/*
Author: Eshaan Shetty
Date: 21/05/2023
USN: 01FE21BEC097
*/
#include<stdio.h>
#define MAXRAND 10000
struct node
{
    int data;
    struct node *next;
};
typedef struct node *NODE;
NODE head, newnode, temp, cur,next,prev;          //Global declaration
NODE head=NULL;

typedef struct topnode
{
    int sp;
    int data;
}TOPNODE;
TOPNODE Topnode;

NODE getnode()
{
    newnode=(NODE)malloc(sizeof(struct node));
    if(newnode==NULL)
    {
        printf ("Memory not allocated for node! \n");
        exit(0);
    }
    newnode->next=NULL;
    return newnode;
}

NODE insertend(int num)
{
    newnode=getnode();
    newnode->data=num;
    if(head==NULL)  //empty LL
    {
        head=newnode;
    }
    else
    {
        temp=head;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newnode;
    }
    return(head);
}
int deleteend()
{
    int item;
    if(head==NULL)  //empty LL
    {
        printf("Stack already empty!\n");
    }
    else
    {
        prev=NULL;
        temp=head;
        while(temp->next!=NULL)
        {
            prev=temp;
            temp=temp->next;
        }
        Topnode.data=prev->data;
        prev->next=NULL;
        item=temp->data;
        free(temp);
    }
    return(item);
}

int StackisEmpty()
{
    return(Topnode.sp==-1);
}
int StackisFull(int n)
{
    if(Topnode.sp==n-1)        //no more random numbers available in file
        return 1;
    else
        return 0;
}

void write_random_to_file(FILE* fptr,char inputfile[],int n)//(file_ptr,file_name,source_array,array_size)
{
    fptr=fopen(inputfile,"w");
    if(fptr==NULL)
    {
        printf("'%s' File creation error!\n",inputfile);
    }
    else
    {
        printf("'%s' File created successfully\n",inputfile);
        for(int i=0;i<n;i++)
        {
            int random=rand()%200;
            fprintf(fptr,"%d\n",random);
        }
        printf("Entered %d random numbers in file successfully\n",n);
    }
    fclose(fptr);
}
void pushfromfile(FILE* fptr,char inputfile[],int n)// FILE* fpPush, FILE* fpStack)
{
    if(fptr==NULL)
    {
        printf("'%s' File reading error!\n",inputfile);
    }
    else if(feof(fptr))
    {
        printf("Reached end of the file '%s'\n",inputfile);
    }
    else
    {
        printf("'%s' File reading successfully\n",inputfile);
        if(StackisFull(n))                //stack is full
        {
            printf("Stack overflow\n");
            return;
        }
        Topnode.sp++;
        fscanf(fptr,"%d",&Topnode.data);
        head=insertend(Topnode.data);
        printf("%d pushed, top=%d\n",Topnode.data,Topnode.sp);
    }
}
int pop()
{
    if(StackisEmpty())     //isempty
    {
        printf("Stack underflow\n");
        return;
    }
    int item=deleteend();
    Topnode.sp--;
    printf("%d popped; top=%d\n",item,Topnode.sp);
    return item;
}
void flush(FILE* fptr, char filename[])
{
    fptr=fopen(filename,"w");
    fclose(fptr);
    printf("Clearing '%s' file...\n",filename);
}
void display()
{
    if(StackisEmpty())      //empty stack => nothing to display
    {
        printf("Stack underflow\n");
        return;
    }
    printf("Displaying stack: ");       //operation similar to seek

    temp=head;
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
}

void main()
{
    Topnode.sp=-1;
    FILE *fpinput;
    FILE *fpPush;
    FILE *fpPop;
    FILE *fpStack;
    FILE *fpOpn;
    char inputfile[]="Inputfile.txt",stackfile[]="stackfile.txt",pushlog[]="Pushlog.txt",poplog[]="Poplog.txt",opfile[]="OperationsFile.txt";
    int n,choice;
    fpinput=fopen(inputfile,"r");
    fpPush=fopen(pushlog,"a");
        if(fpPush==NULL)  printf("'%s' File creation/opening error!\n",pushlog);
    fpPop=fopen(poplog,"a");
        if(fpPop==NULL)   printf("'%s' File creation/opening error!\n",poplog);
    fpOpn=fopen(opfile,"a");
        if(fpOpn==NULL)  printf("'%s' File creation/opening error!\n",fpOpn);
    while(1)
    {
        printf("\n\nEnter choice:\n 0:Clear all files \n 1:Generate random numbers \n 2:Push \n 3:Pop \n 4:Display stack \n 5:Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 0: flush(fpinput,inputfile);
                    flush(fpStack,stackfile);
                    flush(fpPush,pushlog);
                    flush(fpPop,poplog);
                    flush(fpOpn,opfile);
                    printf("\n");
                    break;
            case 1: printf("Enter number of random numbers to write to file (range): ");
                    scanf("%d",&n);
                    write_random_to_file(fpinput,inputfile,n);
                    break;
            case 2: pushfromfile(fpinput,inputfile,n);
                    fprintf(fpPush,"%d\n",Topnode.data);        //appending Topnode.data to pushfile
                    fprintf(fpOpn,"%s\n","Push");        //appending
                    break;
            case 3: fprintf(fpPop,"%d\n",Topnode.data);        //appending Topnode.data to pushfile
                    fprintf(fpOpn,"%s\n","Pop");        //appending
                    pop();
                    break;
            case 4: display();
                    break;
            case 5: printf("Exit\n");
                    goto exit;
            default: printf("wrong choice \n");
        }
    }
    exit:
    fclose(fpinput);
    fclose(fpPush);
    fclose(fpPop);
    fclose(fpOpn);
    fpStack=fopen(stackfile,"a");       //copying the stack to stack file
    temp=head;
    for(int i=Topnode.sp;i>-1;i--)
    {
        fprintf(fpStack,"%d\n",temp->data);
        temp=temp->next;
    }
    fclose(fpStack);
}
