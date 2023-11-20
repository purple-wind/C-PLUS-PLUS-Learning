#include<iostream>
//#include<string>
#include<memory>
////////////////////////////////////////////////////////////
//构造
//1.在构造函数中成员的初始化在函数体之前完成，且他们按照在类中出现的顺序进行初始化
//2.虽然不能直接拷贝一个数组，但是合成的拷贝构造函数会逐元素的拷贝一个数组类型的成员，如果数组元素是类类型，则还会调用类的拷贝构造函数
//3.拷贝初始化发生的时机:
//  1.用等号定义变量，例如： A a; A b = a;此处的第二句
//  2.用同类型的其它对象定义变量，例如： A a; A b(a);此处的第二句
//  3.将一个对象作为函数实参传递给非引用类型的形参
//  4.从一个返回类型为非引用类型的函数返回对象
//  5.花括号列表初始化一个数组中的元素
//  6.花括号列表初始化一个聚合类中的成员,某些类类型还会对他们所分配的对象使用拷贝初始化
//4.拷贝构造函数在某些情况下是隐式发生的，所以拷贝构造函数不能是explicit
//5.三五法则
//  规则一:如果一个类需要自定义析构函数，则该类一定需要自定义拷贝构造函数和拷贝赋值运算符。但是一个类需要自定义拷贝构造和拷贝赋值但未必需要自定义析构函数
//  规则二:需要拷贝操作的类也需要赋值操作，反之亦然
//6.合成构造函数,如果类未定义构造函数，则编译器会为它生成构造函数，编译器生成的构造函数叫合成构造函数。编译器会生成如下5种合成构造函数:
//  合成默认构造函数, 默认构造函数就是可以以无参的方式被调用的构造函数,一种是无参，一种是有参数但是每个参数都有缺省值。如果一个类未定义任何拷贝、移动构造函数，则编译器会生成合成版本
//
//  合成拷贝构造函数,只有拷贝构造函数和移动构造函数和移动赋值运算符都未定义时，编译器才生成合成版本。如果定义了移动构造函数而未定义拷贝构造函数则合成拷贝构造函数是删除的。
//                如果定义了移动赋值运算符，而未定义拷贝构造函数和移动构造函数，则合成的拷贝构造函数是删除的，不合成移动构造函数
//
//  合成拷贝赋值运算符,只有拷贝赋值运算符和移动赋值运算符和移动构造函数都未定义时，编译器才生成合成版本。如果定义了移动赋值运算符而未定义拷贝赋值运算符则合成拷贝构赋值运算符是删除的。
//                  如果定义了移动构造函数而未定义拷贝赋值运算符和移动赋值运算符，则合成的拷贝赋值运算符是删除的，不合成移动赋值运算符
//
//  合成移动构造函数,只有在拷贝构造和移动构造函数和移动赋值运算符都未定义时，编译器才生成合成版本。如果定义了拷贝构造而未定义移动构造，编译器不合成移动构造函数，需要移动操作时使用的还是拷贝构造。
//                如果定义移动赋值运算符而未定义拷贝构造函数和移动构造函数，则不合成的移动构造,合成的拷贝构造函数是删除的
//
//  合成移动赋值运算符,只有在拷贝赋值运算符和移动赋值运算符和移动构造函数都未定义时，编译器才生成合成版本，如果定义了拷贝赋值运算符而未定义移动赋值运算符，需要移动操作时使用的还是拷贝构造。
//                  如果定义了移动构造函数，而未定义移动赋值运算符和拷贝赋值运算符，则不生成合成移动赋值运算符，合成的拷贝赋值运算符是删除的

//  拷贝构造、移动构造、拷贝赋值、移动赋值、析构函数这5个函数一起称为拷贝控制成员
//  只要一个类没有定义拷贝构造函数，则编译器会生成合成版本，但是如果同时定义了移动版本拷贝控制成员，则拷贝构造函数是删除的
//  只要一个类没有定义拷贝赋值运算符，则编译器会生成合成版本，但是如果同时定义了移动版本拷贝控制成员，则拷贝赋值运算符是删除的
//  只有一个类没有定义任何自己版本的拷贝控制成员且类的每个非static的数据成员都可以移动时，编译器才会合成移动构造函数和移动赋值运算符

