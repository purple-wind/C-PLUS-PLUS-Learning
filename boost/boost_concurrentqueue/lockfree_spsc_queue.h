#ifndef LOCKFREE_SPSC_QUEUE_H
#define LOCKFREE_SPSC_QUEUE_H
#include "global.h"

void producer();
void consumer();
extern int producer_count;
extern boost::atomic_int consumer_count;
extern boost::atomic<bool> done;
extern boost::lockfree::spsc_queue<TcpData, boost::lockfree::capacity<1> > spsc_queue;
#endif // LOCKFREE_SPSC_QUEUE_H
