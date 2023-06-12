#include<iostream>
//变量模板,since by c++14
template <class T>
constexpr T pi = T(3.1415926535897932385L); // 变量模板

template <class T> [[deprecated]] T circular_area(T r) {  // 函数模板
  return pi<T> * r * r; // pi<T> 是变量模板实例化
}
