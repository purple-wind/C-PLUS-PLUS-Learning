#include<deque>
#include<stdint.h>
#include<iostream>
#include<unistd.h>
#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_map>
#include <malloc.h>

using namespace std;
struct St0
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t e;
};

void test_vector()
{
   vector<St0> d0;
   for(int i = 0; i<100000000; i++)
   {
       St0 st0 = {1,1,1,i,i*i};
       d0.push_back(st0);
   }
   cout<<"after push"<<std::endl;
//   sleep(10);
//   cout<<"begin pop"<<std::endl;
//   while(true)
//   {
//       if(d0.empty())
//           break;
//       d0.pop_front();
//   }
//   cout<<"after pop"<<std::endl;
//   sleep(10);
//   if(d0.size() == 0)
//   {
//       vector<St0> tmp;
//       std::swap(d0, tmp);
//       //d0.swap(tmp);
//       //d0.shrink_to_fit();
//       cout<<"swap"<<std::endl;
//       sleep(10);
//   }
//   cout<<"after swap"<<std::endl;
   sleep(10);
}

void test_deque()
{
   deque<int> d0;
   for(int i = 0; i<10000000; i++)
   {
       d0.push_back(i*i*i);
   }
   cout<<"after push"<<std::endl;
   sleep(10);
//   cout<<"begin pop"<<std::endl;
//   while(true)
//   {
//       if(d0.empty())
//           break;
       d0.pop_front();
//   }
//   cout<<"after pop size="<<d0.size()<<std::endl;
//   sleep(5);

//   {
//       deque<int> tmp;
//       //std::swap(d0, tmp);
//       d0.swap(tmp);
//       //d0.shrink_to_fit();
//       cout<<"d0 size="<<d0.size()<<" tmp size="<<tmp.size()<<std::endl;
//       sleep(5);
//   }
//   cout<<"after swap"<<std::endl;
//   sleep(5);

   d0.clear();
   cout<<"after clear d0 size="<<d0.size()<<std::endl;
   sleep(5);
//   d0.shrink_to_fit();
   cout<<"after shrink_to_fit"<<std::endl;
   sleep(5);
}

void test_list()
{
   list<St0> d0;
   for(int i = 0; i<10000000; i++)
   {
       St0 st0 = {1,1,1,i,i*i};
       d0.push_back(st0);
   }
   cout<<"after push"<<std::endl;
   sleep(5);
   //d0.clear();
   while(true)
   {
       if(d0.empty())
           break;
       d0.pop_front();
   }
   cout<<"after clear"<<std::endl;
   sleep(5);
   malloc_trim(0);
   cout<<"after malloc_trim"<<std::endl;
   sleep(5);
//   {
//       list<St0> tmp;
//       std::swap(d0, tmp);
//       //d0.swap(tmp);
//       cout<<"d0 size="<<d0.size()<< "tmp size="<<tmp.size()<<std::endl;

//       sleep(10);
//   }
//   cout<<"after swap"<<std::endl;
//   sleep(5);
}

void test_map()
{
   map<int, St0> d0;
   for(int i = 0; i<1000000; i++)
   {
       St0 st0 = {1,1,1,i,i*i};
       d0[i] = st0;
   }
   cout<<"after push"<<std::endl;
   sleep(10);
   {
       map<int, St0> tmp;
       swap(d0, tmp);
       //d0.swap(tmp);
       cout<<"swap"<<std::endl;
       sleep(10);
   }
   cout<<"after swap"<<std::endl;
   sleep(10);
}

void test_set()
{
   set<uint64_t> d0;
   for(int i = 0; i<1000000; i++)
   {
       d0.insert(i*i*i);
   }
   cout<<"after push"<<std::endl;
   sleep(10);
   {
       set<uint64_t> tmp;
       swap(d0, tmp);
       //d0.swap(tmp);
       cout<<"swap"<<std::endl;
       sleep(10);
   }
   cout<<"after swap"<<std::endl;
   sleep(10);
}
