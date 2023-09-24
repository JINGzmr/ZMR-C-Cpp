// #include<stdio.h>
// #include<string.h>
// void mycat(char*a,char*b);
// int main()
// {
//   char arr_a[15]="hello ";
//   char arr_b[]="world!";
//   mycat(a,b);
//   printf("%s\n",a);

//   return 0;
// }
// void mycat(char*a,char*b)
// {
//   int n=strlen(a);
//   int i,j;
//   for(i=n,j=0;j<strlen(b);i++,j++){
//     arr_a[i]=arr_b[j];
//   }
//   arr_a[i]='\0';
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
//     int arr_a[150]={0};
//     char arr_b[100]="";
//     gets(b);
//     int n=strlen(b);
//     for(i=0;i<n;i++){
//         arr_a[arr_b[i]]++;
//     }
//     int max=0,min=100;
//     for(i=0;i<150;i++){
//         if(arr_a[i]!=0){
//             if(arr_a[i]>max)max=arr_a[i];
//             if(arr_a[i]<min)min=arr_a[i];
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
//     int arr_a[20]={0};
//     for(i=0;i<n;i++){
//         sum=0;
//         for(j=0;j<m;j++){
//             scanf("%d",&arr_a[j]);
//             sum+=arr_a[j];
//         }
//         for(k=0;k<m-1;k++){
//             for(l=0;l<m-1-k;l++){
//                 if(arr_a[l]>arr_a[l+1]){
//                     int t=arr_a[l];
//                     arr_a[l]=arr_a[l+1];
//                     arr_a[l+1]=t;
//                 }
//             }
//         }
//         int sum=0;
//         for(k=1;k<m-1;k++){
//             sum+=arr_a[k];
//         }
//         // printf("%d\n",sum);
//         // sum=sum-arr_a[0]-arr_a[m-1];
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
//     int arr_a[n][n];
//     int i,j;
//     for(i=0;i<n;i++){
//         for(j=0;j<n;j++){
//             scanf("%d",&arr_a[i][j]);
//         }
//     }

//     int h,l,x,y,tag=0;
//     i=0;
//     while(m--){
//         int max=-1,min=1000000;
//         for(j=0;j<n;j++){
//             if(arr_a[i][j]>max){
//                 max=arr_a[i][j];
//                 h=i;
//                 l=j;
//             }
//         }
//         for(j=l,x=0;x<n;x++){
//             if(arr_a[x][j]<min){
//                 min=arr_a[x][j];
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
//     char arr_a[1001];
//     char arr_b[1001];
//     gets(a);

//     int i,j,x,y;
//     for(i=0,j=0;arr_a[i]!='\0';i++,j++){
//         while(arr_a[i]==' '&&arr_a[i]!='\0'){
//             i++;
//             j++;
//         }if(arr_a[i]=='\0')break;
//         while(arr_a[j]!=' '&&arr_a[j]!='\0'){
//             j++;
//         }
//         j--;

//         x=i;y=j;
//         for(;x<=y;y--){
//             printf("%c",arr_a[y]);
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
// }arr_a[10];
// int main()
// {
// int i,n,max1,min1;
// double max=-1,min=100000;
// scanf("%d",&n);
// getchar();
// for(i=0;i<n;i++)
// {
// gets(arr_a[i].name);
// scanf("%lf",&arr_a[i].price);
// getchar();
// if(arr_a[i].price>max)
// {
// max=arr_a[i].price;
// max1=i;
// }
// if(arr_a[i].price<min)
// {
// min=arr_a[i].price;
// min1=i;
// }
// }
// printf("%.2f %s\n",arr_a[max1].price,arr_a[max1].name);
// printf("%.2f %s",arr_a[min1].price,arr_a[min1].name);
// }

// #include<stdio.h>
// int main()
// {
//     struct student{
//         char arr_a[6];
//         char arr_b[11];
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
//         char arr_a[31];
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

// struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode*
// list2){
// //排除空表
//     if(list1==NULL)/*不是list1->next=NULL，因为list1指向第一个节点，而非头节点*/
//         return
//         list2;/*list1->next=NULL表示他有且只有第一个节点（也就是有val，像[1]）*/
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

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>

// #define L 30000000
// #define R 30000200