//  编译器永远不会隐式定义合成移动操作为删除函数(只可能不生成移动版本)，只有显示指定移动操作=default时，且编译器不能移动所有成员时，才会将移动操作定义为删除的。
//  移动操作和合成拷贝控制成员有一个相互作用关系：如果一个类定义了自己的移动操作，则该类的其它合成的拷贝版本是删除的，移动版本不合成

//7.合成的构造函数和合成的析构函数有可能是删除的，如果一个类有数据成员不能默认构造、拷贝、赋值、析构，则他们对应的合成函数是删除的。因为编译器合成的函数也是为了
//  保证类可以被正常的构造、拷贝、赋值、析构，如果类的成员变量不能被构造、析构，编译器当然不能随便合成函数，否则会造成错误
////////////////////////////////////////////////////////////

//类值行为
class HasPtr
{
    public:
        HasPtr(const std::string s = std::string()):i(0), ps(new std::string(s))
        {
            std::cout << "general constructor" << std::endl;
        }

        HasPtr(const HasPtr& rv):i(rv.i),ps(new std::string(*rv.ps))
        {
            std::cout << "copy constructor" << std::endl;
        }

        HasPtr(HasPtr&& rv)noexcept:i(rv.i), ps(rv.ps)
        {
            rv.ps = nullptr;
            std::cout << "move constructor" << std::endl;
        }

        HasPtr& operator=(const HasPtr& rv)
        {
            std::cout << "copy assign" << std::endl;
            if(this == &rv)
                return *this;

            i = rv.i;

            std::string* temp_str = new std::string(*rv.ps);
            delete ps;
            ps = temp_str;

            return *this;
        }

        HasPtr& operator=(HasPtr&& rv)noexcept
        {
            std::cout << "move assign" << std::endl;
            if(this == &rv)
                return *this;

            i = rv.i;
            ps = rv.ps;
            return *this;
        }

        //如果类自己管理资源，且这样的类有类值行为。在交换这样的两个对象时，在交换期间会把两个对象管理的资源进行多次的拷贝。
        //其实这些拷贝是没有必要的，因为交换两个对象时不必表现类型行为，不需要交换指针指向的对象，只需要交换指针本身即可，
        //此时可以定义一个swap()函数用于交换指针以提升交换的性能。
        //对于类指针行为的类，交换本身就是交换指针，不需要swap()函数，即使有也不能提升性能

        //如果该类定义了swap()函数,则拷贝赋值运算符可以直接调用swap()。但是要注意拷贝赋值运算符的
        //参数需要使用值传递(不能用引用了)，因为值传递时调用了一次拷贝构造，在改变左侧对象之前拷贝了右侧
        //运算对象，保证了自赋值的正确。所以使用拷贝和交换实现的赋值运算符自动就是异常安全的，且能处理自赋值
        //void swap(HasPtr& r)
        //{
        //    std::cout << "swap" << std::endl;
        //    using std::swap;
        //    std::swap(this->i, r.i);
        //    std::swap(this->ps, r.ps);
        //}

        //HasPtr& operator=(HasPtr r)
        //{
        //    std::cout << "copy assign by swap" << std::endl;
        //    this->swap(r);
        //    return *this;
        //}

        ~HasPtr()
        {
            std::cout<<"delete HasPtr,i="<<i<<std::endl;
            delete ps;
        }

        int i = 0;
        std::string* ps = nullptr;
};

//类指针行为
class HasPtr1
{
    public:
        HasPtr1(std::string s = std::string()): i(0), ps(new std::string(s)), use(new size_t(1))
        {
            std::cout << "general constructor" << std::endl;
        }

        HasPtr1(const HasPtr1& p): i(p.i), ps(p.ps), use(p.use)
        {
            std::cout << "copy constructor" << std::endl;
            ++*use;
        }

