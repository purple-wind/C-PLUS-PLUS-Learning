#ifndef __MY_LOCK_QUEUE_H__

#pragma once
#pragma warning(disable:4996)

#include <boost/thread/mutex.hpp>
//#define USE_LIST

#ifndef USE_LIST
#include <queue>
template<class T>
class enable_queue : public std::queue<T>
{
public:
    void clear()
    {
        std::queue<T>::c.clear();
    }

    bool pop(T& v)
    {
        v = std::queue<T>::front();
        std::queue<T>::pop();
        return true;
    }
};

template<class T>
class enable_safe_queue : public std::queue<T>
{
public:
    void clear()
    {
        std::queue<T>::c.clear();
    }

    bool pop(T& v)
    {
        v = std::queue<T>::front();
        std::queue<T>::pop();
        return true;
    }

    void safe_pop(T& v)
    {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        this->pop(v);
    }

    void safe_push(T& v)
    {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        std::queue<T>::push(v);
    }

    void safe_swap(enable_queue<T> q)
    {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        swap(q);
    }

private:
    boost::mutex m_mutex;
};

#else
#include <list>

template<class T>
class enable_queue : public std::list<T>
{
public:
    bool pop(T& v)
    {
        v = front();
        erase(begin());
        return true;
    }

    void push(T& v)
    {
        push_back(v);
    }
};

template<class T>
class enable_safe_queue : public std::queue<T>
{
public:
    bool pop(T& v)
    {
        v = front();
        erase(begin());
        return true;
    }

    void push(T& v)
    {
        push_back(v);
    }

    void safe_pop(T& v)
    {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        pop(v);
    }

    void safe_push(T& v)
    {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        push(v);
    }

    void safe_swap(enable_safe_queue<T> q)
    {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        swap(q);
    }
private:
    boost::mutex m_mutex;
};

#endif





