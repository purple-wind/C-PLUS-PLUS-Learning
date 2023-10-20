#include<iostream>
#include<time.h>
#include<chrono>
using namespace std;

//常量表达式:值不会改变且在编译过程就能得到计算结果的表达式
//  1.字面值是常量表达式
//  2.常量表达式初始化的const对象也是常量表达式
//  3.字面值常量类常用于生成constexpr对象以及constexpr函数的参数或返回值
void const_expression()
{
    const int max_files = 20;
    const int limit = max_files + 1;
    int staff_size = 27;
    2;
    int x = 0, y = 0;
    (2>0?x:y) = 3;
    cout<<"x="<<x<<" y="<<y<<endl;
}


//constexpr 变量
//c++11起，可以把一个变量申明为constexpr类型，以便编译器来验证变量值是否是一个常量表达式。申明为constexpr的变量一定是
//一个常量，且必须用常量表达式初始化
int g_mf = 1;
void constexpr_variable()
{
    constexpr int mf = 20;
    constexpr int limit = mf + 1;

    //constexpr修饰指针时，constexpr仅对指针本身有效，与指针所指的对象无关
    constexpr int *p0 = nullptr;//p0指向常量
    //constexpr int *p1 = &mf;
    constexpr int *p2 = &g_mf;//p2指向常量，仅仅需要保证g_mf的地址是一个常量即可，而不关注g_mf是否是常量。此处g_mf是一个全局变量，所以它的地址是一个常量，故此可以用constexpr修饰
}


//constexpr函数是指能用于常量表达式的函数。c++11对constexpr的限制如下:
// 1.constexpr函数的返回类型及所有形参的类型都的是字面值类型
// 2.函数体中只能有return这一条有效语句，不能有其它任何有效语句，但是可以有不执行任何操作的语句，比如空语句、类型别名即using申明语句
//注意:定义为constexpr的函数不一定返回常量表达式。当函数的参数是常量表达式时则返回值也是常量表达式，反之则不是。
//也就是说上面2条限制知识最基本的限制,满足以上2个条件未必可以用作常量表达式,满足上面2条限制却也可以用作非常量表达式。
//比如下面对constexpr_fun的使用就无法通过编译(场景1)
//        int c0 = 1;
//        constexpr c1 = constexpr_fun(c0);

//只有如下代码才可编译通过(场景2)
//        constexpr int c0 = 1;
//        constexpr c1 = constexpr_fun(c0);

//或者这样也可编译通过(场景3)
//        int c0 = 1;
//        c1 = constexpr_fun(c0);


constexpr int constexpr_fun(int a)
{
    //int x = 0;//如果函数体内存在此语句，则编译无法通过
    return a;//函数体内只能有return这一条语句
}


//实测使用了constexpr版本的函数反而性能更差，和预期不一致
//在这个函数里面，由于constexpr申明的是fib1这个函数，因此每一次计算都是在编译期执行，且计算结果都会作为一个常量保存下来
//这个实现的复杂度等同于迭代的方法，基本上为O(n)，因为计算工作都在编译期做了，运行时这里就是一个常量，没有运算工作量
constexpr long int fib1(int n)
{
    return (n <= 1)? n : fib1(n-1) + fib1(n-2); //只能包含一个retrun语句
}
//下面这个函数的时间复杂度为O(2^n)
long int fib2(int n)
{
    return (n <= 1)? n : fib2(n-1) + fib2(n-2);
}




//聚合类
//满足以下条件的类是聚合类：
//    1.所有成员都是public,仅仅限制成员变量，不限制成员函数，即使有私有成员函数也是聚合类
//    2.没有定义任何构造函数
//    3.没有类内初始值(使用c++17的is_aggregate<T>验证即是指定了类内初始值依然是聚合类,可能17标准放宽)
//    4.没有基类也没有virtual函数，基类的限制在c++17下验证已经方宽，当公有继承了基类也是聚合类，保护和私有继承不是聚合类
class AggregateClass0
{
    public:
        char a0 = 'a';// 使用c++17的is_aggregate<T>验证即是指定了类内初始值依然是聚合类
        int a1 = 1;
        double a2 = 2.2;
        string a3 = "012345";
        void fun012(){}
};

