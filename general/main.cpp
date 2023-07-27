#include <iostream>
#include <string.h>
#include <unistd.h>
#include "my_friend.hpp"
#include "enum_union.h"
#include "destructor.hpp"
#if __cplusplus >= 201402L
#include "cpp14.hpp"
#endif
#include "macro.hpp"

extern int test_arithmetic(void);
extern int const_constexpr(void);
extern void test_flexible_array();
extern void test_low_align_high();
extern void test_high_align_low();

#include<utility>
#include<memory>
#include<vector>
int main (int argc, char **argv)
{
    std::cout<<"---------------内置数组析构-------------------"<<std::endl;
    /*内置数组在出作用域时会自动析构数组内的元素，且从后向前析构*/
    {

        A a[3];
        for(int i = 0; i<3;i++)
        {
            a[i].a = i;
        }
        std::cout<<"after"<<std::endl;
    }
    /*当数组作为类的成员变量时，类析构时会自动析构数组成员内的元素，且从后向前析构*/
    {
        DelArray da;
    }
    std::cout<<"out"<<std::endl;

    std::cout<<"------------------整数溢出---------------------"<<std::endl;
    test_arithmetic();

    std::cout<<"------------------类型转换---------------------"<<std::endl;
    test_low_align_high();
    test_high_align_low();
    std::cout<<"------------------柔性数组---------------------"<<std::endl;
    test_flexible_array();

    std::cout<<"------------------友元-----------------------"<<std::endl;
    Base base;
    Derived_a ba;
    Derived_b bb;
    bb.print1(base);
    bb.pirnt2(ba);

    std::cout<<"---------------枚举和联合-----------------------"<<std::endl;
    // 	枚举和联合
    std::string* str=new std::string ( "67890" );
    enum_union en ( str );
    en.no_scopes_enum();
    en.scopes_enum();
    en.my_union();

    std::cout<<"---------------枚举和联合-----------------------"<<std::endl;
    //变量模板
    //199711L 03
    //201103L c++11
    //201402L c++14
    //201510L c++15
    //201703L c++17
#if __cplusplus >= 201402L
    std::cout << circular_area(2) << std::endl; 	// 12
    std::cout << circular_area(2.0) << std::endl;	// 12.5664
#endif

    std::cout<<"---------------枚举和联合-----------------------"<<std::endl;
    //decltype推导
    extern void test_decltype_expr();
    extern void test_decltype_fun();
    extern void test_decltype_lv();
    test_decltype_expr();
    test_decltype_fun();
    test_decltype_lv();

    std::cout<<"---------------宏-----------------------"<<std::endl;
    test0();
    test1();
    test2();

    return 0;
}




