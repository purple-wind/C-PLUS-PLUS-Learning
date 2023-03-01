#include"my_fstream.h"
int main()
{
    std::cout<<"---------------文件流--------------------"<<std::endl;
    // 	文件流
    Fstream test_fstream;
    test_fstream.rw_binary ( "test.txt" );
    test_fstream.test_getline();
    Fstream::c_file();
    return 0;
}
