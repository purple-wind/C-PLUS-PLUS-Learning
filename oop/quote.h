/*
 * Copyright 2017 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
/*1.如果基类定义了一个静态成员，则在整个继承体系中只存在该成员的唯一定义。不论从基类中派生出来多少个派生类，
 *  对于每个静态成员来说都只存在唯一的实例。静态成员遵循通用的访问控制规则。
 *2.如果某个类不希望其它类继承它，则可以在类名后加一个关键字final;
 *3.可以将基类的指针或引用绑定到派生类对象上。当使用基类的引用或者指针时，实际上我们并不清除该引用(指针)所绑
 *  定的真实类型。该对象可能是基类对象，也可能是派生类对象。
 *4.静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型。动态类型则是变量或者表达式表示的内存中
 *  的的对象类型，动态类型直到运行时才可知。如果表达式既不是引用也不是指针，则它的动态类型永远与静态类型一致。
 *5.之所以存在派生类向基类的类型转换是因为每个派生类对象都包含一个基类部分，而基类的引用或指针可以绑定到该基类
 *  部分上。一个基类的对象既可以以独立的形式存在，也可以作为派生类对象的一部分存在。如果基类对象不是派生类对象
 *  的一部分，则他只含有基类定义的成员，而不含有派生类定义的成员。因为基类的对象可能是派生类的一部分，也可能不
 *  是，所以不存在从基类向派生类自动类型转换。即使一个基类的指针或引用绑定在一个派生类对象上，我们也不能执行从
 *  基类向派生类型的转换。编译器在编译期无法确定某个特定的转换在运行时是否安全，这是因为编译器只能通过检查指针
 *  或引用的静态类型来推断该转换是否合法。如果在基类中含有一个或多个虚函数，可以使用dynamic_cast请求一个类型转
 *  换，该转换的安全检查将在运行时执行。同样，如果事先知道某个基类向派生类的转换是安全的，可以使用static_cast
 *  来强制覆盖掉编译器的检查工作。特别重要的一点是：这些转换仅限于指针或引用类型有效，在对象之间不存在这样的转
 *  换。
 * 6.派生类到基类的类型转换由编译器隐式完成。
 * 7.在派生类对象中含有与其基类对应的组成部分，这一事实是继承的关键所在。尽管在派生类对象中含有从基类继承而来的
 * 成员，但是派生类并不能直接初始化这些成员。和其它创建基类对象的代码一样，派生类也必须使用基类的构造函数来初始
 * 化它的基类部分。每个类控制它自己的成员初始化过程。派生类的构造过程是先初始化基类的部分，然后按照声明的顺序一
 * 次初始化派生类的成员。
 * 8.当我们用一个派生类对象为一个基类对象初始化或者赋值时，只有该派生类对象中的基类部分会被拷贝、移动或者赋值，
 * 它的派生类部分将被忽略掉。尽管自动类型转换只对拷贝控制成员有效，但是继承体系中的大多数类仍然定义了拷贝控制成员。
 * 因此通常能够将一个派生类对象拷贝、移动或者赋值给一个基类对象。不过这种操作只能处理派生类对象的基类部分。
 * 9.用指针或者引用调用一个虚函数时会执行动态绑定，因为我们直到运行时才知道到底运行哪个版本的虚函数，所有所有的
 * 虚函数必须都有定义。通常情况下，如果我们不使用某个函数，则无需为函数提供定义，但是我们必须为每一个虚函数都提
 * 供定义，而不管它是否被用到，这是因为编译器也无法确定到底会使用哪个虚函数。对虚函数的调用可能在运行时才被解析。
 *10.如果在派生类定义了一个函数与基类中虚函数的名字相同但是形参列表不同，这仍然是合法行为。编译器将认为新定义的
 * 这个函数与基类中原有的函数是相互独立的，此时派生类函数并没有覆盖掉基类中的版本。但通常我们希望在派生类中覆盖
 * 基类，只是不小心把形参列表弄错了，想调试或发现此类错误是十分困难的。c++11中可以使用override关键字来说明派生类
 * 以便让编译器为我们发现此类错误。如果我们用override标记了某个函数，但是该函数并没有覆盖已经存在的虚函数，此时
 * 编译器将报错。因为只有虚函数才能被覆盖，所以override只能用于虚函数。
 * 11.如果虚函数使用默认实参被调用，则该实参值由本次调用的静态类型决定。即传入函数的是基类函数定义的默认实参。
 * 故基类和派生类中定义的默认实参最好一致。
 * 12.如果不需要对虚函数的调用进行动态绑定，则是强迫其执行虚函数的某个特定版本。使用作用域运算符可以实现。通常只
 * 有成员函数或者友元中的代码才需要使用作用域运算符来回避虚函数机制。这种指定作用域来回避虚函数机制的函数调用将
 * 在编译时完成解析。如果一个派生类虚函数需要调用它的基类版本，但是没有使用作用域运算符，则在运行时将被解析为对
 * 派生类版本自身的调用，从而导致无限循递归。
 * 13.纯虚函数无需定义，只要声明就可以。但是如果想为纯虚函数提供定义，必须在类的外部定义，不能在类的内部为一个=0
 * 的函数提供函数体。
 * 14.含有纯虚函数的类叫抽象基类。抽象基类负责定义接口，后续的其它子类可以覆盖该接口。不能直接创建一个抽象基类的
 * 对象。如果一个派生类没有覆盖基类中的纯虚函数，则该派生类也是一个抽象基类
 * 15.派生类的成员元或者友元只能通过访问派生类对象中的基类部分的受保护成员，对于普通的基类对象中的成员不具有特殊的访问权限。
 * 16.派生访问说明符只是控制派生类用户对基类成员的访问权限，不会影响到派生类自己的成员对基类的访问权限。
 * 17.友元关系无法继承，每个类负责控制各自成员的访问权限。如果派生类的派生类是基类的友元，则派生类的派生类可以访
 * 问基类的私有成员（当私有继承时该规则不成立）。
 * 18.通过using来改变基类个别成员的的访问属性。using声明语句中的名字的访问权限由该using声明语句之前的访问说明符来
 * 决定，也就是说如果一条using声明语句出现在该类的private则该名字就是私有的。
 * 19.当继承关系存在是派生类的作用域嵌套在其基类作用域中。名字查找是在编译时进行的，所以一个对象、引用或指针的静态
 * 类型决定了该对象的哪些成员是可见的。即使静态类型和动态类型不一致的情况下，我们能使用哪些成员仍然是由静态类型决定的。
 * 由于派生类嵌套在基类作用域中，所以名字冲突时内层隐藏外层，即派生类隐藏基类。
 * 20.名字查找优于类型检查，所以内层作用域的函数不会重载外层函数，即使它们的参数类型不一致。
 * 21.如果构造函数或者析构函数调用了某个虚函数，则我们应该执行与构造函数或者析构函数所属类型相对应的虚函数版本。
 */
