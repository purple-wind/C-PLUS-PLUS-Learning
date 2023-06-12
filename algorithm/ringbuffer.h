#ifndef RINGBUFFER_H
#define RINGBUFFER_H


class RingBuffer
{
    public:
        RingBuffer();
};



#pragma once
#include<stdio.h>
#include<stdlib.h>   //引入malloc动态分配内存
#include<stdint.h>  //引入uint32_t，32位无符号整形
#include<string.h>  //引入memcpy内存拷贝函数

void InitRingBuffer();
void FreeRingBuffer();
int WriteRingBuffer(uint32_t *pData,int Data_Size);
int ReadRingBuffer(uint32_t* pData, int Data_Size);
int GetRingBufferValidSize();
int TestRingbuffer();
#endif // RINGBUFFER_H
