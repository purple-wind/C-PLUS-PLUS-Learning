#ifndef __FUNCTION_TEMPLATE_H__
#define __FUNCTION_TEMPLATE_H__
#include<type_traits>
#include<utility>
#include<sstream>
#include<functional>
#include<iostream>
#include<cstring>

void fun0(int v)
{
    std::cout<<"fun0="<<v<<std::endl;
}
void fun1(int v)
{
    std::cout<<"fun1="<<v<<std::endl;
}

int g_i = 100;
const int g_ii = 200;
const int* g_pi = &g_i;
std::string g_str = "12345";



void b ( int )
{

}
template<typename T> void a ( T q )
{
    std::cout<<"编译器推断出模板类型"<<std::endl;
}

template<typename T> void debug_rep(const T &t)
{
    std::cout<<"ref"<<" "<<std::is_const<T>::value << std::is_const<const T&>::value <<std::is_const<decltype(t)>::value<<std::endl;
}

template<typename T> void debug_rep(const T *t)
{
    std::cout<<"pointer"<<std::is_const<T>::value << std::is_const<const T&>::value <<std::is_const<decltype(t)>::value<<std::endl;
}


/**
 * @brief:函数模板示例演示：
 * 1.函数模板定义格式template<typename A,typename B> return_value fun_name(arg1,arg2){}
 *   其中A、B为类型参数，类型参数可以作为函数返回值类型、函数参数类型、函数内部定义变量的类型。
 * 2.模板参数也可以是非类型的参数，但是非类型模板参数不代表类型，而代表一个常量，且必须是一个常量。
 *   以保证在编译阶段知道值，可以实例化出一个类型。两种大的类型可以作为非模板参数的形参:
 *  1.整型，注意char、short、long、long long都是整型.但是浮点型不可以
 *  2.对象类型的指针或者左值引用，这里的对象可以是内置类型、也可以是类类型
 *  绑定到非类型模板参数的整型实参必须是一个常量表达式，绑定到非类型参数的指针或者引用的实参必须具有静态生存期。总结来说
 *  就是传递给模板非类型参数的实参必须是一个常量表达式。查阅网上资料有说到"非类型模板参数可以是指针，但该指针必须指向外部链接对象",
 *  听起来有一定道理，但是在本人机器实测跟网上资料有不一致的地方。
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
 * 6.函数模板特化，函数模板只能全特化，不能部分特化。即必须为原函数模板中每个模板参数都提供实参。template<>表示为原函数模板中每个模板参数都提供实参
 */
class fun_temp
{
    public:
        // 函数指针和实参推断,当使用一个函数模板初始化一个函数指针或为一个函数指针赋值时，编译器使用函数指针的类型推断模板的实参。
        void infer_pfun() {
            extern void b ( int );
            void ( *p_fun ) ( int );
            p_fun=b;
            p_fun=a;
            p_fun ( 100 );
        }


        //模板实参推断和引用
        //1.从左值引用函数参数推断类型,只能传递给它一个左值或一个返回引用类型的表达式
        template<typename T> void left_refer ( T& left_value ) {
            T a=left_value;
            std::cout<<"l arg="<<std::is_lvalue_reference<decltype(left_value)>::value<<std::endl;
            std::cout<<"l T="<<std::is_lvalue_reference<decltype(a)>::value<<std::endl;
            std::cout<<"l arg="<<std::is_rvalue_reference<decltype(left_value)>::value<<std::endl;
            std::cout<<"l T="<<std::is_rvalue_reference<decltype(a)>::value<<std::endl;
            a=2;
            std::cout<<"left_value="<<left_value<<std::endl;
        }

        //1.1 const的左值,当函数形参是带const的左值引用时，可以给它传递任何类型的实参(const、非const、临时对象、字面值常量)。
        //当函数参数本身是一个const时T的类型推断的结果不会是一个const的类型，const已经是函数参数类型的一部分了，它不会也是模板参数的一部分。
        template<typename T> void const_left_refer ( const T& const_left_refer ) {
            std::cout<<"const left refer "<<std::endl;
        }
        //2.从 右值引用函数参数类型推断，推断出的类型是该右值的实参类型
        template<typename T> void right_refer ( T&& right_value ) {
            T b=right_value;
            std::cout<<"r arg="<<std::is_reference<decltype(right_value)>::value<<std::endl;
            std::cout<<"r T="<<std::is_reference<decltype(b)>::value<<std::endl;
            std::cout<<"r arg="<<std::is_lvalue_reference<decltype(right_value)>::value<<std::endl;
            std::cout<<"r T="<<std::is_lvalue_reference<decltype(b)>::value<<std::endl;
            std::cout<<"r arg="<<std::is_rvalue_reference<decltype(right_value)>::value<<std::endl;
            std::cout<<"r T="<<std::is_rvalue_reference<decltype(b)>::value<<std::endl;

            std::cout<<"right value1="<<right_value<<std::endl;
            b += 3;
            std::cout<<"right value="<< right_value<<std::endl;
        }


