#ifndef FACTORY_HPP
#define FACTORY_HPP
#include<iostream>
class BaseProduct
{
    public:
        BaseProduct()
        {
        }
};

class Product1:public BaseProduct
{
    public:
        Product1()
        {
            std::cout << "Product1" << std::endl;
        }
};

class Product2:public BaseProduct
{
    public:
        Product2()
        {
            std::cout << "Product2" << std::endl;
        }
};

//简单工厂
class SimpleFactory
{
    public:
        BaseProduct* Create(std::string type)
        {
            if(type == "Product1")
                return new Product1();
            else if(type == "Product2")
                return new Product2();
            else
                return new BaseProduct();
        }
};

//普通工厂
class BaseFactory
{
    public:
        virtual BaseProduct* Create()
        {
            return new BaseProduct();
        }
};

class FactoryProduct1: public BaseFactory
{
    public:
        BaseProduct* Create()
        {
            return new Product1();
        }

};

class FactoryProduct2: public BaseFactory
{
    public:
        BaseProduct* Create()
        {
            return new Product2();
        }
};


//抽象工厂
class AbstractProduct0{

};

class ProductA0:public AbstractProduct0
{
    public:
        ProductA0()
        {
            std::cout << "ProductA0" << std::endl;
        }
};

class ProductB0:public AbstractProduct0
{
    public:
        ProductB0()
        {
            std::cout << "ProductB0" << std::endl;
        }
};

class AbstractProduct1{

};

class ProductA1:public AbstractProduct1
{
    public:
        ProductA1()
        {
            std::cout << "ProductA1" << std::endl;
        }
};

class ProductB1:public AbstractProduct1
{
    public:
        ProductB1()
        {
            std::cout << "ProductB1" << std::endl;
        }
};


class AbstractProduct2
{

};

class ProductA2:public AbstractProduct2
{
    public:
        ProductA2()
        {
            std::cout << "ProductA2" << std::endl;
        }
};

class ProductB2:public AbstractProduct2
{
    public:
        ProductB2()
        {
            std::cout << "ProductB2" << std::endl;
        }
};


class AbstractFactory
{
    public:
        virtual AbstractProduct0* Create0() = 0;

        virtual AbstractProduct1* Create1() = 0;

        virtual AbstractProduct2* Create2() = 0;
};

class FactoryProductA:public AbstractFactory
{
    public:
        AbstractProduct0* Create0()
        {
            return new ProductA0();
        }

        AbstractProduct1* Create1()
        {
            return new ProductA1();
        }

        AbstractProduct2* Create2()
        {
            return new ProductA2();
        }
};

class FactoryProductB:public AbstractFactory
{
    public:
        AbstractProduct0* Create0()
        {
            return new ProductB0();
        }

        AbstractProduct1* Create1()
        {
            return new ProductB1();
        }

        AbstractProduct2* Create2()
        {
            return new ProductB2();
        }
};

#endif // FACTORY_HPP
