#ifndef ATTR_HPP
#define ATTR_HPP
/*
 *1. gnu可以指定函数或者变量的属性，属性用[[]]符号表示，里面包裹的就是属性内容
 *2.
 *
 *
 *
 */
#include <iostream>
[[gnu::always_inline]] [[gnu::hot]] [[gnu::const]] [[nodiscard]] inline int f(); // 声明 f 带四个属性
[[gnu::always_inline, gnu::const, gnu::hot, nodiscard]] int f(); // 同上，但使用含有四个属性的单个属性说明符

// C++17:
[[using gnu : const, always_inline, hot]] [[nodiscard]] int f[[gnu::always_inline]](); // 属性可出现于多个说明符中
int f() { return 0; }

int main() {
 std::cout<<"test attr"<<std::endl;
}
#endif // ATTR_HPP
