#include"class_temp.hpp"
#include"fun_template.hpp"
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

    return 0;
}
