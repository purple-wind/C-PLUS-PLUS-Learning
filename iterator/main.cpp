#include<iostream>
#include<sstream>
#include<fstream>
#include<iterator>
#include<vector>
#include<deque>
#include<algorithm>
#include<numeric>
/**
 迭代器
    存在一组概念上相关类型，我们认定某个类型是迭代器类型，当且仅当它支持一套操作，这套操作使得我们可以访问容器的元素或者从一个元素移动到另外
    一个元素。从这个意义上讲指针也是迭代器

    类似容器，迭代器也定义了一组公共操作。一些操作所有迭代器都支持，另外一些操作只有特定类别才支持。例如流迭代器只支持递增、解引用和赋值。
    但是vector string deque的迭代器除了支持递增、解引用和赋值，还支持递减、关系运算、算术运算。

    1.容器的迭代器：每种容器都对应了自己的迭代器，每种容器迭代器支持的能力不一样，行为大致相同。

    2.流迭代器:流迭代器又有istream_iterator/istreambuf_iterator、ostream_iterator/ostreambuf_iterator
      2.1流迭代器可以关联到标准输入输出(cin cout),也可以关联到文件
      2.2流迭代器一般用于算法的参数，可以把容器和流关联上，比如把容器中的内容写入文件，也可以把文件内容直接读取到容器中(限制较多)，比如把文件
         内容写入vector<int>型的容器中，则文件中只能是数字字符串，遇到非数字字符即结束。只有流缓冲迭代器才可以原封不动的把文件内容获取到，但是
         流缓冲迭代器只能操作字符型（也算一个限制吧）。
      2.3输入流迭代器也支持前后++ 解引用 等于或者不等于操作，且其行为和普通迭代器一致。但是输出迭代器的前后++ 解引用实际上不对迭代器做任何操作，
         只是返回迭代器本身。把内容写到输出流迭代器只需要一直给流迭代器赋值即可
      2.4
      注意：
           1.流缓冲迭代器和流迭代器的区别是流缓冲迭代器会把输入的内容原样保持，但是流迭代器会忽略输入内容中的空格和换行符
           2.流缓冲迭代器无法指定非字符型的模板参数，例如整型.因为缓冲迭代器只是将元素以字符的形式写入到流缓冲区，而不会进行任何类型的转换
           3.流迭代器中有一个特殊迭代器是尾后迭代器，被定义为空的流迭代器。相当于容器的end迭代器。当流迭代器关联的流遇到文件结尾或者IO错误时，迭代器
             的值就等于尾后迭代器。

    3.迭代器适配器:迭代器适配器有插入迭代器，插入迭代器又有inserter、back_inserter、front_inserter

    按照泛型算法的概念来讲，任何标准库算法的最基本特性是它要求其迭代器提供哪些操作。标准库指明了泛型算法的每个迭代器参数的最小类别。
    根据泛型算法要求的最小类别，迭代器又可以大致可分为5类。如下5类迭代器形成了一种层次，高层次迭代器支持低层次迭代器所有操作。
        1.输入迭代器:只读不写，单遍扫瞄，只能递增。输入迭代器只用于顺序访问。对于一个输入迭代器，*it++保证是有效的，但递增它
          可能导致所有其他指向流的迭代器失效。其结果就是不能保证输入迭代器的状态可以保存下来并用来访问元素，因此输入迭代器只能用于单遍扫描。算法要求必须支持
          == != 前后++ * ->操作
        2.输出迭代器:只写不读，单遍扫瞄，只能递增。可以看作是输入迭代器功能上的补集，只写而不读元素。我们只能向一个输出迭代器赋值一次。输出迭代器
          只能用于单遍扫瞄。算法要求必须支持推进迭代器前进的前后++, 赋值操作。
        3.前向迭代器:可读写，多遍扫描，只能递增。只能在序列中沿一个方向移动。支持所有输入输出迭代器的操作且可以多次读写同一个元素。
        4.双向迭代器：可读写，多遍扫描，可递增递减。支持正向/反向读写序列中的元素。支持所有前向迭代器的操作外还支持前置后置--
        5.随即访问迭代器：可读写，多遍扫描，支持全部迭代器运算。除支持双向迭代器所有功能外还支持< <= > >= + += - -= 两个迭代器相减 下标运算
       注意：容器的迭代器、流迭代器满足上面5中迭代器类型中的一种或者多种。比如vector的迭代器满足5中迭代器中的任意一种


 */
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
            inserter1 = 4;
            for(auto& item : deq)
            {
                std::cout<<item<<std::endl;
            }

            std::cout<<"--------------------front insert------------------"<<std::endl;
            //创建一个使用底层容器push_front()的插入迭代器，注意此类迭代器只支持创建在底层容器有push_front()的容器上
            //front_inserter迭代器的赋值语句永远在第一个元素后面插入，同时迭代器永远指向在第一个元素处
            auto front_inserter = std::front_inserter(deq);
            front_inserter = 10;
            front_inserter = 11;
            for(auto& item : deq)
            {
                std::cout<<item<<std::endl;
            }

        }

        //流迭代器
        void test_is_iterator()
        {
            std::cout<<"---------istream iterator---关联到标准输入------"<<std::endl;
            //输入流迭代器关联到std::cin，注意此时只能把屏幕输入的数字关联到流迭代器，当输入不是数字时数据结束
            std::istream_iterator<int> is_iter0(std::cin), eof_iter;
            //std::vector<int> vec0;
            //while(is_iter0 != eof_iter)
            //{
            //  vec0.push_back(*is_iter0++);
            //};

            //用输入流迭代器初始化vec0，即可把屏幕输入保存到vec0中
            std::vector<int> vec0(is_iter0, eof_iter);//词句等价于上面的语句
            for(auto& item : vec0)
            {
                std::cout<<item<<std::endl;
            }

            std::cout<<"---------istream iterator---关联到文件------"<<std::endl;
            //输入流迭代器关联到文件中，此时只能把文件中的整型读取出来，其他类型无法输出，遇到非整型时结束输入
            std::ifstream ifs0("./test0.txt");
            is_iter0 = std::istream_iterator<int>(ifs0);
            std::vector<int> vec1;
            while(is_iter0 != eof_iter)
            {
                vec1.push_back(*(is_iter0++));
            };
            for(auto& item : vec1)
            {
                std::cout<<item<<std::endl;
            }
            ifs0.close();

            std::cout<<"---------istream iterator---读取文件再写入文件------"<<std::endl;
            //输入流迭代器关联到文件中，此时迭代器类型是u_char,会把文件中的所有内容按字符方式读取出来，读取出来的内容去掉
            //了原始内容中的空格或者还行符
            std::ifstream ifs1("./test.txt");
            std::istream_iterator<u_char>is_iter1(ifs1), eof_iter1;
            //std::vector<u_char> vec3;
            //while(is_iter1 != eof_iter1)
            //{
            //    vec3.push_back(*(is_iter1++));
            //};

            //等价于上面注释的4行
            std::vector<u_char>vec3(is_iter1, eof_iter1);

            for(auto& item : vec3)
            {
                printf("%x\n", item);
            }

            //把文件通过输入流迭代器读出来，再通过输出迭代器写入文件，会丢失原始文件中的空格或还行符
            std::ofstream ofs0("./test1.txt");
            std::ostream_iterator<u_char>os_iter1(ofs0);
            ifs1.close();//即使此处关闭了关联的输入文件流，也不印象迭代器的数据，说明数据被拷贝了
            std::copy(vec3.begin(), vec3.end(), os_iter1);
            ofs0.close();


            std::cout<<"------istreambuf iterator---关联到标准输入------"<<std::endl;
            //istreambuf_iterator,流缓冲迭代器会原样保持输入中的空格或换行符，而非缓冲迭代器则会忽略这些字符。比如
            //使用istream_iterator从文件中读取数据，再通过ostream_iterator写入文件中，则会丢失原始文件中的空格或换行符
            //std::istreambuf_iterator<char> isbuf_iter0(std::cin), eof_iter2;

            ////std::vector<char> vec4;
            ////while(isbuf_iter0 != eof_iter2)
            ////{
            ////    vec4.push_back(*isbuf_iter0++);
            ////}

            ////等价于上面注释的4行
            //std::vector<char>vec4(isbuf_iter0, eof_iter2);
            //for(auto& item : vec4)
            //{
            //    std::cout<<item;
            //}

            std::cout<<"------istreambuf iterator---关联到文件------"<<std::endl;
            std::ifstream ifs2("./test.txt");
            std::istreambuf_iterator<char> isbuf_iter1(ifs2), eof_iter3;
            std::vector<char> vec5(isbuf_iter1, eof_iter3);
            for(auto& item : vec5)
            {
                std::cout<<item;
            }
            ifs2.close();

            std::cout<<"---------istreambuf iterator---关联到string---------"<<std::endl;
            std::istringstream iss0("hello world\n");
            std::istreambuf_iterator<char>isbuf_iter2(iss0), eof_iter4;
            std::ostreambuf_iterator<char>osbuf_iter0(std::cout);
            std::copy(isbuf_iter2, eof_iter4, osbuf_iter0);//把输入直接拷贝到输出
        }

        void test_os_iterator()
        {
            std::cout<<"-----------ostream iterator绑定cout,作为copy算法的输出--------"<<std::endl;
            std::vector<int> vec2;
            for (int i=1; i<10; ++i)
                vec2.emplace_back(i*1000);
            std::copy(vec2.begin(), vec2.end(), std::ostream_iterator<int>(std::cout, ", "));
            std::cout<<std::endl;

            std::cout<<"---------ostreambuf iterator绑定cout,作为copy算法的输出-------"<<std::endl;
            //ostreambuf_iterator的模板参数只能是字符型，例如char u_char wchar_t char16_t char32_t等
            std::string str1 = "This is an example\n";
            std::copy(str1.begin(), str1.end(), std::ostreambuf_iterator<char>(std::cout));
            std::cout<<std::endl;

            std::cout<<"---------ostreambuf iterator绑定文件,作为copy算法的输出-------"<<std::endl;
            std::ofstream of0("./test2.txt");
            std::ostreambuf_iterator<char>os0_iter(of0);
            //std::ostreambuf_iterator<int>os1_iter(x);此句报错
            std::copy(vec2.begin(), vec2.end(), os0_iter);//此处把整型数据按字节写入文件,可能存在问题

            std::cout<<"-------iostream iterator混合使用,分别作为算法的输入和输出-------"<<std::endl;
            std::istringstream str0("0.1 0.2 0.3 0.4");
            std::partial_sum(std::istream_iterator<double>(str0),
                             std::istream_iterator<double>(),
                             std::ostream_iterator<double>(std::cout, " "));
            std::cout<<std::endl;
        }

        void test_ios_iter()
        {
            test_is_iterator();
            test_os_iterator();
        }

        //反向迭代器
        void test_reverse()
        {
            std::cout<<"-----------反向迭代器--------"<<std::endl;
            std::vector<int> vec0{1,2,3,4,5,6,2,8,9};
            auto find_iter = find(vec0.crbegin(), vec0.crend(), 2);
            std::cout<<"find="<<*find_iter<<std::endl;//从后向前找到的是6后面的2
            std::cout<<"find="<<*(++find_iter)<<std::endl;//迭代器++后指向6，说明是6后面的2而不是1后面的2
            auto gen_iter = find_iter.base();//反向迭代器转换成正向迭代器，此时gen_iter还是指向6后面那个2
            std::cout<<"正向find="<<*gen_iter<<std::endl;
            std::cout<<"正向find="<<*(++gen_iter)<<std::endl;//正向迭代器递增后指向的是8，说明正向迭代器指向的是6后面那个2而不是1后面的2
        }

        void vec_iterator_as_out_interator()
        {
            std::cout<<"-----------vector的迭代器做输出迭代器--------"<<std::endl;
            std::vector<int> vec0{1,2,3,4,5,6,2,8,9};
            std::vector<int> vec1(10);
            std::copy(vec0.begin(), vec0.end(), vec1.begin());//必须自己保证vec1有足够的空间容纳vec0的所有元素,若容量不足引发内存问题
            for(auto& item : vec1)
            {
                std::cout<<"value0="<<item<<std::endl;
            }

            std::cout<<"-----------vector关联的插入迭代器做输出迭代器--------"<<std::endl;
            std::vector<int> vec2;
            auto bk_iter = std::back_inserter(vec2);
            std::copy(vec0.begin(), vec0.end(), bk_iter);
            for(auto& item : vec2)
            {
                std::cout<<"value1="<<item<<std::endl;
            }
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
    iter0.test_ios_iter();
    iter0.test_reverse();
    iter0.vec_iterator_as_out_interator();
    return 0;
}
