/*
Author:Eshaan Shetty
Date: 21/05/2023
USN: 01FE21BEC097
*/
#include<stdio.h>
#define MAXRAND 10000
#define MAXQUEUE 10000
int queue[MAXQUEUE];
int front=-1,rear=-1;

void generate_random_nums(FILE *fptr,char file_name[])
{
    fptr=fopen(file_name,"w");
    int num;
    if(fptr==NULL)
        printf("'%s' File creation error!\n",file_name);
    else
    {
        printf("File created successfully\n");
        for(int i=0;i<MAXRAND;i++)
        {
            num=rand();
            fprintf(fptr,"%d\n",num%200);       //Store random numbers to file
        }
        printf("%d random numbers are generated and entered in file\n",MAXRAND);
    }
    fclose(fptr);
}

int read_n_nos_from_file(FILE* fptr,char readthisfile[],int n)    //(file_pointer,file_name,size)
{
    printf("Reading from file:\n");
    fptr=fopen(readthisfile,"r");
    if(fptr==NULL)
    {
        printf("%s File opening error!\n",readthisfile);
        return NULL;
    }
    printf("'%s' file opened successfully\n",readthisfile);
    fscanf(fptr,"%d",&n);
    printf("Number of numbers to be operated: %d\n",n);
    for(int i=0;i<n;i++)
    {
        int buf;
        fscanf(fptr,"%d",&buf);     //reading random numbers one by one from file
        enqueue(buf);              //loading random numbers to queue
    }
    printf("%d numbers loaded in queue successfully\n",n);
    return n;
}
int isEmpty()
{
    if(front>rear || front==-1) return 1;
    else                        return 0;
}
int ifFull()
{
    if(rear==MAXQUEUE-1)        return 1;
    else                        return 0;
}
void enqueue(int item)
{
    if(ifFull())
    {
        printf("Queue overflow!\n");
        return;
    }
    if(front==-1)   front=0;
    rear++;
    queue[rear]=item;
}
int dequeue()
{
    if(isEmpty())
    {
        printf("Queue underflow!\n");
        return;
    }
    int item=queue[front];
    printf("Dequeued item: %d\n",item);
    front++;
    return item;
}
void queue_sort()
{
    if(isEmpty())
    {
        printf("Queue underflow!\n");
        return;
    }
    for(int i=front;i<rear;i++)
    {
        for(int j=front;j<rear-front-i;j++)
        {
            if(queue[j]>queue[j+1])
            {
                int temp=queue[j];
                queue[j]=queue[j+1];
                queue[j+1]=temp;
            }
        }
    }
}
void display_queue()
{
    if(isEmpty())
    {
        printf("Queue is empty; Nothing to display\n");
        return;
    }
    printf("Displaying queue:\n");
    for(int i=front;i<=rear;i++)
        printf("%d ",queue[i]);
    printf("\n");
}
void write_to_file(FILE* fptr,char writethisfile[])       //(file_ptr,file_name,source_array,array_size)
{
    fptr=fopen(writethisfile,"w");
    if(fptr==NULL)
    {
        printf("'%s' File creation error!\n",writethisfile);
        return;
    }
    printf("'%s' File created successfully\n",writethisfile);
    for(int i=front;i<=rear;i++)
    {
        fprintf(fptr,"%d\n",queue[i]);
    }
    fclose(fptr);
}
void main()
{
    FILE* fprandom;
    FILE* fpqueue;
    FILE* fpsort;
    int n;
    char file_name[]="Random_nums.txt",queuefile[]="Queue.txt",sortfile[]="Sorted_queue.txt";

    generate_random_nums(fprandom,file_name);
    printf("\n\n\n");

    n=read_n_nos_from_file(fprandom,file_name,n);    //(file_pointer,file_name,size)
    printf("\n\n\n");

    display_queue();
    printf("\n\n\n");
    write_to_file(fpqueue,queuefile);

    queue_sort();
    printf("Sorted queue:\n");
    display_queue();
    printf("\n\n\n");
    write_to_file(fpsort,sortfile);
}
