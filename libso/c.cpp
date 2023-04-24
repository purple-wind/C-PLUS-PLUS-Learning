#include"c.h"
int g_int = 10000;
std::mutex g_highfre_lock;
std::unordered_map<uint32_t, std::tuple<time_t, int, bool> > g_highfreq_map;
