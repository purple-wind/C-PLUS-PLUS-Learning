#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
/**
 * 1.二级指针以及N及指针本质上和一级指针一样，都值存放一个内存地址。多级指针只是在写代码定义类型时才有意义，用于哄骗编译器而已。
 *   实际上一个指针变量是多少级取决于如何初始化这个指针变量(即这个指针变量中存放的是什么地址)。在这个指针变量中存放一个地址即一级指针，存放地址的地址就是二级指针，以此类推多级指针
 */


void test_second_rank_pointer()
{
    printf("start\n");
    uint64_t a = 0xee;
    //a的地址强制转换成uint64_t**类型，然后赋值给c，此时的c虽然定义的是一个二级指针，但是其中存放的是a的地址，本质上
    //是一个一级指针(c是一个假二级指针)，此时对c解引用得到的是a这个变量
    uint64_t**c = (uint64_t**)&a;
    printf("c=%p\n", c);//c存放的是a的地址
    printf("*c=%lu\n", *c);//对c解引用得到的是a这个变量，故打印0xee
    //printf("**c=%p\n", **c); //此句可编译通过，但运行错误。因为c类型是uint64_t**，故编译时可以
    *c = new uint64_t(0xaa);  //分配一块内存，把该内存地址存放到*c中(*c就是a),因为a是uint64_t类型，在64位机器上可以存放的下一个地址大小
    printf("*c=%p\n", *c); //c中存放的就是新分配的这块内存的地址
    printf("**c=%p\n", **c);//此时可以对c二级解引用,**c就是新分配这块内存中存放的内容，即0xaa
    printf("a=%p\n", a);//a就是*c，此时a中存放的就是新分配的这块内存的地址
    printf("a=%lu\n", *(uint64_t*)a);//通过强制类型转换，对a解引用得到a的值就是新分配这块内存中保存的值
}

void test_realloc()
{
    uint64_t** buf = (uint64_t**)malloc(512*8);
    for(int i = 0;i<512;i++)
    {
        auto tmp = new uint64_t(i);
        *(buf + i) = tmp;//因为buf指向的内存是uint64_t类型，所以在64位机器上可存放地址的大小
    }
    printf("buf=%p,buf[0]=%p\n", buf, buf[0]);
    printf("buf+511=%p, buf[511]=%p\n",buf + 511, buf[511]);
    printf("buf+512=%p, buf[512]=%p\n",buf + 512, buf[512]);
    
    //realloc后重新分配了内存，然后把buf中的内容拷贝过去了。当realloc超过原内存大小低于8字节时，不会重新分配内存
    uint64_t** buf2 = (uint64_t**)realloc(buf, 1024*4 + 9);
    printf("buf2=%p, buf2[0]=%p\n", buf2, buf2[0]);
    printf("buf2+511=%p, buf2[0]=%p\n", buf2 + 511, buf2[511]);
    printf("buf2+512=%p, buf2[512]=%p\n", buf2 + 512, buf2[512]);
}

void test_new_delete()
{
    
}

//多维数组的行列
void test_array_row_column()
{
//    int array0[2][3] = {{0,0,0}, {0,0,0}};
    //0 0 0         0 0
    //0 0 0         0 0
    //              0 0
    //2是行 3是列
    //int array0[2][3] = {{0,0}, {0,0}, {0,0}};//编译不过，说明2是行，3是列

    //(*array0 + 1) 前进一个元素
    //(array0 + 1) 前进一行
    //&array0 + 1 前进一个数组全部

    int array1[2][3][4] {  {{0,0,0,0},{0,0,0,0},{0,0,0,0}},  {{0,0,0,0},{0,0,0,0},{0,0,0,0}}  };
    //x,x,x
    //x,x,x
    //x = 0,0,0,0
    int array2[5] = {1,2,3,4,5};
    printf("%p\n", array2);

}
