/* 2250748 �����q �Ű� */

/* ���������Ҫ��ͷ�ļ����궨��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TString.h"
using namespace std;

/* ���� tstring ������г�Ա����������ʵ�� */

// ˽�г�Ա���� init ʵ��
void TString::init(const char* str)
{
	if (str && str[0] != '\0') {//���������������Ƿ�""����Ȼ�������NULL
		len = strlen(str);
		content = new(nothrow) char[len + 1];
		strcpy(content, str);
	}
	else {
		content = nullptr;
		len = 0;
	}
}

// Ĭ�Ϲ��캯��ʵ��
TString::TString() : content(nullptr), len(0) {}
// �� C �ַ�����ʼ���Ĺ��캯��ʵ��/��ʽ���õ�ת�����캯�����ȿ�����ʾ�����������ʽ����

TString::TString(const char* str)
{
	init(str);
}
// �������캯��ʵ��
TString::TString(const TString& other)
{
	init(other.content);
}
// ����ӵ����ַ�����TString����
TString::TString(char c)
{
	len = 1;
	content = new char[2];
	content[0] = c;
	content[1] = '\0';
}
TString::TString(int n) : content(nullptr), len(0) {}
// ��������ʵ��
TString::~TString()
{
	delete[] content;
}



//����>>
istream& operator>>(istream& is, TString& str)
{
	delete[] str.content;
	str.content = nullptr;
	str.len = 0;

	// ���������еĵ��ʹ�С
	const int bufferSize = 1000;
	char buffer[bufferSize];

	// ��ȡ���뵽������
	is >> ws; // ����ǰ���հ�
	char ch;
	int index = 0;
	bool word_finished = false;
	while (is.get(ch) && index < bufferSize - 1) {
		if (isspace(ch)) {
			if (!word_finished) {
				word_finished = true; // ������һ���հ��ַ����������ʶ�ȡ
			}
			if (ch == '\n') {
				is.unget(); // ����ǻ��з����Ż�ȥ�Ա��´ζ�ȡ
				break;
			}
		}
		else if (!word_finished) {
			buffer[index++] = ch; // ֻ���ڵ���δ����ʱ�Ŵ洢�ַ�
		}
	}
	buffer[index] = '\0'; // ȷ���ַ�����ȷ��ֹ

	// ���ƻ�������TString
	str.len = index;
	str.content = new char[str.len + 1];
	strcpy(str.content, buffer);

	return is;
}
//����<<
ostream& operator<<(ostream& os, const TString& str)
{
	//cout << "s3ӦΪ<NULL>��         ʵ�������" << (s3 * 5) << endl;
	//cout << "s3ӦΪ<NULL>��         ʵ�������" << (s3 = s3 * 5) << endl;

	if (str.content && str.content[0] != '\0') {//��һ�������޶����ڵ��Թ�����Ĵ����ӵ�
		os << str.content;
	}
	else {
		os << "<NULL>";
	}
	return os;
}

const char* TString::c_str() const
{
	if (content) {
		return content;
	}
	else {
		// ���content�ǿ�ָ�룬���Ƿ���һ��ָ����ַ�����ָ��
		// ����Ϊ��ȷ��c_str()��Զ���᷵��һ����ָ��
		return "";
	}
}


// ����һ��TString����ֵ
TString& TString::operator=(const TString& other)
{
	if (this != &other) {//�������Ҹ�ֵ
		delete[] content;
		init(other.content);
	}
	return *this;
}

TString& TString::operator=(const char* str)
{
	delete[] content; // ɾ����ǰ���������
	init(str); // ʹ��C����ַ������г�ʼ��
	return *this;
}

//��������һ������+��˼·
//һ����Ա���� +TString�����Դ���TString+char/char*/TString����Ϊ������ʽת��
//�������char/char*����߾�û�취�ˡ����Ի���Ҫд������Ԫ�����ֱ���char+TString��char*+TString

