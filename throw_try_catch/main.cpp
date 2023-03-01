#include"throw.hpp"
int main()
{
    std::cout<<"----------------异常-------------------"<<std::endl;
  //   异常处理
    Throw th;
    for ( int i=99; i<102; i++ )
      {
        th.test ( i );
      }
    Throw th1;
    th1.test1 ( 0 );
    try
      {
        th1.test2 ( 0 );
      }
    catch ( std::logic_error er )
      {
        std::cout<<er.what() <<std::endl;
      }
    return 0;
}
