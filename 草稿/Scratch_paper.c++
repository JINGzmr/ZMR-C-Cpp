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
//       cout << "Hello, my name is " << name << " and I'm " << age << " years
//       old." << endl;
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
//     MyClass(const MyClass& other) {
//     //注意我们不需要修改原来的值，所以传的值用const修饰，且是“引用&”
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
// // private:
// //不能设置为私有，否者person类里的m_phone.m_phonename该语句报错，显示无法访问m_phonename
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

// #include <iostream>
// using namespace std;

// class AbstractCalculator
// {
// public:
// 	virtual int getresult()
// 	{
// 		return 0;
// 	}

// 	int a;
// 	int b;
// };

// // 加法
// class AddCalculator : public AbstractCalculator
// {
// public:
// 	int getresult()
// 	{
// 		return a + b;
// 	}
// };

// // 乘法
// class SubCalculator : public AbstractCalculator
// {
// public:
// 	int getresult()
// 	{
// 		return a * b;
// 	}
// };

// int main()
// {
// 	// 法一：本地变量
// 	AddCalculator add;
// 	AbstractCalculator *ptr1;
// 	ptr1 = &add;
// 	ptr1->a = 1;
// 	ptr1->b = 2;
// 	cout << ptr1->getresult() << endl;

// 	// 法二：new到堆区
// 	AbstractCalculator *ptr2 = new SubCalculator;
// 	ptr2->a = 1;
// 	ptr2->b = 2;
// 	cout << ptr2->getresult() << endl;
// 	delete ptr2;
// }

// #include<iostream>
// using namespace std;

// class drink
// {
// public:
// 	//煮水
// 	virtual void boil() = 0;

// 	//冲泡
// 	virtual void brew() = 0;

// 	//导入杯中
// 	virtual void pour() = 0;

// 	//加入辅料
// 	virtual void put() = 0;

// 	//制作饮品
// 	void makedrink()
// //抽象类也可以定义其他东西（包括不是虚函数的其他成员函数）
// 	{
// 		boil();
// 		brew();
// 		pour();
// 		put();
// 	}

// };

// class coffee:public drink
// {
// public:
// 	//煮水
// 	virtual void boil()
// 	{
// 		cout << "咖啡-煮水" << endl;
// 	}

// 	//冲泡
// 	virtual void brew()
// 	{
// 		cout << "咖啡-冲泡" << endl;
// 	}

// 	//导入杯中
// 	virtual void pour()
// 	{
// 		cout << "咖啡-导入杯中" << endl;
// 	}

// 	//加入辅料
// 	virtual void put()
// 	{
// 		cout << "咖啡-加入辅料" << endl;
// 	}

// };

// class tea:public drink
// {
// public:
// 	//煮水
// 	virtual void boil()
// 	{
// 		cout << "茶-煮水" << endl;
// 	}

// 	//冲泡
// 	virtual void brew()
// 	{
// 		cout << "茶-冲泡" << endl;
// 	}

// 	//导入杯中
// 	virtual void pour()
// 	{
// 		cout << "茶-导入杯中" << endl;
// 	}

// 	//加入辅料
// 	virtual void put()
// 	{
// 		cout << "茶-加入辅料" << endl;
// 	}

// };

// int main()
// {
// 	drink *ptr1 = new coffee;
// 	ptr1->makedrink();
// 	delete ptr1;

// 	drink *ptr2 = new tea;
// 	ptr2->boil();
// 	ptr2->brew();
// 	ptr2->pour();
// 	ptr2->put();
// 	delete ptr2;
// }

// #include <iostream>
// using namespace std;

// // 抽象类
// class CPU
// {
// public:
// 	virtual void caclulate() = 0;
// };

// class VideoCard
// {
// public:
// 	virtual void display() = 0;
// };

// class Memory
// {
// public:
// 	virtual void storage() = 0;
// };

// // 电脑组装
// class Computer
// {
// public:
// 	// 构造函数
// 	Computer(CPU *c, VideoCard *v, Memory *m)
// 	{
// 		cpu = c;
// 		videocard = v;
// 		memory = m;
// 	}

// 	// 成员函数
// 	void work()
// 	{
// 		//让零件工作起来，调用接口
// 		cpu->caclulate();
// 		videocard->display();
// 		memory->storage();
// 	}

// 	//析构函数，释放3个电脑零件
// 	~Computer()
// 	{
// 		if(cpu!=nullptr)
// 		{
// 			delete cpu;
// 			cpu = nullptr;
// 		}

// 		if(videocard!=nullptr)
// 		{
// 			delete videocard;
// 			videocard = nullptr;
// 		}

// 		if(memory!=nullptr)
// 		{
// 			delete memory;
// 			memory = nullptr;
// 		}
// 	}

// private:
// 	//三个电脑零件
// 	CPU *cpu;
// 	VideoCard *videocard;
// 	Memory *memory;
// };

// // intel
// class intel_cpu : public CPU
// {
// public:
// 	void caclulate()
// 	{
// 		cout << "intel cpu 在工作" << endl;
// 	}
// };

// class intel_VideoCard : public VideoCard
// {
// public:
// 	void display()
// 	{
// 		cout << "intel display 在工作" << endl;
// 	}
// };

// class intel_Memory : public Memory
// {
// public:
// 	void storage()
// 	{
// 		cout << "intel storage 在工作" << endl;
// 	}
// };

// // lenovo
// class lenovo_cpu : public CPU
// {
// public:
// 	void caclulate()
// 	{
// 		cout << "lenovo cpu 在工作" << endl;
// 	}
// };

// class lenovo_VideoCard : public VideoCard
// {
// public:
// 	void display()
// 	{
// 		cout << "lenovo display 在工作" << endl;
// 	}
// };

// class lenovo_Memory : public Memory
// {
// public:
// 	void storage()
// 	{
// 		cout << "lenovo storage 在工作" << endl;
// 	}
// };

// int main()
// {
// 	//第一台电脑组装（法一）
// 	//这三个电脑零件在Computer的析构函数里释放（也可以在下面的computer_ptr1后面释放）
// 	CPU *intel_cpu_ptr = new intel_cpu;
// 	VideoCard *intel_VideoCard_ptr = new intel_VideoCard;
// 	Memory *intel_Memory_ptr = new intel_Memory;

// 	Computer *computer_ptr1 = new Computer(intel_cpu_ptr,
// intel_VideoCard_ptr, intel_Memory_ptr); 	computer_ptr1->work(); 	delete
// computer_ptr1;

// 	cout << "-------------------" << endl;
// 	//第二台电脑组装（法二）
// 	Computer *computer_ptr2 = new Computer(new lenovo_cpu, new
// lenovo_VideoCard, new lenovo_Memory); 	computer_ptr2->work(); 	delete
// computer_ptr2;

// 	cout << "-------------------" << endl;
// 	//第三台电脑组装（法二）
// 	Computer *computer_ptr3 = new Computer(new lenovo_cpu, new
// intel_VideoCard, new intel_Memory); 	computer_ptr3->work(); 	delete
// computer_ptr3;

// }

// #include<iostream>
// using namespace std;

// class Base
// {
// friend void func();
// private:
//     int a = 6;
// };

// void func()
// {
//     Base b;
//     std::cout << b.a << endl;

// }

// int main()
// {
//     func();
// }

// #include <iostream>
// using namespace std;

// template <typename T>
// void func(T &a, T &b)
// {
//     T temp = a;
//     a = b;
//     b = temp;
// };

// int main()
// {
//     int a = 10;
//     int b = 20;

//     func(a, b); // 自动类型推导
//     cout << a << b << endl;

//     func<int>(a, b); // 显示指定类型
//     cout << a << b << endl;
// }

// #include <iostream>
// #include <cstring>
// using namespace std;

// template <class T>
// void My_swap(T &a, T &b)
// {
//     T temp = a;
//     a = b;
//     b = temp;
// }

// // 升序
// template <class T>
// void My_sort(T arr[], int len)
// {
//     for (int i = 0; i < len - 1; i++)
//     {
//         for (int j = 0; j < len - 1 - i; j++)
//         {
//             if (arr[j] > arr[j + 1])
//             {
//                 My_swap(arr[j], arr[j + 1]);
//             }
//         }
//     }
// }

// int main()
// {
//     //排序字符串
//     char arr[] = "adbce";
//     My_sort(arr, strlen(arr));
//     puts(arr);

//     //排序int数组
//     int arr1[] = {7, 5, 1, 3, 9};
//     My_sort(arr1, sizeof(arr1)/sizeof(int));
//     for (int i = 0; i < sizeof(arr1)/sizeof(int); i++)
//     {
//         printf("%d", arr1[i]);
//     }
// }

// #include<iostream>
// using namespace std;

// template<class T>
// class Base
// {
// public:
//     void func()
//     {
//         cout << top << endl;
//     }

//     Base(const T& a)
//     {
//         top = a;
//     }

// private:
//     T top;
// };

// int main()
// {
//     Base<int> p(10);
//     p.func();
// }

// #include<iostream>
// using namespace std;

// class Base
// {
// public:
//     Base()
//     {
//         printf("this is fun()");
//     }

// };

// int main()
// {
//     Base b;

// }

// #include <netinet/in.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <iostream>

// using namespace std;

