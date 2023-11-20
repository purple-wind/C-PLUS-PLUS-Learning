#include"my_allocator.h"
#include<vector>

void MyAllocator::test_general()
{
    AS::pointer bp = first;
    a.construct(bp, "hello");
    bp++;
    a.construct(bp, "world");
    bp++;
    *bp = "hahaha";//此时bp指向的内存未被构造，这样使用的行为是未定义的。个人觉得如果是内置内类不会有什么问题，类类型可能会有问题
    bp++;
    for(auto iter = first; iter < bp; iter++)
    {
        std::cout << "iter=" << *iter << std::endl;
        a.destroy(iter); //销毁元素，执行元素类型的析构函数。但是元素本身所占的内存未被释放。此后这个位置可以保存其它元素
    }
    //a.deallocate(first, n);//最好在管理alloctor类的析构函数中释放内存，中同不要释放内存
}

void MyAllocator::test_copy_fill()
{
    std::vector<std::string> v{"123", "456", "789"};
    std::uninitialized_copy(v.begin(), v.end(), first);//把迭代器指定返回内的元素拷贝到目的指定的位置，改函数还会返回一个指针，指向最后一个构造的元素之后的位置
    std::uninitialized_copy_n(v.begin() + 2, 1, first + 3);//把迭代器指定位置之后的n个元素拷贝到目的指定的位置
    std::uninitialized_fill(first + 4, first + 6, "46");//用指定的值填充迭代器指定的范围内的元素
    std::uninitialized_fill_n(first + 6, 4, "79");//用指定的值填充迭代器指定位置之后的n个元素

    for(auto iter = first; iter < first + 10; iter++)
    {
        std::cout << "iter=" << *iter << std::endl;
    }

    //由于uninitialized_fill_n的参数是迭代器，所也也可以往vector中填充数据。不仅限于未初始化的内存。下面的用法也是合法的
    std::uninitialized_fill_n(v.begin(), 2, "111");
    for(auto &item:v)
    {
        std::cout << "v=" << item << std::endl;
    }
}
