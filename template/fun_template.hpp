#ifndef __FUNCTION_TEMPLATE_H__
#define __FUNCTION_TEMPLATE_H__
#include<iostream>
#include<type_traits>
#include<utility>
#include<sstream>
template<typename T>void a ( T );
/**
 * @brief:函数模板示例演示：
 * 1.函数模板定义格式template<typename A,typename B> return_value fun_name(arg1,arg2){}
 * 2.模板参数也可以是非类型的参数，但是非类型模板参数不代表类型，而代表一个常量。且必须是一个常量。
 * 以保证在编译阶段知道值，可以实例化出一个类型。
 * 3.函数模板可以隐式推断，在模板函数调用时如果不显示的指定模板参数，模板函数可以根据传入参数表的
 * 参数类型推断出模板类型。
 * 4.函数指针和实参推断,当使用一个函数模板初始化一个函数指针或为一个函数指针赋值时，编译器使用函数
 * 指针的类型推断模板的实参。当参数是一个函数模板实例地址时，程序上下文必须满足对每个模板参数能唯一确定其类型或值。
 * 5.模板实参推断和引用折叠
 * 通常情况下不能将右值引用绑定到左值，但是c++有两个例外规则
 * 1.当将一个左值传递给函数的右值引用参数，且此右值引用指向模板类型的参数时，编译器推断模板类型参数为实参类型的左值引用类型
 * 2.通常不能直接定义一个引用的引用的，但是可以使用类型别名或者模板推断的方式间接定义引用的引用如果我们间接定义一个引用的引
 *用则这些引用会发生折叠，正常情况下引用会折叠成一个普通的左值引用,特别注意折叠是针对函数从实参到形参的转化规则，此过程中模
 * 板类型参数已经推断完毕.
 */
class fun_temp
{
public:

    void used_fun_temp ( void ) {
// 			可以不指定类型，让编译器自动推断
        int ret=compare ( 100,200 );
        std::cout<<"fun temp litter figure is:"<<ret<<std::endl;
// 显示的指定类型为char
        ret=compare<char> ( 'a','b' );
        std::cout<<"fun temp litter  letter is:"<<ret<<std::endl;
        notype<100>();
    }

//  函数指针和实参推断,当使用一个函数模板初始化一个函数指针或为一个函数指针赋值时，编译器使用函数指针的类型推断模板的实参。
    void pfun_test ( void ) {
        extern void b ( int );
        void ( *p_fun ) ( int );
        p_fun=b;
        p_fun=a;
        p_fun ( 100 );
    }


//     模板实参推断和引用
//     1.从左值引用函数参数推断类型,只能传递给它一个左值或一个返回引用类型的表达式
    template<typename T> void left_refer ( T& left_value ) {
        T a=left_value;
        a=2;
        std::cout<<"left_value="<<left_value<<std::endl;
    }

// 	  1.1 const的左值,当函数形参是带const的左值引用时，可以给它传递任何类型的实参(const、非const、临时对象、字面值常量)。
//     当函数参数本身是一个const时T的类型推断的结果不会是一个const的类型，const已经是函数参数类型的一部分了，它不会也是模板参数的一部分。
    template<typename T> void const_left_refer ( const T& const_left_refer ) {
        std::cout<<"const left refer "<<std::endl;
    }
// 	  2.从 右值引用函数参数类型推断，推断出的类型是该右值的实参类型
    template<typename T> void right_refer ( T&& right_value ) {
        T b=right_value;
        std::cout<<"right value1="<<right_value<<std::endl;
        b=3;
        std::cout<<"right value="<<right_value<<std::endl;
    }


