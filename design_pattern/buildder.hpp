#ifndef BUILDDER_HPP
#define BUILDDER_HPP
//当我们要创建的对象很复杂时，我们要把复杂对象的创建过程和这个对象的表示分离开来，这样做的好处
//是通过一步步的进行复杂对象的构建，由于在每一步的构造过程中可以引入参数，使得经过相同的步骤创建最后
//得到的对象的展示不一样
class Product
{

};

//建造者基类，抽象接口
class Builder
{
    public:
        virtual void BuilderPartA() = 0;
        virtual void BuilderPartB() = 0;
        virtual void BuilderPartC() = 0;
        virtual Product* GetProduct() = 0;

};

//实际的建造者派生类
class ConcreateBuilder1: public Builder
{
    public:
        virtual void BuilderPartA()
        {
            std::cout << __FUNCTION__ << std::endl;
        }
        virtual void BuilderPartB()
        {
            std::cout << __FUNCTION__ << std::endl;

        }
        virtual void BuilderPartC()
        {
            std::cout << __FUNCTION__ << std::endl;
        }
        Product* GetProduct()
        {
            BuilderPartA();
            BuilderPartB();
            BuilderPartC();
            return new Product();
        }
};

class ConcreateBuilder2: public Builder
{
    public:
        virtual void BuilderPartA()
        {
            std::cout << __FUNCTION__ << std::endl;
        }
        virtual void BuilderPartB()
        {
            std::cout << __FUNCTION__ << std::endl;

        }
        virtual void BuilderPartC()
        {
            std::cout << __FUNCTION__ << std::endl;
        }
        Product* GetProduct()
        {
            BuilderPartA();
            BuilderPartB();
            BuilderPartC();
            return new Product();
        }
};

//设计师
class Director
{
    public:
        Director(Builder* bld)
        {
            m_build = bld;
        }

        void Build()
        {
            m_build->BuilderPartA();
            m_build->BuilderPartB();
            m_build->BuilderPartC();
        }

    private:
        Builder* m_build;
};



#endif // BUILDDER_HPP
