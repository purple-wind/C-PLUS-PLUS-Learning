#include"class_template.hpp"
#include"fun_template.hpp"
#include<vector>
extern template class Blob<double>;

//template<int* N> void q123()
//{
//    std::cout<<"notype1 ptr="<<N;
//    std::cout<<" *N="<<*N<<std::endl;
//}
//void xyzz()
//{
//    static int s_iii = 200;
//    q123<&s_iii>();
//}
int main()
{
    // 函数模板
    std::cout<<"-------------函数模板----------------"<<std::endl;
    fun_temp temp;
    temp.used_fun_temp();
    temp.infer_pfun();
    temp.infer0();
    temp.infer1();
    temp.infer2();
    temp.infer3();

    sum1<double>(1, 2);//实例化为double sum(int, int);
    sum1<int>(100, 'a');//int sum(int, char)
    sum1<int, int, char>(100, 'a');//int sum(int, char)
    sum1<int>(100, 200);
    //sum1(100, 200);错误，返回值不参与模板类型推断
    //sum1<>(100, 200);错误，返回值不参与模板类型推断
    sum1<char>('a', 'b');

    //template<long> int sum2(const long&, const long&)
    //由于显示指定了实参类型，所以正常的类型转换规则可以被应用，100被转换成long, 'a'被转换成long
    sum2<long>(100, 'a');
    //由于显示指定了实参类型，所以正常的类型转换规则可以被应用，'a'被转换成long, 'a'被转换成int
    sum2<int>('a', 'b');

    std::vector<int> vec;
    for(int i = 1; i < 5; i++)
        vec.push_back(i);
    std::cout<<sum3(vec.begin(), vec.end())<<std::endl;


    std::cout<<"max="<<Max(1,2)<<std::endl;
    std::cout<<"max="<<Max(1L,2)<<std::endl;
    std::cout<<"max="<<Max('a','b')<<std::endl;

    std::cout<<"-------------类型萃取----------------"<<std::endl;
    test_traits();

    // 类模板
    std::cout<<"-----------------类模板--------------"<<std::endl;
    Class_temp<int,char,t3> ClassTemp;
    ClassTemp.fun_in_class ( "argv1","argv2" );
    typedef Class_temp<std::string,std::string,std::string> CT;
    CT ct;
    //ct.run("abc","def");//run函数是类模板中的一个成员函数，类模板的成员函数只有在被使用时才会被实例化。
    //所以此句没有被调用就不会报错，一旦被调用就会出错。即使此函数的实现中有错误，在模板实例化的时候也不
    //会报错，因为成员函数没有被使用使用。
    Blob<int> blob_int;
    blob_int.empty();
    blob_int.count();

    Blob<double>blob_double;

    Tmp<int, 100> l0;
    l0.Print();
    Tmp1<int> l1;
    l1.Print();
    Tmp1<int, double>l2;
    l2.Print();
    Tmp2<char, char>l3;//此处显示指定了第二个模板参数类型，则第二个模板参数类型是指定的类型，此处是char
    l3.Print();
    l3.Print1();
    Tmp2<char>l33;//此处未指定第二个模板参数的类型，则第二个模板参数类型是默认类型，即int
    l33.Print();
    l33.Print1();
    Tmp3<> l4;//Tmp3的所有模板参数都有默认值，此时定义该类型的对象时需要加空的尖括号<>
    l4.Print();
    Tmp4<int, char> l5;
    l5.Print();
    Tmp4<char, double> l6;
    l6.Print();
    Tmp4<double, char> l7;
    l7.Print();
    Tmp4<char, int> l8;
    l8.Print();
    Tmp5<1, 2, 3> l9;
    std::cout << "l9.val=" << l9.val << std::endl;

    Tmp6<char, int, double> l10;


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

    std::cout<<"--------------构造函数----------------"<<std::endl;
    //构造函数
    //这句在run()函数中用二个参数的构造函数构造出一个t3临时对象,然后返回该临时对象(这个步骤中如果t3定义了移动构造则调用移动构造，否则调用拷贝构造)。
    //然后再用这个临时对象构造a100(这个过程中如果t3定义了移动构造则调用移动构造，否则调用拷贝构造)。因为从run()函数内部返回t3临时对象到用这个临时对象初始化
    //a100，都是临时对象，所以中间两个构造临时对象的过程会被编译器优化。当编译时添加了-fno-elide-constructors参数时可清晰看到该过程
    ClassTemp.run ( 100,'A' );
    std::cout<<"---------------"<<std::endl;//即使临时对象不用于初始化任何对象，单从run()中返回也会隐式调用构造函数
    t3 a100 ( ClassTemp.run ( 100,'A' ) );
    std::cout<<"---------------"<<std::endl;
    t3 a101 ( a100 ); //拷贝构造
    t3 a102 = a100;//拷贝构造
    a101=a100;//拷贝赋值

    std::cout<<"----------------转发------------------"<<std::endl;
    // 转发
    Flips flips;
    flips.test_flips();

    std::cout<<"--------------可变长参数模板-----------"<<std::endl;
    VariadicTemplate var;
    var.test();
    var.test1();

    return 0;
}
