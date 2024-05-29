/* 2250748 �����q �Ű� */
#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* Time������� */ 
class Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 
	int hour;
	int minute;
	int second;
public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
	
		// ���캯��
	Time(); // Ĭ�Ϲ��캯��
	Time(int h, int m, int s);

	// set ��Ա����������
	void set(int h, int m, int s);
	void set(int h, int m);
	void set(int h);

	// get ��Ա����
	void get(int& h, int& m, int& s) const;

	// ��ʾ���ڵĳ�Ա����
	void show() const;

	// ת�����캯��,��19000101��ʼ��������intתdate
	Time(int s);

	//����ת������ dateתint
	operator int() const;

	void adds(int s);
	//����+   date+int
	Time operator+(int s) const;
	//int+date
	friend Time operator+(int s, const Time& time);

	//����-   date-int=date
	Time operator-(int s) const;
	//date-date=int
	int operator-(const Time& other) const;

	//++ --ǰ׺��׺
	// ǰ׺�������������
	Time& operator++();
	// ��׺�������������
	Time operator++(int);

	// ǰ׺�ݼ����������
	Time& operator--();
	// ��׺�ݼ����������
	Time operator--(int);

	//����������������
	friend ostream& operator<<(ostream& os, const Time& time);
	friend istream& operator>>(istream& is, Time& time);

	// �Ƚ����������
	bool operator>(const Time& rhs) const;
	bool operator>=(const Time& rhs) const;
	bool operator<(const Time& rhs) const;
	bool operator<=(const Time& rhs) const;
	bool operator==(const Time& rhs) const;
	bool operator!=(const Time& rhs) const;


};
