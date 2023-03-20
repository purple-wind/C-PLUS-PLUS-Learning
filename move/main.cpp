#include<utility>
#include<iostream>
#include<string.h>
#include<type_traits>
using namespace std;
// std::move()，标准库使用模板类型推断和引用折叠这一特性的经典例子，由于模板类型推断和引用折叠的特性，
// my_move既可以接受左值实参，也可以接受由值实参，都能表现出正确的行为。只是接受右值实参的时候my_move什么都不做而已。
template<typename T> typename std::remove_reference<T>::type&& my_move ( T&& t )
{
    return static_cast<typename std::remove_reference<T>::type&&> ( t );//将一个左值转换成一个右值引用，此时左值被截断。
}


class E
{
    public:
        E(){
            cout<<"gerenal constructor"<<endl;
        }
        E(const E& e)
        {
            cout<<"copy"<<endl;
        }
        E(E&& e)
        {
            cout<<"move"<<endl;
            cout<<"e="<<&e<<endl;
            a = e.a;
        }
        E& operator=(const E& e)
        {
            cout<<"assign copy"<<endl;
        }
        E& operator=(E&& e)
        {
            cout<<"assign move"<<endl;

        }
        ~E()
        {
            cout<<"~"<<endl;
        }

        int a = 100;
};

//返回左值,函数内部临时对象移动构造初始化返回值。当返回值类型为左值类型时，
//局部临时变量会在自己析构之前调用移动构造函数把值移动给返回值
E test()
{
    return E();
}

//此处是错误的，不要试图通过返回右值引用来延长局部对象的生存周期。声明函数返回
//值为右值引用无法延长对象的生命周期。此处局部临时变量直接析构，
//并不会在自己析构之前调用移动构造函数把值移动给返回值。所以此时在调用该函数的
//栈上的右值引用引用的是一个不存在的对象。运气好的话程序coredump，运气差的话
//看起来正常
E&& test1()
{
    return E();
}

void test_return_lrvalue()
{
    test();//1次移动构造
    cout<<"-----------------"<<endl;
    E e1(test());//2次移动构造
    cout<<"-----------------"<<endl;
    E e2 = test();//同上
    cout<<"e2.a="<<e2.a<<endl;
    cout<<"-----------------"<<endl;
    E e3;
    e3 = test();//1次移动构造，1次移动赋值
    cout<<"-----------------"<<endl;
    E e4 = test1();//错误,test1内部临时变量被栈上的返回值引用,因为此时内部临时变量已经析构了,所以栈上的作为返回值的引用引用的是该析构对象，
                   //然后该返回值移动构造e4时段错误
    cout<<"-----------------"<<endl;

    //输出如下:
    //gerenal constructor
    //move
    //e=0x7fff45d91eb4
    //~
    //~
    //-----------------
    //gerenal constructor
    //move
    //e=0x7fff45d91eb4
    //~
    //move
    //e=0x7fff45d91ef4
    //~
    //-----------------
    //gerenal constructor
    //move
    //e=0x7fff45d91eb4
    //~
    //move
    //e=0x7fff45d91ef4
    //~
    //e2.a=100
    //-----------------
    //gerenal constructor
    //gerenal constructor
    //move
    //e=0x7fff45d91eb4
    //~
    //assign move
    //~
    //-----------------
    //gerenal constructor
    //~
    //move
    //e=0
    //Segmentation fault (core dumped)
}

template<typename T> struct XYZ {
        XYZ(){std::cout<<"T"<<std::endl;}
        typedef T type;
        T b;
};

template<typename T> struct XYZ<T&> {
        XYZ(){std::cout<<"T&"<<std::endl;}
        typedef T type;
        T a;
};

template<typename T> struct XYZ<T&&> {
        XYZ(){std::cout<<"T&&"<<std::endl;}
        typedef T type;
        T c;
};

void test_type_diff()
{
    typedef int I;
    std::cout<<"typedef:" << (typeid(int) == typeid(I))<<std::endl;
    std::cout<<"int& == int:" << (typeid(int&) == typeid(int))<<std::endl;
    XYZ<int>::type t0;
    std::cout<<"typeid(t0) == typeid(int):"<<(typeid(t0) == typeid(int))<<std::endl;
    XYZ<int&>::type t1;
    std::cout<<"typeid(t1) == typeid(int):"<<(typeid(t1) == typeid(int))<<std::endl;
    XYZ<int&&>::type t2;
    std::cout<<"typeid(t2) == typeid(int):"<<(typeid(t2) == typeid(int))<<std::endl;


    XYZ<int> xyz0;
    xyz0.b = 0;
    std::cout<<"xyz1.b="<<xyz0.b<<std::endl;
    XYZ<int&> xyz1;
    xyz1.a = 1;
    std::cout<<"xyz1.a="<<xyz1.a<<std::endl;
    XYZ<int&&> xyz2;
    xyz2.c = 2;
    std::cout<<"xyz2.c="<<xyz2.c<<std::endl;
}


