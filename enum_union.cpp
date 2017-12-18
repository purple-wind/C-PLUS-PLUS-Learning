/*
 * Copyright 2017 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "enum_union.h"
#include <iostream>
/*总结：
 * 一、枚举
 * c++有限定作用域枚举和不限定作用域枚举;
 * 限定作用域枚举定义enum class name{xxx,xxx}或者enum struct name{xxx,xxx}
 * 不限定作用域的枚举定义方法和c的方法一样 
 * 1.枚举成员是const的，因此在初始化枚举成员时提供的初始值必须是常量表达式，当然也可以在任何需要
 * 常量表达式的地方使用枚举成员。
 * 2.c++11标准允许给限定作用域的枚举指定成员的值大小，默认情况下枚举成员的值是从0开始依次加1。
 * 如果只为枚举的某个成员指定了一个值，而它之后的成员的值自动在此基础上加1
 * 3.c++11标准还允许给限定作用域的枚举成员指定类型，比如: enum a:char{a='a',b='b'};
 * 如果未指定则默认为int类型。非限定作用域的枚举不存在默认潜在类型，只知道潜在类型足够大，能容纳所有枚举值，类型因机器而异。
 * 4.枚举类型的前置声明，未限定作用域的枚举在声明时必须指定成员类型，因为它没有潜在成员类型;
 * 限定作用域的枚举可以不指定成员类型，此时使用的是潜在类型(int)
 * 二、联合
 * 1.联合体所有成员在内存中直占用一份空间，空间大小取决于最大成员类型大小，只要能容纳最大类型成员即可;
 * 2.联合体中的成员在同一时间点只能有一个值，当某个成员被赋值时其它所有成员都是未定义状态的，此时使用其它成员行为是未定义的。
 * 3.经测试发现，当将占用空间大的成员赋值，然后取出占用空间小的成员，此时可以取出正确的值。条件是成员较大的值未造成成员较大的值溢出。
 * 但是float类型除外。因此有一种通过联合体来判断系统大小端的方法就是利用这个特性。
 * 4.匿名联合体，在匿名联合体定义所在的作用域内该匿名联合的成员是直接可以访问的;但是匿名union不能包含受保护的成员或私有成员，也不能定义成员函数。
 */





/**
 * @brief 普通构造函数,使用合成版本
 * 
 */
enum_union::enum_union()=default;

/**
 * @brief 单参构造函数...
 * 
 * @param arg_str ...
 */
enum_union::enum_union(std::string* arg_str):str(arg_str)
{
	std::cout<<"单参构造函数"<<std::endl;
}
/**
 * @brief 拷贝构造 
 * 
 * @param other ...
 */
enum_union::enum_union(const enum_union& other)
{
   std::cout<<"拷贝构造"<<std::endl;
}

/**
 * @brief ...析构函数
 * 
 */
enum_union::~enum_union()
{

}

/**
 * 因为类内有指针类型成员，为了使类具有类值行为，必须定义拷贝赋值运算符;
 * 该类中还定义了枚举和联合类型，因为它们是类型不是成员，所以在拷贝时不必考虑
 * @brief 拷贝赋值
 * 
 * @param other ...
 * @return enum_union&
 */
enum_union& enum_union::operator=(const enum_union& other)
{
	std::cout<<"拷贝赋值运算符"<<std::endl;
	std::string* temp_str=new std::string(*(other.str));
	delete str;
	str=temp_str;
	return *this;
}

/**
 * @brief 拷贝赋值运算符的常函数版本
 * 
 * @param other ...
 * @return bool
 */
bool enum_union::operator==(const enum_union& other) const
{

}

/**
 * @brief 测试enum的效果，c++中有限定作用域枚举和不限定作用域枚举
 * 此函数演示的是不限定作用域的枚举功能
 * @return void
 */
void enum_union::no_scopes_enum()
{
    int a=0;
    if ( a==red )
    {
        std::cout<<"color::blue="<<color::blue<<std::endl;//非限定作用域的枚举成员可以隐式转化成整型
    }
}

/**
 * @brief 作用域枚举的特性演示
 * 
 * @return void
 */
void enum_union::scopes_enum()
{
    Color sc=Color::blue;
    if ( sc==Color::blue )
        std::cout<<"sc="<< ( int ) Color::red<<std::endl;//限定作用域的枚举成员不可以隐式转化成整型，要想转化必须显示进行
}

/**
 * @brief union特性演示
 * 
 * @return void
 */
void enum_union::my_union() 
{
	union digital_type test;
	test.longer=32767;
	std::cout<<"this is test union,member inter="<<test.inter<<std::endl;
	std::cout<<"this is test union,member shorter="<<test.shorter<<std::endl;
	std::cout<<"this is test union,member longer="<<test.longer<<std::endl;
	
}
std::__cxx11::string* enum_union::get_str()
{
    return str;
}






