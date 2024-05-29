/* 2250748 �����q �Ű� */

#pragma once


#include "17-b1-TString.h"
using namespace std;


class TStringAdv : public TString {
public:
    // ʹ�û���Ĺ��캯��
    using TString::TString;

    TStringAdv& operator=(const TString& rhs) {
        // ���û���ĸ�ֵ������������ֵ
        TString::operator=(rhs);
        // ���ص�ǰ���������
        return *this;
    }

    // TStringAdv���еĳ�Ա��������
    TStringAdv substr(const int pos, const int len = INT_MAX) const;

    // // substr ��������

    // ������ assign ��������
    TStringAdv& assign(const TStringAdv& ts2);
    TStringAdv& assign(const char* s);

    // append ��������
    TStringAdv& append(const TStringAdv& ts2);
    TStringAdv& append(const char* s);
    TStringAdv& append(const char& c);

    // insert ��������
    TStringAdv& insert(const TStringAdv& ts2, int pos);
    TStringAdv& insert(const char* s, int pos);
    TStringAdv& insert(const char& c, int pos);

    // erase ��������
    TStringAdv& erase(const TStringAdv& ts2);
    TStringAdv& erase(const char* s);
    TStringAdv& erase(const char& c);

    char& at(const int n) const;

    int TStringLenAdv(const TStringAdv& str) const;

};
