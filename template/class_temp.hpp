#ifndef __CLASS_TEMP_H__
#define __CLASS_TEMP_H__
#include<iostream>
#include<memory>
#include<cassert>
#include<vector>
#include<type_traits>//标准库的类型转换模板头文件

/* 定义类模板的格式: template<typename T0, typename T1, typename Tn> class XXX_Name{};
 * 1.类模板名字不是一个类型名，类模板用来实例化类型，而一个实例化的类型总是包含模板实参。
 * 2.编译器不会为类模板推断模板类型，但是会为函数模板推断模板参数类型
 * 3.在类模板的内部如果还需要使用其它的类模板，在实例化其它类模板的时候可以传递类模板的模板类型参数，而不必须传递真实的类型参数。
 * 4.在类模板内部如果使用类模板自己的类型时不需要提供模板实参，直接使用类名即可。
 * 5.类模板的成员函数不会在类模板实例化成类型的时候被实例化，只有在该成员函数被使用的时候才会被实例化。类模板成员函数本身是一个普
 * 通函数，但是类模板的每个实例都有自己版本的成员函数，所以类模板的成员函数具有和类模板相同的模板参数。因而定义在类模板之外的成员
 * 函数必须以template开始，后接类模板参数表。类模板的成员函数不能是虚函数
 * 6.类模板和友元，如果某一个类模板包含一个友元声明，如果该友元是一个非模板友元则该友元和该类的所有实例具有友元关系,即该友元被授权
 * 可以访问该模板类的所有实例;如果友元本身也是一个模板，则类模板可以授权给所有友元模板的实例，也可以只授权给特定的友元模板实例。
 * 7.类模板别名，c++11之后的标准允许为类模板定义一个类型别名，以Class_temp为例格式如下template<typename T> using alias=Class_temp<T1,T2,T3>;
 * 8.实例化后的类模板别名定义和普通别名定义一样 typedef Class_temp<T1,T2,T3> Alias;
 * 9.类模板的静态成员，每个实例化的类模板拥有它对应的静态成员和静态成员函数，每个实例化的类模板的对象共用一个静态成员和静态成员函数。和其它成员函数类似，静态
 *   成员函数只有在使用时才会实例化。
 * 10.使用类模板的类型成员必须在前面加typename关键字
 * 11.显示实例化：
 * 当在多个文件中实例化相同的类模板(模板参数相同)时，会在多个文件中分别单独进行一份实例化，而它们实例化出来的类型都是一样的，这在较大型的
 * 系统中开销是比较大的。新标准使用显示实例化来解决这个问题。解决办法和全局变量的方法一样，即一处定义，多处声明。格式如下：
 * extern template declaration;//实例化声明
 * template declaration;//实例化定义
 * 在实例化定义的时候和普通实例化不同，实例化定义的时候会实例化类的所有成员，包括成员函数。而在普通实例化过程中成员函数只会在成员函数被使用时
 * 才会实例化。
 * 12.返回迭代器的解引用类型(对迭代器解引用的得到的是引用);尾置返回,当在编译时不知道返回类型，此时使用尾置返回并使用decltype使编译器知道返回类型;
 * 而使用该接口的用户并不需要定义返回类型，使用auto即可。
 * 13.类模板特化：
 *	  模板全特化:指对所有模板参数进行特化
 *	  模板偏特化：模板偏特化是模板特化的一种特殊情况，指显示指定部分模板参数而非全部模板参数，或者指定模板参数的部分特性分而非全部特性，也称为模板部分特化。
 *	  		模板偏特化又分为两种情况：
 *				一种是指对部分模板参数进行全特化
 *				另一种是对模板参数特性进行特化，包括将模板参数特化为指针、引用或是另外一个模板类
 *14.类的缺省模板参数，类模板也可以制定缺省模板实参，当我们为类模板所有模板参数指定了缺省参数，当我们想以缺省参数实例化模板类时，需要在类名后跟一对空括号。
 */


class t3 {
public:
	t3()=default;
    t3(int a,char b):value1(a),value2(b){std::cout<<"t3 2个参数构造函数"<<std::endl;}
	t3(const t3& that){
		std::cout<<"t3 浅拷贝构造"<<std::endl;
		value1=that.value1;
		value2=that.value2;
	}
	int value1;
    char value2;
	t3& operator=(const t3& rv)
	{
	 std::cout<<"t3 浅拷贝赋值"<<std::endl;
	 value1=rv.value1;
	 value2=rv.value2;
     return *this;
	}
};

template<typename T1,typename T2 ,class T3 > class Class_temp {
public:
	//模板类的成员函数
	T3 run(T1 figure,T2 letter){
		std::cout<<"letter="<<letter<<std::endl;
	     T1 resut=figure*figure;
		return t3(figure,letter);
	}
	//模板类的成员函数也是一个模板函数,成员模板的模板参数必须和类模板的模板参数不一样,在类内定义格式如下
//     template<typename A,typename B> void fun_in_class(A agrv1,B argv2){
// 	 
// 		std::cout<<"fun_in_class out of class Class_temp"<<std::endl;
// 		
// 	}
	template<typename A,typename B>void fun_in_class(A argv1,B argv2);
	
private:
    T1 mumber1;
    T2 mumber2;
};

//如果fun_in_class定义在类的外部应该再加上类模板的模板参数表
template<typename T1,typename T2,typename T3> template<typename A,typename B> void Class_temp<T1,T2,T3>::fun_in_class(A argv1,B argv2){
	std::cout<<"fun_in_class out of class Class_temp"<<std::endl;
}