template<typename T> void lvalue(T& a)
{
    cout<<"T is_lvalue_reference:"<<is_lvalue_reference<T>::value<<endl;
    cout<<"T is_rvalue_reference:"<<is_rvalue_reference<T>::value<<endl;
    cout<<"a is_lvalue_reference:"<<is_lvalue_reference<decltype(a)>::value<<endl;
    cout<<"a is_rvalue_reference:"<<is_rvalue_reference<decltype(a)>::value<<endl;
}

template<typename T> void rvalue(T&& a)
{
    cout<<"T is_lvalue_reference:"<<is_lvalue_reference<T>::value<<endl;
    cout<<"T is_rvalue_reference:"<<is_rvalue_reference<T>::value<<endl;
    cout<<"a is_lvalue_reference:"<<is_lvalue_reference<decltype(a)>::value<<endl;
    cout<<"a is_rvalue_reference:"<<is_rvalue_reference<decltype(a)>::value<<endl;
}

void test_lrvalue()
{
    int && a = 10;//右值引用　引用　右值，不可以引用左值。猜测右值引用在定义的时候必定绑定了一块内存
    std::cout<<"a="<<a<<std::endl;
    int a1 = a;//值传递a把值拷贝给了a1，此后两者无关联,此时a1=10;a=10
    std::cout<<"a="<<a<<" a1="<<a1<<std::endl;
    a1++;//此时a1=11， a=10,可见二者无任何关系
    std::cout<<"a="<<a<<" a1="<<a1<<std::endl;
    int &b = a;//左值引用可以　引用　右值引用类型的变量； 右值引用本身是一个左值，可以用一个左值引用去引用，此时b和a是同一个东西。
    a = 20; //此时a b都是20
    std::cout<<"b="<<b<<" a="<<a<<std::endl;
    b += 1; //此时a b都是21
    std::cout<<"a="<<a<<" b="<<b<<std::endl;

    //int&& b1=a;//错误，右值引用无法　引用　变量，即使这个变量是右值类型的引用。右值引用具有左值属性，是一个左值
    //std::cout<<"b1="<<b1<<std::endl;
    int i = 100;
    a = i; //此时把左值i赋值给a是可以的，由此可见右值引用在定义的时候必定绑定了一块内存。a是这块内存的一个标签，此后对a的操作就是对该
           //内存的操作，故右值引用也是左值。a仅仅在定义的时候无法绑定到左值上。
    std::cout<<"a="<<a<<" b="<<b<<std::endl;
    //使用了move表示把i当做右值让c引用，此后i的值是未定义的，只能对ｉ进行赋值或释放，不能使用i的值。
    //事实上根据实验得知，如果是内置类型，i和c是同一个东西，更改任意一个另一个也会跟着一起变。
    //如果i是类类型，则表现的行为取决于类的移动构造函数的行为。所以上面那句约束依旧成立
    int && c = std::move(i);
    std::cout<<"c="<<c<<std::endl;
    i++;
    std::cout<<i<<std::endl;

    int r0 = 1;
    int& r1 = r0;
    r1 = 200;
    cout<<"r0="<<r0<<" r1="<<r1<<endl;

    int&& r2 = 2;
    r2 = 3;
    std::cout<<"r2="<<r2<<endl;

    int && r3 = move(r0);
    //int&& r3 = static_cast<int&&>(r0);
    //int && r3 = move(0);
    cout<<"r3="<<r3<<" r0="<<r0<<endl;
    r3 = 300;
    cout<<"r3="<<r3<<" r0="<<r1<<endl;
    int & r7 = r3;
    cout<<"r7="<<r7<<" r3="<<r3<<" r0="<<r0<<endl;
    r7 = 400;
    cout<<"r7="<<r7<<" r3="<<r3<<" r0="<<r0<<endl;

    lvalue(r0);
    lvalue(r1);
    lvalue(r2);
    cout<<"---------------------"<<endl;
    rvalue(r0);
    rvalue(r1);
    rvalue(r2);
    rvalue(3);
}

int main()
{
    test_type_diff();
    test_lrvalue();
    test_return_lrvalue();
    std::cout<<std::is_reference<int(*)[3]>::value<<std::endl;//数组的指针
    std::cout<<std::is_reference<int(&)[3]>::value<<std::endl;//数组的引用
    std::cout<<std::is_reference<int&>::value<<std::endl;
    return 0;
}