    void infer() {
        int value1=1;
        left_refer ( value1 );
        const_left_refer ( value1 );
        right_refer ( 1 );//该处调用函数内部推断出的T类型是传递参数的类型，即int类型
        std::cout<<"value1="<<value1<<std::endl;
    }

// 	引用折叠
//  通常情况下不能将右值引用绑定到左值，但是c++有两个例外规则
//  1.当将一个左值传递给函数的右值引用参数，且此右值引用指向模板类型的参数时，编译器推断模板类型参数为实参类型的左值引用类型
//  2.通常不能直接定义一个引用的引用的，但是可以使用类型别名或者模板推断的方式间接定义引用的引用，如果我们间接定义一个引用的引
//  用则这些引用会发生折叠，正常情况下引用会折叠成一个普通的左值引用，特别注意折叠是针对函数从实参到形参的转化规则，影响的是
//  最终形参的类型(而不是模板参数的类型)，此过程中模板类型参数已经推断完毕。
    void infer1() {
        int value1=1;
        right_refer ( value1 ); //把左值类型传递给右值类型引用，此时编译器推断的T类型为int&
    }
    void infer2() {
// 		---------------------------------------------
// 	    |  模板类型 |实参左值| 实参右值引用| 实参右值 |
// 		---------------------------------------------
// 		|函数形参T& |   T    |     T       |  unvalid |
// 		---------------------------------------------
// 		|函数形参T&&|  T&    |     T&      |   T      |
// 		---------------------------------------------
//      左--左 右--右 模板参数类型为实参类型
//      左--右 unvalid
//      const左--右 模板参数类型为实参类型，不会是const的
//      右--左 模板类型为实参的左值引用类型
        int&& refer=1;
        int value1=1;
        int& refer1=value1;

//         left_refer ( refer ); //因为是形参左值引用，所以实参只能是左值，模板类型为实参类型，T类型为int&&
//         left_refer ( refer1 ); //因为是形参左值引用，所以实参只能是左值，模板类型为实参类型，T类型为int&
// 		left_refer(1);错误

        right_refer(value1);//函数形参为右值引用类型且实参是int(左值)，所以模板类型为实参类型的引用,即T=int&;参数形式为int& &&,折叠为int&
        right_refer ( refer1 ); //函数形参为右值引用类型，实参为int(左值)，所以模板类型为实参类型的引用，即T=int&;参数形式为int& &&,折叠为int&
        right_refer ( refer ); //函数形参为右值引用类型，且实参为int&&(左值);所以模板类型为实参类型，即T=int&;此时的形参形式为int& &&,折叠为int&
        right_refer (1); //函数形参为右值引用类型，且实参为int(右值);所以模板类型为实参类型，即T=int;此时的形参形式为int &&,折叠之后还是int&&
        std::cout<<"value1="<<value1<<std::endl;
    }
    


// 	牛叉的std::move()，标准库使用这一特性的经典例子
    template<typename T> typename std::remove_reference<T>::type&& move ( T&& t ) {
		return static_cast<typename std::remove_reference<T>::type&&> ( t );
	}

private:
// 	定义一个比较两个数大小的模板函数，函数返回类型为T,接收两个参数类型为T的参数
// 	当我们调用一个函数模板时，编译器通常会用函数实参来推断模板实参；但是类模板就不会自己推断；
    template<typename T> T compare ( T a,T b ) {
        if ( a<b ) {
            return a;
        }
        if ( b<a ) {
            return b;
        }
        return 0;
    }

//使用std::less来比较大小
    template<typename T> T compare1 ( T a,T b ) {
        if ( std::less<T>() ( a,b ) ) {
            return a;
        } else {
            return b;
        }
    }

//     非类型模板参数，模板的参数不代表类型,而代表一个常量
    template<int N> void notype() {
        std::cout<<"非模板类型参数表示一个值 "<<N*100<<std::endl;
    }

};

void b ( int )
{

}
template<typename T> void a ( T q )
{
    std::cout<<"编译器推断出模板类型"<<std::endl;
}




/*完美转发，模板的引用折叠实参类型推断的经典使用示例
 *当模板函数的参数是指向模板类型参数的右值引用，则该函数可以保持实参的属性，包括const属性、左值、右值属性
 */
class Flips
{
public:
    void left_f ( int v1,int& v2 ) {
        std::cout<<"leftf_f"<<std::endl;
        ++v2;
    }
    void right_f ( int&& v1,int& v2 ) {
        std::cout<<"right_f"<<std::endl;
        ++v2;
    }
// 	  左值类型的完美转发，当要转发的函数是右值引用时不能编译通过
    template<typename F,typename T1,typename T2> void left_flips ( F f1,T1&& t1,T2&& t2 ) {
        f1 ( t2,t1 );
    }

//   右值类型的完美转发，使用标准库的std::forward<TYPE>(arg)模板保持实参的右值属性
    template<typename F,typename T1,typename T2> void right_flips ( F f1,T1&& t1,T2&& t2 ) {
        f1 ( std::forward<T2> ( t2 ),std::forward<T1> ( t1 ) );
    }

    void test_flips() {
        int i=20;
        std::function<void ( int,int& ) >fun=bind( &Flips::left_f,this,std::placeholders::_1,std::placeholders::_2 );
        left_flips ( fun,i,10 );
        std::cout<<"i="<<i<<std::endl;
        auto fun1=bind ( &Flips::right_f,this,std::placeholders::_1,std::placeholders::_2 );
        right_flips ( fun1,i,10 );
        std::cout<<"i="<<i<<std::endl;
    }
};




/*可变长参数模板
 */
class VariadicTemplate
{
public:
    //模板参数包格式
    template<typename T,typename...Arg> T foo1 ( T t,Arg...arg )
    {
        std::cout<<"run fool"<<std::endl;
        std::cout<<"foo1  "<<sizeof... ( arg ) <<std::endl;
    }
    //非模板参数类型参数包格式
    template<int ...N>void foo2()
    {

    }
    void test()
    {
        foo1 ( 10,'a',"hello" );
    }

