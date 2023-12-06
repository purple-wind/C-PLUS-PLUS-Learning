#ifndef MACRO_HPP
#define MACRO_HPP
#include<iostream>
#include<stdio.h>
//可变长参数宏的使用方法
#define PT0(format,...) printf(format,##__VA_ARGS__)
//此处如果不用##粘贴，例如PT1就没有用##粘贴。这样会出现一个问题，就是当可变参数为空时，宏的展开会产生一个语法错误。
//因为PT1有一个固定参数format,当像这样PT1("hello\n")方式使用PT1时,PT1会被展开成printf("hello\n",);第一个参数
//后面的逗号未被去掉。当可变长形参类表为空时，##会去掉__VA_ARGS__前面的第一个逗号和所有连续不可见字符
#define PT1(format,...) printf(format,__VA_ARGS__)


//宏粘贴
//##的主要作用就是连接两个字符串，我们在宏定义中可以使用##来连接两个字符。预处理器在预处理阶段对宏展开时，会将##两边的字符合并，并删除##这两个字符。
//当宏的可变长形参类表为空时，##会去掉__VA_ARGS_前面的第一个逗号和所有连续不可见字符

static void test0()
{
    PT0("%s %s %s","hello", "world", "\n");
}


//使用宏连接符(##)连接的对象中存在宏时要注意一下两条结论：
//第一条：任何使用到胶水运算“##”对形参进行粘合的参数宏，一定需要额外的再套一层
//第二条：其余情况下，如果要用到胶水运算，一定要在内部借助参数宏来完成粘合过程


#define M0 100
#define fun0(...)                             \
{                                             \
      uint32_t tmp##M0 = 1;                   \
      std::cout<<std::dec<<M0<<std::endl;     \
      std::cout<<__VA_ARGS__<<std::endl;      \
      std::cout<<tmp##M0<<std::endl;          \
}

static void test1()
{
    fun0(1000)//期望得到如下代码：
    //{
    //    uint32_t tmp100 = 1;
    //    std::cout<<100<<std::endl;
    //    std::cout<<1000<<std::endl;
    //    std::cout<<tmp100<<std::endl;
    //}

    //实际得到的是:
    //{
    //    uint32_t tmpM0 = 1;
    //    std::cout<<100<<std::endl;
    //    std::cout<<1000<<std::endl;
    //    std::cout<<tmpM0<<std::endl;
    //}
    //我们发现M0并没有被替换，这是因为在宏的内部使用##拼接时违反了上面两条规则,所以未被替换。不使用##拼接时可以正常替换，
    //使用下面的方法才可以正常替换
}


#define APPEND2(__A, __B)    __A##__B
#define APPEND1(__A, __B)    APPEND2(__A, __B)
#define fun1(...)                             \
{                                             \
      uint32_t APPEND1(tmp, M0) = 1;          \
      std::cout<<M0<<std::endl;               \
      std::cout<<__VA_ARGS__<<std::endl;      \
      std::cout<<APPEND1(tmp, M0)<<std::endl; \
}

static void test2()
{
    fun1(1000);//预编译后代码如下:
    //{ uint32_t tmp100 = 1; std::cout<<100<<std::endl; std::cout<<1000<<std::endl; std::cout<<tmp100<<std::endl; };
}



//自定义的常用的宏
#define INVALID_LEN(myuse, data_len, ...) if(myuse > data_len){return __VA_ARGS__;}






//C语言中实现可变长参数函数
#include <iostream>
#include <stdarg.h>
using namespace std;
void simple_va_fun(int i,...)
{
    va_list   arg_ptr;   //定义可变参数指针
    va_start(arg_ptr,i);   // i为最后一个固定参数
    int j=va_arg(arg_ptr,int);   //返回第一个可变参数，类型为int
    char c=va_arg(arg_ptr,int);   //返回第二个可变参数，类型为char
    va_end(arg_ptr);        //  清空参数指针
    printf( "%d %d %u\n",i,j,c);
    return;
}

void test4()
{
    simple_va_fun(100);
    simple_va_fun(100,200);
    simple_va_fun(100,200,'a');
}

#endif // MACRO_HPP
