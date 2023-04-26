#include<stdio.h>
#include"c.h"
//-Bsymbolic参数可以使全局变量优先使用本地符号，即so中使用so自己的
//1.多个共享库中分别定义同名的全局变量，把多个库链接成一个可执行文件时，同名的全局变量只会存在一个(即使分开编译最终用的也是同一个对象)，
// 因为链接器在链接库中的符号时，以先链接的库中的变量为准，后链接的库中的同名全局变量会被忽略。
// 多个cpp文件中定义的同名的全局变量，不以库的方式编译时，直接一起编译链接时会报变量重定义
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
