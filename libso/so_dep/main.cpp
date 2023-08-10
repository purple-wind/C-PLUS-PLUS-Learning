//考虑如下场景：
//liba.so依赖libb.so(即liba.so中的函数调用了libb.so中的函数)，liba.so源码是a.cpp,libb.so的源码是b.cpp
//在编译liba.so时动态链接libb.so
//	g++ -shared -fPIC a.cpp -L. -lb -o liba.so 
//	使用ldd查看liba.so的链接关系是liba.so-->libb.so(其实此时我们就会发现libb.so是not find,这就是后面出问题的一切的根源所在)
//main.cpp使用了liba.so中的函数，在编译main.cpp时
//	使用g++ test.cpp -L. -la 编译失败提示liba.so使用的libb.so中的函数是未定义的
// 	使用g++ test.cpp -L. -la -lb 可以编译通过，但是ldd查看找不到liba.so
//	此时可能会想到使用-rpath指定test运行时查找的路径,故使用g++ main.cpp -L. -la -lb -Wl,-rpath=.编译，可以编译通过，
//  运行时也可以链接到liba.so，但是无法链接到libb.so，实际上此处的-rpath只能指定了test运行时liba.so的库路径，
//  但是没有指定liba.so依赖的libb.so的路径。此处虽然也-lb了，但是只是为了满足liba.so对libb.so的依赖，
//  并不是test对libb.so的直接依赖，因为test.cpp并没有使用b中的函数。
//  实际上也可以写成g++ main.cpp -L. -la -Wl,-rpath=.但是依旧在运行时无法链接到libb.so
//  这就是-rpath只能指定当前编译对象的运行时直接依赖库路径，对于间接依赖无效(依赖库的依赖库)路径无效。
//
//  那上面的情况怎么解决呢？能不能指定liba.so的依赖库libb.so的路径呢？目前解决办法如下：
//  	1.在编译liba.so的时候指定它自己依赖库的-rpath路径(即运行时依赖libb.so库的路径)，
//			然后在编译test时指定运行时依赖库liba.so的路径，且此时只需要链接liba.so即可
//            	g++ -shared -fPIC a.cpp -L. -lb -Wl,-rpath=. -o liba.so
//              g++ main.cpp -L. -la -Wl,-rpath=.
//		2.在编译liba.so的时候不指定动态依赖关系，此时使用ldd查看liba.so是静态链接，然后在编译main.cpp的
//		  时候直接链接liba.so和libb.so(必须同时链接liba.so libb.so)，然后指令test运行时依赖库liba.so libb.so的路径
//        		g++ -shared -fPIC a.cpp -o liba.so
//              g++ main.cpp -L. -la -lb -Wl,-rpath=. #如果此处不指定-rpath则运行时liba.so libb.so都提示找不到

#include"a.h"
int main()
{
		funa();
		return 0;
}
