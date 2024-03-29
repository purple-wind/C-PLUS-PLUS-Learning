#include <iostream>
#include <string.h>
#include <unistd.h>
#include <type_traits>
#include "my_friend.hpp"
#include "enum_union.h"
#include "constructor_destructor.hpp"
#if __cplusplus >= 201402L
#include "cpp14_17_20.hpp"
#endif
#include "macro.hpp"
#include "const_constexpr.hpp"
#include "assert_abc.hpp"
#include "initialization_list.hpp"

extern int test_arithmetic(void);
extern int const_constexpr(void);
extern void const_expression();
extern void test_flexible_array();
extern void test_low_align_high();
extern void test_high_align_low();

#include<utility>
#include<memory>
#include<vector>

int main (int argc, char **argv)
{
    std::cout<<"---------------构造和析构-------------------"<<std::endl;
    test_constructor_destructor();
    test_delete_copy_contral();
    test_my_strvec();
    test3();
    exit(0);
    std::cout<<"------内置数组析构-------------"<<std::endl;
    test_array_destructor();
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
    test3();

    std::cout<<"---------------const and constexpr------------------"<<std::endl;
    const_expression();
    constexpr_variable();

    //编译不过，因为c0不是编译期常量，故造成constexpr_fun返回值也不是编译期常量，所以把返回值复制给c1时无法完成
    //int c0 = 0;
    //constexpr int c1 = constexpr_fun(c0);
    //std::cout<<"constexpr_fun ret="<<c1<<std::endl;

    constexpr int c2 = 2;
    constexpr int c3 = constexpr_fun(c2);
    std::cout<<"constexpr_fun ret="<<c3<<std::endl;

    int c4 = 4;
    int c5 = constexpr_fun(c4);
    std::cout<<"constexpr_fun ret="<<c5<<std::endl;

    // value of res is computed at compile time.
    int a = 30;
    auto start = chrono::system_clock::now().time_since_epoch();
    const long int res = fib1(a);
    auto end = chrono::system_clock::now().time_since_epoch();
    cout << "Totle Time constexpr fib1 : " <<chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "s" << endl;
    std::cout<<"res="<<res<<std::endl;

    start = chrono::system_clock::now().time_since_epoch();
    const long int res1 = fib2(a);
    end = chrono::system_clock::now().time_since_epoch();
    cout << "Totle Time no constexpr fib2 : " <<chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "s" << endl;
    cout << res1 << std::endl;






    std::cout<<"LiteralConstClass1 is literal:"<<std::is_literal_type<LiteralConstClass1>::value<<std::endl;
    std::cout<<"LiteralConstClass1 is const:"<<std::is_const<LiteralConstClass1>::value<<std::endl;

    std::cout<<"LiteralConstClass2 is literal:"<<std::is_literal_type<LiteralConstClass2>::value<<std::endl;
    std::cout<<"LiteralConstClass2 is const:"<<std::is_const<LiteralConstClass2>::value<<std::endl;

    std::cout<<"LiteralConstClass3 is literal:"<<std::is_literal_type<LiteralConstClass3>::value<<std::endl;
    std::cout<<"LiteralConstClass3 is const:"<<std::is_const<LiteralConstClass3>::value<<std::endl;

    std::cout<<"LiteralConstClass4 is literal:"<<std::is_literal_type<LiteralConstClass4>::value<<std::endl;
    std::cout<<"LiteralConstClass4 is const:"<<std::is_const<LiteralConstClass4>::value<<std::endl;


    std::cout<<"LiteralConstClass5 is literal:"<<std::is_literal_type<LiteralConstClass5>::value<<std::endl;
    std::cout<<"LiteralConstClass5 is const:"<<std::is_const<LiteralConstClass5>::value<<std::endl;

    std::cout<<"LiteralConstClass6 is literal:"<<std::is_literal_type<LiteralConstClass6>::value<<std::endl;
    std::cout<<"LiteralConstClass6 is const:"<<std::is_const<LiteralConstClass6>::value<<std::endl;

    std::cout<<"LiteralConstClass7 is literal:"<<std::is_literal_type<LiteralConstClass7>::value<<std::endl;
    std::cout<<"LiteralConstClass7 is const:"<<std::is_const<LiteralConstClass7>::value<<std::endl;


    //判断一个类是否是聚合类,is_aggregate<T>c++17才支持
#if __cplusplus >= 201703L
    std::cout<<"int is aggregate:"<<std::is_aggregate<int>::value<<std::endl;
    std::cout<<"string is aggregate:"<<std::is_aggregate<std::string>::value<<std::endl;
    std::cout<<"AggregateClass0 is aggregate:"<<std::is_aggregate<AggregateClass0>::value<<std::endl;
    std::cout<<"AggregateClass1 is aggregate:"<<std::is_aggregate<AggregateClass1>::value<<std::endl;
    std::cout<<"AggregateClass3 is aggregate:"<<std::is_aggregate<AggregateClass3>::value<<std::endl;
    std::cout<<"AggregateClass4 is aggregate:"<<std::is_aggregate<AggregateClass4>::value<<std::endl;
    std::cout<<"AggregateClass5 is aggregate:"<<std::is_aggregate<AggregateClass5>::value<<std::endl;
#endif

    //constexpr LiteralConstClass6 c6;//由于LiteralConstClass6不是字面值常量类，故无法构造constexpr对象，此句无法通过编译
    constexpr LiteralConstClass7 c7;//LiteralConstClass7是字面值常量类，故可以定义constexpr对象
    constexpr LiteralConstClass1 c8;//LiteralConstClass1是字面值常量类，故可以定义constexpr对象
    constexpr LiteralConstClass1 c9 = c8;//LiteralConstClass1是字面值常量类，故可以用c8初始化

    test_assert1(5);
    test_assert2(5);
    test_assert3(5);

    std::cout<<"---------------统一初始化------------------"<<std::endl;
    test_li();

    ConstexprStaticMemberClass x;
    std::cout<<"i="<<x.arr0[1]<<std::endl;//常量下标可以访问数组元素
    for(int i = 0; i < 4; i++)
    {
        //std::cout<<"i="<<x.arr0[i]<<std::endl;//编译失败,非常量下标不可访问数组元素,因为下标在运行时才知道,但是在运行的代码中不存在数组的定义,所以编译时直接阻止该行为
        //std::cout<<"arr0="<<x.arr0<<std::endl;//编译失败,访问数组名实际上是取数组首元素的地址,该数组都不存在,何来地址?所以编译时直接阻止该行为
        //std::cout<<"&d0="<<&x.d0<<std::endl;//同上,d0不存在,更取不了地址,就像对宏取地址一样

    }
    return 0;
}




