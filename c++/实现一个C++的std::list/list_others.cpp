#include <iostream>
// 使用你的名字替换YOUR_NAME
namespace MAXIBO
{
    template <class T>
    // list存储的节点
    // 可以根据你的需要添加适当的成员函数与成员变量
    struct node
    {
        node<T> *prev_;
        node<T> *next_;
        T data_;
        // 构造函数
        node(const T &data)
            : data_(data), prev_(nullptr), next_(nullptr)
        {
        }
        node()
            : prev_(nullptr), next_(nullptr)
        {
        }
        // 稀构函数
        ~node()
        {
        }
    };

    template <class T>
    // 迭代器类,(类比指针)

    struct iterator
    {
        typedef node<T> node_;
        typedef iterator<T> iterator_;
        node_ *data_;
        iterator(node_ *data)
            : data_(data)
        {
        }
        ~iterator()
        {
        }
        // 迭代到下一个节点
        //++it
        iterator_ &operator++()
        {
            node_ *next = data_->next_;
            this->data_ = next;
            return *this;
        }
        // 迭代到前一个节点
        //--it
        iterator_ &operator--()
        {
            node_ *prev = data_->prev_;
            this->data_ = prev;
            return *this;
        }
        // it++
        iterator operator++(int)
        {
            iterator tmp(this->data_);
            node_ *next = data_->next_;
            this->data_ = next;
            return tmp;
        }
        // it--
        iterator operator--(int)
        {
            iterator tmp(this->data_);
            node_ *pre = data_->prev_;
            this->data_ = pre;
            return tmp;
        }
        // 获得迭代器的值
        T &operator*()
        {
            return data_->data_;
        }
        // 获得迭代器对应的指针
        T *operator->()
        {
            return &(data_->data_);
        }
        // 重载==
        bool operator==(const iterator_ &t)
        {
            if (data_ == t.data_)
                return true;
            else
                return false;
        }
        // 重载！=
        bool operator!=(const iterator_ &t)
        {
            if (data_ == t.data_)
                return false;
            else
                return true;
        }

        //**可以添加需要的成员变量与成员函数**
    };

    template <class T>
    class list
    {
    public:
        typedef node<T> node_;
        typedef iterator<T> Iterator;

    private:
        // 可以添加你需要的成员变量
        node_ *head_; // 头节点,哨兵（不存储有效数据）
    public:
        // 构造函数
        list()
        {
            head_ = new node_;
            head_->next_ = head_;
            head_->prev_ = head_;
        }
        // 拷贝构造，要求实现深拷贝
        list(const list<T> &lt)
        {
            // 创建哨兵节点
            head_ = new node_;
            head_->next_ = head_;
            head_->prev_ = head_;
            for (auto it = lt.begin(); it != lt.end(); ++it)
            {
                push_back(*it);
            }
        }
        template <class inputIterator>
        // 迭代器构造
        list(inputIterator begin, inputIterator end)
        {
            // 创建哨兵节点
            head_ = new node_;
            head_->next_ = head_;
            head_->prev_ = head_;
            for (inputIterator it = begin; it != end; ++it)
            {
                push_back(*it);
            }
        }
        ~list()
        {
            // 遍历列表，删除每个节点
            node_ *current = head_->next_;
            while (current != head_)
            {
                node_ *next = current->next_;
                delete current;
                current = next;
            }
            // 删除哨兵节点
            delete head_;
        }
        // 拷贝赋值
        list<T> &operator=(const list<T> &lt)
        {
            if (this != &lt)
            {
                clear();

                // 遍历原列表，依次将元素插入到当前列表中
                for (auto it = lt.begin(); it != lt.end(); ++it)
                {
                    push_back(*it);
                }
            }
            return *this;
        }

