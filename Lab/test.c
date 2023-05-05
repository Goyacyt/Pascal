#include<stdio.h>
// int mod(int a,int b)
// {
//     return a -(a / b) * b;
// }

// int IsLeap(int y)
// {
//     if(mod(y, 400) == 0 || mod(y, 4) == 0 && mod(y, 100) != 0)
//          return 1;
//     else
//          return 0;
// }

// int main()
// {
//     int year, i, dayofweek, motherday, days=0, leap=0;
//     int monthdays[5];
//     monthdays[0] = 0;
//     monthdays[1] = 31;
//     monthdays[2] = 28;
//     monthdays[3] = 31;
//     monthdays[4] = 30;
//     //year = read();
//     scanf("%d",&year);
//     i = 1900;
//     while(i < year)
//     {
//         if(IsLeap(i))
//             days = days + 366;
// 	else
//             days = days + 365;
//         i = i + 1;
// 	} 
//     printf("days1=%d\n",days);
// 	if(IsLeap(year))
// 		monthdays[2] = 29;
//         i = 1;
//     printf("monthdays[2]=%d\n",monthdays[2]);
// 	while(i < 5)
// 	{
// 	    days = days + monthdays[i];
//             i = i + 1;
// 	}
//     printf("days2=%d\n",days);
// 	dayofweek = mod(days, 7);
// 	motherday = 14 - dayofweek;
// 	//write(5);
//     //    write(motherday);
//     //printf("5\n");
//     printf("dayofweek=%d\n",dayofweek);
//     printf("motherday=%d\n",motherday);
// 	return 0;
// } 


// int main(){
//     int a=1;
//     if(a==1||a==0&&a!=1)
//         printf("yes1\n");
//     if(a==1&&a==0||a==1)
//         printf("yes2\n");
//     return 0;
// }


int main(){
    int i_L2787 = -348375089;
    printf("c=%d\n",i_L2787);
    return 0;
}