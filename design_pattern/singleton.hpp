/*
 * Copyright 2019 zc <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SINGLETON_H
#define SINGLETON_H
#include <pthread.h>
#include <iostream>
/**
 * @todo write docs
 */
class SingleTon
{
public:
  void work()
  {
    std::cout<<str<<std::endl;
  };
  static SingleTon* get_instance()
  {
    if ( m_instance == nullptr )
      {
        pthread_mutex_lock ( m_mutex );
        if ( m_instance == nullptr )
          {
            m_instance = new SingleTon();
          }
        pthread_mutex_unlock ( m_mutex );
      }
    return m_instance;
  }
private:
  SingleTon()
  {
    m_mutex = new pthread_mutex_t();
    pthread_mutex_init ( m_mutex,0 );
  }
  //该类的唯一作用是用于析构SingleTon唯一对象，用于释放系统资源(例如文件描述符等)  
  class Garbo{
    public:
        ~Garbo(){
            if(SingleTon::m_instance)
            {
                delete m_instance;
                pthread_mutex_destroy(m_mutex);
            }
        }
  };
  static Garbo garbo;//定义一个静态成员，在程序结束时，系统会调用它的析构函数
  static pthread_mutex_t* m_mutex;
  static SingleTon* m_instance;
private:
  std::string str = "hello singleton";
};

pthread_mutex_t* SingleTon::m_mutex = nullptr;
SingleTon* SingleTon::m_instance = nullptr;




/**
* @projectName:	SingleTon1
* @author:	zhouchao
* @email:	zhouchao@act-telecom.com
* @date:	2020-08-05
* @brief: 内部静态变量的懒汉单例（C++11 线程安全）,代码量最少的方式
*/
class SingleTon1
{
public:
    void work()
    {
        std::cout<<str<<std::endl;
    }

    static SingleTon1* get_instance()
    {
        //局部静态特性的方式实现单实例
        static SingleTon1 instance;
        return instance;
    }
private:
    //禁止构造
    SingleTon1()
    {
        m_mutex = new pthread_mutex_t();
        pthread_mutex_init ( m_mutex,0 );
    }

    //禁止拷贝构造
    SingleTon1(SingleTon1& rhs){

    }

    //禁止拷贝赋值
    SintleTon1& operator=(SingleTon1& rhs)
    {

    }

    //禁止外部析构
    ~SingleTon1()
    {

    }

private:
    std::string str = "hello singleton";
};


#endif // SINGLETON_H
