#include <assert.h>
void test_assert1(int x)
{
    // 使用了断言 assert(expression) ，这是一个宏，它的参数是一个表达式，这个表达式通常返回一个布尔类型的值，
    // 并且要求表达式必须为 true 程序才能继续向下执行，否则会直接中断。assert 是一个运行时断言，也就是说它只有在程序运行时才能起作用
    assert(x > 0);
}


void test_assert2(int x)
{
    // 静态断言 static_assert，所谓静态就是在编译时就能够进行检查的断言，不满足断言条件(第一个参数为假)时编译报错。
    // 使用时不需要引用头文件。静态断言的另一个好处是，可以自定义违反断言时的错误提示信息
    // 静态断言使用起来非常简单，它接收两个参数：
    // 参数1：断言表达式，这个表达式通常需要返回一个 bool值
    // 参数2：警告信息，它通常就是一段字符串，在违反断言（表达式为false）时提示该信息
    // 因为静态断言是在编译期检查，所以传给断言的第一个表示式必须是一个常量表达式(constexpr)，以保证在编译期知道值
    static_assert(sizeof(x) == 4, "x not equeal 4");
}

// 断言语句可以出现constexpr函数中
constexpr int test_assert3(int x)
{
    static_assert(sizeof(x) == 4, "x not equal 4");
    return x;
}


//constexpr函数的参数不是常量属性,不能用于静态断言,下面函数编译不过
//constexpr int test_assert4(int x)
//{
//    static_assert(x > 0, "x 小于0");
//    return x;
//}