// int main() {
//     // 创建Socket
//     // 第一个参数：AF_INET表示是ipv4，ipv6是AF_INET6；
//     // 第二个参数：传输层协议 这里是流式传输协议（一般tcp用）；
//     // 第三个参数：0表示采用流式传输协议中的tcp协议
//     // 返回值：失败返回-1
//     int server_socket = socket(AF_INET, SOCK_STREAM, 0);

//     if (server_socket == -1) {
//         cout << "Error: Failed to create socket!" << endl;
//         return -1;
//     }

//     // 设置服务器地址和端口号
//     struct sockaddr_in server_addr;
//     memset(&server_addr, 0, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(8888);
//     server_addr.sin_addr.s_addr = INADDR_ANY;

//     // 绑定Socket到地址和端口号
//     // 第一个参数：用于监听的文件描述符，由socket（）返回值得到
//     //
//     第二个参数：结构体(要另外对里面的成员进行初始化，如上几行代码)，存的是本地的ip及端口（一定是大端的-->网络字节序）
//     // 第三个参数：结构体的大小
//     // 返回值:失败返回-1
//     int ret = bind(server_socket, (struct sockaddr*)&server_addr,
//                    sizeof(server_addr));
//     if (ret == -1) {
//         cout << "Error: Failed to bind socket to address and port!" << endl;
//         close(server_socket);
//         return -1;
//     }

//     // 监听Socket
//     //
//     第一个参数：用于监听的文件描述符，由socket（）返回值得到，并由bind函数做了绑定
//     // 第二个参数：一次性能够检测到客户端连接的数量，最大为128（该参数的大小
//     和
//     // 客户端与服务器之间最多可以建立多少个连接 没有关系） 返回值：失败返回-1
//     // listen（）内部维护了一个任务队列，最多可以存储128个请求
//     ret = listen(server_socket, 5);
//     if (ret == -1) {
//         cout << "Error: Failed to listen on socket!" << endl;
//         close(server_socket);
//         return -1;
//     }

//     // 等待客户端连接
//     struct sockaddr_in client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);
//     // 第一个参数：文件描述符
//     // 第二个参数：结构体（不用初始化，调用成功后，里面存的是 发起连接请求的
//     // 客户端的 ip及端口），可以理解为accept（）函数的传出参数
//     // 第三个参数：结构体大小
//     // 返回值：成功 得到用于通信的文件描述符，失败返回-1
//     // 阻塞，直到有客户端连接connect
//     int client_socket =
//         accept(server_socket, (struct sockaddr*)&client_addr,
//         &client_addr_len);
//     if (client_socket == -1) {
//         cout << "Error: Failed to accept client connection!" << endl;
//         close(server_socket);
//         return -1;
//     }

//     // 接收客户端数据
//     char buffer[1024] = {0};
//     ret = recv(client_socket, buffer, sizeof(buffer), 0);
//     if (ret == -1) {
//         cout << "Error: Failed to receive data from client!" << endl;
//         close(client_socket);
//         close(server_socket);
//         return -1;
//     }

//     cout << "Received data from client: " << buffer << endl;

//     // 发送响应数据到客户端
//     const char* data = "Hello, client!";
//     ret = send(client_socket, data, strlen(data), 0);
//     if (ret == -1) {
//         cout << "Error: Failed to send response data to client!" << endl;
//         close(client_socket);
//         close(server_socket);
//         return -1;
//     }

//     // 关闭Socket连接
//     // 参数:要关闭的套接字对应的文件描述符
//     // 返回值：失败返回-1
//     close(client_socket);
//     close(server_socket);

//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <cstring>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>

// using namespace std;

// const int PORT = 8888;
// const char* SERVER_IP = "127.0.0.1";

// int main() {
//     // 创建一个TCP连接对象
//     int client_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (client_socket < 0) {
//         perror("socket creation failed");
//         return EXIT_FAILURE;
//     }

//     // 客户端连接的IP和端口号
//     struct sockaddr_in server_address;
//     memset(&server_address, 0, sizeof(server_address));
//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(PORT);
//     if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
//         perror("invalid address");
//         return EXIT_FAILURE;
//     }

//     // 连接服务器
//     // 第一个参数：用于通信的文件描述符
//     //
//     第二个参数：结构体(要另外对里面的成员进行初始化，如上几行代码)，服务器绑定的是什么ip和端口，这里就初始化相同的数据
//     // 第三个参数：结构体的大小
//     // 返回值：失败返回-1
//     //
//     注：客户端不用bind（）对ip和端口进行绑定，因为客户端会随机绑定一个ip和端口，服务器中accept（）得到的ip和端口便是客户端随机绑定的
//     // （因为服务器不会主动连接客户端）
//     int connect_result = connect(client_socket, (struct
//     sockaddr*)&server_address, sizeof(server_address)); if (connect_result ==
//     -1) {
//         perror("connection failed");
//         return EXIT_FAILURE;
//     }

//     // 发送数据(write() or send())
//     // 第一个参数：用于通信的文件描述符
//     // 第二个参数：指针，指向一块内存，存的是要发送的数据
//     // 第三个参数：发送数据的大小
//     // 第四个参数：一般为0
//     // 返回值: >0 实际的发送的字节数,一般等于第三个参数;  =-1 发送失败
//     string message = "Hello, server!";
//     if (send(client_socket, message.c_str(), message.length(), 0) < 0) {
//         perror("send failed");
//         return EXIT_FAILURE;
//     }

//     // 接收数据（read() or recv()）
//     // 第一个参数：用于通信的文件描述符
//     // 第二个参数：指针，指向一块内存，用于存储接收的数据
//     // 第三个参数：内存的最大容量
//     // 第四个参数：一般为0
//     // 返回值：>0 实际接收的字节数； =0 对方断开连接；  =-1 接收数据失败
//     char buffer[1024] = {0};
//     int bytes_received = recv(client_socket, buffer, 1024, 0);
//     if (bytes_received < 0) {
//         perror("receive failed");
//         return EXIT_FAILURE;
//     }

//     //
//     return EXIT_SUCCESS;

// // 处理接收到的数据
//     cout << "Received from server: " << buffer << endl;

//     // 关闭连接
//     // 参数:要关闭的套接字对应的文件描述符
//     // 返回值：失败返回-1
//     close(client_socket);

//     return EXIT_SUCCESS;
// }

// #include <iostream>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     for (int i = 1; i <= n; i++) {

//     }
// }

// #include <iostream>
// #include <vector>

// // 定义一个函数来生成杨辉三角的前n行
// std::vector<std::vector<int>> generatePascalTriangle(int numRows) {
//     std::vector<std::vector<int>> triangle;

//     for (int i = 0; i < numRows; i++) {
//         std::vector<int> row(i + 1, 1);

//         for (int j = 1; j < i; j++) {
//             row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
//         }

//         triangle.push_back(row);
//     }

//     return triangle;
// }

// // 打印杨辉三角
// void printPascalTriangle(int numRows) {
//     std::vector<std::vector<int>> triangle = generatePascalTriangle(numRows);

//     for (int i = 0; i < numRows; i++) {
//         int numSpaces = numRows - i;

//         // 添加前导空格
//         for (int j = 0; j < numSpaces; j++) {
//             std::cout << " ";
//         }

//         for (int j = 0; j <= i; j++) {
//             std::cout << triangle[i][j] << " ";
//         }

//         std::cout << std::endl;
//     }
// }

// int main() {
//     int numRows;
//     std::cout << "请输入要打印的杨辉三角的行数：";
//     std::cin >> numRows;

//     printPascalTriangle(numRows);

//     return 0;
// }

// vector<int> ivec;           // ivec保存int类型的对象
// vector<vector<int>> ivec1;  // 该向量的元素是vector对象

// vector<int> ivec{"hello", "world"};

// vector<int> ivec(10, 1);//10个int类型的元素，每个初始化为1

// vector<int> ivec(10);//10个int类型的元素，默认初始化为0

// int main() {
//     // std::vector<int> ivec;
//     // for (int i = 0; i < 100; i++) {
//     //     ivec.push_back(i);
//     // }

//     // // 使用范围-based for 循环遍历并打印每个元素
//     // for (const int& element : ivec) { //
//     // 把ivec的每个元素赋给int类型的变量element（相当于const int&
//     // element=ivec[i]）
//     //     std::cout << element << " ";  // 对element输出
//     // }

//     std::vector<int> v{1, 2, 3, 4, 5};
//     for (auto &i : v) { // i是一个引用
//         i *= i;         //
//         可以通过改变i来改变vector里的值（如果i不是引用，则输出还是12345）
//     }
//     for (auto i : v) {
//         std::cout << i << " "; // 1 4 9 16 25
//     }
// }

// #include <vector>
// #include <iostream>

// int main() {
//     // 创建一个包含3行2列的二维整数数组
//     std::vector<std::vector<int>> twoDArray(3, std::vector<int>(2));

//     // 向二维数组中添加一些值
//     twoDArray[0][0] = 1;
//     twoDArray[0][1] = 2;
//     twoDArray[1][0] = 3;
//     twoDArray[1][1] = 4;
//     twoDArray[2][0] = 5;
//     twoDArray[2][1] = 6;

