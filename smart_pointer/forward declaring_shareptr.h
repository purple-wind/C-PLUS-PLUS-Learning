#ifndef XYZ_H
#define XYZ_H

#include <memory>
using namespace std;

class X;

class xyz
{
    public:
        xyz();
        std::shared_ptr<X> m_ptr_x;//前向声明可用于shared_ptr,可正常编译通过
};

#endif // XYZ_H
