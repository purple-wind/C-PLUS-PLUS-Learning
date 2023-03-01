/*柔性数组介绍*/

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
    struct FlexibleArray* a0 = (struct FlexibleArray*)malloc(sizeof(struct FlexibleArray) + 10);
    printf("FlexibleArray sizeof=%lu\n", sizeof(struct FlexibleArray));
    a0->length = 10;
    a0->data[0] = 'a';
    a0->data[1] = 'b';
    for(int i = 0; i < a0->length; i++)
    {
        printf("data[%d]=%c\n",i, a0->data[i]);
    }

    memcpy(a0->data, "0123456789", 10);
    a0->x = 65;
    for(int i = 0; i < a0->length; i++)
    {
        printf("data[%d]=%c\n",i, a0->data[i]);
    }
    printf("FlexibleArray address=%p\n", a0);
    printf("length address=%p\n", &(a0->length));
    printf("data address=%p\n", a0->data);
    printf("x address=%p\n", &(a0->x));

}

