// 注：为使代码易于打包发送及编译运行，本项目并未分多文件（.c/.h）和进行多文件编译（cmake）
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int coef;
    int expn;
    struct node* next;
} Node, *List;

List Creat(int i) {
    List head;
    head = (List)malloc(sizeof(Node));
    List pre, pnew;
    pre = head;
    char a, b;
    for (int j = 0; j <= i; j++) {
        pnew = (List)malloc(sizeof(Node));
        scanf("%c%d,%d%c", &a, &pnew->coef, &pnew->expn, &b);
        pre->next = pnew;
        pre = pnew;
    }
    return head;
}

void Print_plus(List head) {
    List q = head->next->next;
    int flag = 1;
    if (!q) {
        putchar('0');
        printf("\n");
        return;
    }
    while (q) {
        if (q->coef > 0 && flag != 1) {
            putchar('+');
        }
        if (q->coef != 1 && q->coef != -1) {
            printf("%d", q->coef);
            if (q->expn == 1) {
                putchar('X');
            } else if (q->expn) {
                printf("X^%d", q->expn);
            }
        } else {
            if (q->coef == 1) {
                if (!q->expn) {
                    putchar('1');
                } else if (q->expn == 1) {
                    putchar('X');
                } else {
                    printf("X^%d", q->expn);
                }
            }
            if (q->coef == -1) {
                if (!q->expn) {
                    printf("-1");
                } else if (q->expn == 1) {
                    printf("-X");
                } else {
                    printf("-X^%d", q->expn);
                }
            }
        }
        q = q->next;
        flag++;
    }
}

List Plus(List head1, List head2) {
    List pre = NULL, p = NULL, qre = NULL, q = NULL;
    pre = head1->next;
    p = head1->next->next;
    qre = head2->next;
    q = head2->next->next;
    int index = 1;
    while (p != NULL) {
        if (q == NULL) {
            return head1;
        }
        if (p->expn == q->expn) {
            p->coef = p->coef + q->coef;
            if (p->coef == 0) {
                pre->next = p->next;
                free(p);
                if (pre) {
                    p = pre->next;
                } else {
                    p = NULL;
                }
                qre->next = q->next;
                free(q);
                if (qre) {
                    q = qre->next;
                } else {
                    q = NULL;
                }
            } else {
                pre = p;
                p = p->next;
                qre->next = q->next;
                free(q);
                if (qre) {
                    q = qre->next;
                } else {
                    q = NULL;
                }
            }
        } else if (p->expn > q->expn) {
            qre->next = q->next;
            q->next = p;
            pre->next = q;
            pre = q;
            q = qre->next;
        } else if (q->expn > p->expn && p->next && q->expn < (p->next)->expn) {
            qre->next = q->next;
            pre = p;
            p = p->next;
            q->next = p;
            pre->next = q;
            pre = q;
            q = qre->next;
        } else if (q->expn > p->expn && p->next && q->expn >= (p->next)->expn) {
            pre = p;
            p = p->next;
        } else {
            pre = p;
            break;
        }
        index++;
    }
    if (q) {
        pre->next = q;
    }
    return head1;
}

void Print_Minus(List head) {
    List q = head->next->next;
    int flag = 1;
    if (!q) {
        putchar('0');
        printf("\n");
        return;
    }
    while (q) {
        if (q->coef > 0 && flag != 1) {
            putchar('+');
        }
        if (q->coef != 1 && q->coef != -1) {
            printf("%d", q->coef);
            if (q->expn == 1) {
                putchar('X');
            } else if (q->expn) {
                printf("X^%d", q->expn);
            }
        } else {
            if (q->coef == 1) {
                if (!q->expn) {
                    putchar('1');
                } else if (q->expn == 1) {
                    putchar('X');
                } else {
                    printf("X^%d", q->expn);
                }
            }
            if (q->coef == -1) {
                if (!q->expn) {
                    printf("-1");
                } else if (q->expn == 1) {
                    printf("-X");
                } else {
                    printf("-X^%d", q->expn);
                }
            }
        }
        q = q->next;
        flag++;
    }
}

