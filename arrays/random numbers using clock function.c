/*
Author:Eshaan Shetty
Date: 24/04/2023
USN:01FE21BEC097
*/
#include<stdio.h>
#include<time.h>
#define MAX 10000
void main()
{
    clock_t init, fin;
    init=clock();       //mark start time
    int n,num[MAX];
    double timespent=0.0;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        num[i]=rand()%200;
        printf("%d\t",num[i]);
    }
    printf("\n");
    FILE *fptr;
    fptr=fopen("Random_number.txt","w");
    if(fptr==NULL)
    {
        printf("Unable to create file\n");
    }
    else
    {
        printf("File for random number created successfully\n");
        for(int i=0;i<n;i++)
            fprintf(fptr,"%d\n",num[i]);
    }
    fin=clock();        //Mark end time
    timespent=fin-init; //difference gives time lapsed
    printf("time taken=%.3lf ms or %.3lf secs\n",timespent,timespent/1000);
}
