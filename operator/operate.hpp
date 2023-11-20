#include<iostream>
//1.对一个运算符来说，它或者是类的成员函数，户这至少含有一个类类型的参数。不能为内置类型重载运算符
//2.重载的运算符优先级和结合律与对应的内置运算符保持一致
//3.以下运算符不能被重载
// :: .* . ?:
//4.以下运算符符虽然可以被重载，但是不应该被重载
//  逗号运算符 逻辑与 逻辑或
//  取址运算符不应该被重载。因为逗号运算符 逻辑与 逻辑或运算符的求知顺序无法被保留下来，且逻辑与或的短路特性也无法被保留下来，所有一般不应该重载
//  取址运算符已经有了内置含义，故一般不应该重载
//5.重载的运算符可以是类的成员函数也可以是普通非成员函数
//      赋值、下标、调用、箭头访问运算符必须成员函数
//  最好使用成员函数的运算符：
//      1.符合赋值运算符
//      2.改变对象状态或者与给定类型密切相关的运算符，例如递减、解引用
//  最好使用非成员的运算符：
//      1.具有对称性的运算符可能转换任意一端的运算对象，例如算术、相等性、关系、位运算
//  如果想提供含有类对象的混合类型表达式，则运算符必须定义成非成员函数
//6.重载的->运算符必须返回类的指针或者自定义了箭头运算符的某个类类型对象，返回其它都失败
//7.类型转换运算符，当类显示或隐式转换成某中类型时，类型转换运算符函数会被调用。
//  类型转换运算符无显示的返回类型、无形参且必须定义成成员函数，类型转换通常不应该改变转换对象，所以一般定义成const成员。一般情况下
//  只有类类型和转换类型之间存在明显的映射关系时，使用类型转换运算符是比较合适的。有时候隐式的向某个类型转换可能会造成误解，此时可以把想某种类型的类型
//  转换运算符声明为显示的。

//类的new/delete运算符也是可以重载的。在类中的operator new默认就是static.所以加static可以,不加也是全局,可以正常使用
//new关键字有两种:
//    1. std::new 标准库版本
//    2. ::new  全局版本
//  注意std::new和::new是关键字,和operator new不是一回事,只是他们会调用operaotr new而已。
//new A 语句等价于如下两个过程:
//  1.分配内存, 此过程会调用类A重载函数operator new
//  2.调用类型A的构造函数
//operator new也有全局版本和类重载版本
//  1.类内重载版本
//  2.全局重载版本
//  3.全局默认版本
// operator new有三种形式:
//      throwing	void* operator new (std::size_t size) throw (std::bad_alloc);
//      nothrow     void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw();
//      placement   void* operator new (std::size_t size, void* ptr) throw();
//其中throwing版本的operator new分配内存失败时会抛异常,而nothrow版本则不会
//operator new是如何配合new运算符完成分配内存工作的呢?
//以new A();语句为例,new运算符中会调用operator new来分配内存,当A类重载了new,则调用A中重载的这个版本,如果类A没有重载则查看是否有
//全局重载版本,如果有全局重载版本则使用全局重载版本,如果没有全局重载版本则使用全局默认版本.
//这里的重载也遵循作用域覆盖规则,即从内部作用域向外部搜索,如果找到则不再继续向外搜索,如果参数符合则通过,如果不符合则报错,即使外部有参数符合的版本也不会再搜索.

//注意:有一个特殊场景, 直接使用::new运算符会直接使用全局作用域的重载new,而不从类内开始搜索.


//同理,delete也是可以重载的。只是有一点需要注意的是:自定义参数版本的delete不能手动调用
//也就是说new支持如下三种:
//  A* = new A
//  A* = new(std::nothrow)A
//  A* = new(pointer)A
//但是delete只支持一种:
// delete A*

class Operator
{
public:
    //此处不要默认构造函数，因为类持有指针成员，当用无参方式构造时，指针成员值未定义，对下面的拷贝构造、拷贝赋值、符合拷贝运算都是灾难
    //Operator()
    //{

    //}

    Operator(int a, int b, std::string str):a(a), b(b), str(new std::string(str))
    {
    }

    Operator(const Operator& v):a(v.a), b(v.b), str(new std::string(*v.str))
    {
        std::cout << "copy constructor" << std::endl;
    }

    //拷贝赋值运算符，如果类中没有指针、引用类型的成员变量，一般不需要自己显示的定义拷贝赋值运算符，使用编译器生成的默认合成版本即可;本例
    //中假设有一个string指针类型的指针变量。赋值运算符必须定义为成员函数
    Operator& operator=(const Operator& rhs)
    {
        std::cout << "copy assign" << std::endl;
        if(this == &rhs)
            return *this;

        a = rhs.a;
        b = rhs.b;
        std::string* temp_str = new std::string ( *rhs.str );
        delete str;
        str = temp_str;
        return *this;
    }

    ~Operator()
    {
        std::cout << __FUNCTION__ << std::endl;
        delete str;
    }

    //括号运算符，即函数调用运算符，如果某个类被重载了该运算符，则该类可以像函数一样被调用。用这样的类定义的对象叫函数对象(仿函数)
    void operator()(std::string arg1)
    {
        std::cout << "operator ()" << arg1 << std::endl;
    }

