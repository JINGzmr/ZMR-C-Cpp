// #include <iostream>
// using namespace std;

// int fun(int a , int b = 20 , int c = 30)
// {
// return a+b+c;
// }

// int main()
// {
// // fun();//
// fun(10);
// fun(10,10);
// cout << fun(10) << fun(10,10) <<endl;
// }
// #include <iostream>

// using namespace std;
// double PI = 3.14;
// class Circle
// {
// 	//访问权限
// 	//公共权限
// public:

// 	//属性(变量)
// 	int r;

// 	//行为（一般是一个函数）
// 	//获取圆的周长
// 	double zc()
// 	{
// 		return 2*PI*r;
// 	}

// };

// main()
// {
// 	//通过圆类创建具体的圆（对象）
//     //实例化 （通过一个类 创建一个对象的过程）
// 	Circle c1;
// 	//给圆对象的属性进行赋值
// 	c1.r = 10;

// 	cout << "圆的周长为： " << c1.zc() << endl ;

// }

// #include<iostream>
// using namespace std;
// class stu{
//     public:

//     string name;
//     int id;

//     void xw()
//     {
//         getline(cin,name);
//         cin >> id;

//         cout << name << endl << id << endl;
//     }
// };

// int main()
// {
//     stu pp;
//     pp.xw();
// }

// #include <iostream>
// using namespace std;

// int main() {
//     int a = 66;
//     int b = 333;
//     int c = a % b;
//     cout << c << endl; // 输出 1
//     return 0;
// }

// int gdb(int a,int b)
// {
//     return b?gdb(b,a%b):a;
// }

// #include<iostream>
// using namespace std;

// #define PI 3.14

// class Circle
// {
//     public:
//     int r;

//     double zuochang(int r)
//     {
//         return 2*PI*r;
//     }
// };

// // const double PI = 3.14;

// int main()
// {
//     Circle c;
//     c.r=10;

//     cout << "周长为： "  << c.zuochang(c.r) << endl;

//     return 0;
// }

// #include<iostream>
// using namespace std;

// class Person {
//   private:
//     string name;
//     int age;

//   public:
//     // 构造函数
//     Person(string n, int a) {
//       name = n;
//       age = a;
//       cout << "构造函数被调用" << endl;
//     }

//     // // 析构函数
//     // ~Person() {
//     //   cout << "析构函数被调用" << endl;
//     // }

//     // 成员函数
//     void sayHello() {
//       cout << "Hello, my name is " << name << " and I'm " << age << " years old." << endl;
//     }
// };

// int main() {
//   // 创建一个 Person 对象
//   Person person1("Alice", 25);

//   // 调用成员函数
//   person1.sayHello();

//   // 对象会在这里自动销毁，因此会调用析构函数
//   return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// typedef struct {
//     int apple;
//     int count_apple;
//     int orange;
//     int count_orange;
//     pthread_mutex_t lock;
//     pthread_cond_t fmther;
//     pthread_cond_t sonCond;
//     pthread_cond_t daughterCond;
// } Plate;

// // 父亲放苹果的函数
// void* add_apple(void* arg) {
//     Plate* plate = (Plate*)arg;
//     while (1) {
//         // sleep(1);
//         pthread_mutex_lock(&plate->lock);
//         while (plate->orange == 1 || plate->apple == 1) {
//             pthread_cond_wait(&plate->fmther, &plate->lock);
//         }
//         plate->apple++;
//         plate->count_apple++;
//         printf("父亲: 开始放第 %d 个苹果\n", plate->count_apple);
//         pthread_cond_signal(&plate->sonCond);
//         pthread_mutex_unlock(&plate->lock);
//     }
// }

// // 母亲放橘子的函数
// void* add_orange(void* arg) {
//     Plate* plate = (Plate*)arg;
//     while (1) {
//         // sleep(1);
//         pthread_mutex_lock(&plate->lock);
//         while (plate->orange == 1 || plate->apple == 1) {
//             pthread_cond_wait(&plate->fmther, &plate->lock);
//         }
//         plate->orange++;
//         plate->count_orange++;
//         printf("母亲: 开始放第 %d 个橘子\n", plate->count_orange);
//         pthread_cond_signal(&plate->daughterCond);
//         pthread_mutex_unlock(&plate->lock);
//     }
// }

// // 儿子吃苹果的函数
// void* eat_apple(void* arg) {
//     Plate* plate = (Plate*)arg;
//     while (1) {
//         // sleep(1);
//         pthread_mutex_lock(&plate->lock);
//         while (plate->apple < 1) {
//             pthread_cond_wait(&plate->sonCond, &plate->lock);
//         }
//         plate->apple = 0;
//         printf("儿子: 开始吃第 %d 个苹果\n", plate->count_apple);
//         pthread_cond_signal(&plate->fmther);
//         pthread_mutex_unlock(&plate->lock);
//     }
// }

