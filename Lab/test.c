#include<stdio.h>
#include <stdlib.h>
struct TEST{
    int X;
    float Y;
}test;

struct TEST2{
    int X;
    float Y;
}test2;

int TEST(float a){
    return a;
}
int main(){
    struct TEST* tt=(struct TEST*)malloc(sizeof(struct TEST));
    tt->X=2;
    int a=0;
    
    float c=1.4;
        
}