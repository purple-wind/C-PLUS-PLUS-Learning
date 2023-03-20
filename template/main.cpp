#include"class_temp.hpp"
#include"fun_template.hpp"
#include<vector>
int main()
{
    // 函数模板
        std::cout<<"-------------函数模板----------------"<<std::endl;
        fun_temp temp;
        temp.used_fun_temp();
        temp.pfun_test();
        temp.infer();
        temp.infer1();
        temp.infer2();

        int a11=100;
        int&& a22=std::move ( a11 );
        std::cout<<"a1="<<a11<<std::endl;
        a22=200;
        std::cout<<"a1="<<a11<<std::endl;
        a11=300;
        std::cout<<"a1="<<a11<<std::endl;
        std::cout<<"a2="<<a22<<std::endl;
        a22=200;
        std::cout<<"a1="<<a11<<std::endl;
        std::cout<<"-------------类型萃取----------------"<<std::endl;
        test_traits();

    // 类模板
      std::cout<<"-----------------类模板--------------"<<std::endl;
      Class_temp<int,char,t3> ClassTemp;
      ClassTemp.fun_in_class ( "argv1","argv2" );
      typedef Class_temp<std::string,std::string,std::string> CT;
      CT ct;
      // 	ct.run("abc","def");//run函数是类模板中的一个成员函数，类模板的成员函数只有在被使用时才会被实例化。
      // 	所以此句没有被调用就不会报错，一旦被调用就会出错。即使此函数的实现中有错误，在模板实例化的时候也不
      // 	会报错，因为成员函数没有被使用使用。
      Blob<int> blob_int;
      blob_int.empty();

      std::cout<<"--------------构造函数----------------"<<std::endl;
    //构造函数
      t3 a100 ( ClassTemp.run ( 100,'A' ) ); //这句既没有发生拷贝构造也没发生拷贝赋值,可能被编译器优化
      t3 a101 ( a100 ); //拷贝构造
      t3 a102=a100;//拷贝构造
      a101=a100;//拷贝赋值

      std::cout<<"----------------转发------------------"<<std::endl;
    // 转发
      Flips flips;
      flips.test_flips();
      VariadicTemplate var;
      var.test();
      std::cout<<"--------------可变长参数模板-----------"<<std::endl;
      var.test1();


      //引用类型经过std::is_const判断始终为false，即非const类型
      //检查引用的类型的const属性的正确方式是移除引用:is_const<typename remove_reference<T>::type>
      int a = 0;
      const int b = a;
      const int& c = a;
      const int&& d = static_cast<const int&&>(a);
      std::cout<<"b="<<IsConst<decltype(b)>::value<<std::endl;
      std::cout<<"c="<<IsConst<decltype(c)>::value<<std::endl;
      std::cout<<"d="<<IsConst<decltype(d)>::value<<std::endl;
      const int & e = a;
      std::cout<<"e="<<IsConst<std::remove_reference<decltype(e)>::type>::value<<std::endl;
      IsConst<const int> x;
      IsConst<const int&>y;
      IsConst<decltype(b)>z;





      Magic0A magic0a;
      Accept(magic0a);
      Magic1A magic1a;
      Accept(magic1a);


      std::cout<<sum<double>(1, 2)<<std::endl;//实例化为double sum(int, int);
      sum<int>(100, 'a');//int sum(int, char)
      sum<int, int, char>(100, 'a');//int sum(int, char)

      //template<long> int sum2(const long&, const long&)
      //由于显示指定了实参类型，所以正常的类型转换规则可以被应用，100被转换成long, 'a'被转换成long
      sum2<long>(100, 'a');
      //由于显示指定了实参类型，所以正常的类型转换规则可以被应用，'a'被转换成long, 'a'被转换成int
      sum2<int>('a', 'b');

      std::vector<int> vec;
      for(int i = 1; i < 5; i++)
        vec.push_back(i);
      std::cout<<sum3(vec.begin(), vec.end())<<std::endl;

      std::cout<<"==="<<typeid(std::remove_pointer<int*>::type).name() <<std::endl;
      std::cout<<"==="<<typeid(int).name() <<std::endl;

      std::string e0;
      std::cout<<"&ea is string*="<<(typeid(&e0) == typeid(std::string *))<<std::endl;
      std::cout<<"&ea is const string*="<<(typeid(&e0) == typeid(const std::string *))<<std::endl;
      std::cout<<"&ea is string* const="<<(typeid(&e0) == typeid(std::string * const))<<std::endl;
      std::cout<<std::is_const<decltype(&e0)>::value<<std::endl;
      std::cout<<std::is_reference<decltype(&e0)>::value<<std::endl;
      std::cout<<std::is_pointer<decltype(&e0)>::value<<std::endl;
      debug_rep(e0);
      debug_rep(&e0);
      std::string *e1 = &e0;
      debug_rep(e1);
      std::string * const e2 = &e0;
      debug_rep(e2);
      const std::string *e3 = &e0;
      debug_rep(e3);






































    int e4 = 100;
    const int* e41 = &e4;
    const int* &e5 = e41;
//    *e5 = 200;
    std::cout<<std::is_const<const int* &>::value<<std::endl;


    return 0;
}
