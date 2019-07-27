#include<string>
#include<algorithm>
#include<iostream>
#include "single_link.h"
#include "sort.h"
#include "find.h"
int main()
{
//count算法,计算出某个元素在序列中出现的次数
  std::string test100="12345?6789?abcdef?abcd?ef";
  auto it=count ( test100.begin(),test100.end(),'?' );
  std::cout<<"it="<<it<<std::endl;


  int array[10] = {1,2,3,4,5,6,7,8,9,10};
  std::cout<<binary_serach ( 8,array,10 ) <<std::endl;
  std::cout<<binary_serach2 ( 8,array,0,10 ) <<std::endl;

  std::cout<<"-------single link---------"<<std::endl;
  link_init();
  link_insert_tail ( 0 );
  link_insert_tail ( 1 );
  link_insert_tail ( 2 );
  link_insert_head ( -1 );
  link_insert_head ( -2 );
  link_insert_tail ( 3 );
  link_insert_tail ( 4 );
  link_insert_head ( -3 );
  link_insert_head ( -4 );
  link_for_each();
  link_remove_head();
  link_remove_tail();
  link_remove_tail();
  link_for_each();
  link_remove ( 0 );
  link_remove ( -2 );
  link_for_each();
  std::cout<<"size="<<link_size() <<std::endl;
  std::cout<<"get head="<<link_get_head() <<std::endl;
  std::cout<<"get tail="<<link_get_tail() <<std::endl;
  link_reverse();
  link_for_each();
  link_deinit();
  link_remove_head();
  link_remove_tail();
  link_remove_tail();
  link_for_each();
  link_remove ( 0 );
  link_remove ( -2 );
  link_for_each();
  std::cout<<"size="<<link_size() <<std::endl;
  std::cout<<"get head="<<link_get_head() <<std::endl;
  std::cout<<"get tail="<<link_get_tail() <<std::endl;

  std::cout<<"-------sort---------"<<std::endl;  
  int array1[10] = {6,1,2,7,9,3,4,5,10,8};
  bubble_sort ( array1,10 );
  selection_sort ( array1,10 );
  insert_sort ( array1,10 );
  quick_sort ( array1,0,9 );
  for ( int i = 0; i <sizeof ( array1 ) /sizeof ( int ); i++ )
    {
      printf ( "array[%d]=%d\n",i,array1[i] );
    }

}
