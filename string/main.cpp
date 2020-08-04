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



// int main()
// {
//  string str("fsajdfiaiopfopi:FKJSLJFDSLOJOgjkfrsgjkjl:UJieoapiY");
// //  string str="fsajdfiaiopfopi:FKJSLJFDSLOJOgjkfrsgjkjl:UJieoapiY";
//  string str1="fdskjsajk";
//  string str=str1;
//  for(auto& c:str)
//   c=toupper(c);
//  cout<<str<<endl;
//  cout<<str[str.size()-1]<<endl;
//  
//  
//  string hex="0123456789ABCDEF";
//  string result;
//  string::size_type n;
//  while(cin>>n&&n<hex.size())
//   if(n<hex.size())
//    result=result+hex[n];
//   cout<<result<<endl;
//  
//  char arr[10];
//  int j=97;
//  for(int i=0;i<10;i++)
//  {
//   arr[i]=j;
//   j++;
//  }
//  printf("%s\n",arr);
//  string temp(arr);//可以用字符数组初始化string类型对象，即使字符数组不是以'\0'结尾的
//  cout<<temp<<endl;
//  
//  
//  
//  
// 
// 
// //  可以把一个字符用"+"的形式存入string 
//  std::string test;
//  test+='a';
//  test+='b';
//  test+='c';
//  test+='d';
//  test+='e';
//  std::cout<<test<<std::endl;
//  
//  
// // std::to_string(),可以将16进制的数字转化成十进制字符串
//  
// uint64_t value=0xa1;
// pthread_t tid=100;
// std::string test=std::to_string(tid);
// std::cout<<test<<std::endl;
// std::cout<<"atoi="<<atoi(test.data())<<std::endl;
// 
//  
// // strtoul()函数,所有的atoi类型的转换函数都不能转换16进制的字符串，只能转换数字组成的字符串
// std::string str="1a";
// uint64_t l=strtoul(str.data(),NULL,10);
// uint64_t l=stol(str.data());
// std::cout<<l<<std::endl;


// 可以添加空字符串
// std::string abcdef="abcdef";
// abcdef=abcdef+"";
// abcdef+="abcdef";
// std::cout<<abcdef<<std::endl;
// }



void search(std::string& src,std::string c,size_t n)
{
 std::cout<<"n="<<n<<std::endl;
 if(n==0) return;
std::string::size_type pos;
if((pos=src.find(c))!=std::string::npos)
{
 src=std::string(src,pos+1);
 std::cout<<"src="<<src<<std::endl;
 search(src,c,--n);
}
}

void get_index(std::string& src,char key,std::vector<int>& index)
{
	for(int i=0;i<src.size();i++)
	{
		if(src[i]==key)
		  index.push_back(i);
	}
}
int main()
{
 std::string src="?UTF-8?B?c2luYS5jbumCrueusQ==?=";
 std::vector<int>index;
 get_index(src,'?',index);
 for(auto it:index)
	std::cout<<it<<std::endl;


 std::string src_str="12345";
 char len[6];
 size_t a=src_str.size();
 sprintf(len,"%06lu",a);
 std::string dst=std::string(len)+src_str;
 std::cout<<"len="<<dst.size()<<" "<<dst<<std::endl;
 return 0;
}










// int main()
// {
//  std::string html="abc";
//  std::stringstream ss;
//  ss<<65;
//  html+=ss.str();
//  std::cout<<html<<std::endl;
// return 0;
// }