// int main()
// {
//     int i, j;
//     int tag = 1;
//     pid_t pid;

//     for (i = L; i <= R; i++){
//         tag = 1;  //每轮重置tag
//         pid = fork(); //每个数i的判断都交给子进程来完成
//                       //父进程只是用来递增i的，每次i++
//         if(pid < 0){
//             perror("fork()");
//             exit(1);
//         }

//         if(pid == 0){
//             for (j = 2; j < i / 2; j++){
//                 if (i % j == 0){
//                     tag = 0; // 不是素数primer
//                     break;
//                 }
//             }
//             if (tag == 1){
//                 printf("%d is a primer\n", i);
//             }
//             sleep(10000);
//             exit(0);
//             //该子进程的判断任务完成了，就退出当前子进程，使子进程都是由bash的这个子进程fork出来的
//         }
//     }

//     int st;  //存储子进程的状态
//     for(i = L; i < R; i++){
//         wait(&st);
//         //wait(NULL);  或者只要这个也行
//     }

//     exit(0);
// }

// #include<stdio.h>
// // #include<math.h>
// int main()
// {
//     int n;
//     scanf("%d",&n);
//     int i,j;
//     int
//     sum=1,count=0,max=0,l=0;//sum多个因子的乘积,count连续个数,max最大连续个数
//     int tag=0;
//     for(i=2;i<n/2;i++){
//         count=0;
//         tag=0;
//         sum=1;
//         for(j=i;j<n/2;j++){
//             if(sum<n){
//                 sum*=j;
//                 count++;
//             }else if(sum==n){
//                 tag=1;//说明是因为sum==n而出循环的，可以记入
//                 break;
//             }else
//             break;
//         }
//         if(count>max &&
//         tag==1){//如果连续个数大于之前的，且因为sum==n而出循环的，则将开头元素记下来
//             l=i;
//             max=count;
//         }
//     }
//     printf("%d\n",max);
//     for(i=l;i<=max;i++){
//         printf("%d",i);
//         if(i!=max){
//             printf("*");
//         }
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// #define NUM_THREADS 2

// int global_variable = 0;

// void *worker_thread(void *threadarg) {
//     printf("Worker thread started.\n");
//     while (1) {
//         printf("Worker thread updating global variable.\n");
//         global_variable++;
//         printf("Worker thread finished.\n");
//         break;
//     }
//     printf("Main thread waiting for worker thread to finish.\n");
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t threads[NUM_THREADS];
//     int exit_code = 0;
//     for (int i = 0; i < NUM_THREADS; i++) {
//         printf("Main thread started.\n");
//         printf("Creating thread %d ...\n", i + 1);
//         exit_code = pthread_create(&threads[i], NULL, worker_thread, (void
//         *)(i + 1)); if (exit_code != 0) {
//             printf("Failed to create thread %d!\n", i + 1);
//             exit(-1);
//         }
//         printf("Thread %d created.\n", i + 1);
//     }
//     for (int i = 0; i < NUM_THREADS; i++) {
//         printf("Main thread waiting for thread %d to finish.\n", i + 1);
//         pthread_join(threads[i], NULL);
//         printf("Thread %d joined.\n", i + 1);
//     }
//     printf("Main thread finished.\n");
//     printf("Global variable = %d.\n", global_variable);
//     exit(0);
// }

// struct thrd
// {
//     int var;
//     char str[128];
// };
// void *tfn(void *arg)
// {
//     struct thrd *tval;

//     tval = malloc(sizeof(tval));
//     tval->var=100;
//     strcpy(tval->str,"hello thread");

//     return (void *)tval;
// }

// void *tfn(void *arg)
// {
//     struct thrd tval;

//     tval.var=100;
//     strcpy(tval.str,"hello thread");

//     return (void *)&tval;
// }

// #include<stdio.h>
// #include<string.h>
// int main()
// {
//     int arr_a[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
//     char x[11]={1,0,'X',9,8,7,6,5,4,3,2};
//     int n,m=0;
//     char arr_b[100][18]={0};
//     char c[100][18]={0};
//     scanf("%d",&n);
//     int i,j,cnt=0;
//     for(i=0;i<n;i++){
//         scanf("%s",arr_b[i]);
//     }

