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