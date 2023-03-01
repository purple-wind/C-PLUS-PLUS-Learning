#ifndef __MY_FRIEND_H__
#define __MY_FRIEND_H__
#include<iostream>


class Derived_b;
class Base{
public:
	int m_public=0;
protected:
	int m_protected=1;
private:
	int m_private=2;
	friend Derived_b;
};

class Derived_a:public Base{
private:
	int m_ba;
};
class Derived_c:private Base{
private:
	int m_bc;
};

class Derived_b{
public:
    void print1 ( Base& b ) {
        std::cout<<"m_protected="<<b.m_protected<<std::endl;
    }
    void pirnt2 ( Derived_a& b ) {
    /*这句无法通过，因为友元不具有传递性，虽然Derived_b是Base的友元，同时Derived_a继承自Base
     * 但是Derived_b不是Derived_a的友元，所以无法访问到Derived_a的私有部分。
     */
// 		std::cout<<"m_ba="<<b.m_ba<<std::endl;

    /*因为Derived_b是Base的友元，所以Derived_b可以访问到Base的私有部分，即使在Base的派生类的基类部分。
     * 由此可见，类的访问权限是由类本身控制(无继承关系的时候)
     */
    std::cout<<"m_protected="<<b.m_protected<<std::endl;
    }
	/*Derived_c私有继承自Base，Derived_b是Base的友元类，根据友元关Derived_b可以访问Base的私有部分，根据
	 * 继承关系可知Derived_b不可访问Derived_c中的基类Base的私有部分。根据测试可知，继承关系更强于友元
	 * 关系。当两种关系冲突时，优先于继承关系。下面的函数无法编译通过。
	 */
    void print3 ( Derived_c& c ) {
//         std::cout<<"print3="<<c.m_protected<<std::endl;
    }
};


#endif





