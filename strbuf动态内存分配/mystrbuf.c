// #include"strbuf.h"
#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include <unistd.h>//read

struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};

// //Part 2A
// void strbuf_init(struct strbuf *sb, size_t alloc);
// void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc);
// void strbuf_release(struct strbuf *sb);
// void strbuf_swap(struct strbuf *a, struct strbuf *b);
// char *strbuf_detach(struct strbuf *sb, size_t *sz);
// int strbuf_cmp(const struct strbuf *first, const struct strbuf *second);
// void strbuf_reset(struct strbuf *sb);

// //Part 2B
// void strbuf_grow(struct strbuf *sb, size_t extra);
// void strbuf_add(struct strbuf *sb, const void *data, size_t len);
// void strbuf_addch(struct strbuf *sb, int c);
// void strbuf_addstr(struct strbuf *sb, const char *s);
// void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);
// void strbuf_setlen(struct strbuf *sb, size_t len);
// size_t strbuf_avail(const struct strbuf *sb);
// void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);

// //Part 2C
// void strbuf_ltrim(struct strbuf *sb);
// void strbuf_rtrim(struct strbuf *sb);
// void strbuf_remove(struct strbuf *sb, size_t pos, size_t len);

// //Part 2D
// ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint);
// int strbuf_getline(struct strbuf *sb, FILE *fp);


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
    // *sz=sb->alloc;
    sz=(size_t*)&(sb->alloc);
    return sb->buf;
}

//比较两个 strbuf 的内存是否相同。
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
    // int tag=1;
    // if(first->len!=second->len)tag=0;
    // if(first->alloc!=second->alloc)tag=0;
    // if(strcmp(first->buf,second->buf)!=0)tag=0;
    // return tag;//相同‘1’,不同‘0’

    if(first->len>second->len)
        return 1;
    if(first->len<second->len)
        return -1;
    else 
        return 0;

}

//清空 sb 。
void strbuf_reset(struct strbuf *sb)//清空指的是让内存没有东西，而非释放(128G内存恢复出场设置)
{
    // sb->len=0;  
    // sb->alloc=0;
    // free(sb->buf);
    // sb->buf=NULL;

    // int i;  OK!
    // for(i=0;i<sb->len;i++){
    //     sb->buf[i]='\0';
    // }
    // sb->len=0;
    // // sb->alloc=0  因为alloc是申请到的内存大小，所以不能令为零（否则恢复出场设置后128G空间都没了）

    memset(sb->buf,0,sb->len);  //try->OK!
    sb->len=0;

}

/*------------------------------------------------------------------------------------------------------------------------*/

//确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用。
void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if(sb->alloc-sb->len < extra){
        sb->buf=(char*)realloc(sb->buf,sb->alloc+extra);//默认buf之前申请过一块内存，返回值为刚申请到的内存首地址
        sb->alloc += extra;
    }
}

//向 sb 追加长度为 len 的数据 data 。
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    // if(sb->len+len <= sb->alloc){ //（要不要考虑\0?）
    //     sb->buf=strcat(sb->buf,(const char*)data);//(要不要强制类型转换为char*？)要！
    // }
    // else {
    //     strbuf_grow(sb,sb->alloc);//再来一倍
    //     sb->buf=strcat(sb->buf,(const char*)data);
    // }
    // sb->len+=len;//更新len（ alloc？）


    if(sb->len+len >= sb->alloc){
        sb->buf=(char*)realloc(sb->buf,sb->len+len+1);//包括\0
        sb->alloc=sb->len+len+1;//更新扩容后的内存大小256G
    }
    memcpy(sb->buf+sb->len,data,len);
    sb->len+=len;
    // sb->buf+sb->len='\0'; //错
    //*(sb->buf+sb->len)='\0';  //ok!
    sb->buf[sb->len]='\0';

}

