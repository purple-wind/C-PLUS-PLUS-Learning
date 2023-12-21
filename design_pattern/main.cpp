//设计模式遵循六个原则，一个法则
//6个原则分别是:
    //指开闭原则
    //里氏替换原则
    //依赖倒置原则
    //单一职责原则
    //接口隔离原则
    //合成复用原则
//一个法则是迪米特法则
//这7种设计原则是软件设计模式必须尽量遵循的原则，是设计模式的基础。在实际开发过程中，
//并不是一定要求所有代码都遵循设计原则，而是要综合考虑人力、时间、成本、质量，不刻意追求完美，
//要在适当的场景遵循设计原则。这体现的是一种平衡取舍，可以帮助我们设计出更加优雅的代码结构。

//各种原则要求的侧重点不同，下面我们分别用一句话归纳总结软件设计模式的七大原则，如下表所示。

//设计原则              总结                                              目的
//开闭原则          对扩展开放，对修改关闭                              降低维护带来的新风险
//依赖倒置原则       高层不应该依赖低层，要面向接口编程                    更利于代码结构的升级扩展
//单一职责原则	   一个类只干一件事，实现类要单一                       便于理解，提高代码的可读性
//接口隔离原则	   一个接口只干一件事，接口要精简单一                    功能解耦，高聚合、低耦合
//迪米特法则         不该知道的不要知道，一个类应该保持对其
//                    它对象最少的了解，降低耦合度                      只和朋友交流，不和陌生人说话，减少代码臃肿
//里氏替换原则	不要破坏继承体系，子类重写方法功能发生改变，
//                    不应该影响父类方法的含义防止继承泛滥
//合成复用原则	尽量使用组合或者聚合关系实现代码复用，少使用继承            降低代码耦合




#include "singleton1.hpp"
#include "singleton2.hpp"
#include "observer.hpp"
#include "factory.hpp"
#include "buildder.hpp"
#include "prototype.hpp"
#include "facade.hpp"
#include "bridge.hpp"
int main(int argc,char* argv[])
{

    //==============建造模式=====================

    //单例模式
    std::cout << "单例模式" << std::endl;
    Singleton0* instance0 = Singleton0::GetInstance();
    std::cout<<"instance0 addr="<<instance0<<std::endl;
    instance0->Print();
    
    std::shared_ptr<Singleton1> instance1 = Singleton1::GetInstance();
    std::cout<<"instance1 addr="<<instance1<<std::endl;
    instance1->Print();
    
    
    Singleton3* instance3 = Singleton3::GetInstance();
    std::cout<<"instance1 addr="<<instance3<<std::endl;
    instance3->Print();
    
    Singleton4* instance4 = Singleton4::GetInstance();
    std::cout<<"instance11 addr="<<instance4<<std::endl;
    instance4->Print();





    //Factory

    //简单工厂
    SimpleFactory sim_factory;
    BaseProduct* pr1 = sim_factory.Create("Product1");
    BaseProduct* pr2 = sim_factory.Create("Product2");

    //普通工厂,每增加一个产品需要对应的增加一个工厂
    BaseFactory* factory = new FactoryProduct1();
    pr1 = factory->Create();
    factory = new FactoryProduct2();
    pr2 = factory->Create();

    //抽象工厂,每个工厂对应一个产品大类，每个工厂可以生产产品大类中的多个小类。
    //每增加一个大类，需要增加一个工厂。每增加一个小类需要修改基类和对应的大类的工厂。
    //但是已经写好了的使用工厂基类的客户代码不用改变
    AbstractFactory* abs_factory = new FactoryProductA();
    AbstractProduct0* abs_pr0 = abs_factory->Create0();
    AbstractProduct1* abs_pr1 = abs_factory->Create1();

    abs_factory = new FactoryProductB();
    abs_pr0 = abs_factory->Create0();
    abs_pr1 = abs_factory->Create1();

    //假如上面代码已经写好了，此后又添加了ProductA2，上面的代码不用修改。
    //但是增加了ProductA2后，B工厂也要实现2这种产品
    abs_factory->Create2();


    //建造者模式
    Builder* builder = new ConcreateBuilder1();
    Director director1(builder);
    Product* product = director1.Build();
    std::cout << "part1=" << product->part1 << " part2=" << product->part2 << " part3=" << product->part3 << std::endl;

    builder = new ConcreateBuilder2();
    Director director2(builder);
    product = director2.Build();
    std::cout << "part1=" << product->part1 << " part2=" << product->part2 << " part3=" << product->part3 << std::endl;

    //原型模式
    std::string str = "123";
    ProtoType* p = new ConcreateProtoType(100, &str);
    ProtoType* p1 = p->Clone();
    p1->Show();
    ProtoType* p2 = p->DeepClone();
    p2->Show();



    //==============结构模式=====================

    //桥接模式
    AbstractionImp* imp = new ConcreteAbstractionImpA();
    Abstraction* abs = new RefinedAbstraction(imp);
    abs->Operation();

    //外观模式(门面模式)
    TestKTVMode();



    //==============行为模式=====================

    //观察者模式
    std::cout << "观察者模式" << std::endl;
    Subject0 sub0;
    Observer *obj0 = new Observer0();
    Observer *obj1 = new Observer1();

    sub0.registerObserver(obj0);
    sub0.registerObserver(obj1);
    std::cout << "after register" << std::endl;

    std::cout<< "1" << std::endl;
    sub0.setMeasurtements(1.1, 2.2);
    std::cout<< "2" << std::endl;
    sub0.setMeasurtements(8, 5);


    std::cout<< "3" << std::endl;
    sub0.removeObserver(obj0);
    sub0.setMeasurtements(2.2, 4.4);

    delete obj0;
    delete obj1;


    return 0;
}
