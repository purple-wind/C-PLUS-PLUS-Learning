#ifndef STRUCT_HEADER_H
#define STRUCT_HEADER_H
#include<stdint.h>
#include<map>
#include<deque>
#include<boost/lockfree/queue.hpp>
#include<boost/lockfree/spsc_queue.hpp>
#include<boost/atomic.hpp>
struct tuple4
{
  u_short source;
  u_short dest;
  u_int saddr;
  u_int daddr;
};

struct TcpData
{
    struct tuple4 addr={0};
    int status=-1;
    uint64_t src_mac=0;
    uint64_t dst_mac=0;
    char* data=nullptr;
    size_t len=0;
};


extern boost::atomic_int64_t pushc,popc,pushc_last,popc_last;
extern pthread_mutex_t mutexlock;
extern pthread_rwlock_t  rwlock;
extern std::map<std::string,std::deque<TcpData*>> tcp_map;
extern boost::lockfree::queue<TcpData*, boost::lockfree::fixed_sized<false> > que;
extern boost::atomic_int64_t temp;
#endif // STRUCT_HEADER_H
