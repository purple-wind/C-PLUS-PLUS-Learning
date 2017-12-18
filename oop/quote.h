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
 *  对于每个静态成员来说都只存在唯一的实例。
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
 * 
 * 
 * 
 * 
 */
#ifndef QUOTE_H
#define QUOTE_H
#include<string>
class Quote
{
public:
    Quote() =default;
    Quote ( const std::string& book,double sales_price ) :bookNo ( book ),price ( sales_price ) {}
    Quote ( const Quote& other );
    ~Quote() =default;
    Quote& operator= ( const Quote& other );
    bool operator== ( const Quote& other ) const;


    std::string isbn() const;
    virtual double net_price ( std::size_t price ) const;
    
private:
    std::string bookNo;//书籍的ISBN编号
protected:
    double price=0.0;//代表普通状态下不打折的价格
};





class Bulk_quote:public Quote
{
public:
    Bulk_quote() =default;
    Bulk_quote ( const std::string& , double ,std::size_t,double );
    double net_price ( std::size_t ) const override;
private:
    std::size_t min_qty=0;
    double discount=0.0;
};













#endif // QUOTE_H
