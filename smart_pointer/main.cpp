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

    {
        std::shared_ptr<CircularRef> ref0 = std::make_shared<CircularRef>();
        std::shared_ptr<CircularRef> ref1 = std::make_shared<CircularRef>();
        std::cout<<"ref0 ="<<ref0<<std::endl;
        std::cout<<"ref1 ="<<ref1<<std::endl;
        std::cout<<"ref0 ptr="<<ref0->ptr<<std::endl;
        std::cout<<"ref1 ptr="<<ref1->ptr<<std::endl;
        ref1->ptr = ref0;
        ref0->ptr = ref1;
        std::cout<<"ref0 ptr="<<ref0->ptr<<std::endl;
        std::cout<<"ref1 ptr="<<ref1->ptr<<std::endl;

        std::cout<<"ref0 ptr ptr="<<ref0->ptr->ptr<<std::endl;
        std::cout<<"ref1 ptr ptr="<<ref1->ptr->ptr<<std::endl;
        std::cout<<"ref0 use count="<<ref0.use_count()<<std::endl;
        std::cout<<"ref1 use count="<<ref1.use_count()<<std::endl;
    }
}
