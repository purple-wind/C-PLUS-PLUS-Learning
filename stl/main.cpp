#include"stl_clear.hpp"
#include"queue.hpp"
#include"sequential_container.hpp"
#include"tvector.hpp"
#include"unordered_container.hpp"
#include"priority_queue.hpp"

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


    //    struct gre
    //    {
    //            bool operator()(int x, int y)
    //            {
    //                std::cout<<"x="<<x<<std::endl;
    //                std::cout<<"y="<<y<<std::endl;

    //                if(y>x)
    //                    return true;
    //                return false;

    //            }
    //    };

    //    my_priority_queue<int, vector<int>, std::less<vector<int>::value_type> > q;
    //    std::priority_queue<int, std::deque<int>, std::function<bool(int, int)> > pri_queue([](int x, int y){
    //                                                                                           if(x < y)
    //                                                                                               return true;
    //                                                                                           return false;
    //                                                                                       });

    //    std::priority_queue<int, std::deque<int>, bool(*)(int, int) > pri_queue([](int x, int y){
    //                                                                                           if(x < y)
    //                                                                                               return true;
    //                                                                                           return false;
    //                                                                                       });

        //比较函数接受范围中的两个元素作为参数，并返回可转换为bool的值。
        //返回的值指示作为第一个参数传递的元素是否被认为小于它定义的特定严格弱顺序中的第二个参数
        my_priority_queue<int> q;
        q.push(9);
        q.push(2);
        q.push(7);
        std::cout<<"q[0]"<<q.top()<<std::endl;
        q.pop();
        std::cout<<"q[1]"<<q.top()<<std::endl;

    return 0;
}
