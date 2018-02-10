#include <iostream>
#include "./funcation/funcation.cpp"
#include "container/sequential_container.hpp"
#include "container/unordered_container.hpp"
#include "./stream/my_fstream.h"
#include "template/fun_template.hpp"
#include "template/class_temp.hpp"
#include "throw_try_catch/throw.hpp"
#include "friend/my_friend.h"
#include <string.h>
#include "enum_union.h"
#include "operator/operate.cpp"
#include "my_allocator.h"



/**
 * @brief 文档申明，快捷键Alt+Shift+D，貌似只能给函数添加，对整个文档的
 *说明不能生成
 * @param a ...
 * @param b ...
 * @param c ...
 * @return void
 */
void test ( int a,int b ,int c )
{
    std::cout<<"a="<<a<<std::endl;
    std::cout<<"b="<<b<<std::endl;
    std::cout<<"c="<<c<<std::endl;
}

int main ( int argc, char **argv )
{
//     容器
  std::cout<<"------------------容器-------------------"<<std::endl;
  Container test_container;
  test_container.test_assign();
  test_container.test_wsap();
  test_container.my_insert();
  test_container.get_start();
  
  used1();
  used2();
  used3();



  std::cout<<"---------------文件流--------------------"<<std::endl;
  // 	文件流
  Fstream test_fstream;
  test_fstream.rw_binary ( "test.txt" );
  test_fstream.test_getline();
  Fstream::c_file();

  // 	函数对象和绑定
  std::cout<<"--------------函数对象和绑定-------------"<<std::endl;
  PrintString Ps;
  Ps.run();

  My_Bind my_bind;
  my_bind.run();
  my_bind();
  int value1=100,value2=200;
  auto new_fun1=bind ( My_Bind::static_number,value1,value2,std::placeholders::_1 );
  new_fun1 ( 300 );
  auto new_fun2=bind ( &My_Bind::no_static_number,my_bind,value1,std::placeholders::_1,value2 );
  new_fun2 ( 400 );



// 函数模板
  std::cout<<"-------------函数模板----------------"<<std::endl;
  fun_temp temp;
  temp.used_fun_temp();
//     temp.pfun_test();
// 	temp.infer();
// 	temp.infer1();
  temp.infer2();

//     int a11=100;
//     int&& a22=std::move(a11);
//     std::cout<<"a1="<<a11<<std::endl;
//     a22=200;
//     std::cout<<"a1="<<a11<<std::endl;
//     a11=300;
//     std::cout<<"a1="<<a11<<std::endl;
//     std::cout<<"a2="<<a22<<std::endl;
//     a22=200;
//     std::cout<<"a1="<<a11<<std::endl;




// 类模板
  std::cout<<"-----------------类模板--------------"<<std::endl;
  Class_temp<int,char,t3> ClassTemp;
  ClassTemp.fun_in_class ( "argv1","argv2" );
  typedef Class_temp<std::string,std::string,std::string> CT;
  CT ct;
  // 	ct.run("abc","def");//run函数是类模板中的一个成员函数，类模板的成员函数只有在被使用时才会被实例化。
  // 	所以此句没有被调用就不会报错，一旦被调用就会出错。即使此函数的实现中有错误，在模板实例化的时候也不
  // 	会报错，因为成员函数没有被使用使用。
  Blob<int> blob_int;
  blob_int.empty();

  std::cout<<"--------------构造函数----------------"<<std::endl;
//构造函数
  t3 a100 ( ClassTemp.run ( 100,'A' ) ); //这句既没有发生拷贝构造也没发生拷贝赋值,可能被编译器优化
  t3 a101 ( a100 ); //拷贝构造
  t3 a102=a100;//拷贝构造
  a101=a100;//拷贝赋值

  std::cout<<"----------------转发------------------"<<std::endl;
// 转发
  Flips flips;
  flips.test_flips();
  VariadicTemplate var;
  var.test();
  std::cout<<"--------------可变长参数模板-----------"<<std::endl;
  var.test1();



  std::cout<<"----------------异常-------------------"<<std::endl;
//   异常处理
  Throw th;
  for ( int i=99; i<102; i++ )
    {
      th.test ( i );
    }
  Throw th1;
  th1.test1 ( 0 );
  try
    {
      th1.test2 ( 0 );
    }
  catch ( std::logic_error er )
    {
      std::cout<<er.what() <<std::endl;
    }

std::cout<<"------------------友元-------------------"<<std::endl;      
  Base base;
  Derived_a ba;
  Derived_b bb;
  bb.print1(base);
  bb.pirnt2(ba);
  


  std::cout<<"-----------枚举和联合------------------"<<std::endl;
// 	枚举和联合
  std::string* str=new std::string ( "67890" );
  enum_union en ( str );
  en.no_scopes_enum();
  en.scopes_enum();
  en.my_union();

  std::cout<<"运算符重载"<<std::endl;
// 运算符重载
  Operator op ( 1,2,str );
  op.operator() ( "operator 被调用" );
  op ( "省略 operator(),可以像函数一样被调用" );
  std::string* str1=new std::string ( "12345" );
  Operator op2 ( 1,2,str1 );
  op2=op;
  std::cout<<*op2.get_str() <<std::endl;

  std::cout<<"--------------allocator---------------"<<std::endl;
// 内存分配器allocator
  my_allocator a1;
  a1.used_allocator();
  return 0;
}