        HasPtr1& operator =(const HasPtr1& p)
        {
            if(this == &p)
                return *this;

            ++*p.use;
            if(--*use == 0)
            {
                delete ps;
                delete use;
            }

            i = p.i;
            ps = p.ps;
            use = p.use;

            return *this;
        }

        ~HasPtr1()
        {
            if(--*use == 0)
            {
                delete ps;
                delete use;
            }
        }


        int i;
        std::string* ps;
        std::size_t* use;
};

//A0用于演示swap()
class A0
{
    public:
        void swap(A0& r)
        {
            std::cout << "A0 swap" << std::endl;
            using std::swap;
            //this->ptr1.swap(r.ptr1);
        }
    private:
        HasPtr ptr1;
};

//A2 A3用于演示合成拷贝控制成员删除的场景
int x = 10;
class A2
{
    public:
        A2()
        {

        }
};

class A1
{
    public:
        //此处必须定义默认构造函数，因为下面的成员变量有引用类型和const修饰的类型，
        //当类有引用类型的成员变量，则该类的默认构造函数是删除的。
        //当类有const修饰的成员变量且成员变量类型没有默认构造函数时,则该类的默认构造函数是删除的

        //如果自己定义这个默认构造函数，不使用编译器合成的默认构造函数。虽然在编译时不报错，但是逻辑上也是错的，因为
        //类的引用类型的成员变量或者const修饰的成员变量未被初始化，那以后就没有机会再初始化了，那它们就没有存在的意义了
        //A1()
        //{

        //}

        //只有这样自定义的默认构造函数才是有意义的，因为它初始化了类的引用类型的成员变量或者const修饰的成员变量
        //A1():a(x),b(x),c(1),d(x)
        //{

        //}

        //如果定义了该构造函数，未定义上面的两个构造函数，编译器就不会合成默认的构造函数，那么就无法以无参的方式定义A1类型对象
        //A1(int a, int b, int c, int d):a(a),b(b),c(2),d(d)
        //{

        //}

        int a;
        int& b = a; //b是引用类型则必须类内初始化，否则此句会造成默认构造函数被删除
        int&& c = 1;//同理b
        const int d = 2;//d是const修饰，则d要么类内初始化，要么d的类型有默认构造函数，由于d的类型是int，无默认构造函数，故d必须类内初始化，否则此句会造成默认构造函数被删除
        const A2 e; //e是const类型，但是A2有默认构造函数，故此句不会造A1的默认构造函数删除
};


////////////////////////////////////////////////////////////
//析构
//1.析构函数中,首先执行函数体，在析构函数体执行完毕后，成员会被自动销毁，成员按初始化顺序逆序销毁。
//  在一个析构函数中不存在类似构造函数的初始化列表的东西来控制成员如何销毁，析构成员的部分是隐式的，
//  即成员是在析构函数体之后隐含的析构阶段中被销毁的。成员销毁时发生什么取决于成员的类型。隐式销毁
//  一个内置类型指针成员不会delete它所指向的对象。但是销毁智能指针时会调用智能指针的析构函数，智能指针的析构函数会销毁它的成员，同时也会调用它管理的对象的析构函数。
//2.delete一个类类型的指针时会调用该类的析构函数
//3.析构函数调用时机:
//    1.变量离开作用域时
//    2.对象被销毁,会调用成员的析构函数销毁其成员
//    3.容器被销毁,会调用其元素的析构函数销毁其元素
//    4.动态分配的对象,对该对象的指针执行delete时,则调用指向对象类型的析构函数
//    5.对于临时对象,当创建它的完整表达式结束时
//4.编译器合成的析构函数，当一个类未定义析构函数时，编译器会为它生成一个合成析构函数。合成析构函数可以阻止对象销毁，即=delete，此时无函数体。
//  如果有函数体，则函数体为空。合成析构函数只在函数体之后隐含的析构阶段销毁成员。
////////////////////////////////////////////////////////////


