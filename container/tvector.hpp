#ifndef __TVECTOR__
#define __TVECTOR__
#include<vector>
#include<string>
#include<iostream>
#include<map>
using namespace std;
class vector_test {
public:
    vector_test():s_vec( {"abc","def","qwe"}) {}
    void test_value_type()
    {
        //value_type、reference只和类型有关;value_type是vector里的元素类型，reference是value_type&类型
        for(vector<string>::value_type it:s_vec)
        {
            std::cout<<it<<std::endl;
        }
        string b("qqqq");
        vector<std::string>::value_type a=string("aaa");
        vector<std::string>::const_reference c=string("bbb");//string("bbb")是一个临时变量，是一个右值，只能用const引用来引用
        const string& d=string("bbbb");
        std::cout<<"d="<<d<<std::endl;
        std::cout<<"a="<<a<<std::endl;
//         std::cout<<c<<std::endl;

    }
    void test_swap()
    {
        vector<string>a {"123","234","345","456","678"};
        a.swap(s_vec);
        for(auto it:s_vec)
            std::cout<<"s_vec="<<it<<std::endl;

        for(auto it:a)
            std::cout<<"a="<<it<<std::endl;
    }

    void test_size()
	{
		std::cout<<"size="<<s_vec.size()<<std::endl;//size函数计算的是当前容器中的实际存在的元素个数
	}

private:
    vector<string>s_vec;

};

#endif
