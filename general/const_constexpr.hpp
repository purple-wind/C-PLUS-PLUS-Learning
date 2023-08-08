#include<iostream>
#include<time.h>
#include<chrono>
using namespace std;

//常量表达式:值不会改变且在编译过程就能得到计算结果的表达式
//  1.字面值是常量表达式
//  2.常量表达式初始化的const对象也是常量表达式
void const_expression()
{
    const int max_files = 20;
    const int limit = max_files + 1;
    int staff_size = 27;
    2;
    int x = 0, y = 0;
    (2>0?x:y) = 3;
    cout<<"x="<<x<<" y="<<y<<endl;
}


//constexpr 变量
//c++11起，可以把一个变量申明为constexpr类型，以便编译器来验证变量值是否是一个常量表达式。申明为constexpr的变量一定是
//一个常量，且必须用常量表达式初始化
int g_mf = 1;
void constexpr_variable()
{
    constexpr int mf = 20;
    constexpr int limit = mf + 1;

    //constexpr修饰指针时，constexpr仅对指针本身有效，与指针所指的对象无关
    constexpr int *p0 = nullptr;//p0指向常量
    //constexpr int *p1 = &mf;
    constexpr int *p2 = &g_mf;//p2指向常量，仅仅需要保证g_mf的地址是一个常量即可，而不关注g_mf是否是常量。此处g_mf是一个全局变量，所以它的地址是一个常量，故此可以用constexpr修饰
}


//constexpr函数是指能用于常量表达式的函数。c++11对constexpr的限制如下:
// 1.constexpr函数的返回类型及所有形参的类型都的是字面值类型
// 2.函数体中只能有return这一条有效语句，不能有其它任何有效语句，但是可以有不执行任何操作的语句，比如空语句、类型别名即using申明语句
//注意:定义为constexpr的函数不一定返回常量表达式。当函数的参数是常量表达式时则返回值也是常量表达式，反之则不是。
//也就是说上面2条限制知识最基本的限制,满足以上2个条件未必可以用作常量表达式,满足上面2条限制却也可以用作非常量表达式。
//比如下面对constexpr_fun的使用就无法通过编译(场景1)
//        int c0 = 1;
//        constexpr c1 = constexpr_fun(c0);

//只有如下代码才可编译通过(场景2)
//        constexpr int c0 = 1;
//        constexpr c1 = constexpr_fun(c0);

//或者这样也可编译通过(场景3)
//        int c0 = 1;
//        c1 = constexpr_fun(c0);


constexpr int constexpr_fun(int a)
{
    //int x = 0;//如果函数体内存在此语句，则编译无法通过
    return a;//函数体内只能有return这一条语句
}

//constexpr构造函数
void constexpr_constructor()
{

}





//在这个函数里面，由于constexpr稀释的是fib1这个函数，因此每一次计算的结果都会作为一个常量保存下来
//这个实现的复杂度等同于迭代的方法，基本上为O(n)。
constexpr long int fib1(int n)
{
    return (n <= 1)? n : fib1(n-1) + fib1(n-2); //只能包含一个retrun语句
}
//下面这个函数的时间复杂度为O(2^n)
long int fib2(int n){
        return (n <= 1)? n : fib2(n-1) + fib2(n-2);
}

int const_constexpr(void)
{
    // value of res is computed at compile time.
    int a = 30;
    auto start = chrono::system_clock::now().time_since_epoch();
    const long int res = fib1(a);
    auto end = chrono::system_clock::now().time_since_epoch();
    cout << "Totle Time fib1 : " <<chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "s" << endl;
    std::cout<<"res="<<res<<std::endl;

    start = chrono::system_clock::now().time_since_epoch();
    const long res1 = fib2(a);
    end = chrono::system_clock::now().time_since_epoch();
    cout << "Totle Time fib2 : " <<chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "s" << endl;
    cout << res1 << std::endl;
    return 0;
}
