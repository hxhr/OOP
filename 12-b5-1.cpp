/* 信安 2250748 王渝鹮 */
#include <iostream>
using namespace std;

//代码部分求助gpt。已学会应用
//1. 什么是模板？
//模板可以视为一个创建函数或类的蓝图。您可以使用模板为不同的数据类型创建函数或类，
//而无需为每个类型单独编写代码。

// 2、基本语法
//template <typename t>
//t add(t a, t b) {
//	return a + b;
//}
//调用时，可以显示规定模板参数，也可以让编译器自己推测

//3、多模板参数（本题就是

//4、什么是非类型模板参数？
//在c++中，模板不仅可以接受类型作为参数，还可以接受一个具体的值或常量表达式。
//当模板参数是一个值而不是一个类型时，我们称它为非类型模板参数。


/***************************************************************************
  函数名称：test
  功    能：输出给定数组的大小
  输入参数：数组的引用
  返 回 值：无
  说    明：使用模板函数处理不同类型和大小的数组
***************************************************************************/
template<typename t, size_t n>
void test(t(&array)[n])	//使用模板以处理不同类型和大小的数组
{
	cout << sizeof(array) << endl;
}

/***************************************************************************
  函数名称：tj_strcpy_s
  功    能：安全地将src字符串复制到dst字符串
  输入参数：dst (要复制的目标串), src (要复制的源串), size (dst的大小)
  返 回 值：复制的字符串
  说    明：确保不会溢出目标字符串
***************************************************************************/
char* tj_strcpy_s(char* dst, const char* src, size_t size)	
{
	char* d = dst;

	while (*src != '\0' && d - dst < int(size) - 1)
		*d++ = *src++;
	*d = '\0';

	return dst;
}

int main()
{
	int t1[10];
	double t2[20];
	test(t1);	//期望输入40
	test(t2);	//期望输出160

	char s1[10], s2[20];
	const char* s = "welcome to tongji university!";
	cout << tj_strcpy_s(s1, s, sizeof(s1)) << '*' << endl; //期望输出：welcome t*
	cout << tj_strcpy_s(s2, s, sizeof(s2)) << '*' << endl; //期望输出：welcome to tongji u*

	return 0;
}
