#ifndef LOCKFREE_SPSC_QUEUE_H
#define LOCKFREE_SPSC_QUEUE_H
#include "global.h"

void producer();
void consumer();
extern int producer_count;
extern boost::atomic_int consumer_count;
extern boost::atomic<bool> done;
//boost::lockfree::spsc_queue是针对单生产者单消费者模型下做了特殊优化的无锁队列
extern boost::lockfree::spsc_queue<TcpData, boost::lockfree::capacity<1> > spsc_queue;
#endif // LOCKFREE_SPSC_QUEUE_H
