/* 2250748 �����q �Ű� */
#pragma once
using namespace std;

#include "17-b2-date.h"
#include "17-b2-time.h"

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* DateTime��Ļ���Ҫ��
	1�����������κ����ݳ�Ա
	2�������ٶ����Ա���� 
*/

class DateTime:public Date, public Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 

public:
	// Ĭ�Ϲ��캯����ʼ��Ϊ1900-01-01 00:00:00
	DateTime() : Date(1900, 1, 1), Time(0, 0, 0) {}

	// ���캯����ʼ���ض����ں�ʱ��
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


