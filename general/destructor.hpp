#include<iostream>
struct A
{
    public:
        ~A()
        {
            std::cout<<"delete A,a="<<a<<std::endl;
        }
    int a = 0;
};

class DelArray{
    public:
        DelArray()
        {
            for(int i = 0; i<5;i++)
            {
                a[i].a = i;
            }
            b.a = 100;
            std::cout<<"after constructor"<<std::endl;
        }
        ~DelArray()
        {
            //析构的时候先调用析构函数中的语句，该函数节航速后再析构成员变量。
            //此函数中没有手动释放a b, a、b是该函数结束后自动被析构的
            std::cout<<__FUNCTION__<<std::endl;
        }
    private:
        A a[5];
        A b;
};


//out:
//    after
//    delete A,a=2
//    delete A,a=1
//    delete A,a=0
//    after constructor
//    delete A,a=4
//    delete A,a=3
//    delete A,a=2
//    delete A,a=1
//    delete A,a=0
//    out
