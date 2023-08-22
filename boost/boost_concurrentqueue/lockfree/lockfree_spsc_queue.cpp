#include "lockfree_spsc_queue.h"


void producer()
{
    TcpData tcp_node;
    memset(tcp_node.data,'A',sizeof(tcp_node.data));
    while(true)
    {
        spsc_queue.push(tcp_node);
    };
}

void consumer()
{
    TcpData tcp_node;
    //当没有生产完毕，则边消费边生产
    while (!done) {
        //只要能弹出元素，就消费
        while (spsc_queue.pop(tcp_node)) {
            popc++;
            //std::cout<<"pop:"<<tcp_node.data<<std::endl;
        };
    };
    //如果生产完毕，则消费
    while (spsc_queue.pop(tcp_node)){
        popc++;
    };
}

