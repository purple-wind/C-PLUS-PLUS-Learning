#include<iostream>
//变量模板,since by c++14
template <class T>
constexpr T pi = T(3.1415926535897932385L); // 变量模板,从c++14起开始支持，gcc高版本会报警告

//[[deprecated]]申明为废弃的，当代码中其它地方使用了该函数时编译器会报警告，从c++14开始支持
template <class T> [[deprecated]] T circular_area(T r) {  // 函数模板
  return pi<T> * r * r; // pi<T> 是变量模板实例化
}
