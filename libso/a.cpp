#include<stdio.h>
#include"c.h"
double g_d = 1.1;
void fun_a()
{
    printf("liba.so g_int address=%p, v=%d\n", &g_int, g_int);
    printf("liba.so g_d address=%p, v=%f\n", &g_d, g_d);
    printf("liba.so g_highfre_lock address=%p\n", &g_highfre_lock);
    printf("liba.so g_highfreq_map address=%p\n", &g_highfreq_map);
    g_int = 200;
}
