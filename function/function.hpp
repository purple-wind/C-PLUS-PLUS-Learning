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
// 3.当被绑定的函数是全局函数时,bind的参数分别是: 函数名、 变量1.....变量n、 std::placeholders::_1....std::placeholders::_n,
// 其中std::placeholders_n表示绑定到的最终函数对象的参数n,变量n表示的是事先传递的变量
// 4.当被绑定的函数是类的静态成员函数时,bind的参数和全局一样；
// 5.当被绑定的函数是类的非静态成员函数时,bind的参数分别是　&类名::成员函数名、类的实体对象、 变量1.....变量n、 std::placeholders::_1....std::placeholders::_n;
// 6.bind函数传递的参数是拷贝的方式传递，即传递给它的参数在函数内部的改变不会影响到外部，如果想传递引用，则使用ref
//
class My_Bind :public PrintString {
public:
    void operator()() {
        std::cout<<"I'm bind"<<std::endl;
    }

   static int static_number(int a,int b,int c)
    {
		a++;
        std::cout<<"static:a="<<a<<"  b="<<b<<" c="<<c<<std::endl;
        return 0;
    }
  int no_static_number(int a,int b,int c)
  {
	  std::cout<<"no static:a="<<a<<"  b="<<b<<" c="<<c<<std::endl;
      return 0;
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

	int out=10;
	auto new_fun3=bind(static_number,out,2,std::placeholders::_1);
	new_fun3(3);//因为bind参数是值传递，此时如果在static_number内改变了a的值，不会影响到外部的out的值。
	//如果想在内部改变a的值也影响到外部的out则使用ref
	auto new_fun4=bind(static_number,std::ref(out),2,std::placeholders::_1);

	std::function<int(int,int,int)>f=static_number;
	f(1,2,3);
	//std::mem_fn(this->no_static_number);
    std::cout << "name=" << typeid(std::function<int(int, double)>::first_argument_type).name() << std::endl;
    std::cout << "name=" << typeid(std::function<int(int, double)>::second_argument_type).name() << std::endl;

    }
};

//C++11以后，对于函数模板实参，可以让调用者决定是传值还是传引用。当函数模板声明为值传递方式传递参数，
//调用者可以使用std::cref()和std::ref()来以引用方式传递参数，他们在头文件<functional>中声明。
//对于std::bind或std::thread中只能使用std::ref 和 std::cref 不能使用&。
//std::ref 和 std::cref 只是尝试模拟引用传递，并不能真正变成引用，在非模板情况下，std::ref根本没法
//实现引用传递，只有模板自动推导类型时，ref能包装类型reference_wrapper来代替原本会被识别的值类型，
//而reference_wrapper能隐式转换为被引用的值的引用类型，但是并不能被用作 & 类型。

//	std::ref() 用于包装按引用传递的值
//	std::cref() 用户包装按const引用传递的值
//	std::reference_wrapper() 将引用包装成一个对象，即引用的包装器。可以包裹一个指向对象或者指
//				 向函数指针的引用，既可以通过拷贝构造，也可以通过赋值构造
