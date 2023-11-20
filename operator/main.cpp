#include<iostream>
#include"operate.hpp"
int main(int argc, char* argv[])
{
    // 运算符重载
    std::cout<<"------------运算符重载---------------"<<std::endl;
    Operator op0(1, 2, std::string("67890"));
    op0.operator() ("operator");
    op0("省略 operator(),可以像函数一样被调用，此类属于仿函数");

    Operator op1(3, 4, "12345");
    op1 = op0;//重载的赋值运算符函数中深拷贝了op0的str内容,不会出现double free
    std::cout << "op1=" << op1<< std::endl;

    op1 += op0;

    op1[0] = '0';
    op1[1] = '1';
    std::cout << "op1="<< op1 << std::endl;
    op1++;
    std::cout << "op1="<< op1 << std::endl;

    //类型转换，op1类型定义了转换成int的运算符，所以可以直接赋值给int型变量
    int i0 = op1;
    //i0 += op1;
    i0 += static_cast<int>(op1);//此处如果不显示转换则编译失败，因为Opearator同时重载了向int double的转换符，而int又可以隐式转换成double，所以不知道选择那个转换了
    std::cout << "i0=" << i0 << std::endl;

    double i1 = op1;
    //i1 += op1;
    i1 += static_cast<double>(op1);
    std::cout << "i1=" << i1 << std::endl;

    //类型转换，op1类型定义了转换成std::string的运算符，但是该函数是explicit，所以必须static_cast显示的转换才可以
    std::string str0 = static_cast<std::string>(op1);
    str0 += static_cast<std::string>(op1);
    std::cout << "str0=" << str0 << std::endl;

    //在条件语句中如果定义了bool转换，即使申明的是显示的，也可以隐式发生转换
    if(!op1)
        std::cout << "con op1=" << op1 << std::endl;


    //解引用，建议不要重载解引用和->操作符，否则当和内置指针混在一起时会写出难以理解的代码
    //类自己重载的解引用操作符针对的目标是类类型对象
    //重载的解引用毕竟是类的一个函数，需要遵守函数调用规则
    std::cout << "*op1=" << *op1 << std::endl;
    std::cout << "op1->size()=" << op1.operator->()->size() << std::endl;
    std::cout << "op1->size()=" << op1->size() << std::endl;//等价上面那句
    std::cout << "op1->c_str()=" << op1.operator->()->c_str() << std::endl;//等价上面那句
    std::cout << "op1->c_str()=" << op1->c_str() << std::endl;


    Operator* op7 = &op1;
    std::cout << "*op7=" << *op7 << std::endl;//注意此句不会调用Operator重载的解引用操作符，op7是一个内置指针，*op7是解引用指针，遵守内置指针解引用的规则，解引用后得到一个Operator类型的对象
    std::cout << "*op7=" << **op7 << std::endl;//此句才会调用Operator重载的解引用操作符，先对op7解引用得到一个Operaotr类型的对象，再该对象再解引用才会调用Operator自己重载的解引用操作符
    std::cout << "*op7=" << op7->operator*() << std::endl;//等价上面那句
    std::cout << "*op7=" << op7->operator->()->c_str() << std::endl;

    std::cout << "-------------------------" << std::endl;

    //new
    {
        //new操作符重载
        Operator* op2 = new Operator(op1); //Opeartor类重载了new操作符,故该句会使用Operator的重载版本
        std::cout << "op2.a=" << op2->get_a() << std::endl;
        Operator* op3 = new(std::nothrow) Operator(op1);//Opeartor类重载了new操作符的nothrow版本,故该句会使用Operator的重载版本
        std::cout << "op3.a=" << op3->get_a() << std::endl;
        //Opeartor类重载了new操作符的多参数版本,故该句会使用Operator的多参数版本,由于Operaotr的多参数版本是返回参数本身,则此处的op4用的是op3的内存
        //所以修改了op4->a的值后,op3->a的值也改变了
        Operator* op4 = new(op3, 1, 2) Operator(op0);
        std::cout << "op3.a=" << op3->get_a() << std::endl;
        std::cout << "op4.a=" << op4->get_a() << std::endl;

        Operator* op5 = ::new Operator(op1);//虽然Opeartor类重载了new操作符的多参数版本,但是此处使用显示的全局版本(::new),故该句不会使用Operator的重载版本

        //把new运算符分开来操作
        void* temp = Operator::operator new(sizeof(Operator));//仅分配内存
        //void* temp = ::operator new(sizeof(Operator));//仅分配内存时也可以使用全局版本
        Operator* op6 = new(temp, 1, 1)Operator(op1);//使用重载的多参数版本来使用temp并初始化op7

        delete op2;
        //op3和op4只能delete一个,因为他们共用一块内存
        delete op3;
        //delete op4;
        delete op5;
        delete op6;
    }
    std::cout << "after new operator" << std::endl;

    return 0;
}
