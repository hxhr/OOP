/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

/* --- 给出DateTime类的成员函数的体外实现(含友元及其它必要的公共函数)  ---

	几个重要提示：
	1、6参构造函数能否空函数体，直接激活Date和Time的构造函数？
	2、1参构造函数，能否不用循环，直接借助Date和Time的一参构造来快速实现？ 
	3、DateTime转long long的类型转换函数，能否不用循环，借助赋值兼容规则快速实现（(最短可以做到只有一句return)） 
	4、DateTime土n的操作，需要定义几个类型的运算符重载？ 
*/ 

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/


DateTime::DateTime(int y, int m, int d, int h, int mi, int s) 
{
	// 先判断所有参数是否合法
	if (!(y >= 1900 && y <= 2099) || !(m >= 1 && m <= 12) ||
		!(d >= 1 && d <= day_in_month(y, m)) || (h < 0 || h > 23) ||
		(mi < 0 || mi > 59) || (s < 0 || s > 59)) {
		// 如果有任何一个参数非法，则全部初始化为默认值
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
	}
	else {
		// 如果所有参数都合法，才使用传入的参数
		Date::set(y, m, d);
		Time::set(h, mi, s);
	}
}


void DateTime::set(int y, int m, int d, int h, int mi, int s)
{
	//只要有一个非法就直接初始值
	if ((!(y >= 1900 && y <= 2099) || !(m >= 1 && m <= 12) || !(d >= 1 && d <= day_in_month(y, m))) || (h < 0 || h>23) || (mi < 0 || mi>59) || (s < 0 || s>59)) {
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
	}
	else {
		Date::set(y, m, d);
		Time::set(h, mi, s);
	}
}

void DateTime::set(int y, int m, int d, int h, int mi) 
{
	set(y, m, d, h, mi, 0);
}
void DateTime::set(int y, int m, int d, int h) 
{
	set(y, m, d, h, 0, 0);
}
void DateTime::set(int y, int m, int d)
{
	set(y, m, d, 0, 0, 0);
}
void DateTime::set(int y, int m)
{
	set(y, m, 1, 0, 0, 0);
}
void DateTime::set(int y)
{
	set(y, 1, 1, 0, 0, 0);
}
void DateTime::set()
{
	set(1900, 1, 1, 0, 0, 0);
}

void DateTime::show() const
{
	Date::show_endless();
	cout << " ";
	Time::show();

}


void DateTime::get(int& y, int& m, int& d, int& h, int& mi, int& s) const
{
	// 从 Date 类中获取日期
	Date::get(y, m, d);
	// 从 Time 类中获取时间
	Time::get(h, mi, s);
}

ostream& operator<<(ostream& os, const DateTime& dt)
{
	// 先输出日期部分，再输出时间部分
	os << static_cast<const Date&>(dt) << ' ';
	os << static_cast<const Time&>(dt);
	return os;
}

istream& operator>>(istream& is, DateTime& dt) 
{
	// 读取日期和时间
	// 假设日期和时间的输入格式为：yyyy-mm-dd hh:mm:ss
	int year, month, day, hour, minute, second;

	is >> year >> month >> day;
	is >> hour  >> minute >> second;

	if ((!(year >= 1900 && year <= 2099) || !(month >= 1 && month <= 12) || !(day >= 1 && day <= day_in_month(year, month))) || (hour < 0 || hour>23) || (minute < 0 || minute>59) || (second < 0 || second>59)) {
		dt.set();
	}
	else {
		dt.set(year, month, day, hour, minute, second);
	}
	return is;
}



//DateTime::DateTime(long long seconds) {
//	// 总天数 = 秒数 / (24小时 * 60分钟 * 60秒)
//	int days = static_cast<int>(seconds / (24 * 60 * 60));
//
//	// 将天数转换为日期
//	*static_cast<Date*>(this) = Date(days);
//
//	// 计算剩余秒数，并转换为时间
//	int remainingSeconds = static_cast<int>(seconds % (24 * 60 * 60));
//	*static_cast<Time*>(this) = Time(remainingSeconds);
//}


//逻辑对的但是总周期秒数不知道为啥不对，好在测试程序告诉我正确的了，先用着，之后再研究为啥
DateTime::DateTime(long long seconds)
{
	//我这么算出来6311347200
	//const long long totalDays = 365LL * 200 + 48; // 1900年到2099年的总天数（包括闰年）
	//const long long totalSecondsInCycle = totalDays * 24 * 60 * 60; // 总周期内的秒数6311347200

	//正确的是6311433600
	const long long totalSecondsInCycle = 6311433600;
	// 使秒数在循环内
	seconds = seconds % totalSecondsInCycle ;//281028607

	// 计算天数和剩余秒数
	long long remainingSeconds = seconds % (24 * 60 * 60);
	long long days;
	if (remainingSeconds < 0) {
		days = seconds / (24 * 60 * 60)-1;//3252
	}
	else {
		days = seconds / (24 * 60 * 60);//3252
	}


	// 使用Date和Time的转换构造函数
	*static_cast<Date*>(this) = Date((int)days);
	*static_cast<Time*>(this) = Time((int)remainingSeconds);
}


