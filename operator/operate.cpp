#include<iostream>

class Operator
{
public:
    Operator ( int c,int d,std::string* str ) :str ( str )
    {
        a=c;
        b=d;
    }

// 拷贝赋值运算符，如果类中没有指针、引用类型的成员变量，一般不需要自己显示的定义拷贝赋值运算符，使用编译器生成的默认合成版本即可;本例
//  中假设有一个string指针类型的指针变量
    Operator& operator= ( Operator& rhs )
    {
        std::string* temp_str=new std::string ( *rhs.str );
        delete str;
        str=temp_str;
        return *this;
    }

    ~Operator()
    {
        delete str;
    }



//  括号运算符，即函数调用运算符，如果某个类被重载了该运算符，则该类可以像函数一样被调用。用这样的类定义的对象叫函数对象
    void operator() ( std::string arg1 )
    {
        std::cout<<"run operator():"<<arg1<<std::endl;
    }


// 	算术运算
    Operator operator+ ( Operator rhs )
    {
        return Operator ( a+rhs.a,b+rhs.b,str );
    }

// 	条件运算
    bool operator== ( Operator rhs )
    {
        if ( a==rhs.a && b==rhs.b && *str==*rhs.str )
            return true;
        return false;
    }


    bool operator> ( Operator rhs )
    {
        if ( a>rhs.a && b>rhs.b && *str>*rhs.str )
            return true;
        return false;
    }

// 	前++
    Operator& operator++ ( void )
    {
        ++a;
        ++b;
        ++str;
        return *this;
    }

// 	后++
    Operator operator++ ( int )
    {
        Operator before_add=*this;
        ++ ( *this ); //因为重载了前++,所以这里可以直接使用
        return before_add;
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
