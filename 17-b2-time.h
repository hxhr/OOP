/* 2250748 王渝鹮 信安 */
#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

/* Time类的声明 */ 
class Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */ 
	int hour;
	int minute;
	int second;
public:
	/* 允许需要的成员函数及友元函数的声明 */
	
		// 构造函数
	Time(); // 默认构造函数
	Time(int h, int m, int s);

	// set 成员函数的重载
	void set(int h, int m, int s);
	void set(int h, int m);
	void set(int h);

	// get 成员函数
	void get(int& h, int& m, int& s) const;

	// 显示日期的成员函数
	void show() const;

	// 转换构造函数,从19000101开始的天数，int转date
	Time(int s);

	//类型转换函数 date转int
	operator int() const;

	void adds(int s);
	//重载+   date+int
	Time operator+(int s) const;
	//int+date
	friend Time operator+(int s, const Time& time);

	//重载-   date-int=date
	Time operator-(int s) const;
	//date-date=int
	int operator-(const Time& other) const;

	//++ --前缀后缀
	// 前缀递增运算符重载
	Time& operator++();
	// 后缀递增运算符重载
	Time operator++(int);

	// 前缀递减运算符重载
	Time& operator--();
	// 后缀递减运算符重载
	Time operator--(int);

	//重载输入输出运算符
	friend ostream& operator<<(ostream& os, const Time& time);
	friend istream& operator>>(istream& is, Time& time);

	// 比较运算符重载
	bool operator>(const Time& rhs) const;
	bool operator>=(const Time& rhs) const;
	bool operator<(const Time& rhs) const;
	bool operator<=(const Time& rhs) const;
	bool operator==(const Time& rhs) const;
	bool operator!=(const Time& rhs) const;


};