//     for(i=0;i<n;i++){
//         m=0;
//         int tag=0;
//         for(j=0;j<17;j++){
//             m+=(arr_b[i][j]-'0')*arr_a[j];
//             if(arr_b[i][j]>'9'&&arr_b[i][j]<'0'){
//                 tag=1;
//                 break;
//             }
//         }
//         m=(m)%11;
//         if(arr_b[i][j]!=x[m]||tag==1){
//             strcpy(c[cnt++],arr_b[i]);
//         }
//     }

//     if(cnt==0){
//         printf("All passed");
//     }else{
//         for(i=0;i<cnt;i++){
//             printf("%s\n",c[cnt]);
//         }
//     }

//     return 0;
// }

// #include<stdio.h>
// int main()
// {
//     int arr_a[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
//     char x[11]={'1','0','X','9','8','7','6','5','4','3','2'};
//     int n,m=0;
//     char arr_b[100][19]={""};
//     char c[100][19]={""};
//     scanf("%d",&n);
//     int i,j,cnt=0;
// //     getchar();

//     for(i=0;i<n;i++){
//         scanf("%s",arr_b[i]);
// //         gets(arr_b[i]);
//     }
//     for(i=0;i<n;i++){
//         m=0;
//         int tag=0;
//         for(j=0;j<17;j++){
//             if(arr_b[i][j]>'9'&&arr_b[i][j]<'0'){
//                 tag=1;
//                 break;
//             }
//             m+=(arr_b[i][j]-'0')*arr_a[j];
//         }
//         m=m%11;
//         if(arr_b[i][j]!=x[m]||tag==1){
//             strcpy(c[cnt++],arr_b[i]);
//         }
//     }
//     if(cnt==0){
//         printf("All passed");
//     }else{

//         for(i=0;i<cnt;i++){
//             printf("%s\n",c[i]);
//         }
//     }
// //        for(i=0;i<n;i++){
// //             printf("%s\n",arr_b[i]);
// //         }

//     return 0;
// }

// #include<stdio.h>

// int main()
// {
//     int n;
//     scanf("%d",&n);
//     int m=n;
//     int i;
//     int arr_b[100]={0};
//     int arr_a[100][1000]={0};

//     while(m--)
//     {
//         int k;
//         scanf("%d",&k);
//         arr_b[n-m-1]=k;

//         for(i=0;i<k;i++){
//             int x;
//             scanf("%d",&x);
//             arr_a[n-m-1][i]=x;
//         }
//     }

//     scanf("%d",&m);
//     int c[10000]={0};
//     for(i=0;i<m;i++){
//         int id;
//         scanf("%d",&id);
//         c[i]=id;
//     }

//     int x,y;

//     int tag=0;
//     for(i=0;i<m;i++){
// //         tag=0;

//         for(x=0;x<n;x++){
//             for(y=0;y<arr_b[i];y++){
//                 if(c[i]==arr_a[x][y]&&arr_b[i]>1)c[i]=-1;
//             }
//         }
//     }

//     for(i=0;i<m;i++){
//         if(c[i]!=-1){
//             printf("%d ",c[i]);
//                 tag=1;
//             }
//         if(tag==0)printf("No one is handsome");
//     }

//     return 0;
// }

// #include<stdio.h>
// int main()
// {
//     int n;//行数
//     scanf("%d",&n);
//     char arr_a[10000]="";
//     getchar();
//     gets(a);

//     char arr_b[100][1000]={""};
//     int x=strlen(a);
//     int i,j;
//     int m=x/n;//列数，五列m=4
//     int hang=0;
//     int nn=0;//arr_a[]的指针
//     for(i=m;i>=0;i--){
//         for(j=0;j<n;j++){
//             arr_b[j][i]=arr_a[nn++];
//         }
//     }

//     for(i=0;i<n;i++){
//         for(j=0;j<=m;j++){
//             printf("%c",arr_b[i][j]);
//         }
//         printf("\n");
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <string.h>

// int main() {
//     char str1[20] = "Hello";
//     char str2[20];
//     strcpy(str2, str1); // 将 str1 复制到 str2 中
//     printf("str1 = %s\n", str1);
//     printf("str2 = %s\n", str2);
//     return 0;
// }

// #include <stdio.h>
// #include <string.h>

