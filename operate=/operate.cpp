#include<iostream>

class test{
public:
 test(int c,int d)
 {
  a=c;
  b=d;
 }
void operator()()
 {
 std::cout<<"run ()"<<std::endl;  
 } 
private:
 int a;
 int b;
};

int main()
{
 test(1,2)();
//  t();
 return 0;
}