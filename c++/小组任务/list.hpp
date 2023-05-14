#include <iostream>
// 使用你的名字替换YOUR_NAME
namespace ZMR
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
    struct node // 链表中的节点
    {
        node<T> *prev_; // 指向前一个节点的指针，类型为 node<T>*，T是模板类的类型参数
        node<T> *next_; // 指向后一个节点的指针
        T data_;        // 当前节点的数据

        // 构造函数
        // 使用传入的参数 data 构造一个新节点，将 data 存储到节点中，并将指针 prev_ 和 next_ 初始化为 nullptr。
        node(const T &data)
            : data_(data), prev_(nullptr), next_(nullptr)
        {
        }

        // 默认构造函数
        // 创建一个空节点，将指针 prev_ 和 next_ 初始化为 nullptr
        node()
            : prev_(nullptr), next_(nullptr)
        {
        }

        // 析构函数
        ~node()
        {
        }
    };

    template <class T>
    // 迭代器类,(类比指针)
    // 提供了访问链表中元素的方法
    struct iterator
    {
        typedef node<T> node_; // 以后链表中的节点用这个表示，不是指向节点的指针，就只是单纯的一个节点

        /**
         * 迭代器喽，
         * 这struct iterator里的所有的东西都是iterator_的，可以通过它来访问
         * 所以下面的node_ptr_也是迭代器iterator_的
         * 因此在重载==时，可以通过定义的迭代器类型t来访问里面的元素，如t.node_ptr_
         */
        typedef iterator<T> iterator_;

        node_ *node_ptr_; // 指向当前节点的指针  -->这个才是节点指针

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

        // 迭代到下一个节点
        //++it
        iterator_ &operator++()
        {
            node_ptr_ = node_ptr_->next_;
            return *this;
        }
        // 迭代到前一个节点
        //--it
        iterator_ &operator--()
        {
            node_ptr_ = node_ptr_->prev_;
            return *this;
        }
        // it++
        iterator operator++(int) // int参数作为占位符来区分前置++和后置++，该参数没有实际用途
        {
            iterator tmp(this->node_ptr_);
            node_ptr_ = node_ptr_->next_;
            return tmp;
        }
        // it--
        iterator operator--(int)
        {
            iterator tmp(node_ptr_);
            node_ptr_ = node_ptr_->prev_;
            return tmp;
        }

        // 指向迭代器中被访问的成员值
        T &operator*()
        {
            return node_ptr_->data_;
        }
        // 指向迭代器中被访问的成员指针
        T *operator->()
        {
            return &(node_ptr_->data_); // 因为返回值是一个T类型的指针，所以要用取地址符&将data_的地址传回去，接收者也会用指针类型的变量来接收该地址，使之存的是data_的地址
        }

        // 重载==
        bool operator==(const iterator_ &t)
        {
            if (node_ptr_ == t.node_ptr_)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // 重载！=
        bool operator!=(const iterator_ &t)
        {
            if (node_ptr_ == t.node_ptr_) //  这里也是用==
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        //**可以添加需要的成员变量与成员函数**
    };

    template <class T>
    class list // 双向链表
    {
    public:
        typedef node<T> node_;        // 普通的节点，不是节点指针
        typedef iterator<T> Iterator; // 迭代器，里面实现了一些快捷的操作，如：指向下一个节点 ++it

    private:
        // 可以添加你需要的成员变量
        node_ *head_; // 头节点,哨兵（不存储有效数据）

    public:
        // 构造函数
        list()
        {
            head_ = new node_;
            head_->prev_ = head_;
            head_->next_ = head_;
        }

        // 拷贝构造，要求实现深拷贝
        /**
         * 模板类 list 的拷贝构造函数的实现，其目的是创建一个新的 list 对象，其元素与另一个 list 对象 lt 相同
         * 对于 lt 中的每个节点，都创建一个新的节点并将其添加到新的 list 对象中
         */
        list(const list<T> &lt)
        {
            head_ = new node_; // 新list的头节点
            head_->prev_ = head_;
            head_->next_ = head_;

            //法一：
            for (node_ *p = lt.head_->next_; p != lt.head_; p = p->next_) // 通过循环将lt中的每个节点用尾插法添加到新创建的list中，下面的拷贝赋值是另一种做法
            {
                push_back(p->data_);
            }

            //法二：
            // for (auto it = lt.begin(); it != lt.end(); ++it)
            // {
            //     push_back(*it);
            // }
        }

        template <class inputIterator>
        // 迭代器构造
        list(inputIterator begin, inputIterator end)
        {
            head_ = new node_; // 创建哨兵节点
            head_->next_ = head_;
            head_->prev_ = head_;
            for (inputIterator it = begin; it != end; ++it)
            {
                push_back(*it);
            }
        }
        // 析构函数
        ~list()
        {
            // 释放每一个节点
            node_ *p = head_->next_;
            while (p != head_)
            {
                p->next_->prev_ = p->prev_;
                p->prev_->next_ = p->next_;
                node_ *pp = p->next_;
                delete p;
                p = pp;
            }

            head_->next_ = head_;
            head_->prev_ = head_;

            // 最后把哨兵节点给释放
            delete head_;
        }

        // 拷贝赋值
        list<T> &operator=(const list<T> &lt)
        {
            if (this != &lt) // 要 &lt 吗？？？ --->必须要！！！  lt是一个普通的链表，而this是一个指针，所以要用取地址符&取出lt的地址，再和指针this里面存的地址作比较，如果相同，则说明调用该函数的A和原来的B是一样的，若不同，就要执行拷贝赋值操作
            //因为是运算符重载，所以在用到 链表A=链表B 时（即需要将链表B赋值给链表A时）， A是调用这个重载函数的发起方，所以该函数里的this指针指向的就是链表A，而链表B则作为函数的参数，通过引用&变成链表lt，在函数中以lt的形式存在，并通过一系列操作，将lt的每个节点的值都赋给this所指的那个链表（也就是链表A）
            {
                clear(); // 既然不相等，就先清空this所指向的链表，也就是链表A。但为什么clear函数里没有出现this？  --->只是一般默认head_前面的this不写, 其实this->head_ 和 head_ 是等价的

                for (auto it = lt.begin(); it != lt.end(); ++it)
                {
                    push_back(*it);
                } 
            }
            return *this;
        }
        // 清空list中的数据（清空链表）
        void clear()
        {
            // 法一：
            node_ *p = head_->next_;
            while (p != head_)
            {
                p->next_->prev_ = p->prev_;
                p->prev_->next_ = p->next_;
                node_ *pp = p->next_; // node_ *pp = p;  --->这样删除节点会导致段错误！！！
                delete p;             // delete pp;
                p = pp;               // p = p->next_;
            }

            // 法二（好）：
            //  Iterator it(head_->next_);
            //  while(it.node_ptr_ != head_)
            //  {
            //      it.node_ptr_->next_->prev_ = it.node_ptr_->prev_;
            //      it.node_ptr_->prev_->next_ = it.node_ptr_->next_;
            //      node_ *p = it.node_ptr_->next_;
            //      delete it.node_ptr_;
            //      it.node_ptr_ = p;
            //  }

            //公共部分：
            head_->next_ = head_;
            head_->prev_ = head_;
        }

        // 返回容器中存储的有效节点个数
        size_t size() const
        {
            size_t size = 0;

            // 法一：
            for (node_ *p = this->head_->next_; p != this->head_; p = p->next_) // 好像要不要this都行? --->对
            {
                size++;
            }

            // 法二（好）：
            //  for(Iterator it = this->begin(); it!=this->end(); ++it)
            //  {
            //      size++;
            //  }

            return size;
        }

        // 判断是否为空
        bool empty() const
        {
            if (size() == 0) // 或：this->head_->next_ == head_
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // 尾插
        bool push_back(const T &data)
        {
            node_ *p = new node_(data);
            p->prev_ = head_->prev_;
            head_->prev_->next_ = p;
            p->next_ = head_;
            head_->prev_ = p;

            return true;
        }
        // 头插
        bool push_front(const T &data)
        {
            node_ *p = new node_(data);
            p->prev_ = head_;
            p->next_ = head_->next_;
            head_->next_->prev_ = p;
            head_->next_ = p;

            return true;
        }
        // 尾删
        bool pop_back()
        {
            if (head_->prev_ != head_)
            {
                node_ *p = head_->prev_;
                // p->prev_->next_ = head_;
                // head_->prev_ = p->prev_;
                p->prev_->next_ = p->next_;
                p->next_->prev_ = p->prev_;
                delete p;
                return true;
            }
            else
            {
                return false;
            }
        }
        // 头删
        bool pop_front()
        {
            if (head_->next_ != head_)
            {
                node_ *p = head_->next_;
                p->prev_->next_ = p->next_;
                p->next_->prev_ = p->prev_;
                delete p;

                return true;
            }
            else
            {
                return false;
            }
        }

        // 默认新数据添加到pos迭代器的后面,根据back的方向决定插入在pos的前面还是后面
        bool insert(Iterator pos, const T &data, bool back = true)
        {
            node_ *p = new node_(data);
            if (back)
            {
                p->prev_ = pos.node_ptr_;
                p->next_ = pos.node_ptr_->next_;
                pos.node_ptr_->next_->prev_ = p;
                pos.node_ptr_->next_ = p;
            }
            else
            {
                p->prev_ = pos.node_ptr_->prev_;
                pos.node_ptr_->prev_->next_ = p;
                p->next_ = pos.node_ptr_;
                pos.node_ptr_->prev_ = p;
            }

            return true;
        }
        // 删除pos位置的元素
        bool erase(Iterator pos)
        {
            if (pos.node_ptr_ == nullptr || pos.node_ptr_ == head_)
            {
                return false;
            }

            pos.node_ptr_->next_->prev_ = pos.node_ptr_->prev_;
            pos.node_ptr_->prev_->next_ = pos.node_ptr_->next_;
            delete pos.node_ptr_;
            return true;
        }

        // 获得list第一个有效节点的迭代器
        Iterator begin() const // const 说明函数返回的迭代器对象不能用于修改它所指的数据结构
        {
            Iterator it(head_->next_); // 搞了一个名为it的迭代器，并赋初始值为head_->next_
            return it;
        }

        // 获得list最后一个节点的下一个位置
        Iterator end() const
        {
            // 法一：
            Iterator it(head_);
            return it;

            // 法二（好）：
            //  Iterator it(head_->next_);
            //  while(it.node_ptr_ != head_)
            //  {
            //      it++;
            //  }
            //  return it;
        }
        // 查找data对应的迭代器
        Iterator find(const T &data) const
        {
            Iterator it(head_->next_);
            for (; it.node_ptr_ != this->head_; ++it) //++it 相当于节点后移
            {
                if (it.node_ptr_->data_ == data)
                {
                    return it;
                }
            }
            return nullptr; // 能到这一步，说明没有与之匹配的迭代器，那就返回空喽
        }
        // 获得第一个有效节点元素值
        T front() const
        {
            // 法一：
            return head_->next_->data_;

            // 法二（好）：
            //  Iterator it(head_->next_);
            //  return it.node_ptr_->data_;
        }
        // 获得最后一个有效节点元素值
        T back() const
        {
            // 法一：
            return head_->prev_->data_;

            // 法二（好）：
            //  Iterator it(head_->prev_);
            //  return it.node_ptr_->data_;
        }

    private:
        // 可以添加你需要的成员函数
    };
};
