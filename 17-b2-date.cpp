/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/* --- 给出Date类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */ 

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

//构造函数
Date::Date() : year(1900), month(1), day(1) {} // 默认日期1900年1月1日

Date::Date(int y, int m, int d)
{
    //任意错都直接设成1900-1-1
    if (!(y >= 1900 && y <= 2099) || !(m >= 1 && m <= 12) || !(d >= 1 && d <= day_in_month(y, m))) {
        year = 1900;
        month = 1;
        day = 1;
    }
    else {
        year = y;
        month = m;
        day = d;
    }
}

//set函数
void Date::set(int y, int m, int d)
{
    //任意错都直接设成1900-1-1
    if ((y < 1900 || y > 2099) || (m < 1 || m > 12) || (d < 1 || d > day_in_month(y, m))) {
        year = 1900;
        month = 1;
        day = 1;
    }
    else {
        year = y;
        month = m;
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
    cout << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') <<day<<endl;


}

void Date::show_endless() const
{
    cout << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day;


}

//修改
//转换构造函数，int转date
Date::Date(int days)
{
    // 设置起始日期为 1900-01-01
    year = 1900;
    month = 1;
    day = 1;

    //45259
    // 调整天数，确保循环
    const int totalDays = 365 * 200 + 48+1; // 从1900年到2099年总天数（包括闰年）
    if (days < 0) {
        days = totalDays + days % totalDays;
    }
    else {
        days = days % totalDays;
    }

    // 计算年份
    while (days > 365) {
        if (is_leapyear(year) && days >= 366) {
            days -= 366;
            year++;
        }
        else if (!is_leapyear(year)) {
            days -= 365;
            year++;
        }
    }

    // 计算月份
    while (days > 0) {
        int daysInMonth = day_in_month(year, month);
        if (days > daysInMonth) {
            days -= daysInMonth;
            month++;
        }
        else {
            day += days;
            days = 0;
        }
    }
    //最后的day+=days可能冒出，再验证一下就行
    if (day > day_in_month(year, month)) {
        day -= day_in_month(year, month);
        month++;
    }
    if (month > 12) {
        month = 1;
        year++;
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
    days += day-1; // 减去起始日1900年1月1日

    return days;
}

void Date::addDays(int days) 
{
    days += (int)*this;
    // 设置起始日期为 1900-01-01
    year = 1900;
    month = 1;
    day = 1;

    //45259
    // 调整天数，确保循环
    const int totalDays = 365 * 200 + 48 + 1; // 从1900年到2099年总天数（包括闰年）
    if (days < 0) {
        days = totalDays + days % totalDays;
    }
    else {
        days = days % totalDays;
    }

    // 计算年份
    while (days > 365) {
        if (is_leapyear(year) && days >= 366) {
            days -= 366;
            year++;
        }
        else if (!is_leapyear(year)) {
            days -= 365;
            year++;
        }
    }

    // 计算月份
    while (days > 0) {
        int daysInMonth = day_in_month(year, month);
        if (days > daysInMonth) {
            days -= daysInMonth;
            month++;
        }
        else {
            day += days;
            days = 0;
        }
    }
    //最后的day+=days可能冒出，再验证一下就行
    if (day > day_in_month(year, month)) {
        day -= day_in_month(year, month);
        month++;
    }
    if (month > 12) {
        month = 1;
        year++;
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
    os << date.year << "-" << setw(2) << setfill('0')<<date.month  << "-"  <<setw(2) << setfill('0')<<date.day ;
    return os;

}
// 重载输入运算符（用于cin）
istream& operator>>(istream& is, Date& date)
{
    //错一个就1900-1-1，直接让set帮我判了 
    is >> date.year;
     is >> date.month;
    is >> date.day;
    date.set(date.year, date.month, date.day);

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
