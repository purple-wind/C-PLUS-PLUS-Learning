#include<string>
#include<vector>
#include<utility>
//1.列表初始化，即用大口号包裹初始值的方式初始化，形如 std::vector<int>vec{1,2,3};
//2.统一初始化，在c++11中统一初始化就是列表初始化，C++11之前的初始化语法很乱，有如下四种初始化方式:
    //  小括号：int x(0);             //C++98 c++11
    //  等号：int x = 0;              //C++98 c++11
    //  大括号：int x{0};             //C++98成功，C++11成功
    //  等号和大括号：int x = {0};    //C++98失败，C++11成功
//   在c++11之后统一初始化方式为列表初始化，各种初始化场景都可以用列表初始化,例如数数组 容器 类 结构体等

//3.c++11虽然用列表初始化各种场景，但是在某些条件下列表初始化却不能成功
//  1.类类型的对象，如果定义类的时候使用了类内初始化，则该类的对象不能使用列表初始化,直到c++14才支持
//  2.不管时类还是结构体,成员变量必须在public部分,否则也不能初始化
//  如果想在c++11中统一初始化定义了类内初始值的类对象,必须在类内定义构造函数或者使用c++14以上编译器
struct Li0
{
        char a;
        int b;
        double c;
        std::string d;
};


struct Li1
{
        char a = 'a';
        int b;
        double c;
        std::string d;
};

struct Li2
{
        Li2(char a, int b, double c, std::string d):a(a), b(b), c(c), d(d)
        {

        }
        char a;
        int b;
        double c;
        std::string d;
};

void test_li()
{
    int a0{1};
    int a1 = {1};
    int a2[]{1,2,3};
    int a3[] = {1,2,3,4};
    std::vector<int>a4{1,2};//列表初始化二个参数的vector时,表示在容器中放了1 2两个值,而不放了1个2
    std::vector<int>a5 = {1,2};
    std::pair<char, int> a6{'a', 1};
    std::pair<char, int> a7 = {'a', 1};


    Li0 x0{'1', 2, 3.3, "abc"};//ok
    Li0 x1 = {'1', 2, 3.3, "abc"};//ok

//    Li1 x2{'1', 2, 3.3, "abc"};//由于Li1中定义了类内初始值则无法编译通过
//    Li1 x3 = {'1', 2, 3.3, "abc"};//on

    Li2 x4{'1', 2, 3.3, "abc"};
    Li2 x5 = {'1', 2, 3.3, "abc"};

}
