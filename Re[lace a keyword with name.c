#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char str[10];
char t,x;
int i,n=0;
int main()
{
printf("enter your name:\n");
    gets(str);
    FILE*fp1;
    FILE*fp2;
    fp1=fopen("black.txt","r");
    if(fp1==NULL){
    printf("file not opened");                  //checking if file is opened
    exit(0);
}
    fp2=fopen("orange.txt","w");
    if(fp2==NULL){
    printf("file not opened");                  //checking if file is opened
    exit(0);
}
printf("enter a letter alphabet\n");
scanf("%c",&t);
while(!feof(fp1)){
fscanf(fp1,"%c",&x);
if(x==t){
    fprintf(fp2,"%s",str);
    n++;
}
else{
    fprintf(fp2,"%c",x);
}
}
if(n==0){
    printf("/ncharacter not found");
}
fclose(fp1);
fclose(fp2);
}
