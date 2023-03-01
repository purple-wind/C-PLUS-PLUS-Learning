#include<iostream>
#include"operate.hpp"
int main()
{
    // 运算符重载
    std::cout<<"运算符重载"<<std::endl;
    std::string* str = new std::string ( "67890" );
    Operator op ( 1,2,str );
    op.operator() ( "operator 被调用" );
    op ( "省略 operator(),可以像函数一样被调用" );
    std::string* str1 = new std::string ( "12345" );
    Operator op2 ( 1,2,str1 );
    op2 = op;
    std::cout<<*op2.get_str() <<std::endl;
    delete str;
    return 0;
}
