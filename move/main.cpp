#include<utility>
#include<iostream>
#include<string.h>
#include<type_traits>

// 	牛叉的std::move()，标准库使用模板类型推断和引用折叠这一特性的经典例子，由于模板类型推断和引用折叠的特性，
// my_move既可以接受左值实参，也可以接受由值实参，都能表现出正确的行为。只是接受右值实参的时候my_move什么都不做而已。
template<typename T> typename std::remove_reference<T>::type&& my_move ( T&& t )
{
    return static_cast<typename std::remove_reference<T>::type&&> ( t );//将一个左值转换成一个右值引用，此时左值被截断。
}

int main()
{
    int && a=10;//右值引用　引用　右值
    std::cout<<a<<std::endl;
    int & b=a;//左值引用可以　引用　右值引用类型的变量
    std::cout<<b<<std::endl;
    b+=1;
    std::cout<<a<<std::endl;

//     int&& b1=a;//错误，右值引用无法　引用　变量，即使这个变量是右值类型的引用
//     std::cout<<"b1="<<b1<<std::endl;

    int i=100;
    int && c=std::move ( i ); //使用了move表示把ｉ当做右值让ｃ引用，此后i的值是未定义的，只能对ｉ进行赋值或释放，不能使用i的值
    std::cout<<"c="<<c<<std::endl;
    i++;
    std::cout<<i<<std::endl;

    return 0;
}
