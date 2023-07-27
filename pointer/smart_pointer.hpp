#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__
#include<memory>
#include<iostream>
#include<vector>
#include<utility>

/*
 * 1.shared_ptr允许多个指针指向同一个对象；
 * 2.unique_ptr独占所指向的对象，不允许其它指针指向此对象；
 * 3.weak_ptr弱引用，具有对象的访问权，不参与对象的析构。引用一个对象时不增加引用计数
 * 4.(重点),不要混合使用内置指针和智能指针。智能指针可以协调对象的析构(即智能指针在析构的时候会析构它指向的对象)，但这仅限于其自身的拷贝
 * 之间(即share_ptr之间)。假设一个内置指针指向一块new的内存，然后再将share_ptr绑定到此内置指针，
 * 当用内置指针操作这块内存的时候，智能指针是无法知道的，和这块内存相关的计数器不会变化。最终
 * 不会知道对象何时被销毁；如果把一个内置指针绑定到智能指针，即表示把内存管理的责任交给了智能
 * 指针，就不应该再用内置指针操作此内存了。
 * 5.不要将多个独立创建的share_ptr绑定到同一块内存，否则在某一个独立share_ptr的计数器为0时，
 * shared_ptr会控制这块内存的释放，而与此同时假设另外一块独立的share_ptr还在使用中，但是此时内存
 * 已经被释放了，此智能指针将变成一个悬空指针。
 * 6.智能指针支持前向声明，智能指针指向的类型可以使用前向声明而无需include头文件
 * 7.shared_ptr不合理的使用可能存在循环引用问题，造成内存无法释放，可使用weak_ptr解决
 * 8.
 */

using namespace std;
class SmartPointer
{
public:
    SmartPointer() :int1_ptr(),int2_ptr ( new int ( 2 ) ),int3_ptr ( std::make_shared<int> ( 3 ) )
    {

    }

    std::shared_ptr<int>int1_ptr;//默认初始化的智能指针保存着空指针
    std::shared_ptr<int>int2_ptr ; //int2_ptr接管new出来的内存
    std::shared_ptr<int>int3_ptr;//构造一个智能指针并用100初始化，这是最安全的分配和使用动态内存的方法
};


//循环引用
class CircularRef
{
    public:
        ~CircularRef()
        {
            std::cout<<"~CircularRef"<<std::endl;
        }

        std::shared_ptr<CircularRef> ptr;
        //std::weak_ptr<CircularRef> ptr;
};






//智能指针在析构的时候会析构它指向的对象
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




#endif