// int main() {
//     char str1[] = "Hello, world!";
//     char str2[] = "Hello, there!";
//     int n = 8;
//     int result = strncmp(str1, str2, n);
//     if (result < 0) {
//         printf("str1 is less than str2\n");
//     }
//     else if (result == 0) {
//         printf("str1 is equal to str2\n");
//     }
//     else {
//         printf("str1 is greater than str2\n");
//     }
//     return 0;
// }

// #include<stdio.h>
// int main()
// {
//     char arr_a[5]={0};
//     scanf("%s",a);

//     printf("%s",a);

//     return 0;
// }

// #include <stdio.h>
// #include <pthread.h>

// pthread_mutex_t var1_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t var2_mutex = PTHREAD_MUTEX_INITIALIZER;
// int var1 = 0;
// int var2 = 0;

// void* thread1(void* arg) {
//     pthread_mutex_lock(&var1_mutex);
//     printf("线程1获得了var1_mutex锁。\n");

//     // 模拟一些工作
//     sleep(1);

//     // 尝试获取 var2_mutex 锁
//     pthread_mutex_lock(&var2_mutex);
//     printf("线程1获得了var2_mutex锁。\n");

//     // 对 var1 和 var2 进行一些操作
//     var1++;
//     var2++;

//     // 释放锁
//     pthread_mutex_unlock(&var2_mutex);
//     pthread_mutex_unlock(&var1_mutex);

//     return NULL;
// }

// void* thread2(void* arg) {
//     pthread_mutex_lock(&var2_mutex);
//     printf("线程2获得了var2_mutex锁。\n");

//     // 模拟一些工作
//     sleep(1);

//     // 尝试获取 var1_mutex 锁
//     pthread_mutex_lock(&var1_mutex);
//     printf("线程2获得了var1_mutex锁。\n");

//     // 对 var1 和 var2 进行一些操作
//     var1++;
//     var2++;

//     // 释放锁
//     pthread_mutex_unlock(&var1_mutex);
//     pthread_mutex_unlock(&var2_mutex);

//     return NULL;
// }

// int main() {
//     pthread_t t1, t2;

//     // 创建两个线程
//     pthread_create(&t1, NULL, thread1, NULL);
//     pthread_create(&t2, NULL, thread2, NULL);

//     // 等待线程结束
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     printf("%d %d",var1,var2);

//     return 0;
// }

// #include<stdio.h>
// int main()
// {
//     int arr_a[200][300];
//     printf("%d",arr_a[100][200]);

// }

// #include <stdio.h>
// struct Term {
//     int ccficient;
//     int exponent;
// };

// int main() {
//     int n1, n2;
//     scanf("%d", &n1);

//     struct Term poly1[n1];

//     for (int i = 0; i < n1; i++) {
//         scanf(" (%d,%d)", &poly1[i].ccficient, &poly1[i].exponent);
//     }
//     scanf("%d", &n2);

//     struct Term poly2[n2];

//     for (int i = 0; i < n2; i++) {
//         scanf(" (%d,%d)", &poly2[i].ccficient, &poly2[i].exponent);
//     }

//     // 执行多项式相加运算
//     int result_size = n1 + n2;  // 结果多项式的最大项数
//     struct Term result[result_size];
//     int i = 0, j = 0, k = 0;

//     while (i < n1 && j < n2) {
//         if (poly1[i].exponent < poly2[j].exponent) {
//             result[k++] = poly1[i++];
//         } else if (poly1[i].exponent > poly2[j].exponent) {
//             result[k++] = poly2[j++];
//         } else {
//             // 指数相同，系数相加
//             result[k].exponent = poly1[i].exponent;
//             result[k].ccficient = poly1[i].ccficient + poly2[j].ccficient;
//             i++;
//             j++;
//             k++;
//         }
//     }

//     // 处理剩余的项
//     while (i < n1) {
//         result[k++] = poly1[i++];
//     }

//     while (j < n2) {
//         result[k++] = poly2[j++];
//     }

//     for (int i = 0; i < k; i++) {
//         if (i == 0) {
//             printf("%d", result[i].ccficient);
//         } else {
//             if (result[i].ccficient > 0) {
//                 printf("+%d", result[i].ccficient);
//                 if (result[i].exponent > 0) {
//                     printf("X");
//                     if (result[i].exponent > 1) {
//                         printf("^%d", result[i].exponent);
//                     }
//                 }
//             }
//         }
//     }

