#include<stdio.h>
#include"c.h"
double g_d = 2.2;
void fun_b()
{
    printf("libb.so g_int address=%p, v=%d\n", &g_int, g_int);
    printf("libb.so g_d address=%p, v=%f\n", &g_d, g_d);
    printf("libb.so g_highfre_lock address=%p\n", &g_highfre_lock);
    printf("libb.so g_highfreq_map address=%p\n", &g_highfreq_map);
    g_int = 300;
}