    /*变长参数模板的函数实现，一般是采用递归的方式，第一步调用处理包中的第一个实参，然后用剩余实参调用自身。
    *
    */

//    根据模板参数的重载匹配，当最后一个递归调用到print时，参数包只有一个参数，此时该函数和下面函数的匹配度一样高，
// 	  但是该函数相对于可变参数模板更特例化，故选择该函数。
    template<typename T> std::ostream& print ( std::ostream& os,const T& t )
    {
        return os<<t<<std::endl;
    }

// 	除最后一次调用外其它的调用完美匹配的是该可变参数模板函数，上面的print函数不匹配。
//  const Args...rest是包扩展，扩展一个包就是将它分解为构成的元素，通过在模式右边放一个省略号来触发包扩展。
//  下面的例子中对Args的扩展中，编译器将模式const Arg&应用到模板参数包Args中的每个元素，每个参数类型为const type&
//  对print的调用中rest的扩展中模式是rest，此模式扩展出一个由包中元素组成的、逗号分割的列表。
    template<typename T,typename...Args> std::ostream& print ( ostream& os,const T&t ,const Args&...rest )
    {
        os<<t<<", ";
        return print ( os,rest... );
    }






//模式还可以是一个函数，比如此函数中模式就是print1_used(arg)，表示用参数包中的每个元素调用print1_used
    template<typename T>T  print1_used ( const T& t )
    {
        std::cout<<"return by mode="<<t<<std::endl;
        return t;
    }

    template<typename T>std::ostream& print1 ( std::ostream& os,const T& t )
    {
        std::cout<<"end="<<t<<std::endl;
        print1_used ( t );
    }

    template<typename T,typename ... Type>std::ostream& print1 ( std::ostream& os,const T& t,const Type& ...arg )
    {
        std::cout<<"arg="<<t<<std::endl;
        return print1 ( os,print1_used ( arg )... );//此处的模式是print1_used()函数
    }


    
    //  可变长参数函数模板的作用通常是将它们的参数转发给其它函数，所以它们一般形式为：
    // 	template<typename ...Type>fun(Type&&...arg)
    // 	{
    // 		work(std::forward<Type>(arg)...);
    // 	}
    //     此示例中把fun的可变参数传递给work函数，保持参数的所有属性。
    // 	 此例中即扩展了模板参数包也扩展了函数参数包
    template<typename...Type>void forward_print (std::ostream& os, Type&&...args )
    {
        print1(os,std::forward<Type> ( args )... ); //此处的模式是std::forward，把forward_print接收到的可变长参数的属性原封不动的转发给print1函数
    }

    
   
    template<typename T> T& add ( T& t )
    {
        return ++t;
    }
    template<typename T> void expand( T& t )
    {
		
    }

    template<typename T,typename...Args> void expand( T& t ,Args&...rest )
    {
        return expand(add(rest)...);
    }
    
    
    void test1()
    {
        std::ostream& os=std::cout;
        print ( os,'1',"2","3","4",5,1.1 );
        print1 ( os,1,2,3,1.1 );
        forward_print ( os,1,2,3,4,5,6 );
        int a1=1,a2=2,a3=3;
        expand ( a1,a2,a3 );
        std::cout<<"a1="<<a1<<"\ta2="<<a2<<"\ta3="<<a3<<std::endl;
// 		abc();
    }
};

// 类型转换模板
   void test_traits()
   {
	   std::remove_reference<int>::type a_=1;//a_为int型
	   std::remove_reference<int&>::type a1_=1;//a1_为int型
	   std::remove_reference<int&&>::type a2_=1;//a2_为int型
	   
   
	   std::add_const<int>::type a=1;//a的类型是const int
// 	   a=2;//对const变量赋值无法编译通过
	   
	   int a1=1;
	   std::add_const<int&>::type b=a1;//b的类型是int&
       std::add_const< const int >::type b1=a1;//b1的类型是const int
	   
	   std::add_lvalue_reference<int&>::type c=a1;//c的类型是int
	   std::add_lvalue_reference<int && >::type c1=a1;//c的类型是int&
	   
	   std::add_rvalue_reference<int&>::type d=a1;//d的类型为int&
	   std::add_rvalue_reference<int&&>::type d1=100;//d的类型为int&&
	   
	   std::add_pointer<int&>::type e=&a1;//e类型为int*
	   std::add_pointer<int&&>::type e1=&a1;//e1类型为int*
	   std::remove_pointer<int*>::type e2=2;//e2类型为int
	   std::make_signed<unsigned int>::type f=-1;//f类型为有符号数
	   std::make_unsigned<int>::type f1=-1;//f1为无符号数，如果赋值为-1则-1为该类型最大的无符号数
	   std::remove_extent<int[10]>::type g=1;//g为有十个整型元素的数组的元素类型int
	   std::remove_all_extents<int[10][20][30]>::type g1=1;//g1为三位数组的元素类型int

   }

#endif