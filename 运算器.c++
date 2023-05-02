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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int apple;
    int count_apple;
    int orange;
    int count_orange;
    pthread_mutex_t lock;
    pthread_cond_t fmther;
    pthread_cond_t sonCond;
    pthread_cond_t daughterCond;
} Plate;

// 父亲放苹果的函数
void* add_apple(void* arg) {
    Plate* plate = (Plate*)arg;
    while (1) {
        // sleep(1);
        pthread_mutex_lock(&plate->lock);
        while (plate->orange == 1 || plate->apple == 1) {
            pthread_cond_wait(&plate->fmther, &plate->lock);
        }
        plate->apple++;
        plate->count_apple++;
        printf("父亲: 开始放第 %d 个苹果\n", plate->count_apple);
        pthread_cond_signal(&plate->sonCond);
        pthread_mutex_unlock(&plate->lock);
    }
}

// 母亲放橘子的函数
void* add_orange(void* arg) {
    Plate* plate = (Plate*)arg;
    while (1) {
        // sleep(1);
        pthread_mutex_lock(&plate->lock);
        while (plate->orange == 1 || plate->apple == 1) {
            pthread_cond_wait(&plate->fmther, &plate->lock);
        }
        plate->orange++;
        plate->count_orange++;
        printf("母亲: 开始放第 %d 个橘子\n", plate->count_orange);
        pthread_cond_signal(&plate->daughterCond);
        pthread_mutex_unlock(&plate->lock);
    }
}

// 儿子吃苹果的函数
void* eat_apple(void* arg) {
    Plate* plate = (Plate*)arg;
    while (1) {
        // sleep(1);
        pthread_mutex_lock(&plate->lock);
        while (plate->apple < 1) {
            pthread_cond_wait(&plate->sonCond, &plate->lock);
        }
        plate->apple = 0;
        printf("儿子: 开始吃第 %d 个苹果\n", plate->count_apple);
        pthread_cond_signal(&plate->fmther);
        pthread_mutex_unlock(&plate->lock);
    }
}

// 女儿吃橘子的函数
void* eat_orange(void* arg) {
    Plate* plate = (Plate*)arg;
    while (1) {
        // sleep(1);
        pthread_mutex_lock(&plate->lock);
        while (plate->orange < 1) {
            pthread_cond_wait(&plate->daughterCond, &plate->lock);
        }
        plate->orange = 0;
        printf("女儿: 开始吃第 %d 个橘子\n", plate->count_orange);
        pthread_cond_signal(&plate->fmther);
        pthread_mutex_unlock(&plate->lock);
    }
}

int main() {
    Plate plate;
    plate.apple = 0;
    plate.count_apple = 0;
    plate.orange = 0;
    plate.count_orange = 0;
    pthread_mutex_init(&plate.lock, NULL);
    pthread_cond_init(&plate.fmther, NULL);
    pthread_cond_init(&plate.sonCond, NULL);
    pthread_cond_init(&plate.daughterCond, NULL);

    pthread_t father, mother, son, daughter;
    pthread_create(&father, NULL, add_apple, &plate);
    pthread_create(&mother, NULL, add_orange, &plate);
    pthread_create(&son, NULL, eat_apple, &plate);
    pthread_create(&daughter, NULL, eat_orange, &plate);

    pthread_join(father, NULL);
    pthread_join(mother, NULL);
    pthread_join(son, NULL);
    pthread_join(daughter, NULL);

    pthread_mutex_destroy(&plate.lock);
    pthread_cond_destroy(&plate.fmther);
    pthread_cond_destroy(&plate.sonCond);
    pthread_cond_destroy(&plate.daughterCond);

    return 0;
}