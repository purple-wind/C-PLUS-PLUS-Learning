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



 int main()
 {
     string str("fsajdfiaiopfopi:FKJSLJFDSLOJOgjkfrsgjkjl:UJieoapiY");
     string str1="fdskjsajk";
     str=str1;
     for(auto& c:str)
         c=toupper(c);
     cout<<str<<endl;
     cout<<str[str.size()-1]<<endl;


     string hex="0123456789ABCDEF";
     string result;
     string::size_type n;
     while(cin>>n && n<hex.size())
         if(n<hex.size())
             result=result+hex[n];
     cout<<result<<endl;

     char arr[10];
     int j=97;
     for(int i=0;i<10;i++)
     {
         arr[i]=j;
         j++;
     }
     printf("%s\n",arr);
     string temp(arr);//可以用字符数组初始化string类型对象，即使字符数组不是以'\0'结尾的
     cout<<temp<<endl;


     //  可以把一个字符用"+"的形式存入string
     std::string test;
     test+='a';
     test+='b';
     test+='c';
     test+='d';
     test+='e';
     std::cout<<test<<std::endl;


     // std::to_string(),可以将16进制的数字转化成十进制字符串

     pthread_t tid=100;
     test=std::to_string(tid);
     std::cout<<test<<std::endl;
     std::cout<<"atoi="<<atoi(test.data())<<std::endl;


     // strtoul()函数,所有的atoi类型的转换函数都不能转换16进制的字符串，只能转换数字组成的字符串
     str="1a";
     uint64_t l=strtoul(str.data(),NULL,10);
     l=stol(str.data());
     std::cout<<l<<std::endl;


     //可以添加空字符串
     std::string abcdef="abcdef";
     abcdef=abcdef+"";
     abcdef+="abcdef";
     std::cout<<abcdef<<std::endl;

     std::string html="abc";
     std::stringstream ss;
     ss<<65;
     html+=ss.str();
     std::cout<<html<<std::endl;
 }
