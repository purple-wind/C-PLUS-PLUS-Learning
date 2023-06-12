//类型转换特性介绍

#include<iostream>
//小对齐系数类型的指针转换成大对齐系数类型的指针，可编译通过，但是解引用错误
void test_low_align_high()
{
    char c = 1;
    char *p = &c;
    unsigned int  *q = (unsigned int*)p;
    std::cout<<"*q="<<*q<<std::endl;
}

void test_high_align_low()
{
    unsigned int c = 65;
    unsigned int *p = &c;
    char *q = (char*)p;
    std::cout<<"*q="<<*q<<std::endl;
}

//不要认为 decltype很简单,它的玩法实际上可以非常复杂。当程序员使用 decltype(exp) 获取类型时，编译器将根据以下三条规则得出结果：
//如果 exp 是一个不被括号( )包围的表达式，或者是一个类成员访问表达式，或者是一个单独的变量，那么 decltype(exp) 的类型就和 exp 一致，这是最普遍最常见的情况。
//如果 exp 是函数调用，那么 decltype(exp) 的类型就和函数返回值的类型一致。
//如果 exp 是一个左值，或者被括号( )包围，那么 decltype(exp) 的类型就是 exp 的引用；假设 exp 的类型为 T，那么 decltype(exp) 的类型就是 T&。

#include <string>
using namespace std;
class Student{
    public:
        static int total;
        string name;
        int age;
        float scores;
};
int Student::total = 0;
void test_decltype_expr()
{
    int n = 0;
    const int &r = n;
    Student stu;
    decltype(n) a = n;  //n 为 int 类型，a 被推导为 int 类型
    decltype(r) b = n;     //r 为 const int& 类型, b 被推导为 const int& 类型
    decltype(Student::total) c = 0;  //total 为类 Student 的一个 int 类型的成员变量，c 被推导为 int 类型
    decltype(stu.name) url = "http://c.biancheng.net/cplus/";  //total 为类 Student 的一个 string 类型的成员变量， url 被推导为 string 类型
}

void test_decltype_fun()
{
    //函数声明
    int& func_int_r(int, char);  //返回值为 int&
    int&& func_int_rr(void);  //返回值为 int&&
    int func_int(double);  //返回值为 int
    const int& fun_cint_r(int, int, int);  //返回值为 const int&
    const int&& func_cint_rr(void);  //返回值为 const int&&
    //decltype类型推导
    int n = 100;
    decltype(func_int_r(100, 'A')) a = n;  //a 的类型为 int&
    decltype(func_int_rr()) b = 0;  //b 的类型为 int&&
    decltype(func_int(10.5)) c = 0;   //c 的类型为 int
    decltype(fun_cint_r(1,2,3))  x = n;    //x 的类型为 const int &
    decltype(func_cint_rr()) y = 0;  // y 的类型为 const int&&
}

using namespace std;
class Base{
    public:
        int x;
};
void test_decltype_lv()
{
    Base obj;
    //带有括号的表达式
    decltype(obj.x) a = 0;  //obj.x 为类的成员访问表达式，符合推导规则一，a 的类型为 int
    decltype((obj.x)) b = a;  //obj.x 带有括号，符合推导规则三，b 的类型为 int&。
    //加法表达式
    int n = 0, m = 0;
    decltype(n + m) c = 0;  //n+m 得到一个右值，符合推导规则一，所以推导结果为 int
    decltype(n = n + m) d = c;  //n=n+m 得到一个左值，符号推导规则三，所以推导结果为 int&
}