DateTime::operator long long() const 
{
	// 获取自1900年1月1日以来的天数
	long long days = static_cast<long long>(static_cast<const Date&>(*this));

	// 获取当天的秒数
	long long secondsToday = static_cast<long long>(static_cast<const Time&>(*this));

	// 将天数转换为秒数并加上当天的秒数
	return days * 24 * 60 * 60 + secondsToday;
}

void DateTime::addSeconds(long long seconds)
{
	// 将当前日期和时间转换为总秒数
	long long totalSeconds = *this;

	// 添加秒数
	totalSeconds += seconds;
	// 计算更新后的天数和剩余秒数
	const long long totalSecondsInCycle = 6311433600; // 总周期内的秒数

	// 使秒数在循环内
	totalSeconds = totalSeconds % totalSecondsInCycle;

	// 分别更新日期和时间
	long long days;
	long long remainingSeconds = totalSeconds % (24 * 60 * 60);
	//复制粘贴忘了改了，。卡了好久，记得实际意义啊
	if (remainingSeconds < 0) {
		days = totalSeconds / (24 * 60 * 60) - 1;//3252
	}
	else {
		days = totalSeconds / (24 * 60 * 60);//3252
	}
	*static_cast<Date*>(this) = Date((int)days);
	*static_cast<Time*>(this) = Time((int)remainingSeconds);
}

// DateTime类成员函数重载
DateTime DateTime::operator+(long long seconds) const 
{
	DateTime result = *this; // 创建当前对象的副本
	result.addSeconds(seconds); // 在副本上添加秒数
	return result; // 返回修改后的副本
}

// DateTime类友元函数重载
DateTime operator+(long long seconds, const DateTime& dt)
{
	return dt + seconds; // 重用成员函数重载
}

// DateTime类成员函数重载
DateTime DateTime::operator+(int seconds) const 
{
	DateTime result = *this; // 创建当前对象的副本
	result.addSeconds((long long)seconds); // 在副本上添加秒数
	return result; // 返回修改后的副本
}

// DateTime类友元函数重载
DateTime operator+(int seconds, const DateTime& dt) 
{
	return dt + (long long)seconds; // 重用成员函数重载
}


// DateTime类成员函数重载，减去秒数
DateTime DateTime::operator-(long long seconds) const
{
	DateTime result = *this; // 创建当前对象的副本
	result.addSeconds(-seconds); // 在副本上减去秒数
	return result; // 返回修改后的副本
}

// DateTime类成员函数重载，减去秒数（int参数）
DateTime DateTime::operator-(int seconds) const 
{
	DateTime result = *this; // 创建当前对象的副本
	result.addSeconds(-static_cast<long long>(seconds)); // 在副本上减去秒数
	return result; // 返回修改后的副本
}

// DateTime类友元函数重载，左侧为秒数
DateTime operator-(long long seconds, const DateTime& dt)
{
	// 因为seconds是左侧操作数，我们需要计算相对于1900-01-01 00:00:00的时间
	DateTime base(1900, 1, 1, 0, 0, 0);
	return base + (seconds - static_cast<long long>(dt));
}

// DateTime类友元函数重载，左侧为秒数（int参数）
DateTime operator-(int seconds, const DateTime& dt) 
{
	// 同上，但是seconds是int类型
	DateTime base(1900, 1, 1, 0, 0, 0);
	return base + (static_cast<long long>(seconds) - static_cast<long long>(dt));
}

long long DateTime::operator-(const DateTime& other) const 
{
	// 将两个日期时间转换为秒数
	long long seconds1 = *this;
	long long seconds2 = other;

	// 返回秒数差
	return seconds1 - seconds2;
}

// 前缀递增运算符
DateTime& DateTime::operator++() 
{
	this->addSeconds(1); // 增加一秒
	return *this; // 返回当前对象的引用
}

// 后缀递增运算符
DateTime DateTime::operator++(int)
{
	DateTime temp = *this; // 保存当前状态
	++(*this); // 使用前缀递增运算符
	return temp; // 返回未修改的对象
}

// 前缀递减运算符
DateTime& DateTime::operator--()
{
	this->addSeconds(-1); // 减少一秒
	return *this; // 返回当前对象的引用
}

// 后缀递减运算符
DateTime DateTime::operator--(int) 
{
	DateTime temp = *this; // 保存当前状态
	--(*this); // 使用前缀递减运算符
	return temp; // 返回未修改的对象
}



// 比较运算符重载
bool DateTime::operator>(const DateTime& other) const
{
	return static_cast<long long>(*this) > static_cast<long long>(other);
}

bool DateTime::operator>=(const DateTime& other) const 
{
	return static_cast<long long>(*this) >= static_cast<long long>(other);
}

bool DateTime::operator<(const DateTime& other) const
{
	return static_cast<long long>(*this) < static_cast<long long>(other);
}

bool DateTime::operator<=(const DateTime& other) const
{
	return static_cast<long long>(*this) <= static_cast<long long>(other);
}

bool DateTime::operator==(const DateTime& other) const
{
	return static_cast<long long>(*this) == static_cast<long long>(other);
}

bool DateTime::operator!=(const DateTime& other) const 
{
	return static_cast<long long>(*this) != static_cast<long long>(other);
}