//     printf("\n");

//     return 0;
// }

// #include <stdio.h>

// struct Term {
//     int ccficient;
//     int exponent;
// };

// int main() {
//     int n1, n2;
//     scanf("%d", &n1);

//     struct Term poly1[n1];

//     for (int i = 0; i < n1; i++) {
//         scanf(" (%d,%d)", &poly1[i].ccficient, &poly1[i].exponent);
//     }

//     scanf("%d", &n2);

//     struct Term poly2[n2];

//     for (int i = 0; i < n2; i++) {
//         scanf(" (%d,%d)", &poly2[i].ccficient, &poly2[i].exponent);
//     }

//     // 执行多项式相减运算
//     int result_size = n1 + n2; // 结果多项式的最大项数
//     struct Term result[result_size];
//     int i = 0, j = 0, k = 0;

//     while (i < n1 && j < n2) {
//         if (poly1[i].exponent < poly2[j].exponent) {
//             result[k++] = poly1[i++];
//         } else if (poly1[i].exponent > poly2[j].exponent) {
//             result[k].exponent = poly2[j].exponent;
//             result[k].ccficient = -poly2[j].ccficient;
//             j++;
//             k++;
//         } else {
//             // 指数相同，系数相减
//             int diff_ccficient = poly1[i].ccficient - poly2[j].ccficient;
//             if (diff_ccficient != 0) {
//                 result[k].exponent = poly1[i].exponent;
//                 result[k].ccficient = diff_ccficient;
//                 k++;
//             }
//             i++;
//             j++;
//         }
//     }

//     // 处理剩余的项
//     while (i < n1) {
//         result[k++] = poly1[i++];
//     }

//     while (j < n2) {
//         result[k].exponent = poly2[j].exponent;
//         result[k].ccficient = -poly2[j].ccficient;
//         j++;
//         k++;
//     }

//     for (int i = 0; i < k; i++) {
//         if (i == 0) {
//             printf("%d", result[i].ccficient);
//         } else {
//             if (result[i].ccficient > 0) {
//                 printf("+%d", result[i].ccficient);
//             } else {
//                 printf("%d", result[i].ccficient);
//             }
//         }

//         if (result[i].exponent > 0) {
//             printf("X");
//             if (result[i].exponent > 1) {
//                 printf("^%d", result[i].exponent);
//             }
//         }
//     }

//     printf("\n");

//     return 0;
// }

// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>

// typedef struct node {
//     int cc;
//     int ee;
//     struct node *next;
// }Node, *List;

// List Creat(int i) {
//     List head;
//     head = (List)malloc(sizeof(Node));
//     List pre, pnew;
//     pre = head;
//     char a,b;
//     for(int j = 0; j <= i; j++) {
//         pnew = (List)malloc(sizeof(Node));
//         scanf("%c%d,%d%c", &a, &pnew->cc, &pnew->ee, &b);
//         pre -> next = pnew;
//         pre = pnew;
//     }
//     return head;
// }

// void Print(List head) {
//     List q = head->next->next;
//     int flag = 1;
//     if(!q) {
//         putchar('0');
//         printf("\n");
//         return;
//     }
//     while(q) {
//         if(q->cc > 0 && flag != 1) {
//             putchar('+');
//         }
//         if(q->cc != 1 && q->cc != -1) {
//             printf("%d", q->cc);
//             if(q->ee == 1) {
//                 putchar('X');
//             } else if (q->ee) {
//                 printf("X^%d", q->ee);
//             }
//         } else {
//             if(q->cc == 1) {
//                 if(!q->ee) {
//                     putchar('1');
//                 } else if (q->ee == 1) {
//                     putchar('X');
//                 } else {
//                     printf("X^%d", q->ee);
//                 }
//             }
//             if(q->cc == -1) {
//                 if(!q->ee) {
//                     printf("-1");
//                 } else if(q->ee == 1) {
//                     printf("-X");
//                 } else {
//                     printf("-X^%d", q->ee);
//                 }
//             }
//         }
//         q = q->next;
//         flag++;
//     }
// }