// ���� + ����������Դ���TString+char/char*/TString
TString TString::operator+(const TString& rhs) const
{
	int newLen = len + rhs.len;
	char* newContent = new char[newLen + 1];

	/*strcpy(newContent, this->content);
	strcat(newContent, rhs.content);*/
	//������ע������ôд����Ȼ����NULL�ͻ����
	// ���Ƶ�һ���ַ���
	if (this->content) {
		strcpy(newContent, this->content);
	}
	else {
		newContent[0] = '\0'; // �����NULL��������Ϊһ�����ַ���
	}

	// ���ӵڶ����ַ���
	if (rhs.content) {
		strcat(newContent, rhs.content);
	}


	TString result(newContent);
	delete[] newContent; // �����ڴ�й©
	return result;
}

// �ǳ�Ա���������� char ���������
TString operator+(char lhs, const TString& rhs)
{
	return TString(lhs) + rhs; // ת��Ϊ TString Ȼ����ó�Ա���� operator+
}

// �ǳ�Ա���������� const char* ���������
TString operator+(const char* lhs, const TString& rhs)
{
	return TString(lhs) + rhs; // ת��Ϊ TString Ȼ����ó�Ա���� operator+
}

// TString += TString��Ҳ������ʽת���� char �� const char*
TString& TString::operator+=(const TString& rhs)
{
	// ʹ�� operator+ �������ַ�����Ȼ��ֵ����ǰ����
	*this = *this + rhs;
	return *this;
}

//// TString::append ʵ��
//TString& TString::append(const TString& rhs)
//{
//	if (this != &rhs) { // ��ֹ������
//		int newLen = len + rhs.len;
//		char* newContent = new char[newLen + 1];
//		strcpy(newContent, content); // ���Ƶ�ǰ����
//		strcat(newContent, rhs.content); // ����rhs����
//
//		delete[] content; // ɾ��������
//		content = newContent; // ��������
//		len = newLen; // ���³���
//	}
//	return *this;
//}
//
TString TString::operator-(const TString& rhs) const
{
	// ���Ҫ�Ƴ����ַ���Ϊ�գ����ߵ�ǰ�ַ���Ϊ�գ�ֱ�ӷ��ص�ǰ�ַ����ĸ���
	if (rhs.content == nullptr || rhs.len == 0 || this->content == nullptr) {
		return *this;
	}

	TString result(this->content); // ������ǰ�ַ����ĸ���
	size_t pos = 0;
	bool found = true;
	// �ڵ�ǰ�ַ����в��ҵ�һ�γ���Ҫ�Ƴ����ַ�����λ��
	for (int i = 0; i < result.len; ++i) {
		found = true;
		for (int j = 0; j < rhs.len; ++j) {
			if (i + j >= result.len || result.content[i + j] != rhs.content[j]) {
				found = false;
				break;
			}
		}

		// ����ҵ���ƥ����ַ���
		if (found) {
			pos = i;
			break;
		}
	}

	// ����ҵ���һ��ƥ����Ƴ���
	if (pos < (unsigned int)result.len && found) {
		// ����һ���µ���ʱ�������洢�µ�����
		int newLen = result.len - rhs.len;
		char* newContent = new char[newLen + 1];

		// ����ǰ��Ĳ���
		strncpy(newContent, result.content, pos);

		// ���������ҵ��Ĳ��ֺ���ַ���
		strcpy(newContent + pos, result.content + pos + rhs.len);

		// �ͷžɵ��ڴ棬������result��������ݺͳ���
		delete[] result.content;
		result.content = newContent;
		result.len = newLen;
	}

	return result;
}

TString& TString::operator-=(const TString& rhs)
{
	// ʹ��֮ǰ����� operator- ���õ����
	*this = *this - rhs;
	return *this;
}

