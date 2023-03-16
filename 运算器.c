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

// #include<stdio.h>
// int main()
// {

//     return 0;
// }

// #include <stdio.h>
// int f(int n)
// {
// if(n==1)
// return 1;
// return (n*f(n-1));
// }
// int main (void)
// {
// int a;
// scanf("%d",&a);
// printf("%d\n",f(a));
// }

// #include <stdio.h>
// #include <math.h>
// int fact(int n)
// {
//     int i,t=sqrt(n);
//     if(n<=1)return 0;

//     else for(i=2;i<=t;i++){
//             if(n%i==0)return 0;
//         }

//     return 1;
// }
// int main()
// {
// int n,i,a;
// scanf("%d",&n);
// for(i=0;i<n;i++)
// {
// scanf("%d",&a);
// if(fact(a)==1)
// {
// printf("Yes\n");
// }else
// {
// printf("No\n");
// }
// }
// return 0;
// }

// #include<stdio.h>
// int main()
// {
//     int n,m;
//     scanf("%d",&n);
//     m=n;
//     int a[n][n];
//     int i,j;
//     for(i=0;i<n;i++){
//         for(j=0;j<n;j++){
//             scanf("%d",&a[i][j]);
//         }
//     }

//     int h,l,x,y,tag=0;
//     i=0;
//     while(m--){
//         int max=-1,min=1000000;
//         for(j=0;j<n;j++){
//             if(a[i][j]>max){
//                 max=a[i][j];
//                 h=i;
//                 l=j;
//             }
//         }
//         for(j=l,x=0;x<n;x++){
//             if(a[x][j]<min){
//                 min=a[x][j];
//                 y=x;//hangshu
//             }
//         }

//         if(y==h){
//             printf("%d %d\n",h,l);
//             tag=1;
//         }

//         i++;
//     }

//     if(tag==0)printf("NONE");

//     return 0;
// }

// #include<stdio.h>
// int main()
// {
//     char a[1001];
//     char b[1001];
//     gets(a);

//     int i,j,x,y;
//     for(i=0,j=0;a[i]!='\0';i++,j++){
//         while(a[i]==' '&&a[i]!='\0'){
//             i++;
//             j++;
//         }if(a[i]=='\0')break;
//         while(a[j]!=' '&&a[j]!='\0'){
//             j++;
//         }
//         j--;

//         x=i;y=j;
//         for(;x<=y;y--){
//             printf("%c",a[y]);
//         }
//         printf(" ");

//         i=j;

//     }
// printf("...");

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// struct book{
// char name[31];
// double price;
// }a[10];
// int main()
// {
// int i,n,max1,min1;
// double max=-1,min=100000;
// scanf("%d",&n);
// getchar();
// for(i=0;i<n;i++)
// {
// gets(a[i].name);
// scanf("%lf",&a[i].price);
// getchar();
// if(a[i].price>max)
// {
// max=a[i].price;
// max1=i;
// }
// if(a[i].price<min)
// {
// min=a[i].price;
// min1=i;
// }
// }
// printf("%.2f %s\n",a[max1].price,a[max1].name);
// printf("%.2f %s",a[min1].price,a[min1].name);
// }

// #include<stdio.h>
// int main()
// {
//     struct student{
//         char a[6];
//         char b[11];
//         int c;
//     }x[10];

//     int n,i;
//     double sum=0;
//     scanf("%d",&n);
//     for(i=0;i<n;i++){
//         scanf("%s %s %d",x[i].a,x[i].b,&x[i].c);
//         sum+=x[i].c;
//     }

//     printf("%.2f\n",sum*1.00/n);
//     for(i=0;i<n;i++){
//         if(sum*1.00/n>x[i].c)
//             printf("%s %s\n",x[i].b,x[i].a);
//     }

//     return 0;
// }

// #include <stdio.h>
// #define MAXN 10

// struct student{
//     int num;
//     char name[20];
//     int score;
//     char grade;
// };

// int set_grade( struct student *p, int n );

// int main()
// {   struct student stu[MAXN], *ptr;
//     int n, i, count;

//     ptr = stu;
//     scanf("%d\n", &n);
//     for(i = 0; i < n; i++){
//        scanf("%d%s%d", &stu[i].num, stu[i].name, &stu[i].score);
//     }
//    count = set_grade(ptr, n);
//    printf("The count for failed (<60): %d\n", count);
//    printf("The grades:\n");
//    for(i = 0; i < n; i++)
//        printf("%d %s %c\n", stu[i].num, stu[i].name, stu[i].grade);
//     return 0;
// }

// int set_grade( struct student *p, int n )
// {
//     int i,cnt=0;
//     for(i=0;i<n;i++,p++){
//         if(p->score>=85)p->grade='A';
//         else if(p->score>=70)p->grade='B';
//         else if(p->score>=60)p->grade='C';
//         else {
//             p->grade='D';
//             cnt++;
//         }
//     }

//     return cnt;
// }

// #include<stdio.h>
// int main()
// {
//     int n;
//     scanf("%d",&n);
//     while(getchar()!='\n');
//     struct book{
//         char a[31];
//         double b;
//     }x[10],t;

//     int i,j;
//     for(i=0;i<n;i++){
//         gets(x[i].a);
//         scanf("%lf",&x[i].b);
//         while(getchar()!='\n');
//     }