// List Plus(List head1, List head2) {
//     List pre = NULL, p = NULL, qre = NULL, q = NULL;
//     pre = head1->next;
//     p = head1->next->next;
//     qre = head2->next;
//     q = head2->next->next;
//     int index = 1;
//     while (p != NULL) {
//         if (q == NULL) {
//             return head1;
//         }
//         if (p->ee == q->ee) {
//             p->cc = p->cc - q->cc;
//             if (p->cc == 0) {
//                 pre->next = p->next;
//                 free(p);
//                 if (pre) {
//                     p = pre->next;
//                 } else {
//                     p = NULL;
//                 }
//                 qre->next = q->next;
//                 free(q);
//                 if (qre) {
//                     q = qre->next;
//                 } else {
//                     q = NULL;
//                 }
//             } else {
//                 pre = p;
//                 p = p->next;
//                 qre->next = q->next;
//                 free(q);
//                 if (qre) {
//                     q = qre->next;
//                 } else {
//                     q = NULL;
//                 }
//             }
//         } else if (p->ee > q->ee) {
//             q->cc = -q->cc;
//             qre->next = q->next;
//             q->next = p;
//             pre->next = q;
//             pre = q;
//             q = qre->next;
//         } else if (q->ee > p->ee && p->next &&q->ee < (p->next)->ee) {
//             q->cc = -q->cc;
//             qre->next = q->next;
//             pre = p;
//             p = p->next;
//             q->next = p;
//             pre->next = q;
//             pre = q;
//             q = qre->next;
//         } else if (q->ee > p->ee && p->next && q->ee >= (p->next)->ee) {
//             pre = p;
//             p = p->next;
//         } else {
//             pre = p;
//             break;
//         }
//         index ++;
//     }
//     if (q) {
//         pre->next = q;
//         List qq = q;
//         while(qq) {
//             qq->cc = - qq->cc;
//             qq = qq->next;
//         }
//     }
//     return head1;
// }

// int main() {
//     int i1, i2;
//     List head1, head2;
//     scanf("%d", &i1);
//     head1 = Creat(i1);
//     scanf("%d", &i2);
//     head2 = Creat(i2);
//     List head = Plus(head1, head2);
//     Print(head);
// }

// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>

// typedef struct node {
//     int cc;
//     int ee;
//     struct node *next;
// }Node, *List;

// List Creat(int i) {
//     List head;
//     head = (List)malloc(sizeof(Node));
//     List pre, pnew;
//     pre = head;
//     char a,b;
//     for(int j = 0; j <= i; j++) {
//         pnew = (List)malloc(sizeof(Node));
//         scanf("%c%d,%d%c", &a, &pnew->cc, &pnew->ee, &b);
//         pre -> next = pnew;
//         pre = pnew;
//     }
//     return head;
// }

// void Print(List head) {
//     List q = head->next->next;
//     int flag = 1;
//     if(!q) {
//         putchar('0');
//         printf("\n");
//         return;
//     }
//     while(q) {
//         if(q->cc > 0 && flag != 1) {
//             putchar('+');
//         }
//         if(q->cc != 1 && q->cc != -1) {
//             printf("%d", q->cc);
//             if(q->ee == 1) {
//                 putchar('X');
//             } else if (q->ee) {
//                 printf("X^%d", q->ee);
//             }
//         } else {
//             if(q->cc == 1) {
//                 if(!q->ee) {
//                     putchar('1');
//                 } else if (q->ee == 1) {
//                     putchar('X');
//                 } else {
//                     printf("X^%d", q->ee);
//                 }
//             }
//             if(q->cc == -1) {
//                 if(!q->ee) {
//                     printf("-1");
//                 } else if(q->ee == 1) {
//                     printf("-X");
//                 } else {
//                     printf("-X^%d", q->ee);
//                 }
//             }
//         }
//         q = q->next;
//         flag++;
//     }
// }

// List CopyList (List head) {
//     List newHead = (List)malloc(sizeof(Node));
//     newHead->next = NULL;
//     List p = head->next;
//     List p2 = newHead;
//     while (p) {
//         List new = (List)malloc(sizeof(Node));
//         new->cc = p->cc;
//         new->ee = p->ee;
//         p2->next = new;
//         p2 = new;
//         p = p->next;
//     }
//     p2->next = NULL;
//     return newHead;
// }

