#include"function.hpp"
int main()
{
    // 	函数对象和绑定
    std::cout<<"--------------函数对象和绑定-------------"<<std::endl;
    PrintString Ps;
    Ps.run();

    My_Bind my_bind;
    my_bind.run();
    my_bind();
    int value1=100,value2=200;
    auto new_fun1=bind ( My_Bind::static_number,value1,value2,std::placeholders::_1 );
    new_fun1 ( 300 );
    auto new_fun2=bind ( &My_Bind::no_static_number,my_bind,value1,std::placeholders::_1,value2 );
    new_fun2 ( 400 );
    return 0;
}
