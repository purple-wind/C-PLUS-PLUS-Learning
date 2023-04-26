int a0 = 1;//初始化的全局对象在data段
int a1;//未初始化的全局对象在bss段
extern int b;//申明外部符号，如果该单元中未使用，不会出现在符号表中
const int c0;//未初始化的const全局对象也遵守未初始化的在bss段，初始化的在data段,可只定义const全局对象不初始化，但是无法修改值，实际上没什么意义
const int c1 = 1;//初始化的const变量在只读data段
static int d0;//静态全局变量也遵循初始化在data段，未初始化在bss段
static int d1 = 1;
//函数在代码段
void fun123()
{
	b = 1;//无此句b不会出现在符号表中
	int x0 = 100;//局部的非静态变量无法出现在符号表中
	int x1;
	static int z0 = 3;//静态局部变量，初始化的在data段，未初始化的在bss段
	static int z1;	
	//c0 = 2;
}



// 来自 symbol_info.o 的符号：
// Name                  Value           Class        Type         Size             Line  Section
// 
// a0                  |0000000000000000|   D  |            OBJECT|0000000000000004|     |.data
// a1                  |0000000000000004|   C  |            OBJECT|0000000000000004|     |*COM*
// b                   |                |   U  |            NOTYPE|                |     |*UND*
// c0                  |0000000000000004|   C  |            OBJECT|0000000000000004|     |*COM*
// c1                  |0000000000000000|   R  |            OBJECT|0000000000000004|     |.rodata
// d0                  |0000000000000000|   b  |            OBJECT|0000000000000004|     |.bss
// d1                  |0000000000000004|   d  |            OBJECT|0000000000000004|     |.data
// z1.1922             |0000000000000004|   b  |            OBJECT|0000000000000004|     |.bss
// z0.1921             |0000000000000008|   d  |            OBJECT|0000000000000004|     |.data
// fun123              |0000000000000000|   T  |              FUNC|000000000000001c|     |.text
// 
// 
// 来自 libsymbolinfo.so 的符号：
// Name                  Value           Class        Type         Size             Line  Section
// 
// a0                  |0000000000004020|   D  |            OBJECT|0000000000000004|     |.data
// a1                  |0000000000004038|   B  |            OBJECT|0000000000000004|     |.bss
// b                   |                |   U  |            NOTYPE|                |     |*UND*
// d1                  |0000000000004024|   d  |            OBJECT|0000000000000004|     |.data
// d0                  |0000000000004030|   b  |            OBJECT|0000000000000004|     |.bss
// c0                  |000000000000403c|   B  |            OBJECT|0000000000000004|     |.bss
// c1                  |0000000000002000|   R  |            OBJECT|0000000000000004|     |.rodata
// z0.1921             |0000000000004028|   d  |            OBJECT|0000000000000004|     |.data
// z1.1922             |0000000000004034|   b  |            OBJECT|0000000000000004|     |.bss
// fun123              |00000000000010f9|   T  |              FUNC|000000000000001f|     |.text

