/*
 * 1.本文件测试顺序容器的各个功能，测试顺序容器类型为vector、deque、list、forward_list、array、string
 * 2.每个特性定义来测试一个函数
 * 3. 只有内存连续的容器(vector.deque.array.string)才能支持迭代器与一个数字的加减运算,内存不连续的不支持迭代器与数字加减，但是支持++，--运算，其中forward由于是单向list所以不支持--；
 * 4.
 *
*/

#ifndef __BEGIN_H__
#define __BEGIN_H__
#include<vector>
#include<list>
#include<deque>
#include<array>
#include<string>
#include<forward_list>
#include<iostream>
class Container {
public:
    std::vector<int>vec1{1,1,1,1,1};
	std::vector<int>vec2{12,12,12,12,12};
    std::deque<int>deq{2,2,2,2,2};
    std::list<int>lis{3,3,3,3,3};
    std::forward_list<int>forward{4,4,4,4,4};
//     std::array<int,5>arr{5,5,5,5,5};arr暂不支持类内初始化
	std::array<int,5>arr1;
	std::array<int,5>arr2;
    std::string str1{'6','6','6','6','6'};
    std::string str2{'7','7','7','7','7'};
Container():arr1({5,5,5,5,5}),arr2({51,52,53,54,55}){}

    void test_assign()//替换容器中的元素，如果容器中本来有元素就被新元素覆盖
    {
        lis.assign(vec1.begin(),vec1.end());//assign支持一个范围;lis本来被初始化为3，但是被替换后变成了1
		for(auto it:lis)
			std::cout<<"list="<<it<<"  ";
		std::cout<<std::endl;
		std::vector<std::string > vec3;
        vec3.assign(10,"a");//assign支持n个相同元素替换容器中的内容
        for(auto it :vec3)
        {
            std::cout<<it<<"  ";
        }
                std::cout<<std::endl;
    }



// 交换容器，实际上元素本身并未交换，只是交换了容器的内部数据结构(内存和内存中保存的值都不会变，给它们换个名字而已)，迭代器引用和指针都不会失效，但是string调用swap会使迭代器指针引用失效，优点速度快；但是对array进行swap操作会真正交换它们的元素,把元素的值进行对换。

    void test_wsap()
    {
        std::cout<<"----------vector  swap-----------"<<std::endl;
        std::cout<<&vec1[0]<<std::endl;
        std::cout<<&vec2[0]<<std::endl;
        typedef std::vector<int> type_vec;
		type_vec::iterator iter=vec1.begin();
        vec1.swap(vec2);
        std::cout<<&vec1[0]<<std::endl;
        std::cout<<&vec2[0]<<std::endl;
        std::cout<<std::endl;

        /*swap交换后，交换前迭代器还是指向交换前的元素，交换后的迭代器才指向交换后的元素*/
        std::cout<<"iter="<<*iter<<std::endl;
        type_vec::iterator iter1=vec1.begin();
        std::cout<<"iter1="<<*iter1<<std::endl;

        /*gcc4.8.2对string类型的迭代器也不会使迭代器失效*/
        std::cout<<"-------string  swap----------"<<std::endl;
        std::string::iterator s_iter1=str1.begin();
        std::cout<<&str1<<std::endl;
        std::cout<<&str2<<std::endl;
        swap(str1,str2);
        std::cout<<&str1<<std::endl;
        std::cout<<&str2<<std::endl;
        std::cout<<*(++s_iter1)<<std::endl;


        std::cout<<"-------array  swap----------"<<std::endl;
        std::cout<<&arr1[0]<<std::endl;
        std::cout<<&arr2[0]<<std::endl;
        swap(arr1,arr2);
        std::cout<<&arr1[0]<<std::endl;
        std::cout<<&arr2[0]<<std::endl;
    }

    void get_start()
	{
		std::cout<<"front="<<vec1.front()<<"   back="<<vec1.back()<<std::endl;
		std::cout<<"begin="<<*vec1.begin()<<"  end="<<*(vec1.end()-1)<<std::endl;
		std::cout<<"begin="<<*lis.begin()<<"  end="<<*(--lis.end())<<std::endl;
	}
	void my_insert()
	{
		vec1.push_back(100);
		deq.push_back(100);
		lis.push_back(100);
		str1.push_back('c');
		vec1.insert(vec1.end(),101);
		std::cout<<"deq end="<<*(deq.insert(deq.end(),21))<<std::endl;//插入一个数字
        std::cout<<"lis end="<<*(lis.insert(lis.end(),31))<<std::endl;
// 		std::string::iterator it=str1.insert(str1.begin(),2,'q');//插入5个q字符,本gcc未实现c++11这个语法，c++11规定此处返回的是第一个插入元素的迭代器；此处it为void
		str1.insert(str1.end(),5,'q');
        std::cout<<"str1="<<str1<<std::endl;
		str1.insert(str1.begin(),str2.begin(),str2.end());//插入一个迭代器范围，迭代器不能是调用insert的对象的迭代器
        std::cout<<str1<<std::endl;

		vec1.insert(vec1.begin(),vec2.begin(),++vec2.begin());
		for(auto it:vec1)
			std::cout<<"vec1="<<it<<"  ";
		std::cout<<std::endl;

	}
	void my_emplace()//内部构造，直接把元素构造在容器内部
	{
		vec1.emplace_back(102);//在容器内部末尾位置构造一个元素值是102的元素
		deq.emplace_front(101);//在容器开头位置构造一个元素值是101的元素
		vec2.emplace(vec2.begin(),202);//在第一个元素之后创建一个元素值为202的元素
	}

};


#endif