/* 2250748 王渝鹮 信安 */

#pragma once

#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString {
private:

public:
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
	char* content;
	int   len;
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */

	void init(const char* str);//构造函数中会被调用，避免几个构造函数总需要堆叠重复的代码


	TString(); // 默认构造函数
	TString(const char* str); // 从 C 字符串初始化
	TString(const TString& other); // 拷贝构造函数
	TString(char c);//用于+时的隐式转换
	TString(int n);  // 专门处理 NULL 的构造函数
	~TString(); // 析构函数

	friend istream& operator>>(istream& is, TString& str);//重载>>的友元函数
	friend ostream& operator<<(ostream& os, const TString& str);//重载<<的友元函数

	const char* c_str() const;//取字符串，只读操作

	TString& operator=(const TString& other); // 从另一个TString对象赋值
	TString& operator=(const char* str); // 从C风格字符串赋值

	TString operator+(const TString& rhs) const; //TString + char / char* / TString
	friend TString operator+(char lhs, const TString& rhs);//char+TString
	friend TString operator+(const char* lhs, const TString& rhs);//char*+TString

	TString& operator+=(const TString& rhs);//因为我可以隐式转换且+=没有左操作，所以只写一个成员函数就行

	//TString& append(const TString& rhs);//char和char*走隐式转换

	TString operator-(const TString& rhs) const;//char和char*走隐式转换
	TString& operator-=(const TString& rhs); //因为我可以隐式转换且 -= 没有左操作，所以只写一个成员函数就行

	TString& operator*=(int factor);
	TString operator*(int factor);

	TString operator!() const; // 重载 ! 运算符，用于字符串反转

	// 比较运算符声明
	bool operator>(const TString& rhs) const;
	bool operator<(const TString& rhs) const;
	bool operator==(const TString& rhs) const;
	bool operator!=(const TString& rhs) const;
	bool operator>=(const TString& rhs) const;
	bool operator<=(const TString& rhs) const;

	// 为比较运算符声明友元函数
	friend bool operator>(const TString& lhs, const char* rhs);
	friend bool operator<(const TString& lhs, const char* rhs);
	friend bool operator==(const TString& lhs, const char* rhs);
	friend bool operator!=(const TString& lhs, const char* rhs);
	friend bool operator>=(const TString& lhs, const char* rhs);
	friend bool operator<=(const TString& lhs, const char* rhs);

	friend bool operator>(const char* lhs, const TString& rhs);
	friend bool operator<(const char* lhs, const TString& rhs);
	friend bool operator==(const char* lhs, const TString& rhs);
	friend bool operator!=(const char* lhs, const TString& rhs);
	friend bool operator>=(const char* lhs, const TString& rhs);
	friend bool operator<=(const char* lhs, const TString& rhs);

	int length() const;

	char operator[](int index) const; // 常量版本，用于访问字符
	char& operator[](int index); // 非常量版本，用于修改字符
};

/* 如果有其它全局函数需要声明，写于此处 */
int TStringLen(const TString& str);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */

