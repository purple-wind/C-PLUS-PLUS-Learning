#ifndef __C_H__
#define __C_H__
#include<unordered_map>
#include<tuple>
#include<mutex>
extern int g_int;
extern std::mutex g_lock;
extern std::unordered_map<uint32_t, std::tuple<time_t, int, bool> > g_map;
#endif
