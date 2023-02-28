#include<exception>
#include<string>
#include<mutex>
#include<iostream>
#include <pthread.h>

/**
*   name:     singleton2.hpp
*   author:   purple-wind
*   email:    purple-wind
*   created:  2023-02-28 17:14:25
*   brief: 懒汉模式
*   懒汉模式需要自己解决线程安全问题，有如下两种办法
*/

/**
 * @brief The SingleTon3 class  局部静态特性的方式实现单实例
 */
class Singleton3
{
    public:
        void Print()
        {
            std::cout<<str<<std::endl;
        }

        static Singleton3* GetInstance()
        {
            //局部静态特性的方式实现单实例,双检锁保护只实例化一个对象
            std::cout<<"address="<<&m_mutex<<std::endl;
            pthread_mutex_lock(&m_mutex);
            static Singleton3 instance;
            m_instance = &instance;
            pthread_mutex_unlock(&m_mutex);
            return m_instance;
        }

    private:
        //禁止构造
        Singleton3()
        {
        }

        //禁止拷贝构造
        Singleton3(Singleton3& rhs) = delete;

        //禁止拷贝赋值
        Singleton3& operator=(Singleton3& rhs) = delete;

        //禁止外部析构
        ~Singleton3()
        {

        }

    private:
        std::string str = "hello Singleton3";
        static pthread_mutex_t m_mutex;
        static Singleton3* m_instance;
};

Singleton3* Singleton3::m_instance = nullptr;
pthread_mutex_t Singleton3::m_mutex;





/**
 * @brief The Singleton4 class 内部类析构Singleton4唯一对象，释放系统资源
 */
class Singleton4
{
    public:
        void Print()
        {
            std::cout<<str<<std::endl;
        }
        static Singleton4* GetInstance()
        {
            //双检锁保护只实例化一个对象
            if ( m_instance == nullptr )
            {
                pthread_mutex_lock ( m_mutex );
                std::cout<<"address="<<m_mutex<<std::endl;
                if ( m_instance == nullptr )
                {
                    m_instance = new Singleton4();
                }
                pthread_mutex_unlock ( m_mutex );
            }
            return m_instance;
        }
    private:
        Singleton4()
        {
            std::cout<<"construct"<<std::endl;
        }
        //该类的唯一作用是用于析构Singleton4唯一对象，用于释放系统资源(例如文件描述符等)
        class Garbo{
            public:
                ~Garbo(){
                    if(Singleton4::m_instance)
                    {
                        delete m_instance;
                        pthread_mutex_destroy(m_mutex);
                    }
                }
        };
        static Garbo garbo;//定义一个静态成员，在程序结束时，系统会调用它的析构函数
        static pthread_mutex_t* m_mutex;
        static Singleton4* m_instance;
    private:
        std::string str = "hello Singleton4";
};

pthread_mutex_t* Singleton4::m_mutex = new pthread_mutex_t();
Singleton4* Singleton4::m_instance = nullptr;