class AggregateClass1
{
    public:
        char a0 = 'a';// 使用c++17的is_aggregate<T>验证即是指定了类内初始值依然是聚合类
        int a1 = 1;
        double a2 = 2.2;
        string a3 = "012345";
    private:
        void fun012(){} //即使有私有成员函数也是聚合类
};

class AggregateClass2
{
    public:
        char a0 = 'a';// 使用c++17的is_aggregate<T>验证即是指定了类内初始值依然是聚合类
        int a1 = 1;
        double a2 = 2.2;
        void fun012(){}
    private:
        string a3 = "012345";//包含了私有成员变量，故该类不是聚合类
};

class AggregateClass3
{
    public:
        AggregateClass3(){}//包含构造函数，故该类不是聚合类
        char a0 = 'a';// 使用c++17的is_aggregate<T>验证即是指定了类内初始值依然是聚合类
        int a1 = 1;
        double a2 = 2.2;
        void fun012(){}
};

class AggregateClass4
{
    public:
        char a0 = 'a';// 使用c++17的is_aggregate<T>验证即是指定了类内初始值依然是聚合类
        int a1 = 1;
        double a2 = 2.2;
        virtual void fun012(){}//包含了虚函数，故该类不是聚合类
};

//继承了其它类，故该类不是聚合类
class AggregateClass5:public string
{
    public:
        char a0 = 'a';// 使用c++17的is_aggregate<T>验证即是指定了类内初始值依然是聚合类
        int a1 = 1;
        double a2 = 2.2;
};



//字面值常量类:
// 1.如果一个聚合类所有数据成员都是字面值类型，则该类就是字面值常量类
// 2.如果一个类不是聚合类但是满足以下条件则也是字面值常量类：
    //2.1 数据成员都必须是字面值类型
    //2.2 类必须至少含有一个constexpr构造函数
    //2.3 如果一个数据成员含有类内初始值，则内置类型成员的初始值必须是一条常量表达式；或者如果
    //    成员属于某种类类型，则初始值必须使用成员自己的constexpr构造函数
    //2.4 类必须使用析构函数的默认定义，该成员负责销毁类的对象

//所有成员都是字面值类型的聚合类是字面值常量类
class LiteralConstClass1
{
    public:
        char a = 'a';
        int b = 1;
        double c = 1.1;
        void fun0123(){}
};

class LiteralConstClass2
{
    public:
        char a = 'a';
        int b = 0;
        double c = 1.1;
        string d = "123"; //d不是字面值类型，故该类不是字面值常量类
        void fun0123(){}
};


//非聚合类的字面值常量类
class LiteralConstClass3
{
    public:
        constexpr LiteralConstClass3(){} //条件2.2
        ~LiteralConstClass3() = default; //条件2.4
        char a = 'a';//条件2.1
        int b = 0;
        double c = 1.1;
        void fun0123(){}
};

class LiteralConstClass4
{
    public:
        LiteralConstClass4(){} //条件2.2不满足故不是字面值常量类
        ~LiteralConstClass4() = default; //条件2.4
        char a = 'a';//条件2.1
        int b = 0;
        double c = 1.1;
        void fun0123(){}
};

class LiteralConstClass5
{
    public:
        constexpr LiteralConstClass5(){} //条件2.2
        ~LiteralConstClass5(){} //条件2.4不满足故不是字面值常量类
        char a = 'a';//条件2.1
        int b = 0;
        double c = 1.1;
        void fun0123(){}
};

//class LiteralConstClass6
//{
//    public:
//        constexpr LiteralConstClass6(){} //编译无法通过，因为在构造函数构造e时无法构造
//        ~LiteralConstClass6() = default; //条件2.4
//        char a = 'a';//条件2.1
//        int b = 0;
//        double c = 1.1;
//        string e = "0123";//e不是字面值类型，条件2.1不满足故不是字面值常量类
//        void fun0123(){}
//};


class LiteralConstClass6
{
    public:
        LiteralConstClass6(){}
        ~LiteralConstClass6() = default; //条件2.4
        char a = 'a';//条件2.1
        int b = 0;
        double c = 1.1;
        string e = "0123";//e不是字面值类型，条件2.1不满足故不是字面值常量类
        void fun0123(){}
};

struct LiteralA{
    char a;
    int b;
    double c;
};


