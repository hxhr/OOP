/* 2250748 �����q �Ű� */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

/* --- ����DateTime��ĳ�Ա����������ʵ��(����Ԫ��������Ҫ�Ĺ�������)  ---

	������Ҫ��ʾ��
	1��6�ι��캯���ܷ�պ����壬ֱ�Ӽ���Date��Time�Ĺ��캯����
	2��1�ι��캯�����ܷ���ѭ����ֱ�ӽ���Date��Time��һ�ι���������ʵ�֣� 
	3��DateTimeתlong long������ת���������ܷ���ѭ����������ֵ���ݹ������ʵ�֣�(��̿�������ֻ��һ��return)�� 
	4��DateTime��n�Ĳ�������Ҫ���弸�����͵���������أ� 
*/ 

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/


DateTime::DateTime(int y, int m, int d, int h, int mi, int s) 
{
	// ���ж����в����Ƿ�Ϸ�
	if (!(y >= 1900 && y <= 2099) || !(m >= 1 && m <= 12) ||
		!(d >= 1 && d <= day_in_month(y, m)) || (h < 0 || h > 23) ||
		(mi < 0 || mi > 59) || (s < 0 || s > 59)) {
		// ������κ�һ�������Ƿ�����ȫ����ʼ��ΪĬ��ֵ
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
	}
	else {
		// ������в������Ϸ�����ʹ�ô���Ĳ���
		Date::set(y, m, d);
		Time::set(h, mi, s);
	}
}


void DateTime::set(int y, int m, int d, int h, int mi, int s)
{
	//ֻҪ��һ���Ƿ���ֱ�ӳ�ʼֵ
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
	// �� Date ���л�ȡ����
	Date::get(y, m, d);
	// �� Time ���л�ȡʱ��
	Time::get(h, mi, s);
}

ostream& operator<<(ostream& os, const DateTime& dt)
{
	// ��������ڲ��֣������ʱ�䲿��
	os << static_cast<const Date&>(dt) << ' ';
	os << static_cast<const Time&>(dt);
	return os;
}

