#include<utility>
#include<iostream>
#include<string.h>
int main()
{
 int && a=10;//右值引用　引用　右值
 std::cout<<a<<std::endl;
 int & b=a;//左值引用可以　引用　右值引用类型的变量
 std::cout<<b<<std::endl;
 b+=1;
 std::cout<<a<<std::endl;

 int&& b1=a;//错误，右值引用无法　引用　变量，即使这个变量是右值类型的引用
 std::cout<<"b1="<<b1<<std::endl;

  int i=100;
  int && c=std::move(i);//使用了move表示把ｉ当做右值让ｃ引用，此后i的值是未定义的，只能对ｉ进行赋值或释放，不能使用i的值
  std::cout<<"c="<<c<<std::endl;
  i++;
  std::cout<<i<<std::endl;

 return 0;
}