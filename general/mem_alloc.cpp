#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

void test_realloc()
{
    uint64_t** buf = (uint64_t**)malloc(4096);
    for(int i = 0;i<512;i++)
    {
        auto tmp = new uint64_t(i);
        printf("%p\n", tmp);
        *(buf + i) = tmp;
    }

    uint32_t* buf2 = (uint32_t*)malloc(1024);
    uint64_t** buf3 = (uint64_t**)realloc(buf, 1024*8);
    printf("buf1[0]=%lu\n", buf3[0]);
}
