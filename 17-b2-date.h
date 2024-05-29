/* 2250748 �����q �Ű� */

#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

bool is_leapyear(int y);
int day_in_month(int y, int m);








/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
private:
	int year;
	int month;
	int day;
	/* ������������ݳ�Ա */
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */

	// ���캯��
	Date(); // Ĭ�Ϲ��캯��
	Date(int y, int m, int d);

	// set ��Ա����������
	void set(int y, int m, int d);
	void set(int y, int m);
	void set(int y);

	// get ��Ա����
	void get(int& y, int& m, int& d) const;

	// ��ʾ���ڵĳ�Ա����
	void show() const;
	//�޻س���
	void show_endless() const;


	// ת�����캯��,��19000101��ʼ��������intתdate
	Date(int days);

	//����ת������ dateתint
	operator int() const;

	void addDays(int days);
	//����+   date+int
	Date operator+(int days) const;
	//int+date
	friend Date operator+(int days, const Date& date);

	//����-   date-int=date
	Date operator-(int days) const;
	//date-date=int
	int operator-(const Date& other) const;

	//++ --ǰ׺��׺
	// ǰ׺�������������
	Date& operator++();
	// ��׺�������������
	Date operator++(int);

	// ǰ׺�ݼ����������
	Date& operator--();
	// ��׺�ݼ����������
	Date operator--(int);

	//����������������
	friend ostream& operator<<(ostream& os, const Date& date);
	friend istream& operator>>(istream& is, Date& date);

	// �Ƚ����������
	bool operator>(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator==(const Date& rhs) const;
	bool operator!=(const Date& rhs) const;

};

