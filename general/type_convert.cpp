//类型转换特性介绍

#include<iostream>
//小对齐系数类型的指针转换成大对齐系数类型的指针，可编译通过，但是解引用错误
void test_low_align_high()
{
    char c = 1;
    char *p = &c;
    unsigned int  *q = (unsigned int*)p;
    std::cout<<"*q="<<*q<<std::endl;
}

void test_high_align_low()
{
    unsigned int c = 65;
    unsigned int *p = &c;
    char *q = (char*)p;
    std::cout<<"*q="<<*q<<std::endl;
}
