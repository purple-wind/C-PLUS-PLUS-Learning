 
#include<iostream>
using namespace std;
int main()
{
  int i;
  const int& ri=i;
  i=5;
  cout<<ri<<endl;
  return 0;
}
