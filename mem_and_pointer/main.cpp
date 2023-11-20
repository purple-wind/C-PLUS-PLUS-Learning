#include<iostream>
#include<vector>
#include"smart_pointer.hpp"
#include"my_allocator.h"
#include"forward_declaring_shareptr.h"
#include"safe_thread_ptr.hpp"
#include"raw_pointer_array.hpp"

extern void wrap_test_sharedptr();

int main()
{
    std::cout<<"-----------原始指针---------------"<<std::endl;
    std::cout<<"-------二级和多级指针-------"<<std::endl;
    test_second_rank_pointer();
    std::cout<<"-------realloc-------"<<std::endl;
    test_realloc();
    test_array_row_column();
    
    
    std::cout<<"-----------智能指针析构---------------"<<std::endl;
    wrap_test_sharedptr();

    std::cout<<"-----------智能指针前置申明---------------"<<std::endl;
    ForwardDeclar x;
    x.Print();

    std::cout<<"-----------自定义内存管理---------------"<<std::endl;
    MyAllocator alloc(10);
    alloc.test_general();
    alloc.test_copy_fill();

    std::cout<<"-----------智能指针循环引用---------------"<<std::endl;
    {
        std::shared_ptr<CircularRef> ref0 = std::make_shared<CircularRef>();
        std::shared_ptr<CircularRef> ref1 = std::make_shared<CircularRef>();
        std::cout<<"ref0 ="<<ref0<<std::endl;
        std::cout<<"ref1 ="<<ref1<<std::endl;
        std::cout<<"ref0 ptr="<<ref0->ptr<<std::endl;
        std::cout<<"ref1 ptr="<<ref1->ptr<<std::endl;
        std::cout<<"ref0 use count="<<ref0.use_count()<<std::endl;
        std::cout<<"ref1 use count="<<ref1.use_count()<<std::endl;
        ref1->ptr = ref0;
        ref0->ptr = ref1;
        std::cout<<"ref0 ptr="<<ref0->ptr<<std::endl;
        std::cout<<"ref1 ptr="<<ref1->ptr<<std::endl;

        std::cout<<"ref0 ptr ptr="<<ref0->ptr->ptr<<std::endl;
        std::cout<<"ref1 ptr ptr="<<ref1->ptr->ptr<<std::endl;
        std::cout<<"ref0 use count="<<ref0.use_count()<<std::endl;
        std::cout<<"ref1 use count="<<ref1.use_count()<<std::endl;
    }

    int *p0 = new int(1000);
    std::cout<<"p0="<<p0<<std::endl;
    std::shared_ptr<int>p1(p0);
    std::cout<<"*ptr="<< *p1<<std::endl;
    std::cout<<"address="<<p1.get()<<std::endl;


    std::cout<<"-----------智能指针线程安全性---------------"<<std::endl;
    test_safe_thread0();
//    test_safe_thread1();
//    test_safe_thread2();

    std::cout<<"-----------获取对象地址，即使对象重载了&运算符---------------"<<std::endl;
    std::cout<<"x address="<<std::addressof(x)<<" &x="<<&x<<std::endl;
    shared_ptr<ForwardDeclar>y = nullptr;
    std::cout<<"x address="<<std::__to_address(y)<<" &x="<<&y<<std::endl;
#if __cplusplus > 201703L //since c++20
    std::cout<<"x address="<<std::to_address(y)<<" &x="<<&y<<std::endl;
#endif

    test1_sharedptr();




    return 0;
}
