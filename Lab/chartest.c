#include<stdio.h>
#include<string.h>
int main(){
    char* str;
    char str2[10];
    str="hello";
    strcpy(str2,str);
    printf("strlen=%ld\n",strlen(str));    
    printf("strlen=%ld\n",strlen(str2));    
    for(int i=0;i<=strlen(str2);i++){
        printf("%d ",str2[i]);
    }
    printf("\n");
    char input[16]="abc,d,";
    char*p;
    /*strtok places a NULL terminator
    infront of the token,if found*/
    p=strtok(input,",");
    if(p)
        printf("%s\n",p);
        /*Asecond call to strtok using a NULL
        as the first parameter returns a pointer
        to the character following the token*/
    p=strtok(NULL,",");
    if(p)
        printf("%s\n",p);
    p=strtok(NULL,",");
    if(p==NULL)
        printf("yes\n");
    return 0;
}