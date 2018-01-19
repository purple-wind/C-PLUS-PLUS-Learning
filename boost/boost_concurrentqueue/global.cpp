#include"global.h"
#include<boost/lockfree/queue.hpp>
pthread_mutex_t mutexlock;
pthread_rwlock_t  rwlock;
std::map<std::string,std::deque<TcpData*>> tcp_map;
boost::lockfree::queue<TcpData*, boost::lockfree::fixed_sized<false> > que(0);
boost::atomic_int64_t pushc(0),popc(0),pushc_last(0),popc_last(0);
boost::atomic_int64_t temp(0);