//内置数组的析构
class DelArray{
    public:
        DelArray()
        {
            std::cout<<__FUNCTION__<<std::endl;
            for(int i = 0; i < 5;i++)
            {
                a[i].i = i;
            }
            b.i = 100;
            std::cout<<"after constructor"<<std::endl;
        }
        ~DelArray()
        {
            //析构的时候先调用析构函数中的语句，该函数结束后再析构成员变量。
            //此函数中没有手动释放a b, a、b是该函数结束后自动被析构的
            std::cout<<__FUNCTION__<<std::endl;
        }
    private:
        HasPtr a[5];
        HasPtr b;
};


//简化的string版vector
class StrVec
{
    public:
        StrVec():elements(nullptr),first_free(nullptr),cap(nullptr)
        {

        }

        StrVec(const StrVec& r)
        {
            std::pair<std::string*, std::string*> new_data = alloc_n_copy(r.begin(), r.end());
            elements = new_data.first;
            first_free = new_data.second;
        }

        //移动构造函数，把指针赋值给新对象实现了窃取源对象的目的。但是移动后必须保证源对象可析构且析构是无害的
        StrVec(StrVec&& r)noexcept:elements(r.elements), first_free(r.first_free), cap(r.cap)
        {
            //r的成员指针赋空指针，保证被移动的对象是可析构且析构无害的
            r.elements = nullptr;
            first_free = nullptr;
            cap = nullptr;
        }

        StrVec& operator=(const StrVec& r)
        {
            auto new_data = alloc_n_copy(r.begin(), r.end());
            this->free();
            elements = new_data.first;
            first_free = new_data.second;
            return *this;
        }

        StrVec& operator=(StrVec&& r)noexcept
        {
            if(this == &r)
                return *this;

            free();
            elements = r.elements;
            first_free = r.first_free;
            cap = r.cap;

            r.elements = nullptr;
            r.first_free = nullptr;
            r.cap = nullptr;

            return *this;
        }

        ~StrVec()
        {
            free();
        }

        //左值引用版本的push_back，s绑定到任意类型
        void push_back(const std::string& s)
        {
            std::cout<<"copy push_back"<<std::endl;
            chk_n_alloc();
            alloc.construct(first_free++, s);
        }

        //右值引用版本的push_back,s只能绑定到非const的右值
        void push_back(std::string&& s)
        {
            std::cout<<"move push_back "<<std::is_rvalue_reference<decltype(s)>::value<<std::endl;
             chk_n_alloc();
             //alloc.construct(first_free++, std::move(s));
             alloc.construct(first_free++, std::forward<decltype(s)>(s));

        }

        size_t size() const
        {
            return first_free - elements;
        }

        std::size_t capacity() const
        {
            return cap - elements;
        }

        std::string* begin() const
        {
            return elements;
        }

        std::string* end() const
        {
            return first_free;
        }

        void reserve(size_t n)
        {
            std::cout<<"reserve="<<capacity()<<std::endl;
            if(n > capacity())
            {
                reallocate2();
                reserve(n);
            }
        }

        void resize(size_t n)
        {
            if(n < size())
            {
                for(auto& p = first_free; p != elements + n;)
                {
                    p--;
                    p->clear();
                }
                first_free = elements + n;
            }
            else if(n > size())
            {
                reserve(n);
            }
        }

    private:

        std::pair<std::string*, std::string*> alloc_n_copy(const std::string *b, const std::string *e)
        {
            auto data = alloc.allocate(e - b);
            return {data, std::uninitialized_copy(b, e, data)};//uninitialized_copy()返回一个指针，指向最后一个构造元素之后位置
        }

        void free()
        {
            if(elements)
            {
                for(auto p = first_free; p != elements;)
                {
                    alloc.destroy(--p);
                }

                alloc.deallocate(elements, cap - elements);
            }
        }

        void chk_n_alloc()
        {
            if(size() == capacity())
            {
                reallocate();
            }
        }

