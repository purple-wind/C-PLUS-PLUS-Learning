#include<iostream>
#include<vector>
#include"smart_pointer.hpp"
#include"my_allocator.h"
#include"forward_declaring_shareptr.h"

extern void wrap_test_sharedptr();

int main()
{
    std::cout<<"-----------智能指针析构---------------"<<std::endl;
    wrap_test_sharedptr();

    std::cout<<"-----------智能指针前置申明---------------"<<std::endl;
    ForwardDeclar x;
    x.Print();

    std::cout<<"-----------自定义内存管理---------------"<<std::endl;
    MyAllocator alloc;
    alloc.used_allocator();
}
