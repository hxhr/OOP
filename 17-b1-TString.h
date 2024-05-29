/* 2250748 �����q �Ű� */

#pragma once

#include <iostream>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class TString {
private:

public:
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
	char* content;
	int   len;
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */

	void init(const char* str);//���캯���лᱻ���ã����⼸�����캯������Ҫ�ѵ��ظ��Ĵ���


	TString(); // Ĭ�Ϲ��캯��
	TString(const char* str); // �� C �ַ�����ʼ��
	TString(const TString& other); // �������캯��
	TString(char c);//����+ʱ����ʽת��
	TString(int n);  // ר�Ŵ��� NULL �Ĺ��캯��
	~TString(); // ��������

	friend istream& operator>>(istream& is, TString& str);//����>>����Ԫ����
	friend ostream& operator<<(ostream& os, const TString& str);//����<<����Ԫ����

	const char* c_str() const;//ȡ�ַ�����ֻ������

	TString& operator=(const TString& other); // ����һ��TString����ֵ
	TString& operator=(const char* str); // ��C����ַ�����ֵ

	TString operator+(const TString& rhs) const; //TString + char / char* / TString
	friend TString operator+(char lhs, const TString& rhs);//char+TString
	friend TString operator+(const char* lhs, const TString& rhs);//char*+TString

	TString& operator+=(const TString& rhs);//��Ϊ�ҿ�����ʽת����+=û�������������ֻдһ����Ա��������

	//TString& append(const TString& rhs);//char��char*����ʽת��

	TString operator-(const TString& rhs) const;//char��char*����ʽת��
	TString& operator-=(const TString& rhs); //��Ϊ�ҿ�����ʽת���� -= û�������������ֻдһ����Ա��������

	TString& operator*=(int factor);
	TString operator*(int factor);

	TString operator!() const; // ���� ! ������������ַ�����ת

	// �Ƚ����������
	bool operator>(const TString& rhs) const;
	bool operator<(const TString& rhs) const;
	bool operator==(const TString& rhs) const;
	bool operator!=(const TString& rhs) const;
	bool operator>=(const TString& rhs) const;
	bool operator<=(const TString& rhs) const;

	// Ϊ�Ƚ������������Ԫ����
	friend bool operator>(const TString& lhs, const char* rhs);
	friend bool operator<(const TString& lhs, const char* rhs);
	friend bool operator==(const TString& lhs, const char* rhs);
	friend bool operator!=(const TString& lhs, const char* rhs);
	friend bool operator>=(const TString& lhs, const char* rhs);
	friend bool operator<=(const TString& lhs, const char* rhs);

	friend bool operator>(const char* lhs, const TString& rhs);
	friend bool operator<(const char* lhs, const TString& rhs);
	friend bool operator==(const char* lhs, const TString& rhs);
	friend bool operator!=(const char* lhs, const TString& rhs);
	friend bool operator>=(const char* lhs, const TString& rhs);
	friend bool operator<=(const char* lhs, const TString& rhs);

	int length() const;

	char operator[](int index) const; // �����汾�����ڷ����ַ�
	char& operator[](int index); // �ǳ����汾�������޸��ַ�
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int TStringLen(const TString& str);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

