#include "singleton1.hpp"
#include "singleton2.hpp"
#include "observer.hpp"
#include "factory.hpp"
#include "buildder.hpp"

int main(int argc,char* argv[])
{
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

    return 0;
}
