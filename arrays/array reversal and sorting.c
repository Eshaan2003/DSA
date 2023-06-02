/*
Author:Eshaan Shetty
Date: 24/04/2023
USN:01FE21BEC097
*/

#include<stdio.h>
int array[1000];

int read_n_nos_from_file(FILE* fptr,char readthisfile[],int arr[],int n)    //(file_pointer,file_name,store_in_this_array,size_of_array)
{
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
        fscanf(fptr,"%d",&n);       //number of random numbers to be read
        printf("%d\n",n);

        for(int i=0;i<n;i++)        //reading random numbers
        {
             fscanf(fptr,"%d",&arr[i]);
        }
        return n;
    }
    fclose(fptr);
}

void write_n_nos_to_file(FILE* fptr,char writethisfile[],int arr[],int n)       //(file_ptr,file_name,source_array,array_size)
{
    fptr=fopen(writethisfile,"w");
    if(fptr==NULL)
    {
        printf("'%s' File creation error!\n",writethisfile);
    }
    else
    {
        printf("'%s' File created successfully\n",writethisfile);
        for(int i=0;i<n;i++)        //copy array to file
        {
            fprintf(fptr,"%d\n",arr[i]);
        }
    }
    fclose(fptr);
}

void display_array(int arr[], int n)
{
        for(int i=0;i<n;i++)
        {
            printf("%d\t",arr[i]);
        }
    printf("\n\n\n");
}

void reverse_nos_array(int arr[],int n)     //(array,size)
{
    printf("reverse array: \n",n);
    for(int i=0;i<n/2;i++)
    {
        int temp=arr[i];        //swap 1st and last elements
        arr[i]=arr[n-i-1];
        arr[n-i-1]=temp;
    }
}

void bubble_sort(int arr[],int n)
{
    printf("Bubble sort array: \n");
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])     //Ascending order
            {
                int temp=arr[j];   //swap
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void main()
{
    FILE *fptr;
    int n;
    n=read_n_nos_from_file(fptr,"file11.txt",array,n);  //(file_pointer,file_name,storing_array,array_size)
    display_array(array,n);

    reverse_nos_array(array,n);       //(array,size)
    write_n_nos_to_file(fptr,"Reversed_array.txt",array,n);       //(file_ptr,file_name,source_array,array_size)
    display_array(array,n);

    bubble_sort(array,n);
    write_n_nos_to_file(fptr,"Sorted_array.txt",array,n);          //(file_ptr,file_name,source_array,array_size)
    display_array(array,n);
}