        void infer0() {
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
            std::cout<<"------------infer1"<<std::endl;
            int value1=1;
            right_refer ( value1 ); //把左值类型传递给右值类型引用，此时编译器推断的T类型为int&
        }
        void infer2() {
            // 		---------------------------------------------
            // 	    |  模板类型 | 实参左值| 实参右值引用  | 实参右值  |
            // 		---------------------------------------------
            // 		|函数形参T& |   T    |     T       |  unvalid |
            // 		---------------------------------------------
            // 		|函数形参T&&|   T&   |     T&      |   T      |
            // 		---------------------------------------------
            //      左--左 右--右 模板参数类型为实参类型
            //      左--右 unvalid
            //      const左--右 模板参数类型为实参类型，不会是const的
            //      右--左 模板类型为实参的左值引用类型

            std::cout<<"------------infer2"<<std::endl;
            int value1 = 1;
            int&& refer = 1;
            int& refer1 = value1;

            left_refer(refer); //因为是形参左值引用，所以实参只能是左值，模板类型为实参类型，T类型为int
            left_refer(refer1); //因为是形参左值引用，所以实参只能是左值，模板类型为实参类型，T类型为int
            //left_refer(1);错误

            right_refer(value1);//函数形参为右值引用类型且实参是int(左值)，所以模板类型为实参类型的引用,即T=int&;参数形式为int& &&,折叠为int&,
            //该函数被实例化为这样void right_refer(int& right_value);

            right_refer(refer1); //函数形参为右值引用类型，实参为int(左值)，所以模板类型为实参类型的引用，即T=int&;参数形式为int& &&,折叠为int&
            //该函数被实例化为这样void right_refer(int& right_value);
            std::cout<<"infer2 value1=" << value1<<std::endl;
            right_refer(refer); //函数形参为右值引用类型，且实参为int(左值);所以模板类型为实参类型的引用，即T=int&;此时的形参形式为int& &&,折叠为int&
            //该函数被实例化为这样void right_refer(int& right_value);

            right_refer(1); //函数形参为右值引用类型，且实参为int(右值);所以模板类型为实参类型，即T=int;此时的形参形式为int &&,折叠之后还是int&&
            //该函数被实例化为这样void right_refer(int&& right_value);
            std::cout<<"value1="<<value1<<std::endl;
        }



        //牛叉的std::move()，标准库使用这一特性的经典例子
        template<typename T> typename std::remove_reference<T>::type&& move ( T&& t ) {
            return static_cast<typename std::remove_reference<T>::type&&> ( t );
        }

        //定义一个比较两个数大小的模板函数，函数返回类型为T,接收两个参数类型为T的参数
        //当我们调用一个函数模板时，编译器通常会用函数实参来推断模板实参；但是类模板就不会自己推断；
        //此版本无法处理不能拷贝的类型
        template<typename T> T compare(const T a, const T b ) {
            return a < b ? a : b;
            //或者使用std::less来比较大小
            //return std::less<T>() ( a,b ) ? a : b;
        }

        //支持处理不能拷贝的类型,但是此函数不能和上面函数同时出现，因为他们具有同样好的匹配对，造成模板无法实例化
        //template<typename T> T compare(const T& a, const T& b ) {
        //return a < b ? a : b;
        ////或者使用std::less来比较大小
        ////return std::less<T>() ( a,b ) ? a : b;
        //}

        //模板函数的缺省模板参数,缺省模板参数只能放在非缺省模板参数后面
        //template<typename T, typename F=std::less<T>> T compare(const T a, const T b, F f = F())
        //{
        //    return f(a, b) ? a : b;
        //}

        //非类型模板参数，模板的参数不代表类型,而代表一个常量
        //模板参数是整型
        template<const int N> void notype0() {
            std::cout<<"notype0 N= "<<N<<std::endl;
        }

        //模板参数是整型指针
        template<const int* N> void notype1()
        {
            std::cout<<"notype1 ptr="<<N;
            std::cout<<" *N="<<*N<<std::endl;
        }

        //模板参数是函数指针
        template<void(*pfun)(int)>void notype2()
        {
            printf("notype2 fun ptr=%p\n", pfun);
            pfun(1);
        }

        //模板参数是类类型指针
        template<const std::string* S> void notype3()
        {
            std::cout<<"notype3 ptr="<<S;
            std::cout<<" *S="<<*S<<std::endl;
        }

