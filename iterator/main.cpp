#include<iostream>
#include<vector>
int main()
{
 std::vector<int>vec{1,2,3};
 std::vector<int>::iterator it=vec.begin()+1;
 vec.erase(it);
 std::cout<<*it<<std::endl;
 std::cout<<*(--it)<<std::endl;
 std::cout<<*(++it)<<std::endl;
 std::cout<<*(it+2)<<std::endl;
 std::cout<<vec.size()<<std::endl;
 std::cout<<vec.capacity()<<std::endl;
 return 0;
}
