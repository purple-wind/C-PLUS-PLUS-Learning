#include <iostream>
#include <string.h>
#include <unistd.h>
#include "my_friend.hpp"
#include "enum_union.h"
#include "destructor.hpp"

void test_array_row_column()
{
//    int array0[2][3] = {{0,0,0}, {0,0,0}};
    //0 0 0         0 0
    //0 0 0         0 0
    //              0 0
    //2是行 3是列
    //int array0[2][3] = {{0,0}, {0,0}, {0,0}};//编译不过，说明2是行，3是列

    //(*array0 + 1) 前进一个元素
    //(array0 + 1) 前进一行
    //&array0 + 1 前进一个数组全部

    int array1[2][3][4] {  {{0,0,0,0},{0,0,0,0},{0,0,0,0}},  {{0,0,0,0},{0,0,0,0},{0,0,0,0}}  };
    //x,x,x
    //x,x,x
    //x = 0,0,0,0
    int array2[5] = {1,2,3,4,5};
    printf("%p\n", array2);

}


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
    extern void test_realloc();
    test_realloc();
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
    test_array_row_column();

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

    //可变长参数宏的使用方法
    #define PT(format,...) printf(format,##__VA_ARGS__);
    PT("%s %s %s","hello", "world", "\n")

    return 0;
}