// List Plus(List head1, List head2) {
//     List pre = NULL, p = NULL, qre = NULL, q = NULL;
//     pre = head1->next;
//     p = head1->next->next;
//     qre = head2->next;
//     q = head2->next->next;
//     int index = 1;
//     while (p != NULL) {
//         if (q == NULL) {
//             return head1;
//         }
//         if (p->ee == q->ee) {
//             p->cc = p->cc + q->cc;
//             if (p->cc == 0) {
//                 pre->next = p->next;
//                 free(p);
//                 if (pre) {
//                     p = pre->next;
//                 } else {
//                     p = NULL;
//                 }
//                 qre->next = q->next;
//                 free(q);
//                 if (qre) {
//                     q = qre->next;
//                 } else {
//                     q = NULL;
//                 }
//             } else {
//                 pre = p;
//                 p = p->next;
//                 qre->next = q->next;
//                 free(q);
//                 if (qre) {
//                     q = qre->next;
//                 } else {
//                     q = NULL;
//                 }
//             }
// //            printf("4\n");
//         } else if (p->ee > q->ee) {//多项式1的项的指数大于多项式2的项时
//             qre->next = q->next;
//             q->next = p;
//             pre->next = q;
//             pre = q;
//             q = qre->next;
// //            printf("3\n");
//         } else if (q->ee > p->ee && p->next &&q->ee < (p->next)->ee)
//         {//多项式2的项指数大小在多项式1的项与下一项中间时
// //            printf("1\n");
//             qre->next = q->next;
//             pre = p;
//             p = p->next;
//             q->next = p;
//             pre->next = q;
//             pre = q;
//             q = qre->next;
//         } else if (q->ee > p->ee && p->next && q->ee >= (p->next)->ee) {
//             pre = p;
//             p = p->next;
// //            printf("2\n");
//         } else {
//             pre = p;
//             break;
//         }
//         index ++;
//     }
//     if (q) {//多项式2未计算完
//         pre->next = q;
//     }
//     return head1;
// }

// List Multiply (List head1, List head2) {
//     List p2 = head2->next->next;
//     List newHead = (List)malloc(sizeof(Node));
//     List pp = (List)malloc(sizeof(Node));
//     newHead->next = pp;
//     pp->next = NULL;
//     List p1;
//     List head1Pre = CopyList(head1);
//     List res = NULL;
//     while (p2) {
//         p1 = head1->next->next;
//         while (p1) {
//             p1->cc *= p2->cc;
//             p1->ee += p2->ee;
//             p1 = p1->next;
//         }
//         p2 = p2->next;
//         res = Plus(head1, newHead);
//         newHead = CopyList(head1);
//         head1 = CopyList(head1Pre);
//     }
//     return res;
// }

