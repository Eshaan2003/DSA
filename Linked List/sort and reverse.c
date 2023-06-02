/*
Author: Eshaan Shetty
Date: 02/05/2023
USN: 01FE21BEC097
*/
/*
Done using singly linked list
Constraint: maximum number of numbers written to file is defined in MAXRAND
*/
#include<stdio.h>
#define MAXRAND 1000
struct node
{
    int data;
    struct node *next;  //link
};
typedef struct node *NODE;
NODE head, newnode, temp, cur,next,prev;          //Global declaration
NODE head=NULL;

NODE getnode()      //memory allocation
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

NODE insertend(int num)     //insert a new node at the end of LL
{
    newnode=getnode();
    newnode->data=num;
    if(head==NULL           //empty LL
    {
        head=newnode;
    }
    else
    {
        temp=head;
        while(temp->next!=NULL) //Traverse till end of LL
            temp=temp->next;
        temp->next=newnode;
    }
    //printf("Entered the element %d in a node\n",newnode->data);
    return(head);
}

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
    else
    {
        printf("'%s' file opened successfully\n",readthisfile);
        int n;
        printf("Enter number of numbers to operate: ");
        scanf("%d",&n);

        for(int i=0;i<n;i++)
        {
            int buf;
            fscanf(fptr,"%d",&buf);     //reading random numbers one by one from file
            head=insertend(buf);        //loading random numbers to LL
        }
        printf("%d numbers loaded in nodes successfully\n",n);
        return n;
    }
}

NODE reverse_nodes(NODE head)
{
    printf("Reversing Linked list:\n");
    cur=head;
    prev=NULL;
    NODE fwd=head;
    while(cur!=NULL)
    {
        fwd=cur->next;      //Reversing the links
        cur->next=prev;
        prev=cur;
        cur=fwd;
    }
    head=prev;
    temp=head;
    return head;
}

NODE bubble_sort(NODE head)
{
    printf("\nBubble sorting Linked list: \n");
    cur=head;
    prev=head;
    while(cur->next!=NULL)
    {
        while(prev->next!=NULL)
        {
            if(prev->data > prev->next->data){
                int tempdata=prev->data;
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

void display_SLL(NODE start)
{
    if(start==NULL)
    {
        printf ("No data available in Linked list!");
    }
    temp=start;
    printf("Displaying numbers from nodes:\n");
    do
    {
        printf ("%d\t",temp->data);
        temp=temp->next;
    }while(temp->next!=NULL);
    printf ("%d ",temp->data);
}

void main()
{
    FILE *fptr;
    int n;
    char file_name[]="Random_nums.txt";

    generate_random_nums(fptr,file_name);
    printf("\n\n\n");

    n=read_n_nos_from_file(fptr,file_name,n);    //(file_pointer,file_name,size)
    printf("\n\n\n");

    display_SLL(head);
    printf("\n\n\n");

    head=reverse_nodes(head);
    display_SLL(head);
    printf("\n\n\n");

    head=bubble_sort(head);
    display_SLL(head);
    printf("\n\n\n");
}
