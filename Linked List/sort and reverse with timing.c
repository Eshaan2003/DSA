/*
Author: Eshaan Shetty
Date: 02/05/2023
USN: 01FE21BEC097
*/

#include<stdio.h>
#include<time.h>
#define MAXRAND 1000
struct node             //Structure declaration
{
    int data;
    struct node *next;
};
typedef struct node *NODE;            //alias name for structure
NODE head, newnode, temp, cur,next,prev;          //Global declaration
NODE head=NULL;

NODE getnode()              //Creating a new node
{
    newnode=(NODE)malloc(sizeof(struct node));
    if(newnode==NULL)           //Overflow condition    (maximum memory reached)
    {
        printf ("Memory not allocated for node! \n");
        exit(0);
    }
    newnode->next=NULL;     //assigning link of created node to NULL
    return newnode;
}

NODE insertend(int num)             //Insert newnode at the end of SLL
{
    newnode=getnode();              //Creating newnode
    newnode->data=num;              //assign data into node
    if(head==NULL)                  //SLL is empty
    {
        head=newnode;               //newnnode is the first node
    }
    else                            //SLL exists
    {
        temp=head;
        while(temp->next!=NULL)    //traverse till the end of SLL
            temp=temp->next;
        temp->next=newnode;         //last node
    }
    //printf("Entered the element %d in a node\n",newnode->data);
    return(head);
}

void generate_random_nums(FILE *fptr,char file_name[])
{
    fptr=fopen(file_name,"w");          //open file in write mode
    int num;
    if(fptr==NULL)
        printf("'%s' File creation error!\n",file_name);
    else
    {
        printf("File created successfully\n");
        for(int i=0;i<MAXRAND;i++)              //generating MAXRAND number of random numbers
        {
            num=rand();
            fprintf(fptr,"%d\n",num%200);
        }
        printf("%d random numbers are generated and entered in file\n",MAXRAND);
    }
    fclose(fptr);
}

int read_n_nos_from_file(FILE* fptr,char readthisfile[],int n)    //(file_pointer,file_name,size)
{
    printf("Reading from file:\n");
    fptr=fopen(readthisfile,"r");                           //opening file in read mode
    if(fptr==NULL)
    {
        printf("%s File opening error!\n",readthisfile);
        return NULL;
    }
    else
    {
        printf("'%s' file opened successfully\n",readthisfile);
        int n;
        printf("Enter number of numbers to operate: ");
        scanf("%d",&n);

        for(int i=0;i<n;i++)                    //inserting n numbers from file into SLL
        {
            int buf;
            fscanf(fptr,"%d",&buf);
            head=insertend(buf);
        }
        printf("%d numbers loaded in nodes successfully\n",n);
        return n;
    }
}

NODE reverse_nodes(NODE head)           //reversing the links (and not the data)
{
    printf("Reversing Linked list:\n");
    cur=head;
    prev=NULL;
    NODE fwd=head;              //this is the node next to cur
    while(cur!=NULL)            //traverse throughout the LL
    {
        fwd=cur->next;
        cur->next=prev;         //assigning link of cur to prev
        prev=cur;
        cur=fwd;
    }
    head=prev;          //new head points to the last node
    return head;
}

NODE bubble_sort(NODE head)
{
    printf("\nBubble sorting Linked list: \n");
    cur=head;
    prev=head;
    while(cur->next!=NULL)                  //traversing throughout the SLL
    {
        while(prev->next!=NULL)             //traversing throughout the SLL (from start to end)
        {
            if(prev->data > prev->next->data){      //if 1st element is greater than 2nd ==> Ascending order condition
                int tempdata=prev->data;            //swap
                prev->data = prev->next->data;
                prev->next->data = tempdata;
            }
            prev=prev->next;
        }
        cur=cur->next;
        prev=head;
    }
    return head;
}
/*void bubble_sort(int arr[],int n)
{
    printf("Bubble sort array: \n");
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])     //Ascending order
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
*/

void display_SLL(NODE head)
{
    if(head==NULL)                 //empty SLL
    {
        printf ("No data available in Linked list!");
        return;
    }
    temp=head;
    printf("Displaying numbers from nodes:\n");
    do                              //traversing throughout the SLL (since it is not empty)
    {
        printf ("%d\t",temp->data);
        temp=temp->next;
    }while(temp!=NULL);
    //printf ("%d ",temp->data);
}

void main()
{
    clock_t start_time,end_time;        //declaring timimgs
    double duration=0.0;
    FILE *fptr;
    int n;
    char file_name[]="Random_nums";

    generate_random_nums(fptr,file_name);
    printf("\n\n\n");

    n=read_n_nos_from_file(fptr,file_name,n);    //(file_pointer,file_name,size)
    printf("\n\n\n");

    display_SLL(head);
    printf("\n\n\n");

    head=reverse_nodes(head);
    display_SLL(head);
    printf("\n\n\n");

    start_time=clock();
    head=bubble_sort(head);
    end_time=clock();
    duration=end_time-start_time;
    display_SLL(head);
    printf("\n\n\n");
    printf("Time required for bubble sorting numbers in SLL and writing to file = %lf s\n",duration/1000);
}