istream& operator>>(istream& is, DateTime& dt) 
{
	// ��ȡ���ں�ʱ��
	// �������ں�ʱ��������ʽΪ��yyyy-mm-dd hh:mm:ss
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
//	// ������ = ���� / (24Сʱ * 60���� * 60��)
//	int days = static_cast<int>(seconds / (24 * 60 * 60));
//
//	// ������ת��Ϊ����
//	*static_cast<Date*>(this) = Date(days);
//
//	// ����ʣ����������ת��Ϊʱ��
//	int remainingSeconds = static_cast<int>(seconds % (24 * 60 * 60));
//	*static_cast<Time*>(this) = Time(remainingSeconds);
//}


//�߼��Եĵ���������������֪��Ϊɶ���ԣ����ڲ��Գ����������ȷ���ˣ������ţ�֮�����о�Ϊɶ
DateTime::DateTime(long long seconds)
{
	//����ô�����6311347200
	//const long long totalDays = 365LL * 200 + 48; // 1900�굽2099������������������꣩
	//const long long totalSecondsInCycle = totalDays * 24 * 60 * 60; // �������ڵ�����6311347200

	//��ȷ����6311433600
	const long long totalSecondsInCycle = 6311433600;
	// ʹ������ѭ����
	seconds = seconds % totalSecondsInCycle ;//281028607

	// ����������ʣ������
	long long remainingSeconds = seconds % (24 * 60 * 60);
	long long days;
	if (remainingSeconds < 0) {
		days = seconds / (24 * 60 * 60)-1;//3252
	}
	else {
		days = seconds / (24 * 60 * 60);//3252
	}


	// ʹ��Date��Time��ת�����캯��
	*static_cast<Date*>(this) = Date((int)days);
	*static_cast<Time*>(this) = Time((int)remainingSeconds);
}


DateTime::operator long long() const 
{
	// ��ȡ��1900��1��1������������
	long long days = static_cast<long long>(static_cast<const Date&>(*this));

	// ��ȡ���������
	long long secondsToday = static_cast<long long>(static_cast<const Time&>(*this));

	// ������ת��Ϊ���������ϵ��������
	return days * 24 * 60 * 60 + secondsToday;
}

void DateTime::addSeconds(long long seconds)
{
	// ����ǰ���ں�ʱ��ת��Ϊ������
	long long totalSeconds = *this;

	// �������
	totalSeconds += seconds;
	// ������º��������ʣ������
	const long long totalSecondsInCycle = 6311433600; // �������ڵ�����

	// ʹ������ѭ����
	totalSeconds = totalSeconds % totalSecondsInCycle;

	// �ֱ�������ں�ʱ��
	long long days;
	long long remainingSeconds = totalSeconds % (24 * 60 * 60);
	//����ճ�����˸��ˣ������˺þã��ǵ�ʵ�����尡
	if (remainingSeconds < 0) {
		days = totalSeconds / (24 * 60 * 60) - 1;//3252
	}
	else {
		days = totalSeconds / (24 * 60 * 60);//3252
	}
	*static_cast<Date*>(this) = Date((int)days);
	*static_cast<Time*>(this) = Time((int)remainingSeconds);
}

// DateTime���Ա��������
DateTime DateTime::operator+(long long seconds) const 
{
	DateTime result = *this; // ������ǰ����ĸ���
	result.addSeconds(seconds); // �ڸ������������
	return result; // �����޸ĺ�ĸ���
}

// DateTime����Ԫ��������
DateTime operator+(long long seconds, const DateTime& dt)
{
	return dt + seconds; // ���ó�Ա��������
}

// DateTime���Ա��������
DateTime DateTime::operator+(int seconds) const 
{
	DateTime result = *this; // ������ǰ����ĸ���
	result.addSeconds((long long)seconds); // �ڸ������������
	return result; // �����޸ĺ�ĸ���
}

// DateTime����Ԫ��������
DateTime operator+(int seconds, const DateTime& dt) 
{
	return dt + (long long)seconds; // ���ó�Ա��������
}


// DateTime���Ա�������أ���ȥ����
DateTime DateTime::operator-(long long seconds) const
{
	DateTime result = *this; // ������ǰ����ĸ���
	result.addSeconds(-seconds); // �ڸ����ϼ�ȥ����
	return result; // �����޸ĺ�ĸ���
}

// DateTime���Ա�������أ���ȥ������int������
DateTime DateTime::operator-(int seconds) const 
{
	DateTime result = *this; // ������ǰ����ĸ���
	result.addSeconds(-static_cast<long long>(seconds)); // �ڸ����ϼ�ȥ����
	return result; // �����޸ĺ�ĸ���
}

// DateTime����Ԫ�������أ����Ϊ����
DateTime operator-(long long seconds, const DateTime& dt)
{
	// ��Ϊseconds������������������Ҫ���������1900-01-01 00:00:00��ʱ��
	DateTime base(1900, 1, 1, 0, 0, 0);
	return base + (seconds - static_cast<long long>(dt));
}

// DateTime����Ԫ�������أ����Ϊ������int������
DateTime operator-(int seconds, const DateTime& dt) 
{
	// ͬ�ϣ�����seconds��int����
	DateTime base(1900, 1, 1, 0, 0, 0);
	return base + (static_cast<long long>(seconds) - static_cast<long long>(dt));
}

long long DateTime::operator-(const DateTime& other) const 
{
	// ����������ʱ��ת��Ϊ����
	long long seconds1 = *this;
	long long seconds2 = other;

	// ����������
	return seconds1 - seconds2;
}

// ǰ׺���������
DateTime& DateTime::operator++() 
{
	this->addSeconds(1); // ����һ��
	return *this; // ���ص�ǰ���������
}

// ��׺���������
DateTime DateTime::operator++(int)
{
	DateTime temp = *this; // ���浱ǰ״̬
	++(*this); // ʹ��ǰ׺���������
	return temp; // ����δ�޸ĵĶ���
}

// ǰ׺�ݼ������
DateTime& DateTime::operator--()
{
	this->addSeconds(-1); // ����һ��
	return *this; // ���ص�ǰ���������
}

// ��׺�ݼ������
DateTime DateTime::operator--(int) 
{
	DateTime temp = *this; // ���浱ǰ״̬
	--(*this); // ʹ��ǰ׺�ݼ������
	return temp; // ����δ�޸ĵĶ���
}



// �Ƚ����������
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