List Minus(List head1, List head2) {
    List pre = NULL, p = NULL, qre = NULL, q = NULL;
    pre = head1->next;
    p = head1->next->next;
    qre = head2->next;
    q = head2->next->next;
    int index = 1;
    while (p != NULL) {
        if (q == NULL) {
            return head1;
        }
        if (p->expn == q->expn) {
            p->coef = p->coef - q->coef;
            if (p->coef == 0) {
                pre->next = p->next;
                free(p);
                if (pre) {
                    p = pre->next;
                } else {
                    p = NULL;
                }
                qre->next = q->next;
                free(q);
                if (qre) {
                    q = qre->next;
                } else {
                    q = NULL;
                }
            } else {
                pre = p;
                p = p->next;
                qre->next = q->next;
                free(q);
                if (qre) {
                    q = qre->next;
                } else {
                    q = NULL;
                }
            }
        } else if (p->expn > q->expn) {
            q->coef = -q->coef;
            qre->next = q->next;
            q->next = p;
            pre->next = q;
            pre = q;
            q = qre->next;
        } else if (q->expn > p->expn && p->next && q->expn < (p->next)->expn) {
            q->coef = -q->coef;
            qre->next = q->next;
            pre = p;
            p = p->next;
            q->next = p;
            pre->next = q;
            pre = q;
            q = qre->next;
        } else if (q->expn > p->expn && p->next && q->expn >= (p->next)->expn) {
            pre = p;
            p = p->next;
        } else {
            pre = p;
            break;
        }
        index++;
    }
    if (q) {
        pre->next = q;
        List qq = q;
        while (qq) {
            qq->coef = -qq->coef;
            qq = qq->next;
        }
    }
    return head1;
}

void Print_Multiply(List head) {
    List q = head->next->next;
    int flag = 1;
    if (!q) {
        putchar('0');
        printf("\n");
        return;
    }
    while (q) {
        if (q->coef > 0 && flag != 1) {
            putchar('+');
        }
        if (q->coef != 1 && q->coef != -1) {
            printf("%d", q->coef);
            if (q->expn == 1) {
                putchar('X');
            } else if (q->expn) {
                printf("X^%d", q->expn);
            }
        } else {
            if (q->coef == 1) {
                if (!q->expn) {
                    putchar('1');
                } else if (q->expn == 1) {
                    putchar('X');
                } else {
                    printf("X^%d", q->expn);
                }
            }
            if (q->coef == -1) {
                if (!q->expn) {
                    printf("-1");
                } else if (q->expn == 1) {
                    printf("-X");
                } else {
                    printf("-X^%d", q->expn);
                }
            }
        }
        q = q->next;
        flag++;
    }
}

List CopyList(List head) {
    List newHead = (List)malloc(sizeof(Node));
    newHead->next = NULL;
    List p = head->next;
    List p2 = newHead;
    while (p) {
        List new = (List)malloc(sizeof(Node));
        new->coef = p->coef;
        new->expn = p->expn;
        p2->next = new;
        p2 = new;
        p = p->next;
    }
    p2->next = NULL;
    return newHead;
}

List Plus_Multiply(List head1, List head2) {
    List pre = NULL, p = NULL, qre = NULL, q = NULL;
    pre = head1->next;
    p = head1->next->next;
    qre = head2->next;
    q = head2->next->next;
    int index = 1;
    while (p != NULL) {
        if (q == NULL) {
            return head1;
        }
        if (p->expn == q->expn) {
            p->coef = p->coef + q->coef;
            if (p->coef == 0) {
                pre->next = p->next;
                free(p);
                if (pre) {
                    p = pre->next;
                } else {
                    p = NULL;
                }
                qre->next = q->next;
                free(q);
                if (qre) {
                    q = qre->next;
                } else {
                    q = NULL;
                }
            } else {
                pre = p;
                p = p->next;
                qre->next = q->next;
                free(q);
                if (qre) {
                    q = qre->next;
                } else {
                    q = NULL;
                }
            }
        } else if (p->expn > q->expn) {
            qre->next = q->next;
            q->next = p;
            pre->next = q;
            pre = q;
            q = qre->next;
        } else if (q->expn > p->expn && p->next && q->expn < (p->next)->expn) {
            qre->next = q->next;
            pre = p;
            p = p->next;
            q->next = p;
            pre->next = q;
            pre = q;
            q = qre->next;
        } else if (q->expn > p->expn && p->next && q->expn >= (p->next)->expn) {
            pre = p;
            p = p->next;
        } else {
            pre = p;
            break;
        }
        index++;
    }
    if (q) {
        pre->next = q;
    }
    return head1;
}

List Multiply(List head1, List head2) {
    List p2 = head2->next->next;
    List newHead = (List)malloc(sizeof(Node));
    List pp = (List)malloc(sizeof(Node));
    newHead->next = pp;
    pp->next = NULL;
    List p1;
    List head1Pre = CopyList(head1);
    List res = NULL;
    while (p2) {
        p1 = head1->next->next;
        while (p1) {
            p1->coef *= p2->coef;
            p1->expn += p2->expn;
            p1 = p1->next;
        }
        p2 = p2->next;
        res = Plus_Multiply(head1, newHead);
        newHead = CopyList(head1);
        head1 = CopyList(head1Pre);
    }
    return res;
}

