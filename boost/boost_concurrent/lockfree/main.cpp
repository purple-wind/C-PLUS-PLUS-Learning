#include <iostream>
#include </usr/include/boost/threadpool/boost/threadpool.hpp>
#include <signal.h>
#include <syscall.h>
#include "global.h"
#include "lockfree_queue.h"
#include "lockfree_spsc_queue.h"
void cb(int sig)
{
    //统计1s内入队数量和出队数量
    if(sig==SIGALRM)
    {
        std::cout<<"------------------"<<std::endl;
        std::cout<<"push offset="<<pushc-pushc_last<<std::endl;
        std::cout<<"pop  offset="<<popc-popc_last<<std::endl;
        pushc_last.store(pushc);
        popc_last.store(popc);
        alarm(1);
    }
}

void test0()
{
    //单生产者多消费者通过boost::lockfree::queue交互数据
    //线程池容量为3，在thread_pool时启动3个线程，即是没有任务也会启动
    boost::threadpool::pool thread_pool(3);
    //以下3个任务永远不会结束，一直占用线程
    thread_pool.schedule(&thread_set_queue1);//执行入队任务
    thread_pool.schedule(&thread_get_queue1);//执行出队任务
    thread_pool.schedule(&thread_get_queue1);//执行出队任务
    std::cout<<"pend="<<thread_pool.pending()<<std::endl;
    std::cout<<"empty="<<thread_pool.empty()<<std::endl;
    thread_pool.wait();
}

void test1()
{
    //单生产者单消费者通过boost::lockfree::spsc_queue交互数据
    boost::threadpool::pool thread_pool(2);
    std::cout << "boost::lockfree::queue is ";
    if (!spsc_queue.is_lock_free())
        std::cout << "not ";
    std::cout << "lockfree" << std::endl;

    thread_pool.schedule(&producer);
    thread_pool.schedule(&consumer);


    ////使用原始api启动线程
    //pthread_t producer_tid;
    //pthread_t consumer_tid;

    //pthread_create(&producer_tid, NULL, producer, NULL);
    //pthread_create(&consumer_tid, NULL, consumer, NULL);

    ////wait producer
    //pthread_join(producer_tid, NULL);
    //    done = true;
    ////wait consumer
    //pthread_join(consumer_tid, NULL);
}


int main()
{
    std::cout<<"main thread id="<<syscall(SYS_gettid)<<std::endl;

    signal(SIGALRM,cb);
    alarm(1);

    test0();
//    test1();

    return 0;
}
