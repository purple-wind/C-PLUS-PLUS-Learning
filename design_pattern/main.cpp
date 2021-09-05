#include "singleton.hpp"
int main(int argc,char* argv[])
{
    SingleTon* instance0 = SingleTon::get_instance();
    std::cout<<"instance0 addr="<<instance0<<std::endl;
    instance0->work();
    
    SingleTon* instance01 = SingleTon::get_instance();
    std::cout<<"instance01 addr="<<instance01<<std::endl;
    instance01->work();
    
    
    SingleTon1* instance1 = SingleTon1::get_instance();
    std::cout<<"instance1 addr="<<instance1<<std::endl;
    instance1->work();
    
    SingleTon1* instance11 = SingleTon1::get_instance();
    std::cout<<"instance11 addr="<<instance11<<std::endl;
    instance11->work();

    return 0;
}
