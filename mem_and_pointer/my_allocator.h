/*
 * Copyright 2017 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H
/*
 * 1.当我们使用new分配内存时，它在分配内存的同时也构造了对象，造成一些灵活性上的局限。
 *   有时候我们希望将内存分配和对象构造分离，例如分配一块很大的内存，但是直到使用时才在该内存上构造对象。
 *   标准库提供了allocator类为我们实现该功能。
 * 2.allocator是一个模板，它需要一个类型参数指明allocator可以分配的对象的类型，便于根据allocator调用allocate()时根据对象类型来确定恰当的
 *   内存大小和对齐位置。allocator对象本身构造时不分配动态内存，只有调用allocate()函数时才需要分配内存。
 * 2.allocate(n),定义n个未构造的内存，此内存必须经过construct构造才能使用，使用未构造的内存行为是未定义的;
 * 3.construct(p, args)用来在p指向的内存中构造一个对象，p是指向的原始内存，args是要构造类型的构造函数的参数
 * 3.destroy(p)对p指向的元素进行析构，destroy只能对真正被构造了的元素操作。执行了destroy的对象
 * 4.deallocate(p,n)函数用来将内存归还给系统，deallocte的p参数必须是allocate返回的指针，即从系统获取的内存
 * 的首地址;n必须等于allocate函数调用时的参数;而且在调用deallocate前必须对已经构造过了的内存进行destory操作;
 * 5.标准库定义了4个拷贝和填充未初始化的内存的伴随算法
 * 		std::uninitialized_copy();
        std::uninitialized_copy_n();
 		std::uninitialized_fill();
		std::uninitialized_fill_n();
        这4个函数参数是迭代器，表明它们操所的对象不仅仅限于未初始化的内存。其实只要把迭代器做参数传递给这4个函数，他们都可以对迭代器指定的位置
        进行操作。但最常见的使用方式是用他们来操作未初始化的内存
 */

#include<string>
#include<memory>
#include<iostream>
class MyAllocator
{
    public:
        using AS = std::allocator<std::string>;
        MyAllocator(size_t n): first(a.allocate(n))
        {
        }
        ~MyAllocator()
        {
            //元素所占的内存释放,第一个参数必须是allocate()返回的指针,n必须是allocate()函数调用时给定的值
            a.deallocate(first, n);
        }
        void test_general();
        void test_copy_fill();
    private:
        AS a;
        AS::pointer first;
        size_t n;
};

#endif // MY_ALLOCATOR_H
