#include<stdio.h>
#include"c.h"

void fun_b()
{
    printf("libb.so g_int address=%p\n", &g_int);
    printf("libb.so g_highfre_lock address=%p\n", &g_highfre_lock);
    printf("libb.so g_highfreq_map address=%p\n", &g_highfreq_map);
    g_int = 300;
}