        //模板参数是类类型左值引用
        template<const std::string& S> void notype3()
        {
            std::cout<<"notype3 ref="<<S;
            std::cout<<" *S="<<S<<std::endl;
        }

        //右值引用无法作为非类型模板参数，此处编译无法通过
        //template<std::string&& S> void notype3()
        //{
        //    std::cout<<"notype3 ref="<<S;
        //    std::cout<<" *S="<<S<<std::endl;
        //}

        //整型作为模板参数，用来表示数组的长度,由于不能拷贝数组，所以此处用的是数组的引用
        template<size_t M, size_t N> bool notype4(const char (&p1)[M], const char (&p2)[N])
        {
            std::cout<<"notype4 p1="<<p1<<" p2="<<p2<<std::endl;
            return strcmp(p1, p2);
        }


        void used_fun_temp() {
            //可以不指定类型，让编译器自动推断
            int ret=compare ( 100,200 );
            std::cout<<"fun temp litter figure is:"<<ret<<std::endl;
            // 显示的指定类型为char
            ret=compare<char> ( 'a','b' );
            std::cout<<"fun temp litter letter is:"<<ret<<std::endl;


            //非模板参数演示
            //整型常量可以作为非类型的模板参数.浮点型不可以.注意char、short、long、long long都是整型，都可以作为非类型模板参数
            notype0<5>();

            //const类型的局部变量是一个常量表达式，在编译期是知道值的
            const int f = 5;
            notype0<f>();

            //全局变量的地址可以作为非类型模板参数，因为g_i具有静态生命期，所以对它取地址是一个常量表达式，在编译期知道值
            notype1<&g_i>();
            notype1<&g_ii>();

            //局部变量的指针无法编译通过
            //int scoped_i = 200;
            //notype1<&scoped_i>();

            //无法编译通过,g_pi是一个指向全局变量的指针变量，不是一个常量表达式。即使把g_pi定义成const int*也不行
            //notype1<g_pi>();

            //该处可以编译通过。
            //但是在一个非类的成员函数(普通函数)中定义的局部静态变量作为实参调用notype1格式的模板函数(非类的成员函数)时无法编译通过(不理解)，
            //按理说s_i是一个静态局部变量，具有静态生存期，对它取地址也应该是一个常量表达式
            static int s_i = 200;
            notype1<&s_i>();
            //函数指针
            notype2<fun1>();
            //左值引用
            notype3<&g_str>();
            //数组
            notype4("hi", "world");
        }
};

////显示实例化compare函数
//extern template compare(const double a, const double b);
//template compare(const double a, const double b );


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
        //左值类型的完美转发，当要转发的函数是右值引用时不能编译通过
        template<typename F,typename T1,typename T2> void left_flips ( F f1,T1&& t1,T2&& t2 ) {
            f1 ( t2,t1 );
        }

        //右值类型的完美转发，使用标准库的std::forward<TYPE>(arg)模板保持实参的右值属性
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
            return t;
        }
        //非模板参数类型参数包格式
        template<int ...N>void foo2()
        {

        }
        void test()
        {
            foo1 ( 10,'a',"hello" );
        }

        //变长参数模板的函数实现，一般是采用递归的方式，第一步调用处理包中的第一个实参，然后用剩余实参调用自身。

        //根据模板参数的重载匹配，当最后一个递归调用到print时，参数包只有一个参数，此时该函数和下面函数的匹配度一样高，
        //但是该函数相对于可变参数模板更特例化，故选择该函数。
        template<typename T> std::ostream& print ( std::ostream& os,const T& t )
        {
            return os<<t<<std::endl;
        }

        //除最后一次调用外其它的调用完美匹配的是该可变参数模板函数，上面的print函数不匹配。
        //const Args...rest是包扩展，扩展一个包就是将它分解为构成的元素，通过在模式右边放一个省略号来触发包扩展。
        //下面的例子中对Args的扩展中，编译器将模式const Arg&应用到模板参数包Args中的每个元素，每个参数类型为const type&
        //对print的调用中rest的扩展中模式是rest，此模式扩展出一个由包中元素组成的、逗号分割的列表。
        template<typename T,typename...Args> std::ostream& print ( std::ostream& os,const T&t ,const Args&...rest )
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
            return os;
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