//     // 访问和输出二维数组中的值
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 2; j++) {
//             std::cout << twoDArray[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }

//   // 使用范围-based for 循环遍历二维数组并输出其内容
//     for (const auto& row : twoDArray) {
//         for (const auto& element : row) {
//             std::cout << element << " ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }

// #include <iostream>
// #include <vector>
// using namespace std;

// int main() {
//     int n;
//     vector<vector<int>> v;

//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         vector<int> row(i + 1, 1);

//         for (int j = 1; j < i; j++) {
//             row[j] = v[i - 1][j - 1] + v[i - 1][j];
//         }

//         v.push_back(row);
//     }

//     for (auto row_ : v) {
//         for (auto element : row_) {
//             cout << element << " ";
//         }
//         cout << endl;
//     }
// }

// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//     string str;
//     cin >> str;

//     vector<char> v;
//     int half_length = str.length() / 2;

//     for (int i = 0; i < half_length; i++) {
//         v.push_back(str[i]);
//     }

//     int flag = half_length;
//     if (str.length() % 2 != 0) {  // 说明长度为奇数
//         flag ++;
//     }

//     while (!v.empty()) {
//         char c = v.back();
//         v.pop_back();
//         if(c!=str[flag++]){
//             cout<< "不是回文";
//             return 0;
//         }
//     }
//     cout << "回文";
// }

// #include <iostream>
// #include <vector>
// using namespace std;

// int main() {
//     int n;
//     vector<vector<int>> v;

//     cin >> n;
//     for (int i = 0; i < n; i++) {
//         vector<int> row(i + 1, 1);

//         for (int j = 1; j < i; j++) {
//             row[j] = v[i - 1][j - 1] + v[i - 1][j];
//         }

//         v.push_back(row);
//     }

//     for (auto row_ : v) {
//         for (auto element : row_) {
//             cout << element << " ";
//         }
//         cout << endl;
//     }
// }

// #include <iostream>
// int main()
// {
//     std::cout << "today is a good day!"<< std::endl;
// }

// #include <vector>
// #include <iostream>

// int main() {
//     // 创建一个包含3行2列的二维整数数组
//     std::vector<std::vector<int>> twoDArray(3, std::vector<int>(2));

//     // 向二维数组中添加一些值
//     twoDArray[0][0] = 1;
//     twoDArray[0][1] = 2;
//     twoDArray[1][0] = 3;
//     twoDArray[1][1] = 4;
//     twoDArray[2][0] = 5;
//     twoDArray[2][1] = 6;

//     // 访问和输出二维数组中的值
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 2; j++) {
//             std::cout << twoDArray[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }

//   // 使用范围-based for 循环遍历二维数组并输出其内容
//     for (const auto& row : twoDArray) {
//         for (const auto& element : row) {
//             std::cout << element << " ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }

// struct Node* reverseLinkedList(struct Node* head) {
//     struct Node* prev = NULL;
//     struct Node* current = head;
//     struct Node* nextNode;

//     while (current != NULL) {
//         nextNode = current->next;
//         current->next = prev;
//         prev = current;
//         current = nextNode;
//     }

//     return prev;  // 返回逆置后的头节点
// }

// #include <stdio.h>
// #include <stdlib.h>

// // 单链表节点的定义
// struct Node {
//     int data;
//     struct Node* next;
// };

// // 从表la中删除自第i个元素起共len个元素，并插入到表lb的第j个元素之后
// void deleteAndInsert(struct Node** la, struct Node** lb, int i, int len, int
// j) {
//     if (*la == NULL) {
//         printf("Error: Source list (la) is empty.\n");
//         return;
//     }

//     // 定位删除的起始位置
//     struct Node* current = *la;
//     struct Node* prev = NULL;
//     int count = 1;
//     while (count < i && current != NULL) {
//         prev = current;
//         current = current->next;
//         count++;
//     }

//     if (count < i) {
//         printf("Error: Invalid starting position (i).\n");
//         return;
//     }

//     // 从表la中删除元素
//     struct Node* temp = current;
//     count = 0;
//     while (count < len && temp != NULL) {
//         temp = temp->next;
//         count++;
//     }

//     if (count < len) {
//         printf("Error: Invalid number of elements to delete (len).\n");
//         return;
//     }

//     if (prev != NULL) {
//         prev->next = temp;
//     } else {
//         *la = temp;
//     }

//     // 定位插入位置
//     struct Node* lbCurrent = *lb;
//     count = 1;
//     while (count < j && lbCurrent != NULL) {
//         lbCurrent = lbCurrent->next;
//         count++;
//     }

//     if (count < j) {
//         printf("Error: Invalid insertion position (j).\n");
//         return;
//     }

//     // 将删除的元素插入到表lb的第j个元素之后
//     if (lbCurrent != NULL) {
//         temp = lbCurrent->next;
//         lbCurrent->next = current;
//         while (current->next != NULL) {
//             current = current->next;
//         }
//         current->next = temp;
//     } else {
//         printf("Error: Invalid insertion position (j).\n");
//     }
// }

// // 打印链表元素
// void printList(struct Node* head) {
//     struct Node* current = head;
//     while (current != NULL) {
//         printf("%d ", current->data);
//         current = current->next;
//     }
//     printf("\n");
// }

// // 示例用法
// int main() {
//     // 创建两个单链表
//     struct Node* la = (struct Node*)malloc(sizeof(struct Node));
//     la->data = 1;
//     la->next = (struct Node*)malloc(sizeof(struct Node));
//     la->next->data = 2;
//     la->next->next = (struct Node*)malloc(sizeof(struct Node));
//     la->next->next->data = 3;
//     la->next->next->next = NULL;

//     struct Node* lb = (struct Node*)malloc(sizeof(struct Node));
//     lb->data = 9;
//     lb->next = (struct Node*)malloc(sizeof(struct Node));
//     lb->next->data = 10;
//     lb->next->next = NULL;

//     // 打印原始链表
//     printf("Original list la: ");
//     printList(la);
//     printf("Original list lb: ");
//     printList(lb);

//     // 删除从第1个元素开始共2个元素，插入到lb的第1个元素之后
//     deleteAndInsert(&la, &lb, 1, 2, 1);

//     // 打印修改后的链表
//     printf("Modified list la: ");
//     printList(la);
//     printf("Modified list lb: ");
//     printList(lb);

//     // 释放内存
//     free(la->next->next);
//     free(la->next);
//     free(la);
//     free(lb->next);
//     free(lb);

//     return 0;
//

// #include <iostream>
// int main()
// {
//     std::cout << "today is a good day!"<< std::endl;
// }

// #include <vector>
// #include <iostream>

// int main() {
//     // 创建一个包含3行2列的二维整数数组
//     std::vector<std::vector<int>> twoDArray(3, std::vector<int>(2));

//     // 向二维数组中添加一些值
//     twoDArray[0][0] = 1;
//     twoDArray[0][1] = 2;
//     twoDArray[1][0] = 3;
//     twoDArray[1][1] = 4;
//     twoDArray[2][0] = 5;
//     twoDArray[2][1] = 6;

//     // 访问和输出二维数组中的值
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 2; j++) {
//             std::cout << twoDArray[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }

//   // 使用范围-based for 循环遍历二维数组并输出其内容
//     for (const auto& row : twoDArray) {
//         for (const auto& element : row) {
//             std::cout << element << " ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }

// struct Node* reverseLinkedList(struct Node* head) {
//     struct Node* prev = NULL;
//     struct Node* current = head;
//     struct Node* nextNode;

//     while (current != NULL) {
//         nextNode = current->next;
//         current->next = prev;
//         prev = current;
//         current = nextNode;
//     }

//     return prev;  // 返回逆置后的头节点
// }

// #include<iostream>
// #include<vector>
// using namespace std;
// int main()
// {
//     int n;
//     cin >> n;
//     vector<vector<int>> v;

//     for(int i=0;i<n;i++){
//         vector<int> row(i+1,1);

//         for(int j=1;j<i;j++){
//             row[j]=v[i-1][j-1]+v[i-1][j];
//         }

//         v.push_back(row);
//     }

//     for(int i=0;i<n;i++){
//         for(int j=0;j<=i;j++){
//             cout << v[i][j]<<" ";
//         }
//         cout << endl;
//     }

// //     for (auto row_ : v) {
// //         for (auto element : row_) {
// //             cout << element << " ";
// //         }
// //         cout << endl;
// //     }

// }

// #include <iostream>
// #include <queue>
// using namespace std;
// typedef struct Node
// {
//     char data;
//     struct Node* Lchild;
//     struct Node* Rchild;
// }*pnode,node;

// queue<pnode> myQueue;

// pnode init()
// {
//     pnode bt;
//     char ch = getchar();
//     if(ch=='#')
//         return NULL;
//     bt = (pnode)malloc(sizeof(node));
//     bt->data = ch;
//     bt->Lchild = init();
//     bt->Rchild = init();
//     return bt;
// }

// void print1(pnode root)
// {
//     myQueue.push(root);
//     while(!myQueue.empty()){
//         pnode p = myQueue.front();
//         myQueue.pop();
//         printf("%c",p->data);
//         if(p->Lchild)
//             myQueue.push(p->Lchild);
//         if(p->Rchild)
//             myQueue.push(p->Rchild);

//     }
// }

// int main()
// {
//     pnode root;
//     root = init();
//     print1(root);
// }

// #include <iostream>
// #include <queue>
// using namespace std;
// typedef struct Node
// {
//     char data;
//     struct Node* Lchild;
//     struct Node* Rchild;
// }*pnode,node;

// queue<pnode> myQueue;

// pnode init()
// {
//     pnode bt;
//     char ch = getchar();
//     if(ch=='#')
//         return NULL;
//     bt = (pnode)malloc(sizeof(node));
//     bt->data = ch;
//     bt->Lchild = init();
//     bt->Rchild = init();
//     return bt;
// }

// void print1(pnode root)
// {
//     myQueue.push(root);
//     while(!myQueue.empty()){
//         pnode p = myQueue.front();
//         myQueue.pop();
//         printf("%c",p->data);
//         if(p->Lchild)
//             myQueue.push(p->Lchild);
//         if(p->Rchild)
//             myQueue.push(p->Rchild);

//     }
// }

// int main()
// {
//     pnode root;
//     root = init();
//     print1(root);
// }

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <climits>

// #define min(x, y) (x < y ? x : y)

// using namespace std;

// struct edge {  // 边的结构体
//     int s;
//     int e;
//     int v;
//     edge(int ss, int ee, int vv) {
//         s = ss;
//         e = ee;
//         v = vv;
//     }
// };

// vector<edge> vc;  // 存放所有边

// int pre[10010];  // 记录前节点

// bool cmp(const edge& a, const edge& b) {
//     return a.v < b.v;
// }

// int Find(int a) {  // 找根节点
//     int t = a;
//     while (pre[t] != t) {
//         t = pre[t];
//     }

//     while (pre[a] != t) {  // 路径压缩
//         int tt = a;
//         a = pre[a];
//         pre[tt] = t;
//     }
//     return t;
// }

// int merg(int a, int b, int val) {  // 引入新边
//     int ta = Find(a);
//     int tb = Find(b);
//     if (ta != tb) {
//         pre[ta] = tb;
//         return 1;
//     } else {
//         if (val <=
//             0) {  //
//             这就是最大的坑，必须当这条边为负，且加入后构成环时返回2（意味着边数不加1）
//         }
//     }

//     int kruskal(vector<edge> & vc,
//                 int n) {  // 生成最小生成树，返回值为最小生成树值
//         sort(vc.begin(), vc.end(), cmp);
//         int te = 0;    // 边数
//         int tsum = 0;  // 权值和
//         for (int i = 0; i < vc.size(); i++) {
//             int tt;
//             if (tt = merg(vc[i].s, vc[i].e, vc[i].v)) {
//                 if (tt != 2) {  /// 最大的坑，不为2时边数才++
//                     te++;
//                 }
//                 tsum += vc[i].v;
//             }
//         }
//         if (te == n - 1) {  // 构成生成树了
//             return tsum;
//         }
//         return INT_MAX;  // 不连通
//     }

//     int main() {
//         int n;
//         int m;
//         cin >> n >> m;
//         for (int i = 0; i < m; i++) {
//             int a, b, c;
//             cin >> a >> b >> c;
//             vc.push_back(edge(a, b, c));
//         }
//         for (int i = 1; i <= n; i++) {
//             pre[i] = i;
//         }
//         int t1 = kruskal(vc, n);  // 求n个节点的最小生成树

//         for (int i = 1; i <= n; i++) {
//             int t;
//             cin >> t;
//             if (t != -1) {
//                 vc.push_back(
//                     edge(0, i, t));  // vc中加入可以修建码头的点到0点的边
//             }
//         }
//         for (int i = 0; i <= n; i++) {
//             pre[i] = i;
//         }
//         int t2 = kruskal(vc, n + 1);  // 求n+1个节点的最小生成树

//         cout << min(t1, t2);
//         return 0;
//     }
// }

// #include <vector>
// #include <iostream>

// int main() {
//     // 创建一个包含3行2列的二维整数数组
//     std::vector<std::vector<int>> twoDArray(3, std::vector<int>(2));

//     // 向二维数组中添加一些值
//     twoDArray[0][0] = 1;
//     twoDArray[0][1] = 2;
//     twoDArray[1][0] = 3;
//     twoDArray[1][1] = 4;
//     twoDArray[2][0] = 5;
//     twoDArray[2][1] = 6;

//     // 访问和输出二维数组中的值
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 2; j++) {
//             std::cout << twoDArray[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }

//   // 使用范围-based for 循环遍历二维数组并输出其内容
//     for (const auto& row : twoDArray) {
//         for (const auto& element : row) {
//             std::cout << element << " ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }

// #include <iostream>
// using namespace std;

// // int main()
// // {
// //     int a=2;
// //     int *b =&a;
// //     cout << b << endl << *b<< endl;
// // }

// template <typename T>
// void printX(T& t) {
//     std::cout << "left value" << std::endl;
// }

// template <typename T>
// void printX(T&& t) {
//     std::cout << "rifht value " << std::endl;
// }

// template <typename T>
// void test(T&& v) {
//     printX(v);
//     printX(move(v));
//     printX(forward<T>(v));
// }

// int main() {
//     test(100);
//     cout << "--------" << endl;

//     int num = 10;
//     test(num);
//     cout << "--------" << endl;

//     test(forward<int>(num));
//     cout << "--------" << endl;

//     test(forward<int&>(num));
//     cout << "--------" << endl;

//     test(forward<int&&>(num));

//     return 0;
// }

// #include <iostream>
// #include <queue>
// using namespace std;

// int a[100][100];  // 各位置信息（是否有路径）
// int v[100][100];  // 标记某个位置是否被访问过（1有0无）
// struct point {
//     int x;
//     int y;
//     int step;
// };                          // 队列里每个元素
// queue<point> r;             // 申请队列
// int dx[4] = {1, 0, -1, 0};  // 向四个方向延伸，顺序为：右 下 左 上
// int dy[4] = {0, -1, 0, 1};
// int flag = 0;  // 是否到达终点

// int main() {
//     // 数据输入
//     int n, m, startx, starty, endx, endy;
//     scanf("%d %d", &n, &m);
//     for (int i = 1; i <= n; i++) {
//         for (int j = 1; j <= m; j++) {
//             scanf("%d", &a[i][j]);//1为路径，2为墙
//         }
//     }
//     scanf("%d %d %d %d", &startx, &starty, &endx,
//           &endy);  // 输入起点坐标和终点坐标

//     // BFS
//     point start;
//     start.x = startx;
//     start.y = starty;
//     start.step = 0;
//     r.push(start);          // 将起点坐标入队
//     v[startx][starty] = 1;  // 将该点标记为已访问

//     while (!r.empty()) {
//         int x = r.front().x;  // 取队首元素的x坐标
//         int y = r.front().y;  // 取队首元素的y坐标
//         int step = r.front().step;
//         printf("%d %d %d\n",x,y,step);

//         if (x == endx && y == endy) {  // 到达终点了
//             flag = 1;
//             printf("%d\n", step);
//             break;
//         }

//         for (int k = 0; k <= 3; k++) {  // 向四个方向拓展
//             int newx, newy;
//             newx = x + dx[k];
//             newy = y + dy[k];
//             if (a[newx][newy] == 1 &&
//                 v[newx][newy] == 0)  // 该拓展点可以被访问且未被访问过
//             {
//                 point newpoint;
//                 newpoint.x = newx;
//                 newpoint.y = newy;
//                 newpoint.step = step+1;
//                 r.push(newpoint);  // 新拓展点入队
//                 v[newx][newy] = 1;
//             }
//         }
//         r.pop();  // 拓展完后将队首元素出队
//     }

//     if (flag == 1) {
//         printf("找到路径");
//     } else {
//         printf("未找到路径");
//     }

//     return 0;
// }

// // #include <iostream>
// // #include <vector>

// // using namespace std;

// // class Solution {
// // public:
// //     int orangesRotting(vector<vector<int>>& grid) {

// //     }
// // };

// #include <iostream>
// #include <string>

// int main() {
//     std::string str = "Hello, World!";
//     int length = str.length();
//     // 或者使用 int length = str.size();

//     std::cout << "字符串长度为: " << length << std::endl;

//     return 0;
// }

// #include <iostream>
// #include <string>

// int main() {
//     std::string str1 = "Hello, World!";
//     std::string str2 = "World";

//     int pos = str1.find(str2);

//     if (pos != std::string::npos) {
//         std::cout << "找到了子字符串 \"" << str2 << "\"，位置在 " << pos <<
//         std::endl;
//     } else {
//         std::cout << "未找到子字符串 \"" << str2 << "\"" << std::endl;
//     }

//     return 0;
// }

// #include <iostream>
// #include <string>

// int main() {
//     std::string str1 = "Hello, ";
//     std::string str2 = "World!";

//     std::string result = str1 + str2;

//     std::cout << "拼接结果: " << result << std::endl;

//     return 0;
// }

// #include <iostream>
// #include <string>

// int main() {
//     std::string str1 = "Hell";
//     std::string str2 = "HelL";

//     if (str1 <= str2) {
//         std::cout << "两个字符串相等" << std::endl;
//     } else {
//         std::cout << "两个字符串不相等" << std::endl;
//     }

//     return 0;
// }

// #include <iostream>
// #include <string>

// int main() {
//     std::string str1 = "Hello";
//     std::string str2;

//     if (str1.empty()) {
//         std::cout << "str1是空字符串" << std::endl;
//     } else {
//         std::cout << "str1不是空字符串" << std::endl;
//     }

//     if (str2.empty()) {
//         std::cout << "str2是空字符串" << std::endl;
//     } else {
//         std::cout << "str2不是空字符串" << std::endl;
//     }

//     return 0;
// }

// #include <iostream>
// #include <string>
// using namespace std;
// int main() {
//     std::string str = "Hello, World!";
//     int a = 'a'-'A';
//     cout << a << endl;
//     // 将字符串转换为小写
//     for(int i=0;i<str.length();i++){
//         if(str[i]>='A'&&str[i]<='Z'){
//             char ch = str[i]+a;
//             cout << ch;
//         }else if(str[i]>='a'&&str[i]<='z'){
//             char ch = str[i]-a;
//             cout << ch;
//         }else{
//             cout << str[i];
//         }
//     }

//     return 0;
// }

// #include <iostream>
// #include <string>
// using namespace std;

// int main() {
//     string user_name;
//     cout << "Please enter your first name: ";
//     cin >> user_name;
//     cout << '\n' << "Hello, " << user_name << " ... and goodbye!\n";
//     return 0;
// }

// #include <iostream>
// int max(int x, int y);
// int main() {
//     int a, b, c;
//     std::cin >> a >> b;
//     c = max(a, b);
//     std::cout << "max= " << c <<'\n';
// }
// int max(int x, int y)
// {
//     int z;
//     if (x > y)
//         z = x;
//     else
//         z = y;
//     return (z);
// }

// I/O stream 单行注释(single line comment)
// #include <iostream>
// using namespace std;
// int main() {
//     int i;
//     float f;
//     char s[80];
//     cout << "Enter an integer,float,and string:";
//     cin >> i >> f >> s;
//     cout << "Here's your data:" << i << ' ' << f << endl << s << '\n';
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int main() {
//     int a, b, c;
//     cin >> a >> b;
//     if (b == 0)
//         return -1;
//     c = a / b;
//     cout << "c= " << c << '\n';
//     return 0;
// }

// #include <iostream>
// using namespace std;

// int model = 90;
// int v[] = {1, 2, 3, 4};
// const int x = 0;
// void f() {
//     model = 200;
//     v[2]++;
// }
// int main()
// {
//     f();
//     return 0;
// }

// #include <iostream>
// using namespace std;

// void sqr_it(int* i);
// int main() {
//     int x;
//     x = 10;
//     sqr_it(&x);
//     cout << "The square of x is " << x << '\n';
//     return 0;
// }
// void sqr_it(int* i) {
//     *i = (*i) * (*i);
// }

// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     char* name = new char[30];
//     cin.getline(name,30);
//     cout << name << endl;
// }

// #include <iostream>
// using namespace std;

// void f(int a[], int n, int& max, int& min) {
//     max = min = a[0];
//     for (int i = 1; i < n; i++) {
//         if (max < a[i])
//             max = a[i];
//         if (min > a[i])
//             min = a[i];
//     }
// }
// int main() {
//     int a[10] = {2, 5, 3, 9, 0, 8, 1, 7, 6, 4};
//     int max, min;
//     f(a, 10, max, min);
//     cout << "Max: " << max << endl;
//     cout << "Min: " << min << endl;
// }

// class FindMax {
//    public:
//     int max(int a, int b) { return a > b ? a : b; }

//     long max(long a, long b) { return a > b ? a : b; }

//     double max(double a, double b) { return a > b ? a : b; }
// };

// int main() {
//     FindMax findmax;
//     cout << findmax.max(2,3) << endl;
//     cout << findmax.max(1000000000,2000000000) << endl;
//     cout << findmax.max(2.2,3.3) << endl;
// }

// // 21：55
// #include <iostream>
// #include <vector>
// #include <bits/stdc++.h>
// using namespace std;
// int dx[4] = {1, 0, -1, 0};
// int dy[4] = {0, 1, 0, -1};
// int dxx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
// int dyy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
// int v[50][50] = {0};
// int num = 0;

// int BFS(vector<vector<int>>& grid, queue<pair<int, int>>& q) {
//     queue<pair<int, int>> p = q;
//     int flag = 0;  // 默认没找到
//     while (!q.empty() && !flag) {
//         pair<int, int> newpoint, point = p.front();
//         p.pop();
//         for (int i = 0; i < 8; i++) {
//             newpoint.first = point.first + dxx[i];
//             newpoint.second = point.second + dyy[i];
//             if (newpoint.first < 0 || newpoint.second < 0 ||
//                 newpoint.first >= grid.size() ||
//                 newpoint.second >= grid[0].size())
//                 continue;
//             if (newpoint.first == 0 || newpoint.second == 0 ||
//                 newpoint.first == grid.size() - 1 ||
//                 newpoint.second == grid[0].size() - 1)
//                 flag = 1;
//             if (grid[newpoint.first][newpoint.second] == 0) {
//                 p.push(newpoint);
//             }
//         }
//     }
//     if (flag == 0)
//         return flag;

//     while (!q.empty()) {
//         pair<int, int> newpoint, point = q.front();
//         q.pop();
//         for (int i = 0; i < 4; i++) {
//             newpoint.first = point.first + dx[i];
//             newpoint.second = point.second + dy[i];
//             if (newpoint.first < 0 || newpoint.second < 0 ||
//                 newpoint.first >= grid.size() ||
//                 newpoint.second >= grid[0].size())
//                 continue;
//             if (grid[newpoint.first][newpoint.second] == 1 &&
//                 v[newpoint.first][newpoint.second] == 0) {
//                 q.push(newpoint);
//                 v[newpoint.first][newpoint.second] = 1;
//             }
//         }
//     }
//     return 1;
// }

// int main() {
//     int t;
//     cin >> t;
//     while (t--) {
//         int m, n;
//         cin >> m >> n;
//         vector<vector<int>> grid(m, vector<int>(n));
//         for (int i = 0; i < m; i++) {
//             string row;
//             cin >> row;
//             for (int j = 0; j < n; j++) {
//                 grid[i][j] = row[j] - '0';
//             }
//         }

//         num = 0;  // 岛屿数量
//         for (int i = 0; i < 50; i++) {
//             for (int j = 0; j < 50; j++) {
//                 v[i][j] = 0;
//             }
//         }
//         queue<pair<int, int>> q;

//         for (int i = 0; i < m; i++) {
//             for (int j = 0; j < n; j++) {
//                 if (grid[i][j] == 1 && v[i][j] == 0) {
//                     pair<int, int> point = make_pair(i, j);
//                     q.push(point);
//                     v[i][j] = 1;
//                     if (BFS(grid, q))
//                         num++;
//                 }
//             }
//         }
//         cout << "-----------" << num << "-----------" << endl;
//     }

//     return 0;
// }

// #include <bits/stdc++.h>
// using namespace std;

// int dx[4] = {1, 0, -1, 0};
// int dy[4] = {0, 1, 0, -1};
// int dxx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
// int dyy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// void BFS(vector<vector<int>>& grid,
//          queue<pair<int, int>>& q,
//          vector<vector<int>>& v,
//          int flag) {
//     while (!q.empty()) {
//         pair<int, int> newpoint, point = q.front();
//         q.pop();
//         if (flag == 2) {  // 说明是标志海能够到达的区域模块
//             for (int i = 0; i < 8; i++) {
//                 int x = point.first + dxx[i];
//                 int y = point.second + dyy[i];
//                 if (x < 0 || y < 0 || x >= grid.size() || y >=
//                 grid[0].size())
//                     continue;
//                 if (grid[x][y] == 0) {
//                     newpoint.first = x;
//                     newpoint.second = y;
//                     q.push(newpoint);
//                     grid[x][y] = 2;
//                 }
//             }
//         }
//         if (flag == 1) {  // 说明是统计岛屿个数模块
//             for (int i = 0; i < 4; i++) {
//                 int x = point.first + dx[i];
//                 int y = point.second + dy[i];
//                 if (x < 0 || y < 0 || x >= grid.size() || y >=
//                 grid[0].size())
//                     continue;
//                 if (grid[x][y] == 1 && v[x][y] == 0) {
//                     newpoint.first = x;
//                     newpoint.second = y;
//                     q.push(newpoint);
//                     v[x][y] = 1;
//                 }
//             }
//         }
//     }
// }

// int main() {
//     int t;
//     cin >> t;
//     while (t--) {
//         int m, n, num = 0;
//         cin >> m >> n;
//         vector<vector<int>> grid(m + 2, vector<int>(n + 2)),
//             v(m + 2, vector<int>(n + 2));
//         string str;
//         for (int i = 0; i < m; i++) {
//             cin >> str;
//             for (int j = 0; j < n; j++) {
//                 grid[i + 1][j + 1] = str[j] - '0';
//             }
//         }

//         // for(int i=0;i<m+2;i++){
//         //     for(int j=0;j<n+2;j++){
//         //         cout << grid[i][j];
//         //     }
//         //     cout << endl;
//         // }

//         //
//         从00开始,通过八个方向遍历地图,把是0的地方全部设置为2,表示外部海水能到达的区域

//         queue<pair<int, int>> q;
//         pair<int, int> point(0, 0);
//         q.push(point);
//         BFS(grid, q, v, 2);

//         // 遍历一次地图,把所有0变为1.这样内部的子岛屿就和外部的岛屿连到一起了
//         for (int i = 0; i < m + 2; i++) {
//             for (int j = 0; j < n + 2; j++) {
//                 if (grid[i][j] == 0)
//                     grid[i][j] = 1;
//             }
//         }

//         // 正常BFS,找岛屿的个数即可
//         for (int i = 1; i <= n; i++) {
//             for (int j = 1; j <= m; j++) {
//                 if (v[i][j] == 0 && grid[i][j] == 1) {
//                     pair<int, int> point = make_pair(i, j);
//                     q.push(point);
//                     v[i][j] = 1;
//                     num++;
//                     BFS(grid, q, v, 1);
//                 }
//             }
//         }

//         // 打印岛屿个数
//         // cout << "-----" << num << "------" << endl;
//         cout << num << endl;
//     }
// }

// #include <bits/stdc++.h>
// using namespace std;

// class counter {
//    private:
//     int value;

//    public:
//     counter(int number) : value(number) {}  // 构造函数用于初始化计数器的值

//     // 方法用于增加计数器的值
//     void increment() { value++; }

//     // 方法用于减少计数器的值
//     void decrement() { value--; }

//     // 方法用于获取计数器的当前值
//     int getvalue() { return value; }

//     // 方法用于打印计数器的当前值
//     void print() { std::cout << "计数器的值为: " << value << std::endl; }
// };

// int main() {
//     // 创建一个初始值为5的计数器实例
//     counter myCounter(5);

//     // 增加计数器的值
//     myCounter.increment();

//     // 打印当前计数器的值
//     myCounter.print();  // 输出将会是: 计数器的值为: 6

//     // 减少计数器的值
//     myCounter.decrement();

//     // 打印当前计数器的值
//     myCounter.print();  // 输出将会是: 计数器的值为: 5

//     return 0;
// }

// class Score{
//     float computer;
//     float english;
//     float mathematics;
//     public:
//     Score(float x1;float y1;float z1);
//     Score();
//     void print();
//     void modify(float x2,float y2,float z2);
// };

// #include <bits/stdc++.h>
// using namespace std;

// // Student类的定义部分存放在接口文件student.h 中
// class Student {
//    private:
//     int number;
//     char* name;
//     float score;

//    public:
//     Student(int number1, char* name1, float score1);  // 构造函数的声明
//     ~Student();                                       // 析构函数的声明
//     void modify(float score1) { score = score1; }
//     void print();
// };
// // Student类中成员函数的定义部分存放在实现文件student.cpp 中

// using namespace std;
// // 构造函数的定义
// Student::Student(int number1, char* name1, float score1) {
//     number = number1;
//     name = new char[strlen(name1) + 1];  // 申请动态内存单元
//     strcpy(name, name1);
//     score = score1;
// }
// // 析构函数的定义
// Student::~Student() {
//     delete[] name;  // 释放动态内存单元
// }
// void Student::print() {
//     cout << "number: " << number << " name: " << name << " score: " << score
//          << '\n';
// }

// // main( )函数主模块文件main.cpp
// #include <iostream>
// #include <string>
// using namespace std;
// int main() {
//     int numberi;
//     char namei[15];
//     float scorei;

//     cout << "Enter number:\n";
//     cin >> numberi;
//     cout << "Enter name:\n";
//     cin >> namei;
//     cout << "Enter score:\n";
//     cin >> scorei;
//     Student stu1(numberi, namei, scorei);  // 创建对象stu1时执行了初始化

//     cout << "Enter number:\n";
//     cin >> numberi;
//     cout << "Enter name:\n";
//     cin >> namei;
//     Student stu 2(numberi, namei, scorei);  // 创建对象stu2时执行了初始化
//     stu2.modify(87);  // 对象stu2调用成员函数modify( )

//     stu1.print();  // 对象stu1调用成员函数print( )
//     stu2.print();  // 对象stu2调用成员函数print( )
//     return 0;
// }

// #include <iostream>

// class Rectangle {
// private:
//     double length;
//     double width;

// public:
//     // 构造函数
//     Rectangle(double l, double w) {
//         length = l;
//         width = w;
//     }

//     // 计算矩形面积的成员函数
//     double calculateArea() {
//         return length * width;
//     }
// };

// int main() {
//     // 创建矩形对象
//     Rectangle rect(5.0, 3.0);

//     // 计算并显示矩形面积
//     std::cout << "Rectangle Area: " << rect.calculateArea() << std::endl;

//     return 0;
// }

// #include<iostream>
// using namespace std;

// class Date {
//     int d, m, y;

// public:
//     Date(int day, int month, int year) : d(day), m(month), y(year) {}

//     int day() const { return d; }
//     int month() const { return m; }
//     inline int year() {
//         return y++;
//     }
// };

// int main() {
//     Date date(26, 3, 2024);
//     cout << "Day: " << date.day() << endl;
//     cout << "Month: " << date.month() << endl;
//     cout << "Year: " << date.year() << endl;

//     return 0;
// }

// #include <iostream>
// #include <cstring>
// #include <string>
// using namespace std;

// class Score {
// private:
//     float computer;
//     float english;
//     float mathematics;

// public:
//     Score(float x1, float y1, float z1) : computer(x1), english(y1),
//     mathematics(z1) {} Score() : computer(0), english(0), mathematics(0) {}

//     void print() {
//         cout << "Computer: " << computer << ", English: " << english << ",
//         Mathematics: " << mathematics << endl;
//     }

//     void modify(float x2, float y2, float z2) {
//         computer = x2;
//         english = y2;
//         mathematics = z2;
//     }
// };

// class Student {
// private:
//     int number;
//     char* name;
//     Score score; // 将Score类的对象作为成员变量添加到Student类中

// public:
//     // 构造函数的声明
//     Student(int number1, const char* name1, float comp_score, float
//     eng_score, float math_score);
//     // 析构函数的声明
//     ~Student();
//     void modify_scores(float comp_score, float eng_score, float math_score) {
//         score.modify(comp_score, eng_score, math_score);
//     }
//     void print();
// };

// // 构造函数的定义
// Student::Student(int number1, const char* name1, float comp_score, float
// eng_score, float math_score) : number(number1), score(comp_score, eng_score,
// math_score) {
//     name = new char[strlen(name1) + 1]; // 申请动态内存单元
//     strcpy(name, name1);
// }

// // 析构函数的定义
// Student::~Student() {
//     delete[] name; // 释放动态内存单元
// }

// void Student::print() {
//     cout << "Number: " << number << ", Name: " << name << ", Scores: ";
//     score.print();
// }

// int main() {
//     int number;
//     char name[15];
//     float comp_score, eng_score, math_score;

//     cout << "Enter number: ";
//     cin >> number;
//     cout << "Enter name: ";
//     cin >> name;
//     cout << "Enter Computer score: ";
//     cin >> comp_score;
//     cout << "Enter English score: ";
//     cin >> eng_score;
//     cout << "Enter Mathematics score: ";
//     cin >> math_score;

//     Student stu1(number, name, comp_score, eng_score, math_score);

//     cout << "Enter number: ";
//     cin >> number;
//     cout << "Enter name: ";
//     cin >> name;
//     cout << "Enter Computer score: ";
//     cin >> comp_score;
//     cout << "Enter English score: ";
//     cin >> eng_score;
//     cout << "Enter Mathematics score: ";
//     cin >> math_score;

//     Student stu2(number, name, comp_score, eng_score, math_score);
//     stu2.modify_scores(85, 90, 95); // 修改stu2的成绩

//     cout << "\nStudent 1:\n";
//     stu1.print();
//     cout << "\nStudent 2:\n";
//     stu2.print();

//     return 0;
// }

// #include<iostream>
// #include<vector>
// #include<cmath>
// #include<algorithm>
// #include<string>

// using namespace std;

// struct peo
// {
//     int num;
//     string str;
//     long long int sum;
// }p[100];

// bool cmp(const peo&a,const peo&b){
//     // return a.num>b.num;//降序
//     return a.num<b.num;//升序
// }

// int main()
// {
//     int n;
//     cin >> n;
//     for(int i=0;i<n;i++){
//         cin >> p[i].num >> p[i].str >> p[i].sum;
//     }

//     sort(p,p+n,cmp);

//     for(int i=0;i<n;i++){
//         cout << p[i].num <<" " <<  p[i].str << " "<< p[i].sum<< endl;
//     }

//     return 0;
// }

// #include <iostream>
// #include <string>

// class Student {
// public:
//   std::string name;
//   int age;

//   Student(const std::string& n, int a) : name(n), age(a) {}
// };

// int main() {
//   Student students[5] = {
//     Student("Alice", 20),
//     Student("Bob", 21),
//     Student("Charlie", 19),
//     Student("David", 22),
//     Student("Eve", 20)
//   };

//   for (int i = 0; i < 5; ++i) {
//     std::cout << "Student " << i+1 << ": " << students[i].name << ", " <<
//     students[i].age << std::endl;
//   }

//   Student* studentPtrs[5];
//   for (int i = 0; i < 5; ++i) {
//     studentPtrs[i] = &students[i];
//   }

//   for (int i = 0; i < 5; ++i) {
//     std::cout << "Student " << i+1 << ": " << studentPtrs[i]->name << ", " <<
//     studentPtrs[i]->age << std::endl;
//   }

//   return 0;
// }

// #include <iostream>
// using namespace std;

// class samp {
//     int i;

//    public:
//     samp(int x) { i = x; }
//     void set_i(int n) { i = n; }
//     int get_i() { return i; }
// };
// void sqr_it(samp &o){
//     o.set_i(o.get_i() * o.get_i());
//     cout << o.get_i() << endl;
//     cout << endl;
// }

// int main() {
//     samp a(10);
//     sqr_it(a);
//     cout << a.get_i();
//     return 0;

// }

// #include <iostream>

// class Circle {
// private:
//     double radius;
//     static int count; // 静态数据成员

// public:
//     Circle(double r) : radius(r) {
//         count++; // 在构造函数中增加对象计数
//     }

//     ~Circle() {
//         count--; // 在析构函数中减少对象计数
//     }

//     static int getCount() { // 静态成员函数
//         return count;
//     }
// };

// int Circle::count = 0; // 初始化静态数据成员

// int main() {
//     Circle c1(2.0);
//     Circle c2(3.0);
//     Circle c3(4.0);

//     std::cout << "Number of objects: " << Circle::getCount() << std::endl;

//     return 0;
// }

// #include <iostream>
// #include <cmath>

// class Point {
// private:
//     double x;
//     double y;

// public:
//     Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

//     double distance(const Point& other) const;

//     friend double calculateDistance(const Point& p1, const Point& p2);
// };

// double Point::distance(const Point& other) const {
//     double dx = x - other.x;
//     double dy = y - other.y;
//     return std::sqrt(dx * dx + dy * dy);
// }

// double calculateDistance(const Point& p1, const Point& p2) {
//     return p1.distance(p2);
// }

// int main() {
//     Point p1(1.0, 2.0);
//     Point p2(3.0, 4.0);

//     double dist = calculateDistance(p1, p2);
//     std::cout << "Distance between p1 and p2: " << dist << std::endl;

//     return 0;
// }

// #include <bits/stdc++.h>
// #include <cmath>
// #include <algorithm>
// using namespace std;
// class Point {
//    public:
//     Point(double xi, double yi) {
//         X = xi;
//         Y = yi;
//     }
//     double GetX() { return X; }
//     double GetY() { return Y; }
//     double Distance(Point& b);

//    private:
//     double X, Y;
// };
// double Point::Distance(Point& b) {
//     double dx = X - b.X;
//     double dy = Y - b.Y;
//     return sqrt(dx * dx + dy * dy);
// }
// int main() {
//     Point p1(3.0, 5.0), p2(4.0, 6.0);
//     double d = p1.Distance(p2);
//     cout << "The distance is " << d << endl;
//     return 0;
// }

// #include<stdio.h>
// #include<stdlib.h>
// #include<signal.h>
// #include<sys/types.h>
// #include<sys/wait.h>
// #include<string.h>

// int main(int argc, char *argv[])
// {
//     pid_t pid;
//     char cmd;
//     char *arg_psa[]={"ps","-a",NULL};
//     char *arg_psx[]={"ps","-x",NULL};
//     while(1)
//     {
//         printf("------------------------------\n");
//         printf("输入a执行'ps-a'命令\n");
//         printf("输入x执行'ps-x'命令\n");
//         printf("输入q退出\n");
//         cmd=getchar();//接收输入命令字符
//         getchar();

//         if((pid=fork())<0)
//         {
//             perror("fork error:");
//             return -1;
//         }
//         if(pid==0)
//         {
//             switch(cmd)
//             {
//                 case 'a':
//                 execve("/bin/ps",arg_psa,NULL);
//                 break;
//                 case 'x':
//                 execve("/bin/ps",arg_psx,NULL);
//                 break;
//                 case 'q':
//                 break;
//                 defaul有意设置子进程结束
//          } else if(pid>0){
//              if(cmd=='q')
//              break;
//          }
//     }//进程退出循环
//     while(waitpid(-1,NULL,WNOHANG)>0);
//     return 0;
// }t:
//                 perror("wrong cmd:\n");
//                 break;
//             }//子进程结束
//             exit(0);//

// #include <iostream>
// #include <thread>
// #include <queue>
// #include <mutex>
// #include <condition_variable>

// using namespace std;

// const int BUFFER_SIZE = 5;
// queue<int> buffer;
// mutex mtx;
// condition_variable not_full, not_empty;

// void producer() {
//     for (int i = 0; i < 10; ++i) {
//         unique_lock<mutex> lock(mtx);
//         not_full.wait(lock, []{ return buffer.size() < BUFFER_SIZE; });
//         buffer.push(i);
//         cout << "Produced item " << i << endl;
//         lock.unlock();
//         not_empty.notify_one();
//         this_thread::sleep_for(chrono::seconds(1));
//     }
// }

// void consumer() {
//     for (int i = 0; i < 10; ++i) {
//         unique_lock<mutex> lock(mtx);
//         not_empty.wait(lock, []{ return !buffer.empty(); });
//         int item = buffer.front();
//         buffer.pop();
//         cout << "Consumed item " << item << endl;
//         lock.unlock();
//         not_full.notify_one();
//         this_thread::sleep_for(chrono::seconds(2));
//     }
// }

// int main() {
//     thread prod_thread(producer);
//     thread cons_thread(consumer);
//     prod_thread.join();
//     cons_thread.join();
//     return 0;
// }

// #include <iostream>
// #include <thread>
// #include <vector>
// #include <mutex>
// #include <condition_variable>

// using namespace std;

// mutex mtx;
// condition_variable read_cv, write_cv;
// int readers = 0;
// bool writing = false;

// void reader(int id) {
//     while (true) {
//         unique_lock<mutex> lock(mtx);
//         while (writing) {
//             read_cv.wait(lock);
//         }
//         ++readers;
//         lock.unlock();
//         // Reading...
//         cout << "Reader " << id << " is reading." << endl;
//         lock.lock();
//         --readers;
//         if (readers == 0) {
//             write_cv.notify_one();
//         }
//         lock.unlock();
//         this_thread::sleep_for(chrono::milliseconds(1000));
//     }
// }

// void writer(int id) {
//     while (true) {
//         unique_lock<mutex> lock(mtx);
//         while (writing || readers > 0) {
//             write_cv.wait(lock);
//         }
//         writing = true;
//         lock.unlock();
//         // Writing...
//         cout << "Writer " << id << " is writing." << endl;
//         lock.lock();
//         writing = false;
//         read_cv.notify_all();
//         write_cv.notify_one();
//         lock.unlock();
//         this_thread::sleep_for(chrono::milliseconds(2000));
//     }
// }

// int main() {
//     vector<thread> reader_threads;
//     vector<thread> writer_threads;

//     for (int i = 0; i < 3; ++i) {
//         reader_threads.emplace_back(reader, i);
//         writer_threads.emplace_back(writer, i);
//     }

//     for (auto& thread : reader_threads) {
//         thread.join();
//     }

//     for (auto& thread : writer_threads) {
//         thread.join();
//     }

//     return 0;
// }

// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <condition_variable>

// using namespace std;

// const int NUM_PHILOSOPHERS = 5;
// mutex mtx;
// condition_variable cv;
// bool chopsticks[NUM_PHILOSOPHERS];

// void philosopher(int id) {
//     while (true) {
//         // Thinking...
//         cout << "Philosopher " << id << " is thinking." << endl;
//         this_thread::sleep_for(chrono::milliseconds(1000));

//         // Pick up left chopstick
//         unique_lock<mutex> lock(mtx);
//         while (chopsticks[id] || chopsticks[(id + 1) % NUM_PHILOSOPHERS]) {
//             cv.wait(lock);
//         }
//         chopsticks[id] = true;
//         chopsticks[(id + 1) % NUM_PHILOSOPHERS] = true;
//         lock.unlock();

//         // Eating...
//         cout << "Philosopher " << id << " is eating." << endl;
//         this_thread::sleep_for(chrono::milliseconds(2000));

//         // Put down left chopstick
//         lock.lock();
//         chopsticks[id] = false;
//         chopsticks[(id + 1) % NUM_PHILOSOPHERS] =
// int main() {
//     thread philosophers[NUM_PHILOSOPHERS];
//     for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
//         philosophers[i] = thread(philosopher, i);
//     }
//     for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
//         philosophers[i].join();
//     }
//     return 0;
// }

// int main() {
//     thread philosophers[NUM_PHILOSOPHERS];
//     for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
//         philosophers[i] = thread(philosopher, i);
//     }
//     for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
//         philosophers[i].join();
//     }
//     return 0;
// }

// #include<iostream>

// using namespace std;

// class Point
// {
// public:
//     Point():x(0), y(0) {}
//     Point (int x,int y):x(x), y(y) {}

//     int getX() const { return x; }
//     int getY() const { return y; }

//     ~Point() {}

// private:
//     int x;
//     int y;
// };

// class Distance
// {
// public:
//     Distance(Point p1,Point p2):p1(p1), p2(p2){}

//     int getDist(){
//         return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) + (p1.getY()
//         - p2.getY()) * (p1.getY() - p2.getY());
//     }

// private:
//     Point p1;
//     Point p2;
// };

// int main()
// {
//     Point p1(0, 0);
//     Point p2(3, 4);
//     Distance d(p1, p2);

//     cout << "两点间的距离是" << d.getDist() << endl;

//     return 0;
// }

// #include <iostream>

// // 基类：图形类
// class Shape {
// public:
//     // 公有数据成员
//     double height, width;

//     // 无参构造函数
//     Shape() : height(0), width(0) {}

//     // 有参构造函数
//     Shape(double h, double w) : height(h), width(w) {}

//     // 设置信息函数
//     void setInfo(double h, double w) {
//         height = h;
//         width = w;
//     }

//     // 显示信息函数
//     void displayInfo() const {
//         std::cout << "Height: " << height << ", Width: " << width <<
//         std::endl;
//     }

//     // 析构函数
//     ~Shape() {}
// };

// // 派生类1：矩形类
// class Rectangle : public Shape {
// public:
//     // 构造函数
//     Rectangle(double h, double w) : Shape(h, w) {}

//     // 计算矩形面积函数
//     double area() const {
//         return height * width;
//     }
// };

// // 派生类2：等腰三角形类
// class IsoscelesTriangle : public Shape {
// public:
//     // 构造函数
//     IsoscelesTriangle(double h, double b) : Shape(h, b) {}

//     // 计算等腰三角形面积函数
//     double area() const {
//         return (height * width) / 2;
//     }
// };

// int main() {
//     // 创建矩形对象并计算面积
//     Rectangle rect(5.0, 6.0);
//     std::cout << "Rectangle area: " << rect.area() << std::endl;

//     // 创建等腰三角形对象并计算面积
//     IsoscelesTriangle itri(7.0, 8.0);
//     std::cout << "Isosceles Triangle area: " << itri.area() << std::endl;

//     return 0;
// }

// #include<iostream>

// using namespace std;

// class Employee
// {
// private:
//     char *name;
//     int individualEmpNo;
//     int grade;
//     float accumPay;
//     static int employeeNo;

// public:
//     Employee();
//     ~Employee();
//     void pay();
//     void prommote(int);
//     void displayStatus();
// };

// class Technician : public Employee
// {
// private:
//     float hourlyRate;
//     int workHours;

// public:
//     Technician();
//     ~Technician();
//     void pay();
//     void displayStatus();
// };

// class Manager : public Employee
// {
// private:
//     float bonus;

// public:
//     Manager();
//     ~Manager();
//     void pay();
//     void displayStatus();
// };

// class Salesman : public Employee
// {
// private:
//     float commission;
//     float sales;

// public:
//     Salesman();
//     ~Salesman();
//     void pay();
//     void displayStatus();
// };

// class Salesmanager : public Manager, public Salesman
// {
// private:
//     float bonus;

// public:
//     Salesmanager();
//     ~Salesmanager();
//     void pay();
//     void displayStatus();
// };

// #include <iostream>
// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <thread>

// class MessageQueue {
// private:
//     std::queue<std::string> buffer;  // 消息缓冲区
//     std::mutex mtx;                  // 互斥锁
//     std::condition_variable cv;      // 条件变量

// public:
//     void PushMessage(const std::string& message) {
//         std::unique_lock<std::mutex> lock(mtx);
//         buffer.push(message);
//         cv.notify_one();  // 通知等待的线程
//     }

//     std::string PopMessage() {
//         std::unique_lock<std::mutex> lock(mtx);
//         while (buffer.empty()) {
//             cv.wait(lock);  // 等待消息到达
//         }
//         std::string message = buffer.front();
//         buffer.pop();
//         return message;
//     }
// };

// int main() {
//     MessageQueue messageQueue;

//     // 生产者线程
//     std::thread producer([&]() {
//         for (int i = 0; i < 5; ++i) {
//             std::string message = "Message " + std::to_string(i + 1);
//             messageQueue.PushMessage(message);
//             // std::cout << "Sent message: " << message << std::endl;
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//         }
//     });

//     // 消费者线程
//     std::thread consumer([&]() {
//         for (int i = 0; i < 5; ++i) {
//             std::string message = messageQueue.PopMessage();
//             std::cout << "Received message: " << message << std::endl;
//         }
//     });

//     producer.join();
//     consumer.join();

//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>

// using namespace std;

// class Information {
//    private:
//     int age;
//     string sex;

//    public:
//     Information(int a, string b) : age(a), sex(b) {}
//     Information() {}
//     ~Information() {}

//     int getAge() const { return age; }

//     string getSex() const { return sex; }

//     void setAge(int a) { age = a; }

//     void setSex(string s) { sex = s; }

//     void printAge() const { cout << "Age: " << age << endl; }

//     void printSex() const { cout << "Sex: " << sex << endl; }
// };

// class Student {
//    private:
//     string stu_id;
//     string name;
//     int math;
//     int chinese;
//     int total;
//     Information info;

//    public:
//     Student(string id, string n, int m, int c, Information i)
//         : stu_id(id), name(n), math(m), chinese(c), info(i) {
//         total = math + chinese;
//     }

//     Student() { total = 0; }

//     ~Student() {}

//     string getStudentID() const { return stu_id; }

//     string getName() const { return name; }

//     int getMathScore() const { return math; }

//     int getChineseScore() const { return chinese; }

//     int getTotalScore() const { return total; }

//     Information getInfo() const { return info; }

//     void setStudentID(string id) { stu_id = id; }

//     void setName(string n) { name = n; }

//     void setMathScore(int m) {
//         math = m;
//         updateTotalScore();
//     }

//     void setChineseScore(int c) {
//         chinese = c;
//         updateTotalScore();
//     }

//     void setInfo(Information i) { info = i; }

//     void updateTotalScore() { total = math + chinese; }

//     void printInfo() const {
//         cout << "Student ID: " << stu_id << endl;
//         cout << "Name: " << name << endl;
//         cout << "Math Score: " << math << endl;
//         cout << "Chinese Score: " << chinese << endl;
//         cout << "Total Score: " << total << endl;
//         cout << "Information:" << endl;
//         info.printAge();
//         info.printSex();
//     }
// };

// class Class {
//    private:
//     vector<Student> students;

//    public:
//     void addStudent(const Student& s) { students.push_back(s); }

//     void setStudents(const vector<Student>& s) { students = s; }

//     vector<Student> getStudents() const { return students; }

//     void displayStudentInfo() const {
//         for (const auto& student : students) {
//             student.printInfo();
//             cout << endl;
//         }
//     }

//     Student getHighestScoringStudent() const {
//         auto maxScoreStudent =
//             max_element(students.begin(), students.end(),
//                         [](const Student& s1, const Student& s2) {
//                             return s1.getTotalScore() < s2.getTotalScore();
//                         });

//         return *maxScoreStudent;
//     }

//     float getAverageScore() const {
//         int totalScore = 0;
//         for (const auto& student : students) {
//             totalScore += student.getTotalScore();
//         }

//         return static_cast<float>(totalScore) / students.size();
//     }

//     void sortByTotalScore() {
//         sort(students.begin(), students.end(),
//              [](const Student& s1, const Student& s2) {
//                  return s1.getTotalScore() < s2.getTotalScore();
//              });
//     }
// };

// int main() {
//     Information info1(20, "Male");
//     Information info2(22, "Female");

//     Student student1("S001", "John", 80, 90, info1);
//     Student student2("S002", "Alice", 75, 85, info2);
//     Student student3("S003", "Bob", 90, 95, info1);

//     Class myClass;
//     myClass.addStudent(student1);
//     myClass.addStudent(student2);
//     myClass.addStudent(student3);

//     cout << "Class Information:" << endl;
//     cout << "==================" << endl;
//     cout << "Displaying student information:" << endl;
//     myClass.displayStudentInfo();
//     cout << endl;

//     Student highestScoringStudent = myClass.getHighestScoringStudent();
//     cout << "The highest scoring student:" << endl;
//     highestScoringStudent.printInfo();
//     cout << endl;

//     float averageScore = myClass.getAverageScore();

//     cout << "The average score of the class: " << averageScore << endl;
//     cout << "Sorting students by total score..." << endl;
//     myClass.sortByTotalScore();

//     cout << "Displaying student information after sorting:" << endl;
//     myClass.displayStudentInfo();

//     return 0;
// }

#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14;

class Shape {
public:
    virtual double getArea() = 0;
    virtual double getPerim() = 0;
};

class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double getArea() override {
        return width * height;
    }

    double getPerim() override {
        return 2 * (width + height);
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double getArea() override {
        return PI * radius * radius;
    }

    double getPerim() override {
        return 2 * PI * radius;
    }
};

int main() {
    int n;
    double w, h, r;
    cin >> n;
    switch (n) {
        case 1: {
            cin >> w >> h;
            Rectangle rect(w, h);
            cout << "area=" << rect.getArea() << endl;
            cout << "perim=" << rect.getPerim() << endl;
            break;
        }
        case 2: {
            cin >> r;
            Circle c(r);
            cout << "area=" << c.getArea() << endl;
            cout << "perim=" << c.getPerim() << endl;
            break;
        }
    }

    return 0;
}
