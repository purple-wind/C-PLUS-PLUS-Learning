#include<stdio.h>
#include"c.h"
//-Bsymbolic参数可以使全局变量优先使用本地符号，即so中使用so自己的
extern void fun_a();
extern void fun_b();
extern double g_d;
int g_int;
int main()
{
    printf("main g_int address=%p, v=%d\n", &g_int, g_int);
    printf("main g_d address=%p, v=%f\n", &g_d, g_d);
    printf("main g_lock address=%p\n", &g_lock);
    printf("main g_map address=%p\n", &g_map);
    fun_a();
    fun_b();
    return 0;
}
