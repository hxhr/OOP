/* 2250748 �����q �Ű� */
#include <iostream>
#include "16-b4.h"
using namespace std;

/* ���� Date ������г�Ա����������ʵ�� */

//���캯��
Date::Date() : year(2000), month(1), day(1) {} // Ĭ������2000��1��1��

Date::Date(int y, int m, int d) 
{
    // ���ȣ�����Ĭ��ֵ
    year = 2000;
    month = 1;
    day = 1;

    // Ȼ�󣬳���ʹ���ṩ��ֵ���и���
    // �������Ƿ�����Ч��Χ��
    if (y >= 1900 && y <= 2099) {
        year = y;
    }

    // ����·��Ƿ�����Ч��Χ��
    if (m >= 1 && m <= 12) {
        month = m;
    }

    // ��������Ƿ�����Ч��Χ�ڣ���������ݺ��·�
    if (d >= 1 && d <= day_in_month(year, month)) {
        day = d;
    }
}

//set����
void Date::set(int y, int m, int d)
{
    // ����겻��ָ����Χ�ڣ�����ΪĬ��ֵ
    if (y != 0) {
        if (y < 1900 || y > 2099) {
            year = 2000;
        }
        else {
            year = y;
        }
    }

    // ����²���ָ����Χ�ڣ�����ΪĬ��ֵ
    if (m != 0) {
        if (m < 1 || m > 12) {
            month = 1;
        }
        else {
            month = m;
        }

    }

    // ���������ȷ���յķ�Χ��������ڷ�Χ�ڣ�����ΪĬ��ֵ
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
    cout << year << "��" << month << "��" << day << "��"<<endl;
    
}

//ת�����캯����intתdate
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
        // ������ʼ����Ϊ 1900-01-01
        year = 1900;
        month = 1;
        day = 1;

        // �������
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
                break; // ��������꣬��ʣ������������������꣬���˳�ѭ��
            }
        }

        // �����·�
        while (days >= day_in_month(year, month)) {
            days -= day_in_month(year, month);
            month++;
        }

        // ʣ�������Ϊ���µ�����
        day += (days-1);

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
    days += day; // ��ȥ��ʼ��1900��1��1��

    return days;
}

void Date::addDays(int days)
{
    while (days > 0) {
        int daysInCurrentMonth = day_in_month(year, month);
        // ����������ӳ����˵�ǰ�·ݵ�ʣ����������ת����һ����
        if (day + days > daysInCurrentMonth) {
            days -= (daysInCurrentMonth - day + 1); // ��ȥ��ǰ��ʣ�������
            day = 1; // ����Ϊ���µĵ�һ��
            month++;
            if (month > 12) { // ����·ݳ�����12�£���ת����һ���1��
                month = 1;
                year++;
            }
        }
        else { // ����ֻ��Ҫ��������
            day += days;
            days = 0; // �Ѿ�������ϣ�û��ʣ�������
        }
    }

    while (days < 0) {
        // ����������ٵ����·ݵĿ�ʼ֮ǰ����ת����һ����
        if (day + days <= 0) {
            month--;
            if (month < 1) { // ����·ݼ��ٵ���1��֮ǰ����ת����һ���12��
                month = 12;
                year--;
            }
            days += day; // �����ϸ��µ�����
            day = day_in_month(year, month); // ����Ϊ�ϸ��µ����һ��
        }
        else { // ����ֻ��Ҫ��������
            day += days;
            days = 0; // �Ѿ�������ϣ�û��ʣ�������
        }
    }
    //��ֹ��Խ���½�
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
    os << date.year << "��" << date.month << "��" << date.day<<"��";
    return os;
    
}
// �������������������cin��
istream& operator>>(istream& is, Date& date)
{
    is >> date.year;
    if (date.year < 1900 || date.year > 2099) {
        date.year = 2000; // �����ݵĺϷ���
    }

    is >> date.month;
    if (date.month < 1 || date.month > 12) {
        date.month = 1; // ����·ݵĺϷ���
    } 

    is >> date.day;
    // ������ڵĺϷ��ԣ�����򻯴���ʵ�ʿ�����Ҫ�����ӵ��߼�������ÿ������
    if (date.day < 1 || date.day >day_in_month(date.year, date.month)) {
        date.day = 1;
    }

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
