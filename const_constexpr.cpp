#include<iostream>
#include<time.h>
#include<chrono>
using namespace std;
//在这个函数里面，由于constexpr稀释的是fib1这个函数，因此每一次计算的结果都会作为一个常量保存下来
//这个实现的复杂度等同于迭代的方法，基本上为O(n)。
constexpr long int fib1(int n)
{
    return (n <= 1)? n : fib1(n-1) + fib1(n-2); //只能包含一个retrun语句
}
//下面这个函数的时间复杂度为O(2^n)
long int fib2(int n){
        return (n <= 1)? n : fib2(n-1) + fib2(n-2);
}
int main ()
{
    // value of res is computed at compile time.
    int a = 30;
    auto start = chrono::system_clock::now().time_since_epoch();
    const long int res = fib1(a);
    auto end = chrono::system_clock::now().time_since_epoch();
    cout << "Totle Time fib1 : " <<chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "s" << endl;
    start = chrono::system_clock::now().time_since_epoch();
    std::cout<<"res="<<res<<std::endl;
    const long res1 = fib2(a);
    end = chrono::system_clock::now().time_since_epoch();
    cout << "Totle Time fib2 : " <<chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "s" << endl;
    cout << res1 << std::endl;
    return 0;
}
