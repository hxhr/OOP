/* 2250748 王渝鹮 信安 */
#include <iostream>
#include "16-b4.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */

//构造函数
Date::Date() : year(2000), month(1), day(1) {} // 默认日期2000年1月1日

Date::Date(int y, int m, int d) 
{
    // 首先，设置默认值
    year = 2000;
    month = 1;
    day = 1;

    // 然后，尝试使用提供的值进行更新
    // 检查年份是否在有效范围内
    if (y >= 1900 && y <= 2099) {
        year = y;
    }

    // 检查月份是否在有效范围内
    if (m >= 1 && m <= 12) {
        month = m;
    }

    // 检查日期是否在有效范围内，依赖于年份和月份
    if (d >= 1 && d <= day_in_month(year, month)) {
        day = d;
    }
}

//set函数
void Date::set(int y, int m, int d)
{
    // 如果年不在指定范围内，设置为默认值
    if (y != 0) {
        if (y < 1900 || y > 2099) {
            year = 2000;
        }
        else {
            year = y;
        }
    }

    // 如果月不在指定范围内，设置为默认值
    if (m != 0) {
        if (m < 1 || m > 12) {
            month = 1;
        }
        else {
            month = m;
        }

    }

    // 根据年和月确定日的范围，如果不在范围内，设置为默认值
    if (d == 0) {
        d = day;
    }
    if (d < 1 || d > day_in_month(year, month)) {
        day = 1;
    }
    else {
        day = d;
    }
}

void Date::set(int y, int m) 
{
    set(y, m, 1); // 默认日为1
}

void Date::set(int y) 
{
    set(y, 1, 1); // 默认月和日都为1
}

//get函数
void Date::get(int& y, int& m, int& d) const 
{
    y = year;
    m = month;
    d = day;
}

//show函数
void Date::show() const 
{
    cout << year << "年" << month << "月" << day << "日"<<endl;
    
}

//转换构造函数，int转date
Date::Date(int days)
{
    if (days <= 1) {
        year = 1900;
        month = 1;
        day = 1;
    }
    else if (days >= 73049) {
        year = 2099;
        month = 12;
        day = 31;
    }
    else {
        // 设置起始日期为 1900-01-01
        year = 1900;
        month = 1;
        day = 1;

        // 计算年份
        while (days >= 365) {
            if (is_leapyear(year) && days >= 366) {
                days -= 366;
                year++;
            }
            else if (!is_leapyear(year)) {
                days -= 365;
                year++;
            }
            else {
                break; // 如果是闰年，但剩余天数不足以完成整年，则退出循环
            }
        }

        // 计算月份
        while (days >= day_in_month(year, month)) {
            days -= day_in_month(year, month);
            month++;
        }

        // 剩余的天数为当月的日期
        day += (days-1);

    }
}

//类型转换函数 date转int
Date::operator int() const
{
    int days = 0;
    // 计算从1900年到当前年份的天数（不包括当前年份）
    for (int y = 1900; y < year; ++y) {
        days += is_leapyear(y) ? 366 : 365;
    }

    // 计算当前年份中，从1月到当前月份的天数（不包括当前月份）
    for (int m = 1; m < month; ++m) {
        days += day_in_month(year, m);
    }

    // 加上当前月份中的天数
    days += day; // 减去起始日1900年1月1日

    return days;
}

void Date::addDays(int days)
{
    while (days > 0) {
        int daysInCurrentMonth = day_in_month(year, month);
        // 如果天数增加超过了当前月份的剩余天数，则转到下一个月
        if (day + days > daysInCurrentMonth) {
            days -= (daysInCurrentMonth - day + 1); // 减去当前月剩余的天数
            day = 1; // 重置为新月的第一天
            month++;
            if (month > 12) { // 如果月份超过了12月，则转到下一年的1月
                month = 1;
                year++;
            }
        }
        else { // 否则，只需要增加日子
            day += days;
            days = 0; // 已经增加完毕，没有剩余的天数
        }
    }

    while (days < 0) {
        // 如果天数减少到了月份的开始之前，则转到上一个月
        if (day + days <= 0) {
            month--;
            if (month < 1) { // 如果月份减少到了1月之前，则转到上一年的12月
                month = 12;
                year--;
            }
            days += day; // 增加上个月的天数
            day = day_in_month(year, month); // 重置为上个月的最后一天
        }
        else { // 否则，只需要减少日子
            day += days;
            days = 0; // 已经减少完毕，没有剩余的天数
        }
    }
    //防止超越上下界
    if (year < 1900) {
        year = 1900;
        month = 1;
        day = 1;
    }
    if (year > 2099) {
        year = 2099;
        month = 12;
        day = 31;
    }
}