#ifndef QUOTE_H
#define QUOTE_H
#include<string>
#include<iostream>
#include <memory>
#include <set>
class Quote
{
public:
    Quote() =default;
    Quote ( const std::string& book,double sales_price ) :bookNo ( book ),price ( sales_price ) {}
    Quote ( const Quote& other );
    virtual ~Quote() =default;
    Quote& operator= ( const Quote& other );
    bool operator== ( const Quote& other ) const;


    std::string isbn() const;
    virtual double net_price ( std::size_t price ) const;
    virtual Quote* clone() const& {
        return new Quote ( *this );
    }
    virtual Quote* clone() && {return new Quote ( std::move ( *this ) );}
private:
    std::string bookNo="0000";//书籍的ISBN编号
protected:
    double price=0.0;//代表普通状态下不打折的价格
};





class Bulk_quote:public Quote
{
public:
    Bulk_quote() =default;
    Bulk_quote ( const std::string& , double ,std::size_t,double );
    double net_price ( std::size_t ) const override;//c++11特性，在函数参数列表后加override显示的说明该函数是覆盖了其继承的基类中的函数
    double print_total ( std::ostream&os,const Quote& item,size_t n );
    virtual Bulk_quote* clone() const& {
        return new Bulk_quote ( *this );
    }
    virtual Bulk_quote* clone() && {
        return new Bulk_quote ( std::move ( *this ) );
    }
private:
    std::size_t min_qty=0;
    double discount=0.0;
};



class Disc_quote:public Quote
{
public:
    Disc_quote() =default;
    Disc_quote ( const std::string& book,double price,std::size_t qty,double disc ) :Quote ( book,price ),quantity ( qty ),discount ( disc ) {}
    double net_price ( std::size_t ) const=0;
protected:
    std::size_t quantity=0;
    double discount=0.0;
};

class Bulk_quote1:public Disc_quote
{
public:
    Bulk_quote1() =default;
    Bulk_quote1 ( const std::string& book,double price,std::size_t qty,double disc ) :Disc_quote ( book,price,qty,disc ) {}
    double net_price ( std::size_t ) const override;

};



class Bulk_quote2:public Quote
{
public:
    /*派生类的成员和友元可以访问基类的保护成员，且只能通过派生类的对象来访问。
     * 该函数是派生类的友元，故该函数可以通过派生类的对象来访问基类的受保护成员
     */
    friend void clobber ( Bulk_quote2& s );


    /*该函数是派生类的友元但是没有通过派生类的对象来访问，故不可访问基类受保护成员,
     *该函数内部通过Quote对象访问基类的受保护成员的语句将无法通过编译
     */
    friend void clobber ( Quote& q );


    /*该函数是成员函数，如果在该函数内部通过q来访问基类的保护成员则是不允许的，编译
     * 无法通过。但是该函数内部可以直接使用基类的受保护成员，因为它是该类的成员函数，
     * 在该类的作用域中，相当于通过他自己的对象访问基类受保护成员。在类的内部，基类的
     * 受保护成员是可访问的。
     */
    void clobber2 ( Quote& q );
    void my_number() {
        std::cout<<isbn() <<std::endl;
    }

};
void clobber ( Bulk_quote2& );
void clobber ( Quote& );







double print_total ( std::ostream& os, const Quote& item, size_t n );
class Basket
{
public:
    // 	默认的合成构造
    Basket() =default;
    // 	拷贝构造
    Basket ( Basket& rhv );
    // 	移动构造
    Basket ( Basket&& rhv ) noexcept;
    // 	拷贝赋值
    Basket& operator= ( Basket& rhv );
    // 	移动赋值
    Basket& operator= ( Basket&& rhv );
    virtual ~Basket();
    void add_item ( const std::shared_ptr<Quote>& sale );

    // 	隐藏指针，使该函数接收对象而不是指针
    void add_item ( const Quote& sale ) {
        items.insert ( std::shared_ptr<Quote> ( sale.clone() ) );
    }
    void add_item ( Quote&&  sale ) {
        std::shared_ptr<Quote> ( std::move ( sale ).clone() );
    }
    double total_receipt ( std::ostream&os ) const;
private:
    static bool compare ( const std::shared_ptr<Quote>&lhs,const std::shared_ptr<Quote>&rhs );
    std::multiset< std::shared_ptr<Quote> , decltype ( compare ) * > items {compare} ;

};


#endif // QUOTE_H