// *= �������ʵ��
TString& TString::operator*=(int factor)
{
	if (factor <= 0 || this->content == nullptr) {
		// ������ӷ�������ǰ�ַ���Ϊ�գ���ִ���κβ���
		return *this;
	}

	// �����µ��ַ�������
	int newLen = len * factor;
	char* newContent = new char[newLen + 1];

	// ���Ƶ�ǰ�ַ������ɱ�
	for (int i = 0; i < factor; ++i) {
		strcpy(newContent + i * len, content);
	}

	// �ͷžɵ��ڴ棬���µ�ǰ��������ݺͳ���
	delete[] content;
	content = newContent;
	len = newLen;

	return *this;
}


TString TString::operator*(int factor)
{
	TString result(*this); // ������ǰ����ĸ���

	if (factor <= 0 || this->content == nullptr) {
		// ������ӷ�������ǰ�ַ���Ϊ�գ����ؿ��ַ���
		result.content = new char[1];
		result.content[0] = '\0';
		result.len = 0;
		return result;
	}

	// ���Ƶ�ǰ�ַ������ɱ�
	for (int i = 1; i < factor; ++i) {
		result += *this;
	}

	return result;
}

TString TString::operator!() const
{
	if (content == nullptr) {
		// �����ǰ�ַ���Ϊ�գ�����һ�����ַ���
		return TString();
	}

	// �����µ��ַ�������
	int newLen = len;
	char* newContent = new char[newLen + 1];

	// ��ԭ�ַ�����ת���Ƶ����ַ�����
	for (int i = 0; i < len; ++i) {
		newContent[i] = content[len - 1 - i];
	}
	newContent[len] = '\0'; // ��� null ��β

	// ����һ���µ� TString ���󲢷���
	TString result(newContent);
	delete[] newContent; // ������Ҫ���ַ������ڴ棬�ͷŵ�
	return result;
}

bool TString::operator>(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) > 0;
}

bool TString::operator<(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) < 0;
}

bool TString::operator==(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) == 0;
}

bool TString::operator!=(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) != 0;
}

bool TString::operator>=(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) >= 0;
}

bool TString::operator<=(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) <= 0;
}

bool operator>(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // �� NULL ��Ϊָ����ַ�����ָ��
	return strcmp(lhs.c_str(), rhs_ptr) > 0;
}

bool operator<(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // �� NULL ��Ϊָ����ַ�����ָ��
	return strcmp(lhs.c_str(), rhs_ptr) < 0;
}

bool operator==(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // �� NULL ��Ϊָ����ַ�����ָ��
	return strcmp(lhs.c_str(), rhs_ptr) == 0;
}

bool operator!=(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // �� NULL ��Ϊָ����ַ�����ָ��
	return strcmp(lhs.c_str(), rhs_ptr) != 0;
}

bool operator>=(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // �� NULL ��Ϊָ����ַ�����ָ��
	return strcmp(lhs.c_str(), rhs_ptr) >= 0;
}

bool operator<=(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // �� NULL ��Ϊָ����ַ�����ָ��
	return strcmp(lhs.c_str(), rhs_ptr) <= 0;
}

bool operator>(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) > 0;
}

bool operator<(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) < 0;
}

bool operator==(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) == 0;
}

bool operator!=(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) != 0;
}

bool operator>=(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) >= 0;
}

bool operator<=(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) <= 0;
}

int TString::length() const
{
	return len;
}

// �����汾���±������ʵ��
char TString::operator[](int index) const
{
	if (index < 0 || index >= len || content == nullptr) {
		static char nullchar = '\0';
		// ����һ�����ַ��������׳�һ���쳣
		return nullchar;
	}
	return content[index];
}

// �ǳ����汾���±������ʵ��
char& TString::operator[](int index)
{
	if (index < 0 || index >= len || content == nullptr) {
		static char nullchar = '\0';
		// ����һ�����ַ������ã������׳�һ���쳣
		return nullchar;
	}
	return content[index];
}

/* �������Ҫ������ȫ�ֺ�����ʵ�֣�����д�ڴ˴� */

int TStringLen(const TString& str)
{
	return str.length(); // ����TString��length����
}