// // 女儿吃橘子的函数
// void* eat_orange(void* arg) {
//     Plate* plate = (Plate*)arg;
//     while (1) {
//         // sleep(1);
//         pthread_mutex_lock(&plate->lock);
//         while (plate->orange < 1) {
//             pthread_cond_wait(&plate->daughterCond, &plate->lock);
//         }
//         plate->orange = 0;
//         printf("女儿: 开始吃第 %d 个橘子\n", plate->count_orange);
//         pthread_cond_signal(&plate->fmther);
//         pthread_mutex_unlock(&plate->lock);
//     }
// }

// int main() {
//     Plate plate;
//     plate.apple = 0;
//     plate.count_apple = 0;
//     plate.orange = 0;
//     plate.count_orange = 0;
//     pthread_mutex_init(&plate.lock, NULL);
//     pthread_cond_init(&plate.fmther, NULL);
//     pthread_cond_init(&plate.sonCond, NULL);
//     pthread_cond_init(&plate.daughterCond, NULL);

//     pthread_t father, mother, son, daughter;
//     pthread_create(&father, NULL, add_apple, &plate);
//     pthread_create(&mother, NULL, add_orange, &plate);
//     pthread_create(&son, NULL, eat_apple, &plate);
//     pthread_create(&daughter, NULL, eat_orange, &plate);

//     pthread_join(father, NULL);
//     pthread_join(mother, NULL);
//     pthread_join(son, NULL);
//     pthread_join(daughter, NULL);

//     pthread_mutex_destroy(&plate.lock);
//     pthread_cond_destroy(&plate.fmther);
//     pthread_cond_destroy(&plate.sonCond);
//     pthread_cond_destroy(&plate.daughterCond);

//     return 0;
// }

// #include <iostream>
// #include <string>
// using namespace std;

// class Person {
// public:
//     string name;
//     int age;

//     // 深拷贝
//     Person* DeepCopy() {
//         Person* p = new Person();
//         p->name = this->name;
//         p->age = this->age;
//         return p;
//     }

//     // 浅拷贝
//     Person* ShallowCopy() {
//         return this;
//     }
// };

// int main() {
//     // 创建一个原始对象
//     Person* john = new Person();
//     john->name = "John";
//     john->age = 25;

//     // 浅拷贝
//     Person* johnCopy = john->ShallowCopy();

//     // 修改原始对象的属性
//     john->name = "Jack";
//     john->age = 30;

//     // 输出浅拷贝对象的属性
//     cout << johnCopy->name << endl; // 输出 Jack
//     cout << johnCopy->age << endl;  // 输出 30

//     // 深拷贝
//     johnCopy = john->DeepCopy();

//     // 修改原始对象的属性
//     john->name = "Tom";
//     john->age = 35;

//     // 输出深拷贝对象的属性
//     cout << johnCopy->name << endl; // 输出 Jack
//     cout << johnCopy->age << endl;  // 输出 30

//     delete johnCopy;
//     delete john;

//     return 0;
// }

// #include <iostream>
// using namespace std;

// class MyClass {
// public:
//     int* a;

//     MyClass(int value) {
//         a = new int(value);
//     }

//     ~MyClass() {
//         delete a;
//     }

//     MyClass* ShallowCopy() {
//         return this;
//     }
// };

// int main() {
//     MyClass* obj1 = new MyClass(10);
//     MyClass* obj2 = obj1->ShallowCopy();

//     // 修改原始对象的a属性
//     *obj1->a = 20;

//     // 输出拷贝对象的a属性
//     cout << *obj2->a << endl;  // 输出 20  -->因为共享一块内存

//     delete obj1;
//     delete obj2;

//     return 0;
// }

// #include <iostream>
// using namespace std;

// class MyClass {

// public:
//     int *value;

//     // 默认构造函数
//     MyClass() {
//         value = 0;
//         cout << "Default constructor called." << endl;
//     }

//     // 带参数的构造函数
//     MyClass(int* v) {
//         value = v;
//         cout << "Parameterized constructor called." << endl;
//     }

//     // 拷贝构造函数
//     MyClass(const MyClass& other) {  //注意我们不需要修改原来的值，所以传的值用const修饰，且是“引用&”
//        this->value = other.value;
//         cout << "Copy constructor called." << endl;
//     }

//     // 成员函数
//     void printValue() {
//         cout << "Value = " << value << endl;
//     }
// };