int Calculate(List head, int X) {
    List q = head->next->next;
    if (!q) {
        return 0;
    }
    int r = 0;
    while (q) {
        r += q->coef * pow(X, q->expn);
        q = q->next;
    }
    return r;
}

void Print_Diff(List head) {
    List q = head->next->next;
    int flag = 1;
    if (!q) {
        putchar('0');
        printf("\n");
        return;
    }
    while (q) {
        if (q->coef > 0 && flag != 1) {
            putchar('+');
        }
        if (q->coef != 1 && q->coef != -1) {
            printf("%d", q->coef);
            if (q->expn == 1) {
                putchar('X');
            } else if (q->expn) {
                printf("X^%d", q->expn);
            }
        } else {
            if (q->coef == 1) {
                if (!q->expn) {
                    putchar('1');
                } else if (q->expn == 1) {
                    putchar('X');
                } else {
                    printf("X^%d", q->expn);
                }
            }
            if (q->coef == -1) {
                if (!q->expn) {
                    printf("-1");
                } else if (q->expn == 1) {
                    printf("-X");
                } else {
                    printf("-X^%d", q->expn);
                }
            }
        }
        q = q->next;
        flag++;
    }
}

void Process(List head) {
    List pre = head->next;
    while (pre->next) {
        if (pre->next && pre->next->expn == 0) {
            pre->next = pre->next->next;
        }
        pre = pre->next;
        pre->coef *= pre->expn;
        pre->expn--;
    }
}

void menu() {
    int num;
    do {
        printf("\n——————————————————————————————————————————————————\n");
        printf("---------------欢迎进入一元多项式运算器！----------\n");
        printf("——————————————————————————————————————————————————\n");
        printf("---------------------1.加法------------------------\n");
        printf("---------------------2.减法------------------------\n");
        printf("---------------------3.乘法------------------------\n");
        printf("---------------------4.求值------------------------\n");
        printf("---------------------5.求导------------------------\n");
        printf("---------------------0.退出------------------------\n");
        printf("——————————————————————————————————————————————————\n");

        // 清空输入缓冲区
        fflush(stdin);

        scanf("%d", &num);

        switch (num) {
            case 1:
                printf("给出一组输入。例如:\n2\n(6,0)(2,1)\n1\n(7,1)\n");
                int i1, i2;
                List head1, head2;
                printf("请进行你的输入：\n");
                scanf("%d", &i1);
                head1 = Creat(i1);
                scanf("%d", &i2);
                head2 = Creat(i2);
                List head = Plus(head1, head2);
                printf("\n运算结果为：");
                Print_plus(head);
                printf("\n\n");
                break;

            case 2:
                printf("给出一组输入。例如:\n2\n(6,0)(2,1)\n1\n(7,1)\n");
                printf("请进行你的输入：\n");
                scanf("%d", &i1);
                head1 = Creat(i1);
                scanf("%d", &i2);
                head2 = Creat(i2);
                head = Minus(head1, head2);
                printf("\n运算结果为：");
                Print_Minus(head);
                printf("\n\n");
                break;

            case 3:
                printf("给出一组输入。例如:\n2\n(6,0)(2,1)\n1\n(7,1)\n");
                printf("请进行你的输入：\n");
                scanf("%d", &i1);
                head1 = Creat(i1);
                scanf("%d", &i2);
                head2 = Creat(i2);
                head = Multiply(head1, head2);
                printf("\n运算结果为：");
                Print_Multiply(head);
                printf("\n\n");
                break;

            case 4:
                printf("给出一组输入。例如:\n2\n(6,0)(2,1)\n2\n");
                printf("请进行你的输入：\n");
                int i, X;
                scanf("%d", &i);
                head = Creat(i);
                scanf("%d", &X);
                int result = Calculate(head, X);
                printf("\n运算结果为：");
                printf("%d\n\n", result);
                break;

            case 5:
                printf("给出一组输入。例如:\n2\n(6,0)(2,1)\n");
                printf("请进行你的输入：\n");
                scanf("%d", &i);
                head = Creat(i);
                Process(head);
                printf("\n运算结果为：");
                Print_Diff(head);
                printf("\n\n");
                break;

            case 0:
                break;
            default:
                printf("无效的数字，请重新输入！\n");
                break;
        }
    } while (num != 0);
}

int main() {
    menu();
}