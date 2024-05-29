/* 2250748 �����q �Ű� */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TStringAdv.h"
#include "17-b1-TString.h"

TStringAdv TStringAdv::substr(const int pos, const int n) const
{
    // ���� pos Ϊ�� 1 ��ʼ������
    int adjustedPos = pos - 1;

    // ��� pos �Ƿ������ؿ��ַ���
    if (adjustedPos < 0 || adjustedPos >= this->len||n<=0) {
        return TStringAdv();
    }

    // ����ʵ��Ҫ���Ƶĳ���
    int actualLen = n;
    if (n == INT_MAX|| adjustedPos + n > this->len) {
        actualLen = this->len - adjustedPos;
    }

    // ����һ���µ� TStringAdv �������洢�Ӵ�
    TStringAdv subString;
    subString.content = new char[actualLen + 1];
    strncpy(subString.content, this->content + adjustedPos, actualLen);
    subString.content[actualLen] = '\0'; // ȷ���� null �ַ���ֹ
    subString.len = actualLen; // ������ȷ�ĳ���

    return subString;
}


// ʹ�� TStringAdv ������Ϊ������ assign ����ʵ��
TStringAdv& TStringAdv::assign(const TStringAdv& ts2) 
{
    if (this != &ts2) {
        delete[] this->content; // ɾ��������
        this->init(ts2.content); // ����������
        this->len = ts2.len; // �����³���
    }
    return *this; // ���ص�ǰ���������
}

// ʹ�� C ����ַ�����Ϊ������ assign ����ʵ��
TStringAdv& TStringAdv::assign(const char* s)
{
    delete[] this->content; // ɾ��������
    this->init(s); // ����������
    if (s) {
        this->len = strlen(s); // �����³���
    }
    else {
        this->len = 0; // ���ַ�����������Ϊ0
    }
    return *this; // ���ص�ǰ���������
}

// ׷�� TStringAdv ����
TStringAdv& TStringAdv::append(const TStringAdv& ts2)
{
    // ��������� TString::operator+= �������ַ���
    *this += ts2;
    return *this;
}

// ׷�� C ����ַ���
TStringAdv& TStringAdv::append(const char* s) 
{
    // ��������� TString::operator+= �������ַ���
    TString temp(s);  // ���� TString ��һ������ const char* �Ĺ��캯��
    *this += temp;
    return *this;
}

// ׷�ӵ����ַ�
TStringAdv& TStringAdv::append(const char& c) 
{
    char str[2] = { c, '\0' }; // ����һ����ʱ�� C ����ַ���
    TString temp(str);  // ʹ����ʱ�ַ������� TString ����
    *this += temp;
    return *this;
}

// ���� TStringAdv ����
TStringAdv& TStringAdv::insert(const TStringAdv& ts2, int pos)
{
    if (pos < 1 || pos > this->len + 1) {
        return *this; // ��� pos ���Ϸ������ص�ǰ����
    }
    TStringAdv before = this->substr(1, pos - 1); // �ӵ�һ���ַ���ʼ����ȡ�� pos - 1
    TStringAdv after = this->substr(pos);         // �� pos ��ʼ��ȡ
    *this = before + ts2 + after;
    return *this;
}

// ���� C ����ַ���
TStringAdv& TStringAdv::insert(const char* s, int pos)
{
    if (pos < 1 || pos > this->len + 1) {
        return *this; // ��� pos ���Ϸ������ص�ǰ����
    }
    TStringAdv before = this->substr(1, pos - 1); // �ӵ�һ���ַ���ʼ����ȡ�� pos - 1
    TStringAdv after = this->substr(pos);         // �� pos ��ʼ��ȡ
    *this = before + TStringAdv(s) + after;
    return *this;
}
//
//// ���뵥���ַ�
//TStringAdv& TStringAdv::insert(const char& c, int pos)
//{
//    if (pos < 1 || pos > this->len + 1) {
//        return *this; // ��� pos ���Ϸ������ص�ǰ����
//    }
//    TStringAdv before = this->substr(1, pos - 1); // �ӵ�һ���ַ���ʼ����ȡ�� pos - 1
//    TStringAdv after = this->substr(pos);         // �� pos ��ʼ��ȡ
//    char str[2] = { c, '\0' };
//    *this = before + TStringAdv(str) + after;
//    return *this;
//}

TStringAdv& TStringAdv::insert(const char& c, int pos) 
{
    if (pos < 1 || pos > this->len + 1) {
        return *this; // ��� pos ���Ϸ������ص�ǰ����
    }

    // ���⴦����� pos=1 �� c �� '\0'
    if (pos == 1 && c == '\0') {
        delete[] this->content; // �ͷ�ԭ�ַ���
        this->len = 0;
        this->content = nullptr;
        return *this;
    }

    TStringAdv before = this->substr(1, pos - 1); // �ӵ�һ���ַ���ʼ����ȡ�� pos - 1
    TStringAdv after = (c == '\0') ? TStringAdv() : this->substr(pos); // ��� c �� '\0'���� after Ϊ��

    char str[2] = { c, '\0' };
    // ��� c �� '\0'���򲻰�����
    *this = before + ((c == '\0') ? TStringAdv() : TStringAdv(str)) + after;
    return *this;
}


// �Ƴ� TStringAdv ����
TStringAdv& TStringAdv::erase(const TStringAdv& ts2)
{
    *this -= ts2;  // ʹ�� TString::operator-= ���Ƴ����ַ���
    return *this;
}

// �Ƴ� C ����ַ���
TStringAdv& TStringAdv::erase(const char* s)
{
    TStringAdv temp(s);  // �� C ����ַ���ת��Ϊ TStringAdv ����
    *this -= temp;  // ʹ�� TString::operator-= ���Ƴ����ַ���
    return *this;
}

TStringAdv& TStringAdv::erase(const char& c)
{
    char str[2] = { c, '\0' };  // ����һ���� null ��β���ַ���
    TStringAdv temp(str);      // ����һ��������һ�ַ��� TStringAdv ����
    *this -= temp;             // ʹ�� TStringAdv::operator-= ���Ƴ����ַ�
    return *this;
}


char& TStringAdv::at(const int n) const
{
    int num = n;
    if (n < 0 || n >= this->len) {
        num  = 0;
    }
    return this->content[num];
}

int TStringAdv::TStringLenAdv(const TStringAdv& str) const
{
    return str.length();
}
