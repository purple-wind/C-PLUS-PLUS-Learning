#include"my_allocator.h"
#include<memory>
#include<iostream>
#include<vector>
void my_allocator::used_allocator()
{
    typedef std::allocator<std::string> AS;
    AS a;
    AS::pointer bp=a.allocate ( 10 );
    std::vector<std::string> v= {"123","456","789"};
    std::uninitialized_copy ( v.begin(),v.end(),bp );
    std::uninitialized_copy_n ( v.begin() +2,1,bp+3 );
    std::uninitialized_fill ( bp+4,bp+6,"46" );
    std::uninitialized_fill_n ( bp+6,4,"79" );
    for ( int i=0; i<10; i++ )
    {
        std::cout<<"bp+"<<i<<"="<<* ( bp+i ) <<"  ";
    }
        std::cout<<std::endl;
    a.deallocate ( bp,10 );
}
