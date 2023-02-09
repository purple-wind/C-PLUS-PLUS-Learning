struct A
{
    public:
        ~A()
        {
            std::cout<<"delete A,a="<<a<<std::endl;
        }
    int a = 0;
};

class DelArray{
    public:
        delarray()
        {
            for(int i = 0; i<5;i++)
            {
                a[i].a = i;
            }
            std::cout<<"after constructor"<<std::endl;
        }
    private:
        A a[5];
};


int main(int argc, char* argv[])
{
    /*内置数组在出作用域时会自动析构数组内的元素，且从后向前析构*/
    {

        A a[3];
        for(int i = 0; i<3;i++)
        {
            a[i].a = i;
        }
        std::cout<<"after"<<std::endl;
    }

    /*当数组作为类的成员变量时，类析构时会自动析构数组成员内的元素，且从后向前析构*/
    {
        DelArray da;
    }
    cout<<"out"<<endl;
    return 0;
}



out:
    after
    delete A,a=2
    delete A,a=1
    delete A,a=0
    after constructor
    delete A,a=4
    delete A,a=3
    delete A,a=2
    delete A,a=1
    delete A,a=0
    out
