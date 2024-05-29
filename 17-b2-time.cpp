/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- 给出Time类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */ 



Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int h, int m, int s)
{
	if ((h < 0 || h>23) || (m < 0 || m>59) || (s < 0 || s>59)) {
		hour = 0;
		minute = 0;
		second = 0;
	}
	else {
		hour = h;
		minute = m;
		second = s;
	}
}

//set函数
void Time::set(int h, int m, int s)
{
	//任意错都直接设成00-00-00
	if ((h < 0 || h>23) || (m < 0 || m>59) || (s < 0 || s>59)) {
		hour = 0;
		minute = 0;
		second = 0;
	}
	else {
		hour = h;
		minute = m;
		second = s;
	}
}

void Time::set(int h, int m) 
{
	set(h, m, 0);
}

void Time::set(int h)
{
	set(h, 0, 0);
}




void Time::get(int& h, int& m, int& s) const
{
	h = hour;
	m = minute;
	s = second;
}

void Time::show() const
{
	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << ":" << setw(2) << setfill('0') << second << endl;

}

Time::Time(int s)
{
	hour = 0;
	minute = 0;
	second = 0;
	const int total_s = 24 * 60 * 60;
	if (s < 0) {
		s = total_s + s % total_s;
	}
	else {
		s = s % total_s;
	}
	while (s >= 3600) {
		s -= 3600;
		hour++;
	}
	while (s > 0) {
		if (s >= 60) {
			s -= 60;
			minute++;
		}
		else {
			second = s;
			s = 0;
		}
	}

}

Time::operator int() const
{
	int s = 0;
	for (int h = 0; h < hour; ++h) {
		s += 3600;
	}

	// 计算当前年份中，从1月到当前月份的天数（不包括当前月份）
	for (int m = 0; m < minute; ++m) {
		s += 60;
	}
	s += second;
	return s;

}

void Time::adds(int s)
{
	s += (int)*this;
	hour = 0;
	minute = 0;
	second = 0;
	const int total_s = 24 * 60 * 60;
	if (s < 0) {
		s = total_s + s % total_s;
	}
	else {
		s = s % total_s;
	}
	while (s >= 3600) {
		s -= 3600;
		hour++;
	}
	while (s > 0) {
		if (s >= 60) {
			s -= 60;
			minute++;
		}
		else {
			second = s;
			s = 0;
		}
	}


}

Time Time::operator+(int s) const
{
	Time newTime = *this; // 创建当前对象的副本
	newTime.adds(s); // 在副本上添加天数
	return newTime; // 返回修改后的副本

}

Time operator+(int s, const Time& time)
{
	return time + s;
}

Time Time::operator-(int s) const
{
	Time newTime = *this; // 创建当前对象的副本
	newTime.adds(-s); // 在副本上添加天数
	return newTime; // 返回修改后的副本

}

int Time::operator-(const Time& other) const
{
	int s1 = (int)(*this);
	int s2 = (int)(other);
	return s1 - s2;
}

Time& Time::operator++()
{
	this->adds(1); // 加一天
	return *this; // 返回当前对象的引用
}

Time Time::operator++(int)
{
	Time temp = *this; // 保存当前状态
	++(*this); // 使用前缀递增运算符
	return temp; // 返回未修改的对象

}

Time& Time::operator--()
{
	this->adds(-1); // 减一天
	return *this; // 返回当前对象的引用
}

Time Time::operator--(int)
{
	Time temp = *this; // 保存当前状态
	--(*this); // 使用前缀递减运算符
	return temp; // 返回未修改的对象
}

ostream& operator<<(ostream& os, const Time& time)
{
	os << setw(2) << setfill('0') << time.hour << ":" << setw(2) << setfill('0') << time.minute << ":" << setw(2) << setfill('0') <<time.second;
	return os;

}


istream& operator>>(istream& is, Time& time)
{
	//错一个就1900-1-1，直接让set帮我判了 
	is >> time.hour;
	is >> time.minute;
	is >>time.second;
	time.set(time.hour, time.minute, time.second);

	return is;
}


bool Time::operator>(const Time& rhs) const
{
	// 首先比较年份，如果年份相同，则比较月份，如果月份也相同，则比较日期
	if (hour != rhs.hour) return hour > rhs.hour;
	if (minute != rhs.minute) return minute > rhs.minute;
	return second > rhs.second;
}

bool Time::operator>=(const Time& rhs) const
{
	return *this > rhs || *this == rhs;
}

bool Time::operator<(const Time& rhs) const
{
	return !(*this >= rhs);
}

bool Time::operator<=(const Time& rhs) const
{
	return *this < rhs || *this == rhs;
}

bool Time::operator==(const Time& rhs) const
{
	return hour == rhs.hour && minute== rhs.minute&& second == rhs.second;
}

bool Time::operator!=(const Time& rhs) const
{
	return !(*this == rhs);
}