        void reallocate()
        {
            auto newcapacity = size() ? 2 * size() : 1;
            auto new_data = alloc.allocate(newcapacity);
            auto dest = new_data;
            auto elem = elements;
            //for(size_t i = 0; i != size(); ++i)
            //{
            //    alloc.construct(dest++, std::move(*elem++));
            //}

            //使用移动迭代器也可以代替上面的for循环移动功能
            //通常情况下解引用一个迭代器得到迭代器指向元素的左值引用，但是移动迭代器解引用返回的却是迭代器指向的元素的右值引用
            std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), dest);

            free();


            elements = new_data;
            first_free = dest;
            cap = elements + newcapacity;
        }

        void reallocate2()
        {
            auto newcapacity = capacity() ? 2 * capacity() : 1;
            auto new_data = alloc.allocate(newcapacity);
            auto dest = new_data;
            auto elem = elements;
            for(size_t i = 0; i != size(); ++i)
            {
                alloc.construct(dest++, std::move(*elem++));
            }

            free();


            elements = new_data;
            first_free = dest;
            cap = elements + newcapacity;
        }

    private:
        static std::allocator<std::string> alloc;
        std::string* elements;//首元素
        std::string* first_free;//第一个空闲元素
        std::string* cap;//尾后位置
};

std::allocator<std::string> StrVec::alloc;

void test_constructor_destructor()
{
    HasPtr a0;
    HasPtr a1(a0);//拷贝构造
    HasPtr a2 = a0;//拷贝构造
    a2 = a1; //拷贝赋值

    HasPtr a3();//错误,编译器把它识别成了 A a3(void);这样的函数申明,虽然编译期不报错,但是并不是我们想要的逻辑
    HasPtr* a4 = new HasPtr();//普通构造
    HasPtr* a5 = new HasPtr(a0);//拷贝构造,new关键字在初始化新分配的内存时会调用拷贝构造,相当于在new的过程中调用了A x(a0)
    HasPtr* a6 = new HasPtr(std::move(a0));//移动构造

    delete a4; //delete会调用A的析构函数
    delete a5;
    delete a6;
}

void test_delete_copy_contral()
{
    A1 a7;
    //A1 a8(1, 2, 3, 4);
}

void test_my_strvec()
{
    StrVec svec;
    svec.push_back("0");
    svec.push_back("1");
    svec.push_back("2");
    svec.push_back("3");
    std::cout<<"capacity="<<svec.capacity()<<std::endl;
    std::cout<<"after"<<std::endl;
    svec.reserve(10);
    for(auto item:svec)
    {
        std::cout<<"reserve svec="<<item<<std::endl;
    }
    std::cout<<"size="<<svec.size()<<std::endl;
    for(int i = svec.size(); i < svec.capacity(); i++)
    {
        svec.push_back(std::to_string(i));
    }
    for(auto item:svec)
    {
        std::cout<<"after reserve svec="<<item<<std::endl;
    }
    std::cout<<"size="<<svec.size()<<" capacity="<<svec.capacity()<<std::endl;

    svec.resize(8);
    for(auto item:svec)
    {
        std::cout<<"after resize svec="<<item<<std::endl;
    }
    std::cout<<"size="<<svec.size()<<" capacity="<<svec.capacity()<<std::endl;

}

void test_array_destructor()
{
    /*内置数组在出作用域时会自动析构数组内的元素，且从后向前析构*/
    {
        HasPtr a[3];
        for(int i = 0; i<3;i++)
        {
            a[i].i = i;
        }
        std::cout<<"after"<<std::endl;
    }
    /*当数组作为类的成员变量时，类析构时会自动析构数组成员内的元素，且从后向前析构*/
    {
        DelArray da;
    }
    std::cout<<"out"<<std::endl;
}

class Q
{
    public:
        Q(){std::cout<<"general"<<std::endl;}
        Q(const Q& q){std::cout<<"copy"<<std::endl;}
        Q(Q&& q){std::cout<<"move"<<std::endl;}
//        ~Q(){std::cout<<"destory"<<std::endl;}
};



void test1(const Q& q)
{
    std::cout<<"1 "<< std::is_rvalue_reference<decltype(q)>::value<< std::endl;
    Q a(q);
}

void test1(Q&& q)
{
    std::cout<<"2 "<< std::is_rvalue_reference<decltype(q)>::value<< std::endl;
    Q(std::forward<decltype(q)>(q));
}

void test3()
{
    Q x;
    test1(x);
    test1(Q());
}
