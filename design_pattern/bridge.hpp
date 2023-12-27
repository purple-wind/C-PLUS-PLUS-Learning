#ifndef BRIDGE_HPP
#define BRIDGE_HPP
//Bridge 模式又叫做桥接模式，是结构模式的设计模式之一。
//Bridge 模式基于类的最小设计原则，通过使用封装，聚合以及继承等行为来让不同的类承担不同的责任。
//它的主要特点是把抽象（abstraction）与行为实现（implementation）分离开来，从而可以保持各部分的独立性以及应对它们的功能扩展
using namespace std;
class AbstractionImp
{
    public:
        AbstractionImp()
        {
        }
        virtual ~AbstractionImp()
        {

        }
        virtual void Operation() = 0;
};

class ConcreteAbstractionImpA:public AbstractionImp
{
    public:
        ConcreteAbstractionImpA()
        {
        }

        ~ConcreteAbstractionImpA()
        {

        }
        void Operation()
        {
            cout<<"ConcreteAbstractionImpA...."<<endl;
        }
};

class ConcreteAbstractionImpB:public AbstractionImp
{
    public:
        ConcreteAbstractionImpB()
        {
        }
        ~ConcreteAbstractionImpB()
        {

        }
        void Operation()
        {
            cout<<"ConcreteAbstractionImpB...."<<endl;
        }
};


class Abstraction
{
    public:
        virtual ~Abstraction()
        {

        }
        virtual void Operation() = 0;
};

class RefinedAbstraction:public Abstraction
{
    public:
        RefinedAbstraction(AbstractionImp* imp)
        {
            _imp = imp;
        }
        ~RefinedAbstraction()
        {

        }
        void Operation()
        {
            _imp->Operation();
        }
    private:
        AbstractionImp* _imp;
};
#endif // BRIDGE_HPP
