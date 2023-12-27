#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP
//使用复制原型对象的方法来创建对象，使对象有赋值自己的能力。
//使用原型模式创建出来的对象具有与原对象一样的数据
//其实拷贝赋值运算符和该模式有相似功能

#include<string>
class ProtoType{
    public:
        virtual ProtoType* Clone() = 0;
        virtual ProtoType* DeepClone() = 0;
        virtual void Show() = 0;
};

class ConcreateProtoType: public ProtoType
{
    public:
        ConcreateProtoType()
        {
        }

        ConcreateProtoType(int i, std::string* str)
        {
            m_i = i;
            m_str = str;
        }

        ProtoType* Clone()
        {
            ConcreateProtoType* x = new ConcreateProtoType();
            *x = *this;
            return x;
        }

        ProtoType* DeepClone()
        {
            ConcreateProtoType* x = new ConcreateProtoType();
            x->m_str = new std::string();
            x->m_i = m_i;
            *x->m_str = *m_str;
            return x;
        }

        void Show()
        {
            std::cout << "i=" << m_i << " str=" << *m_str << std::endl;
        }
    private:
        int m_i = 0;
        std::string* m_str = nullptr;
};

#endif // PROTOTYPE_HPP