//constexpr构造函数用于生成constexpr对象以及constexpr函数的参数或返回值
class LiteralConstClass7
{
    public:
        constexpr LiteralConstClass7(){} //必须列表初始化或者类内初始化，根据constexpr函数的限制函数体内不能写语句
        ~LiteralConstClass7() = default; //条件2.4
        char a = 'a';//条件2.1
        int b = 0;
        double c = 1.1;
        LiteralA e{'a', 1, 2.2};//e是字面值类型，条件2.1
        void fun0123(){}
};

#include<vector>
class LiteralConstClass11
{
    public:
        char a;
        int b;
        double c;
        void fun0123(){}
};

//类的constexpr静态成员变量
//1.constexpr的静态成员变量必须在类内初始化,不能在类内申明类外定义
//2.类内初始化只能是列表初始化方式，不能是其他方式，故类型要遵守列表初始化的限制
//3.constexpr的静态成员变量类型支持整型、 浮点型、数组、字面值类型
// 注意支持数组时下标必须是编译期常量
//    支持多维数组但是在使用时只能取最底层维度的值，高维度值无法取
//    例如 int arr[2][3] = {{1,2,3},{4,5,6}}在定义类可以正常定义，
//    但是使用时只能使用 arr[0][1] arr[1][1]这样的最底层维度，但是使用arr[0] arr[1]这样的高维度就无法编译通过
//  为什么是这样呢？因为constexpr申明的是编译期常量，并不会定义这个对象。在编译的时候用到constexpr申明的对象时直接用它的内容去替换，
//  所以如果在使用时如果使用了访问此类对象的语句，编译时直接报未定义。因为不存在这样的对象，又如何访问得了。
//  数组的非常量标取数组元素、多维数组未访问最底层元素、一维数组数组名等都是访问此类对象，所以会报此对象未定义
//4. 在类内成员变量只有静态的时候才可以申明成constexpr否则编译失败
//5. 要在类内初始化非整型的静态成员变量，必须是constexpr

//6.static const constexpr等修饰对类内初始化的影响
//    1.非静态成员变量，不管是什么类型都可以在类内初始化
//    2.静态成员变量则必须是const属性，且类型必须是整型，如果不想是整型，则要用constexpr修饰，此时可以把类型放宽到字面值类型

// 注意：以上讨论仅限于c++11,可能更高的标准放宽条件
class ConstexprStaticMemberClass
{
    public:
        static constexpr int d0 = 1;
        static constexpr double d1 = 2;
        //constexpr int d3 = 1; //d3不是静态成员变量，所以c++11下编译失败
        static constexpr  char* arr0[4] = {"123", "456"}; //constexpr的静态成员变量必须在类内初始化,不能在类内申明类外定义,数组使用时下标必须是编译期常量
        static constexpr  int arr1[2][3] = {{1, 2, 3}, {4, 5, 6}}; //constexpr的静态成员变量必须在类内初始化,不能在类内申明类外定义。数组使用时下标必须是编译期常量
        //static constexpr LiteralConstClass1 d1 = {'1', 2, 3.3};//LiteralConstClass1有类内初始值，无法满足列表初始化条件，c++11下编译失败
        static constexpr LiteralConstClass11 c0 = {'1', 2, 3.3};//LiteralConstClass11无类内初始化，满足列表初始化条件，编译成功
        //static constexpr std::vector<int> vec0 = {1,2,3};//vector不是字面值类型，c++11下编译失败


        //下面讨论static const constexpr对类型的要求
        const std::vector<int> vec1 = {1,2,3};//vector不是字面值类型，但是也不是静态成员变量，编译成功
        //static LiteralConstClass11 c1 = {'1', 2, 3.3};//vector是字面值类型，但是是静态成员变量，静态成员变量要想在类内初始化必须是整型类型，c++11下编译失败
        //static int d4 = 1;//非cosnt的静态变量不能在类内初始化，不管变量是什么类型满足什么条件都不行，c++11下编译失败
        int d8 = 1;
        const int d7 = 1;//非静态成员变量，不管是什么类型都可以在类内初始化，但是如果是静态成员变量则必须是const属性，且类型必须是整型
        static const int d5 = 1;//整型的const静态变量可以在类内初始化
        //static const double d6 = 1.1;//非整型的const静态变量不可以在类内初始化，要想在类内初始化则把const改成constexpr，c++11下编译失败
};
