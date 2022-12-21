#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>

struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};

//Part 2A
void strbuf_init(struct strbuf *sb, size_t alloc);
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc);
void strbuf_release(struct strbuf *sb);
void strbuf_swap(struct strbuf *a, struct strbuf *b);
char *strbuf_detach(struct strbuf *sb, size_t *sz);
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second);
void strbuf_reset(struct strbuf *sb);

//Part 2B
void strbuf_grow(struct strbuf *sb, size_t extra);
void strbuf_add(struct strbuf *sb, const void *data, size_t len);
void strbuf_addch(struct strbuf *sb, int c);
void strbuf_addstr(struct strbuf *sb, const char *s);
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);
void strbuf_setlen(struct strbuf *sb, size_t len);
size_t strbuf_avail(const struct strbuf *sb);
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);

int main() {
  struct strbuf sb;
  strbuf_init(&sb, 10);
  strbuf_attach(&sb, "xiyou", 5, 10);
  assert(strcmp(sb.buf, "xiyou") == 0);
  strbuf_addstr(&sb, "linux");
  assert(strcmp(sb.buf, "xiyoulinux") == 0);
  strbuf_release(&sb);
}


//初始化 sb 结构体，容量为 alloc。
void strbuf_init(struct strbuf *sb, size_t alloc)
{
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char *)malloc(sizeof(char)*alloc);//强制类型转换（void*--char*）
    strcpy(sb->buf,"");
}

//将字符串填充到 sb 中，长度为 len, 容量为 alloc。
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc)
{
    sb->buf=(char*)str;//强制类型转换（void*--char*）
    sb->len=len;
    sb->alloc=alloc;
}

//释放 sb 结构体的内存。
void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);//参数是malloc()返回的地址，当时用buf存该地址
    sb->buf=NULL;//把指针设为NULL
    sb->len=0;
    sb->alloc=0;
}

//交换两个 strbuf。
void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    struct strbuf t;
    t=*a;
    *a=*b;
    *b=t;

    // t.len=a->len;
    // t.alloc=a->alloc;
    // t.buf=a->buf;
    
    // a->len=b->len;
    // a->alloc=b->alloc;
    // a->buf=b->buf;

    // b->len=t.len;
    // b->alloc=t.alloc;
    // b->buf=t.buf;
}

//将 sb 中的原始内存取出，并将 sz 设置为其 alloc 大小 。
char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
    *sz=sb->alloc;
    return sb->buf;
}

//比较两个 strbuf 的内存是否相同。
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
    int tag=1;
    if(first->len!=second->len)tag=0;
    if(first->alloc!=second->alloc)tag=0;
    if(strcmp(first->buf,second->buf)!=0)tag=0;
    return tag;//相同‘1’,不同‘0’
}

//清空 sb 。
void strbuf_reset(struct strbuf *sb)
{
    sb->len=0;
    sb->alloc=0;
    free(sb->buf);
    sb->buf=NULL;

    // sb=NULL;
}

/*---------------------------------------------------------------------------------*/

//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用。
//                           （包括alloc的4字节吗？）
void strbuf_grow(struct strbuf *sb, size_t extra)
{
    sb->buf=(char*)realloc(sb->buf,extra);//默认buf之前申请过一块内存，返回值为刚申请到的内存首地址
    //(还要)
}