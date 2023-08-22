#include <iostream>
#include </usr/include/boost/threadpool/boost/threadpool.hpp>
#include "global.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <fcntl.h>

void thread_set_queue1()
{
    while ( 1 ) {
        TcpData* tcp_node= ( TcpData* ) malloc ( sizeof ( TcpData ) );
        tcp_node->data= ( char* ) malloc ( 4096 );
        tcp_node->len=4096;
        memset ( tcp_node->data,'A',tcp_node->len );

        //push成功则增加pushc计数，pushs失败则继续push，直到成功为止
        while (!que.push(tcp_node)) {};
        pushc++;
        //boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(1));
        //boost::thread::sleep(boost::get_system_time()+boost::posix_time::microseconds(1));
        //boost::thread::sleep(boost::get_system_time()+boost::posix_time::milliseconds(1));
    };
}


void thread_get_queue1()
{
    std::cout<<"thread id="<<syscall(SYS_gettid)<<std::endl;
    TcpData* out = nullptr;
    while(true)
    {
        if (que.pop(out)) {
            popc++;
            free(out->data);
            free(out);
        }
    }
}
