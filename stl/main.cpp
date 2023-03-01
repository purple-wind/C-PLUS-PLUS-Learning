#include"stl_clear.hpp"
#include"queue.hpp"
#include"sequential_container.hpp"
#include"tvector.hpp"
#include"unordered_container.hpp"

int main(int argc, char *argv[])
{
    //容器
    std::cout<<"------------------容器-------------------"<<std::endl;
    vector_test vct_test;
    vct_test.test_index_operator();


    Container test_container;
    test_container.test_assign();
    test_container.test_wsap();
    test_container.my_insert();
    test_container.get_start();

    used1();
    used2();
    used3();


    switch(stoi(argv[1]))
    {
        case 0:
            test_vector();
            cout<<"after return"<<std::endl;
            break;
        case 1:
            test_list();
            cout<<"after return"<<std::endl;
            break;
        case 2:
            test_deque();
            cout<<"after return"<<std::endl;
            break;
        case 3:
            test_map();
            cout<<"after return"<<std::endl;
            break;
        case 4:
            test_set();
            cout<<"after return"<<std::endl;
            break;
    }
    sleep(10);
    return 0;
}
