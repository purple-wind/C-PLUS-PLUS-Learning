#include <unistd.h>
#include <limits>
#include <limits.h>
#include <iostream>
#include <climits>
#include <math.h>
//无符号数溢出在c/c++中有明确定义，即溢出时进行modulo 2^(sizeof(TYPE))
//有符号数是未定义的行为,一般有如下四种行为:
//  1.按照表示法规则(典型为补码)发生回绕；实测gcc即是此种
//  2.在某些平台上或者由于编译器选项（例如 GCC 和 Clang 中的 -ftrapv）引发陷阱
//  3.在某些时候截断到最小或最大值（在许多 DSP 上）
//  4.完全被编译器优化掉
int main(int argc, char *argv[])
{
    unsigned int  i0 = UINT_MAX;
    unsigned int  i1 = std::numeric_limits<unsigned int>::min();
    unsigned int i2 = std::numeric_limits<unsigned int>::max();
    std::cout<<"unsigned int min="<<i1<<" min - 1="<< i1 - 1 <<std::endl;
    std::cout<<"unsigned int max="<<i2<<" max + 1="<< i2 + 1 <<std::endl;
    unsigned long long i5 = i2 * i2;
    std::cout<<"max * max ="<<i5<<" "<<std::hex<<0x00123456 * 0x00654321<<std::endl;

    int i3 = std::numeric_limits<int>::max();
    int i4 = std::numeric_limits<int>::min();
    std::cout<<"int max="<<i3<<" int min="<<i4<<std::endl;
    std::cout<<"int max +1 ="<<i3 + 1<<std::endl;
    std::cout<<"int min -1 = "<<i4 -1<<std::endl;

    unsigned long long i6 = 0x00123456;
    unsigned long long i7 = 0x00654321;
    std::cout<<std::hex<<i6*i7<<std::endl;

    unsigned int i8 = 0x00123456;
    unsigned int i9 = 0x00654321;
    std::cout<<std::hex<<"uint*uint="<<i8*i9<<std::endl;//截断

}