// int main() {
//     int i1, i2;
//     List head1, head2;
//     scanf("%d", &i1);
//     head1 = Creat(i1);
//     scanf("%d", &i2);
//     head2 = Creat(i2);
//     List head = Multiply(head1, head2);
//     Print(head);
// }

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct node {
//     int number;
//     struct node* next;
// } Node, *List;

// int main(void) {
//     List head = (List)malloc(sizeof(Node));
//     head->next = head;
//     List prev = head;
//     int numbers, password;
//     scanf("%d%d", &numbers, &password);
//     for (int i = 1; i <= numbers; i++) {
//         List pnew = (List)malloc(sizeof(Node));
//         prev->next = pnew;
//         pnew->number = i;
//         pnew->next = head;
//         prev = pnew;
//     }
//     List p = head->next;
//     prev = head;

//     while (head->next != head) {
//         for (int i = 0; i < password - 1; i++) {
//             if (p->next == head)  // 跳过头节点
//             {
//                 p = p->next;
//                 prev = prev->next;
//             }
//             p = p->next;
//             prev = prev->next;
//         }
//         if (p->next == head) {
//             printf("%d ", p->number);
//             prev->next = head;
//             prev = head;
//             List t = p;
//             p = head->next;
//             free(t);
//         } else {
//             printf("%d ", p->number);
//             prev->next = p->next;
//             List t = p;
//             p = p->next;
//             free(t);
//         }
//     }

//     return 0;
// }

// #include <malloc.h>
// #include <stdio.h>
// typedef struct set {
//     int password;
//     int num;
//     struct set* next;
// } Node;

// int main(void) {
//     int n, m, i, j = 1, k = 1, flag = 1;
//     int arr_a[100000];
//     Node head, *phead, *p0, *p1;
//     phead = NULL;
//     scanf("%d %d", &n, &m);
//     getchar();

//     for (i = 0; i < n; i++) {
//         if (phead == NULL) {
//             phead = &head;
//             phead->num = j;
//             p0 = phead;
//             phead->next = phead;

//         } else {
//             p1 = (Node*)malloc(sizeof(Node));
//             p1->next = p0;
//             phead->next = p1;
//             phead = p1;
//             phead->num = j;
//         }
//         scanf("%d", &phead->password);
//         j++;
//     }
//     i = 0;

//     while (p0) {
//         if (p0->num == 0) {
//             p0 = p0->next;
//             continue;
//         }
//         if (k == m && p0->num != 0) {
//             arr_a[i] = p0->num;
//             m = p0->password;
//             p0->num = 0;
//             i++;
//             k = 0;
//         }
//         k++;
//         if (i == (j - 1))
//             break;
//         p0 = p0->next;
//     }

//     for (j = 0; j < i; j++)
//         printf("%d ", arr_a[j]);

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct node {
//     int number;
//     struct node* next;
// } Node, *List;

// List head = NULL;
// List pFront = NULL;
// List per = NULL;
// int n, m, k;
// int arr_b[10000];

// void Create() {
//     List tail;
//     for (int i = 0; i < n; i++) {
//         List pnew;
//         pnew = (List)malloc(sizeof(Node));
//         pnew->number = i + 1;
//         if (head == NULL) {
//             head = pnew;
//         } else {
//             tail->next = pnew;
//         }
//         tail = pnew;
//     }
//     tail->next = head;
//     pFront = tail;
// }

// void Joseph(int number, int m) {
//     if (number == 0) {
//         return;
//     }
//     int count = 1;
//     List p = NULL;
//     while (count != m) {
//         per = per->next;
//         pFront = pFront->next;
//         count++;
//     }
//     p = per;
//     pFront->next = per->next;
//     if (number == 1) {
//         arr_b[k++] = p->number;
//     } else {
//         arr_b[k++] = p->number;
//     }
//     per = per->next;
//     free(p);
//     Joseph(number - 1, m);
// }

// int main() {
//     scanf("%d %d", &n, &m);
//     int i;
//     int arr_a[n];
//     for (i = n - m; i < n; i++) {
//         scanf("%d", &arr_a[i]);
//     }
//     for (i = 1; i <= n; i++) {
//         head = NULL;
//         pFront = NULL;
//         k = 0;
//         int flag = 1;
//         Create();
//         per = head;
//         Joseph(n, i);
//         for (int j = n - m; j < n; j++) {
//             if (arr_a[j] != arr_b[j]) {
//                 flag = 0;
//             }
//         }
//         if (flag == 1) {
//             printf("%d", i);
//             return 0;
//         }
//     }
//     return 0;
// }

#include <stdio.h>
#define MAXSIZE 10000

typedef struct {
    int num[MAXSIZE];
    int top;
} nump, *numpp;

typedef struct {
    char oth[MAXSIZE];
    int top;
} othp, *othpp;

//栈的创建                                    
numpp init_num() {
    nump* s;
    s = (nump*)malloc(sizeof(nump));
    s->top =-1;
    return s;
}

othpp init_oth() {
    othp* s;
    s = (othp*)malloc(sizeof(othp));
    s->top =-1;
    return s;
}

// // 判断是否为空（空返回1）
// int empty_num(numpp s)
// {
//     if(s->top==-1)
//         return 1;
//     else    
//         return 0;
// }

// int empty_oth(othpp s)
// {
//     if(s->top==-1)
//         return 1;
//     else    
//         return 0;
// }

// 入栈(成功1)
int push_num(numpp s,int num){
    if(s->top==MAXSIZE-1)
        return 0;

    s->num[s->top++]=num;
    return 1;
}

int push_oth(othpp s,char oth){
    if(s->top==MAXSIZE-1)
        return 0;

    s->oth[s->top++]=oth;
    return 1;
}



int main() {
    numpp s1 = init_num();
    othpp s2 = init_oth();

    char buffer[MAXSIZE]; 

    scanf("%s", buffer); 


    
}