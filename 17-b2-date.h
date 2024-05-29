/* 2250748 王渝鹮 信安 */

#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

bool is_leapyear(int y);
int day_in_month(int y, int m);








/* 如果有需要的宏定义、只读全局变量等，写于此处 */

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */

	// 构造函数
	Date(); // 默认构造函数
	Date(int y, int m, int d);

	// set 成员函数的重载
	void set(int y, int m, int d);
	void set(int y, int m);
	void set(int y);

	// get 成员函数
	void get(int& y, int& m, int& d) const;

	// 显示日期的成员函数
	void show() const;
	//无回车版
	void show_endless() const;


	// 转换构造函数,从19000101开始的天数，int转date
	Date(int days);

	//类型转换函数 date转int
	operator int() const;

	void addDays(int days);
	//重载+   date+int
	Date operator+(int days) const;
	//int+date
	friend Date operator+(int days, const Date& date);

	//重载-   date-int=date
	Date operator-(int days) const;
	//date-date=int
	int operator-(const Date& other) const;

	//++ --前缀后缀
	// 前缀递增运算符重载
	Date& operator++();
	// 后缀递增运算符重载
	Date operator++(int);

	// 前缀递减运算符重载
	Date& operator--();
	// 后缀递减运算符重载
	Date operator--(int);

	//重载输入输出运算符
	friend ostream& operator<<(ostream& os, const Date& date);
	friend istream& operator>>(istream& is, Date& date);

	// 比较运算符重载
	bool operator>(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator==(const Date& rhs) const;
	bool operator!=(const Date& rhs) const;

};

