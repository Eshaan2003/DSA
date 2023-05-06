#include<stdio.h>
int main()
{
    FILE *fp1;
    int n,i;
    fp1=fopen("ran.txt","w");
    printf("elements: ");
    scanf("%d",&n);

    int r[n];
    for(i=0;i<n;i++)
    {
        r[i]=rand();
        printf("\n%d",r[i]);
        fprintf(fp1,"%d\n",r[i]);
    }
   fclose(fp1);

int main()
{
    int s;
    time_t t;
    t=time(NULL);
    s=localtime(&t);
    printf("%d",s);


}
}
