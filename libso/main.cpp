#include<stdio.h>
#include"c.h"
extern void fun_a();
extern void fun_b();

int main()
{
    printf("main g_int address=%p\n", &g_int);
    printf("main g_highfre_lock address=%p\n", &g_highfre_lock);
    printf("main g_highfreq_map address=%p\n", &g_highfreq_map);
    fun_a();
    fun_b();
    return 0;
}
