//饿汉模式本身就是线程安全的
#include<exception>
#include<string>
#include<memory>
#include<mutex>
#include<iostream>

//饿汉模式,普通类型
class Singleton0{
    public:
        static Singleton0* GetInstance()
        {
            return g_singleton;
        }
        static void deleteInstance()
        {
            if(g_singleton)
            {
                delete g_singleton;
                g_singleton = nullptr;
            }
        }
        void Print()
        {
            std::cout<<str<<std::endl;
        }
    private:
        Singleton0()
        {

        }
        ~Singleton0();
        Singleton0(const Singleton0 &single);
        const Singleton0& operator=(const Singleton0 &single);
        static Singleton0 *g_singleton;
        std::string str = "hello Singleton0";
};

Singleton0 * Singleton0::g_singleton = new(std::nothrow) Singleton0();

//饿汉模式,智能指针
class Singleton1{
    public:
        static std::shared_ptr<Singleton1> GetInstance()
        {
            if(!instance)
            {
                std::unique_lock<std::mutex> lock(g_mutex);
                if(!instance)
                {
                    instance = std::shared_ptr<Singleton1>(new Singleton1());
                }
            }
            return instance;
        }

        void Print()
        {
            std::cout<<str<<std::endl;
        }

        ~Singleton1()
        {
            if(instance)
            {
                instance = nullptr;
            }
        }

    private:
        Singleton1()
        {

        }

        Singleton1(const Singleton1 &single);
        const Singleton1& operator=(const Singleton1 &single);

        static std::shared_ptr<Singleton1> instance;
        static std::mutex g_mutex;
        std::string str = "hello Singleton1";
};

std::shared_ptr<Singleton1> Singleton1::instance = nullptr;
std::mutex Singleton1::g_mutex;