//     for(i=0;i<n-1;i++){
//         for(j=0;j<n-1-i;j++){
//             if(x[j].b<x[j+1].b){
//                 t=x[j];
//                 x[j]=x[j+1];
//                 x[j+1]=t;
//             }
//         }
//     }

//     printf("%.2f,%s\n",x[0].b,x[0].a);
//     printf("%.2f,%s\n",x[n-1].b,x[n-1].a);

//     return 0;
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

// 写一个函数交换两个结构体变量
//  #include<stdio.h>
//  struct Cat{
//      char name[20];
//      char sex;
//      int age;
//      int score;
//  };

// void change(struct Cat *a,struct Cat *b)
// {
//     struct Cat change = {};
//     change = *a;
//     *a = *b;
//     *b = change;

//     printf("%s %c %d %d\n",a->name,a->sex,a->age,a->score);
//     printf("%s %c %d %d\n",b->name,b->sex,b->age,b->score);
// }

// int main()
// {

//     struct Cat cat1 = {"tom",'m',28,0};
//     struct Cat *p1 = &cat1;

//     struct Cat cat2 = {"heimao",'f',18,100};
//     struct Cat *p2 = &cat2;

//     printf("%s %c %d %d\n",cat1.name,cat1.sex,cat1.age,cat1.score);
//     printf("%s %c %d %d\n",cat2.name,cat2.sex,cat2.age,cat2.score);
//     printf("\n");

//     change(p1 , p2);

//     printf("%s %c %d %d\n",cat1.name,cat1.sex,cat1.age,cat1.score);
//     printf("%s %c %d %d\n",cat2.name,cat2.sex,cat2.age,cat2.score);

//     return 0;
// }

// #include<stdio.h>
// #include<string.h>
// int main()
// {
//     int b=99;
//     char a=b;
//     printf("%c",a);
// }

// #include<stdio.h>
// int main()
// {
//     if(-1)printf("666");
//     return 0;
// }

// #include<stdio.h>
// #include<stdlib.h>
// //  Definition for singly-linked list.
//   struct ListNode {
//       int val;
//       struct ListNode *next;
//  };

// struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
// //排除空表
//     if(list1==NULL)/*不是list1->next=NULL，因为list1指向第一个节点，而非头节点*/
//         return list2;/*list1->next=NULL表示他有且只有第一个节点（也就是有val，像[1]）*/
//     if(list2==NULL)
//         return list1;

// //创新表、新指针
//     struct ListNode* list3,*p,*q,*t;
//     list3=(struct ListNode*)malloc(sizeof(struct ListNode));
//     list3->next=NULL;
//     p=list1;
//     q=list2;
//     t=list3;

// //串
//     while(p!=NULL&&q!=NULL)
//     {
//         if(p->val < q->val){
//             t->next=p;
//             // t->val=p->val;
//             p=p->next;
//         }
//         else{
//             t->next=q;
//             // t->val=q->val;
//             q=q->next;
//         }
//         t=t->next;
//         t->next=NULL;//不要忘
//     }

// //其中一表空了，直接把另一表剩下的全部给list3
//     if(p){
//         t->next=p;
//     }
//     if(q){
//         t->next=q;
//     }

//     return list3->next;//如果是list3,则会把list3->val中的乱码输出
// }

// struct ListNode* deleteDuplicates(struct ListNode* head){
//     if(head==NULL)
//         return head;

//     struct ListNode* p,*q;
//     p=head;
//     q=head->next;

//     while(q)
//     {
//         if(p->val == q->val){
//             p->next=q->next;
//             q=q->next;
//         }
//         else{
//             p=p->next;
//             q=q->next;
//         }

//     }

//     return head;
// }

// #include <stdio.h>
// #include <stdlib.h>

// extern char **environ;

// int main()
// {
//     int i;
//     for (i = 0; environ[i] != NULL; i++)
//     {
//         puts(environ[i]);
//     }
// }

// #include<stdio.h>
// #include<stdlib.h>

// int main()
// {
//     setenv("PATH","666",1);
//     puts(getenv("PATH"));

//     exit(0);
// }

// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <stdlib.h>

// int main()
// {
//     pid_t pid;

//     printf("[%d]begin!\n", getpid());

//     pid = fork();
//     if (pid < 0)
//     {
//         perror("fork()");
//         exit(1);
//     }

//     if (pid == 0) // child
//     {
//         printf("[%d]:child is working!\n", getpid());
//     }
//     else // parent
//     {
//         printf("[%d]:parent is working!\n", getpid());
//     }

//     printf("[%d]End!\n", getpid());

//     exit(0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define L 30000000
#define R 30000200

int main()
{
    int i, j;
    int tag = 1;
    pid_t pid;

    for (i = L; i <= R; i++){
        tag = 1;  //每轮重置tag
        pid = fork(); //每个数i的判断都交给子进程来完成
                      //父进程只是用来递增i的，每次i++
        if(pid < 0){
            perror("fork()");
            exit(1);
        }

        if(pid == 0){
            for (j = 2; j < i / 2; j++){
                if (i % j == 0){
                    tag = 0; // 不是素数primer
                    break;
                }
            }
            if (tag == 1){
                printf("%d is a primer\n", i);
            }
            sleep(10000);
            exit(0); //该子进程的判断任务完成了，就退出当前子进程，使子进程都是由bash的这个子进程fork出来的
        }
    }

    int st;  //存储子进程的状态
    for(i = L; i < R; i++){
        wait(&st);
        //wait(NULL);  或者只要这个也行
    }

    exit(0);
}