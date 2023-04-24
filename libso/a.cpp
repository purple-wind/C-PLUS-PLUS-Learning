double g_d;
#include<stdio.h>
#include"c.h"
void fun_a()
{
    printf("liba.so g_int address=%p\n", &g_int);
    printf("liba.so g_highfre_lock address=%p\n", &g_highfre_lock);
    printf("liba.so g_highfreq_map address=%p\n", &g_highfreq_map);
    g_int = 200;
}
