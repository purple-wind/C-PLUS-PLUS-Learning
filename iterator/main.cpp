#include<iostream>
#include<vector>
#include<iterator>
#include<vector>
#include<deque>
class IteratorTest
{
    public:
        //插入迭代器
        void test_inserter()
        {
            std::deque<int> deq;
            std::cout<<"--------------------bk insert------------------"<<std::endl;
            //创建一个使用底层容器push_back()的插入迭代器，注意此类迭代器只支持创建在底层容器有push_back()的容器上
            //back_inserter迭代器的赋值语句永远在最后一个元素后面插入，同时迭代器永远指向最后一个元素处
            auto bk_inserter = std::back_inserter(deq);
            bk_inserter = 9;
            bk_inserter = 8;
            for(auto& item : deq)
            {
                std::cout<<item<<std::endl;
            }

            std::cout<<"--------------------insert----------------------"<<std::endl;
            //创建一个使用底层容器insert()的插入迭代器，在end()之前插入数据(即在尾部插入)，第二个参数表示要在指定元素之前插入
            auto inserter = std::inserter(deq, deq.end());
            inserter = 7;//该句等价于iter = deq.insert(deq.end(), 7); iter++;
            inserter = 6;

            for(auto& item : deq)
            {
                std::cout<<item<<std::endl;
            }

            std::cout<<"----------------------"<<std::endl;
            //创建一个使用底层容器insert()的插入迭代器，在begin()之前插入数据(即头部插入)，第二个参数表示要在指定元素之前插入
            auto inserter1 = std::inserter(deq, deq.begin());
            inserter1++;//++操作虽然存在，但是不会对inster1做什么操作，只是返回该迭代器本身
            inserter1 = 5;

            for(auto& item : deq)
            {
                std::cout<<item<<std::endl;
            }

            std::cout<<"--------------------front insert------------------"<<std::endl;
            //创建一个使用底层容器push_front()的插入迭代器，注意此类迭代器只支持创建在底层容器有push_front()的容器上
            //front_inserter迭代器的赋值语句永远在第一个元素后面前面，同时迭代器永远指向在第一个元素处
            auto front_inserter = std::front_inserter(deq);
            front_inserter = 10;
            front_inserter = 11;
            for(auto& item : deq)
            {
                std::cout<<item<<std::endl;
            }

        }

        //流迭代器
        void test_iostream()
        {

        }

        //反向迭代器
        void test_reverse()
        {

        }

};

int main()
{
 std::vector<int>vec{1,2,3};
 std::vector<int>::iterator it=vec.begin()+1;
 vec.erase(it);
 std::cout<<*it<<std::endl;
 std::cout<<*(--it)<<std::endl;
 std::cout<<*(++it)<<std::endl;
 std::cout<<*(it+2)<<std::endl;
 std::cout<<vec.size()<<std::endl;
 std::cout<<vec.capacity()<<std::endl;

 IteratorTest iter0;
 iter0.test_inserter();
 return 0;
}
