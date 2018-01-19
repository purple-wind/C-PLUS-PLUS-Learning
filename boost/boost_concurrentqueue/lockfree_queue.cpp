#include <iostream>
#include <boost/threadpool.hpp>
#include "global.h"
#include <sys/types.h>



void Thread_SetQueue1()
{
    bool bRet = false;
    while ( 1 ) {


        TcpData* tcp_node= ( TcpData* ) malloc ( sizeof ( TcpData ) );
        tcp_node->data= ( char* ) malloc ( 4096 );
        tcp_node->len=4096;
        memset ( tcp_node->data,'A',tcp_node->len );

        while ( !que.push ( tcp_node ) ) {};
        pushc++;
// 		boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(1));
// 		boost::thread::sleep(boost::get_system_time()+boost::posix_time::microseconds(1));
// 		boost::thread::sleep(boost::get_system_time()+boost::posix_time::milliseconds(1));
    };
}


void Thread_GetQueue1()
{
    TcpData* out;
    while ( 1 ) {
        if ( que.pop ( out ) ) {
            popc++;
            free ( out->data );
            free ( out );
//            int fd=open("./get1.txt",O_CREAT|O_RDWR|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
//            std::string str(std::to_string(out.src_mac));
//            str+="---1\n";
//            write(fd,str.c_str(),str.size());
//            close(fd);

        }
    }
}


//void Thread_GetQueue2()
//{
//    TcpData* out;
//    while(1)
//    {
//        if(que.pop(out))
//        {
////            popc++;
////            int fd=open("./get2.txt",O_CREAT|O_RDWR|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
////            std::string str(std::to_string(out.src_mac));
////            str+="---2\n";
////            write(fd,str.c_str(),str.size());
////            close(fd);
//        }
//    }
//}
