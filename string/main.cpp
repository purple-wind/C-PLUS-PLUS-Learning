#include<iostream>
#include<string>
#include<cstdio>
#include<stdint.h>
#include<map>
#include<pthread.h>
#include<sstream>
#include<algorithm>
#include<vector>
#include<string.h>
#include<iostream>
#include<errno.h>
using namespace std;
/*1.字符串的find函数效率高于拆分后的字符串存放到set中，用set.find
 *2.可以把一个字符用"+"的形式存入string
 *3.所有的stox()转换函数都不能转换16进制的字符串，只能转换数字组成的字符串
 */
void str_to_number()
{
    std::cout<<std::stoi("1243") - 1<<std::endl;
    std::cout<<std::stol("1243.3") - 1<<std::endl;
    std::cout<<std::stof("1243.333333") - 1<<std::endl;
    std::cout<<std::stod("1243.333333") - 1<<std::endl;
    std::cout<<std::stoul("-1") - 1<<std::endl;
    std::cout<<std::stoull("1243.333333") - 1<<std::endl;
    std::cout<<std::stoull("1243.333333") - 1<<std::endl;
    std::cout<<std::stold("1243.333333") - 1<<std::endl;
}



//整数初始化std::string在语法上是允许的，但是结果可能是错误的，因为basic_string<>模板类实现了basic_string& operator=(_CharT __c)赋值运算符重载函数
//允许接收一个字符的参数，造成整形数占用的第一个字节被隐式转换成单个字符。这在使用中是灾难性的，因为这造成了一个结果就是"用大于127的整型数赋值给std::string
//是被允许的，而编译器不会报错"，但是这样的赋值语句并不是代码的本意，可能仅仅是类型使用错误而把一个整型数赋值给了string，但是编译时编译器发现不了该问题，运行时
//获取的结果却是错误的。
void integer_init_string()
{
    std::string b;
    b = 123;
    std::cout<<"b="<<b<<std::endl;


    //    string c = 123; //编译失败，因为123不能隐式转换成string类型，此拷贝构造无法进行


    struct ABC{
            std::string a;
    };

    struct ABC abc;
    abc.a = 123;

}

// 可以把一个字符用"+"的形式存入string
void string_join()
{
    std::cout<<"---------------string join-------------------"<<std::endl;
    std::string test;
    test+='a';
    test+='b';
    test+='c';
    test+='d';
    test+='e';
    std::cout<<test<<std::endl;
}


void string_to_x()
{
    std::cout<<"---------------string to x-------------------"<<std::endl;

    // strtoul()函数,所有的atoi类型的转换函数都不能转换16进制的字符串，只能转换数字组成的字符串
    std::string str="1a";
    uint64_t l=strtoul(str.data(),NULL,10);
    l=stol(str.data());
    std::cout<<l<<std::endl;


    // std::to_string(),可以将16进制的数字转化成十进制字符串
    pthread_t tid=0x0f;
    std::string test=std::to_string(tid);
    std::cout<<test<<std::endl;
    std::cout<<"atoi="<<atoi(test.data())<<std::endl;
}


void intit_string()
{
    //可以用字符数组初始化string类型对象，即使字符数组不是以'\0'结尾的
    std::cout<<"---------------arr init string-------------------"<<std::endl;

    string temp0{'1', '2', '3'};
    std::cout << "temp0=" << temp0 << std::endl;

    string temp1 = {'1', '2', '3'};
    std::cout << "temp1=" << temp1 << std::endl;

    //不支持
    //string temp2 = {"123", "456", "789"};
    //std::cout << "temp2=" << temp2 << std::endl;

    char arr[10];
    int j = 97;
    for(int i = 0;i < 10; i++)
    {
        arr[i] = j;
        j++;
    }
    printf(" array=%s\n",arr);
    string temp3(arr);
    cout << "string3=" << temp3 << endl;

    string temp4("12345");
    cout << "string4=" << temp4 << endl;

    const char arr1[] = "12345";
    string temp5(arr1);
    cout << "string5=" << temp5 << endl;

    const char *cstr = "12345";
    string temp6(cstr);
    cout << "string6=" << temp6 << endl;

    string temp7(cstr, 5);
    cout << "string7=" << temp7 << endl;


    string temp8(cstr, 4);
    cout << "string8=" << temp8 << endl;

    string temp9(10, 'A');
    cout << "string9=" << temp9 << endl;

}


int main()
{
    intit_string();
    string_join();
    string_to_x();
    integer_init_string();
}
