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
            std::cout<<"after constructor"<<std::endl;
        }
    private:
        A a[5];
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
