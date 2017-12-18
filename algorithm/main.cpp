#include<string>
#include<algorithm>
#include<iostream>
int main()
{
//count算法,计算出某个元素在序列中出现的次数
  std::string test100="12345?6789?abcdef?abcd?ef";
  auto it=count ( test100.begin(),test100.end(),'?' );
  std::cout<<"it="<<it<<std::endl;
}