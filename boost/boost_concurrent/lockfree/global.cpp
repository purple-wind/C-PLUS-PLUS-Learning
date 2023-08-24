#include"global.h"
#include<boost/lockfree/queue.hpp>
pthread_mutex_t mutexlock;
pthread_rwlock_t  rwlock;
std::map<std::string,std::deque<TcpData*>> tcp_map;
//boost::lockfree::queue对存入其中的元素的要求是元素对象不能有自定义的析构函数，只能使用系统默认的析构函数，否则不支持
//例如标准库的std::string std::shared_ptr等都不支持，因为它们自定义了析构函数
boost::lockfree::queue<TcpData*, boost::lockfree::fixed_sized<false> > que(0);
boost::atomic_int64_t pushc(0),popc(0),pushc_last(0),popc_last(0);
boost::atomic_int64_t temp(0);


//是否生产完毕标志
boost::atomic<bool> done (false);
boost::lockfree::spsc_queue<TcpData, boost::lockfree::capacity<1> > spsc_queue;
