//#include "split_queue.h"

//#include <stdio.h>
//#include <pthread.h>
//#include <string.h>
//#include <stdlib.h>
//#include "stdint.h"

//const int count_per_thread_push = 100000000;

//const float CPU_MHZ = 1596; //use cat /proc/cpuinfo get the value
//const float CPU_tick_count_per_second = CPU_MHZ*1000*1000;

//#define RING_BUFF_SIZE 65536
//#define RING_BUFF_NUM 10

//static __thread int __thread_id__ = -1;

//typedef struct RingBuffer {
//unsigned long long *buffer;
//int head;
//int tail;
//int size;
//int po;
//int pu;
//pthread_mutex_t push_used;
//pthread_mutex_t pop_used;
//} RingBuffer;

//inline bool init_rb(struct RingBuffer* rb, int size) {
//rb->buffer = (unsigned long long *)malloc(sizeof(unsigned long long) * (size + 1));
//if (rb->buffer == NULL) {
//return false;
//}
//rb->head = 0;
//rb->tail = 0;
//rb->po = 0;
//rb->pu = 0;
//pthread_mutex_init(&(rb->push_used), NULL);
//pthread_mutex_init(&(rb->pop_used), NULL);
//rb->size = size + 1;

//return true;
//}

//inline void free_rb_buff(struct RingBuffer* rb) {
//if (rb) {
//if (rb->buffer) {
//free(rb->buffer);
//}
//}
//}

//inline bool rb_push(struct RingBuffer* rb, unsigned long long number) {
//if ((rb->tail + 1) % rb->size == rb->head) {
//return false;
//}
//rb->buffer[rb->tail] = number;
//rb->tail = (rb->tail + 1) % rb->size;
//return true;
//}

//inline bool rb_pop(struct RingBuffer* rb) {
//if (rb->tail == rb->head) {
//return true;
//}
//bool ret = (rb->buffer[rb->head] != 0);
//rb->head = (rb->head + 1) % rb->size;
//return ret;
//}

//struct lock_free_queue {
//void push(unsigned long long pop_time)
//{
//while (__thread_id__ == -1) {
//for(int i = pop_time % RING_BUFF_NUM; i < RING_BUFF_NUM; i = (i + 1) % RING_BUFF_NUM) {
//pthread_mutex_lock(&(rb[i].push_used));
//if (rb[i].pu == 0) {
//rb[i].pu = 1;
//__thread_id__ = i;
//pthread_mutex_unlock(&(rb[i].push_used));
//break;
//}
//pthread_mutex_unlock(&(rb[i].push_used));
//}
//}
//while(!rb_push(rb + __thread_id__, pop_time));
//};

//bool pop()
//{
//while (__thread_id__ == -1) {
//for(int i = 0; i < RING_BUFF_NUM; i++) {
//pthread_mutex_lock(&(rb[i].pop_used));
//if (rb[i].po == 0) {
//rb[i].po = 1;
//__thread_id__ = i;
//pthread_mutex_unlock(&(rb[i].pop_used));
//break;
//}
//pthread_mutex_unlock(&(rb[i].pop_used));
//}
//}

//// if(now%(1000000) == 0) {
//// printf("task get:%u,task write:%u,latency:%lf\n",
//// m_head[now],rdtsc(),(rdtsc()-m_head[now])/CPU_tick_count_per_second);
//// }

//return rb_pop(rb + __thread_id__);
//};

//lock_free_queue()
//{
//for(int i = 0; i < RING_BUFF_NUM; i++) {
//init_rb(rb + i, RING_BUFF_SIZE);
//}
//};

//~lock_free_queue()
//{
//for(int i = 0; i < RING_BUFF_NUM; i++) {
//free_rb_buff(rb + i);
//}
//}

//struct RingBuffer rb[RING_BUFF_NUM];
//};

//void* pop(void* queue)
//{
//lock_free_queue* lfq = (lock_free_queue*)queue;
//do{
//}while(lfq->pop());

//return NULL;
//}

//void* push(void* queue)
//{
//lock_free_queue* lfq = (lock_free_queue*)queue;
//for(int i=0;i<count_per_thread_push/4;++i)
//{
//unsigned long long now = rdtsc();
//lfq->push(now);
//lfq->push(now);
//lfq->push(now);
//lfq->push(now);
//}

//// new add for signal stop
//lfq->push(0);
//return NULL;
//}

////void* push_end(void* queue)
////{
//// lock_free_queue* lfq = (lock_free_queue*)queue;
//// for(int i=0;i<1000;++i)
//// {
//// lfq->push(0);
//// }
////}

//int main(void)
//{
//pthread_t* thread_pop = (pthread_t*) malloc(10*sizeof( pthread_t));
//pthread_t* thread_push = (pthread_t*) malloc(10*sizeof( pthread_t));
//pthread_t* thread_push_end = (pthread_t*) malloc(sizeof( pthread_t));
//lock_free_queue lfq;

//for(int i=0;i<10;++i)
//{
//pthread_create(&thread_push[i],NULL,push,&lfq);
//}

//for(int i=0;i<10;++i)
//{
//pthread_create(&thread_pop[i],NULL,pop,&lfq);
//}

//for(int i=0;i<10;++i) //make push end
//{
//pthread_join(thread_push[i],NULL);
//}

////pthread_create(thread_push_end,NULL,push_end,&lfq); //push end signal

//for(int i=0;i<10;++i) //wait pop quit
//{
//pthread_join(thread_pop[i],NULL);
//}

//if( NULL != thread_pop )
//{
//free(thread_pop);
//thread_pop = NULL;
//}
//if( NULL != thread_push )
//{
//free(thread_push);
//thread_push = NULL;
//}
//if( NULL != thread_push_end )
//{
//free( thread_push_end );
//thread_push_end = NULL;
//}
//}
