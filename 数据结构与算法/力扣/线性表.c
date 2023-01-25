#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//  Definition for singly-linked list.
  struct ListNode {
      int val;
      struct ListNode *next;
 };
 
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


bool hasCycle(struct ListNode *head) {
    if(head==NULL)
        return false;

    struct ListNode *p;
    p=head;
    int i=1;

    while(p)
    {
        p=p->next;
        if(i>10000)
            return true;
        i++;
    }

    return false;   
}
