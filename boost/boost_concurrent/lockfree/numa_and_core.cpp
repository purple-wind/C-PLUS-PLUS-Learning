#include <iostream>
#include <signal.h>
#include <syscall.h>
#include <unistd.h>
#include <string.h>
#include<boost/lockfree/spsc_queue.hpp>
//numa分布对性能的影响
//通常情况下把线程绑定到特定的cpu核心上为了提升缓存命中率，减少线程上下文切换，以便于提升性能。
//但是绑核后未必性能都能获得提升，或者绑核后没有获取最大的性能提升。这和numa的分布有关，我们都知道
//cpu访问本地内存比访问远端内粗速度更快。但是如果绑核不对就不能获得最大的性能提升。不同的线程工作方式
//绑核方式也不一样。以下分三种情况分析:
//  1.所有线程使用的内存都是本线程的本地内存，不和其它线程交互内存数据。这种场景下，线程分布在多个numa对应的
//      cpu核上性能最佳。下面代码示例的work，多个work工作内容一样且彼此之间没什么关联，当这些work工作的时候，如果
//      把他们绑定到cpu的兄弟核上，则这些work由于处理的数据不同，一个线程放在cpu中的缓存另外一个线程也用不到，当另一个线程
//      工作的时候就会把这些缓存换出，这样就会造成L2 L3缓存会被大量换进换出，性能低下。而且兄弟核会竞争本地numa上的内存，内存
//      使用效率也会下降。如果每个线程绑定在互不关联的cpu核心上，则每个线程访问自己cpu核对应的内存，内存竞争会减小，其次缓存换进换出的概率也会减小。
//  2.线程之间协同工作，一个线程使用的内存也被另外一个线程使用，这种场景下，共享线程分布在同个numa下的兄弟核性能最佳
//      下面示例的producer-consumer模式,生产者生成的数据通过无锁队列共享给消费者使用，消费者使用的数据内存分配在
//      生产者cpu核对应的numa上，此时如果消费者线程工作在生产者兄弟核上，则他们使用的是本地内存，速度会更快。而且兄弟
//      核的L2 L3及缓存也是共享的，缓存命中率会大大增加，所以性能更好。如果消费者线程工作在其他numa对应的cpu核心上则
//      消费者线程要访问的内存对它来讲就是远端内存，即使用的cpu核和访问的内存之间更远，且缓存会被大量换出，利用率较低。
//  3. 1 2的混合场景，这种场景下需要考虑 1 2两种场景在混合场景下那种占比的趋势更大，采用对应的方式绑核




//本代码编译后的程序使用方法:
//data1=$(cat numa_and_core.cpp) && data2=$(cat numa_and_core.cpp) && time ./a.out 1 2 1000000 "$data1" "$data2"
//把本源码文件的内容作为输入给各个线程去大量的拷贝测试线程绑核方式的性能差异


boost::lockfree::spsc_queue<char*, boost::lockfree::capacity<1000000> > spsc_queue;

struct Ctx{
        int count = 0;
        char* data = nullptr;
        int work_core = 1;
};

void BindCore(int id)
{
    std::cout<<"bind core="<<id<<std::endl;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(id, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
}

static void* work(void* data)
{
    Ctx* ctx = (Ctx*)data;
    BindCore(ctx->work_core);
    uint64_t g_p = 0;
    char* buf0 = new char[4096];
    snprintf(buf0, 4096, "%s", ctx->data);
    for(int i = 0; i< ctx->count; i++)
    {
        char* buf = new char[4096];
        int ret = snprintf(buf, 4096, "%s", buf0);
        g_p += ret;
        delete [] buf;
    }
    delete [] buf0;
    std::cout<<"g_p="<<g_p<<std::endl;
    return nullptr;
}




static void* producer(void* data)
{
    std::cout<<"producer thread id="<<syscall(SYS_gettid)<<std::endl;
    Ctx* ctx = (Ctx*)data;
    BindCore(ctx->work_core);
    uint64_t g_p1 = 0;
    int max_c = ctx->count;
    char* buf0 = new char[4096];
    snprintf(buf0, 4096, "%s", ctx->data);
    for(int i = 0; i < max_c; i++)
    {
        char* buf = new char[4096];
        int ret = snprintf(buf, 4096, "%s", buf0);
        while(!spsc_queue.push(buf)){};
        g_p1 += ret;
    };
    delete [] buf0;
    std::cout<<"g_p1="<<g_p1<<std::endl;

    return nullptr;
}

static void* consumer(void* data)
{
    std::cout<<"consumer thread id="<<syscall(SYS_gettid)<<std::endl;
    Ctx* ctx = (Ctx*)data;
    BindCore(ctx->work_core);
    uint64_t g_p2 = 0;
    int max_c = ctx->count;
    int succ_c = 0;

    char* pop_data = nullptr;
    while(true)
    {
        if(spsc_queue.pop(pop_data))
        {
            char* buf = new char[4096];
            int ret = snprintf(buf, 4096, "%s", (char*)pop_data);
            delete [] pop_data;
            delete [] buf;

            g_p2 += ret;
            ++succ_c;

            if(succ_c == max_c)
                break;
        }
    };

    std::cout<<"g_p2="<<g_p2<<std::endl;

    return nullptr;
}


int main(int argc, char* argv[])
{
    std::cout<<"main thread id="<<syscall(SYS_gettid)<<std::endl;

    //使用原始api启动线程
    pthread_t producer_tid;
    pthread_t consumer_tid;

    Ctx* ctx0 = new Ctx();
    Ctx* ctx1 = new Ctx();
    ctx0->count = std::stod(argv[3]);
    ctx0->data = argv[4];
    ctx0->work_core = std::stoull(argv[1]);

    ctx1->count = std::stod(argv[3]);
    ctx1->data = argv[5];
    ctx1->work_core = std::stoull(argv[2]);

    //pthread_create(&producer_tid, NULL, work, (void*)ctx0);
    //pthread_create(&consumer_tid, NULL, work, (void*)ctx1);



    pthread_create(&producer_tid, NULL, producer, (void*)ctx0);
    pthread_create(&consumer_tid, NULL, consumer, (void*)ctx1);

    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    return 0;
}
