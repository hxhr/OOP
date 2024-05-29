/* 2250748 �����q �Ű� */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/* --- ����Date��ĳ�Ա����������ʵ��(����Ԫ��������Ҫ�Ĺ�������)  --- */ 

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/

//���캯��
Date::Date() : year(1900), month(1), day(1) {} // Ĭ������1900��1��1��

Date::Date(int y, int m, int d)
{
    //�����ֱ�����1900-1-1
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

//set����
void Date::set(int y, int m, int d)
{
    //�����ֱ�����1900-1-1
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
    set(y, m, 1); // Ĭ����Ϊ1
}

void Date::set(int y)
{
    set(y, 1, 1); // Ĭ���º��ն�Ϊ1
}

//get����
void Date::get(int& y, int& m, int& d) const
{
    y = year;
    m = month;
    d = day;
}

//show����
void Date::show() const
{
    cout << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') <<day<<endl;


}

void Date::show_endless() const
{
    cout << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day;


}

//�޸�
//ת�����캯����intתdate
Date::Date(int days)
{
    // ������ʼ����Ϊ 1900-01-01
    year = 1900;
    month = 1;
    day = 1;

    //45259
    // ����������ȷ��ѭ��
    const int totalDays = 365 * 200 + 48+1; // ��1900�굽2099�����������������꣩
    if (days < 0) {
        days = totalDays + days % totalDays;
    }
    else {
        days = days % totalDays;
    }

    // �������
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

    // �����·�
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
    //����day+=days����ð��������֤һ�¾���
    if (day > day_in_month(year, month)) {
        day -= day_in_month(year, month);
        month++;
    }
    if (month > 12) {
        month = 1;
        year++;
    }
}


//����ת������ dateתint
Date::operator int() const
{
    int days = 0;
    // �����1900�굽��ǰ��ݵ���������������ǰ��ݣ�
    for (int y = 1900; y < year; ++y) {
        days += is_leapyear(y) ? 366 : 365;
    }

    // ���㵱ǰ����У���1�µ���ǰ�·ݵ���������������ǰ�·ݣ�
    for (int m = 1; m < month; ++m) {
        days += day_in_month(year, m);
    }

    // ���ϵ�ǰ�·��е�����
    days += day-1; // ��ȥ��ʼ��1900��1��1��

    return days;
}

void Date::addDays(int days) 
{
    days += (int)*this;
    // ������ʼ����Ϊ 1900-01-01
    year = 1900;
    month = 1;
    day = 1;

    //45259
    // ����������ȷ��ѭ��
    const int totalDays = 365 * 200 + 48 + 1; // ��1900�굽2099�����������������꣩
    if (days < 0) {
        days = totalDays + days % totalDays;
    }
    else {
        days = days % totalDays;
    }

    // �������
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

    // �����·�
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
    //����day+=days����ð��������֤һ�¾���
    if (day > day_in_month(year, month)) {
        day -= day_in_month(year, month);
        month++;
    }
    if (month > 12) {
        month = 1;
        year++;
    }



}

//����+ date+int
Date Date::operator+(int days) const
{
    Date newDate = *this; // ������ǰ����ĸ���
    newDate.addDays(days); // �ڸ������������
    return newDate; // �����޸ĺ�ĸ���
}
//����int+date
Date operator+(int days, const Date& date)
{
    return date + days; // ���������� Date + int ������
}

//����date-int=date
Date Date::operator-(int days) const
{
    Date newDate = *this;
    newDate.addDays(-days); // ʹ��֮ǰ�����addDays����
    return newDate;
}
//����date-date=int
int Date::operator-(const Date& other) const
{
    // ����������ת��Ϊ������Ȼ������ֵ
    int thisDays = static_cast<int>(*this); // �����д�Date��int������ת��
    int otherDays = static_cast<int>(other);
    return thisDays - otherDays;
}

// ǰ׺���������
Date& Date::operator++()
{
    this->addDays(1); // ��һ��
    return *this; // ���ص�ǰ���������
}

// ��׺���������
Date Date::operator++(int)
{
    Date temp = *this; // ���浱ǰ״̬
    ++(*this); // ʹ��ǰ׺���������
    return temp; // ����δ�޸ĵĶ���
}

// ǰ׺�ݼ������
Date& Date::operator--()
{
    this->addDays(-1); // ��һ��
    return *this; // ���ص�ǰ���������
}

// ��׺�ݼ������
Date Date::operator--(int)
{
    Date temp = *this; // ���浱ǰ״̬
    --(*this); // ʹ��ǰ׺�ݼ������
    return temp; // ����δ�޸ĵĶ���
}

// ������������������cout��
ostream& operator<<(ostream& os, const Date& date)
{
    os << date.year << "-" << setw(2) << setfill('0')<<date.month  << "-"  <<setw(2) << setfill('0')<<date.day ;
    return os;

}
// �������������������cin��
istream& operator>>(istream& is, Date& date)
{
    //��һ����1900-1-1��ֱ����set�������� 
    is >> date.year;
     is >> date.month;
    is >> date.day;
    date.set(date.year, date.month, date.day);

    return is;
}

bool Date::operator>(const Date& rhs) const
{
    // ���ȱȽ���ݣ���������ͬ����Ƚ��·ݣ�����·�Ҳ��ͬ����Ƚ�����
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
/* �������Ҫ������ȫ�ֺ�����ʵ�֣�����д�ڴ˴� */

//�ж��Ƿ�������ĺ���
bool is_leapyear(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

//�����·ݶ�Ӧ������
int day_in_month(int y, int m)
{
    if (m < 1 || m > 12) {
        return 0;
    }
    int days[12] = { 31, 28 + is_leapyear(y), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return days[m - 1];
}
