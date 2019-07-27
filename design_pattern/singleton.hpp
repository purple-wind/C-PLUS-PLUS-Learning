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

  static pthread_mutex_t* m_mutex;
  static SingleTon* m_instance;
private:
  std::string str = "hello singleton";
};

pthread_mutex_t* SingleTon::m_mutex = nullptr;
SingleTon* SingleTon::m_instance = nullptr;
#endif // SINGLETON_H