//向 sb 追加一个字符 c。
void strbuf_addch(struct strbuf *sb, int c)
{
    // char a[1];
    // a[0]=c;
//     if(sb->len+1 <= sb->alloc){ 
//         sb->buf=strcat(sb->buf,a);
//     }
//     else {
//         strbuf_grow(sb,sb->alloc);
//         sb->buf=strcat(sb->buf,a);
//     }
//     sb->len+=1;

    if(sb->len+1 >= sb->alloc){
        sb->buf=(char*)realloc(sb->buf,(sb->alloc)*2);//内存翻两倍
        sb->alloc=sb->alloc*2;
    }
    memcpy(sb->buf+sb->len,&c,1);
    sb->len+=1;
    sb->buf[sb->len]='\0';

}

//向 sb 追加一个字符串 s。
void strbuf_addstr(struct strbuf *sb, const char *s)
{
    int n;
    n=strlen(s);
    // while(sb->len+n > sb->alloc)
    // {
    //     strbuf_grow(sb,sb->alloc);
    // }
    // sb->buf=strcat(sb->buf,s);
    // sb->len+=n;

    if(sb->len+n >= sb->alloc){
        sb->buf=(char*)realloc(sb->buf,sb->len+n+1);
        sb->alloc=sb->len+n+1;
    }
    memcpy(sb->buf+sb->len,s,n);
    // sb->buf=strcat(sb->buf,s); 错(wen)
    sb->len+=n;
    sb->buf[sb->len]='\0';

}

//向一个 sb 追加另一个 strbuf 的数据。
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)//追加一个结构体
{
    if(sb->len+sb2->len >= sb->alloc){
        sb->buf=(char*)realloc(sb->buf,sb->len+sb2->len+1);
        sb->alloc=sb->len+sb2->len+1;
    }
    sb->buf=strcat(sb->buf,sb2->buf);
    sb->len+=sb2->len;
}

//设置 sb 的长度 len。
void strbuf_setlen(struct strbuf *sb, size_t len)
{
    if(len >= sb->alloc){
        sb->buf=(char*)realloc(sb->buf,len+1);
        sb->alloc=len+1;
    }
    sb->len=len;
    sb->buf[sb->len]='\0';

}

//计算 sb 目前仍可以向后追加的字符串长度。
size_t strbuf_avail(const struct strbuf *sb)
{
    return (sb->alloc-(sb->len+1));//末尾的\0
}

//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data 。
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{
    if(sb->len+len > sb->alloc){
        strbuf_grow(sb,sb->len+len+1);
    }
    // int i;
    // char a[len];
    // strcpy(a,(const char*)data);
    // for(i=0;i<len;i++){
    //     sb->buf[pos+i]=a[i];  //默认原来位置没有数据
    // }

    memmove(sb->buf+pos+len,sb->buf+pos,sb->len-pos);//把pos位置后面的数据移到pos+len的地方，空出来的len长度来存放data
    memcpy(sb->buf+pos,data,len);//sb->buf[pos]错
    sb->len+=len;
    sb->buf[sb->len]='\0';

}


/*----------------------------------------------------------------------------------------------------------------*/

//去除 sb 缓冲区左端的所有 空格，tab,'\t'。
void strbuf_ltrim(struct strbuf *sb)
{
    while((*(sb->buf)==' '||sb->buf[0]=='\t')&&sb->buf[0]!='\0')//这两种都可以，就是不行sb->buf==' '，因为
    {                                                        //C++ forbids comparison between pointer and integer
        sb->buf=(char*)memmove(sb->buf,sb->buf+1,sb->len-1);
        sb->len--;
    }
}

//去除 sb 缓冲区右端的所有 空格，tab, '\t'。
void strbuf_rtrim(struct strbuf *sb)
{
    while((sb->buf[(sb->len)-1]==' '||sb->buf[(sb->len)-1]=='\t')&&sb->buf[(sb->len)-1]!='\0')
    {
        // sb->buf+(sb->len)-1='\0';
        // sb->buf=(char*)memmove(sb->buf+(sb->len)-1,sb->buf+(sb->len),1);
        sb->buf[(sb->len)-1]='\0';
        sb->len--;
    }
}