// int main() {
//     // 使用默认构造函数创建对象
//     MyClass obj1;  //不要这样：obj1 ( ) ---> 没有括号（）
//     obj1.printValue();

//     // 使用带参数的构造函数创建对象
//     int a = 10;
//     int *x = &a;
//     MyClass obj2(x);
//     obj2.printValue();

//     // 使用拷贝构造函数创建对象
//     MyClass obj3 = obj2;   //用括号法也ok
//     obj3.printValue();

//     obj3.value=666;
//     obj3.printValue();
//     obj2.printValue();

//     return 0;
// }

// #include <iostream>

// template <class T>
// struct node
// {
//     node<T> *prev_;
//     node<T> *next_;
//     T data_;
//     node(const T &data)
//         : data_(data), prev_(nullptr), next_(nullptr)
//     {
//     }
//     node()
//         : prev_(nullptr), next_(nullptr)
//     {
//     }
//     ~node()
//     {
//     }
// };

// template <class T>
// class list
// {
// public:
//     typedef node<T> node_;
//     node_ *head_;

//     list()
//         : head_(new node_<T>())
//     {
//         head_->prev_ = head_->next_ = head_;
//     }

//     ~list()
//     {
//         node_ *p = head_;
//         while (p != nullptr)
//         {
//             node_ *q = p->next_;
//             delete p;
//             p = q;
//         }
//     }

//     void push_back(const T &data)
//     {
//         node_ *p = new node_<T>(data);
//         p->prev_ = head_->prev_;
//         p->next_ = head_;
//         head_->prev_->next_ = p;
//         head_->prev_ = p;
//     }

//     void print()
//     {
//         node_ *p = head_->next_;
//         while (p != head_)
//         {
//             std::cout << p->data_ << " ";
//             p = p->next_;
//         }
//         std::cout << std::endl;
//     }
// };

// int main()
// {
//     list<int> mylist;
//     mylist.push_back(1);
//     mylist.push_back(2);
//     mylist.push_back(3);
//     mylist.print();
//     return 0;
// }

// #include<iostream>
// using namespace std;

// class goods
// {
// private:
//     int pen;
//     int pencil;

// public:
// // 带参数的构造函数（用于变量的初始化）-->函数名要和类的名字一样，返回值
//     //传统方式初始化
//     // goods(int a, int b)
//     // {
//     //     pen = a;
//     //     pencil = b;
//     // }

//     //初始化列表方式初始化
//     goods(int a, int b):pen(a),pencil(b)
//     {}

// //成员函数  --->函数名不一定要和类的名字一样，且有返回值
//     void print_goods()
//     {
//         cout << "pen的价格是：" << pen << endl;
//         cout << "pencil的价格是："<< pencil << endl;
//     }
// };

// int main()
// {
//     goods mygoods(12,20); //两种不同的初始化均用该行代码
//     mygoods.print_goods();
// }

// #include<iostream>
// #include<string>
// using namespace std;

// class phone
// {
// // private: //不能设置为私有，否者person类里的m_phone.m_phonename该语句报错，显示无法访问m_phonename
// public:
//     string m_phonename;

// public:
//     phone (string a):m_phonename(a)
//     {
//         cout << "phone 构造函数调用" << endl;
//     }

//     ~phone ()
//     {
//         cout << "phone 析构函数调用" << endl;
//     }
// };

// class person
// {
// private:
//     string m_name;  //普通的数据成员（person类的属性/变量）
//     phone m_phone;  //phone类对象成员

// public:
//     person (string a, string b):m_name(a),m_phone(b)
//     {
//         cout << "person 构造函数调用" << endl;
//     }

//     ~person()
//     {
//         cout << "person 析构函数调用" << endl;
//     }

//     void print_()
//     {
//         cout << m_name << "的手机是：" << m_phone.m_phonename <<endl;
//     }
// };

// int main()
// {
//     person p("张三","HUAWEI");
//     p.print_();
// }

// #include<iostream>
// using namespace std;

// class MyClass {
// private:
//   static int count;
// public:
//   static void incrementCount() {
//     count++;
//   }
//   static int getCount() {
//     return count;
//   }
// };

// int MyClass::count = 0;

// int main() {
//   MyClass::incrementCount();
//   MyClass::incrementCount();
//   cout << MyClass::getCount() << endl;
//   return 0;
// }



// class person
// {
//     int A;
//     static int B; // 有没有这句，结果都为4 ，因为静态成员变量不属于每个对象
// };
// int person::B = 0;

// int main()
// {
//     person p;
//     cout << sizeof(p) << endl; //4
// }

// class Point
// {
// public:
//     Point &move(int dx, int dy)
//     {
//         x += dx;
//         y += dy;
//         cout << x << " " << y << endl;
//         return *this;
//     }

