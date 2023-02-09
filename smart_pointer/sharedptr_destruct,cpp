/*智能指针析构*/

#include "forward declaring_shareptr.h"
#include<iostream>
#include<vector>
#include<utility>
struct X
{
        X(int x)
        {
            a = x;
        }

        int a;
};

xyz::xyz()
{
    m_ptr_x = std::make_shared<X>(100);
}

struct S0{
        S0(int x)
        {
            a = x;
        }

        int a;
        ~S0()
        {
            std::cout<<"析构S0"<<std::endl;
        }
};

using tup = tuple<std::string, shared_ptr<struct S0> >;
void test_sharedptr(shared_ptr<vector<tup> >& x)
{
    {
        vector<tup> vec = {tup("123", make_shared<struct S0>(100))};
        x = make_shared<vector<tup> >(vec);
        shared_ptr<vector<tup> > temp_ptr = nullptr;
        x.swap(temp_ptr);
        std::cout<<"x address="<<x<<std::endl;
    }
    std::cout<<"test_sharedptr end"<<std::endl;
}


int main()
{
    xyz x;
    std::cout<<x.m_ptr_x->a<<std::endl;


    {
        //智能指针在析构的时候会析构它指向的对象
        shared_ptr<vector<tup> > x = nullptr;
        test_sharedptr(x);
//        std::cout<<get<0>((*x)[0])<<std::endl;
        std::cout<<"x address="<<x<<std::endl;
    }
    std::cout<<"after test_sharedptr"<<std::endl;
}
