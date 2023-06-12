#include "ringbuffer.h"
#include <iostream>

RingBuffer::RingBuffer()
{

}




#define BUFFER_SIZE 16  //环形存储区长度

uint32_t* pHead = NULL; //环形缓冲区首地址
uint32_t* pTail = NULL; //环形缓冲区尾地址
uint32_t* pRead = NULL; //读指针
uint32_t* pWrite = NULL; //写指针
int BUFFER_VALID_SIZE; //环形存储区存储的数据大小

//初始化环形缓冲区
void InitRingBuffer()
{
    if (pHead == NULL)
    {
        pHead = (uint32_t*)malloc(BUFFER_SIZE);
    }
    pRead = pHead;
    pWrite = pHead;
    pTail = pHead + BUFFER_SIZE;
    BUFFER_VALID_SIZE = 0;
}
//释放环形缓冲区
void FreeRingBuffer()
{
    if (pHead != NULL) //当存在缓冲区时
    {
        free(pHead);  //释放
    }
    pHead = NULL;  //重新令环形器起始地址为空
    BUFFER_VALID_SIZE = 0;
}
//写命令
int WriteRingBuffer(uint32_t* pData, int Data_Size)
{
    if (pHead == NULL)  //缓冲区未初始化
    {
        printf("Writing Failed! The ringbuffer is not inited!\n");
        return -1;
    }
    if (Data_Size > BUFFER_SIZE)  //加入数据过多
    {
        printf("Writing Failed! The input data size exceeds the ringbuffer size!\n");
        return -2;
    }
    if (pWrite+Data_Size>pTail)
        //将数据存入缓冲区，但是数据需要分成两段
    {
        int Data_Part1 = pTail - pWrite; //存放在靠近尾部的Data部分
        int Data_Part2 = Data_Size - Data_Part1;//存放在靠近头部的Data部分
        memcpy(pWrite, pData, Data_Part1 * sizeof(uint32_t));
        memcpy(pHead, pData+Data_Part1, Data_Part2 * sizeof(uint32_t));
        pWrite = pHead + Data_Part2; //更新写指针
        BUFFER_VALID_SIZE = Data_Size;
    }
    else //不用分段
    {
        memcpy(pWrite, pData, Data_Size * sizeof(uint32_t));
        pWrite += Data_Size;//更新写指针
        BUFFER_VALID_SIZE += Data_Size;
    }
    return 0;
}
//读命令
int ReadRingBuffer(uint32_t* pData, int Data_Size)
{
    if (pHead == NULL)  //缓冲区未初始化
    {
        printf("Reading Failed! The ringbuffer is not inited!\n");
        return -1;
    }

    if (Data_Size > pTail-pHead)  //读出数据过多，超出BUFFER大小
    {
        printf("Reading Failed! The reading data size exceeds the ringbuffer size!\n");
        return -2;
    }
    //无数据读出
    if (Data_Size == 0)
    {
        printf("Reading Failed! No data exists!\n");
        return 0;
    }
    //判断是否需要分成两段读出
    if (pRead + Data_Size > pTail)
    {
        int Data_Part1 = pTail - pRead;
        int Data_Part2 = Data_Size - Data_Part1;
        memcpy(pData, pRead, Data_Part1 * sizeof(uint32_t));
        memcpy(pData + Data_Part1, pHead, Data_Part2 * sizeof(uint32_t));
        pRead = pHead + Data_Part2;
        BUFFER_VALID_SIZE -= Data_Size;
    }
    else
    {
        memcpy(pData, pRead, Data_Size * sizeof(uint32_t));
        pRead += Data_Size;
        BUFFER_VALID_SIZE -= Data_Size;
    }
    return 1;
}
//获取当前缓冲区有效长度，即存储的数据个数
int GetRingBufferValidSize()
{
    return BUFFER_VALID_SIZE;
}



int TestRingbuffer()
{
    //InitRingBuffer();
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Input your choice:" << std::endl;
    std::cout << "1. Initializatize the ring buffer." << std::endl;
    std::cout << "2. Delete the ring buffer." << std::endl;
    std::cout << "3. Write the ring buffer." << std::endl;
    std::cout << "4. Read the ring buffer." << std::endl;
    std::cout << "---------------------------------" << std::endl;
    int choice;

    int Len;   //存储当前环形缓冲区的数据长度
    uint32_t ReadData[50];  //存储读出的数据
    uint32_t data[5] = {1,2,3,4,5,};   //假设有5个读入的数据
    int Data_Size = 5;  //数据大小，占20个字节

    while (1)
    {
        std::cin >> choice;
        switch (choice)
        {
            case 1: InitRingBuffer();
                std::cout << "缓冲区初始化成功！" << std::endl;
                break;
            case 2: FreeRingBuffer();
                std::cout << "缓冲区释放成功！" << std::endl;
                return 1;
            case 3:
                std::cout << "执行数据拷贝！" << std::endl;
                WriteRingBuffer(data,  Data_Size);
                std::cout << "当前缓冲区存储的数据个数：" << GetRingBufferValidSize() << std::endl;
                break;
            case 4:
                Len = GetRingBufferValidSize();
                std::cout << "当前缓冲区存储的数据个数：" << Len << std::endl;
                ReadRingBuffer(ReadData, Data_Size);
                if (Len > 0)
                {
                    std::cout << "读取环形存储区的数据为：" << std::endl;
                    for (int i = 0; i < Len; i++)
                    {
                        std::cout << ReadData[i] << std::endl;
                    }
                }
                else
                {
                    std::cout << "当前缓冲区无数据！" << std::endl;
                }
                break;
            default:
                break;
        }
    }
    system("pause");
    return 1;
}
