#include "singleton.hpp"
int main(int argc,char* argv[])
{
    SingleTon* instance1 = SingleTon::get_instance();
    std::cout<<"instance1 addr="<<instance1<<std::endl;
    instance1->work();
    return 0;
}
