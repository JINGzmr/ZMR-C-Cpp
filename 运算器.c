// #include<stdio.h>
// #include<string.h>
// void mycat(char*a,char*b);
// int main()
// {
//   char a[15]="hello ";
//   char b[]="world!";
//   mycat(a,b);
//   printf("%s\n",a);

//   return 0;
// }
// void mycat(char*a,char*b)
// {
//   int n=strlen(a);
//   int i,j;
//   for(i=n,j=0;j<strlen(b);i++,j++){
//     a[i]=b[j];
//   }
//   a[i]='\0';
// //   int c=sqrt(9);
// }

// #include<math.h>
// #include<stdio.h>
// int main()
// {
//     int a=sqrt(9);
//     printf("%d\n",a);
//     return 0;
// }

// #include<stdio.h>
// #include<math.h>
// #include<string.h>
// int ss(int a);
// int main()
// {   
//     int i;
//     // printf("%d\n",ss(2));
//     int a[150]={0};
//     char b[100]="";
//     gets(b);
//     int n=strlen(b);
//     for(i=0;i<n;i++){
//         a[b[i]]++;
//     }
//     int max=0,min=100;
//     for(i=0;i<150;i++){
//         if(a[i]!=0){
//             if(a[i]>max)max=a[i];
//             if(a[i]<min)min=a[i];
//         }
//     }
//     int x=max-min;
//     printf("%d %d\n",max,min);
//     if(ss(x)){
//         printf("Lucky Word\n%d",x);
//     }
//     else printf("No Answer\n%d",x);

//     return 0;
// }
// int ss(int a)
// {
//     int i,t,tag=1;
//     t=sqrt(a);
//     if(a==1||a==0)tag=0;
//     else for(i=2;i<=t;i++){
//             if(a%i==0){
//                 tag=0;
//                 break;
//             }
//     }
//     // printf("%d",tag);
//     return tag;
// }

// #include<stdio.h>
// #include<math.h>
// int ss(int a);
// int main()
// {
//     int n,a;
//     scanf("%d",&n);
//     int i;
//     for(i=0;i<n;i++){
//         scanf("%d",&a);
//         if(ss(a))printf("Yes\n");
//         else printf("No\n");
//     }
    
//     return 0;
// }
// int ss(int a)
// {
//     int i,y,tag=1;
//     y=sqrt(a);
//     if(a==1)tag=0;
//     for(i=2;i<=y;i++){
//         if(a%i==0){
//             tag=0;
//             break;
//         }
//     }
    
    
//     return tag;
// }


// #include<stdio.h>
// double fact(int a,int b);
// int main()
// {
//     int m,n;
//     scanf("%d %d",&m,&n);
//     double x=fact(m,n);
//     printf("result = %d",x);
    
    
//     return 0;
// }
// double fact(int a,int b)
// {
//     double x=1,y=1,z=1,i;
//     printf("%d\n\n",z);
//     for(i=a;i>0;i--){
//         x*=i;
//     }
//     for(i=b;i>0;i--){
//         y*=i;
//     }
//     for(i=b-a;i>0;i--){
//         z*=i;
//         printf("%d\n",z);
        
//     }
//     double c=x/(y*z);
// //     printf("%d %d %d\n",x,y,z);
    
//     return c;
// }



// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <string.h>
// int main(){   
//     int bir[4];
//     int year, n;   
//     scanf("%d %d",&year, &n);
//     int i, count = 0;   
//     for(i=year; i<3020; i++){      
//         count = 1;       
//         bir[0] = i/1000;      
//         bir[1] = i/100%10;       
//         bir[2] = i/10%10;       
//         bir[3] = i%10;
//         if(bir[0] != bir[1] && bir[0] != bir[2] && bir[0] != bir[3]) count++;      
//         if(bir[1] != bir[2] && bir[1] != bir[3]) count++;        
//         if(bir[2] != bir[3]) count++;
//         if(count == n) break;  
// }   
//         printf("%d %04d", i-year, i);      
//         // system("pause");    
//         return 0;
// }


// #include <stdio.h>
// int main()
// {
//     double eps;
//     scanf("%le", &eps);
//     double sum=1;
//     double temp=1;
//     for(int i=1;temp>eps;i++)
// 	{
//         temp = temp*i/(2*i+1);
//         sum += temp;
//     }
//     printf("PI = %.5f\n", 2*sum);
//     return 0;
// }


// #include<stdio.h>
// #include<math.h>
// int main()
// {
//     double x1,y1;
//     double x2,y2;
//     double x3,y3;
//     scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3);
//     double a,b,c,d=0.0;
//     int i;
   
//         a=pow(x2-x1,2);
//         b=pow(y2-y1,2);
//         c=sqrt(a+b);
//         d+=c;

//         a=pow(x3-x1,2);
//         b=pow(y3-y1,2);
//         c=sqrt(a+b);
//         d+=c;
    
//         a=pow(x2-x3,2);
//         b=pow(y2-y3,2);
//         c=sqrt(a+b);
//         d+=c;
    
//     printf("%.2f",d);

//     return 0;
// }


// #include<stdio.h>
// int main()
// {
//     int n,m;
//     scanf("%d %d",&n,&m);
//     int i,j,k,l,max=0,t,sum=0;
//     int a[20]={0};
//     for(i=0;i<n;i++){
//         sum=0;
//         for(j=0;j<m;j++){
//             scanf("%d",&a[j]);
//             sum+=a[j];
//         }
//         for(k=0;k<m-1;k++){
//             for(l=0;l<m-1-k;l++){
//                 if(a[l]>a[l+1]){
//                     int t=a[l];
//                     a[l]=a[l+1];
//                     a[l+1]=t;
//                 }
//             }
//         }
//         int sum=0;
//         for(k=1;k<m-1;k++){
//             sum+=a[k];
//         }
//         // printf("%d\n",sum);
//         // sum=sum-a[0]-a[m-1];
//         if(sum>max){
//             max=sum;
//             t=i;
//         }
//     }
//     // printf("%d %d\n",max,t);
//     printf("%.2f\n",(double)max/(m-2));

//     return 0;
// }


#include<stdio.h>
int main()
{


    return 0;
}
