#include<memory>
#include<iostream>
#include <cstdio>
#include <thread>
#include <unistd.h>
/**
 * 智能指针的线程安全性：智能指针的线程安全级别和内建类型、标准库容器等一致
 *  1.一个shared_ptr对象实体可被多个线程同时读取
 *  2.两个shared_ptr对象实体可以被两个线程同时写入
 *  3.如果多个线程同时读写同一个shared_ptr对象，那么需要加锁
 *  此处描述的是智能指针本身的线程安全级别，不是它管理对象的线程安全级别。它所管理对象的线程安全等级有被管理对象自身保证。
 *
 */
void test_safe_thread0()
{
 std::shared_ptr<int> sp0 = std::make_shared<int>(1);
 std::cout<<"sp0 address="<<sp0<<" " << sp0.get()<<" "<<sp0.use_count()<<std::endl;
 std::shared_ptr<int>& sp0_ref = sp0;
 std::cout<<"sp0 ref address="<<sp0_ref<<" " << sp0_ref.get()<<" " <<sp0_ref.use_count()<<std::endl;
 std::shared_ptr<int> sp1 = sp0;
 std::cout<<"sp1 address="<<sp1<<" " << sp1.get()<<" " <<sp1.use_count()<<std::endl;
 sp0.reset();
 std::cout<<"sp1 address="<<sp1<<" " << sp1.get()<<" " <<sp1.use_count()<<std::endl;
}

//通过值传递方式在多个线程中共享一个shared_ptr是线程安全的
//思考一个问题，为什么传值的方式是线程安全的?
//因为一旦智能指针被值方式传递到线程中，即是线程还没开始运行，此时实参的引用计数已经
//增加了1，无论其它线程如何交织执行，也不会让实参指向的内存对应的引用计数小于1。
//以此处为例，当该函数以线程处理函数被启动时，arg已经被传递进来了，
//此时外部的实参的cnt=2，即test_safe_thread2中的pointer->cnt=2
//即foo_value中的arg和test_safe_thread2中的poninter指向的是同一个被管理的
//内存int*, 他们的引用计数指针也是同一个且为2。此后无论foo_value和test_safe_thread2两个
//线程如何交织执行都是线程安全的。因为在foo_value内部arg已经增加了引用计数，在foo_value之外的
//任意线程都不会使引用计数减少到小于1的状态。别的线程同理。
void foo_value(std::shared_ptr<int> arg)
{
    int data = 0;
    for (;;) {
        auto p = arg;
        if (p) {
            data += *p;
        }
    }
}

//通过引用或者指针的方式在多个线程中共享一个shared_ptr是非线程安全的，避免使用此方式
void foo_ref(std::shared_ptr<int>& arg)
{
    int data = 0;
    for (;;) {
        auto p = arg;
        if (p) {
            data += *p;
        }
    }
}


void test_safe_thread1()
{
    int i = 0;
    static std::shared_ptr<int> pointer = std::make_shared<int>(++i);
    std::thread t1(foo_value, pointer);
    for (;;) {
      pointer = std::make_shared<int>(++i);
    }
}

void test_safe_thread2()
{
    int i = 0;
    static std::shared_ptr<int> pointer = std::make_shared<int>(++i);
    std::thread t1(foo_ref, std::ref(pointer));
    for (;;) {
      pointer = std::make_shared<int>(++i);
    }
}

