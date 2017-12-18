#ifndef __MY_FRIEND_H__
#define __MY_FRIEND_H__
#include<iostream>
class A{
private:
	static int a;
	friend class B;
};

class B{
public:
	void run()
	{
		std::cout<<"a="<<A::a<<std::endl;
	}
};

#endif