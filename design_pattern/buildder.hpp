#ifndef BUILDDER_HPP
#define BUILDDER_HPP
//指将一个复杂对象的构造与它的表示分离，使同样的构建过程可以创建不同的表示，这样的设计模式被称为建造者模式。
//它是将一个复杂的对象分解为多个简单的对象，然后一步一步构建而成。它将变与不变相分离，即产品的组成部分是不变的，但每一部分是可以灵活选择的。
//
//当我们要创建的对象很复杂时，我们要把复杂对象的创建过程和这个对象的表示分离开来，这样做的好处
//是通过一步步的进行复杂对象的构建，由于在每一步的构造过程中可以引入参数，使得经过相同的步骤创建最后
//得到的对象的展示不一样

//该模式的主要优点如下：
//封装性好，构建和表示分离。
//扩展性好，各个具体的建造者相互独立，有利于系统的解耦。
//客户端不必知道产品内部组成的细节，建造者可以对创建过程逐步细化，而不对其它模块产生任何影响，便于控制细节风险。

//其缺点如下：
//产品的组成部分必须相同，这限制了其使用范围。
//如果产品的内部变化复杂，如果产品内部发生变化，则建造者也要同步修改，后期维护成本较大。


#include<string>
class Product
{
    public:
        void setPartA(char c){ part1 = c;}
        void setPartB(int integer){ part2 = integer;}
        void setPartC(std::string str){part3 = str;}

        char part1;
        int part2;
        std::string part3;
};

//建造者基类，抽象接口
class Builder
{
    public:
        virtual void BuilderPartA() = 0;
        virtual void BuilderPartB() = 0;
        virtual void BuilderPartC() = 0;
        virtual Product* GetProduct()
        {
            return m_product;
        }
    protected:
        Product* m_product = new Product();

};

//实际的建造者派生类
class ConcreateBuilder1: public Builder
{
    public:
        virtual void BuilderPartA()
        {
            //用自己的方法构造产品的partA
            std::cout << __FUNCTION__ << std::endl;
            m_product->setPartA('a');
        }
        virtual void BuilderPartB()
        {
            //用自己的方法构造产品的partB
            std::cout << __FUNCTION__ << std::endl;
            m_product->setPartB(1);

        }
        virtual void BuilderPartC()
        {
            //用自己的方法构造产品的partC
            std::cout << __FUNCTION__ << std::endl;
            m_product->setPartC("abc");

        }
};

class ConcreateBuilder2: public Builder
{
        virtual void BuilderPartA()
        {
            std::cout << __FUNCTION__ << std::endl;
            m_product->setPartA('x');
        }
        virtual void BuilderPartB()
        {
            std::cout << __FUNCTION__ << std::endl;
            m_product->setPartB(2);

        }
        virtual void BuilderPartC()
        {
            std::cout << __FUNCTION__ << std::endl;
            m_product->setPartC("xyz");

        }
};

//建造师
class Director
{
    public:
        Director(Builder* bld)
        {
            m_build = bld;
        }

        Product* Build()
        {
            m_build->BuilderPartA();
            m_build->BuilderPartB();
            m_build->BuilderPartC();
            return m_build->GetProduct();
        }

    private:
        Builder* m_build;
};



#endif // BUILDDER_HPP
