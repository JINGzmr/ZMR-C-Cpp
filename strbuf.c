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
    // strbuf_init(sb, extra);//更新alloc
    sb->alloc += extra;
}

//向 sb 追加长度为 len 的数据 data 。
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    if(sb->len+len <= sb->alloc){ //（要不要考虑\0?）
        sb->buf=strcat(sb->buf,data);//(要不要强制类型转换为char*？)
    }
    else {
        strbuf_grow(sb,sb->alloc);//再来一倍
        sb->buf=strcat(sb->buf,data);
    }
    sb->len+=len;//更新len（ alloc？）
}

//向 sb 追加一个字符 c。
void strbuf_addch(struct strbuf *sb, int c)
{
    if(sb->len+1 <= sb->alloc){ 
        sb->buf=strcat(sb->buf,c);
    }
    else {
        strbuf_grow(sb,sb->alloc);
        sb->buf=strcat(sb->buf,c);
    }
    sb->len+=1;
}

//向 sb 追加一个字符串 s。
void strbuf_addstr(struct strbuf *sb, const char *s)
{
    int n;
    n=strlen(s);
    // if(sb->len+n <= sb->alloc){ 
    //     sb->buf=strcat(sb->buf,s);
    // }
    // else {
    //     strbuf_grow(sb,sb->alloc);
    //     sb->buf=strcat(sb->buf,s);
    // }
    // sb->len+=n;

    while(sb->len+n > sb->alloc)
    {
        strbuf_grow(sb,sb->alloc);
    }
    sb->buf=strcat(sb->buf,s);
    sb->len+=n;
}

//向一个 sb 追加另一个 strbuf 的数据。
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)//追加一个结构体
{
    // if(sb->len+sb2->len <= sb->alloc){ 
    //     sb->buf=strcat(sb->buf,sb2->buf);
    // }
    // else {
    //     strbuf_grow(sb,sb->alloc);
    //     sb->buf=strcat(sb->buf,sb2->buf);
    // }
    // sb->len+=(sb2->len);

    while(sb->len+sb2->len > sb->alloc)
    {
        strbuf_grow(sb,sb->alloc);
    }
    sb->buf=strcat(sb->buf,sb2->buf);
    sb->len+=(sb2->len);
}

//设置 sb 的长度 len。
void strbuf_setlen(struct strbuf *sb, size_t len)
{
    while(sb->alloc < len)
    {
        strbuf_grow(sb,sb->alloc);
    }
    sb->len=len;
}

//计算 sb 目前仍可以向后追加的字符串长度。
size_t strbuf_avail(const struct strbuf *sb)
{
    return (sb->alloc-(sb->len+1));//末尾的\0
}

//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data 。
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{
    while(sb->len+len > sb->alloc)
    {
        strbuf_grow(sb,sb->alloc);
    }
    int i;
    for(i=0;i<len;i++){
        sb->buf[pos+i]=(char*)data;
        data++;
    }
}