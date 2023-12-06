#include "singleton1.hpp"
#include "singleton2.hpp"
#include "observer.hpp"

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




    return 0;
}
