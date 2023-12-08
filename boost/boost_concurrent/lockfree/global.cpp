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
boost::lockfree::spsc_queue<TcpData, boost::lockfree::capacity<1> > spsc_queue;



















#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
//无锁线程安全队列

template<class T>
class fast_safe_queue : public boost::lockfree::spsc_queue<T>
{
public:
    //queue必须先定义队列数量 过大会初始化很慢
    fast_safe_queue(uint16_t maxqueue = std::numeric_limits<uint16_t>::max())
        :boost::lockfree::spsc_queue<T>(maxqueue)
    {

    }
    ~fast_safe_queue()
    {
        //clear();
    }


    //必须在停止使用后调用 否则无法完全清理掉
    void clear()
    {
        T temp;
        while(!boost::lockfree::spsc_queue<T>::empty())
        {
            if(!boost::lockfree::spsc_queue<T>::pop(temp))
                break;
        }
    }
};

template<class T>
class fast_count_queue : public boost::lockfree::spsc_queue<T>
{
public:
    //queue必须先定义队列数量 过大会初始化很慢
    fast_count_queue(uint16_t maxqueue = std::numeric_limits<uint16_t>::max())
        :boost::lockfree::spsc_queue<T>(maxqueue),m_count(0)
    {

    }
    ~fast_count_queue()
    {
        //clear();
    }

    //必须在停止使用后调用 否则无法完全清理掉
    void clear()
    {
        T temp;
        while(!boost::lockfree::spsc_queue<T>::empty())
        {
            if(!safe_pop(temp))
                break;
        }
    }

    bool safe_pop(T& v)
    {
        if(boost::lockfree::spsc_queue<T>::pop(v))
        {
            m_count--;
            return true;
        }
        return false;
    }

    bool safe_push(const T& v)
    {
        if(boost::lockfree::spsc_queue<T>::push(v))
        {
            m_count++;
            return true;
        }
        return false;
    }

    int size()
    {
        return m_count;
    }

private:
    boost::atomic_int m_count;
};

//释放资源时可能出问题
template<class T>
class fast_mutli_queue : public boost::lockfree::queue<T>
{
public:
    //queue必须先定义队列数量 过大会初始化很慢
    fast_mutli_queue(uint16_t maxqueue = std::numeric_limits<uint16_t>::max())
        :boost::lockfree::queue<T>(maxqueue)
    {

    }
    ~fast_mutli_queue()
    {
        //clear();
    }


    //必须在停止使用后调用 否则无法完全清理掉
    void clear()
    {
        T temp;
        while(!boost::lockfree::queue<T>::empty())
        {
            if(!boost::lockfree::queue<T>::pop(temp))
                break;
        }
    }
};

#endif // __MY_LOCKFREE_QUEUE_H__
