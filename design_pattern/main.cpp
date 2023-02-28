#include "singleton1.hpp"
#include "singleton2.hpp"

int main(int argc,char* argv[])
{
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

    return 0;
}
