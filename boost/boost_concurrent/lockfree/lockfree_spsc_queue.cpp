#include <iostream>
#include <sys/syscall.h>
#include "global.h"
#include "lockfree_spsc_queue.h"
void producer()
{
    std::cout<<"producer thread id="<<syscall(SYS_gettid)<<std::endl;
    TcpData tcp_node;
    tcp_node.data = "AAAAA";
    tcp_node.len = 5;
    while(true)
    {
        while(!spsc_queue.push(tcp_node)){};
        pushc++;
    };
}

void consumer()
{
    std::cout<<"consumer thread id="<<syscall(SYS_gettid)<<std::endl;
    TcpData tcp_node;

    while(true)
    {
        if(spsc_queue.pop(tcp_node))
        {
            popc++;
        }
    };
}