//---------------------------------------------------------------------------------
//C++ Primer中的示例
//---------------------------------------------------------------------------------
/*为了引用模板的一个特定实例，必须先声明模板自身。下面前置声明是在Blob类模板中声明友元所必需的;
 前置声明
 */
template<typename T> class Pal;

template<typename T> class Blob{
public:
	/*一对一友好关系
	 * 每个Blob实例将访问权限授予用相同类型实例化的BlobPtr和相等运算符，这就是所谓的一对一友好关系。
	 *由于友元的声明用Blob的模板形参作为它们自己的模板实参，因此友好关系被限定在用相同类型实例化的
	 * Blob与BlobPtr、相等运算符之间。
	 */
	friend class Pal<T>;
	
	/*通用和特定的模板友好关系
	 * 一个类也可以将另外一个模板的每个实例都声明为自己的友元，或者限定特定的实例为友元。
     *Pal2的所有实例都是Blob的每个实例的友元，不需要前置声明;为了让所有实例成为友元，
     *友元声明中必须使用与类模板本省不同的模板参数，我们在这使用了X模板参数
     */
	template<typename X> friend class Pal2;
	
	/*Pal3是一个非类型模板类，它是所有Blob实例的友元,Pal3不需要前置声明*/
	friend class Pal3;
	
	/*将模板自己的类型参数声明为模板的友元,即将访问权限授予用来实例化Blob的类型
	 *
	 */
	friend T;
	
	
	
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;//使用typename的目的是告诉size_type是一个类型而不是一个静态成员
    Blob():data(std::make_shared<std::vector<T>>()){
		
	}
	Blob(std::initializer_list<T>il);
	size_type size()const{return data->size();}
	bool empty()const{return data->empty();}
	void push_back(const T& t){data->push_back(t);}
	void push_back(T&& t){data->push_back(std::move(t));}
	void pop_back();
	T& back();
	T& operator[](size_type i);
    static size_t count(){return ctr;}
private:
	std::shared_ptr<std::vector<T>>data;
	void check(size_type i,const std::string& msg)const;
    static size_t ctr;
};

//类模板成员函数本身是一个普通函数，但是类模板的每个实例都有自己版本的成员函数，所以类模板的成员函数具有和类模板相同的模板参数。因而
// 定义在类模板之外的成员函数必须以template开始，后接类模板参数表。
template<typename T> void Blob<T>::check(size_type i,const std::string& msg)const{
    assert(data!=nullptr);
	if(i>=data->size())
		throw std::out_of_range(msg);
}

template<typename T> T& Blob<T>::back()
{
	assert(data!=nullptr);
	return data->back();
}

template<typename T> T& Blob<T>::operator[](size_type i)
{
	assert(data!=nullptr);
    check(i,"[] out_of_range");
	return (*data)[i];
}

template<typename T> Blob<T>::Blob(std::initializer_list<T>il):data(std::make_shared<std::vector<T>>(il)){
}

template<typename T> size_t Blob<T>::ctr = 0;


//显示实例化Blob的一个类
//extern template class Blob<double>;
template class Blob<double>;

/*
 *
 *
 *
 *
 *
 */
// 返回迭代器的解引用类型(对迭代器解引用的得到的是引用);尾置返回,当在编译时不知道返回类型，
// 此时使用尾置返回并使用decltype使编译器知道返回类型;而使用该接口的用户并不需要定义返回类型，使用auto即可。
template<typename Iter> auto fun1(Iter begin,Iter end)->decltype(*begin)
{
	return *begin;
}

// 把引用类型转换成变量本身的类型
template<typename Iter>auto fun2(Iter begin,Iter end)->typename std::remove_reference<decltype(*begin)>::type
{
	return *begin;
}



//模板偏特化
//模板偏特化经典应用是标准库的remove_reference系列操作
template<typename _Tp>
  struct remove_reference0
  { typedef _Tp   type; };

template<typename _Tp>
  struct remove_reference0<_Tp&>
  { typedef _Tp   type; };

template<typename _Tp>
  struct remove_reference0<_Tp&&>
  { typedef _Tp   type; };


#endif

//标准库std::is_const的实现
template<typename _Tp> class IsConst : public std::false_type
{
    public:
    IsConst()
    {
        std::cout<<"1"<<std::endl;
    }
};
template<typename _Tp> class IsConst<const _Tp>: public std::true_type
{
    public:
    IsConst()
    {
        std::cout<<"2"<<std::endl;
    }
};






struct Magic0{};
struct Magic1{};
class Magic0A
{
    public:
        typedef Magic0 type;

};

class Magic1A
{
    public:
        typedef Magic1 type;

};

template<class T> void Accept(T magic)
{
    std::cout<<"Magic general"<<std::endl;
    Accept(magic, typename T::type());
    Accept(magic, typename T::type());
}

//base
template<class T> void Accept(T magic1, T magic2)
{

}

//part args is general type
template<class T> void Accept(T magic1, char mime)
{
   //magic1 = extract(mime);
}

//only give general type
template<class T> void Accept(T magic, Magic1)
{
    std::cout<<"Maigc1"<<std::endl;
}
template<class T> void Accept(T magic, Magic0)
{
    std::cout<<"Magic0"<<std::endl;
}

//类的偏特化,第二个模板参数本质上是一个非类型模板参数，
//只是这个参数的类型是类型模板参数(即此处的第一个模板参数)，
//所以第二个参数需要满足非类型模板参数的一切限制。
template<typename T, T v> class Tmp{
public:
        void Print()
        {
            std::cout<<"v="<<v<<std::endl;
        }
};