// 类型萃取
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
    std::remove_extent<int[10]>::type g=1;//降低数组一个维度,g为有十个整型元素的数组的元素类型int
    std::remove_all_extents<int[10][20][30]>::type g1=1;//降低数组所有维度，即数据最底层元素类型。g1为三位数组的元素类型int
    auto g2 = std::rank<int[10][20][30]>::value; //获取数组的维度，g2=3
    auto g3 = std::extent<int[10][20][30]>::value;//返回数组第一个维度的长度
    std::cout<<"g2="<<g2<<" g3="<<g3<<std::endl;
    typeid(std::remove_pointer<int*>::type).name();//int，移除指针的指针属性，一级指针变为普通类型，二级指针变为一级指针。普通类型保持原类型



    std::conditional<sizeof(int) >= sizeof(double), int, double>::type h0 = 1.1;
    std::enable_if<std::is_arithmetic<int>::value, double>::type h1 = 'a';
    std::cout<<"h1="<<h1<<std::endl;

    std::integral_constant<int, 2> h3;
    std::integral_constant<int, 4> h4;
    std::cout<<"h3="<< h3<<std::endl;
    std::cout<<"h4="<< h4<<std::endl;

    std::cout<<"int* type="<<typeid(std::remove_pointer<int*>::type).name() <<std::endl;
    std::cout<<"int  type="<<typeid(int).name() <<std::endl;


    std::string i0;
    std::cout<<"&ea is string*="<<(typeid(&i0) == typeid(std::string *))<<std::endl;
    std::cout<<"&ea is const string*="<<(typeid(&i0) == typeid(const std::string *))<<std::endl;
    std::cout<<"&ea is string* const="<<(typeid(&i0) == typeid(std::string * const))<<std::endl;
    std::cout<<std::is_const<decltype(&i0)>::value<<std::endl;
    std::cout<<std::is_reference<decltype(&i0)>::value<<std::endl;
    std::cout<<std::is_pointer<decltype(&i0)>::value<<std::endl;
    debug_rep(i0);
    debug_rep(&i0);
    std::string *i1 = &i0;
    debug_rep(i1);
    std::string * const i2 = &i0;
    debug_rep(i2);
    const std::string *i3 = &i0;
    debug_rep(i3);

    int i4 = 100;
    const int* i41 = &i4;
    const int* &i5 = i41;
    //*e5 = 200;
    std::cout<<std::is_const<const int* &>::value<<std::endl;


}


template<typename T1, typename T2, typename T3> T1 sum1(T2 first, T3 second)
{
    std::cout<<"sum1基础版本"<<std::endl;
    T1 r = first + second;
    return r;
}

template<typename T1>T1 sum1(int first, int second)
{
    std::cout<<"sum1部分特化版本1"<<std::endl;
    return first + second;
}

template<typename T1> T1 sum1(char first, char second)
{
    std::cout<<"sum1部分特化版本2"<<std::endl;
    return first + second;
}

template<typename T1> T1 sum1(int first, char second)
{
    std::cout<<"sum1部分特化版本3"<<std::endl;
    return first + second;
}

template<> int sum1(int first, int second)
{
    std::cout<<"sum1全特化版本"<<std::endl;
    return first + second;
}



template<typename T> int sum2(const T &v1, const T &v2)
{
    return 0;
}


//尾置返回迭代器解引用类型
template<typename T> auto sum3(T begin, T end)->decltype(*begin+0)
{
    std::cout<<"sum3="<<std::is_reference<decltype(*begin)>::value <<std::endl;
    std::cout<<"sum3="<<std::is_reference<decltype(*begin+0)>::value <<std::endl;
    std::cout<<"sum3="<<std::is_lvalue_reference<decltype(*begin)>::value <<std::endl;
    std::cout<<"sum3="<<std::is_lvalue_reference<decltype(*begin+0)>::value <<std::endl;
    std::cout<<"sum3="<<std::is_rvalue_reference<decltype(*begin)>::value <<std::endl;
    std::cout<<"sum3="<<std::is_rvalue_reference<decltype(*begin+0)>::value <<std::endl;
    return *begin;
}



template<typename A> A Max(A x, A y)
{
    std::cout<<"Max 基础版本"<<std::endl;
    return x > y ? x:y;
}

template<>int Max(int x, int y)
{
    std::cout<<"Max 特化版本1"<<std::endl;
    return x > y ? x:y;
}

template<typename A>int Max(unsigned int x, A y)
{
    std::cout<<"Max 特化版本2"<<std::endl;
    return x > y ? x:y;
}

template<> char Max<char>(char x, char y)
{
    std::cout<<"Max 特化版本3"<<std::endl;
    return x > y ? x:y;
}



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

//部分参数是通用类型
template<class T> void Accept(T magic1, char mime)
{
   //magic1 = extract(mime);
}

//只有通用类型参数
template<class T> void Accept(T magic, Magic1)
{
    std::cout<<"Maigc1"<<std::endl;
}
template<class T> void Accept(T magic, Magic0)
{
    std::cout<<"Magic0"<<std::endl;
}





#endif