    //算术运算，算术运算符一般不需要改变运算对象的状态，所以形参可以是const
    Operator operator+(const Operator& rhs)
    {
        return Operator(a + rhs.a, b + rhs.b, *str + *rhs.str);
    }

    //复合赋值运算符，符合赋值运算符可以是成员函数也可以是普通函数，不过一般定义为成员函数。
    //为和与内置类型符合赋值运算符一致，复合赋值运算符也返回左侧运算对象的引用。
    //也可以把该函数委托给上面的+运算符和=运算符一起来实现，但是使用委托的话会有多余的拷贝操作
    Operator& operator+=(const Operator& rhs)
    {
        //实现一
        a += rhs.a;
        b += rhs.b;

        std::string* temp = new std::string(*str);
        *temp += *rhs.str;
        delete str;
        str = temp;

        return *this;

        //实现二 依赖于 + 、= 两个运算符重载的实现
        //*this = *this + rhs;
        //return *this;

        //实现三 使用std::string的+=操作且会自动扩展内存,不用释放左侧对象内存，复用左侧对象内存
        //a += rhs.a;
        //b += rhs.b;
        //*str += *rhs.str;
        //return *this;
    }

    //条件运算,条件运算符一般不需要改变运算对象的状态，所以形参可以是const
    bool operator==(const Operator& rhs)
    {
        return  a == rhs.a && b == rhs.b && *str == *rhs.str ;
    }

    //该函数可以委托==运算符来实现，因为上面已经实现了==运算符
    bool operator!=(const Operator& rhs)
    {
        return !(*this == rhs);
    }


    bool operator>(Operator rhs)
    {
        return a > rhs.a && b > rhs.b && *str > *rhs.str;
    }

    //前++
    Operator& operator++()
    {
        ++a;
        ++b;
        return *this;
    }

    //后++，后++的重载函数接受一个int型参数，当非显示调用该函数时编译器给该参数提供一个0的实参。该参数不被使用，仅仅用于区分前置还是后置。
    //但是当显示调用该函数时，实参需要调用这自己提供，且必能省略
    Operator operator++(int)
    {
        Operator before_add = *this;
        ++(*this); //因为重载了前++,所以这里可以直接使用
        return before_add;
    }

    //重载下标运算符时最好重载一个常量版本和一个非常常量版本
    //此处重载的下标运算符取字符串的字符
    char& operator[](std::size_t index)
    {
        return (*str)[index];
    }

    const char& operator[](std::size_t index) const
    {
        return (*str)[index];
    }

    //解引用得到的是一个引用，所以返回值必须是引用，同理->运算符也必须是引用或者指针
    std::string& operator*() const
    {
        return *str;
    }

    //重载的->运算符必须返回类的指针或者自定义了箭头运算符的某个类类型对象，返回其它都失败
    std::string* operator->() const
    {
        //return str;
        //return &this->operator*();
        return  &*(*this);//注句不等价于 return (*this); 因为*this是对指针(内置)解引用的到Opeartor这个对象，*(*this)是对Operator对象解引用，调用的是上面的operator*函数，再&是对str字符串取址，不是对Operator对象取址
    }

    //类型转换运算符，转换成int
    operator int()const
    {
        return a;
    }

    //类型转换运算符，转换成double
    operator double()const
    {
        return 1.1;
    }

    //该类向char类型转换时只能显示指定,不能隐式发生。但是当表达式被用作条件时，会隐式发生
    explicit  operator std::string()const
    {
        return *str;
    }

    explicit operator bool()const
    {
        return a == b;
    }


    //输入输出运算符必须定义成非成员函数的形式，否则使用时左侧运算对象将是我们的类对象，与标准库的不一致
    friend std::istream& operator>>(std::istream& is, Operator& op);

    //输入运算符因为改变了对象，所以还要处理输入过程中发生的错误，以保证能从错误中恢复
    friend std::ostream& operator<<(std::ostream& os, const Operator& op);

    //void* operator new(size_t s)throw(std::bad_alloc)也可以写成这样
    void* operator new(size_t s)
    {
        std::cout << "operator new" << std::endl;
        return malloc(s);
    }

    void* operator new(size_t s, const std::nothrow_t& value)throw()
    {
        std::cout << "operator new nothrow" << std::endl;
        return malloc(s);
    }

    void* operator new(size_t s, void* ptr, int x, int y)
    {
        std::cout << "operator new more args" << std::endl;
        return ptr;
    }

    void operator delete(void* ptr)
    {
        std::cout << "operator delete" << std::endl;
        free(ptr);
    }

    void operator delete(void* ptr, const std::nothrow_t& value)throw()
    {
        std::cout << "operator delete nothrow" << std::endl;
        free(ptr);
    }

    void operator delete(void* ptr, int x, int y)
    {
        std::cout << "operator delete args" << std::endl;
        free(ptr);
    }

    std::string* get_str()
    {
        return str;
    }

    int get_a()
    {
        return a;
    }

    int get_b()
    {
        return b;
    }

private:
    int a;
    int b;
    std::string* str;
};

std::istream& operator>>(std::istream& is, Operator& op)
{
    is >> op.a;
    is >> op.b;
    is >> *op.str;
    return  is;
}

std::ostream& operator<<(std::ostream& os, const Operator& op)
{
    os << op.a << " " << op.b << " " << *op.str;
    return os;
}
