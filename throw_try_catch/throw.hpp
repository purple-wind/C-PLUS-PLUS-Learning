#ifndef __THROW_TRY_CATCH_H__
#define __THROW_TRY_CATCH_H__
#include<iostream>
#include<stdexcept>
class Throw {
public:
    /**
     * @brief 测试异常系统
     *
     * @return void
     */
    void test(int a)
    {
        try
        {
            int b=1;
            char c=2;
            double d=3;
            if(a==100)
                throw a;
            if(a==99)
                throw b;
            if(a==101)
                throw c;
        }
        catch(int q)
        {
            std::cout<<"a"<<std::endl;
        }
        catch(char w)
        {
            std::cout<<"b"<<std::endl;
        }
        catch(double e)
        {
            std::cout<<"c"<<std::endl;
        }
        std::cout<<"after catch"<<std::endl;
    }

    void test1(int a)
    {
        try {
            if(a==0)
                throw std::runtime_error("a eq 0");
        }
        catch(std::runtime_error run_err) {
            std::cout<<run_err.what()<<std::endl;
        }
    }

    void test2(int a)
    {
        throw std::logic_error("run test2");
    }

};


#endif