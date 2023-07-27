#include"forward_declaring_shareptr.h"
struct X
{
        X(int x)
        {
            a = x;
        }

        int a;
};

ForwardDeclar::ForwardDeclar()
{
    //执行此句时需要知道X类型的详细信息，以便于分配内存，所有X的定义一定要在此之前
    m_ptr_x = std::make_shared<X>(100);
    m_p_x = new X(200);
}

ForwardDeclar::~ForwardDeclar()
{
    delete m_p_x;
}

void ForwardDeclar::Print()
{
    std::cout<<m_ptr_x->a<<std::endl;
    std::cout<<m_p_x->a<<std::endl;
}
