#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__
#include<memory>
/*
 * 1.shared_ptr允许多个指针指向同一个对象；
 * 2.unique_ptr独占所指向的对象，不允许其它指针指向此对象；
 * 3.weak_ptr弱引用，
 * 4.(重点),不要混合使用内置指针和只能指针。智能指针可以协调对象的析构，但这仅限于其自身的拷贝
 * 之间(即share_ptr之间)。假设一个内置指针指向一块new的内存，然后再将share_ptr绑定到此内置指针，
 * 当用内置指针操作这块内存的时候，智能指针是无法知道的，和这块内存相关的计数器不会变化。最终
 * 不会知道对象何时被销毁；如果把一个share_ptr绑定到内置指针，即表示把内存管理的责任交给了只能
 * 指针，就不因该再用内置指针操作此内存了。
 * 5.不要将多个独立创建的share_ptr绑定到同一块内存，否则在某一个独立share_ptr的计数器为0时，会
 * shared_ptr会控制这块内存的释放，而与此同时假设另外一块独立的share_ptr还在使用中，但是此时内存
 * 已经被释放了，此智能指针将变成一个悬空指针。
 */
class SmartPointer{
public:
	void construction()
	{
		std::shared_ptr<int>int1_ptr;//默认初始化的智能指针保存着空指针
		std::shared_ptr<int>int2_ptr(new int(10));//

	}
};


#endif