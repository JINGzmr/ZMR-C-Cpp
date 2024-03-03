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

#include <iostream>
using namespace std;

// int main()
// {
//     int a=2;
//     int *b =&a;
//     cout << b << endl << *b<< endl;
// }

template <typename T>
void printX(T& t) {
    std::cout << "left value" << std::endl;
}

template <typename T>
void printX(T&& t) {
    std::cout << "rifht value " << std::endl;
}

template <typename T>
void test(T&& v) {
    printX(v);
    printX(move(v));
    printX(forward<T>(v));
}

int main() {
    test(100);
    cout << "--------" << endl;

    int num = 10;
    test(num);
    cout << "--------" << endl;

    test(forward<int>(num));
    cout << "--------" << endl;

    test(forward<int&>(num));
    cout << "--------" << endl;

    test(forward<int&&>(num));

    return 0;
}