//重载+ date+int
Date Date::operator+(int days) const 
{
    Date newDate = *this; // 创建当前对象的副本
    newDate.addDays(days); // 在副本上添加天数
    return newDate; // 返回修改后的副本
}
//重载int+date
Date operator+(int days, const Date& date)
{
    return date + days; // 这里重用了 Date + int 的重载
}

//重载date-int=date
Date Date::operator-(int days) const 
{
    Date newDate = *this;
    newDate.addDays(-days); // 使用之前定义的addDays方法
    return newDate;
}
//重载date-date=int
int Date::operator-(const Date& other) const 
{
    // 将两个日期转换为天数，然后计算差值
    int thisDays = static_cast<int>(*this); // 假设有从Date到int的类型转换
    int otherDays = static_cast<int>(other);
    return thisDays - otherDays;
}

// 前缀递增运算符
Date& Date::operator++() 
{
    this->addDays(1); // 加一天
    return *this; // 返回当前对象的引用
}

// 后缀递增运算符
Date Date::operator++(int) 
{
    Date temp = *this; // 保存当前状态
    ++(*this); // 使用前缀递增运算符
    return temp; // 返回未修改的对象
}

// 前缀递减运算符
Date& Date::operator--()
{
    this->addDays(-1); // 减一天
    return *this; // 返回当前对象的引用
}

// 后缀递减运算符
Date Date::operator--(int) 
{
    Date temp = *this; // 保存当前状态
    --(*this); // 使用前缀递减运算符
    return temp; // 返回未修改的对象
}

// 重载输出运算符（用于cout）
ostream& operator<<(ostream& os, const Date& date) 
{
    os << date.year << "年" << date.month << "月" << date.day<<"日";
    return os;
    
}
// 重载输入运算符（用于cin）
istream& operator>>(istream& is, Date& date)
{
    is >> date.year;
    if (date.year < 1900 || date.year > 2099) {
        date.year = 2000; // 检查年份的合法性
    }

    is >> date.month;
    if (date.month < 1 || date.month > 12) {
        date.month = 1; // 检查月份的合法性
    } 

    is >> date.day;
    // 检查日期的合法性，这里简化处理，实际可能需要更复杂的逻辑来考虑每月天数
    if (date.day < 1 || date.day >day_in_month(date.year, date.month)) {
        date.day = 1;
    }

    return is;
}

bool Date::operator>(const Date& rhs) const
{
    // 首先比较年份，如果年份相同，则比较月份，如果月份也相同，则比较日期
    if (year != rhs.year) return year > rhs.year;
    if (month != rhs.month) return month > rhs.month;
    return day > rhs.day;
}

bool Date::operator>=(const Date& rhs) const 
{
    return *this > rhs || *this == rhs;
}

bool Date::operator<(const Date& rhs) const 
{
    return !(*this >= rhs);
}

bool Date::operator<=(const Date& rhs) const 
{
    return *this < rhs || *this == rhs;
}

bool Date::operator==(const Date& rhs) const 
{
    return year == rhs.year && month == rhs.month && day == rhs.day;
}

bool Date::operator!=(const Date& rhs) const
{
    return !(*this == rhs);
}
/* 如果有需要的其它全局函数的实现，可以写于此处 */

//判断是否是闰年的函数
bool is_leapyear(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

//返回月份对应的天数
int day_in_month(int y, int m)
{
	if (m < 1 || m > 12) {
		return 0;
	}
	int days[12] = { 31, 28 + is_leapyear(y), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return days[m - 1];
}
