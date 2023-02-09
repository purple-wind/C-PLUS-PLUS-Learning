#include<iostream>
#include<string>
#include<list>
using namespace std;
class A
{
    public:
        A()
        {
            fun1();
        }
        virtual ~A()
        {
            std::cout<<__FUNCTION__<< std::endl;
        }

        virtual void fun1()
        {
            std::cout<<__FUNCTION__<<" A "<<a<<" "<<(typeid(this) == typeid(A*))<<std::endl;
            fun2();
        }
        virtual void fun2()
        {
            std::cout<< __FUNCTION__<< " A " << (typeid(this) == typeid(A*)) << std::endl;
            fun3();
        }

        virtual void fun3()
        {
            std::cout<<__FUNCTION__<<" A"<<std::endl;
        }
        int a = 10;
};

class B: public A
{
    public:
        ~B()
        {
            std::cout<<__FUNCTION__<<std::endl;
        }
        void fun1()
        {
            std::cout<<__FUNCTION__<<" B"<< std::endl;
            A::fun2();
        }

        void fun2()
        {
            std::cout<<__FUNCTION__<<" B "<<a<<" A::a "<<A::a<<std::endl;
            fun3();
        }

        void fun3()
        {
            std::cout<< __FUNCTION__<<" B " << std::endl;
        }
        void fun4()
        {
            std::cout<< __FUNCTION__<<" B " << std::endl;
        }

    private:
        int a = 100;
};

class C
{
    public:
        virtual void fun0()
        {
            std::cout<<"fun00 this==C* "<<(typeid(this) == typeid(C*))<< " this=" << this<<std::endl;
            std::cout<<"fun00 *this==C "<<(typeid(*this) == typeid(C))<< " this=" << this<<std::endl;
        }

        ~C(){}
    private:
        void* x;
};

class D : public C
{
    public:
        void fun0()
        {
            std::cout<<"fun01 this==C* "<<(typeid(this) == typeid(C*))<< " this=" << this<<std::endl;
            std::cout<<"fun01 this==D* "<<(typeid(this) == typeid(D*))<< " this=" << this<<std::endl;
            std::cout<<"fun01 *this==C "<<(typeid(*this) == typeid(C))<< " this=" << this<<std::endl;
            std::cout<<"fun01 *this==D "<<(typeid(*this) == typeid(D))<< " this=" << this<<std::endl;
        }

        void fun1()
        {
            fun0();
            C::fun0();
        }
};



int main()
{
    //构造B的时候会先构造A，在A的构造函数中this指针是一个内存块，这个内存地址还并不代表一个类对象，
    //当构造函数完成后，这个地址有足够的信息后才表示这是一个类对象。此时还没有B对象，且虚函数表等
    //一系列内容都还未必存在，在此时调用的其它虚函数只能是A类自己的，不会体现多态特性而调用到B中的同名覆盖函数。
    A* classb = (A*)new B;
    //此时调用fun1体现多态特性，调用的是B中的fun1而不是A中的，如果fun1中调用了其它一些列虚函数,只要是
    //在B中覆盖过了的，调用的都是B的。如果在fun1中显示指定调用A中的某个被B覆盖的虚函数（fun2）,此时只有
    //这个fun2是调用A中的，如果fun2调用了在B中的覆盖了的同名虚函数，调用的依然是B中的函数。
    classb->fun1();
    //已知classb是B类型指针，可直接静态转换
    B* bb = static_cast<B*>(classb);
    bb->fun4();
    //动态转换在运行期检查
    B* bb1 = dynamic_cast<B*>(classb);
    bb1->fun4();
    delete classb;



    //    D* classd = new D;
    //    std::cout<<"D address="<<classd<<std::endl;
    //    classd->fun1();
    //    delete classd;

    //    C* classc = new C;
    //    classc->fun0();

    return 0;
}
