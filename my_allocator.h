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
/* 定义该类为类指针行为
 * 1.allocate(n),定义n个未构造的内存，此内存必须经过construct构造才能使用，使用未构造的内存行为是未定义的;
 * 2.destroy(p)对p指向的元素进行析构，destroy只能对真正被构造了的元素操作。
 * 3.deallocate(p,n)函数用来将内存归还给系统，deallocte的p参数必须是allocate返回的指针，即从系统获取的内存
 * 的首地址;n必须等于allocate函数调用时的参数;而且在调用deallocate前必须对已经构造过了的内存进行destory操作;
 * 4.标准库定义了4个拷贝和填充未初始化的内存的算法
 * 		std::uninitialized_copy(v.begin(),v.end(),bp);
        std::uninitialized_copy_n(v.begin()+*2,1,bp+3);
 		std::uninitialized_fill(bp+4,bp+6,"46");
		std::uninitialized_fill_n(bp+6,4,"79");
 */
class my_allocator
{
public:
    my_allocator()=default;
	void used_allocator();
};

#endif // MY_ALLOCATOR_H