        // 清空list中的数据
        void clear()
        {
            Iterator it(head_->next_);
            while (it.data_ != head_)
            {
                node_ *next = it.data_->next_;
                delete it.data_;
                it.data_ = next;
            }
            head_->next_ = head_;
            head_->prev_ = head_;
        }
        // 返回容器中存储的有效节点个数
        size_t size() const
        {
            size_t cnt = 0;
            if (this->head_->next_ != head_)
            {
                for (Iterator it = this->begin(); it != this->end(); ++it)
                {
                    cnt++;
                }
            }
            return cnt;
        }
        // 判断是否为空
        bool empty() const
        {
            if (this->head_->next_ == head_)
                return true;
            else
                return false;
        }
        // 尾插
        bool push_back(const T &data)
        {
            // 如果链表为空
            if (this->head_->next_ == head_ && this->head_->prev_ == head_)
            {
                this->head_ = new node_;
                this->head_->next_ = this->head_;
                this->head_->prev_ = this->head_;
            }

            node_ *tail = this->head_->prev_;
            node_ *cur = new node_;
            cur->data_ = data;
            cur->next_ = head_;
            cur->prev_ = tail;
            tail->next_ = cur;
            head_->prev_ = cur;
            return true;
        }
        // 头插
        bool push_front(const T &data)
        {
            // 如果链表为空
            if (this->head_->next_ == NULL && this->head_->prev_ == NULL)
            {
                this->head_ = new node_;
                this->head_->next_ = this->head_;
                this->head_->prev_ = this->head_;
            }

            node_ *first = this->head_->next_;
            node_ *cur = new node_;
            cur->data_ = data;
            cur->next_ = first;
            cur->prev_ = head_;
            first->prev_ = cur;
            head_->next_ = cur;
            return true;
        }
        // 尾删
        bool pop_back()
        {
            node_ *pre = this->head_->prev_->prev_;
            node_ *cur = this->head_->prev_;

            pre->next_ = this->head_;
            head_->prev_ = pre;

            cur->next_ = NULL;
            cur->prev_ = NULL;
            delete cur;
            return true;
        }
        // 头删
        bool pop_front()
        {
            node_ *next = this->head_->next_->next_;
            node_ *cur = this->head_->next_;

            next->prev_ = this->head_;
            head_->next_ = next;

            cur->next_ = NULL;
            cur->prev_ = NULL;
            delete cur;
            return true;
        }
        // 默认新数据添加到pos迭代器的后面,根据back的方向决定插入在pos的前面还是后面
        bool insert(Iterator pos, const T &data, bool back = true)
        {
            node_ *tmp = new node_(data);
            node_ *next = pos.data_->next_;
            node_ *pre = pos.data_->prev_;
            node_ *cur = pos.data_;
            if (back)
            {
                tmp->prev_ = cur;
                tmp->next_ = next;
                next->prev_ = tmp;
                cur->next_ = tmp;
                return true;
            }
            else
            {
                tmp->next_ = cur;
                tmp->prev_ = pre;
                pre->next_ = tmp;
                cur->prev_ = tmp;
                return true;
            }
        }
        // 删除pos位置的元素
        bool erase(Iterator pos)
        {
            if (pos.data_ == head_)
            {
                return true;
            }
            node_ *cur = pos.data_;
            node_ *pre = cur->prev_;
            node_ *next = cur->next_;
            pre->next_ = next;
            next->prev_ = pre;

            cur->next_ = NULL;
            cur->prev_ = NULL;
            delete cur;
            return true;
        }

        // 获得list第一个有效节点的迭代器
        Iterator begin() const
        {
            Iterator it(head_->next_);
            return it;
        }

        // 获得list最后一个节点的下一个位置，可以理解为nullptr
        Iterator end() const
        {
            Iterator it(head_->next_);
            while (it.data_ != head_)
            {
                it++;
            }
            return it;
        }
        // 查找data对应的迭代器
        Iterator find(const T &data) const
        {
            Iterator it(head_->next_);
            for (size_t i = 0; i < this->size(); i++)
            {
                it++;
                if (it.data_->data_ == data)
                    return it;
            }
            return nullptr;
        }
        // 获得第一个有效节点
        T front() const
        {
            Iterator it(head_->next_);

            return it.data_->data_;
        }
        // 获得最后一个有效节点
        T back() const
        {
            Iterator it(head_->prev_);

            return it.data_->data_;
        }

    private:
        // 可以添加你需要的成员函数
    };
};