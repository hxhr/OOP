/* 2250748 �����q �Ű� */
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- ����Time��ĳ�Ա����������ʵ��(����Ԫ��������Ҫ�Ĺ�������)  --- */ 



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

//set����
void Time::set(int h, int m, int s)
{
	//�����ֱ�����00-00-00
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

	// ���㵱ǰ����У���1�µ���ǰ�·ݵ���������������ǰ�·ݣ�
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
	Time newTime = *this; // ������ǰ����ĸ���
	newTime.adds(s); // �ڸ������������
	return newTime; // �����޸ĺ�ĸ���

}

Time operator+(int s, const Time& time)
{
	return time + s;
}

Time Time::operator-(int s) const
{
	Time newTime = *this; // ������ǰ����ĸ���
	newTime.adds(-s); // �ڸ������������
	return newTime; // �����޸ĺ�ĸ���

}

int Time::operator-(const Time& other) const
{
	int s1 = (int)(*this);
	int s2 = (int)(other);
	return s1 - s2;
}

Time& Time::operator++()
{
	this->adds(1); // ��һ��
	return *this; // ���ص�ǰ���������
}

Time Time::operator++(int)
{
	Time temp = *this; // ���浱ǰ״̬
	++(*this); // ʹ��ǰ׺���������
	return temp; // ����δ�޸ĵĶ���

}

Time& Time::operator--()
{
	this->adds(-1); // ��һ��
	return *this; // ���ص�ǰ���������
}

Time Time::operator--(int)
{
	Time temp = *this; // ���浱ǰ״̬
	--(*this); // ʹ��ǰ׺�ݼ������
	return temp; // ����δ�޸ĵĶ���
}

ostream& operator<<(ostream& os, const Time& time)
{
	os << setw(2) << setfill('0') << time.hour << ":" << setw(2) << setfill('0') << time.minute << ":" << setw(2) << setfill('0') <<time.second;
	return os;

}


istream& operator>>(istream& is, Time& time)
{
	//��һ����1900-1-1��ֱ����set�������� 
	is >> time.hour;
	is >> time.minute;
	is >>time.second;
	time.set(time.hour, time.minute, time.second);

	return is;
}


bool Time::operator>(const Time& rhs) const
{
	// ���ȱȽ���ݣ���������ͬ����Ƚ��·ݣ�����·�Ҳ��ͬ����Ƚ�����
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
