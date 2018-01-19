#include <iostream>
#include <boost/lockfree/queue.hpp>
#include <boost/threadpool.hpp>
#include <signal.h>
#include "global.h"
#include "lockfree_queue.h"
#include "lockfree_spsc_queue.h"
void cb(int sig)
{
    if(sig==SIGALRM)
    {
        std::cout<<"------------------"<<std::endl;
//        std::cout<<"pushc="<<pushc<<std::endl;
        std::cout<<"push offset="<<pushc-pushc_last<<std::endl;
//        std::cout<<"popc ="<<popc<<std::endl;
        std::cout<<"pop offset="<<popc-popc_last<<std::endl;
        pushc_last.store(pushc);
        popc_last.store(popc);
//        exit(0);
        alarm(1);
    }
}
int main()
{
   signal(SIGALRM,cb);
   alarm(1);
   
    boost::threadpool::pool thread_pool(4);
    thread_pool.schedule(&Thread_GetQueue1);
    thread_pool.schedule(&Thread_GetQueue1);
    thread_pool.schedule(&Thread_GetQueue1);
    thread_pool.schedule(&Thread_SetQueue1);
    thread_pool.wait();


//    std::cout << "boost::lockfree::queue is ";
//    if (!spsc_queue.is_lock_free())
//        std::cout << "not ";
//    std::cout << "lockfree" << std::endl;

//    thread_pool.schedule(&producer);
//    thread_pool.schedule(&consumer);

//    pthread_t producer_tid;
//    pthread_t consumer_tid;

//    pthread_create(&producer_tid, NULL, producer, NULL);
//    pthread_create(&consumer_tid, NULL, consumer, NULL);

//    //wait producer
//    pthread_join(producer_tid, NULL);
//        done = true;
//    //wait consumer
//    pthread_join(consumer_tid, NULL);

    return 0;
}

