#ifndef FORWARDDECLAR_H
#define FORWARDDECLAR_H

#include<memory>
#include<iostream>
/*shared_ptr、普通指针申明时不需要知道所指向的类型的详细情况,前向申明即可
 *但是必须在定义指针时知道所指向类型的详细信息，以分配内存。例如:std::make_shared<>/new
 */
class X;

class ForwardDeclar
{
    public:
        ForwardDeclar();
        ~ForwardDeclar();
        void Print();
    private:
        std::shared_ptr<X> m_ptr_x;//前向声明可用于shared_ptr,可正常编译通过
        X * m_p_x;//前向声明可用于shared_ptr,可正常编译通过
};

#endif // FORWARDDECLAR_H
