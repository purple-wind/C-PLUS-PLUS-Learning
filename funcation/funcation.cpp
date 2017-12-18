#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<functional>
using namespace std;
class PrintString {
public:
    PrintString(std::ostream &o=cout,char c=' '):os(o),sep(c) {}

    void operator()(const std::string& s)const
    {
        os<<"operator():"<<s<<sep<<'\t';
    }
    void operator()(const int a)const
    {
        std::cout<<"函数对象:"<<a<<"\t";
    }


    void run()
    {
        std::vector<string>vec= {"a","b","c"};
		//lambda表达式
        for_each(vec.begin(),vec.end(),[](std::string a)->void {
            std::cout<<"lambda:"<<a<<"\t";
        });
		std::cout<<std::endl;
		//重载了()运算符的函数对象
		PrintString p;
        for_each(vec.begin(),vec.end(),p);
		std::cout<<std::endl;

        std::vector<int>intger{1,2,3,4,5};
        for_each(intger.begin(),intger.end(),p);
		std::cout<<std::endl;
    }

private:
    std::ostream& os;
    char sep;
	std::vector<int> vec;
};

// 1.bind可以预先把指定可调用实体的某些参数绑定到已有的变量;
// 2.绑定一个函数(既可以是类的成员函数也可以是全局函数)到一个指定的类型的函数对象，
// 比如:将n个参数的函数绑定到一个参数小于n的函数对象,为了把参数数量不同的函数进行转换以便调用.
// 2.当被绑定的函数是全局函数时,bind的参数分别是: 函数名、 变量1.....变量n、 std::placeholders::_1....std::placeholders::_n,
// 其中std::placeholders_n表示绑定到的最终函数对象的参数n,变量n表示的是事先传递的变量
// 3.当被绑定的函数是类的静态成员函数时,bind的参数和全局一样；
// 4.当被绑定的函数是类的非静态成员函数时,bind的参数分别是　&类名::成员函数名、类的实体对象、 变量1.....变量n、 std::placeholders::_1....std::placeholders::_n;
//
//
class My_Bind :public PrintString {
public:
    void operator()() {
        std::cout<<"I'm bind"<<std::endl;
    }

   static int static_number(int a,int b,int c)
    {
        std::cout<<"static:a="<<a<<"  b="<<b<<" c="<<c<<std::endl;
    }
  int no_static_number(int a,int b,int c)
  {
	  std::cout<<"no static:a="<<a<<"  b="<<b<<" c="<<c<<std::endl;
  }
  void general_number(void)
  {
  }

    void run()
    {
        PrintString::operator()("I'm PrintString operator()");
        this->operator()();
		auto new_fun1=bind(static_number,1,2,std::placeholders::_1);
		new_fun1(3);
		std::cout<<"here"<<std::endl;
		new_fun1(-1,-2,-3);
		auto new_fun2=bind(&My_Bind::no_static_number,this,1,2,std::placeholders::_1);
		new_fun2(4);
		
		std::function<int(int,int,int)>f=static_number;
		f(1,2,3);
// 		std::mem_fn(this->no_static_number);
    }
};



