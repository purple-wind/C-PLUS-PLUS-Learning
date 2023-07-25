/**
 * 1.动态绑定只有使用基类指针指向子类对象，且用基类指针调用被覆盖了的虚函数才会体现出来(指针同理).
 *      使用指向子类对象的指针调用虚函数，调用基于静态关系类型，即调用子类自己的函数(指针同理)
 *      使用指向基类对象的指针调用虚函数，调用关系基于静态类型，即调用基类自己的函数(指针同理)
 * 2.具有多态关系的子类与基类，在子类的构造函数中如果调用了被覆盖的虚函数，只会调用基类自己的版本，不会体现多态
 * 3.
 */
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
            fun0();//此处调用的是D自己的fun0(),基于静态类型调用,故this是D*类型,*this对应的对象是D
            C::fun0();//此处调用的是C的fun0(),基于静态类型调用.故在fun0()内部this指针是C*,但是*this是D
            //this->C::fun0();//等价上面一句
        }
};



int main()
{
    //构造B的时候会先构造A，在A的构造函数中this指针是一个内存块，这个内存地址还并不代表一个类对象，
    //当构造函数完成后，这个地址有足够的信息后才表示这是一个类对象。此时还没有B对象和虚函数表等
    //一系列内容都还未必存在，在此时调用的其它虚函数只能是A类自己的，不会体现多态特性而调用到B中的同名覆盖函数。
    std::cout<<"------on constructor-------------"<<std::endl;
    A* classb = (A*)new B;
    //此时调用fun1体现多态特性，调用的是B中的fun1而不是A中的，如果fun1中调用了其它一系列虚函数,只要是
    //在B中覆盖过了的，调用的都是B的。如果在fun1中显示指定调用A中的某个被B覆盖的虚函数（fun2）,此时只有
    //这个fun2是调用A中的，如果fun2调用了在B中的覆盖了的同名虚函数，调用的依然是B中的函数。
    std::cout<<"------after constructor----------"<<std::endl;
    classb->fun1();
    std::cout<<"------cast----------"<<std::endl;
    //已知classb是B类型指针，可直接静态转换
    B* bb = static_cast<B*>(classb);
    bb->fun4();
    //动态转换在运行期检查(向下造型)
    B* bb1 = dynamic_cast<B*>(classb);
    bb1->fun4();
    delete classb;



    std::cout<<"-------------------"<<std::endl;
    D* classd = new D;
    std::cout<<"D address="<<classd<<std::endl;
    classd->fun1();
    delete classd;
    //out:
    //D address=0x55dd0f161eb0
    //fun01 this==C* 0 this=0x55dd0f161eb0
    //fun01 this==D* 1 this=0x55dd0f161eb0
    //fun01 *this==C 0 this=0x55dd0f161eb0
    //fun01 *this==D 1 this=0x55dd0f161eb0
    //fun00 this==C* 1 this=0x55dd0f161eb0 
    //fun00 *this==C 0 this=0x55dd0f161eb0
    
    
    
    std::cout<<"-------------------"<<std::endl;
    C* classc = new C;
    classc->fun0();//此处调用的是C自己的fun0(),基于静态类型的调用
    //out:    
    //fun00 this==C* 1 this=0x55dd0f161eb0
    //fun00 *this==C 1 this=0x55dd0f161eb0
    
    std::cout<<"-------------------"<<std::endl;
    C* c0 = new D;
    c0->fun0();
    std::cout<<"c0==C* "<<(typeid(c0) == typeid(C*))<< " this=" << c0<<std::endl;//true,此处typeid获取到的是静态类型
    std::cout<<"*c0==D* "<<(typeid(*c0) == typeid(D))<< " this=" << c0<<std::endl;
    //out:    
    //fun01 this==C* 0 this=0x55dd0f1622e0
    //fun01 this==D* 1 this=0x55dd0f1622e0
    //fun01 *this==C 0 this=0x55dd0f1622e0
    //fun01 *this==D 1 this=0x55dd0f1622e0
    //c0==C* 1 this=0x55dd0f1622e0
    //*c0==D* 1 this=0x55dd0f1622e0
    
    
    
    std::cout<<"-------------------"<<std::endl;
    C* c1 = c0;
    c1->fun0();
    std::cout<<"c1==C* "<<(typeid(c1) == typeid(C*))<< " this=" << c1<<std::endl;//true,此处typeid获取到的是静态类型
    std::cout<<"*c1==D* "<<(typeid(*c1) == typeid(D))<< " this=" << c1<<std::endl;
    //out:    
    //fun01 this==C* 0 this=0x55dd0f1622e0
    //fun01 this==D* 1 this=0x55dd0f1622e0
    //fun01 *this==C 0 this=0x55dd0f1622e0
    //fun01 *this==D 1 this=0x55dd0f1622e0
    //c1==C* 1 this=0x55dd0f1622e0
    //*c1==D* 1 this=0x55dd0f1622e0

    return 0;
}