// private:
//     int x = 0;
//     int y = 0;
// };

// int main()
// {
//     Point p;
//     p.move(1, 2).move(3, 4).move(5, 6); // 链式调用
// }


// #include <iostream>
// using namespace std;
// class person
// {
// public:
// 	void func1() const // 常函数
// 	{
//         ;
// 	// ...
// 	}
	
// 	void func2() // 普通函数
// 	{
//         ;
// 	// ...
// 	}
// };

// int main()
// {
// 	const person p; // 常对象
// 	p.func1(); // 对
// 	p.func2(); // 错
// }

// class person
// {
// public:
//     void func1() const // 常成员函数
//     {
//         // ...
//     }
//     void func2() const // 常成员函数
//     {
//         // ...
//     }
// };

// int main()
// {
//     const person p; // 常对象
//     p.func1(); // 可以调用
//     p.func2(); // 可以调用
//     return 0;
// }

// #include<iostream>
// using namespace std;


// class Building
// {
// 	//相当于一个函数声明，表示gay这个函数是类Building的好朋友，可以谁便访问任何成员，包括private的
// 	friend void gay(Building * building); // 前面加上`friend`，后面加上`;`
// public:
// 	Building()
// 	{
// 		this->m_sittingroom = "客厅";
// 		this->m_bedroom = "卧室";
// 	}

// 	string m_sittingroom;

// private:
// 	string m_bedroom;
// };

// // 全局函数
// void gay(Building * building)
// {
// 	cout << "gay正在访问：" << building->m_sittingroom << endl;
// 	cout << "gay正在访问：" << building->m_bedroom << endl;
// }

// int main()
// {
// 	Building p;
	
// 	//法一：
// 	// Building *ptr = &p;  
// 	// gay(ptr);
	
// 	//法二：
// 	gay(&p);
// } 

// #include<iostream>
// using namespace std;

// int main(int argc, char* argv[])
// {
// 	int a,b;
// 	cin >> a >> b;
// 	int c = a+b;
// 	c+=3;
// 	cout << c << endl;

// }
// #include <iostream>
// using namespace std;

// int main(int argc, char* argv[]) {
//   int arr[] = {1, 2, 3, 4, 5};
//   int n = sizeof(arr) / sizeof(arr[0]);
//   int sum = 0;
//   for (int i = 0; i < n; i++) {
//     sum += arr[i];
//   }
//   cout << "The sum of the array is: " << sum << endl;
//   return 0;
// }


// #include<iostream>
// using namespace std;

// class Base
// {
// public:
// 	int a;

// protected:
// 	int b;

// private:
// 	int c;	// 虽然son访问不到，但也会继承到son中
// };

// class son : public Base
// {
// public:
// 	int d;
// };

// int main()
// {
// 	cout << sizeof(son) << endl;  //16 = a+b+c+d  即4（int）*4（abcd）=16
// }


// class Base
// {
// public:
// 	int a = 100;
// };

// class son : public Base
// {
// public:
// 	int a = 200;
// };

// int main()
// {
// 	son s;
// 	cout << s.a << endl;
// 	cout << s.Base::a << endl;
// }


// #include<iostream>
// using namespace std;
// #include<string>

// class CPU
// {
// public:
// 	virtual void jisuan() = 0;
// };

// // class xianka
// // {
// // public:
// // 	virtual void xianshi() = 0;
// // };

// // class neicuntiao
// // {
// // public:
// // 	virtual void cuncu() = 0;	
// // };


// class intel_cpu:public CPU
// {
// public:
// 	void jisuan()
// 	{
// 		cout << "intel cpu 在工作" << endl;
// 	}
// };

// int main()
// {
// 	intel_cpu ic;
// 	ic.jisuan();
// }



#include<iostream>
using namespace std;

class AbstractCalculator
{
public:
	virtual int getresult() = 0;

	int a;
	int b;
};

//加法
class AddCalculator:public AbstractCalculator
{
public:
	int getresult()
	{
		return a+b;
	}
};

//乘法
class SubCalculator:public AbstractCalculator
{
public:
	int getresult()
	{
		return a*b;
	}
};

int main()
{
	// 法一：本地变量
	AddCalculator add;
	AbstractCalculator *ptr1 ;
	ptr1 = &add;
	ptr1->a=1;
	ptr1->b=2;
	cout << ptr1->getresult() << endl;

	//法二：new到堆区
	AbstractCalculator *ptr2 = new SubCalculator;
	ptr2->a = 1;
	ptr2->b = 2;
	cout << ptr2->getresult() << endl;
	delete ptr2;
}
