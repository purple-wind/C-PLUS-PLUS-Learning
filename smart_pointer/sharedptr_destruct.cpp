/*智能指针析构*/

#include<iostream>
#include<vector>
#include<utility>
#include<memory>
using namespace std;

struct S0{
        S0(int x)
        {
            a = x;
        }

        ~S0()
        {
            std::cout<<"析构S0"<<std::endl;
        }
        int a;
};

using Tup = std::tuple<std::string, std::shared_ptr<struct S0> >;

void test_sharedptr(std::shared_ptr<std::vector<Tup> > &x)
{
    {
        vector<Tup> vec = {Tup("123", make_shared<struct S0>(100))};
        x = make_shared<vector<Tup> >(vec);
        shared_ptr<vector<Tup> > temp_ptr = nullptr;
        x.swap(temp_ptr);
        std::cout<<"x address="<<x<<std::endl;
    }
    std::cout<<"test_sharedptr end"<<std::endl;
}

void wrap_test_sharedptr()
{
    {
        //智能指针在析构的时候会析构它指向的对象
        std::shared_ptr<std::vector<Tup> > x = nullptr;
        test_sharedptr(x);
        //std::cout<<get<0>((*x)[0])<<std::endl;
        std::cout<<"x address="<<x<<std::endl;
    }
    std::cout<<"after test_sharedptr"<<std::endl;
}
