#include <iostream>
// 使用你的名字替换YOUR_NAME
namespace YOUR_NAME
{
    template <class T> 
/**
 * template: 声明创建一个模板
 * class:表明他后面的符号是一种数据类型
 * T ：通用的数据类型，名称可以替换，一般是大写字母
 * 
 * 然后在这行代码后面紧跟着写一个类
*/

    // list存储的节点
    // 可以根据你的需要添加适当的成员函数与成员变量
    struct node  //链表中的节点
    {
        node<T> *prev_; //指向前一个节点的指针，类型为 node<T>*，T是模板类的类型参数
        node<T> *next_; //指向后一个节点的指针
        T data_; //当前节点的数据
        
        //构造函数
        //使用传入的参数 data 构造一个新节点，将 data 存储到节点中，并将指针 prev_ 和 next_ 初始化为 nullptr。
        node(const T &data)
            : data_(data), prev_(nullptr), next_(nullptr)
        {
        }

        //默认构造函数
        //创建一个空节点，将指针 prev_ 和 next_ 初始化为 nullptr
        node()
            : prev_(nullptr), next_(nullptr)
        {
        }

        //析构函数
        ~node()
        {
        }

    };

    template <class T>
    //迭代器类,(类比指针)
    //提供了访问链表中元素的方法
    struct iterator
    {
        typedef node<T> node_;  //以后链表中的节点用这个表示，不是指向节点的指针，就只是单纯的一个节点
        
        /**
         * 迭代器喽，
         * 这struct iterator里的所有的东西都是iterator_的，可以通过它来访问
         * 所以下面的node_ptr_也是迭代器iterator_的
         * 因此在重载==时，可以通过定义的迭代器类型t来访问里面的元素，如t.node_ptr_
        */
        typedef iterator<T> iterator_;   

        node_ * node_ptr_;  //指向当前节点的指针  -->这个才是节点指针
        
        /**
         * 迭代器(iterator)的构造函数
         * 参数为指向一个节点的指针(node_ptr)
         * 用于初始化迭代器的成员变量node_ptr_，指向当前节点。
        */
        iterator(node_ *node_ptr) 
            : node_ptr_(node_ptr)
        {
        }
        ~iterator()
        {
        }

        //迭代到下一个节点
        //++it
        iterator_ &operator++()
        {
            node_ptr_ = node_ptr_->next_;
            return *this;
        }
        //迭代到前一个节点
        //--it
        iterator_ &operator--()
        {
            node_ptr_ = node_ptr_->prev_;
            return *this;
        }    
        // it++
        iterator operator++(int)  //int参数作为占位符来区分前置++和后置++，该参数没有实际用途
        {
            iterator tmp(this->node_ptr_);
            node_ptr_ = node_ptr_->next_;
            return tmp;
        }
        // it--
        iterator operator--(int)
        {
            iterator tmp = node_ptr_;
            node_ptr_ = node_ptr_->prev_;
            return tmp;
        }
        //指向迭代器中被访问的成员值
        T &operator*()
        {

        }

        //指向迭代器中被访问的成员指针
        T *operator->()
        {
        }
        //重载==
        bool operator==(const iterator_ &t)
        {
            return node_ptr_ == t.node_ptr_;
        }
        //重载！=
        bool operator!=(const iterator_ &t)
        {

        }

        //**可以添加需要的成员变量与成员函数**
    };


    template <class T>
    class list  //双向链表
    {
    public:
        typedef node<T> node_;
        typedef iterator<T> Iterator;

    private:
        //可以添加你需要的成员变量
        node_ *head_; //头节点,哨兵（不存储有效数据）

    public:
        //构造函数
        list()
        {
        }
        //拷贝构造，要求实现深拷贝
        list(const list<T> &lt)
        {
        }
        
        template <class inputIterator>
        //迭代器构造
        list(inputIterator begin, inputIterator end)
        {
        }
        //析构函数
        ~list()
        {
        }

        //拷贝赋值
        list<T> &operator=(const list<T> &lt)
        {
        }
        //清空list中的数据（清空链表）
        void clear()
        {
        }
        //返回容器中存储的有效节点个数
        size_t size() const
        {
        }
        //判断是否为空
        bool empty() const
        {
        }
        //尾插
        bool push_back(const T &data)
        {
        }
        //头插
        bool push_front(const T &data)
        {
        }
        //尾删
        bool pop_back()
        {
        }
        //头删
        bool pop_front()
        {
        }
        //默认新数据添加到pos迭代器的后面,根据back的方向决定插入在pos的前面还是后面
        bool insert(Iterator pos, const T &data, bool back = true)
        {
        }
        //删除pos位置的元素
        bool erase(Iterator pos)
        {
        }

        //获得list第一个有效节点的迭代器
        Iterator begin() const
        {
        }

        //获得list最后一个节点的下一个位置
        Iterator end() const
        {
        }
        //查找data对应的迭代器
        Iterator find(const T &data) const
        {
        }
        //获得第一个有效节点元素值
        T front() const
        {
        }
        //获得最后一个有效节点元素值
        T back() const
        {
        }

    private:
        //可以添加你需要的成员函数
    };
};


