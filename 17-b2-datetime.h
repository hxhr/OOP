/* 2250748 王渝鹮 信安 */
#pragma once
using namespace std;

#include "17-b2-date.h"
#include "17-b2-time.h"

/* 如果有其它全局函数需要声明，写于此处 */

/* DateTime类的基本要求：
	1、不允许定义任何数据成员
	2、尽量少定义成员函数 
*/

class DateTime:public Date, public Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */ 

public:
	// 默认构造函数初始化为1900-01-01 00:00:00
	DateTime() : Date(1900, 1, 1), Time(0, 0, 0) {}

	// 构造函数初始化特定日期和时间
	DateTime(int y, int m, int d, int h, int mi, int s);

	void set(int y, int m, int d, int h, int mi, int s);
	void set(int y, int m, int d, int h, int mi);
	void set(int y, int m, int d, int h);
	void set(int y, int m, int d);
	void set(int y, int m);
	void set(int y);
	void set();

	void show() const;

	void get(int& y, int& m, int& d, int& h, int& mi, int& s) const;

	friend ostream& operator<<(ostream& os, const DateTime& dt);
	friend istream& operator>>(istream& is, DateTime& dt);

	DateTime(long long seconds);

	operator long long() const;

	void addSeconds(long long seconds);

	DateTime operator+(long long seconds) const;
	friend DateTime operator+(long long seconds, const DateTime& dt);
	DateTime operator+(int seconds) const;
	friend DateTime operator+(int seconds, const DateTime& dt);

	DateTime operator-(long long seconds) const;
	DateTime operator-(int seconds) const;
	friend DateTime operator-(long long seconds, const DateTime& dt);
	friend DateTime operator-(int seconds, const DateTime& dt);
	long long operator-(const DateTime& other) const;


	DateTime& operator++();
	DateTime operator++(int);
	DateTime& operator--();
	DateTime operator--(int);

	bool operator>(const DateTime& other) const;
	bool operator>=(const DateTime& other) const;
	bool operator<(const DateTime& other) const;
	bool operator<=(const DateTime& other) const;
	bool operator==(const DateTime& other) const;
	bool operator!=(const DateTime & other) const ;











};


