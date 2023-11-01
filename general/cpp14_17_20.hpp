#include<iostream>
//变量模板,since by c++14
template <class T>
constexpr T pi = T(3.1415926535897932385L); // 变量模板,从c++14起开始支持，gcc高版本会报警告

//[[deprecated]]申明为废弃的，当代码中其它地方使用了该函数时编译器会报警告，从c++14开始支持
template <class T> [[deprecated]] T circular_area(T r) {  // 函数模板
  return pi<T> * r * r; // pi<T> 是变量模板实例化
}




#if __cplusplus >= 201703L

//c++17编译期获取数据类型
//此处参考网上代码
#include<tuple>
#include<string_view>
#include<cstdio>
#include<iostream>
using namespace std;

template<char...args>
struct static_string
{
        static constexpr const char str[] = {args...};
        operator const char*()const{return static_string::str;}
};
template<typename Object>
constexpr auto get_type_name()
{
    constexpr std::string_view fully_name = __PRETTY_FUNCTION__;
    constexpr std::size_t begin = [&]()
    {
        for(std::size_t i = 0; i < fully_name.size(); i++)
            if(fully_name[i] == '=')
                return i + 2;
    }();
    constexpr std::size_t end = [&]()
    {
        for(std::size_t i = 0; i < fully_name.size(); i++)
            if(fully_name[i] == ']')
                return i;
    }();
    constexpr auto type_name_view = fully_name.substr(begin, end - begin);
    constexpr auto indices = std::make_index_sequence<type_name_view.size()>();
    constexpr auto type_name = [&]<std::size_t...indices>(std::integer_sequence<std::size_t, indices...>)
    {
                               constexpr auto str = static_string<type_name_view[indices]..., '\0'>();
                               return str;
}(indices);
    return type_name;
}

void test_c17_get_type()
{
	constexpr auto p0  = get_type_name<std::tuple<int,float,string>>();
    std::cout<<" "<< p0.str << std::endl;

	constexpr auto p1 = get_type_name<int>();
	std::cout << (std::string(p1) == "int") << std::endl;
}


template<char...args> struct C17Template
{
    //c++17才支持此句
	static constexpr const char str[] = {args...};

    void print()
    {
        std::cout<<"str="<<str<<std::endl;
    }
};

void test_c17_template()
{
    C17Template<'a', 'b'> ccc;
    ccc.print();
}

#endif