//删除 sb 缓冲区从 pos 坐标长度为 len 的内容。
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len)
{
    // int i;
    // for(i=0;i<len;i++){
    //     sb->buf[pos+i]=0;
    // }
    memmove(sb->buf+pos,sb->buf+pos+len,sb->len-pos-len);//strlen(sb->buf+pos+len)+1  OK！
    sb->len=sb->len-len;
    sb->buf[sb->len]='\0';
}


/*------------------------------------------------------------------------------------------------------------------------*/

//sb 增长 hint ? hint : 8192 大小， 然后将文件描述符为 fd 的所有文件内容追加到 sb 中。
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    ssize_t result; 
    sb->buf=(char*)realloc(sb->buf,sb->alloc+(hint ? hint : 8192));//不是sb->len+(...)
    sb->alloc+=(hint ? hint : 8192);
    result=read(fd,sb->buf+sb->len,sb->alloc-sb->len-1);
    if(result){
        sb->len+=result;
        sb->buf[sb->len]='\0';
    }
    return result;

}

//将 将文件句柄为 fp 的一行内容（抛弃换行符）读取到 sb 。
int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    char ch;
    // ch=fgetc(fp);//返回值为int,然后再ch！=EOF错
    while((ch=fgetc(fp))!=EOF){
        if(feof(fp)!=0||ch=='\n')
            break;
        else 
            strbuf_addch(sb,ch);
    }
    return 1;
}

/*------------------------------------------------------------------------------------------------------------------------*/

//实现字符串切割
//将长度为 len 的字符串 str 根据切割字符 terminator 切成多个 strbuf,并从结果返回，
//max 可以用来限定最大切割数量。返回 struct strbuf 的指针数组，数组的最后元素为 NULL
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
{
    struct strbuf **p=(struct strbuf**)malloc(sizeof(struct strbuf*)*(max+1));
    const char *begin = str;
    const char *end=str+len;  
    const char *next;
    int i=0;
    int len2;

    while(*begin==terminator)
        begin++;

    for (next=begin;next<=end;next++)
    {
        if (*next==terminator||next==end)
        {
            len2=next-begin;
            p[i]=(struct strbuf*)malloc(sizeof(struct strbuf));
            p[i]->len=len2;
            p[i]->alloc=len2+1;
            p[i]->buf=(char*)malloc(sizeof(char)*(len2+1));
            memcpy(p[i]->buf,begin,len2);
            *(p[i]->buf+len2)='\0';
            i++;

            while(*next==terminator&&next<=end)
                next++;

            begin=next;
        }
        if(i==max)
            break;
    }
    p[i]=NULL;
    return p;
}

//实现判断一个 strbuf 是否以指定字符串开头的功能
//target_str:目标字符串，str:前缀字符串，strlen:target_str 长度，前缀相同返回 true 失败返回 false
bool strbuf_begin_judge(char* target_str, const char* str, int strlen)
{
    //why？
    // if(str[0]=='\0') 
    //     return true;
    // int len=sizeof(str)-1;//因为strlen函数会和变量名一样，报错 ‘strlen’ cannot be used as a function
    // if(memcmp(target_str,str,len)==0)//相同返回0
    //     return true;
    // else 
    //     return false;

    int i;
    for(i=0;i<strlen;i++){
        if(str[i]=='\0')
            break;
        if(target_str[i]!=str[i])
            return false;
    }
    return true;
}

//获取字符串从坐标 [begin, end) 的所有内容（可以分成引用和拷贝两个模式）
//target_str:目标字符串，begin:开始下标，end:结束下标，len:target_buf的长度
//下标从0开始，[begin, end)区间，参数不合法返回 NULL
char* strbuf_get_mid_buf(char* target_buf, int begin, int end, int len)
{
    if(end<begin||target_buf==NULL)// <= 错
        return NULL;
    char *a;
    a=(char*)malloc(end-begin+1);
    a=(char*)memcpy(a,target_buf+begin,end-begin);
    a[end-begin]='\0';
    return a;
}
