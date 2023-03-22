/*柔性数组介绍
 * 定义数组长度为0的数组为柔性数组
 * 使用该类型数组时必须分配足够大的内存供使用.和指针不同的是柔性数组名本身不占空间。
 * 当柔性数组出现在结构体中时，最好放在结构体末尾。这样该数组占用的空间就在结构体末尾的位置
 * 当柔性数组后面还有字段时，柔性数组和后面的第一个字段共享内存，操作柔性数组实际上影响的后面
 * 字段占用的内存
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct FlexibleArray
{
    size_t length;
    char data[0];
    int x;
};

void test_flexible_array()
{
    struct FlexibleArray* a0 = (struct FlexibleArray*)malloc(sizeof(struct FlexibleArray));
    printf("FlexibleArray sizeof=%lu\n", sizeof(struct FlexibleArray));
    a0->length = 10;
    a0->data[0] = 'a';
    a0->data[1] = 'b';
    for(int i = 0; i < a0->length; i++)
    {
        printf("data[%d]=%c\n",i, a0->data[i]);
    }

    memcpy(a0->data, "0123456789", 10);
    for(int i = 0; i < a0->length; i++)
    {
        printf("data[%d]=%c\n",i, a0->data[i]);
    }

    a0->x = 65;
    for(int i = 0; i < a0->length; i++)
    {
        printf("data[%d]=%c\n",i, a0->data[i]);
    }
    printf("x=%d\n", a0->x);

    a0->data[0] = 3;

    printf("FlexibleArray address=%p\n", a0);
    printf("length address=%p\n", &(a0->length));
    printf("data address=%p\n", a0->data);
    printf("data[0] address=%p\n", &a0->data[0]);
    printf("data[1] address=%p\n", &a0->data[1]);
    printf("x address=%p,x=%d\n", &(a0->x), a0->x);

}

